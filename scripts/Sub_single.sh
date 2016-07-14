#!/bin/bash

#run locally
#analysis -c $MPAF/cfg/tmpFiles/susy3l_${sregion}_${pairstate}.cfg
 
#submit jobs to batch
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/3l.out -e $MPAF/workdir/logs/susy3l/3l.err $MPAF/scripts/submit.sh $MPAF/cfg/3l.cfg
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/3l_closure.out -e $MPAF/workdir/logs/susy3l/3l_closure.err $MPAF/scripts/submit.sh $MPAF/cfg/3l_closure.cfg
