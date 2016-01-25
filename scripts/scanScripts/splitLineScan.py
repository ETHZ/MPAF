import os, sys, ROOT

line=sys.argv[1]
mass=sys.argv[2]

mGluinoIdx=line.find('mGluino_')+8
mLSPEndIdx=line.find('mLSP_')-1
mLSPIdx=line.find('mLSP_')+5
#rootIdx=line.find('.root')

subGluino=line[mGluinoIdx:mLSPEndIdx]
subLSP=line[mLSPIdx:] #:rootIdx]

if 'to' in subGluino:
    toIdx=subGluino.find('to')
    mGlu=int(subGluino[0:toIdx])
    MGlu=int(subGluino[toIdx+2:])
else:
    mGlu=int(subGluino)-1
    MGlu=int(subGluino)

if 'to' in subLSP:
    toIdx=subLSP.find('to')
    mLSP=int(subLSP[0:toIdx])
    MLSP=int(subLSP[toIdx+2:])
else:
    mLSP=int(subLSP)-1
    MLSP=int(subLSP)

#print mGluinoIdx, mLSPEndIdx, mLSPIdx, rootIdx
#print line[mGluinoIdx:mLSPEndIdx] , line[mLSPIdx:]

#print mGlu,MGlu,mLSP,MLSP

masses=mass.split("-")[1:3]
#print masses
#print mLSP, int(masses[1]), mLSP>int(masses[1])

#print mGlu>int(masses[0]), MGlu<=int(masses[0]), mLSP>int(masses[1]), MLSP<=int(masses[1])
if mGlu>=int(masses[0]) or MGlu<int(masses[0]) or mLSP>=int(masses[1]) or MLSP<int(masses[1]):
    print 0
else:
    print 1





ifile=open("fileNames",'r')
lines=ifile.read().splitlines()

allMasses={}

for line in lines:
    
    f = ROOT.TFile.Open(line+"/T1tttt.root", "read")
    t = f.Get("tree")

    for massSel in massesSelections:
        nEntries=t.GetEntries("GenSusyMScan1=="+str(gluMass)+
                              " && GenSusyMScan2=="+str(lspMass))
        if nEntries==0:
            continue
    
    massName="-"+str(gluMass)+"-"+str(lspMass)+"-"
    allMasses[massName]=line

    os.system("cp $MPAF/cfg/ssdlScan_template_file.cfg $MPAF/cfg/tmpFiles/ssdlScan"+massName+".cfg")
    os.system("sed -i 's|MASSBENCH|'$mass'|' $MPAF/cfg/tmpFiles/ssdlScan"+massName+".cfg")
os.system("sed -i 's|FILE|'$file'|' $MPAF/cfg/tmpFiles/ssdlScan"+line.split()[1]+".cfg")
os.system("sed -i 's|PATH|'$path'|' $MPAF/cfg/tmpFiles/ssdlScan"+line.split()[2]+".cfg")




