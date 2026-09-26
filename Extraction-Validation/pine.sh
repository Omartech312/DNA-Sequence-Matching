#!/bin/bash
#SBATCH --job-name=pine                     # the name of your job
#SBATCH --output=/home/sor22/HW1/pine.txt    # this is the file your output and errors go to
#SBATCH --chdir=/home/sor22/HW1                 # your work directory
#SBATCH --time=1:00:00                      # (max time) 13 hrs, hmm ya that sounds good 
#SBATCH --mem=248000                         # (total mem) 10GB of memory hmm, sounds good to me
srun homework a n /common/contrib/classroom/inf503/genomes/pine.fasta