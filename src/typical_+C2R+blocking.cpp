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
	
	start=MPI_Wtime();
	for(int i=0;i<n;i++) local_sumofcol[i]=0;
        int tep=0;
        for(int i=0;i<m*n;i++){
                local_sumofcol[tep]+=local_sinkhorn[i];
                tep++;
                if(tep==n) tep=0;
        }
	const int ii=1000,jj=4,kk=m/jj;
	double temp[ii];
	double *x0=&local_sinkhorn[0];
	double *y0=x0,*z0=x0;
	for(int i=0;i<n;i+=ii){
		double *t0=&sumofcol[i],*t1=&local_sumofcol[i];
		for(int j=0;j<ii;j++,t0++,t1++){
			temp[j]=(*t0)/(*t1);
		}
		for(int j=0;j<kk;j++){
			for(int h=0;h<jj;h++){
				for(int t=0;t<ii;t++,z0++){
					*z0*=temp[t];
				}
				y0+=n;
				z0=y0;
			}
		}
		x0+=ii;
		y0=x0;
		z0=y0;
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
