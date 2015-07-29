#!/bin/bash


ISOS="mixiso"
MVAS="cut"
SAMPLES=( "DYJetsToLL_M50_HT400to600" )
#SAMPLES=( "DYJetsToLL_M50_HT100to200" "DYJetsToLL_M50_HT200to400" "DYJetsToLL_M50_HT400to600" "DYJetsToLL_M50_HT600toInf" "TTH" "TTJets" "TTWJets" "TTZJets" "WJetsToLNu_HT100to200" "WJetsToLNu_HT200to400" "WJetsToLNu_HT400to600" "WJetsToLNu_HT600toInf" "WZJetsTo3LNu" )

#rm cfg/tmpFiles/*

for sample in ${SAMPLES[@]}; do

  ds=$sample

  cp cfg/template_sideband_Skim.cfg cfg/tmpFiles/sidebandSkim_${ds}.cfg
  sed -i 's|LEPTONID|'$MVAS'|' cfg/tmpFiles/sidebandSkim_${ds}.cfg
  sed -i 's|LEPTONISO|'$ISOS'|' cfg/tmpFiles/sidebandSkim_${ds}.cfg
  sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/sidebandSkim_${ds}.cfg

  #analysis -c $MPAF/cfg/tmpFiles/sidebandSkim_${ds}.cfg
  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/sideband/sidebandSkim_${ds}.out -e $MPAF/workdir/logs/sideband/sidebandSkim_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/sidebandSkim_${ds}.cfg

done
