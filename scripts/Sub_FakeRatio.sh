#!/bin/bash


#MRS=( "all" "MR00" "MR01" "MR02" "MR03" )
MRS=( "sync" )
FAKES=( "none" )
#FAKES=( "none" "all" "b" "c" "light" "tau" )
ISOS=( "mixisoM" "mixisoT" )
#ISOS=( "mixisoT" "mixisoVT" "mixisoHT" )
HTBINS=( "all" )
ETABINS=( "all" )
XPOLS=( "iso" "isoid" "isofo3" )
#XPOLS=( "isoid" )
LIDS=( "cut" )
DIRS=( "cut" )

#MRS=( "MR00" "MR01" "MR02" "MR03" )
#FAKES=( "b" "bjet" "c" "cjet" "light" "lightjet" )
#ISOS=( "relIso" )
#HTBINS=( "all" ) 
#ETABINS=( "all" )
#XPOLS=( "isosip" )
#LIDS=( "cut" )
#DIRS=( "cut" )

##CH: here all options that are possible
##note denominator does not depend on choice of ID, so skims are all the same
#MRS=( "all" "MR00" "MR01" "MR02" "MR03" )
#FAKES=( "none" "all" "b" "c" "light" "bjet" "cjet" "lightjet" "tau" )
#ISOS=( "newiso" "pTrel" "miniiso" "relIso" )
#HTBINS=( "all" "0" "200" "400" ) 
#ETABINS=( "all" "0" "09" "12" "15" "09-" "09+" "12-" "12+" "15-" "15+" ) 
#XPOLS=( "iso" "isosip" )
#LPTCUT=( "mu15" "mu5" "10" )
#LIDS=( "mva" "mvanotcut" "mvaandcut" "cut" "cutnotmva" "cutandmva" )
#DIRS=( "cut" "cut" "cut" "cut" "cut" "cut" )



#rm cfg/tmpFiles/*

for mregion in ${MRS[@]}; do
  for fake in ${FAKES[@]}; do
    for iso in ${ISOS[@]}; do
      for htbin in ${HTBINS[@]}; do
        for etabin in ${ETABINS[@]}; do
          for xpol in ${XPOLS[@]}; do
            ii=0
            for lid in ${LIDS[@]}; do

              mr=$mregion
              fs=$fake
              is=$iso
              ht=$htbin
              et=$etabin
              xp=$xpol
              id=$lid
              dr=${DIRS[$ii]}
      
              ## all flavors from every sample -> not good
              #cp cfg/template_FakeRatio.cfg cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|MEASUREMENTREGION|'$mr'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|LEPTONID|'$id'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|LEPTONISO|'$is'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|FAKESOURCE|'$fs'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|EXTRAPOL|'$xp'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|ADDHTBIN|'$ht'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|ADDETABIN|'$et'|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #sed -i 's|SKIMDIR|FRskims_miniiso_sync|' cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg

              #analysis -c cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              #qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatio_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg

              ## electrons
              cp cfg/template_FakeRatioEM.cfg cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|MEASUREMENTREGION|'$mr'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|LEPTONID|'$id'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|LEPTONISO|'$is'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|FAKESOURCE|'$fs'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|EXTRAPOL|'$xp'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|ADDHTBIN|'$ht'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|ADDETABIN|'$et'|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|SKIMDIR|FRskims_miniiso_sync|' cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatioEM_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg

              ## muons
              cp cfg/template_FakeRatioMu5.cfg cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|MEASUREMENTREGION|'$mr'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|LEPTONID|'$id'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|LEPTONISO|'$is'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|FAKESOURCE|'$fs'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|EXTRAPOL|'$xp'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|ADDHTBIN|'$ht'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|ADDETABIN|'$et'|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|SKIMDIR|FRskims_miniiso_sync|' cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatioMu5_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg

              ## we do not want an overlap of QCDMu15 and Mu5 samples, two different lepptcut values
              cp cfg/template_FakeRatioMu15.cfg cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|MEASUREMENTREGION|'$mr'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|LEPTONID|'$id'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|LEPTONISO|'$is'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|FAKESOURCE|'$fs'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|EXTRAPOL|'$xp'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|ADDHTBIN|'$ht'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|ADDETABIN|'$et'|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              sed -i 's|SKIMDIR|FRskims_miniiso_sync|' cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg
              qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatioMu15_${mr}_${id}_${is}_${fs}_${xp}_${ht}_${et}.cfg

              ii=`echo $ii +1 | bc`
            done
          done
        done
      done
    done
  done
done
