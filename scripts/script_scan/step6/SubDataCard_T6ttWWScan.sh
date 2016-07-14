#!/bin/bash

sub() {
    echo $1
    cd $MPAF/display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

#===============================================================================
rm $MPAF/display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
for i in `ls $MPAF/workdir/stats/SUSY3L/3l_scanSig_T6ttWW_*_*.dat`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

    tmp=${i#"$MAPF/workdir/stats/SUSY3L/3l_scanSig_T6ttWW"}
    mass=${tmp%".dat"}

    bench=`echo $mass | tr '_' ' '`

    m1=`echo $bench | awk '{print $4}'`
    m2=`echo $bench | awk '{print $5}'`

    mass="_"$m1"_"$m2
    bench="_m"$m1"_m"$m2

    cp $MPAF/display/cards/susy3lScanCombine.C $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

    sed -i 's|MASS|'$mass'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
    sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
    #sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub susy3l_scanSig${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  susy3l_scanSig${bench}.C
	NJ=0
    fi
    #break
done
