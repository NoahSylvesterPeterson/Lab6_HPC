#!/bin/bash

# -
# |
# | This is a batch script for running a MPI parallel job on Alpine
# |
# | (o) To submit this job, enter:  sbatch slurm.bat 
# | (o) To check the status of this job, enter: squeue -u <username>
# |
# -

# -
# |
# | Part 1: Directives
# |
# -

#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --time=00:20:00
#SBATCH --partition=atesting
#SBATCH --output=slurm-%j.out

# -
# |
# | Part 2: Loading software
# |
# -

module purge
module load intel
module load impi
module use /projects/scru5660/public/software/module
module load valgrind
module load kcachegrind

# -
# |
# | Part 3: User scripting
# |
# -

echo "=="
echo "||"
echo "|| Begin Execution of ert in slurm batch script."
echo "||"
echo "=="

mpirun -n 4 valgrind --tool=callgrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 10 -nCelly 10 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycall.out
mpirun -n 4 valgrind --tool=cachegrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 10 -nCelly 10 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycahce.out

echo "=="
echo "||"
echo "|| Execution of ert in slurm batch script complete."
echo "||"
echo "=="