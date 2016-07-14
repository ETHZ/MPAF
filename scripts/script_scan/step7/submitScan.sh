#!/bin/bash

source $VO_CMS_SW_DIR/cmsset_default.sh
cd /shome/jhoss/analysis/CMSSW_7_1_12/src/datacards
eval `scramv1 runtime -sh`
combine -M Asymptotic $1 -n $1
