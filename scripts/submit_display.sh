#!/bin/bash
source /mnt/t3nfs01/data01/swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh

#cd /mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF
cd /mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/

source setup.sh
cd mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/display

root -l -b cards/tmpFiles/susy3l_data_${var}_${reg}.C

#../scripts/Sub_Display.sh
