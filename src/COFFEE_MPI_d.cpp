#include "COFFEE_MPI_d.h"

int main(int argc,char *argv[]){
        //initialize
	int total_matrix_row=atoi(argv[1]);
        int total_matrix_col=atoi(argv[2]);
	int m=total_matrix_row;
        int n=total_matrix_col;
	int process_per_node=atoi(argv[3]);	
	int p=process_per_node;
	int total_iternum=4;
	int each_iterlength=n/total_iternum;

	//world communicate
        int world_rank,world_size;
        MPI_Init(NULL,NULL);
        MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
        MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	MPI_Group world_group;
	MPI_Comm_group(MPI_COMM_WORLD,&world_group);
        int w=world_size;
	
	//local communicate
        int local_rank,local_size=p;
	int local_color=world_rank/local_size;
	MPI_Comm local_comm;
	MPI_Comm_split(MPI_COMM_WORLD,local_color,world_rank,&local_comm);
	MPI_Comm_rank(local_comm,&local_rank);
        MPI_Comm_size(local_comm,&local_size);
	//printf("world_rank:%d/%d,local_rank:%d/%d\n",world_rank,world_size,local_rank,local_size);
	
	//worker conmmunicate
	MPI_Group local_group;
	MPI_Comm_group(local_comm,&local_group);
	int *worker_ranks=new int[local_size-1];
	for(int i=0;i<local_size-1;i++){
		worker_ranks[i]=i;
	}
	MPI_Group worker_group;
	MPI_Group_incl(local_group,local_size-1,worker_ranks,&worker_group);
	MPI_Comm worker_comm;
	MPI_Comm_create_group(local_comm,worker_group,0,&worker_comm);
	int worker_rank=-1,worker_size=-1;
	if(MPI_COMM_NULL!=worker_comm){
		MPI_Comm_rank(worker_comm, &worker_rank);
		MPI_Comm_size(worker_comm, &worker_size);
	}
	delete []worker_ranks;
	//printf("world_rank:%d/%d,worker_rank:%d/%d\n",world_rank,world_size,worker_rank,worker_size);

	//manager communicate
	int *manager_ranks=new int[world_size/local_size];
	for(int i=0;i<world_size/local_size;i++){
		manager_ranks[i]=local_size-1+i*local_size;
	}
        MPI_Group manager_group;
        MPI_Group_incl(world_group,world_size/local_size,manager_ranks,&manager_group);
        MPI_Comm manager_comm;
        MPI_Comm_create_group(MPI_COMM_WORLD,manager_group,1,&manager_comm);
        int manager_rank=-1,manager_size=-1;
        if(MPI_COMM_NULL!=manager_comm){
        	MPI_Comm_rank(manager_comm,&manager_rank);
                MPI_Comm_size(manager_comm,&manager_size);
        }
	//printf("world_rank:%d/%d,manager_rank:%d/%d\n",world_rank,world_size,manager_rank,manager_size);
	delete []manager_ranks;
             
        //allocate memory
        int length_of_perprocess=m/w;
        m=length_of_perprocess;
	int m2=m+m/(local_size-1);
        double *local_sinkhorn=new double[m2*n];
        double *copy_sinkhorn=new double[m*n];
        double *sumofrow=new double[m*w];
        double *sumofcol=new double[n];
        double *local_sumofcol=new double[n];
	double *reduce_sumofcol=new double[n];
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
        if(MPI_COMM_NULL!=manager_comm){
                MPI_Request manager_request;
                MPI_Status manager_status;
                int temp=m*n/(local_size-1);
                for(int i=0;i<local_size-1;i++){
                        MPI_Isend(local_sinkhorn+i*temp,temp,MPI_DOUBLE,i,i,local_comm,&manager_request);
                }
                MPI_Wait(&manager_request,&manager_status);
        }else{
                MPI_Status worker_status;
		int temp=m*n/(local_size-1);
                MPI_Recv(local_sinkhorn+m*n,temp,MPI_DOUBLE,local_size-1,local_rank,local_comm,&worker_status);
        }

        //start
	MPId_test(local_sinkhorn, copy_sinkhorn, sumofrow, sumofcol, local_sumofcol, reduce_sumofcol, allreduce_sumofcol, m, m2, n, world_rank, local_rank, local_size, total_iternum, each_iterlength, local_comm, worker_comm, manager_comm);

	//finish
        MPI_Finalize();
        delete []sumofrow;
        delete []sumofcol;
	delete []local_sumofcol;
        delete []local_sinkhorn;
        delete []copy_sinkhorn;
        delete []reduce_sumofcol;
        delete []allreduce_sumofcol;
        return 0;
}
