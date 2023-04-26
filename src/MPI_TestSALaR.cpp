#include "MPI_TestSALaR.h"

void SALaR_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *reduce_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank, const int local_rank, const int local_size, const int total_iternum, const int each_iterlength, MPI_Comm local_comm, MPI_Comm worker_comm, MPI_Comm leader_comm) {
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
}
