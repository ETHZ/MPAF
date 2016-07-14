#!/bin/bash

echo -n "" > Limits_T6ttWW_scan.txt

mydir=/mnt/t3nfs01/data01/shome/jhoss/logs

for i in `ls $mydir/*.log`; do

spl=`echo $i | tr '_' ' '`

sig="T6ttWW"
m1=`echo $spl | awk '{print $5}'`
m1=${m1#m}
m2=`echo $spl | awk '{print $6}'`
m2=${m2%.txt.log}
m2=${m2#m}

#echo $m1
#echo $m2

obs=`grep "Observed"    $i | awk '{print $5}'`
exp=`grep "Expected 50" $i | awk '{print $5}'`
d1s=`grep "Expected 16" $i | awk '{print $5}'`
u1s=`grep "Expected 84" $i | awk '{print $5}'`
u2s=`grep "Expected 97" $i | awk '{print $5}'`
d2s=`grep "Expected  2" $i | awk '{print $5}'`

#$sig"\t"
if [[ -n "$exp" ]]; then
    echo -e $m1"\t"$m2"\t"$obs"\t"$exp"\t"$d1s"\t"$u1s"\t"$d2s"\t"$u2s >> Limits_T6ttWW_scan.txt
fi



done
