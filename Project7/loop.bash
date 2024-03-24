#!/bin/bash
#SBATCH -J proj07
#SBATCH -A cs475-575
#SBATCH -p classmpifinal
#SBATCH -N 4 # number of nodes
#SBATCH -n 4 # number of tasks
#SBATCH --constraint=ib
#SBATCH -o proj07.out
#SBATCH -e proj07.err
#SBATCH --mail-type=END,FAIL
#SBATCH --mail-user=patenirm@oregonstate.edu
module load openmpi
mpic++ proj07.cpp -o proj07 -lm
for n in 1 2 4 6 8
do
    mpiexec -mca btl self,tcp -np $n ./proj07
done