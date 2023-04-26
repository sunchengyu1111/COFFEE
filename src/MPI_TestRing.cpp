#include "MPI_TestRing.h"

void Ring_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank) {
	int count=0;
        double error=0;
        bool loop=true;
        double start,finish;
        double time01,time1;
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
                for(int i=0;i<n;i++){
                        double temp=0;
                        for(int j=0;j<m;j++){
                                temp+=local_sinkhorn[i+j*n];
                        }
                        local_sumofcol[i]=temp;
                }
                //usleep(2245000);
                MPI_RingAllreduce(local_sumofcol,allreduce_sumofcol,n,MPI_DOUBLE);
		for(int i=0;i<n;i++){
                        double temp=sumofcol[i]/allreduce_sumofcol[i];
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
