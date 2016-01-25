#!/bin/bash

rm $MPAF/workdir/logs/FakeRatio/FakeRatioSkim.out
rm $MPAF/workdir/logs/FakeRatio/FakeRatioSkim.err
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatioSkim.out -e $MPAF/workdir/logs/FakeRatio/FakeRatioSkim.err $MPAF/scripts/submit.sh $MPAF/cfg/FakeRatioSkim.cfg

#rm $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu.out
#rm $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu.err
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu.err $MPAF/scripts/submit.sh $MPAF/cfg/FakeRatio2015Bmu.cfg
#
#rm $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel.out
#rm $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel.err
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel.err $MPAF/scripts/submit.sh $MPAF/cfg/FakeRatio2015Bel.cfg


