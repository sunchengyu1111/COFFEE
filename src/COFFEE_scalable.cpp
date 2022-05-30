#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <mpi.h>
#include <iostream>
#define eps 1e-12

void MPI_Reduce_scy(double *local_sumofcol,double *reduce_sumofcol,int each_iterlength,int each_itercommlen,int each_iteroffset,int local_rank,MPI_Comm local_comm,int worker_num,int workerstart_num);
void MPI_Reduce_base(double *local_sumofcol,double *reduce_sumofcol,int each_itercommlen,int each_iteroffset,int local_rank,MPI_Comm local_comm,int workerstart_num);
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
                        printf("count:%d\n",count);
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
		
		if(MPI_COMM_NULL!=worker_comm) MPI_Reduce(local_sumofcol,reduce_sumofcol,each_iterlength,MPI_DOUBLE,MPI_SUM,0,worker_comm);
		for(int i=1;i<total_iternum;i++){
			if(local_rank==0){
                                MPI_Send(reduce_sumofcol,each_iterlength,MPI_DOUBLE,local_size-1,0,local_comm);
                        }
                        if(local_rank==local_size-1){
                                MPI_Recv(allreduce_sumofcol,each_iterlength,MPI_DOUBLE,0,0,local_comm,MPI_STATUS_IGNORE);
			}
			if(MPI_COMM_NULL!=worker_comm){
				MPI_Reduce(local_sumofcol+i*each_iterlength,reduce_sumofcol,each_iterlength,MPI_DOUBLE,MPI_SUM,0,worker_comm);
				if(i==1){
                 			MPI_Status worker_status;
                 			MPI_Recv(local_sinkhorn+m*n,m*n/(local_size-1),MPI_DOUBLE,local_size-1,local_rank,local_comm,&worker_status);
					/*	
					if(world_rank==2){
                				printf("rank:%d,here2,local_sinkhorn\n",world_rank);
                				for(int i=8;i<10;i++){
                        				for(int j=0;j<n;j++){
                                				printf("%f\t",local_sinkhorn[i*n+j]);
                        				}
                        				printf("\n");
                				}
				        }
					*/
		        	}else{
					int kk=m2/jj,hh=m2%jj;
					double *x0=&local_sinkhorn[(i-2)*each_iterlength],*x1=&local_sinkhorn[n+(i-2)*each_iterlength],*x2=&local_sinkhorn[2*n+(i-2)*each_iterlength],*x3=&local_sinkhorn[3*n+(i-2)*each_iterlength];
					double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
					for(int a=(i-2)*each_iterlength;a<(i-1)*each_iterlength;a+=ii){
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
							for(int t=0;t<ii;t++,z0++,z1++){
								*z0*=tmp[t];
								*z1*=tmp[t];
							}
						}
						x0+=ii,x1+=ii,x2+=ii,x3+=ii;
						y0=x0,y1=x1,y2=x2,y3=x3;
						z0=y0,z1=y1,z2=y2,z3=y3;
					}
					/*	
					for(int a=(i-2)*each_iterlength;a<(i-1)*each_iterlength;a++){
                        			for(int b=0;b<m2;b++){
                                			local_sinkhorn[a+b*n]=local_sinkhorn[a+b*n]/local_sumofcol[a]*sumofcol[a];
                        			}
                			}
					*/
					/*
					if(world_rank==2){
                                                printf("rank:%d,here3,local_sinkhorn\n",world_rank);
						for(int j=0;j<20;j++){
							printf("%f\t",local_sumofcol[j]);
						}
						printf("\n");
						for(int j=0;j<20;j++){
                                                        printf("%f\t",sumofcol[j]);
                                                }
						printf("\n");
                                                for(int i=8;i<10;i++){
                                                        for(int j=0;j<20;j++){
                                                                printf("%f\t",local_sinkhorn[i*n+j]);
                                                        }
                                                        printf("\n");
                                                }
                                        }
					*/
				}
			}
			/*	
			if(world_rank==0){
				printf("rank:%d,here4,reduce_sumofcol\n",world_rank);
				for(int i=0;i<n;i++){
					printf("%f\t",reduce_sumofcol[i]);
				}
				printf("\n");   
			}
			*/
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
				//check
				if(i==1) MPI_Wait(&manager_request,&manager_status);
                     		/*				
                               	printf("rank:%d,here5,allreduce_sumofcol\n",world_rank);
                               	for(int i=0;i<n;i++){
                              	        printf("%f\t",allreduce_sumofcol[i]);
                       	        }
				printf("\n");
                	  	*/      
                	}
			MPI_Bcast(local_sumofcol+(i-1)*each_iterlength,each_iterlength,MPI_DOUBLE,local_size-1,local_comm);
			/*
                        printf("rank:%d,here6,local_sumofcol\n",world_rank);
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
		}		
		if(MPI_COMM_NULL!=worker_comm){
			int kk=m2/jj,hh=m2%jj;
			double *x0=&local_sinkhorn[(total_iternum-2)*each_iterlength],*x1=&local_sinkhorn[n+(total_iternum-2)*each_iterlength],*x2=&local_sinkhorn[2*n+(total_iternum-2)*each_iterlength],*x3=&local_sinkhorn[3*n+(total_iternum-2)*each_iterlength];
			double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
			for(int a=(total_iternum-2)*each_iterlength;a<(total_iternum-1)*each_iterlength;a+=ii){
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
					for(int t=0;t<ii;t++,z0++,z1++){
						*z0*=tmp[t];
						*z1*=tmp[t];
					}
				}
				x0+=ii,x1+=ii,x2+=ii,x3+=ii;
				y0=x0,y1=x1,y2=x2,y3=x3;
				z0=y0,z1=y1,z2=y2,z3=y3;
			}
			/*
			for(int a=(total_iternum-2)*each_iterlength;a<(total_iternum-1)*each_iterlength;a++){
				for(int b=0;b<m2;b++){
					local_sinkhorn[a+b*n]=local_sinkhorn[a+b*n]/local_sumofcol[a]*sumofcol[a];
				}
			}
			*/
			/*
			if(world_rank==2){
				printf("rank:%d,here8,local_sinkhorn\n",world_rank);
				for(int j=0;j<20;j++){
					printf("%f\t",local_sumofcol[j]);
				}
				printf("\n");
				for(int j=0;j<20;j++){
					printf("%f\t",sumofcol[j]);
				}
				printf("\n");
				for(int i=8;i<10;i++){
					for(int j=0;j<20;j++){
						printf("%f\t",local_sinkhorn[i*n+j]);
					}
					printf("\n");
				}
			}
			*/
		}
                if(MPI_COMM_NULL!=manager_comm){
                        for(int j=0;j<each_iterlength;j++){
                                allreduce_sumofcol[j]+=local_sumofcol[j+(total_iternum-1)*each_iterlength];
                        }
			usleep(160000);
                        MPI_Allreduce(allreduce_sumofcol,local_sumofcol+(total_iternum-1)*each_iterlength,each_iterlength,MPI_DOUBLE,MPI_SUM,manager_comm);
			/*                              
                        printf("rank:%d,here9,allreduce_sumofcol\n",world_rank);
                        for(int i=0;i<n;i++){
                                printf("%f\t",allreduce_sumofcol[i]);
                        }
                       	printf("\n");
			*/
                }
		MPI_Bcast(local_sumofcol+(total_iternum-1)*each_iterlength,each_iterlength,MPI_DOUBLE,local_size-1,local_comm);
		/*		
		printf("rank:%d,here10,local_sumofcol\n",world_rank);
                for(int i=0;i<n;i++){
                        printf("%f\t",local_sumofcol[i]);
                }
                printf("\n");
		*/
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
		double *x0=&local_sinkhorn[(total_iternum-1)*each_iterlength],*x1=&local_sinkhorn[n+(total_iternum-1)*each_iterlength],*x2=&local_sinkhorn[2*n+(total_iternum-1)*each_iterlength],*x3=&local_sinkhorn[3*n+(total_iternum-1)*each_iterlength];
		double *y0=x0,*y1=x1,*y2=x2,*y3=x3,*z0=x0,*z1=x1,*z2=x2,*z3=x3;
		for(int a=(total_iternum-1)*each_iterlength;a<n;a+=ii){
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
				for(int t=0;t<ii;t++,z0++,z1++){
					*z0*=tmp[t];
					*z1*=tmp[t];
				}
			}
			x0+=ii,x1+=ii,x2+=ii,x3+=ii;
			y0=x0,y1=x1,y2=x2,y3=x3;
			z0=y0,z1=y1,z2=y2,z3=y3;
		}
		/*
		for(int a=(total_iternum-1)*each_iterlength;a<n;a++){
			for(int b=0;b<m;b++){
				local_sinkhorn[a+b*n]=local_sinkhorn[a+b*n]/local_sumofcol[a]*sumofcol[a];
			}
		}
		*/

		//cal error
               	for(int i=0;i<m*n;i++){
                        temp2=fabs(local_sinkhorn[i]-copy_sinkhorn[i]);
                        temp1+=temp2*temp2;
                }
                MPI_Allreduce(&temp1,&error,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
                error=sqrt(error);
                if(error<eps) loop=false;
		temp1=0,temp2=0;
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
