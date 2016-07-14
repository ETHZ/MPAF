import ROOT

#line format
# Interactions - gluinos  Nominal (pb) +/- Uncertainty
# 200 GeV 3574.52 +/- 14.0616%


#xsFile = open("SUSYCrossSections13TeVgluglu.txt")
xsFile = open("SUSYCrossSections13TeVsquarksquark.txt")
lines = [x.strip('\n') for x in xsFile if "GeV" in x]

h_xs = ROOT.TH1F("xs","", 561, 197.5, 3002.5)

for line in lines:
    mass = float(line.split()[0])
    xsec = float(line.split()[2])
    err  = float(line.split()[4].strip("%"))/100*xsec
    ibin = h_xs.FindBin(mass)
    h_xs.SetBinContent( ibin, xsec ) 
    h_xs.SetBinError  ( ibin, err  ) 

rootFile = ROOT.TFile(xsFile.name.replace(".txt",".root"),"RECREATE")
h_xs.Write()
rootFile.Close()

