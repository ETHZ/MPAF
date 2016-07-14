#!/bin/bash

ANTYPE=$1
SIGNAME=$2
SAMPLELIST=$3
SIGNALSAMPLELIST=$4

TEMPLATEMPAF=$5
TEMPLATEDISPLAY=$6

SIGFILELOC=$7


echo " ====== Configuration ===== "
echo "analysis      : $ANTYPE"
echo "signal        : $SIGNAME"
echo "list bkgs     : $SAMPLELIST"
echo "list signal   : $SIGNALSAMPLELIST"
echo "template MPAF : $TEMPLATEMPAF"
echo "template card : $TEMPLATEDISPLAY"
echo "location      : $SIGFILELOC"


#step 0
#reprocess=0
#if [[ $reprocess == 1 ]]; then
#    rm $MPAF/workdir/stats/${ANTYPE}/*
#    rm $MPAF/workdir/stats/${ANTYPE}/*
#fi

#step 1
source SubScanPerFile.sh $TEMPLATEMPAF $ANTYPE "" $SIGNAME $SAMPLELIST
#exit
#step 2
if [[ ! -e $MPAF/workdir/database/histoScan$SIGNAME.root ]]; then
root -b -l <<EOF
.L getTH3Histo.C+
getTH3Histo("$SIGNALSAMPLELIST","$MPAF/workdir/database/histoScan$SIGNAME.root")
.q
EOF
fi
if [[ ! -e mass$SIGNAME.txt ]]; then
    root -b -l <<EOF
.L getMassBenchmarks.C+
#getMassBenchmarks("$SIGNALSAMPLELIST","mass$SIGNAME.txt")
.q
EOF
fi

for i in `ls -d /pnfs/psi.ch/cms/trivcat/store/user/$SIGFILELOC/*$SIGNAME*`; do echo $i $SIGNAME  ; done > fileNames
source SubScanPerFile.sh $TEMPLATEMPAF $ANTYPE mass${SIGNAME}.txt ${SIGNAME} fileNames

tmp=`qstat`
while [ "$tmp" != "" ]; do
    tmp=`qstat`
    sleep 5m
done

#step 3
FSTATNAME=`ls $MPAF/workdir/stats/${ANTYPE}/ | grep -v ${SIGNAME} | tail -1`
source mergeScanStatFiles.sh $ANTYPE $FSTATNAME $SIGNAME #> tmp

line=`cat tmp | grep tks`
echo $line
cp mergeScanRootFilesTemplate.C mergeScanRootFiles${ANTYPE}${SIGNAME}.C
sed -i 's|PLACEHOLDER|'"${line}"'|' mergeScanRootFiles${ANTYPE}${SIGNAME}.C
#sed -i 's|ANTYPE|'${ANTYPE}'|' mergeScanRootFiles${ANTYPE}${SIGNAME}.C
#sed -i 's|SIGNAME|'${SIGNAME}'|' mergeScanRootFiles${ANTYPE}${SIGNAME}.C

root -b -l <<EOF
.L mergeScanRootFiles${ANTYPE}${SIGNAME}.C+
mergeScanRootFiles("$MPAF/workdir/root/${ANTYPE}/mergedFile${SIGNAME}.root")
.qqqqqqqqqq
EOF

#step 4, datacard production
source SubDataCardScan.sh $TEMPLATEDISPLAY $ANTYPE $SIGNAME
cd $MPAF/scripts
