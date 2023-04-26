#include "COFFEE_Testc.h"

void MPIc_test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank)
{
        int count = 0;
        double error = 0;
        bool loop = true;
        double start, finish;
        double time1, time01;
        start = MPI_Wtime();
        while (loop)
        {
                if (world_rank == 0)
                {
                        // printf("count %d\n",count);
                        count++;
                }

                // copy data
                for (int i = 0; i < m * n; i++)
                {
                        copy_sinkhorn[i] = local_sinkhorn[i];
                }

                // row
                int startrow = world_rank * m;
                for (int i = 0; i < m; i++)
                {
                        double temp = 0;
                        for (int j = 0; j < n; j++)
                        {
                                temp += local_sinkhorn[i * n + j];
                        }
                        temp = sumofrow[startrow + i] / temp;
                        for (int j = 0; j < n; j++)
                        {
                                local_sinkhorn[i * n + j] *= temp;
                        }
                }

                // col
                for (int i = 0; i < n; i++)
                        local_sumofcol[i] = 0;
                int tep = 0;
                for (int i = 0; i < m * n; i++)
                {
                        local_sumofcol[tep] += local_sinkhorn[i];
                        tep++;
                        if (tep == n)
                                tep = 0;
                }
                MPI_Allreduce(local_sumofcol, allreduce_sumofcol, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
                const int ii = 1440, jj = 4, kk = m / jj, hh = m % jj;
                double temp[ii];
                double *x0 = &local_sinkhorn[0], *x1 = &local_sinkhorn[n], *x2 = &local_sinkhorn[2 * n], *x3 = &local_sinkhorn[3 * n];
                double *y0 = x0, *y1 = x1, *y2 = x2, *y3 = x3, *z0 = x0, *z1 = x1, *z2 = x2, *z3 = x3;
                for (int i = 0; i < n; i += ii)
                {
                        double *t0 = &sumofcol[i], *t1 = &allreduce_sumofcol[i];
                        for (int j = 0; j < ii; j++, t0++, t1++)
                        {
                                temp[j] = (*t0) / (*t1);
                        }
                        for (int j = 0; j < kk; j++)
                        {
                                for (int t = 0; t < ii; t++, z0++, z1++, z2++, z3++)
                                {
                                        *z0 *= temp[t];
                                        *z1 *= temp[t];
                                        *z2 *= temp[t];
                                        *z3 *= temp[t];
                                }
                                y0 += jj * n, y1 += jj * n, y2 += jj * n, y3 += jj * n;
                                z0 = y0, z1 = y1, z2 = y2, z3 = y3;
                        }
                        if (hh)
                        {
                                for (int t = 0; t < ii; t++, z0++, z1++)
                                {
                                        *z0 *= temp[t];
                                        *z1 *= temp[t];
                                }
                                printf("haha\n");
                        }
                        x0 += ii, x1 += ii, x2 += ii, x3 += ii;
                        y0 = x0, y1 = x1, y2 = x2, y3 = x3;
                        z0 = y0, z1 = y1, z2 = y2, z3 = y3;
                }

                // cal error
                double temp1 = 0, temp2 = 0;
                for (int i = 0; i < m * n; i++)
                {
                        temp2 = fabs(local_sinkhorn[i] - copy_sinkhorn[i]);
                        temp1 += temp2 * temp2;
                }
                MPI_Allreduce(&temp1, &error, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
                error = sqrt(error);
                if (error < eps)
                        loop = false;
        }
        finish = MPI_Wtime();
        time01 = (finish - start) * 1000;
        MPI_Allreduce(&time01, &time1, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
        if (world_rank == 0)
                printf("%f, ", time1);
}
