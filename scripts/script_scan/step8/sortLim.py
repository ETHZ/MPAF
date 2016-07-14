import ROOT
import numpy as np
from os import path
import os.path
#load logon file
if path.exists('/mnt/t3nfs01/data01/shome/jhoss/rootlogon.C'):
    ROOT.gROOT.Macro('/mnt/t3nfs01/data01/shome/jhoss/rootlogon.C')  # Run ROOT logon script

ROOT.squareStyle.SetOptStat(0)
ROOT.squareStyle.SetOptFit(0)

ROOT.squareStyle.SetCanvasDefW(690)
ROOT.squareStyle.SetPadRightMargin(0.20)

c1 = ROOT.TCanvas("c1", "c1")
xbins=58
xmin=600
xmax=2000
ybins=82
ymin=0
ymax=2000
map = ROOT.TH2F("map", "", xbins,xmin,xmax,ybins,ymin,ymax)

#---------------------------------------------------

path = '/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/scripts/script_scan/step8/LimitsPerSR_T5ttttdeg.txt'
with open(path,'r') as inputfile:
    arr=[]
    row=[]
    first = True
    m1_old=-1
    m2_old=-1
    for line in inputfile:
        if line.startswith('#'):
            continue
        m1 = float(line.split()[0])
        m2 = float(line.split()[1])
        sr = float(line.split()[2])
        if len(line.split())==4:
            exp = float(line.split()[3])
            if exp > 99999:
                exp=99999
        else:
            exp = 99999
       
        if(not m1==m1_old or not m2==m2_old):
            if not first:
                row=sorted(row)
                row.append((m1_old, m2_old))
                arr.append(row)
                row=[]
            m1_old=m1         
            m2_old=m2   
            row.append((exp, sr))
            if first:
                first=False
        else:
            row.append((exp, sr))

    row=sorted(row)
    row.append((m1_old, m2_old))
    arr.append(row)
        
inputfile.close()

#print arr




#map.SetBinContent(10,10,100)

#map.Draw("COLZ")
xaxis = map.GetXaxis();
yaxis = map.GetYaxis();

for n in range(len(arr)):
    binx = xaxis.FindBin(arr[n][30][0]);
    biny = yaxis.FindBin(arr[n][30][1]);
    map.SetBinContent(binx,biny,arr[n][0][1])



map.Draw("COLZ")
map.Draw("TEXT SAME")
map.GetXaxis().SetTitle("m_{#tilde{g}} [GeV]")
map.GetYaxis().SetTitle("m_{#tilde{#chi}_{1}^{0}} [GeV]")
map.GetZaxis().SetTitle("most sensitive signal region number")

ROOT.gPad.Update()
c1.Update()


#-------------------------------------------------------
c2 = ROOT.TCanvas("c2", "c2")

path=[[800,0],[800,100],[800,200],[800,300],[800,400],[800,500],[800,600]]
#path=[[700,0],[700,100],[700,200],[700,300],[700,400],[700,500]]
#path=[[600,0],[600,100],[600,200],[600,300],[600,400]]

histo = ROOT.TH1F("histo","",len(path)*4,0,len(path)*4)
histo_xaxis = histo.GetXaxis();
histo2 = ROOT.TH1F("histo2","",len(path)*4,0,len(path)*4)
histo2_xaxis = histo2.GetXaxis();
histo3 = ROOT.TH1F("histo3","",len(path)*4,0,len(path)*4)
histo3_xaxis = histo3.GetXaxis();

histo.SetLineColor(4)
histo.SetFillStyle(1001)
histo.SetFillColor(4)
histo2.SetLineColor(ROOT.kBlue-7)
histo2.SetFillStyle(1001)
histo2.SetFillColor(ROOT.kBlue-7)
histo3.SetLineColor(ROOT.kBlue-10)
histo3.SetFillStyle(1001)
histo3.SetFillColor(ROOT.kBlue-10)

for i in range(len(path)):
    m1=path[i][0]
    m2=path[i][1]
    for n in range(len(arr)):
        if(arr[n][30][0]==m1 and arr[n][30][1]==m2):
            histo.SetBinContent(i*4+1,arr[n][0][0])
            state="onZ"
            region=round(arr[n][0][1],0)
            if(arr[n][0][1]>15):
                state="offZ"
                region=round(arr[n][0][1]-15,0)
            histo3_xaxis.SetBinLabel(i*4+1,"SR%i_%s" %(region,state))
            
            state="onZ"
            region=round(arr[n][1][1],0)
            if(arr[n][1][1]>15):
                state="offZ"
                region=round(arr[n][1][1]-15,0)
            histo2.SetBinContent(i*4+2,arr[n][1][0])
            histo3_xaxis.SetBinLabel(i*4+2,"SR%i_%s" %(region,state))
            
            state="onZ"
            region=round(arr[n][2][1],0)
            if(arr[n][2][1]>15):
                state="offZ"
                region=round(arr[n][2][1]-15,0)
            histo3.SetBinContent(i*4+3,arr[n][2][0])
            histo3_xaxis.SetBinLabel(i*4+3,"SR%i_%s" %(region,state))
           
            #histo.SetBinContent(i*4+2,arr[n][1][0])
            #histo.SetBinContent(i*4+3,arr[n][2][0])

    
histo3.Draw("")
histo2.Draw("SAME")
histo.Draw("SAME")
histo3.GetXaxis().SetTitle("signal region")
histo3.GetYaxis().SetTitle("r_{exp}")


ROOT.gPad.Update()
c2.Update()








