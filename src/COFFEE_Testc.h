#ifndef _COFFEE_TESTC_H
#define _COFFEE_TESTC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <mpi.h>
#define eps 1e-12

void MPIc_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank);

#endif
