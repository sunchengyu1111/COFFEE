#!/bin/bash
#!/bin/sh
#SBATCH -J COFFEE_MPI_d
#SBATCH -N 64 --ntasks-per-node=9
#SBATCH -p work
#SBATCH -exclusive

yhrun -p work -N 64 -n 576 ../src/MPI_Ring       23040   23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       46080   46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       69120   69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160   92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       115200  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       138240  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       184320  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       207360  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       230400  230400 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   23040   23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   46080   46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   69120   69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160   92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   115200  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   138240  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   184320  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   207360  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   230400  230400 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      23040   23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      46080   46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      69120   69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160   92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      115200  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      138240  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      184320  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      207360  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      230400  230400 9 >>COFFEE_MPI_d.log

yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160  230400 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160  230400 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160  230400 9 >>COFFEE_MPI_d.log

yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  230400 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  230400 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  23040  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  46080  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  69120  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  92160  9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  115200 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  138240 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  184320 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  207360 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  230400 9 >>COFFEE_MPI_d.log

yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      23040   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      46080   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      69120   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      115200  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      138400  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      184320  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      207360  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      230400  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       23040   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       46080   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       69120   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       115200  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       138400  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       184320  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       207360  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       230400  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   23040   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   46080   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   69120   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160   92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   115200  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   138240  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   184320  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   207360  92160 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   230400  92160 9 >>COFFEE_MPI_d.log

yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      23040   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      46080   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      69120   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      92160   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      115200  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      138400  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      184320  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      207360  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_SALaR      230400  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       23040   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       46080   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       69120   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       92160   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       115200  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       138400  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       184320  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       207360  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/MPI_Ring       230400  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   23040   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   46080   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   69120   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   92160   161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   115200  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   138240  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   161280  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   184320  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   207360  161280 9 >>COFFEE_MPI_d.log
yhrun -p work -N 64 -n 576 ../src/COFFEE_MPI_d   230400  161280 9 >>COFFEE_MPI_d.log