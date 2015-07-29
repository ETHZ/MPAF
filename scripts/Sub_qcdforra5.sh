#!/bin/bash

LIDS=( "cut" )
MRS=( "MR00" "MR01" "MR02" "MR03" )

#rm cfg/tmpFiles/*

for mr in ${MRS[@]}; do

  ii=0

  for lid in ${LIDS[@]}; do

    mregion=$mr 
    lepid=$lid

    cp cfg/template_qcdforra5.cfg cfg/tmpFiles/qcdforra5_${mregion}_${lepid}.cfg
    sed -i 's|MEASUREMENTREGION|'$mregion'|' cfg/tmpFiles/qcdforra5_${mregion}_${lepid}.cfg

    qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/qcdforra5_${mregion}_${lepid}.out -e $MPAF/workdir/logs/FakeRatio/qcdforra5_${mregion}_${lepid}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/qcdforra5_${mregion}_${lepid}.cfg

    ii=`echo $ii +1 | bc`

  done
done
