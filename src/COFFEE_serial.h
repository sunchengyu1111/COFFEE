#ifndef _COFFEE_SERIAL_H
#define _COFFEE_SERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <mpi.h>
#include <immintrin.h>
#include <emmintrin.h>

static void typical(double *copy_sinkhorn, double *sumofcol, const int m, const int n, const int world_rank);
static void C2R(double *local_sinkhorn, double *copy_sinkhorn, double *local_sumofcol, double *sumofcol, const int m, const int n, const int world_rank);
static void COFFEE(double *local_sinkhorn, double *local_sumofcol, double *sumofcol, const int m, const int n, const int world_rank);

#endif
