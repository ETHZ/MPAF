#!/bin/bash
 
SIG=( "T1tttt_mGo1200_mChi800" "T1tttt_mGo1500_mChi100" "T6ttWW_mSbot600_mCh425_mChi50" "T6ttWW_mSbot650_mCh150_mChi50" "T5qqqqWZ_mGo1200_mCh1000_mChi800_lep" "T5qqqqWZ_mGo1500_mCh800_mChi100_lep" )

for sig in ${SIG[@]}; do
    signal=$sig

    cp cards/susy3l_74X.C cards/tmpFiles/susy3l_74X.C
    sed -i 's|SIGNAL|'$signal'|' cards/tmpFiles/susy3l_74X.C

    root -l -b cards/tmpFiles/susy3l_74X.C
    #break
done


