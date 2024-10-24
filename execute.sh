#! /bin/bash

rm times.tsv

for SCHEDULE in 'static' 'static, 8' 'dynamic' 'guided'
do
    for THREADS in 1 2 4 8 16 32
    do 
        export OMP_SCHEDULE=$SCHEDULE
        export OMP_NUM_THREADS=$THREADS
        ./jim-haslett-csc6220-hw4
    done # for THREADS
done # for SCHEDULE
