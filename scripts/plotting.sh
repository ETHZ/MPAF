#!/bin/bash

VAR=("njets" "nbjets" "met" "ht" "pt1" "pt2" "pt3" "srs" "flavor") # "mt") # "el_multi" "mu_multi" "lep_multi")
REG=("OffZBaseline" " OnZBaseline" )
#REG=(" OnZBaseline" )
#VAR=("ftype")
#VAR=("njets")


for reg in ${REG[@]}; do
    region=$reg
    for var in ${VAR[@]}; do

        variable=$var

        cp cards/susy3l_tt_closure.C cards/tmpFiles/susy3l_tt_closure.C
        sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l_tt_closure.C
        sed -i 's|REGION|'$region'|' cards/tmpFiles/susy3l_tt_closure.C

        root -l -b cards/tmpFiles/susy3l_tt_closure.C
    done
done

