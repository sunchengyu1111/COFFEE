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
        int count=0;
        double error=0;
        bool loop=true;
        double start,finish;
	double time01,time1;
	start=MPI_Wtime();
        while(loop){
                if(world_rank==0){
                        //printf("count:%d\n",count);
                        count++;
                }

		//copy data
                for(int i=0;i<m*n;i++){
                        copy_sinkhorn[i]=local_sinkhorn[i];
                }

                //row
                int start_row=world_rank*m;
                for(int i=0;i<m;i++){
                        double temp=0;
                        for(int j=0;j<n;j++){
                                temp+=local_sinkhorn[i*n+j];
                        }
			temp=sumofrow[start_row+i]/temp;
                        for(int j=0;j<n;j++){
                                local_sinkhorn[i*n+j]*=temp;
                        }
                }
                
                //col
                for(int i=0;i<n;i++){
                        double temp=0;
                        for(int j=0;j<m;j++){
                                temp+=local_sinkhorn[i+j*n];
                        }
                        local_sumofcol[i]=temp;
		}

		if(MPI_COMM_NULL!=worker_comm){
			MPI_Reduce(local_sumofcol,reduce_sumofcol,each_iterlength,MPI_DOUBLE,MPI_SUM,0,worker_comm);
			/*
			if(worker_rank==0){
				printf("rank:%d,here1,reduce_sumofcol\n",world_rank);
				for(int i=0;i<n;i++){
                                        printf("%f\t",reduce_sumofcol[i]);
                       	 	}	
			}
			printf("\n");
			*/
		}
		for(int i=1;i<total_iternum;i++){
			if(local_rank==0){
				MPI_Send(reduce_sumofcol,each_iterlength,MPI_DOUBLE,local_size-1,0,local_comm);
			}
			if(local_rank==local_size-1){
				MPI_Recv(allreduce_sumofcol,each_iterlength,MPI_DOUBLE,0,0,local_comm,MPI_STATUS_IGNORE);
				/*		
				printf("rank:%d,here2,allreduce_sumofcol\n",world_rank);
				for(int i=0;i<each_iterlength;i++){
					printf("%f\t",allreduce_sumofcol[i]);
				}
				printf("\n");
				*/
			}
			if(MPI_COMM_NULL!=worker_comm){
                        	MPI_Reduce(local_sumofcol+i*each_iterlength,reduce_sumofcol,each_iterlength,MPI_DOUBLE,MPI_SUM,0,worker_comm);
                       		/* 		
                        	if(worker_rank==0){
                                	printf("rank:%d,here3,reduce_sumofcol\n",world_rank);
                                	for(int i=0;i<n;i++){
                                        	printf("%f\t",reduce_sumofcol[i]);
                                	}
				 	printf("\n");	
                       	 	}
                        	*/
                	}
			if(MPI_COMM_NULL!=leader_comm){
				for(int j=0;j<each_iterlength;j++){
					allreduce_sumofcol[j]+=local_sumofcol[j+(i-1)*each_iterlength];
				}
				usleep(160000);
				MPI_Allreduce(allreduce_sumofcol,local_sumofcol+(i-1)*each_iterlength,each_iterlength,MPI_DOUBLE,MPI_SUM,leader_comm);
                     		/*				
                               	printf("rank:%d,here4,allreduce_sumofcol\n",world_rank);
                               	for(int i=0;i<n;i++){
                              	        printf("%f\t",allreduce_sumofcol[i]);
                       	        }
				printf("\n");
                	        */
                	}
			MPI_Bcast(local_sumofcol+(i-1)*each_iterlength,each_iterlength,MPI_DOUBLE,local_size-1,local_comm);
			/*
                        printf("rank:%d,here5,local_sumofcol\n",world_rank);
                        for(int i=0;i<n;i++){
                                printf("%f\t",local_sumofcol[i]);
                        }
                        printf("\n");
                       	*/
		}
                if(local_rank==0){
                        MPI_Send(reduce_sumofcol,each_iterlength,MPI_DOUBLE,local_size-1,0,local_comm);
                }
                if(local_rank==local_size-1){
                        MPI_Recv(allreduce_sumofcol,each_iterlength,MPI_DOUBLE,0,0,local_comm,MPI_STATUS_IGNORE);
                       	/* 
                        printf("rank:%d,here6,allreduce_sumofcol\n",world_rank);
                        for(int i=0;i<n;i++){
                                printf("%f\t",allreduce_sumofcol[i]);
       	                }
                        printf("\n");
                        */
                }
                if(MPI_COMM_NULL!=leader_comm){
                        for(int j=0;j<each_iterlength;j++){
                                allreduce_sumofcol[j]+=local_sumofcol[j+(total_iternum-1)*each_iterlength];
                        }
			usleep(160000);
                        MPI_Allreduce(allreduce_sumofcol,local_sumofcol+(total_iternum-1)*each_iterlength,each_iterlength,MPI_DOUBLE,MPI_SUM,leader_comm);
			/*                              
                        printf("rank:%d,here7,allreduce_sumofcol\n",world_rank);
                        for(int i=0;i<n;i++){
                                printf("%f\t",allreduce_sumofcol[i]);
                        }
                       	printf("\n");
			*/
                }
		MPI_Bcast(local_sumofcol+(total_iternum-1)*each_iterlength,each_iterlength,MPI_DOUBLE,local_size-1,local_comm);
		/*		
		printf("rank:%d,here8,local_sumofcol\n",world_rank);
                for(int i=0;i<n;i++){
                        printf("%f\t",local_sumofcol[i]);
                }
                printf("\n");
		*/
		
                for(int i=0;i<n;i++){
			double temp=sumofcol[i]/local_sumofcol[i];
                        for(int j=0;j<m;j++){
                                local_sinkhorn[i+j*n]*=temp;
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
	delete []local_sumofcol;
        delete []local_sinkhorn;
        delete []copy_sinkhorn;
        delete []reduce_sumofcol;
        delete []allreduce_sumofcol;
        return 0;
}
