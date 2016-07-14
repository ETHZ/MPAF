#!/bin/bash

SAMPLES=( 
DoubleEG_Run2016B_PromptReco_v2_runs_273150_275125
DoubleMuon_Run2016B_PromptReco_v2_runs_273150_275125
DYJetsToLL_M10to50_LO
DYJetsToLL_M10to50
DYJetsToLL_M50_LO
DYJetsToLL_M50
GGHZZ4L
MuonEG_Run2016B_PromptReco_v2_runs_273150_275125
SingleElectron_Run2016B_PromptReco_v2_runs_273150_275125
SingleMuon_Run2016B_PromptReco_v2_runs_273150_275125
Tau_Run2016B_PromptReco_v2_runs_273150_274442
Tau_Run2016B_PromptReco_v2_runs_274443_275125
TBarToLeptons_tch_powheg
TBar_tWch
TChiSlepSnu
TGJets
TTGJets
TTHnobb_mWCutfix_ch1
TTHnobb_pow
TTJets_DiLepton
TTJets
TTJets_SingleLeptonFromTbar
TTJets_SingleLeptonFromT
TTLLJets_m1to10
TToLeptons_tch_powheg
TT_pow_ext4
TTTT
T_tWch
TTW_LO
TTWToLNu
TTZ_LO
TTZToLLNuNu
tZq_ll
VHToNonbb
WGToLNuG
WJetsToLNu_LO
WJetsToLNu
WpWpJJ
WWDouble
WWTo2L2Nu
WWW
WWZ
WZTo3LNu_amcatnlo
WZTo3LNu
WZZ
ZGTo2LG
ZZTo4L
ZZZ
)

#SAMPLES=( TTW_LO )

PFXS=( "" ) # "_OS2l" "_fakes" )

cfgFile=skimsusy3l.cfg

rm cfg/tmpFiles/*
rm workdir/logs/logskim*
for ds in ${SAMPLES[@]}; do
    for pfx in "${PFXS[@]}"; do
	era=8011_July5
	if [ "${ds:0:6}" == "Double" ] || [ "${ds:0:6}" == "MuonEG" ] || [ "${ds:0:6}" == "TTW_LO" ] || [ "${ds:0:6}" == "TTZ_LO" ]; then
	    era=8011_July5
	fi
#	echo $ds $era

	cp cfg/$cfgFile cfg/tmpFiles/skim_${ds}${pfx}.cfg
	sed -i 's|PFX|'$pfx'|' cfg/tmpFiles/skim_${ds}${pfx}.cfg
	sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/skim_${ds}${pfx}.cfg
	sed -i 's|ERA|'$era'|' cfg/tmpFiles/skim_${ds}${pfx}.cfg
	
	#qsub -q long.q -N MPAFjob -o $MPAF/workdir/logs/logskim_${ds}${pfx}.out -e $MPAF/workdir/logs/logskim_${ds}${pfx}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/skim_${ds}${pfx}.cfg

    done
done