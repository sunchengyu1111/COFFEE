#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#define eps 1e-12

int main(int argc,char *argv[]){
	//initialize
        int m=atoi(argv[1]);
        int n=atoi(argv[2]);
	int k=atoi(argv[3]);
	
	//allocate memory
    	double *local_sinkhorn=new double[m*n];
	double *copy_sinkhorn=new double[m*n];
    	double *sumofrow=new double[m];
	double *sumofcol=new double[n];
	srand((unsigned int)time(NULL));
	for(int i=0;i<m*n;i+=k){
		int temp=rand()%k;
		for(int j=0;j<k;j++){
			if(j==temp){
				local_sinkhorn[j+i]=0;
			}else{
				local_sinkhorn[j+i]=(double)rand()/(double)(RAND_MAX)*100;
			}
		}
        }
	for(int i=0;i<m;i++){
		sumofrow[i]=(double)rand()/(double)(RAND_MAX)*100;
	}
	for(int i=0;i<n;i++){
		sumofcol[i]=(double)rand()/(double)(RAND_MAX)*100;
	}
	
	//start
	int count=0;
	bool loop=true;
	double time=0;
	while(loop){
		clock_t start=clock();

		//copy data
		for(int i=0;i<m*n;i++){
			copy_sinkhorn[i]=local_sinkhorn[i];
		}
		
		//row
		for(int i=0;i<m;i++){
			double temp=0;
			for(int j=0;j<n;j++){
				temp+=local_sinkhorn[i*n+j];
			}
			temp=sumofrow[i]/temp;
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
			temp=sumofcol[i]/temp;
			for(int j=0;j<m;j++){
				local_sinkhorn[i+j*n]*=temp;
			}
		}

		//cal error
		double temp=0,error=0;
		for(int i=0;i<m*n;i++){
			temp=fabs(local_sinkhorn[i]-copy_sinkhorn[i]);
			error+=temp*temp;
		}
		error=sqrt(error);
		if(error<eps) loop=false;
		
		clock_t finish=clock();
		time+=(double)(finish-start)/CLOCKS_PER_SEC*1000;
		//printf("dense:count:%d,time:%f,error:%f\n",count,(double)(finish-start)/CLOCKS_PER_SEC*1000,error);
                count++;
	}
	printf("dense:%f",time/count);

        //finish
        delete []sumofrow;
        delete []sumofcol;
        delete []local_sinkhorn;
        delete []copy_sinkhorn;
        return 0;
}
