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
#NUMBER=( 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 )
#NUMBER=( 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 )
NUMBER=(1)

for nr in ${NUMBER[@]}; do

    for i in `ls $MPAF/workdir/stats/SUSY3L/3l_scanSig_T5tttt_*_*.dat`; do
    #while [[ $N -lt ${#SIGS[*]} ]]; do

        tmp=${i#"$MPAF/workdir/stats/SUSY3L/3l_scanSig_T5tttt"}
        mass=${tmp%".dat"}


        bench=`echo $mass | tr '_' ' '`
        #echo $bench

        m1=`echo $bench | awk '{print $1}'`
        m2=`echo $bench | awk '{print $2}'`

        mass="_"$m1"_"$m2
        bench="_m"$m1"_m"$m2
        #echo $bench
    
        cp $MPAF/display/cards/susy3lScanCombine.C $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

        sed -i 's|NUMBER|'$nr'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
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
    sleep 10
    mkdir -p $MPAF/workdir/datacards/SR$nr/
    mv $MPAF/workdir/datacards/ra7_* $MPAF/workdir/datacards/SR$nr/
done
