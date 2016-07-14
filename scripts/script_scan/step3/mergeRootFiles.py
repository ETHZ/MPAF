import glob
import os

#command = "hadd /mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/merged_2fb_Bkg.root "
#arr = glob.glob("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg*")
command = "hadd /mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/workdir/root/SUSY3L/merged_v2_2fb_Bkg.root "
arr = glob.glob("/mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/workdir/root/SUSY3L/3l_v2_scanBkg*")

for i in range(len(arr)):
    command += arr[i]
    command += " " 

os.system(command)




