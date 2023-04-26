#ifndef _MPI_TESTRING_H
#define _MPI_TESTRING_H

#include <cmath>
#include "Ring.h"
#define eps 1e-12

void Ring_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank);

#endif

