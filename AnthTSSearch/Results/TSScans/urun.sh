#!/bin/bash
for i in {0..13}
do 
    cd TSSCAN_$i
    sbatch RunScript
    cd ..
done
