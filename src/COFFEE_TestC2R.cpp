#include "COFFEE_TestC2R.h"

void C2R_Test(double *local_sinkhorn, double *copy_sinkhorn, double *sumofrow, double *sumofcol, double *local_sumofcol, double *allreduce_sumofcol, const int m, const int n, const int world_rank)
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
                double temp = 0;
                for (int i = 0; i < m; i++)
                {
                        for (int j = 0; j < n; j++)
                        {
                                temp = sumofcol[j] / allreduce_sumofcol[j];
                                local_sinkhorn[j + i * n] *= temp;
                        }
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
