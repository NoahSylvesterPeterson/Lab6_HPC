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
rm esPIC
mpicxx -g esPIC.cpp -o esPIC

rm run_2b2pros_10b10cell_400flux/cachegrind.out*
rm run_2b2pros_100b100cell_400flux/cachegrind.out*
rm run_2b2pros_50b50cell_400flux/cachegrind.out*
rm run_2b2pros_50b50cell_600flux/cachegrind.out*
rm run_2b2pros_50b50cell_800flux/cachegrind.out*

rm run_2b2pros_10b10cell_400flux/callgrind.out*
rm run_2b2pros_100b100cell_400flux/callgrind.out*
rm run_2b2pros_50b50cell_400flux/callgrind.out*
rm run_2b2pros_50b50cell_600flux/callgrind.out*
rm run_2b2pros_50b50cell_800flux/callgrind.out*


mpirun -n 4 valgrind --tool=callgrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 10 -nCelly 10 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycall.out
mpirun -n 4 valgrind --tool=cachegrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 10 -nCelly 10 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycahce.out
cp cachegrind.out* run_2b2pros_10b10cell_400flux
cp callgrind.out* run_2b2pros_10b10cell_400flux
rm cachegrind.out*
rm callgrind.out*


mpirun -n 4 valgrind --tool=callgrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 50 -nCelly 50 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycall.out
mpirun -n 4 valgrind --tool=cachegrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 50 -nCelly 50 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycahce.out
cp cachegrind.out* run_2b2pros_50b50cell_400flux
cp callgrind.out* run_2b2pros_50b50cell_400flux
rm cachegrind.out*
rm callgrind.out*


mpirun -n 4 valgrind --tool=callgrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 100 -nCelly 100 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycall.out
mpirun -n 4 valgrind --tool=cachegrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 100 -nCelly 100 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycahce.out
cp cachegrind.out* run_2b2pros_100b100cell_400flux
cp callgrind.out* run_2b2pros_100b100cell_400flux
rm cachegrind.out*
rm callgrind.out*



mpirun -n 4 valgrind --tool=callgrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 50 -nCelly 50 -flux 600. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycall.out
mpirun -n 4 valgrind --tool=cachegrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 50 -nCelly 50 -flux 600. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycahce.out
cp cachegrind.out* run_2b2pros_50b50cell_600flux
cp callgrind.out* run_2b2pros_50b50cell_600flux
rm cachegrind.out*
rm callgrind.out*

mpirun -n 4 valgrind --tool=callgrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 50 -nCelly 50 -flux 800. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycall.out
mpirun -n 4 valgrind --tool=cachegrind  ./esPIC -nPEx 2 -nPEy 2 -nCellx 50 -nCelly 50 -flux 800. -vx_bdy 1. -npHat 80. -tEnd 0.1 -dt .01 > ttycahce.out
cp cachegrind.out* run_2b2pros_50b50cell_800flux
cp callgrind.out* run_2b2pros_50b50cell_800flux
rm cachegrind.out*
rm callgrind.out*

rm *.plt

echo "=="
echo "||"
echo "|| Execution of ert in slurm batch script complete."
echo "||"
echo "=="
