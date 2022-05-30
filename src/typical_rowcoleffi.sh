#!/bin/bash
#!/bin/sh
#SBATCH -J typical_rowcoleffi
#SBATCH -N 64 --ntasks-per-node=8
#SBATCH -p work
#SBATCH -exclusive

yhrun -p work -N 1  -n 1   ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 1  -n 2   ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 1  -n 4   ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 1  -n 8   ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 2  -n 16  ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 4  -n 32  ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 8  -n 64  ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 16 -n 128 ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 32 -n 256 ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
yhrun -p work -N 64 -n 512 ./typical_rowcoleffi 20480 >> typical_rowcoleffi.log
