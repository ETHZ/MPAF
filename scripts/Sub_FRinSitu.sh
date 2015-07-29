#!/bin/bash


FAKES=( "none" )
FLAVORS=( "ee" "em" "mm" )
LIDS=( "cut" )
ISOS=( "mixiso" )
PTS=( "all" )
XPS=( "iso" "isoid" "isofo4" )
MRS=( "sync" )
LPTCUT=( "10" "c10" )
ETAS=( "all" )
#ETAS=( "all" "15-" "15+" "12-" "12+" )

# CH: all possibilities given below
#FAKES=( "none" )
#FLAVORS=( "all" "ee" "em" "mm" )
#LIDS=( "cut" "mva" )
#ISOS=( "mixiso" "relIso" "pTrel" "miniiso" )
#PTS=( "hh" "hl" "ll" )
#XPS=( "iso" "isoid" )
#LPTCUT=( "mu15" "mu5" "10" "cmu15" "cmu5" "c10" )
#SBS=( "SB00" "SB10" "SB20" "SB30" )
#ETAS=( "all" "bb" "be" "ee" "0" "09" "12" "15" "09-" "09+" "12-" "12+" "15-" "15+" )
 
#rm cfg/tmpFiles/*

for mr in ${MRS[@]}; do
  for xp in ${XPS[@]}; do
    for pt in ${PTS[@]}; do
      for is in ${ISOS[@]}; do
        for id in ${LIDS[@]}; do
          for fl in ${FLAVORS[@]}; do
            for fs in ${FAKES[@]}; do
              for es in ${ETAS[@]}; do
                for lc in ${LPTCUT[@]}; do

                  cp cfg/template_FRinSitu.cfg cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|MEASUREMENTREGION|'$mr'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|LEPTONPT|'$pt'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|LEPTONXPOL|'$xp'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|LEPTONFLAV|'$fl'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|LEPTONID|'$id'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|LEPTONISO|'$is'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|LEPTONFAKES|'$fs'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|ADDLEPPTCUT|'$lc'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  sed -i 's|ADDETABIN|'$es'|' cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg

                  #analysis -c $MPAF/cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FRinSitu/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.out -e $MPAF/workdir/logs/FRinSitu/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FRinSitu_${mr}_${pt}_${xp}_${fl}_${id}_${is}_${fs}_${es}_${lc}.cfg
                done
              done
            done
          done
        done
      done
    done
  done
done
