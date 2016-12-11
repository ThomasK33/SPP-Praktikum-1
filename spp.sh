#!/bin/bash
#SBATCH -J SSP_420
#SBATCH --mail-user=thomas.kosiewski@stud.tu-darmstadt.de
#SBATCH --mail-type=ALL
#SBATCH -e /home/tk83vydi/SPP_Praktikum1/Job_Name.err.%j
#SBATCH -o /home/<tu-id>/SPP_Praltikum1/Job_Name.out.%j
#SBATCH --mem-per-cpu=250
#SBATCH –t 00:05:00
#SBATCH –n 4
#SBATCH –p kurs1
echo "This is Job $SLURM_JOB_ID"
module load gcc
module load openmpi/gcc
mpirun ./bin/Ex2a
