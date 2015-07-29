#!/bin/bash

SRS=( "SR00" "SR10" "SR20" "SR30" )
PTS=( "hh" )
FLS=( "ee" "em" "mm" )

#SRS=( "SR00" "SR10" "SR20" "SR30" "SR01" "SR02" "SR03" "SR04" "SR05" "SR06" "SR07" "SR08" "SR11" "SR12" "SR13" "SR14" "SR15" "SR16" "SR17" "SR18" "SR21" "SR22" "SR23" "SR24" "SR25" "SR26" "SR27" "SR28" )
#PTS=( "hh" "hl" "ll" )
#FLS=( "ee" "em" "mm" )

#rm cfg/tmpFiles/*

for sr in ${SRS[@]}; do

  for pt in ${PTS[@]}; do

    for fl in ${FLS[@]}; do

      sregion=$sr
      leppt=$pt
      flavor=$fl

      cp cfg/template_phys14limits.cfg cfg/tmpFiles/phys14limits_${sregion}_${leppt}_${flavor}.cfg
      sed -i 's|SIGNALREGION|'$sregion'|' cfg/tmpFiles/phys14limits_${sregion}_${leppt}_${flavor}.cfg
      sed -i 's|PTSCENARIO|'$leppt'|' cfg/tmpFiles/phys14limits_${sregion}_${leppt}_${flavor}.cfg
      sed -i 's|FLAVORS|'$flavor'|' cfg/tmpFiles/phys14limits_${sregion}_${leppt}_${flavor}.cfg

      #analysis -c $MPAF/cfg/tmpFiles/phys14limits_${sregion}_${leppt}_${flavor}.cfg
      qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/phys14limits/phys14limits_${sregion}_${leppt}_${flavor}.out -e $MPAF/workdir/logs/phys14limits/phys14limits_${sregion}_${leppt}_${flavor}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/phys14limits_${sregion}_${leppt}_${flavor}.cfg

    done
  done
done
