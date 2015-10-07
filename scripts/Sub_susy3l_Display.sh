#!/bin/bash


#SRS=( "SR000"  "SR001" "SR002" "SR003" "SR004" "SR005" "SR006" "SR007" "SR008" "SR009" "SR010" "SR011" "SR012" "SR013" "SR014" "SR015" "SR016" "SR017" "SR018" "SR019" "SR020" "SR021" "SR022" "SR023" "SR024" "SR025" "SR026" "SR027" "SR028" "SR029" ) #"SR030"  "SR031"  "SR032"  "SR033"  "SR034"  "SR035"  "SR036"  "SR037"  "SR038"  "SR039"  "SR040"  "SR041"  "SR042"  "SR043"  "SR044"  "SR045"  "SR046"  "SR047"  "SR048"  "SR049"  "SR050"  "SR051"  "SR052"  "SR053" ) # "SR054"  "SR055"  "SR056"  "SR057"  "SR058"  "SR059"  "SR060"  "SR061"  "SR062" "SR063"  "SR064"  "SR065"  "SR066"  "SR067"  "SR068" "SR069" "SR070" "SR071" "SR072" "SR073" "SR074" "SR075" "SR076" "SR077" "SR078" "SR079" "SR080" "SR081"  "SR082" "SR083" "SR084" "SR085" "SR086" "SR087" "SR088" "SR089" "SR090" "SR091" "SR092" "SR093" "SR094"  "SR095"  "SR096" "SR097" "SR098" "SR099" "SR100" "SR101" "SR102" "SR103" "SR104" "SR105" "SR106" "SR107" )

SRS=( "SR000"  "SR001" "SR002" "SR003" "SR004" "SR005" "SR006" "SR007" "SR008" "SR009" "SR010" "SR011" "SR012" "SR013" "SR014" "SR015" "SR016" "SR017" "SR018" "SR019" "SR020" "SR021" "SR022" "SR023" "SR024" "SR025" "SR026" "SR027" "SR028" "SR029" "SR030"  "SR031"  "SR032"  "SR033"  "SR034"  "SR035"  "SR036"  "SR037"  "SR038"  "SR039"  "SR040"  "SR041"  "SR042"  "SR043"  "SR044"  "SR045"  "SR046"  "SR047"  "SR048"  "SR049"  "SR050"  "SR051"  "SR052"  "SR053"  "SR054"  "SR055"  "SR056"  "SR057"  "SR058"  "SR059"  "SR060"  "SR061"  "SR062" "SR063"  "SR064"  "SR065"  "SR066"  "SR067"  "SR068" "SR069" "SR070" "SR071" "SR072" "SR073" "SR074" "SR075" "SR076" "SR077" "SR078" "SR079" "SR080" "SR081"  "SR082" "SR083" "SR084" "SR085" "SR086" "SR087" "SR088" "SR089" "SR090" "SR091" "SR092" "SR093" "SR094"  "SR095"  "SR096" "SR097" "SR098" "SR099" "SR100" "SR101" "SR102" "SR103" "SR104" "SR105" "SR106" "SR107" )

OSSFPAIR=( "on" "off" )

for sr in ${SRS[@]}; do

    for pair in ${OSSFPAIR[@]}; do

        sregion=$sr
        pairstate=$pair

        cp cards/tmpFiles/susy3l_auto.C cards/tmpFiles/susy3l_${sregion}_${pairstate}.C
        sed -i 's|SIGNALREGION|'$sregion'|' cards/tmpFiles/susy3l_${sregion}_${pairstate}.C
        sed -i 's|PAIRSTATE|'$pairstate'|' cards/tmpFiles/susy3l_${sregion}_${pairstate}.C

        root -l -b cards/tmpFiles/susy3l_${sregion}_${pairstate}.C

    done
done
