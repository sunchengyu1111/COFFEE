#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

int main(int argc,char *argv[]){
	int m=atoi(argv[1]);
	int n=atoi(argv[2]);
    	double *local_sinkhorn=new double[m*n];
	double *sumofcol=new double[n];
	for(int i=0;i<m*n;i++){
        	local_sinkhorn[i]=(double)rand()/(double)(RAND_MAX)*100;                      
        }
	for(int i=0;i<n;i++){
		sumofcol[i]=(double)rand()/(double)(RAND_MAX)*100;
	}
	clock_t start=clock();
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
	clock_t finish=clock();
	printf("%f, ",(double)(finish-start)/CLOCKS_PER_SEC*1000);
	delete []local_sinkhorn;
	delete []sumofcol;
	return 0;
}
