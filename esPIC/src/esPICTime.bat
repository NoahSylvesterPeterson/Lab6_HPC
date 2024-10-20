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
#SBATCH --time=00:09:00
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
mpicxx esPIC.cpp -p -g -o esPICTime
gprof ./esPICTime > gprof.out
echo "=="
echo "||"
echo "|| Execution of ert in slurm batch script complete."
echo "||"
echo "=="
