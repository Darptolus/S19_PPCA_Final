#!/bin/bash
for i in 10 20 30 40 50 60 70 80 90 100; do make clean; make N_SIZE=$i N_OPR=480 N_ITER=1; make run; done;
for i in 1 2 3 4 5 6 7 8 9 10; do make clean; make N_SIZE=100 N_OPR=48*$i N_ITER=1; make run; done;