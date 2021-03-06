#!/bin/bash

sub() {
    cd display
    root -b -l cards/tmpFiles/$1
    cd $MPAF
}

SIGS=( 
  #  "SMS_T1tttt_2J_mGl1200_mLSP800"
  #  "SMS_T1tttt_2J_mGl1500_mLSP100"
  #  "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"
  #  "T5qqqqWWDeg_mGo1000_mCh315_mChi300_dilep"
  #  "T5qqqqWW_mGo1200_mCh1000_mChi800_dilep"
    "T1ttbbWW_mGo1300_mCh300_mChi290"
    "T5qqqqWW_mGo1500_mCh800_mChi100"
    "T6ttWW_mSbot600_mCh425_mChi50"
    "T6ttWW_mSbot650_mCh150_mChi50"
 )


SIGTAGS=( #"T1t412" "T1t415" "T5t4Deg"
   # "T5q410" "T5q412"
    "T1t2b2W2" "T5q415" "T6t264" "T6t261"
 )
#===============================================================================

CATS=(
    "SR1A" "SR2A" "SR3A" "SR4A" "SR5A" "SR6A" "SR7A" "SR8A"
    "SR9A" "SR10A" "SR11A" "SR12A" "SR13A" "SR14A" "SR15A" "SR16A"
    "SR17A" "SR18A" "SR19A" "SR20A" "SR21A" "SR22A" "SR23A" "SR24A"
    "SR25A" "SR26A" "SR27A" "SR28A" "SR29A" "SR30A" "SR31A" "SR32A"
    
    "SR1B" "SR2B" "SR3B" "SR4B" "SR5B" "SR6B" "SR7B" "SR8B"
    "SR9B" "SR10B" "SR11B" "SR12B" "SR13B" "SR14B" "SR15B" "SR16B"
    "SR17B" "SR18B" "SR19B" "SR20B" "SR21B" "SR22B" "SR23B" "SR24B"
    "SR25B" "SR26B"
    
    "SR1C" "SR2C" "SR3C" "SR4C" "SR5C" "SR6C" "SR7C" "SR8C")


JESRare=(
    "1.05" "1.08" "1.05" "1.04" "1.08" "1.04" "1.08" "1.04" 
    "1.05" "1.08" "1.05" "1.04" "1.08" "1.04" "1.08" "1.04" 
    "1.05" "1.08" "1.05" "1.04" "1.08" "1.04" "1.08" "1.04"
    "1.05" "1.08" "1.05" "1.08" "1.05" "1.08" "1.08" "1.08"
    
    "1.03" "1.08" "1.03" "1.08" "1.08" "1.08" "1.03" "1.08" 
    "1.03" "1.08" "1.08" "1.08" "1.03" "1.08" "1.03" "1.08" 
    "1.08" "1.08" "1.03" "1.08" "1.03" "1.08" "1.03" "1.08"
    "1.08" "1.08" 
    
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" )

JEST1t412=( 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.03" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.03" "1.10" "1.03" "1.10" "1.03" "1.10" "1.10"
    
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" 
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.03" 
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.03" "1.05" "1.03"
    "1.05" "1.05" 
    
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05") 

JEST1t415=(
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" 
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" 
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06"
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06"
    
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" 
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" 
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06"
    "1.06" "1.06" 
    
    "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06" "1.06") #6% partout

JEST5t4Deg=(
    "1.05" "1.03" "1.05" "1.03" "1.05" "1.03" "1.05" "1.03" 
    "1.05" "1.03" "1.05" "1.03" "1.05" "1.03" "1.05" "1.05" 
    "1.05" "1.03" "1.05" "1.03" "1.05" "1.03" "1.05" "1.05"
    "1.05" "1.03" "1.05" "1.03" "1.05" "1.03" "1.10" "1.05"
    
    "1.05" "1.10" "1.05" "1.10" "1.10" "1.10" "1.05" "1.10" 
    "1.05" "1.10" "1.10" "1.10" "1.05" "1.10" "1.05" "1.10" 
    "1.10" "1.10" "1.05" "1.10" "1.05" "1.10" "1.05" "1.10"
    "1.10" "1.10" 
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" ) 

JEST5q410=(
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" 
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" 
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15"
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15"
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.10" 
    
    "1.02" "1.02" "1.02" "1.02" "1.02" "1.02" "1.02" "1.02") 

JEST5q412=(
    "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" 
    "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" 
    "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07"
    "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07" "1.07"
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.10" 
    
    "1.20" "1.20" "1.20" "1.20" "1.20" "1.20" "1.20" "1.20")


JEST1ttbbWW=(
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" 
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" 
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08"
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08"
    
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" 
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" 
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08"
    "1.08" "1.08" 
    
    "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08" "1.08") #8% partout


JEST5q415=(
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" 
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" 
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05"
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05"
    
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" 
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" 
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05"
    "1.05" "1.05" 
    
    "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05" "1.05") #8% partout


JEST6t264=(
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.10" 
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10") #8% partout

JEST6t261=(
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" 
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10"
    "1.10" "1.10" 
    
    "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10" "1.10") #8% partout

TTWXsect=(
    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" 
    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" 
    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27"
    "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" "1.27" "1.27"

    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.10" 
    "1.10" "1.27" "1.10" "1.27" "1.10" "1.10" "1.10" "1.27" 
    "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27"
    "1.27" "1.27"
    
    "1.20" "1.20" "1.20" "1.20" "1.20" "1.20" "1.20" "1.20")


TTZXsect=(
    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" 
    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" 
    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27"
    "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" "1.27" "1.27"

    "1.10" "1.10" "1.10" "1.27" "1.10" "1.27" "1.10" "1.10" 
    "1.10" "1.27" "1.10" "1.27" "1.10" "1.10" "1.10" "1.27" 
    "1.10" "1.27" "1.10" "1.27" "1.10" "1.27" "1.10" "1.27"
    "1.27" "1.27"
    
    "1.20" "1.20" "1.20" "1.20" "1.20" "1.20" "1.20" "1.20")



WZBTag=(
    "1.00" "1.00" "1.00" "1.00" "1.00" "1.00" "1.00" "1.00" 
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" 
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15"
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15"
    
    "1.00" "1.00" "1.00" "1.00" "1.00" "1.00" "1.15" "1.15" 
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" 
    "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15"
    "1.15" "1.15" 
    
    "1.00" "1.00" "1.15" "1.15" "1.15" "1.15" "1.15" "1.15")



LUMIS=( "10000" "3000" )

WZLUMIS=( "1.08" "1.15" )


rm display/cards/tmpFiles/*

NL=0
while [[ $NL -lt ${#LUMIS[*]} ]]; do
    
    lumi=${LUMIS[$NL]}
    wzlumi=${WZLUMIS[$NL]}

    NSR=0
    while [[ $NSR -lt ${#CATS[*]} ]]; do

	sr=${CATS[$NSR]}
	jesR=${JESRare[$NSR]}
	
	ttwXS=${TTWXsect[$NSR]}
	ttzXS=${TTZXsect[$NSR]}
	wzbtag=${WZBTag[$NSR]}

	N=0
	while [[ $N -lt ${#SIGS[*]} ]]; do

	    sig=${SIGS[$N]}
	    tag=${SIGTAGS[$N]}
	    
	    jesSig=""
	    if [ "$tag"=="T1t412" ]; then
		jesSig=${JEST1t412[$N]}
	    elif [ "$tag"=="T1t415" ]; then
		jesSig=${JEST1t415[$N]}
	    elif [ "$tag"=="T5t4Deg" ]; then
		jesSig=${JEST5t4Deg[$N]}
	    elif [ "$tag"=="T5q410" ]; then
		jesSig=${JEST5q410[$N]}
	    elif [ "$tag"=="T5q412" ]; then
		jesSig=${JEST5q412[$N]}

	    elif [ "$tag"=="T1t2b2W2" ]; then
		jesSig=${JEST1ttbbWW[$N]}
	    elif [ "$tag"=="T5q415" ]; then
		jesSig=${JEST5q415[$N]}
	    elif [ "$tag"=="T6t264" ]; then
		jesSig=${JEST6t264[$N]}
	    elif [ "$tag"=="T6t261" ]; then
		jesSig=${JEST6t261[$N]}


	    fi
	    jes="${jesR}:${jesR}:${jesSig}"

	    cp display/cards/ssdl2015card_template.C display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|LUMTAG|'$lumi'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	     

	    sed -i 's|CATTAG|'$sr'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	     
	    sed -i 's|JESTAG|'$jes'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|TTWTAILTAG|'$ttwXS'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|TTZTAILTAG|'$ttzXS'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|WZBTAG|'$wzbtag'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|WZLUMITAG|'$wzlumi'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	     
	    
	    sed -i 's|SIGNAME|'$sig'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|SIGTAG|'$tag'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C
	    sed -i 's|SIGTAG|'$tag'|' display/cards/tmpFiles/dataCardProd_${sr}_${tag}_${lumi}.C #double for the card name

	    
	    #echo ${sr} ${tag} ${lumi}
	    N=`echo $N +1 | bc`
	  #  continue
	    NJ=0
	    if [[ $NJ -lt 4 ]]; then
		sub dataCardProd_${sr}_${tag}_${lumi}.C &
		NJ=`echo $NJ +1 | bc`
	    else
		sub dataCardProd_${sr}_${tag}_${lumi}.C
		NJ=0
	    fi
	    
	done
	NSR=`echo $NSR +1 | bc`
    done
    NL=`echo $NL +1 | bc`
done
