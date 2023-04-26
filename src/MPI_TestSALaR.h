#ifndef _MPI_TESTSALAR_H
#define _MPI_TESTSALAR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <mpi.h>
#define eps 1e-12

void SALaR_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *reduce_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank, const int local_rank, const int local_size, const int total_iternum, const int each_iterlength, MPI_Comm local_comm, MPI_Comm worker_comm, MPI_Comm leader_comm);

#endif
