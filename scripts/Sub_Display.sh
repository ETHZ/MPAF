#!/bin/bash

SIG=( "T1t412" ) # "T1t415" "T5t410" "T5q4WZ315" "T5q4WZ325" "T5q4WZ12" "T5q4WZ15" "T5q4ZZ315" "T5q4ZZ325" "T5q4ZZ12" "T5q4ZZ15" )



#rm cfg/tmpFiles/*

for sigs in ${SIG[@]}; do


    signalmodel=$sigs
    cp cards/susy3l_auto.C cards/tmpFiles/susy3l_auto.C
    sed -i 's|SIGNALMOD|'$signalmodel'|' cards/tmpFiles/susy3l_auto.C

    #run locally
    ../scripts/Sub_susy3l_Display.sh
    
    #submit jobs to batch
    #qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_${sregion}_${pairstate}.out -e $MPAF/workdir/logs/susy3l/susy3l_${sregion}_${pairstate}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/susy3l_${sregion}_${pairstate}.cfg
done
