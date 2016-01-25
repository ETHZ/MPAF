#!/bin/bash

sub() {
    echo $1
    cd display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

#===============================================================================
rm display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
for i in `ls $MPAF/workdir/stats/SSDL2015/ssdlScan_T1tttt-*-*-.dat`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

    tmp=${i#"/shome/cheidegg/d/MPAF/workdir/stats/SSDL2015/ssdlScan_T1tttt-"}
    mass=${tmp%"-.dat"}
    bench=`echo $mass | tr "-" "_"`
	echo $bench
    
    cp display/cards/ssdlScan_template_new.C display/cards/tmpFilesShape/ssdlScan_${bench}.C

    sed -i 's|MASS|'$mass'|' display/cards/tmpFilesShape/ssdlScan_${bench}.C
    sed -i 's|BENCH|'$bench'|' display/cards/tmpFilesShape/ssdlScan_${bench}.C
    sed -i 's|BENCH|'$bench'|' display/cards/tmpFilesShape/ssdlScan_${bench}.C

    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub ssdlScan_${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  ssdlScan_${bench}.C
	NJ=0
    fi
    
done
