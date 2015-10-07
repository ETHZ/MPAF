#!/bin/bash

HTS=( "0" "25" "50" "75" "100" "125" "150" "175" "200" "225" "250" "275" "300" "325" "350" "375" "400" "425" "450" "475" "500" "525" "550" "575" "600")

#rm cfg/tmpFiles/*

for ht in ${HTS[@]}; do


    htcut=$ht

    cp cfg/template3L_trig.cfg cfg/tmpFiles/susy3l_trig_${htcut}.cfg
    sed -i 's|HTCUT|'$htcut'|' cfg/tmpFiles/susy3l_trig_${htcut}.cfg

    #run locally
    analysis -c $MPAF/cfg/tmpFiles/susy3l_trig_${htcut}.cfg
    
    #submit jobs to batch
    #qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_${sregion}_${pairstate}.out -e $MPAF/workdir/logs/susy3l/susy3l_${sregion}_${pairstate}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/susy3l_${sregion}_${pairstate}.cfg
done
