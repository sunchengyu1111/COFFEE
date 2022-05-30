#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <mpi.h>
#include <iostream>
#include <immintrin.h>
#include <emmintrin.h>

int main(int argc,char *argv[]){
	int m=atoi(argv[1]);
	int n=atoi(argv[2]);
	int world_rank,world_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    	double *local_sinkhorn=new double[m*n];
	double *copy_sinkhorn=new double[m*n];
	double *sumofcol=new double[n];
	double *local_sumofcol=new double[n];
	for(int i=0;i<m*n;i++){
        	local_sinkhorn[i]=(double)rand()/(double)(RAND_MAX)*100;                      
        }
	if(world_rank==0){
		for(int i=0;i<n;i++){
			sumofcol[i]=(double)rand()/(double)(RAND_MAX)*100;
		}
	}
	MPI_Bcast(sumofcol,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	double start,finish,time1,time2,time01,time02;
	
	for(int i=0;i<m*n;i++){
		copy_sinkhorn[i]=local_sinkhorn[i];
	}
		
	start=MPI_Wtime();
	for(int i=0;i<n;i++) local_sumofcol[i]=0;
	int tep=0;
	for(int i=0;i<m*n;i++){
		local_sumofcol[tep]+=local_sinkhorn[i];
		tep++;
		if(tep==n) tep=0;
	}
        double temp4=0;
        for(int i=0;i<m;i++){
                //temp2=sumofcol[i]/local_sumofcol[i];
                for(int j=0;j<n;j++){
			temp4=sumofcol[j]/local_sumofcol[j];
                        copy_sinkhorn[j+i*n]*=temp4;
                }
        }
        finish=MPI_Wtime();
        time01=(finish-start)*1000;
        MPI_Allreduce(&time01,&time1,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
        if(world_rank==0) printf("%.3f, ",time1);
	
	MPI_Finalize();	
	delete []sumofcol;
	delete []local_sinkhorn;
	delete []copy_sinkhorn;
	delete []local_sumofcol;
	return 0;
}
