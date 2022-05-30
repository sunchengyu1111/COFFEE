#!/bin/bash
#!/bin/sh
#SBATCH -J COFFEE_scalable
#SBATCH -N 64 --ntasks-per-node=8
#SBATCH -p work
#SBATCH -exclusive

yhrun -p work -N 2  -n 16  ./COFFEE_centralized       61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 4  -n 32  ./COFFEE_centralized       61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 8  -n 64  ./COFFEE_centralized       61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 16 -n 128 ./COFFEE_centralized       61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 32 -n 256 ./COFFEE_centralized       61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 64 -n 512 ./COFFEE_centralized       61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 2  -n 16  ./COFFEE_scalable          61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 4  -n 32  ./COFFEE_scalable          61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 8  -n 64  ./COFFEE_scalable          61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 16 -n 128 ./COFFEE_scalable          61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 32 -n 256 ./COFFEE_scalable          61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 64 -n 512 ./COFFEE_scalable          61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 2  -n 16  ./MPICH_Ring               61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 4  -n 32  ./MPICH_Ring               61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 8  -n 64  ./MPICH_Ring               61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 16 -n 128 ./MPICH_Ring               61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 32 -n 256 ./MPICH_Ring               61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 64 -n 512 ./MPICH_Ring               61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 2  -n 16  ./MPICH_Ring_distributed   61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 4  -n 32  ./MPICH_Ring_distributed   61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 8  -n 64  ./MPICH_Ring_distributed   61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 16 -n 128 ./MPICH_Ring_distributed   61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 32 -n 256 ./MPICH_Ring_distributed   61440 61440 8 >> COFFEE_scalable.log
yhrun -p work -N 64 -n 512 ./MPICH_Ring_distributed   61440 61440 8 >> COFFEE_scalable.log
