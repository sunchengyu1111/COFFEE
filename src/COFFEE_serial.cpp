#include "COFFEE_serial.h"

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
	for(int i=0;i<m*n;i++){
		copy_sinkhorn[i]=local_sinkhorn[i];
	}
	
	// test typical	
	typical(copy_sinkhorn, sumofcol, m, n, world_rank);
		
	// test C2R
	C2R(local_sinkhorn, copy_sinkhorn, local_sumofcol, sumofcol, m, n, world_rank);
	
	// test COFFEE
	COFFEE(local_sinkhorn, local_sumofcol, sumofcol, m, n, world_rank);

	// finish	
	MPI_Finalize();	
	delete []sumofcol;
	delete []local_sinkhorn;
	delete []copy_sinkhorn;
	delete []local_sumofcol;
	return 0;
}

static void typical(double *copy_sinkhorn, double *sumofcol, const int m, const int n, const int world_rank) {
	double time01, time1;
	double start=MPI_Wtime();
        for(int i=0;i<n;i++){
                double temp=0;
                for(int j=0;j<m;j++){
                        temp+=copy_sinkhorn[i+j*n];
                }
                temp=sumofcol[i]/temp;
                for(int j=0;j<m;j++){
                        copy_sinkhorn[i+j*n]*=temp;
                }
        }
        double finish=MPI_Wtime();
        time01=(finish-start)*1000;
        MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
        if(world_rank==0) printf("%.3f, ",time1);
}

static void C2R(double *local_sinkhorn, double *copy_sinkhorn, double *local_sumofcol, double *sumofcol, const int m, const int n, const int world_rank) {
	double time01, time1;
	double start=MPI_Wtime();
        for(int i=0;i<n;i++) local_sumofcol[i]=0;
        int tep=0;
        for(int i=0;i<m*n;i++){
                local_sumofcol[tep]+=local_sinkhorn[i];
                tep++;
                if(tep==n) tep=0;
        }
        double temp4=0;
        for(int i=0;i<m;i++){
                //temp2=sumofcol[i]/local_sumofcol[i];
                for(int j=0;j<n;j++){
                        temp4=sumofcol[j]/local_sumofcol[j];
                        copy_sinkhorn[j+i*n]*=temp4;
                }
        }
        double finish=MPI_Wtime();
        time01=(finish-start)*1000;
        MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
        if(world_rank==0) printf("%.3f, ",time1);
}

static void COFFEE(double *local_sinkhorn, double *local_sumofcol, double *sumofcol, const int m, const int n, const int world_rank) {
	double time2,time02;
	double start=MPI_Wtime();
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
                tep1+=8;
                if(tep1==n) {tep1=0;p0=p2;}
                else p0+=8;
        }
        const int ii=1000,jj=4,kk=m/jj,rr=jj/4;
        double temp[ii];
        double *x0=&local_sinkhorn[0],*x1=&local_sinkhorn[n],*x2=&local_sinkhorn[2*n],*x3=&local_sinkhorn[3*n];
        double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
        for(int i=0;i<n;i+=ii){
                double *t0=&sumofcol[i],*t1=&local_sumofcol[i];
                for(int j=0;j<ii;j++,t0++,t1++){
                        temp[j]=(*t0)/(*t1);
                }
                for(int j=0;j<kk;j++){
                        for(int r=0;r<rr;r++){
                                for(int t=0;t<ii;t+=4,z0+=4,z1+=4,z2+=4,z3+=4){
                                        vec_t=_mm256_loadu_pd(&temp[t]);
                                        vec_0=_mm256_loadu_pd(z0);vec_0=_mm256_mul_pd(vec_0,vec_t);_mm256_storeu_pd(z0,vec_0);
                                        vec_1=_mm256_loadu_pd(z1);vec_1=_mm256_mul_pd(vec_1,vec_t);_mm256_storeu_pd(z1,vec_1);
                                        vec_2=_mm256_loadu_pd(z2);vec_2=_mm256_mul_pd(vec_2,vec_t);_mm256_storeu_pd(z2,vec_2);
                                        vec_3=_mm256_loadu_pd(z3);vec_3=_mm256_mul_pd(vec_3,vec_t);_mm256_storeu_pd(z3,vec_3);
                                }
                                y0+=4*n,y1+=4*n,y2+=4*n,y3+=4*n;
                                z0=y0,z1=y1,z2=y2,z3=y3;
                        }

                }
                x0+=ii,x1+=ii,x2+=ii,x3+=ii;
                y0=x0,y1=x1,y2=x2,y3=x3;
                z0=y0,z1=y1,z2=y2,z3=y3;
        }
        double finish=MPI_Wtime();
        time02=(finish-start)*1000;
        MPI_Allreduce(&time02,&time2,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
        if(world_rank==0) printf("%.3f, ",time2);
}
