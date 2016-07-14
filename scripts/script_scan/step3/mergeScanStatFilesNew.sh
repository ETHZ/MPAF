#!/bin/bash

mainFile=${MPAF}/workdir/stats/SUSY3L/merged_v2_4fb_Bkg.dat

## first merge backgrounds
python ${MPAF}/scripts/script_scan/step3/mergeBkgs.py ${mainFile} ${MPAF}/workdir/stats/SUSY3L/3l_v2_scanBkg_

## merge signals and backgrounds
for i in `ls $MPAF/workdir/stats/SUSY3L/3l_scanSig_*.dat`; do

    red=${i#$MPAF/workdir/stats/SUSY3L/3l_scanSig_}
    echo $red
    python ${MPAF}/scripts/script_scan/step3/addSample.py $mainFile $i $MPAF/workdir/stats/SUSY3L/merged_v2_4fb_$red

done

### merge root files
files="vector<string> tks; tks.push_back(\"$MPAF/workdir/root/SUSY3L/merged_v2_4fb_Bkg.root\");"
for i in `ls $MPAF/workdir/root/SUSY3L/3l_scanSig_*.root`; do
    files=$files" tks.push_back(\"$i\");"
done

#past string to next step
echo $files




