#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <mpi.h>
#include <iostream>
#define eps 1e-12

int main(int argc,char *argv[]){
	//initialize
	int total_matrix_row=atoi(argv[1]);
        int total_matrix_col=atoi(argv[2]);
        int m=total_matrix_row;
        int n=total_matrix_col;
	int world_rank,world_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int w=world_size;
	
	//allocate memory
    	int length_of_perprocess=m/w;
	m=length_of_perprocess;
    	double *local_sinkhorn=new double[m*n];
	double *copy_sinkhorn=new double[m*n];
    	double *sumofrow=new double[m*w];
	double *sumofcol=new double[n];
	double *local_sumofcol=new double[n];
	double *allreduce_sumofcol=new double[n];
	for(int i=0;i<m*n;i++){
        	local_sinkhorn[i]=(double)rand()/(double)(RAND_MAX)*100;                      
        }
	if(world_rank==0){
		for(int i=0;i<m*w;i++){
			sumofrow[i]=(double)rand()/(double)(RAND_MAX)*100;
		}
		for(int i=0;i<n;i++){
                        sumofcol[i]=(double)rand()/(double)(RAND_MAX)*100;
                }
	}
	MPI_Bcast(sumofrow,m*w,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(sumofcol,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	//start loop
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
		/*
		for(int i=0;i<n;i++){
                        double temp=0;
                        for(int j=0;j<m;j++){
                                temp+=local_sinkhorn[i+j*n];
                        }
                        local_sumofcol[i]=temp;
                }
		*/

		for(int i=0;i<n;i++) local_sumofcol[i]=0;
                int tep=0;
                for(int i=0;i<m*n;i++){
                        local_sumofcol[tep]+=local_sinkhorn[i];
                        tep++;
                        if(tep==n) tep=0;
                }
		
		MPI_Allreduce(local_sumofcol,allreduce_sumofcol,n,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		const int ii=1440,jj=4,kk=m/jj,hh=m%jj;
		double temp[ii];
		double *x0=&local_sinkhorn[0],*x1=&local_sinkhorn[n],*x2=&local_sinkhorn[2*n],*x3=&local_sinkhorn[3*n];
		double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
		for(int i=0;i<n;i+=ii){
			double *t0=&sumofcol[i],*t1=&allreduce_sumofcol[i];
			for(int j=0;j<ii;j++,t0++,t1++){
				temp[j]=(*t0)/(*t1);
			}
			for(int j=0;j<kk;j++){
				for(int t=0;t<ii;t++,z0++,z1++,z2++,z3++){
					*z0*=temp[t];
					*z1*=temp[t];
					*z2*=temp[t];
					*z3*=temp[t];
				}
				y0+=jj*n,y1+=jj*n,y2+=jj*n,y3+=jj*n;
				z0=y0,z1=y1,z2=y2,z3=y3;
			}
			if(hh){
				for(int t=0;t<ii;t++,z0++,z1++){
					*z0*=temp[t];
					*z1*=temp[t];
				}
				printf("haha\n");
			}
			x0+=ii,x1+=ii,x2+=ii,x3+=ii;
			y0=x0,y1=x1,y2=x2,y3=x3;
			z0=y0,z1=y1,z2=y2,z3=y3;
		}
		/*		
		for(int i=0;i<n;i++){
                        double temp=sumofcol[i]/allreduce_sumofcol[i];
                        for(int j=0;j<m;j++){
                                local_sinkhorn[i+j*n]*=temp;
                        }
                }
		*/

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

        //finish
        MPI_Finalize();
        delete []sumofrow;
        delete []sumofcol;
        delete []local_sinkhorn;
        delete []copy_sinkhorn;
        delete []local_sumofcol;
        delete []allreduce_sumofcol;
        return 0;
}
