#!/bin/bash

VAR=("njets" "nbjets" "met" "ht" "lep" "zpeak" "zpt" "mt" "mt2" "pt1" "pt2" "pt3" "mll" "muonsip" "muoniso" "muondz" "muondxy" "muonptrel" "muonptratio"  "elsip" "eliso" "eldz" "eldxy" "elptrel" "elptratio")


for var in ${VAR[@]}; do

    variable=$var

    cp cards/susy3l_data_25ns_auto.C cards/tmpFiles/susy3l_data_25ns.C
    sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l_data_25ns.C

    root -l -b cards/tmpFiles/susy3l_data_25ns.C

done

