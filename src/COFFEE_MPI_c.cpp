#include "COFFEE_MPI_c.h"

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
	
	//start
	MPIc_test(local_sinkhorn, copy_sinkhorn, sumofrow, sumofcol, local_sumofcol, allreduce_sumofcol, m, n, world_rank);
	
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
