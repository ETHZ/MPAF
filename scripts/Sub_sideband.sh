#!/bin/bash


FAKES=( "none" "all" "b" "c" "light" "tau" )
#FAKES=( "all" )
FLAVORS=( "ee" "em" "mm" )
LIDS=( "cut" )
ISOS=( "mixiso" )
PTS=( "hh" )
TLS=( "tl" "ll" )
SBS=( "all" )
ETAS=( "all" )
#ETAS=( "all" "15-" "15+" "12-" "12+" )

# CH: all possibilities given below
#FAKES=( "none" "all" "b" "c" "light" "tau" )
#FLAVORS=( "all" "ee" "em" "mm" )
#LIDS=( "cut" "mva" )
#ISOS=( "mixiso" "relIso" "pTrel" "miniiso" )
#PTS=( "hh" "hl" "ll" )
#TLS=( "tl" "ll" )
#SBS=( "SB00" "SB10" "SB20" "SB30" )
#ETAS=( "all" "bb" "be" "ee" "0" "09" "12" "15" "09-" "09+" "12-" "12+" "15-" "15+" )
 
#rm cfg/tmpFiles/*

for sb in ${SBS[@]}; do
  for tl in ${TLS[@]}; do
    for pt in ${PTS[@]}; do
      for is in ${ISOS[@]}; do
        for id in ${LIDS[@]}; do
          for fl in ${FLAVORS[@]}; do
            for fs in ${FAKES[@]}; do
              for es in ${ETAS[@]}; do

                cp cfg/template_sideband.cfg cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|SIDEBANDREGION|'$sb'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|LEPTONPT|'$pt'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|LEPTONTL|'$tl'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|LEPTONFLAV|'$fl'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|LEPTONID|'$id'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|LEPTONISO|'$is'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|LEPTONFAKES|'$fs'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                sed -i 's|ADDETABIN|'$es'|' cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg

                #analysis -c $MPAF/cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
                qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/sideband/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.out -e $MPAF/workdir/logs/sideband/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/sideband_${sb}_${pt}_${tl}_${fl}_${id}_${is}_${fs}_${es}.cfg
              done
            done
          done
        done
      done
    done
  done
done
