from array import *

class sms():

    def __init__(self, modelname):
        if modelname.find("T1tttt") != -1: self.T1tttt()
        if modelname.find("T1bbbb") != -1: self.T1bbbb()
        if modelname.find("T1qqqq") != -1: self.T1qqqq()
        if modelname.find("T6ttWW") != -1: self.T6ttWW()
        if modelname.find("T5qqqqVV") != -1: self.T5qqqqVV()
        if modelname.find("T5ttttdeg") != -1: self.T5ttttdeg()
    
    def T1tttt(self):
        # model name
        self.modelname = "T1tttt"
        # decay chain
        self.label= "pp #rightarrow #tilde{g}#tilde{g}, #tilde{g} #rightarrow t#bar{t}#tilde{#chi}^{0}_{1}";
        # scan range to plot
        self.Xmin = 687.5
        self.Xmax = 1712.5
        self.Ymin = -12.5
        self.Ymax = 1712.5
        self.Zmin = 0.01
        self.Zmax = 50
        # produce sparticle
        self.sParticle = "m_{#tilde{g}} (GeV)"
        # LSP
        self.LSP = "m_{#tilde{#chi}_{1}^{0}} (GeV)"
        # diagonal position: mLSP = mgluino - 2m(W+b)
        mT = 170
        self.diagX = array('d',[0,20000])
        self.diagY = array('d',[-mT, 20000-mT])        
        self.diagText = 'm_{#tilde{g}} - m_{#tilde{#chi}^{0}_{1}} = 2 (m_{W} + m_{b})'
        self.diagAngle = 34.6
        self.diagTextX = 0.2
        self.diagTextY = 0.47
        # turn off diagonal lines
        self.diagOn = True
        self.fixMass = ''
 
    def T5ttttdeg(self):
        # model name
        self.modelname = "T5ttttdeg"
        # decay chain
        self.label= "pp #rightarrow #tilde{g}#tilde{g}, #tilde{g} #rightarrow #tilde{t}_{1}t, #tilde{t}_{1} #rightarrow t#tilde{#chi}^{0}_{1}";
        # scan range to plot
        self.Xmin = 587.5
        self.Xmax = 1312.5
        self.Ymin = -12.5
        self.Ymax = 1362.5
        self.Zmin = 0.01
        self.Zmax = 50
        # produce sparticle
        self.sParticle = "m_{#tilde{g}} (GeV)"
        # LSP
        self.LSP = "m_{#tilde{#chi}_{1}^{0}} (GeV)"
        # diagonal position: mLSP = mgluino - 2m(W+b)
        mT = 85
        self.diagX = array('d',[0,20000])
        self.diagY = array('d',[-mT, 20000-mT])        
        self.diagText = 'm_{#tilde{g}} - m_{#tilde{#chi}^{0}_{1}} = m_{W} + m_{b}'
        self.diagAngle = 29.5
        self.diagTextX = 0.2
        self.diagTextY = 0.49
        # turn off diagonal lines
        self.diagOn = True
        self.fixMass = 'm_{#tilde{t}_{1}} = m_{#tilde{#chi}^{0}_{1}} + 20 GeV'
        
    def T1bbbb(self):
        # model name
        self.modelname = "T1bbbb"
        # decay chain
        self.label= "pp #rightarrow #tilde{g} #tilde{g}, #tilde{g} #rightarrow b #bar{b} #tilde{#chi}^{0}_{1}";
        # plot boundary. The top 1/4 of the y axis is taken by the legend
        self.Xmin = 600
        self.Xmax = 1950
        self.Ymin = 0
        self.Ymax = 1900
        self.Zmin = 0.001
        self.Zmax = 2
        # produce sparticle
        self.sParticle = "m_{#tilde{g}} (GeV)"
        # LSP
        self.LSP = "m_{#tilde{#chi}_{1}^{0}} (GeV)"
        # diagonal position: mLSP = mgluino - 2mtop
        self.diagX = array('d',[0,20000])
        self.diagY = array('d',[0, 20000])
        # turn off diagonal lines
        self.diagOn = False
 
    def T1qqqq(self):
        # model name
        self.modelname = "T1qqqq"
        # decay chain
        self.label= "pp #rightarrow #tilde{g} #tilde{g}, #tilde{g} #rightarrow q #bar{q} #tilde{#chi}^{0}_{1}";
        # plot boundary. The top 1/4 of the y axis is taken by the legend
        self.Xmin = 600
        self.Xmax = 1950
        self.Ymin = 0
        self.Ymax = 1600
        self.Zmin = 0.001
        self.Zmax = 2
        # produce sparticle
        self.sParticle = "m_{#tilde{g}} (GeV)"
        # LSP
        self.LSP = "m_{#tilde{#chi}_{1}^{0}} (GeV)"
        # diagonal position: mLSP = mgluino - 2mtop
        self.diagX = array('d',[0,20000])
        self.diagY = array('d',[0, 20000])
        # turn off diagonal lines
        self.diagOn = False


    def T6ttWW(self):
        # model name
        self.modelname = "T6ttWW"
        # decay chain
        self.label= "pp #rightarrow #tilde{b}_{1}#tilde{b}_{1}*, #tilde{b}_{1}#rightarrow tW#tilde{#chi}^{0}_{1} ";
        # scan range to plot
        self.Xmin = 287.5
        self.Xmax = 912.5
        self.Ymin = 62.5
        self.Ymax = 1112.5
        self.Zmin = 0.01
        self.Zmax = 10
        # produce sparticle
        self.sParticle = "m_{#tilde{b}} (GeV)"
        # LSP
        self.LSP = "m_{#tilde{#chi}^{#pm}_{1}} (GeV)"
        # diagonal position: msbottom = mXpm
        mT = 0
        self.diagX = array('d',[0,20000])
        self.diagY = array('d',[-mT, 20000-mT])        
        self.diagText = 'm_{#tilde{b}} = m_{#tilde{#chi}^{#pm}_{1}}'
        self.diagAngle = 35.5
        self.diagTextX = 0.2
        self.diagTextY = 0.38
        # turn off diagonal lines
        self.diagOn = True
        self.fixMass = 'm_{#tilde{#chi}^{0}_{1}} = 50 GeV'
        

    def T5qqqqVV(self):
        # model name
        self.modelname = "T5qqqqVV"
        # decay chain
        self.label= "pp #rightarrow #tilde{g}#tilde{g}, #tilde{g} #rightarrow q#bar{q}'W/Z#tilde{#chi}^{0}_{1}";
        # scan range to plot
        self.Xmin = 587.5
        self.Xmax = 1312.5
        self.Ymin = -12.5
        self.Ymax = 1412.5
        self.Zmin = 0.01
        self.Zmax = 50
        # produce sparticle
        self.sParticle = "m_{#tilde{g}} (GeV)"
        # LSP
        self.LSP = "m_{#tilde{#chi}_{1}^{0}} (GeV)"
        # diagonal position: mLSP = mgluino - 2mtop 
        mT = 0
        self.diagX = array('d',[0,20000])
        self.diagY = array('d',[-mT, 20000-mT])        
        self.diagText = 'm_{#tilde{g}} = m_{#tilde{#chi}^{0}_{1}}'
        self.diagAngle = 29.01
        self.diagTextX = 0.2
        self.diagTextY = 0.53
        # turn off diagonal lines
        self.diagOn = True
        self.fixMass = 'm_{#tilde{#chi}^{#pm}_{1}} = 0.5 (m_{#tilde{g}} + m_{#tilde{#chi}^{0}_{1}})'
 
 


