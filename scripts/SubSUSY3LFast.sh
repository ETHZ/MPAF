#!/bin/bash

cfgFile=3l_scan_fastSim.cfg

rm cfg/tmpFiles/skimfast*
rm cfg/tmpFiles/3l_scanSig*
rm workdir/logs/logskimfast*
rm workdir/logs/logfast*
for ds in `ls /pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/tmpScan/T1ttttFiles/`; do
    #for pfx in "${PFXS[@]}"; do
    ds=${ds%.root}

	cp cfg/$cfgFile cfg/tmpFiles/3l_scanSig_${ds}.cfg
	sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/3l_scanSig_${ds}.cfg
	
	qsub -q all.q -N MPAFjob$ds -o $MPAF/workdir/logs/loggfast_${ds}.out -e $MPAF/workdir/logs/logfast_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanSig_${ds}.cfg
#	break
   # done
done