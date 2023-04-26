#include "MPI_SALaR.h"

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

        //leader communicate
        int *leader_ranks=new int[world_size/local_size];
        for(int i=0;i<world_size/local_size;i++){
                leader_ranks[i]=local_size-1+i*local_size;
        }
        MPI_Group leader_group;
        MPI_Group_incl(world_group,world_size/local_size,leader_ranks,&leader_group);
        MPI_Comm leader_comm;
        MPI_Comm_create_group(MPI_COMM_WORLD,leader_group,1,&leader_comm);
        int leader_rank=-1,leader_size=-1;
        if(MPI_COMM_NULL!=leader_comm){
                MPI_Comm_rank(leader_comm,&leader_rank);
                MPI_Comm_size(leader_comm,&leader_size);
        }
        //printf("world_rank:%d/%d,leader_rank:%d/%d\n",world_rank,world_size,leader_rank,leader_size);
        delete []leader_ranks;

        //allocate memory
        int length_of_perprocess=m/w;
        m=length_of_perprocess;
        double *local_sinkhorn=new double[m*n];
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

        //start
	SALaR_test(local_sinkhorn, copy_sinkhorn, sumofrow, sumofcol, local_sumofcol, reduce_sumofcol, allreduce_sumofcol, m, n, world_rank, local_rank, local_size, total_iternum, each_iterlength, local_comm, worker_comm, leader_comm);

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
