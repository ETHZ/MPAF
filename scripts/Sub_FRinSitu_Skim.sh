#!/bin/bash


ISOS="mixiso"
MVAS="cut"
SAMPLES=( "TTJets" )
#SAMPLES=( "DYJetsToLL_M50_HT100to200" "DYJetsToLL_M50_HT200to400" "DYJetsToLL_M50_HT400to600" "DYJetsToLL_M50_HT600toInf" "TTH" "TTJets" "TTWJets" "TTZJets" "WJetsToLNu_HT100to200" "WJetsToLNu_HT200to400" "WJetsToLNu_HT400to600" "WJetsToLNu_HT600toInf" "WZJetsTo3LNu" )

#rm cfg/tmpFiles/*

for sample in ${SAMPLES[@]}; do

  ds=$sample

  cp cfg/template_FRinSitu_Skim.cfg cfg/tmpFiles/FRinSituSkim_${ds}.cfg
  sed -i 's|LEPTONID|'$MVAS'|' cfg/tmpFiles/FRinSituSkim_${ds}.cfg
  sed -i 's|LEPTONISO|'$ISOS'|' cfg/tmpFiles/FRinSituSkim_${ds}.cfg
  sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/FRinSituSkim_${ds}.cfg

  #analysis -c $MPAF/cfg/tmpFiles/FRinSituSkim_${ds}.cfg
  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FRinSitu/FRinSituSkim_${ds}.out -e $MPAF/workdir/logs/FRinSitu/FRinSituSkim_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FRinSituSkim_${ds}.cfg

done
