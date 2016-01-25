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

    echo $path
	echo $file

	cp $MPAF/cfg/ssdlScan_template_file.cfg $MPAF/cfg/tmpFiles/ssdlScan_${file}.cfg

	sed -i 's|FILE|'$file'|' $MPAF/cfg/tmpFiles/ssdlScan_${file}.cfg
	sed -i 's|PATH|'$path'|' $MPAF/cfg/tmpFiles/ssdlScan_${file}.cfg

    analysis -c $MPAF/cfg/tmpFiles/ssdlScan_${file}.cfg
	#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SSDL2015/ssdlScan_${file}.out -e $MPAF/workdir/logs/SSDL2015/ssdlScan_${file}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/ssdlScan_${file}.cfg
	#bsub -q 8nh source submitLxbatch.sh cfg/tmpFiles/ssdlScan$mass.cfg

	N=`echo $N + 1 | bc`

#break

done < fileNamesV1
