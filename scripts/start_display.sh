#!/bin/bash
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_display.out -e $MPAF/workdir/logs/susy3l/susy3l_display.err $MPAF/scripts/submit_display.sh
qsub -q all.q -N MPAFjob -e $MPAF/workdir/logs/susy3l/susy3l_display.err $MPAF/scripts/submit_display.sh
