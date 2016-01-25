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

    #mGluinoMax=`python splitLineScan.py $file | awk '{print $1}' `
    #mGluinoMin=`python splitLineScan.py $file | awk '{print $1}' `

    #mLSPMax=`python splitLineScan.py $file | awk '{print $1}' `
    #mLSPMin=`python splitLineScan.py $file | awk '{print $1}' `

    while read line; do

		mass=$line
		
		if [[ -e $MPAF/cfg/tmpFiles/ssdlScan_${mass}.cfg ]]; then
		    continue
		fi

		dec=`python splitLineScan.py $path $mass`
		if [[ $dec == 0 ]]; then
		    continue
		fi
		#break


		cp $MPAF/cfg/ssdlScan_template_file.cfg $MPAF/cfg/tmpFiles/ssdlScan_${mass}.cfg

		sed -i 's|MASSBENCH|'$mass'|' $MPAF/cfg/tmpFiles/ssdlScan_${mass}.cfg
		sed -i 's|FILE|'$file'|' $MPAF/cfg/tmpFiles/ssdlScan_${mass}.cfg
		sed -i 's|PATH|'$path'|' $MPAF/cfg/tmpFiles/ssdlScan_${mass}.cfg
		#bsub -q 8nh source submitLxbatch.sh cfg/tmpFiles/ssdlScan$mass.cfg


    done < massT1ttt.txt

N=`echo $N + 1 | bc`

#break

done < fileNamesV3
