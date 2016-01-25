#!/bin/bash

mainFile=$MPAF/workdir/stats/SSDL2015/ssdl2fb_Bkg.dat

for i in `ls $MPAF/workdir/stats/SSDL2015/ssdlScan-*.dat`; do

    red=${i#$MPAF/workdir/stats/SSDL2015/}
    echo $red
    python addSample.py $mainFile $i $MPAF/workdir/stats/SSDL2015/merged$red


done


files="vector<string> tks; tks.push_back(\"$MPAF/workdir/root/SSDL2015/mergedssdlScan.root\");"
for i in `ls $MPAF/workdir/root/SSDL2015/ssdlScan-*.root`; do
    files=$files" tks.push_back(\"$i\");"
done

echo $files

#root -b -l  <<EOF
#$files
#.L mergeScanRootFiles.C
#mergeScanRootFiles(files,"$MPAF/workdir/root/SSDL2015/mergedssdlScanV2.root");
#.q
#EOF
#hadd -f $MPAF/workdir/root/SSDL2015/mergedssdlScan.root $MPAF/workdir/root/SSDL2015/ssdl2fb_Bkg.root $MPAF/workdir/root/SSDL2015/ssdlScan-*.root

