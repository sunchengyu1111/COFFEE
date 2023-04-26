#include "COFFEE_TestCPU.h"

void CPU_Test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank) {
	int count=0;
        double error=0;
        bool loop=true;
        double start,finish;
        double time1,time01;
        start=MPI_Wtime();
        while(loop){
                if(world_rank==0){
                        //printf("count %d\n",count);
                        count++;
                }

                //copy data
                for(int i=0;i<m*n;i++){
                        copy_sinkhorn[i]=local_sinkhorn[i];
                }

                //row
                int startrow=world_rank*m;
                for(int i=0;i<m;i++){
                        double temp=0;
                        for(int j=0;j<n;j++){
                                temp+=local_sinkhorn[i*n+j];
                        }
                        temp=sumofrow[startrow+i]/temp;
                        for(int j=0;j<n;j++){
                                local_sinkhorn[i*n+j]*=temp;
                        }
                }

                //col
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
		MPI_Allreduce(local_sumofcol,allreduce_sumofcol,n,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
                const int ii=1000,jj=4,kk=m/jj,hh=m%jj;
                double temp[ii];
                double *x0=&local_sinkhorn[0],*x1=&local_sinkhorn[n],*x2=&local_sinkhorn[2*n],*x3=&local_sinkhorn[3*n];
                double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
                for(int i=0;i<n;i+=ii){
                        double *t0=&sumofcol[i],*t1=&allreduce_sumofcol[i];
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
                                        "vmulpd %%ymm0, %%ymm3, %%ymm3\n"
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
				if(hh){
                                if(hh==2){
                                        for(int t=0;t<ii;t++,z0++,z1++){
                                                *z0*=temp[t];
                                                *z1*=temp[t];
                                        }
                                }
                                if(hh==1){
                                        for(int t=0;t<ii;t++,z0++){
                                                *z0*=temp[t];
                                        }
                                }
                                if(hh==3){
                                        for(int t=0;t<ii;t++,z0++,z1++,z2++){
                                                *z0*=temp[t];
                                                *z1*=temp[t];
                                                *z2*=temp[t];
                                        }
                                }
                        }
                        x0+=ii,x1+=ii,x2+=ii,x3+=ii;
                        y0=x0,y1=x1,y2=x2,y3=x3;
                        z0=y0,z1=y1,z2=y2,z3=y3;
                }

                //cal error
                double temp1=0,temp2=0;
                for(int i=0;i<m*n;i++){
                        temp2=fabs(local_sinkhorn[i]-copy_sinkhorn[i]);
                        temp1+=temp2*temp2;
                }
                MPI_Allreduce(&temp1,&error,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
                error=sqrt(error);
                if(error<eps) loop=false;
        }
        finish=MPI_Wtime();
        time01=(finish-start)*1000;
        MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
        if(world_rank==0) printf("%f, ",time1);
}
