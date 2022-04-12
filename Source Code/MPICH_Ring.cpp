#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <mpi.h>
#include <cassert>
#include <vector>
#include <iostream>
#define eps 1e-12

int MPI_RingAllreduce(double* input,double* output,int count,MPI_Datatype datatype);
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
	double time01,time1;
	start=MPI_Wtime();
	while(loop){
		if(world_rank==0){
			printf("count %d\n",count);
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

int MPI_RingAllreduce(double* input,double* output,int count,MPI_Datatype datatype){
    	int n,r;
    	MPI_Comm_size(MPI_COMM_WORLD, &n);
    	MPI_Comm_rank(MPI_COMM_WORLD, &r);
    	double* buffer=output;
    	for(int i=0;i<count;i++){
		buffer[i]=input[i];
	}
	double* temp=new double[count];
    	int elements_to_reduce=count;
    	int segment_size=elements_to_reduce/n;
    	std::vector<int> segment_sizes(n,segment_size);
    	int residual=elements_to_reduce%n;
    	for(int i=0;i<residual;++i){
        	segment_sizes[i]++;
    	}
    	std::vector<int> segment_starts(n);
    	segment_starts[0] = 0;
    	for(int i=1;i<segment_starts.size();++i){
        	segment_starts[i]=segment_starts[i-1]+segment_sizes[i-1];
    	}
    	assert(segment_starts[n-1]+segment_sizes[n-1]==elements_to_reduce);
    	double* segment_recv=(double*) temp;
    	int recv_from=((r-1)+n)%n;
    	int send_to=(r+1)%n;
    	MPI_Status recv_status;
    	MPI_Request recv_req;
    	for(int i=0;i<n-1;i++){
        	int send_seg_id=((r-i)+n)%n;
        	int recv_seg_id=((r-i-1)+n)%n;
		double* segment_send=&(buffer[segment_starts[send_seg_id]]);
		MPI_Irecv(segment_recv,segment_sizes[recv_seg_id],MPI_DOUBLE,recv_from,123,MPI_COMM_WORLD,&recv_req);
		MPI_Send(segment_send, segment_sizes[send_seg_id],MPI_DOUBLE,send_to,123,MPI_COMM_WORLD);
        	double *segment_update=&(buffer[segment_starts[recv_seg_id]]);
        	MPI_Wait(&recv_req, &recv_status);
        	int recv_seg_size=segment_sizes[recv_seg_id];
		for(int i=0;i<recv_seg_size;i++){
			segment_update[i]+=segment_recv[i];
		}     
	}
    	for(int i=0;i<n-1;++i){
        	int send_seg_id=((r-i+1)+n)%n;
        	int recv_seg_id=((r-i)+n)%n;
        	double* segment_send=&(buffer[segment_starts[send_seg_id]]);
        	double* segment_recv=&(buffer[segment_starts[recv_seg_id]]);
        	MPI_Sendrecv(segment_send, segment_sizes[send_seg_id],MPI_DOUBLE,send_to,123,segment_recv,segment_sizes[recv_seg_id],MPI_DOUBLE,recv_from,123,MPI_COMM_WORLD,&recv_status);
	}
    	return 1;
}
