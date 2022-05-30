#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <mpi.h>
#include <iostream>
#include <immintrin.h>
#include <emmintrin.h>

int main(int argc,char *argv[]){
	int m=atoi(argv[1]);
	int n=atoi(argv[2]);
	int world_rank,world_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    	double *local_sinkhorn=new double[m*n];
	double *copy_sinkhorn=new double[m*n];
	double *sumofcol=new double[n];
	double *local_sumofcol=new double[n];
	for(int i=0;i<m*n;i++){
        	local_sinkhorn[i]=(double)rand()/(double)(RAND_MAX)*100;                      
        }
	if(world_rank==0){
		for(int i=0;i<n;i++){
			sumofcol[i]=(double)rand()/(double)(RAND_MAX)*100;
		}
	}
	MPI_Bcast(sumofcol,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	double start,finish,time1,time2,time01,time02;
	
	for(int i=0;i<m*n;i++){
		copy_sinkhorn[i]=local_sinkhorn[i];
	}
	double temp1=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			temp1+=fabs(local_sinkhorn[j+i*n]-copy_sinkhorn[j+i*n]);
		}
	}
	//if(world_rank==0) printf("error1=%f\n",temp1);
		
	start=MPI_Wtime();
	for(int i=0;i<n;i++){
		double temp=0;
		for(int j=0;j<m;j++){
			temp+=local_sinkhorn[i+j*n];
		}
		local_sumofcol[i]=temp;
	}
	double temp2=0;
	for(int i=0;i<n;i++){
		temp2=sumofcol[i]/local_sumofcol[i];
		for(int j=0;j<m;j++){
			copy_sinkhorn[i+j*n]*=temp2;
		}
	}
	finish=MPI_Wtime();
	time01=(finish-start)*1000;
	MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
	//if(world_rank==0) printf("%.3f, ",time1);
	
	start=MPI_Wtime();
	__m256d vec_0=_mm256_setzero_pd();__m256d vec_1=_mm256_setzero_pd();__m256d vec_2=_mm256_setzero_pd();__m256d vec_3=_mm256_setzero_pd();
        __m256d vec_t=_mm256_setzero_pd();__m256d res=_mm256_setzero_pd();
        for(int i=0;i<n;i++) local_sumofcol[i]=0;
        double *p0=&local_sumofcol[0],*p1=&local_sinkhorn[0],*p2=p0;
        int tep1=0;
        for(int i=0;i<m*n/8;i++,p1+=8){
                vec_0=_mm256_loadu_pd(p0);
                vec_1=_mm256_loadu_pd(p0+4);
                vec_2=_mm256_loadu_pd(p1);
                vec_3=_mm256_loadu_pd(p1+4);
                vec_0=_mm256_add_pd(vec_0,vec_2);_mm256_storeu_pd(p0,vec_0);
                vec_1=_mm256_add_pd(vec_1,vec_3);_mm256_storeu_pd(p0+4,vec_1);
                //(*p0)+=(*p1);
                tep1+=8;
                if(tep1==n) {tep1=0;p0=p2;}
                else p0+=8;
        }
	const int ii=1000,jj=4,kk=m/jj;
	double temp[ii];
	double *x0=&local_sinkhorn[0],*x1=&local_sinkhorn[n],*x2=&local_sinkhorn[2*n],*x3=&local_sinkhorn[3*n];
	double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
	for(int i=0;i<n;i+=ii){
		double *t0=&sumofcol[i],*t1=&local_sumofcol[i];
		for(int j=0;j<ii;j++,t0++,t1++){
			temp[j]=(*t0)/(*t1);
		}
		for(int j=0;j<kk;j++){
			for(int t=0;t<ii;t+=4,z0+=4,z1+=4,z2+=4,z3+=4){
			__asm__ __volatile__(
				"movq %0, %%rax\n"
				"movq %1, %%rbx\n"
				"movq %2, %%rcx\n"
				"movq %3, %%rdx\n"    
				"vmovupd (%%rax), %%ymm0\n"				    
				"vmovupd (%%rbx), %%ymm1\n"
				"vmulpd %%ymm0, %%ymm1, %%ymm1\n"
				"vmovupd (%%rcx), %%ymm2\n"
				"vmovupd (%%rdx), %%ymm3\n" 
				"vmulpd %%ymm0, %%ymm2, %%ymm2\n"
				"movq %4, %%rax\n"
				"vmulpd	%%ymm0, %%ymm3, %%ymm3\n"
				"vmovupd (%%rax), %%ymm4\n"
				"vmovupd %%ymm1, (%%rbx)\n"
				"vmovupd %%ymm2, (%%rcx)\n"
				"vmulpd %%ymm0, %%ymm4, %%ymm4\n"
				"vmovupd %%ymm3, (%%rdx)\n"				
				"vmovupd %%ymm4, (%%rax)"
				:             
				:"a"(&temp[t]),"b"(z0),"c"(z1),"d"(z2),"g"(z3)
				:"cc","memory","ymm0","ymm1","ymm2","ymm3","ymm4");							
			}
			y0+=jj*n,y1+=jj*n,y2+=jj*n,y3+=jj*n;
			z0=y0,z1=y1,z2=y2,z3=y3;
		}
		x0+=ii,x1+=ii,x2+=ii,x3+=ii;
		y0=x0,y1=x1,y2=x2,y3=x3;
		z0=y0,z1=y1,z2=y2,z3=y3;
	}
	finish=MPI_Wtime();
	time02=(finish-start)*1000;
	MPI_Allreduce(&time02,&time2,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
	if(world_rank==0) printf("%.3f, ",time2);
	
	double temp3=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			temp3+=fabs(local_sinkhorn[j+i*n]-copy_sinkhorn[j+i*n]);
		}
	}
	//if(world_rank==0) printf("error2=%f\n",temp3);
	
	MPI_Finalize();	
	delete []sumofcol;
	delete []local_sinkhorn;
	delete []copy_sinkhorn;
	delete []local_sumofcol;
	return 0;
}
