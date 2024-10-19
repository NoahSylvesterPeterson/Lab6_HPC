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
#SBATCH --ntasks=16
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
mpirun -n 1  ./esPIC -nPEx 1 -nPEy 1 -nCellx 24 -nCelly 24 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.5 -dt .01 > Speed1.out
mpirun -n 4 ./esPIC -nPEx 2 -nPEy 2 -nCellx 12 -nCelly 12 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.5 -dt .01 > Speed2.out
mpirun -n 9 ./esPIC -nPEx 3 -nPEy 3 -nCellx 8 -nCelly 8 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.5 -dt .01 > Speed3.out
mpirun -n 16 ./esPIC -nPEx 4 -nPEy 4 -nCellx 6 -nCelly 6 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.5 -dt .01 > Speed4.out

echo "=="
echo "||"
echo "|| Execution of ert in slurm batch script complete."
echo "||"
echo "=="
