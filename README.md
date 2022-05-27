# COFFEE
## Background
The SK algorithm is a matrix scaling algorithm which can convert a non-negative matrix into a double stochastic matrix. It is a simple but very useful iterative method to approach the double stochastic matrix of Sinkhorn’s theorem by alternately rescaling all rows and all columns of the given matrix. It has been applied to a wide range of theoretical and practical problems, including optimal transport problem, word mover’s distance (WMD), and Cooperative Bayesian, etc. 

## About COFFEE
COFFEE is a tool for fast and efficient executions of the Sinkhorn-Knopp (SK) algorithm on HPC systems and this work continues to be optimized. 

## Software dependences
* [GNU Compiler (GCC)](https://gcc.gnu.org/)
* [MPICH](https://mpich.org/)

## Hardware platform

\                |AMD    |Intel  |ARM V8 |
-----------------|-------|-------|-------|
Number of Cores  |8      |12     |10     |
Frequency        |2.9 GHz|2.9 GHz|3.2 GHz|
L1 cache         |512 KB |64 KB  |320 KB |
L2 cache         |4 MB   |256KB  |12MB   |
L3 cache         |8 MB   |12 MB  |None   |
RAM              |16 GB  |48 GB  |16 GB  |

## Compile and install
```bash
$ cd src && make
```
