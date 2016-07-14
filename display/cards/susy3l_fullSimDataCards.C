MPAFDisplay md;

void susy3l_fullSimDataCards(){
    md.refresh();

    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="merged_2fb"; // not needed for statistics but provides the normalization
    string fileList="merged_2fb_Bkg"; // put command line that gives all files as in a "ls" command

    bool mcOnly = false;
  
    md.anConf.configureNames( dir, fileName, fileList );
    md.anConf.configureData(false, 0, mcOnly);
     
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=10000; //pb-1 19470
    float energy=13; //TeV

    bool useXS=true;

    md.anConf.loadXSDB("XSectionsSpring15.db");

    map<string,float> LumisXS;

    //via XSect
  
    map<string,float> KFactors;
  
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
 
    //===============================================================
 
    string signal = "SIGSAMPLE";
  
    if(signal == "T1t4_1200"      ) md.addDataCardSigSample("T1tttt_mGo1200_mChi800",                     signal);
    if(signal == "T1t4_1500"      ) md.addDataCardSigSample("T1tttt_mGo1500_mChi100",                     signal);
    if(signal == "T54q_deg"       ) md.addDataCardSigSample("T5ttttDeg_mGo1000_mStop300_mCh285_mChi280",  signal);
    if(signal == "T6t2W2_600"     ) md.addDataCardSigSample("T6ttWW_mSbot600_mCh425_mChi50",              signal);
    if(signal == "T6t2W2_650"     ) md.addDataCardSigSample("T6ttWW_mSbot650_mCh150_mChi50",              signal);
    if(signal == "T54qWZ_315"     ) md.addDataCardSigSample("T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep",   signal);
    if(signal == "T54qWZ_325"     ) md.addDataCardSigSample("T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep",   signal);
    if(signal == "T54qWZ_800"     ) md.addDataCardSigSample("T5qqqqWZ_mGo1500_mCh800_mChi100_lep",        signal);
    if(signal == "T54qWZ_1000"    ) md.addDataCardSigSample("T5qqqqWZ_mGo1200_mCh1000_mChi800_lep",       signal);

    md.addDataCardSample( "TGJets", "XG"); 
    md.addDataCardSample( "TTGJets", "XG"); 
    md.addDataCardSample( "ZGTo2LG", "XG"); 
    md.addDataCardSample( "WGToLNuG", "XG"); 
    md.addDataCardSample( "TTHnobb", "ttZH"); 
    md.addDataCardSample( "TTLLJets_m1to10", "ttZH"); 
    md.addDataCardSample( "TTZToLLNuNu", "ttZH"); 
    md.addDataCardSample( "TTWToLNu", "ttW", 1); 
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

    /*
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
    */
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

    md.addNuisanceParameter("JES","ttW:ttZH:WZ:XG:rares:" + signal,"shape","");
    md.addNuisanceParameter("BTAG","ttW:ttZH:WZ:XG:rares:" + signal,"shape","");
    md.addNuisanceParameter("PUXS","ttW:ttZH:WZ:XG:rares:" + signal,"shape","");

    md.addNuisanceParameter("EWKFR","fake","shape","");

    md.addNuisanceParameter("ttWAcc","ttW","shape","");
    md.addNuisanceParameter("ttZHAcc","ttZH","shape","");

    //md.addNuisanceParameter("BTAGFS",signal,"shape",""); //no fastSim uncert. for fullSim
    //md.addNuisanceParameter("LepEffFS","T1ttttBENCH","shape","");
    //md.addNuisanceParameter("ISR",signal,"shape",""); //no fastSim uncert. for fullSim

    //md.addNuisanceParameter("QCDScale","T1ttttBENCH","shape","");


    string cats[30]={
        "OnZSR001", "OnZSR002", "OnZSR003", "OnZSR004", "OnZSR005", "OnZSR006",
        "OnZSR007", "OnZSR008", "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012",
        "OnZSR013", "OnZSR014", "OnZSR015",
	
        "OffZSR001", "OffZSR002", "OffZSR003", "OffZSR004", "OffZSR005", "OffZSR006",
        "OffZSR007", "OffZSR008", "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012",
        "OffZSR013", "OffZSR014", "OffZSR015"
    };

    string dss[7]={"ttW","ttZH","WZ","XG","fake","rares",signal};

    for(int isr=0;isr<30;isr++) {
        md.addNuisanceParameter("pdfS"+cats[isr],signal,"shape","");
        md.addNuisanceParameter("fake"+cats[isr]+"stat","fake","shape","");
        for(size_t id=0;id<7;id++) {
            md.addNuisanceParameter(dss[id]+cats[isr]+"stat",dss[id],"shape","");
        }
    }   


    //Flat uncertanties =================================
    //lumi
    md.addNuisanceParameter("lumi","ttW:ttZH:XG:rares:" + signal,"lnN","1.046:1.046:1.046:1.046:1.046");
    //experimental uncertainties
    md.addNuisanceParameter("tEff","ttW:ttZH:XG:rares:" + signal,"lnN","1.03:1.03:1.03:1.03:1.03");
    md.addNuisanceParameter("lEff","ttW:ttZH:XG:rares:" + signal,"lnN","1.02:1.02:1.02:1.02:1.02");
    //md.addNuisanceParameter("pileup","ttW:ttZH:XG:rares:" + signal,"lnN","1.03:1.03:1.03:1.03:1.03");
    //Data-driven methods
    md.addNuisanceParameter("fratio","fake","lnN","1.30");
    //theoretical uncertainties
    md.addNuisanceParameter("wzTh","WZ","lnN","1.30");
    md.addNuisanceParameter("WWTh","ttW","lnN","1.50");
    md.addNuisanceParameter("TGTh","XG","lnN","1.50");
    md.addNuisanceParameter("rareTh","rares","lnN","1.50");
  
    md.addNuisanceParameter("ttWPdf","ttW","lnN","1.04");
    md.addNuisanceParameter("ttZHPdf","ttZH","lnN","1.04");
    md.addNuisanceParameter("ttWXs","ttW","lnN","1.13");
    md.addNuisanceParameter("ttZHXs","ttZH","lnN","1.11");
    //md.addNuisanceParameter("fsHLT",signal,"lnN","1.05"); no fastSim uncert. for fullSim


    //*********************************************************************²

    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
   
    md.prepareDisplay();

    int ncategs=30;
    string categs[30]={
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
    for(int i=0;i<30;i++) {
        vcategs.push_back( categs[i] );
    }

    //external uncertainties ===================================
    float AccTTW[30]={
        0.05, 0.05, 0.18, 0.18, 0.05, 
        0.05, 0.18, 0.18, 0.05, 0.05, 
        0.18, 0.18, 0.18, 0.18, 0.18,

        0.05, 0.05, 0.18, 0.18, 0.05, 
        0.05, 0.18, 0.18, 0.05, 0.05, 
        0.18, 0.18, 0.18, 0.18, 0.18
    };
  
    float AccTTZH[30]={
        0.03, 0.03, 0.03, 0.03, 0.03, 
        0.03, 0.03, 0.03, 0.03, 0.03, 
        0.03, 0.03, 0.03, 0.03, 0.03, 

        0.05, 0.05, 0.08, 0.08, 0.05, 
        0.05, 0.08, 0.08, 0.05, 0.05, 
        0.08, 0.08, 0.08, 0.08, 0.08
    };



    for(size_t ic=0;ic<30;ic++) {
        for(int isr=0;isr<30;isr++) {
            if(categs[ic].substr(7, categs[ic].size()-7)==cats[isr])
	            md.addExternalSystUnc(signal,"pdfS"+cats[isr],0.1, -0.1, categs[ic], "selected");
            else
	            md.addExternalSystUnc(signal,"pdfS"+cats[isr],0., 0., categs[ic], "selected");
        }
        //md.addExternalSystUnc(signal,"QCDScale",hQCDUp->GetBinContent(ic+1), hQCDDown->GetBinContent(ic+1), categs[ic], "selected");

        md.addExternalSystUnc("ttW","ttWAcc",AccTTW[ic], -1*AccTTW[ic], categs[ic], "selected");
        md.addExternalSystUnc("ttZH","ttZHAcc",AccTTZH[ic], -1*AccTTZH[ic], categs[ic], "selected");
        //for(size_t id=0;id<7;id++) {
            //md.addExternalSystUnc(dss[id],"tHTE",HLTEff[ic], -1*HLTEff[ic], categs[ic], "selected");
        //}
    }
    
    md.makeMultiDataCard(signal, vcategs, "selected", signal);
    //md.getStatistics("global_OffZSR001");
    gROOT->ProcessLine(".q");
}
