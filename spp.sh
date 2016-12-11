#!/bin/bash
#SBATCH -J SSP_420
#SBATCH --mail-user=thomas.kosiewski@stud.tu-darmstadt.de
#SBATCH --mail-type=ALL
#SBATCH -e /home/kurse/kurs1/tk83vydi/logs/SPP_Prak1.err.%j
#SBATCH -o /home/kurse/kurs1/tk83vydi/logs/SPP_Prak1.out.%j
#SBATCH --mem-per-cpu=250
#SBATCH -t 5
#SBATCH -n 4
#SBATCH -p kurs1
#SBATCH -c 4
echo "This is Job $SLURM_JOB_ID"
module load gcc
module load openmpi/gcc
make
mpirun ./bin/Ex2a pg30.txt 82-0.txt
