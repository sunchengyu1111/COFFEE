#ifndef _RING_H
#define _RING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cassert>
#include <mpi.h>
#include <vector>

int MPI_RingAllreduce(double* input, double* output, int count, MPI_Datatype datatype);

#endif
