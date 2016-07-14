MPAFDisplay md;
void susy3l_getYields(){
    md.refresh();

    //general parameters ********************* general parameters
    string sig="T1ttttBENCH";

    string dir="SUSY3L";
    string fileName="3l_test";
    if(sig=="T1ttttBENCH") string fileList="3l_test"; //susy3lUnc
    if(sig=="T6ttWWBENCH") string fileList="3l_scanSig_T6ttWW_600_300"; //susy3lUnc
    if(sig=="T5qqqqVVBENCH") string fileList="3l_scanSig_T5qqqqVV_800_550"; //susy3lUnc
  
    bool mcOnly = false;
  
    md.anConf.configureNames( dir, fileName, fileList );
    md.anConf.configureData(false, 0, mcOnly);
     
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=2260; //pb-1 19470
    float energy=13; //TeV

    bool useXS=true;

    md.anConf.loadXSDB("XSectionsSpring15.db");

    map<string,float> LumisXS;

    //via XSect
  
    map<string,float> KFactors;
  
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
 
    //===============================================================
  
    if(sig=="T1ttttBENCH") md.addDataCardSigSample("T1tttt-1000-600-",sig);
    if(sig=="T6ttWWBENCH") md.addDataCardSigSample("T6ttWW_600_300",sig);
    if(sig=="T5qqqqVVBENCH") md.addDataCardSigSample("T5qqqqVV_800_550",sig);

    md.addDataCardSample( "TGJets", "XG"); 
    md.addDataCardSample( "TTGJets", "XG"); 
    md.addDataCardSample( "ZGTo2LG", "XG"); 
    md.addDataCardSample( "WGToLNuG", "XG"); 

    md.addDataCardSample( "TTHnobb", "ttZH"); 
    md.addDataCardSample( "TTLLJets_m1to10", "ttZlowM"); 
    md.addDataCardSample( "TTZToLLNuNu", "ttZH"); 

    md.addDataCardSample( "TTWToLNu", "ttW"); 
   
    md.addDataCardSample( "WZTo3LNu", "WZ"); 
    
    md.addDataCardSample( "tZq_ll", "rares"); 
    md.addDataCardSample( "VHToNonbb", "rares"); 
    md.addDataCardSample( "GGHZZ4L", "rares"); 
    md.addDataCardSample( "ZZTo4L", "rares"); 
    md.addDataCardSample( "WWZ", "rares"); 
    md.addDataCardSample( "WZZ", "rares"); 
    md.addDataCardSample( "ZZZ", "rares"); 
    md.addDataCardSample( "TTTT", "rares"); 

    md.addDataCardSample( "data:Fake:DoubleEG_Run2015C_Oct05_runs_254231_254914", "fake"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015D_Oct05_runs_256630_258158", "fake"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015D_PromptV4_runs_258159_260627", "fake"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015C_Oct05_runs_254231_254914", "fake"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015D_Oct05_runs_256630_258158", "fake"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015D_PromptV4_runs_258159_260627","fake");
    md.addDataCardSample( "data:Fake:MuonEG_Run2015C_Oct05_runs_254231_254914", "fake"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2015D_Oct05_runs_256630_258158", "fake"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2015D_PromptV4_runs_258159_260627", "fake"); 

    md.addDataCardSample( "Fake:TGJets", "fake", -1 );
    md.addDataCardSample( "Fake:TTGJets", "fake", -1 );
    md.addDataCardSample( "Fake:ZGTo2LG", "fake", -1 );
    md.addDataCardSample( "Fake:WGToLNuG", "fake", -1 );
    md.addDataCardSample( "Fake:TTHnobb", "fake", -1 );
    md.addDataCardSample( "Fake:TTLLJets_m1to10", "fake", -1 );
    md.addDataCardSample( "Fake:TTZToLLNuNu", "fake", -1 );
    md.addDataCardSample( "Fake:TTWToLNu", "fake", -1 );
    md.addDataCardSample( "Fake:WZTo3LNu", "fake", -1 );
    md.addDataCardSample( "Fake:tZq_ll", "fake", -1 );
    md.addDataCardSample( "Fake:VHToNonbb", "fake", -1 );
    md.addDataCardSample( "Fake:GGHZZ4L", "fake", -1 );
    md.addDataCardSample( "Fake:ZZTo4L", "fake", -1 );
    md.addDataCardSample( "Fake:WWZ", "fake", -1 );
    md.addDataCardSample( "Fake:WZZ", "fake", -1 );
    md.addDataCardSample( "Fake:ZZZ", "fake", -1 );
    md.addDataCardSample( "Fake:TTTT", "fake", -1 );
/*
    md.addDataCardSample( "TGJets", "pseudodata"); 
    md.addDataCardSample( "TTGJets", "pseudodata"); 
    md.addDataCardSample( "ZGTo2LG", "pseudodata"); 
    md.addDataCardSample( "WGToLNuG", "pseudodata"); 
    md.addDataCardSample( "TTHnobb", "pseudodata"); 
    md.addDataCardSample( "TTLLJets_m1to10", "pseudodata"); 
    md.addDataCardSample( "TTZToLLNuNu", "pseudodata"); 
    md.addDataCardSample( "TTWToLNu", "pseudodata"); 
    md.addDataCardSample( "WZTo3LNu", "pseudodata"); 
    md.addDataCardSample( "tZq_ll", "pseudodata"); 
    md.addDataCardSample( "VHToNonbb", "pseudodata"); 
    md.addDataCardSample( "GGHZZ4L", "pseudodata"); 
    md.addDataCardSample( "ZZTo4L", "pseudodata"); 
    md.addDataCardSample( "WWZ", "pseudodata"); 
    md.addDataCardSample( "WZZ", "pseudodata"); 
    md.addDataCardSample( "ZZZ", "pseudodata"); 
    md.addDataCardSample( "TTTT", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015C_Oct05_runs_254231_254914", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015D_Oct05_runs_256630_258158", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015D_PromptV4_runs_258159_260627", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015C_Oct05_runs_254231_254914", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015D_Oct05_runs_256630_258158", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015D_PromptV4_runs_258159_260627","pseudodata");
    md.addDataCardSample( "data:Fake:MuonEG_Run2015C_Oct05_runs_254231_254914", "pseudodata"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2015D_Oct05_runs_256630_258158", "pseudodata"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2015D_PromptV4_runs_258159_260627", "pseudodata"); 
    md.addDataCardSample( "Fake:TGJets", "pseudodata", -1 );
    md.addDataCardSample( "Fake:TTGJets", "pseudodata", -1 );
    md.addDataCardSample( "Fake:ZGTo2LG", "pseudodata", -1 );
    md.addDataCardSample( "Fake:WGToLNuG", "pseudodata", -1 );
    md.addDataCardSample( "Fake:TTHnobb", "pseudodata", -1 );
    md.addDataCardSample( "Fake:TTLLJets_m1to10", "pseudodata", -1 );
    md.addDataCardSample( "Fake:TTZToLLNuNu", "pseudodata", -1 );
    md.addDataCardSample( "Fake:TTWToLNu", "pseudodata", -1 );
    md.addDataCardSample( "Fake:WZTo3LNu", "pseudodata", -1 );
    md.addDataCardSample( "Fake:tZq_ll", "pseudodata", -1 );
    md.addDataCardSample( "Fake:VHToNonbb", "pseudodata", -1 );
    md.addDataCardSample( "Fake:GGHZZ4L", "pseudodata", -1 );
    md.addDataCardSample( "Fake:ZZTo4L", "pseudodata", -1 );
    md.addDataCardSample( "Fake:WWZ", "pseudodata", -1 );
    md.addDataCardSample( "Fake:WZZ", "pseudodata", -1 );
    md.addDataCardSample( "Fake:ZZZ", "pseudodata", -1 );
    md.addDataCardSample( "Fake:TTTT", "pseudodata", -1 );
*/
  
    md.addDataCardSample( "DoubleEG_Run2015C_Oct05_runs_254231_254914", "data"); 
    md.addDataCardSample( "DoubleEG_Run2015D_Oct05_runs_256630_258158", "data"); 
    md.addDataCardSample( "DoubleEG_Run2015D_PromptV4_runs_258159_260627", "data"); 
    md.addDataCardSample( "DoubleMuon_Run2015C_Oct05_runs_254231_254914", "data"); 
    md.addDataCardSample( "DoubleMuon_Run2015D_Oct05_runs_256630_258158", "data"); 
    md.addDataCardSample( "DoubleMuon_Run2015D_PromptV4_runs_258159_260627","data");
    md.addDataCardSample( "MuonEG_Run2015C_Oct05_runs_254231_254914", "data"); 
    md.addDataCardSample( "MuonEG_Run2015D_Oct05_runs_256630_258158", "data"); 
    md.addDataCardSample( "MuonEG_Run2015D_PromptV4_runs_258159_260627", "data"); 

    //===============================================================
    //UNCERTANITIES

    md.addNuisanceParameter("JES","ttW:ttZH:ttZlowM:WZ:XG:rares:"+sig,"shape","");
    md.addNuisanceParameter("BTAG","ttW:ttZH:ttZlowM:WZ:XG:rares:"+sig,"shape","");
    md.addNuisanceParameter("PUXS","ttW:ttZH:ttZlowM:WZ:XG:rares:"+sig,"shape","");
    md.addNuisanceParameter("EWKFR","fake","shape","");

    //fastSim related uncertainties
    md.addNuisanceParameter("BTAGFS",sig,"shape","");
    md.addNuisanceParameter("LepEffFS",sig,"shape","");
	md.addNuisanceParameter("HLTFS",sig,"shape","");
    md.addNuisanceParameter("ISR",sig,"shape","");
    md.addNuisanceParameter("XSFS",sig,"shape","");
	md.addNuisanceParameter("ACCFS",sig,"shape","");

    md.addNuisanceParameter("ttWAcc","ttW","shape","");
    md.addNuisanceParameter("ttZAcc","ttZH","shape","");
    md.addNuisanceParameter("ttZlowMAcc","ttZlowM","shape","");
    //md.addNuisanceParameter("ttHAcc","ttH","shape","");
    md.addNuisanceParameter("wzTh","WZ","shape","");

    const int nBins = 30;
    string cats[nBins]={
        "OnZSR001", "OnZSR002", "OnZSR003", "OnZSR004", "OnZSR005", "OnZSR006",
        "OnZSR007", "OnZSR008", "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012",
        "OnZSR013", "OnZSR014", "OnZSR015",
	
        "OffZSR001", "OffZSR002", "OffZSR003", "OffZSR004", "OffZSR005", "OffZSR006",
        "OffZSR007", "OffZSR008", "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012",
        "OffZSR013", "OffZSR014", "OffZSR015"
    };
  
    //Flat uncertanties =================================
    //lumi
    md.addNuisanceParameter("lumi","ttW:ttZH:ttZlowM:XG:rares:"+sig,"lnN","1.046:1.046:1.046:1.046:1.046:1.046");
    //experimental uncertainties
    md.addNuisanceParameter("HLTEff","ttW:ttZH:ttZlowM:XG:rares:"+sig,"lnN","1.03:1.03:1.03:1.03:1.03:1.03");
    md.addNuisanceParameter("LepEff","ttW:ttZH:ttZlowM:XG:rares:"+sig,"lnN","1.06:1.06:1.06:1.06:1.06:1.06"); //2% per lepton
 
    //Data-driven methods
    md.addNuisanceParameter("fakeExtrapol","fake","lnN","1.30");
    md.addNuisanceParameter("wzNorm","WZ","lnN","1.15");
 
    //theoretical uncertainties
    
    //rare processes
    md.addNuisanceParameter("XGTh","XG","lnN","1.50");
    md.addNuisanceParameter("rareTh","rares","lnN","1.50");
  
    //pdf uncertainty
    md.addNuisanceParameter("ttWPdf","ttW","lnN","1.02");
    md.addNuisanceParameter("ttZPdf","ttZH:ttZlowM","lnN","1.03:1.06");
    //md.addNuisanceParameter("ttHPdf","ttH","lnN","1.035");

    //x-section uncertainty
    md.addNuisanceParameter("ttWXs","ttW","lnN","1.11");
    md.addNuisanceParameter("ttZXs","ttZH:ttZlowM","lnN","1.13:1.33");
    //md.addNuisanceParameter("ttHXs","ttH","lnN","1.09");


    //*********************************************************************²

    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
   
    md.prepareDisplay();

    string categs[nBins]={
        "global_OnZSR001", "global_OnZSR002", "global_OnZSR003", "global_OnZSR004",
        "global_OnZSR005", "global_OnZSR006", "global_OnZSR007", "global_OnZSR008",
        "global_OnZSR009", "global_OnZSR010", "global_OnZSR011", "global_OnZSR012",
        "global_OnZSR013", "global_OnZSR014", "global_OnZSR015",
    
        "global_OffZSR001", "global_OffZSR002", "global_OffZSR003", "global_OffZSR004", 
        "global_OffZSR005", "global_OffZSR006", "global_OffZSR007", "global_OffZSR008", 
        "global_OffZSR009", "global_OffZSR010", "global_OffZSR011", "global_OffZSR012",
        "global_OffZSR013", "global_OffZSR014", "global_OffZSR015"
    };
    vector<string> vcategs;
    for(int i=0;i<nBins;i++) {
        vcategs.push_back( categs[i] );
    }
    //vcategs.push_back( categs[15] );

    //external uncertainties ===================================
    float AccTTW[30]={
        0.05, 0.05, 0.18, 0.18, 0.05, 
        0.05, 0.18, 0.18, 0.05, 0.05, 
        0.18, 0.18, 0.18, 0.18, 0.18,

        0.05, 0.05, 0.18, 0.18, 0.05, 
        0.05, 0.18, 0.18, 0.05, 0.05, 
        0.18, 0.18, 0.18, 0.18, 0.18
    };
  
    float AccTTZ[30]={
        0.03, 0.03, 0.05, 0.05, 0.03, 
        0.03, 0.05, 0.05, 0.03, 0.03, 
        0.05, 0.05, 0.05, 0.05, 0.05, 

        0.05, 0.05, 0.08, 0.08, 0.05, 
        0.05, 0.08, 0.08, 0.05, 0.05, 
        0.08, 0.08, 0.08, 0.08, 0.08
    };
    
    float AccTTZlowM[30]={
        0.03, 0.03, 0.05, 0.05, 0.03, 
        0.03, 0.05, 0.05, 0.03, 0.03, 
        0.05, 0.05, 0.05, 0.05, 0.05, 

        0.05, 0.05, 0.08, 0.08, 0.05, 
        0.05, 0.08, 0.08, 0.05, 0.05, 
        0.08, 0.08, 0.08, 0.08, 0.08
    }; 

    float AccTTH[30]={
        0.05, 0.05, 0.08, 0.08, 0.05, 
        0.05, 0.08, 0.08, 0.05, 0.05, 
        0.08, 0.08, 0.08, 0.08, 0.08, 

        0.03, 0.03, 0.05, 0.05, 0.03, 
        0.03, 0.05, 0.05, 0.03, 0.03, 
        0.05, 0.05, 0.05, 0.05, 0.05
    };

    float ExtrapolWZ[30]={
        0.10, 0.10, 0.20, 0.20, 0.10, 
        0.10, 0.20, 0.20, 0.10, 0.10, 
        0.20, 0.20, 0.30, 0.20, 0.20, 

        0.10, 0.10, 0.20, 0.20, 0.10, 
        0.10, 0.20, 0.20, 0.10, 0.10, 
        0.20, 0.20, 0.30, 0.20, 0.20, 
    };

	//datasets
    string dss[8]={"ttW","ttZH","ttZlowM","WZ","XG","fake","rares",sig};

    //statistical uncertainties for all processes
    for(int isr=0;isr<nBins;isr++) {
        for(size_t id=0;id<8;id++) {
            md.addNuisanceParameter(dss[id]+cats[isr]+"stat",dss[id],"shape","");
        }
    }

    //Q2 background acceptance uncertainties 
    for(size_t ic=0;ic<nBins;ic++) {
        md.addExternalSystUnc("ttW"     ,"ttWAcc"       ,AccTTW[ic]     , -1*AccTTW[ic]     , categs[ic], "selected");
        md.addExternalSystUnc("ttZH"    ,"ttZAcc"       ,AccTTZ[ic]     , -1*AccTTZ[ic]     , categs[ic], "selected");
        md.addExternalSystUnc("ttZlowM" ,"ttZlowMAcc"   ,AccTTZlowM[ic] , -1*AccTTZlowM[ic] , categs[ic], "selected");
        //md.addExternalSystUnc("ttH"     ,"ttHAcc"       ,AccTTH[ic]     , -1*AccTTH[ic]     , categs[ic], "selected");
        md.addExternalSystUnc("WZ"      ,"wzTh"         ,ExtrapolWZ[ic] , -1*ExtrapolWZ[ic] , categs[ic], "selected");
    }

    //md.makeMultiDataCard(sig, vcategs, "selected", "susy3l_"+sig);
    //md.getStatistics("global_OffZSR001");
    //md.getStatistics("global_OffZSR002");
    //md.getStatistics("global_OffZSR003");
    //md.getStatistics("global_OffZSR004");
    //md.getStatistics("global_OffZSR005");
    //md.getStatistics("global_OffZSR006");
    //md.getStatistics("global_OffZSR007");
    //md.getStatistics("global_OffZSR008");
    //md.getStatistics("global_OffZSR009");
    //md.getStatistics("global_OffZSR010");
    //md.getStatistics("global_OffZSR011");
    //md.getStatistics("global_OffZSR012");
    //md.getStatistics("global_OffZSR013");
    //md.getStatistics("global_OffZSR014");
    //md.getStatistics("global_OffZSR015");
    md.getStatistics("global_OffZBaseline");

    gROOT->ProcessLine(".qqqqqqqqqqqqqq");
}
