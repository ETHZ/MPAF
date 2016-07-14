MPAFDisplay md;

void susy3l_scanSigBENCH(){
    md.refresh();

    //general parameters ********************* general parameters
    string sig="fs_t1ttttBENCH";

    string dir="SUSY3L";
    string fileName="merged_2fb";
    if(sig=="fs_t1ttttBENCH") string fileList="merged_2fb_T1tttt-MASS-"; //susy3lUnc
    if(sig=="fs_t6ttww_50BENCH") string fileList="merged_2fb_T6ttWWMASS"; //susy3lUnc
    if(sig=="fs_t5qqqqvvBENCH") string fileList="merged_2fb_T5qqqqVVMASS"; //susy3lUnc
  
    bool mcOnly = false;
    bool onlyOneSR = false;
    //int testSR = NUMBER;
  
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
  
    float kfac = 0.55555555;

    if(sig=="fs_t1ttttBENCH") md.addDataCardSigSample("T1tttt-MASS-",sig);
    if(sig=="fs_t6ttww_50BENCH") md.addDataCardSigSample("T6ttWWMASS",sig);
    if(sig=="fs_t5qqqqvvBENCH") md.addDataCardSigSample("T5qqqqVVMASS",sig, kfac);

    md.addDataCardSample( "TGJets", "xg"); 
    md.addDataCardSample( "TTGJets", "xg"); 
    md.addDataCardSample( "ZGTo2LG", "xg"); 
    md.addDataCardSample( "WGToLNuG", "xg"); 

    md.addDataCardSample( "TTHnobb", "ttzh"); 
    md.addDataCardSample( "TTZToLLNuNu", "ttzh"); 

    md.addDataCardSample( "TTLLJets_m1to10", "ttzlowM"); 

    md.addDataCardSample( "TTWToLNu", "ttw"); 
   
    md.addDataCardSample( "WZTo3LNu", "wz"); 
    
    md.addDataCardSample( "tZq_ll", "rares"); 
    md.addDataCardSample( "VHToNonbb", "rares"); 
    md.addDataCardSample( "GGHZZ4L", "rares"); 
    //md.addDataCardSample( "ZZTo4L", "rares"); 
    md.addDataCardSample( "WWZ", "rares"); 
    md.addDataCardSample( "WZZ", "rares"); 
    md.addDataCardSample( "ZZZ", "rares"); 
    md.addDataCardSample( "TTTT", "rares"); 

    md.addDataCardSample( "data:Fake:DoubleEG_Run2015C_Oct05_runs_254231_254914", "fakes"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015D_Oct05_runs_256630_258158", "fakes"); 
    md.addDataCardSample( "data:Fake:DoubleEG_Run2015D_PromptV4_runs_258159_260627", "fakes"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015C_Oct05_runs_254231_254914", "fakes"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015D_Oct05_runs_256630_258158", "fakes"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2015D_PromptV4_runs_258159_260627","fakes");
    md.addDataCardSample( "data:Fake:MuonEG_Run2015C_Oct05_runs_254231_254914", "fakes"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2015D_Oct05_runs_256630_258158", "fakes"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2015D_PromptV4_runs_258159_260627", "fakes"); 

    md.addDataCardSample( "Fake:TGJets", "fakes", -1 );
    md.addDataCardSample( "Fake:TTGJets", "fakes", -1 );
    md.addDataCardSample( "Fake:ZGTo2LG", "fakes", -1 );
    md.addDataCardSample( "Fake:WGToLNuG", "fakes", -1 );
    md.addDataCardSample( "Fake:TTHnobb", "fakes", -1 );
    md.addDataCardSample( "Fake:TTLLJets_m1to10", "fakes", -1 );
    md.addDataCardSample( "Fake:TTZToLLNuNu", "fakes", -1 );
    md.addDataCardSample( "Fake:TTWToLNu", "fakes", -1 );
    md.addDataCardSample( "Fake:WZTo3LNu", "fakes", -1 );
    md.addDataCardSample( "Fake:tZq_ll", "fakes", -1 );
    md.addDataCardSample( "Fake:VHToNonbb", "fakes", -1 );
    md.addDataCardSample( "Fake:GGHZZ4L", "fakes", -1 );
//    md.addDataCardSample( "Fake:ZZTo4L", "fakes", -1 );
    md.addDataCardSample( "Fake:WWZ", "fakes", -1 );
    md.addDataCardSample( "Fake:WZZ", "fakes", -1 );
    md.addDataCardSample( "Fake:ZZZ", "fakes", -1 );
    md.addDataCardSample( "Fake:TTTT", "fakes", -1 );

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

    md.addNuisanceParameter("jes","ttw:ttzh:ttzlowM:wz:xg:rares:"+sig,"shape","");
    md.addNuisanceParameter("btag","ttw:ttzh:ttzlowM:wz:xg:rares:"+sig,"shape","");
    md.addNuisanceParameter("pu","ttw:ttzh:ttzlowM:wz:xg:rares:"+sig,"shape","");
    md.addNuisanceParameter("fakes_EWK","fakes","shape","");

    //fastSim related uncertainties
    md.addNuisanceParameter("fs_btag",sig,"shape","");
    md.addNuisanceParameter("fs_lep",sig,"shape","");
	md.addNuisanceParameter("fs_hlt",sig,"shape","");
    md.addNuisanceParameter("isr",sig,"shape","");
    //md.addNuisanceParameter("XSFS",sig,"shape","");
	md.addNuisanceParameter("scale",sig,"shape","");

    md.addNuisanceParameter("ttw_extr_htl","ttw","shape","");
    md.addNuisanceParameter("ttw_extr_hth","ttw","shape","");
    md.addNuisanceParameter("ttzh_extr_htl","ttzh","shape","");
    md.addNuisanceParameter("ttzh_extr_hth","ttzh","shape","");
    md.addNuisanceParameter("ttz_lowM_extr_htl","ttzlowM","shape","");
    md.addNuisanceParameter("ttz_lowM_extr_hth","ttzlowM","shape","");
    md.addNuisanceParameter("wz_extr","wz","shape","");

    vector<string> vcategs;
    int nBins = 30;
    string categs[30]={
        "OnZSR001", "OnZSR002", "OnZSR003", "OnZSR004",
        "OnZSR005", "OnZSR006", "OnZSR007", "OnZSR008",
        "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012",
        "OnZSR013", "OnZSR014", "OnZSR015",
    
        "OffZSR001", "OffZSR002", "OffZSR003", "OffZSR004", 
        "OffZSR005", "OffZSR006", "OffZSR007", "OffZSR008", 
        "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012",
        "OffZSR013", "OffZSR014", "OffZSR015"
    };

    if(!onlyOneSR){
        for(int i=0;i<nBins;i++) {
            vcategs.push_back( categs[i] );
        }
    }
    else{
        nBins = 1;
        vcategs.push_back(categs[testSR-1]);
    }

 
    //Flat uncertanties =================================
    //lumi
    md.addNuisanceParameter("lumi","ttw:ttzh:ttzlowM:xg:rares:"+sig,"lnN","1.027:1.027:1.027:1.027:1.027:1.027");
    //experimental uncertainties
    md.addNuisanceParameter("HLTEff","ttw:ttzh:ttzlowM:xg:rares:"+sig,"lnN","1.03:1.03:1.03:1.03:1.03:1.03");
    md.addNuisanceParameter("LepEff","ttw:ttzh:ttzlowM:xg:rares:"+sig,"lnN","1.06:1.06:1.06:1.06:1.06:1.06"); //2% per lepton

    //Data-driven methods
    md.addNuisanceParameter("fakes","fakes","lnN","1.30");
    md.addNuisanceParameter("ra7_WZ","wz","lnN","1.15");

    //theoretical uncertainties

    //rare processes
    md.addNuisanceParameter("XG","xg","lnN","1.50");
    md.addNuisanceParameter("rares","rares","lnN","1.50");

    //pdf uncertainty
    md.addNuisanceParameter("ttw_pdf","ttw","lnN","1.03");
    md.addNuisanceParameter("ttzh_pdf","ttzh:ttZlowM","lnN","1.02:1.06");
    //md.addNuisanceParameter("ttHPdf","ttH","lnN","1.035");

    //x-section uncertainty
    md.addNuisanceParameter("TTW","ttw","lnN","1.13");
    md.addNuisanceParameter("TTZH","ttzh:ttzlowM","lnN","1.11:1.33");
    //md.addNuisanceParameter("ttHXs","ttH","lnN","1.09");


    //*********************************************************************²

    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
   
    md.prepareDisplay();
    
    //external uncertainties ===================================
    float AccTTWlowHT[30]={
        0.05, 0.05, 0.00, 0.00, 0.05, 
        0.05, 0.00, 0.00, 0.05, 0.05, 
        0.00, 0.00, 0.00, 0.00, 0.00,

        0.05, 0.05, 0.00, 0.00, 0.05, 
        0.05, 0.00, 0.00, 0.05, 0.05, 
        0.00, 0.00, 0.00, 0.00, 0.00
    };
 
    float AccTTWhighHT[30]={
        0.00, 0.00, 0.18, 0.18, 0.00, 
        0.00, 0.18, 0.18, 0.00, 0.00, 
        0.18, 0.18, 0.18, 0.18, 0.18,

        0.00, 0.00, 0.18, 0.18, 0.00, 
        0.00, 0.18, 0.18, 0.00, 0.00, 
        0.18, 0.18, 0.18, 0.18, 0.18
    };
  
    float AccTTZlowHT[30]={
        0.03, 0.03, 0.00, 0.00, 0.03, 
        0.03, 0.00, 0.00, 0.03, 0.03, 
        0.00, 0.00, 0.00, 0.00, 0.00, 

        0.05, 0.05, 0.00, 0.00, 0.05, 
        0.05, 0.00, 0.00, 0.05, 0.05, 
        0.00, 0.00, 0.00, 0.00, 0.00
    };
   
    float AccTTZhighHT[30]={
        0.00, 0.00, 0.05, 0.05, 0.00, 
        0.00, 0.05, 0.05, 0.00, 0.00, 
        0.05, 0.05, 0.05, 0.05, 0.05, 

        0.00, 0.00, 0.08, 0.08, 0.00, 
        0.00, 0.08, 0.08, 0.00, 0.00, 
        0.08, 0.08, 0.08, 0.08, 0.08
    };
    
    float AccTTZlowMlowHT[30]={
        0.03, 0.03, 0.00, 0.00, 0.03, 
        0.03, 0.00, 0.00, 0.03, 0.03, 
        0.00, 0.00, 0.00, 0.00, 0.00, 

        0.05, 0.05, 0.00, 0.00, 0.05, 
        0.05, 0.00, 0.00, 0.05, 0.05, 
        0.00, 0.00, 0.00, 0.00, 0.00
    }; 
 
    float AccTTZlowMhighHT[30]={
        0.00, 0.00, 0.05, 0.05, 0.00, 
        0.00, 0.05, 0.05, 0.00, 0.00, 
        0.05, 0.05, 0.05, 0.05, 0.05, 

        0.00, 0.00, 0.08, 0.08, 0.00, 
        0.00, 0.08, 0.08, 0.00, 0.00, 
        0.08, 0.08, 0.08, 0.08, 0.08
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
    //string dss[8]={sig,"xg","ttzh","ttzlowM","ttw","wz","rares","fakes"};
    string dss[8]={sig,"xg","ttzh","ttzlowM","ttw","wz","rares","fakes"};

    //statistical uncertainties for all processes
    for(int isr=0;isr<nBins;isr++) {
        for(size_t id=0;id<8;id++) {
            md.addNuisanceParameter(dss[id]+vcategs[isr]+"stat",dss[id],"shape","");
        }
    }

    for(int i=0;i<nBins;i++){
        vcategs[i] = "global_" + vcategs[i];
    }

    //Q2 background acceptance uncertainties 
    for(size_t ic=0;ic<nBins;ic++) {
        md.addExternalSystUnc("ttw"     ,"ttw_extr_htl"     ,AccTTWlowHT[ic]        , -1*AccTTWlowHT[ic]        , vcategs[ic], "selected");
        md.addExternalSystUnc("ttw"     ,"ttw_extr_hth"     ,AccTTWhighHT[ic]       , -1*AccTTWhighHT[ic]       , vcategs[ic], "selected");
        md.addExternalSystUnc("ttzh"    ,"ttzh_extr_htl"    ,AccTTZlowHT[ic]        , -1*AccTTZlowHT[ic]        , vcategs[ic], "selected");
        md.addExternalSystUnc("ttzh"    ,"ttzh_extr_hth"    ,AccTTZhighHT[ic]       , -1*AccTTZhighHT[ic]       , vcategs[ic], "selected");
        md.addExternalSystUnc("ttzlowM" ,"ttz_lowM_extr_htl",AccTTZlowMlowHT[ic]    , -1*AccTTZlowMlowHT[ic]    , vcategs[ic], "selected");
        md.addExternalSystUnc("ttzlowM" ,"ttz_lowM_extr_hth",AccTTZlowMhighHT[ic]   , -1*AccTTZlowMhighHT[ic]   , vcategs[ic], "selected");
        md.addExternalSystUnc("wz"      ,"wz_extr"          ,ExtrapolWZ[ic]         , -1*ExtrapolWZ[ic]         , vcategs[ic], "selected");
    }

   
    md.makeMultiDataCard(sig, vcategs, "selected", "ra7_"+sig);

    gROOT->ProcessLine(".qqqqqqqqqqqqqq");
}
