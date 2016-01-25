#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi

#DATASETS=("DoubleEG_Run2015C_Oct05_runs_254231_254914" "DoubleEG_Run2015D_Oct05_runs_256630_258158" "DoubleEG_Run2015D_PromptV4_runs_258159_260627" "DoubleMuon_Run2015C_Oct05_runs_254231_254914" "DoubleMuon_Run2015D_Oct05_runs_256630_258158" "DoubleMuon_Run2015D_PromptV4_runs_258159_260627" "MuonEG_Run2015C_Oct05_runs_254231_254914" "MuonEG_Run2015D_Oct05_runs_256630_258158" "MuonEG_Run2015D_PromptV4_runs_258159_260627" "GGHZZ4L" "TGJets" "TTGJets" "TTHnobb" "TTLLJets_m1to10" "TT_pow" "TTTT" "TTWToLNu" "TTZToLLNuNu" "tZq_ll" "VHToNonbb" "WGToLNuG" "WpWpJJ" "WWDouble" "WWZ" "WZTo3LNu" "WZZ" "ZGTo2LG" "ZZTo4L" "ZZZ" "DYJetsToLL_M10to50" "DYJetsToLL_M50" )

#DIRS=("/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-20-14-10-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-20-14-10-00/" )

## those need JES uncertainty turned off
#DATASETS=( "DYJetsToLL_M10to50" "DYJetsToLL_M50" )
#DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-20-14-10-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-20-14-10-00/" )

## resubmit bkg
#DATASETS=("GGHZZ4L" "TGJets" "TTGJets" "TTHnobb" "TTLLJets_m1to10" "TT_pow" "TTTT" "TTWToLNu" "TTZToLLNuNu" "tZq_ll" "VHToNonbb" "WGToLNuG" "WpWpJJ" "WWDouble" "WWZ" "WZTo3LNu" "WZZ" "ZGTo2LG" "ZZTo4L" "ZZZ" )
#
#DIRS=("/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" )


## resubmit DYM50
#DATASETS=( "DYJetsToLL_M10to50" )
#DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-20-14-10-00/" )

## resubmit data
DATASETS=("DoubleEG_Run2015C_Oct05_runs_254231_254914" "DoubleEG_Run2015D_Oct05_runs_256630_258158" "DoubleEG_Run2015D_PromptV4_runs_258159_260627" "DoubleMuon_Run2015C_Oct05_runs_254231_254914" "DoubleMuon_Run2015D_Oct05_runs_256630_258158" "DoubleMuon_Run2015D_PromptV4_runs_258159_260627" "MuonEG_Run2015C_Oct05_runs_254231_254914" "MuonEG_Run2015D_Oct05_runs_256630_258158" "MuonEG_Run2015D_PromptV4_runs_258159_260627" )
DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00/" )


N=0

for ds in ${DATASETS[@]}; do

	cp $MPAF/cfg/ssdlBkg_template_file.cfg $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	dir=${DIRS[$N]}

	sed -i 's|FILE|'$ds'|' $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg
	sed -i 's|PATH|'$dir'|' $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SSDL2015/ssdlBkg_${ds}.out -e $MPAF/workdir/logs/SSDL2015/ssdlBkg_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg
	#bsub -q 8nh source submitLxbatch.sh $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	N=`echo $N + 1 | bc`
  
done



