#!/bin/bash

mainFile=${MPAF}/workdir/stats/SSDL2015/merged_2fb_Bkg.dat

## first merge backgrounds
python ${MPAF}/scripts/scanScripts/mergeBkgs.py ${mainFile} ${MPAF}/workdir/stats/SSDL2015/ssdlBkg_

## merge signals and backgrounds
for i in `ls $MPAF/workdir/stats/SSDL2015/ssdlScan_*.dat`; do

    red=${i#$MPAF/workdir/stats/SSDL2015/ssdlScan_}
    echo $red
    python ${MPAF}/scripts/scanScripts/addSample.py $mainFile $i $MPAF/workdir/stats/SSDL2015/merged_2fb_$red


done

### merge root files
#files="vector<string> tks; tks.push_back(\"$MPAF/workdir/root/SSDL2015/merged_2fb.root\");"
#for i in `ls $MPAF/workdir/root/SSDL2015/ssdlScan_*.root`; do
#    files=$files" tks.push_back(\"$i\");"
#done
#
#echo $files




#root -b -l  <<EOF
#$files
#.L mergeScanRootFiles.C
#mergeScanRootFiles(files,"$MPAF/workdir/root/SSDL2015/mergedssdlScanV2.root");
#.q
#EOF
#hadd -f $MPAF/workdir/root/SSDL2015/mergedssdlScan.root $MPAF/workdir/root/SSDL2015/ssdl2fb_Bkg.root $MPAF/workdir/root/SSDL2015/ssdlScan-*.root

