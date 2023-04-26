#ifndef _COFFEE_TESTCPU_H
#define _COFFEE_TESTCPU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <mpi.h>
#include <immintrin.h>
#include <emmintrin.h>
#define eps 1e-12

void CPU_Test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank);

#endif
