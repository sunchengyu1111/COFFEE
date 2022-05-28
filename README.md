# COFFEE
## Background
The SK algorithm is a matrix scaling algorithm which can convert a non-negative matrix into a double stochastic matrix. It is a simple but very useful iterative method to approach the double stochastic matrix of Sinkhorn’s theorem by alternately rescaling all rows and all columns of the given matrix. It has been applied to a wide range of theoretical and practical problems, including optimal transport problem, word mover’s distance (WMD), and Cooperative Bayesian, etc. 

## About COFFEE
COFFEE is a tool for fast and efficient executions of the Sinkhorn-Knopp (SK) algorithm on HPC systems and this work continues to be optimized. 

## Software dependences
* [GNU Compiler (GCC)](https://gcc.gnu.org/)
* [MPICH](https://mpich.org/)

We use GCC 9.3.0 and MPICH 3.4.0 to implement COFFEE. You can also use other compilers such as [Clang](https://clang.llvm.org/) and other MPI open source software such as [Open MPI](https://www.open-mpi.org/).

## Hardware platform

\                |AMD    |Intel  |ARM V8 |
-----------------|-------|-------|-------|
Number of Cores  |8      |12     |10     |
Frequency        |2.9 GHz|2.9 GHz|3.2 GHz|
L1 cache         |512 KB |64 KB  |320 KB |
L2 cache         |4 MB   |256KB  |12MB   |
L3 cache         |8 MB   |12 MB  |None   |
RAM              |16 GB  |48 GB  |16 GB  |

We implement COFFEE using the above hardware platform. But COFFEE is equally applicable to other platforms and supercomputers.

## Compile and install
Our makefile is based on [GNU Compiler (GCC)](https://gcc.gnu.org/) and can be compiled on the Tianhe series of supercomputers by the following command.
```bash
$ cd src && make
```
Supercomputers using other compilers need to modify the makefile.

## Running
Every executable file has a corresponding .sh file with the same name.
For example, you can run COFFEE_serial with COFFEE_serial.sh in single-node.
```bash
$ sh COFFEE_serial.sh
```
You can also run on multiple nodes on a supercomputer or in a distributed environment built by yourself. Here is a tutorial [Running an MPI Cluster within a LAN](https://mpitutorial.com/tutorials/running-an-mpi-cluster-within-a-lan/) to help you build an MPI cluster environment.

## Result
When finishing executing, you can find running time results in .log file with the same name.
For example, COFFEE_serial.log.

## Contributor
[@sunchengyu1111](https://github.com/sunchengyu1111)

Contact: Chengyu Sun (scyna1024@gmail.com)
