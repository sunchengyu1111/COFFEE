#include "COFFEE_Testd.h"

void MPId_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *reduce_sumofcol, double *allreduce_sumofcol, const int m, const int m2, const int n, const int world_rank, const int local_rank, const int local_size, const int total_iternum, const int each_iterlength, MPI_Comm local_comm, MPI_Comm worker_comm, MPI_Comm manager_comm) {
	int count=0;
        const int ii=1440,jj=4;
        double tmp[ii];
        double error=0,temp1=0,temp2=0;
        bool loop=true;
        double start,finish;
        double time01,time1;
        int each_itercommlen=each_iterlength/(local_size-1);
        start=MPI_Wtime();
        while(loop){
                //copy data
                if(world_rank==0){
                        //printf("count:%d\n",count);
                        count++;
                }
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
                for(int i=0;i<n;i++) local_sumofcol[i]=0;
                int tep=0;
                for(int i=0;i<m*n;i++){
                        local_sumofcol[tep]+=local_sinkhorn[i];
                        tep++;
                        if(tep==n) tep=0;
                }

                if(MPI_COMM_NULL!=worker_comm) MPI_Reduce_scy(local_sumofcol,reduce_sumofcol,each_iterlength,each_itercommlen,0,local_rank,local_comm,local_size-1,0);
		for(int i=1;i<total_iternum;i++){
                        if(MPI_COMM_NULL!=worker_comm){
                                for(int j=0;j<local_size-1;j++){
                                        if(local_rank==j) MPI_Send(reduce_sumofcol+(i-1)*each_iterlength+j*each_itercommlen,each_itercommlen,MPI_DOUBLE,local_size-1,2021+j,local_comm);
                                }
                        }
                        if(MPI_COMM_NULL!=manager_comm){
                                for(int j=0;j<local_size-1;j++){
                                        MPI_Recv(allreduce_sumofcol+j*each_itercommlen,each_itercommlen,MPI_DOUBLE,j,2021+j,local_comm,MPI_STATUS_IGNORE);
                                }
                        }
                        if(MPI_COMM_NULL!=worker_comm){
                                int each_iteroffset=i*each_iterlength;
                                //do i reduce
                                MPI_Reduce_scy(local_sumofcol,reduce_sumofcol,each_iterlength,each_itercommlen,each_iteroffset,local_rank,local_comm,local_size-1,0);
                                //i==1 recv local data from manager
                                if(i==1){
                                        MPI_Status worker_status;
                                        MPI_Recv(local_sinkhorn+m*n,m*n/(local_size-1),MPI_DOUBLE,local_size-1,local_rank,local_comm,&worker_status);
                                }else{
                                        int kk=m2/jj,hh=m2%jj;
					col_subroutine(local_sinkhorn, local_sumofcol, sumofcol, tmp, ii, jj, kk, hh, i-2, (i-1)*each_iterlength, each_iterlength, n);
                                 
                                }
                        }
                        if(MPI_COMM_NULL!=manager_comm){
                                //i==1 send local data to worker
                                MPI_Request manager_request;
                                MPI_Status manager_status;
                                if(i==1){
                                        int temp=m*n/(local_size-1);
                                        for(int j=0;j<local_size-1;j++){
                                                MPI_Isend(local_sinkhorn+j*temp,temp,MPI_DOUBLE,j,j,local_comm,&manager_request);
                                        }
                                }
                                for(int j=0;j<each_iterlength;j++){
                                        allreduce_sumofcol[j]+=local_sumofcol[j+(i-1)*each_iterlength];
                                }
                                //do i-1 allreduce
                                usleep(160000);
                                MPI_Allreduce(allreduce_sumofcol,local_sumofcol+(i-1)*each_iterlength,each_iterlength,MPI_DOUBLE,MPI_SUM,manager_comm);
                                if(i==1) MPI_Wait(&manager_request,&manager_status);
                        }
                        MPI_Bcast(local_sumofcol+(i-1)*each_iterlength,each_iterlength,MPI_DOUBLE,local_size-1,local_comm);
                }
		if(MPI_COMM_NULL!=worker_comm){
                        for(int i=0;i<local_size-1;i++){
                                if(local_rank==i) MPI_Send(reduce_sumofcol+(total_iternum-1)*each_iterlength+i*each_itercommlen,each_itercommlen,MPI_DOUBLE,local_size-1,2021+i,local_comm);
                        }
                }
                if(MPI_COMM_NULL!=manager_comm){
                        for(int i=0;i<local_size-1;i++){
                                MPI_Recv(allreduce_sumofcol+i*each_itercommlen,each_itercommlen,MPI_DOUBLE,i,2021+i,local_comm,MPI_STATUS_IGNORE);
                        }   
                }   
                if(MPI_COMM_NULL!=worker_comm){
                        int kk=m2/jj,hh=m2%jj;
			col_subroutine(local_sinkhorn, local_sumofcol, sumofcol, tmp, ii, jj, kk, hh, total_iternum-2, (total_iternum-1)*each_iterlength, each_iterlength, n);
                }   
                if(MPI_COMM_NULL!=manager_comm){
                        for(int j=0;j<each_iterlength;j++){
                                allreduce_sumofcol[j]+=local_sumofcol[j+(total_iternum-1)*each_iterlength];
                        }   
                        usleep(160000);
                        MPI_Allreduce(allreduce_sumofcol,local_sumofcol+(total_iternum-1)*each_iterlength,each_iterlength,MPI_DOUBLE,MPI_SUM,manager_comm);
                }   
                MPI_Bcast(local_sumofcol+(total_iternum-1)*each_iterlength,each_iterlength,MPI_DOUBLE,local_size-1,local_comm);
                if(MPI_COMM_NULL!=manager_comm){
                        int temp=m*n/(local_size-1);
                        for(int i=0;i<local_size-1;i++){
                                MPI_Recv(local_sinkhorn+i*temp,temp,MPI_DOUBLE,i,i,local_comm,MPI_STATUS_IGNORE);
                        }   
                }else{
                        int temp=m*n/(local_size-1);
                        MPI_Send(local_sinkhorn+m*n,temp,MPI_DOUBLE,local_size-1,local_rank,local_comm);
                }
                int kk=m/jj,hh=m%jj;
               
		col_subroutine(local_sinkhorn, local_sumofcol, sumofcol, tmp, ii, jj, kk, hh, total_iternum-1, n, each_iterlength, n);
                //cal error
                for(int i=0;i<m*n;i++){
                        temp2=fabs(local_sinkhorn[i]-copy_sinkhorn[i]);
                        temp1+=temp2*temp2;
                }
                MPI_Allreduce(&temp1,&error,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
                error=sqrt(error);
                //if(world_rank==0) printf("rank:%d,error:%f\n",error);
                if(error<eps) loop=false;
                temp1=0,temp2=0;
        }
        finish=MPI_Wtime();
        time01=(finish-start)*1000;
        MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
        if(world_rank==0) printf("%f, ",time1);
}

void col_subroutine (double *local_sinkhorn, double *local_sumofcol, double *sumofcol, double *tmp, const int ii, const int jj, const int kk, const int hh, const int i, const int s, const int each_iterlength, const int n) {
	double *x0=&local_sinkhorn[i*each_iterlength];
	double *x1=&local_sinkhorn[n+i*each_iterlength];
	double *x2=&local_sinkhorn[2*n+i*each_iterlength];
	double *x3=&local_sinkhorn[3*n+i*each_iterlength];
	double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
	for(int a=i*each_iterlength;a<s;a+=ii){
		double *t0=&sumofcol[a],*t1=&local_sumofcol[a];
		for(int j=0;j<ii;j++,t0++,t1++){
			tmp[j]=(*t0)/(*t1);
		}
		for(int j=0;j<kk;j++){
			for(int t=0;t<ii;t++,z0++,z1++,z2++,z3++){
				*z0*=tmp[t];
				*z1*=tmp[t];
				*z2*=tmp[t];
				*z3*=tmp[t];
			}
			y0+=jj*n,y1+=jj*n,y2+=jj*n,y3+=jj*n;
			z0=y0,z1=y1,z2=y2,z3=y3;
		}
		if(hh){
			if(hh==2){
				for(int t=0;t<ii;t++,z0++,z1++){
					*z0*=tmp[t];
					*z1*=tmp[t];
				}
			}
			if(hh==1){
				for(int t=0;t<ii;t++,z0++){
					*z0*=tmp[t];
				}
			}
			if(hh==3){
				for(int t=0;t<ii;t++,z0++,z1++,z2++){
					*z0*=tmp[t];
					*z1*=tmp[t];
					*z2*=tmp[t];
				}
			}
		}
		x0+=ii,x1+=ii,x2+=ii,x3+=ii;
		y0=x0,y1=x1,y2=x2,y3=x3;
		z0=y0,z1=y1,z2=y2,z3=y3;
	}
}

void MPI_Reduce_scy(double *local_sumofcol,double *reduce_sumofcol,int each_iterlength,int each_itercommlen,int each_iteroffset,int local_rank,MPI_Comm local_comm,int worker_num,int workerstart_num){
        if(worker_num==4){
                MPI_Reduce_base(local_sumofcol,reduce_sumofcol,each_itercommlen,each_iteroffset,local_rank,local_comm,workerstart_num);
                return;
        }else{
                int start=workerstart_num;
                int medium=start+worker_num/2;
                int end=start+worker_num;
                if(local_rank>=start&&local_rank<medium){
                        MPI_Reduce_scy(local_sumofcol,reduce_sumofcol,each_iterlength/2,each_itercommlen,each_iteroffset,local_rank,local_comm,worker_num/2,workerstart_num);
                        MPI_Reduce_scy(local_sumofcol,reduce_sumofcol,each_iterlength/2,each_itercommlen,each_iteroffset+each_iterlength/2,local_rank,local_comm,worker_num/2,workerstart_num);
                }else if(local_rank>=medium&&local_rank<end){
                        MPI_Reduce_scy(local_sumofcol,reduce_sumofcol,each_iterlength/2,each_itercommlen,each_iteroffset,local_rank,local_comm,worker_num/2,medium);
                        MPI_Reduce_scy(local_sumofcol,reduce_sumofcol,each_iterlength/2,each_itercommlen,each_iteroffset+each_iterlength/2,local_rank,local_comm,worker_num/2,medium);
                }
                int connect=worker_num/2;
                for(int i=start;i<medium;i++){
                        if(local_rank==i){
                                MPI_Send(reduce_sumofcol+each_iteroffset+(i+connect)*each_itercommlen,each_itercommlen,MPI_DOUBLE,i+connect,1011+i,local_comm);
                                MPI_Recv(local_sumofcol+each_iteroffset+i*each_itercommlen,each_itercommlen,MPI_DOUBLE,i+connect,2022+i,local_comm,MPI_STATUS_IGNORE);
                                for(int j=0;j<each_itercommlen;j++){
                                        reduce_sumofcol[j+each_iteroffset+i*each_itercommlen]+=local_sumofcol[j+each_iteroffset+i*each_itercommlen];
                                }
                        }else if(local_rank==i+connect){
                                MPI_Send(reduce_sumofcol+each_iteroffset+i*each_itercommlen,each_itercommlen,MPI_DOUBLE,i,2022+i,local_comm);
                                MPI_Recv(local_sumofcol+each_iteroffset+(i+connect)*each_itercommlen,each_itercommlen,MPI_DOUBLE,i,1011+i,local_comm,MPI_STATUS_IGNORE);
                                for(int j=0;j<each_itercommlen;j++){
                                        reduce_sumofcol[j+each_iteroffset+(i+connect)*each_itercommlen]+=local_sumofcol[j+each_iteroffset+(i+connect)*each_itercommlen];
                                }
                        }
                }
                return;
        }
}

void MPI_Reduce_base(double *local_sumofcol,double *reduce_sumofcol,int each_itercommlen,int each_iteroffset,int local_rank,MPI_Comm local_comm,int workerstart_num){
        if(local_rank==0+workerstart_num){
                MPI_Send(local_sumofcol+each_iteroffset+each_itercommlen,each_itercommlen,MPI_DOUBLE,1+workerstart_num,101,local_comm);
                MPI_Send(local_sumofcol+each_iteroffset+3*each_itercommlen,each_itercommlen,MPI_DOUBLE,1+workerstart_num,102,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset,each_itercommlen,MPI_DOUBLE,1+workerstart_num,103,local_comm,MPI_STATUS_IGNORE);
                MPI_Recv(reduce_sumofcol+each_iteroffset+2*each_itercommlen,each_itercommlen,MPI_DOUBLE,1+workerstart_num,104,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        local_sumofcol[j+each_iteroffset]+=reduce_sumofcol[j+each_iteroffset];
                        local_sumofcol[j+each_iteroffset+2*each_itercommlen]+=reduce_sumofcol[j+each_iteroffset+2*each_itercommlen];
                }
                MPI_Send(local_sumofcol+each_iteroffset+2*each_itercommlen,each_itercommlen,MPI_DOUBLE,2+workerstart_num,111,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset,each_itercommlen,MPI_DOUBLE,2+workerstart_num,112,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        reduce_sumofcol[j+each_iteroffset]+=local_sumofcol[j+each_iteroffset];
                }
        }else if(local_rank==1+workerstart_num){
                MPI_Send(local_sumofcol+each_iteroffset,each_itercommlen,MPI_DOUBLE,0+workerstart_num,103,local_comm);
                MPI_Send(local_sumofcol+each_iteroffset+2*each_itercommlen,each_itercommlen,MPI_DOUBLE,0+workerstart_num,104,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset+each_itercommlen,each_itercommlen,MPI_DOUBLE,0+workerstart_num,101,local_comm,MPI_STATUS_IGNORE);
                MPI_Recv(reduce_sumofcol+each_iteroffset+3*each_itercommlen,each_itercommlen,MPI_DOUBLE,0+workerstart_num,102,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        local_sumofcol[j+each_iteroffset+each_itercommlen]+=reduce_sumofcol[j+each_iteroffset+each_itercommlen];
                        local_sumofcol[j+each_iteroffset+3*each_itercommlen]+=reduce_sumofcol[j+each_iteroffset+3*each_itercommlen];
                }
                MPI_Send(local_sumofcol+each_iteroffset+3*each_itercommlen,each_itercommlen,MPI_DOUBLE,3+workerstart_num,113,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset+each_itercommlen,each_itercommlen,MPI_DOUBLE,3+workerstart_num,114,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        reduce_sumofcol[j+each_iteroffset+each_itercommlen]+=local_sumofcol[j+each_iteroffset+each_itercommlen];
                }
        }else if(local_rank==2+workerstart_num){
                MPI_Send(local_sumofcol+each_iteroffset+each_itercommlen,each_itercommlen,MPI_DOUBLE,3+workerstart_num,105,local_comm);
                MPI_Send(local_sumofcol+each_iteroffset+3*each_itercommlen,each_itercommlen,MPI_DOUBLE,3+workerstart_num,106,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset,each_itercommlen,MPI_DOUBLE,3+workerstart_num,107,local_comm,MPI_STATUS_IGNORE);
                MPI_Recv(reduce_sumofcol+each_iteroffset+2*each_itercommlen,each_itercommlen,MPI_DOUBLE,3+workerstart_num,108,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        local_sumofcol[j+each_iteroffset]+=reduce_sumofcol[j+each_iteroffset];
                        local_sumofcol[j+each_iteroffset+2*each_itercommlen]+=reduce_sumofcol[j+each_iteroffset+2*each_itercommlen];
                }
                MPI_Send(local_sumofcol+each_iteroffset,each_itercommlen,MPI_DOUBLE,0+workerstart_num,112,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset+2*each_itercommlen,each_itercommlen,MPI_DOUBLE,0+workerstart_num,111,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        reduce_sumofcol[j+each_iteroffset+2*each_itercommlen]+=local_sumofcol[j+each_iteroffset+2*each_itercommlen];
                }
        }else if(local_rank==3+workerstart_num){
                MPI_Send(local_sumofcol+each_iteroffset,each_itercommlen,MPI_DOUBLE,2+workerstart_num,107,local_comm);
                MPI_Send(local_sumofcol+each_iteroffset+2*each_itercommlen,each_itercommlen,MPI_DOUBLE,2+workerstart_num,108,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset+each_itercommlen,each_itercommlen,MPI_DOUBLE,2+workerstart_num,105,local_comm,MPI_STATUS_IGNORE);
                MPI_Recv(reduce_sumofcol+each_iteroffset+3*each_itercommlen,each_itercommlen,MPI_DOUBLE,2+workerstart_num,106,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        local_sumofcol[j+each_iteroffset+each_itercommlen]+=reduce_sumofcol[j+each_iteroffset+each_itercommlen];
                        local_sumofcol[j+each_iteroffset+3*each_itercommlen]+=reduce_sumofcol[j+each_iteroffset+3*each_itercommlen];
                }
                MPI_Send(local_sumofcol+each_iteroffset+each_itercommlen,each_itercommlen,MPI_DOUBLE,1+workerstart_num,114,local_comm);
                MPI_Recv(reduce_sumofcol+each_iteroffset+3*each_itercommlen,each_itercommlen,MPI_DOUBLE,1+workerstart_num,113,local_comm,MPI_STATUS_IGNORE);
                for(int j=0;j<each_itercommlen;j++){
                        reduce_sumofcol[j+each_iteroffset+3*each_itercommlen]+=local_sumofcol[j+each_iteroffset+3*each_itercommlen];
                }
        }
}

