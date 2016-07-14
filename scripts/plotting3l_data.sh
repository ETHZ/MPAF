#!/bin/bash

VAR=( "njets" "nbjets" "met" "ht" "mt" "pt1" "pt2" "pt3" "srs" "flavor" "mu_multi" "el_multi" "lep_multi" )
#VAR=( "flavor" )
#VAR=( "srs" )
REG=( "OffZBaseline" "OnZBaseline")
#REG=( "WZCR" "FakeCR" )
#REG=(  "OffZBaseline" "OnZBaseline" "WZCR" "FakeCR" )
REG=(  "OffZBaseline" "OnZBaseline" ) # "WZCR" "FakeCR" )
#REG=( "WZCR" )
 #"lep1dxy" "lep1dz" "lep1sip" "lep2dxy" "lep2dz" "lep2sip" "lep3dxy" "lep3dz" "lep3sip" ) #"flavor" "mt") # "el_multi" "mu_multi" "lep_multi")
#VAR=("flavor") #"lep1dxy" "lep1dz" "lep1sip" "lep2dxy" "lep2dz" "lep2sip" "lep3dxy" "lep3dz" "lep3sip" ) #"flavor" "mt") # "el_multi" "mu_multi" "lep_multi")
#VAR=("ftype")
#VAR=("srs")
#VAR=("lep1dxy" "lep1dz" "lep1sip" "lep2dxy" "lep2dz" "lep2sip" "lep3dxy" "lep3dz" "lep3sip" ) # "srs" "flavor" "mt") # "el_multi" "mu_multi" "lep_multi")
#VAR=("lep1sip" "lep2sip" "lep3sip" ) # "srs" "flavor" "mt") # "el_multi" "mu_multi" "lep_multi")

for reg in ${REG[@]}; do
    region=$reg
    for var in ${VAR[@]}; do

        variable=$var

        cp cards/susy3l_data.C cards/tmpFiles/susy3l_data_${var}_${reg}.C
        sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l_data_${var}_${reg}.C
        sed -i 's|REGION|'$region'|' cards/tmpFiles/susy3l_data_${var}_${reg}.C
	
        root -l -b cards/tmpFiles/susy3l_data_${var}_${reg}.C

	#qsub -q long.q -N MPAFPlot_${var}_${reg} -o $MPAF/workdir/logs/SUSY3l/susy3l_data_${var}_${reg}.out -e $MPAF/workdir/logs/SUSY3l/susy3l_data_${var}_${reg}.err $MPAF/scripts/submit_display.sh cards/tmpFiles/susy3l_data_${var}_${reg}.C


	#qsub

    done

done

