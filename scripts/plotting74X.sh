#!/bin/bash

#VAR=( "njets" "nbjets" "met" "ht" "srs" ) # "mt" "pt1" "pt2" "pt3" "srs" )
VAR=( "srs" )
#REG=( "OffZBaseline" "OnZBaseline")
REG=( "OnZBaseline")
#REG=( "WZCR" "FakeCR" )
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

        cp cards/susy3l_data74X.C cards/tmpFiles/susy3l_data74X.C
        sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l_data74X.C
        sed -i 's|REGION|'$region'|' cards/tmpFiles/susy3l_data74X.C

        root -l -b cards/tmpFiles/susy3l_data74X.C
    done

done

