#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
		for(int i=0;i<n;i++) local_sumofcol[i]=0;
		int tep=0;
		for(int i=0;i<m*n;i++){
			local_sumofcol[tep]+=local_sinkhorn[i];
			tep++;
			if(tep==n) tep=0;
		}
		MPI_Allreduce(local_sumofcol,allreduce_sumofcol,n,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		double temp=0;
                for(int i=0;i<m;i++){
                        for(int j=0;j<n;j++){
                                temp=sumofcol[j]/allreduce_sumofcol[j];
                                local_sinkhorn[j+i*n]*=temp;
                        }
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
