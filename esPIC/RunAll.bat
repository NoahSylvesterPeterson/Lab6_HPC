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
#SBATCH --time=00:10:00
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
module load python

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
echo "src"
cd src
mpicxx esPIC.cpp -o esPIC
mpirun -n 4 ./esPIC -nPEx 2 -nPEy 2 -nCellx 10 -nCelly 10 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 1 -dt 0.01 > ../orig.out
cp ptcl_0_99.plt pc_0_F.out
cp ptcl_1_99.plt pc_1_F.out
cp ptcl_2_99.plt pc_2_F.out
cp ptcl_3_99.plt pc_3_F.out
rm *.plt




echo "equ1"
cd ../src_equ_Vec1
mpicxx esPIC.cpp -o esPIC
mpirun -n 4 ./esPIC -nPEx 2 -nPEy 2 -nCellx 10 -nCelly 10 -flux 400. -vx_bdy 1. -npHat 80. -tEnd 1 -dt 0.01 > ../equ1.out
cp ptcl_0_99.plt pc_0_F.out
cp ptcl_1_99.plt pc_1_F.out
cp ptcl_2_99.plt pc_2_F.out
cp ptcl_3_99.plt pc_3_F.out
rm *.plt

cd ..
python RMSE.py > RMSE.out
echo "=="
echo "||"
echo "|| Execution of ert in slurm batch script complete."
echo "||"
echo "=="