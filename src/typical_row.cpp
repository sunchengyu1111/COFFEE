#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

int main(int argc,char *argv[]){
	int m=atoi(argv[1]);
        int n=atoi(argv[2]);
        double *local_sinkhorn=new double[m*n];
        double *sumofrow=new double[m];
        for(int i=0;i<m*n;i++){
                local_sinkhorn[i]=(double)rand()/(double)(RAND_MAX)*100;
        }
        for(int i=0;i<m;i++){
                sumofrow[i]=(double)rand()/(double)(RAND_MAX)*100;
        }
	clock_t start=clock();
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
	clock_t finish=clock();
	printf("%f, ",(double)(finish-start)/CLOCKS_PER_SEC*1000);
        delete []sumofrow;
        delete []local_sinkhorn;
        return 0;
}
