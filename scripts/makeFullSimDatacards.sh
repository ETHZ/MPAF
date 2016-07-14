#!/bin/bash

VAR=("T1t4_1200" "T1t4_1500" "T54q_deg" "T6t2W2_600" "T6t2W2_650" "T54qWZ_315" "T54qWZ_325" "T54qWZ_800" "T54qWZ_1000")

for var in ${VAR[@]}; do

    variable=$var

    cp $MPAF/display/cards/susy3l_fullSimDataCards.C $MPAF/display/cards/tmpFiles/susy3l_fullSimDataCards.C
    sed -i 's|SIGSAMPLE|'$variable'|' $MPAF/display/cards/tmpFiles/susy3l_fullSimDataCards.C

    root -l -b $MPAF/display/cards/tmpFiles/susy3l_fullSimDataCards.C

done

