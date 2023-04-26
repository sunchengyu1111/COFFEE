#include "Ring.h"

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
