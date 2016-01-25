import os, sys, ROOT

ifile=open("fileNamesV3",'r')
lines=ifile.read().splitlines()

allMasses={}

mGluMax=2025
mLSPMax=2025

step=25

massesSelections=[]
for ig in range(0, mGluMax, step):
    for il in range(0, mLSPMax, step):
        if il>ig: continue
        massSel=[ig, il]
        massesSelections.append(massSel)
       # print ig, il



for line in lines:
    
    fileName=("dcap://t3se01.psi.ch:22125/"+line.split()[0]+"/T1tttt.root")
    print fileName
    f = ROOT.TFile.Open( fileName , "read")
    t = f.Get("tree")

    mGluinoIdx=line.find('mGluino_')+8
    mLSPEndIdx=line.find('mLSP_')-1
    mLSPIdx=line.find('mLSP_')+5
    subGluino=line[mGluinoIdx:mLSPEndIdx]
    if 'to' in subGluino:
        toIdx=subGluino.find('to')
        mGlu=int(subGluino[0:toIdx])
        MGlu=int(subGluino[toIdx+2:])
    else:
        mGlu=int(subGluino)
        MGlu=int(subGluino)

    for massSel in massesSelections:
        gluMass=massSel[0]
        lspMass=massSel[1]

        if gluMass<mGlu or gluMass>MGlu: #trimming
            continue

        nEntries=t.GetEntries("GenSusyMScan1=="+str(gluMass)+
                              " && GenSusyMScan2=="+str(lspMass))
        if nEntries==0:
            continue
    
        print "selected point ", gluMass, lspMass

        massName="-"+str(gluMass)+"-"+str(lspMass)+"-"
        allMasses[massName]=line

        os.system("cp /shome/mmarionn/MPAF/cfg/ssdlScan_template_file.cfg /shome/mmarionn/MPAF/cfg/tmpFiles/ssdlScan"+massName+".cfg")
        os.system("sed -i 's|MASSBENCH|'"+massName+"'|' /shome/mmarionn/MPAF/cfg/tmpFiles/ssdlScan"+massName+".cfg")
        os.system("sed -i 's|FILE|'"+line.split()[1]+"'|' /shome/mmarionn/MPAF/cfg/tmpFiles/ssdlScan"+massName+".cfg")
        os.system("sed -i 's|PATH|'"+line.split()[0]+"'|' /shome/mmarionn/MPAF/cfg/tmpFiles/ssdlScan"+massName+".cfg")




