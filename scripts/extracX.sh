#!/bin/bash/

#for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-12-04-21-54-00/*          #T1tttt
#for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-02-02-11-22-00/*.root     #T6ttWW
for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-03-04-18-49-00/*.root      #T5qqqqVV
    do
        fdir=$(dirname "$file")
        fname=$(basename "$file")
        echo "$fdir"
        echo "$fname"
        
        #IFS='-' read -ra MASSES <<< "$fname"  
        IFS='_' read -ra MASSES <<< "$fname"  
        M1="${MASSES[1]}"
        M2="${MASSES[2]}"
        echo "$M1"
        echo "$M2"
        root -b -q -l "PrintXfactor.C(\"$fdir\",\"$fname\",\"$M1\",\"$M2\")"
        
    done


