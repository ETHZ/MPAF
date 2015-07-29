#!/bin/bash


ISOS="miniiso"
MVAS="cut"
SAMPLES=( "QCD_Mu15" "QCD_Pt30to50_Mu5" "QCD_Pt50to80_Mu5" "QCD_Pt80to120_Mu5" "QCD_Pt20to30_EMEnriched" "QCD_Pt30to80_EMEnriched" "QCD_Pt80to170_EMEnriched" "QCD_Pt20to30_bcToE" "QCD_Pt30to80_bcToE" "QCD_Pt80to170_bcToE" "QCD_Pt170toInf_bcToE" "TTJets" )

#MVAS="mva"
#SAMPLES=( "DYJetsToLL_M50" "DYJetsToLL_M50_HT100to200" "DYJetsToLL_M50_HT200to400" "DYJetsToLL_M50_HT400to600" "DYJetsToLL_M50_HT600toInf" "TTJets" "WJetsToLNu_HT100to200" "WJetsToLNu_HT200to400" "WJetsToLNu_HT400to600" "WJetsToLNu_HT600toInf" "TTWJets" "TTZJets" "WZJetsTo3LNu" "TBarToLeptons_sch" "TBarToLeptons_tch" "TBar_tWch" "T_tWch" "TToLeptons_sch" "TToLeptons_tch" )

#rm cfg/tmpFiles/*

for sample in ${SAMPLES[@]}; do

  ds=$sample

  cp cfg/template_FakeRatio_Skim.cfg cfg/tmpFiles/FakeRatioSkim_${ds}.cfg
  sed -i 's|LEPTONID|'$MVAS'|' cfg/tmpFiles/FakeRatioSkim_${ds}.cfg
  sed -i 's|LEPTONISO|'$ISOS'|' cfg/tmpFiles/FakeRatioSkim_${ds}.cfg
  sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/FakeRatioSkim_${ds}.cfg

  #analysis -c $MPAF/cfg/tmpFiles/FakeRatioSkim_${ds}.cfg
  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatioSkim_${ds}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatioSkim_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatioSkim_${ds}.cfg

done
