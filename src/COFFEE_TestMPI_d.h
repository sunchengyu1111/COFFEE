#ifndef _COFFEE_TESTMPI_D_H
#define _COFFEE_TESTMPI_D_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <mpi.h>
#define eps 1e-12

void col_subroutine(double *local_sinkhorn, double *local_sumofcol, double *sumofcol, double *tmp, const int ii, const int jj, const int kk, const int hh, const int i, const int s, const int each_iterlength, const int n);

void MPI_Reduce_scy(double *local_sumofcol, double *reduce_sumofcol, int each_iterlength, int each_itercommlen, int each_iteroffset, int local_rank, MPI_Comm local_comm, int worker_num, int workerstart_num);

void MPI_Reduce_base(double *local_sumofcol, double *reduce_sumofcol, int each_itercommlen, int each_iteroffset, int local_rank, MPI_Comm local_comm, int workerstart_num);

void MPId_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *reduce_sumofcol, double *allreduce_sumofcol, const int m, const int m2, const int n, const int world_rank, const int local_rank, const int local_size, const int total_iternum, const int each_iterlength, MPI_Comm local_comm, MPI_Comm worker_comm, MPI_Comm manager_comm);

#endif
