#!/bin/bash

#cd $MPAF/workdir/datacards/

N=0
for i in `ls *.txt`; do
    
    badCard=`grep "rate		218" $i`

    if [[ -n "$badCard" ]]; then
	#echo $i
	continue
    fi
    

   #if [[ $N -lt 6 ]];then
   #    combine -M Asymptotic $i > ../scanLogs/log_$i & 
   #    N=`echo $N + 1 | bc`
   #else
   #    combine -M Asymptotic $i > ../scanLogs/log_$i
   #    N=0
   #fi

    #bsub -q8nh source submitScan.sh $i
    #qsub -q all.q -N combine -o /shome/mmarionn/cmssw/limits715/src/scanLogs/$i.log -e /shome/mmarionn/cmssw/limits715/src/scanLogs/$i.err /shome/mmarionn/cmssw/limits715/src/shapeCardsScan/submitScan.sh $i
    qsub -q all.q -N combine -o /shome/jhoss/logs/$i.log -e /shome/jhoss/logs/$i.err /shome/jhoss/analysis/CMSSW_7_1_12/src/submitScan.sh $i
done
