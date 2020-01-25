#!/bin/bash
# BASH script: hw1.sh; to make executable use: chmod u+x hw1.sh
# wget https://mac.r-project.org/benchmarks/bench.R
# to run and time it use: time ./hw1.sh

# module load R

# export R_BATCH_OPTIONS="--no-save --no-restore --slave"

for i in {x..z}
do
        for j in {1..5}
        do
                R CMD BATCH bench.R file-${i}${j} &
        done
 wait
 done
                
# 5 parallel jobs repeated 3 times for x y z variables
