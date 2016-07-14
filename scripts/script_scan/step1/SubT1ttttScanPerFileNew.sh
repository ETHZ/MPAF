#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi

#root -b -l getMassBenchmarks.C <<EOF
#.q
#EOF

N=0
while read fileLine; do

    if [[ "${fileLine:0:1}" == "#" ]]; then
	continue
    fi

    path=`echo $fileLine | awk '{print $1}'`
    file=`echo $fileLine | awk '{print $2}'`

    #echo $path
	#echo $file

	cp $MPAF/cfg/3l_scan.cfg $MPAF/cfg/tmpFiles/3l_scanSig_${file}.cfg

	sed -i 's|FILE|'$file'|' $MPAF/cfg/tmpFiles/3l_scanSig_${file}.cfg
	sed -i 's|PATH|'$path'|' $MPAF/cfg/tmpFiles/3l_scanSig_${file}.cfg
	sed -i 's|SIMFLAG|1|' $MPAF/cfg/tmpFiles/3l_scanSig_${file}.cfg

    #analysis -c $MPAF/cfg/tmpFiles/3l_scanSig_${file}.cfg
	qsub -q all.q -N MPAFjob $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanSig_${file}.cfg

	N=`echo $N + 1 | bc`
    #break

#CHANGE depending on scan
done < fileNamesT1tttt 
