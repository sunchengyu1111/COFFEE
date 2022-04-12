#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <iostream>

int main(int argc,char *argv[]){
	int n=atoi(argv[1]);
	int world_rank,world_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int m=world_size;
    	int length_of_perprocess=n/world_size;
	int k=length_of_perprocess;
    	double *local_sinkhorn=new double[k*n];
    	double *sumofrow=new double[n];
	double *sumofcol=new double[n];
	double *local_sumofcol=new double[n];
	double *allreduce_sumofcol=new double[n];
	for(int i=0;i<k*n;i++){
        	local_sinkhorn[i]=(double)rand()/(double)(RAND_MAX)*100;                      
        }
	if(world_rank==0){
		for(int i=0;i<n;i++){
			sumofrow[i]=(double)rand()/(double)(RAND_MAX)*100;
			sumofcol[i]=(double)rand()/(double)(RAND_MAX)*100;
		}
	}
	MPI_Bcast(sumofrow,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(sumofcol,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	double start,finish,time01,time02,time1,time2;
	
	//Row
	start=MPI_Wtime();
	int startrow=world_rank*k;
	for(int i=0;i<k;i++){
		double temp=0;
		for(int j=0;j<n;j++){
			temp+=local_sinkhorn[i*n+j];
		}
		temp=sumofrow[startrow+i]/temp;
		for(int j=0;j<n;j++){
			local_sinkhorn[i*n+j]*=temp;
		}
	}
	finish=MPI_Wtime();
	time01=(finish-start)*1000;
	MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	if(world_rank==0) printf("%f, ",time1);

	//Col
	start=MPI_Wtime();
	for(int i=0;i<n;i++){
		double temp=0;
		for(int j=0;j<k;j++){
			temp+=local_sinkhorn[i+j*n];
		}
		local_sumofcol[i]=temp;
	}
	MPI_Allreduce(local_sumofcol,allreduce_sumofcol,n,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	for(int i=0;i<n;i++){
		double temp=sumofcol[i]/allreduce_sumofcol[i];
		for(int j=0;j<k;j++){
			local_sinkhorn[i+j*n]*=temp;
		}
	}
	finish=MPI_Wtime();
	time02=(finish-start)*1000;
        MPI_Allreduce(&time02,&time2,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	if(world_rank==0) printf("%f, \n",time2);

	MPI_Finalize();	
	delete []sumofrow;
	delete []sumofcol;
	delete []local_sinkhorn;
	delete []local_sumofcol;
	delete []allreduce_sumofcol;
	return 0;
}
