MPAFDisplay md;

void susy3lttV() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="3l_v2_scanBkg_TTW_LO"; //was treeName in LUNE susy_cut_lowpt
    string fileList="3l_v2_scanBkg_TTW_LO"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable

    //string fileName="merged_2fb_Bkg"; //was treeName in LUNE susy_cut_lowpt
    //string fileList="merged_2fb_Bkg"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
 

    string hName="";

    bool mcOnly = true;
    bool closure = false;
    bool nlo_vs_lo = true;
    bool fixLeg = true;
    bool printTable = false;

    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
    string sigs = "none"; 
    bool data = false;
    bool manual = true;
    if(!manual) string region = "REGION";
    else string region = "OffZBaseline";

    if(!manual){string obs = "VARIABLE" ;}    //njets, nbjets, met, ht, lep, zpeak, zpt, mt, pt1, pt2, pt3, mll
    else{string obs = "ht";}
     
    float lumi=10000; //pb-1 19470
    float energy=13; //TeV

    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    bool logYScale=true;
    //double rangeX[2]={0,7};
    int xDiv[3]={8,6,0};
    int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
    bool overFlowBin=true;
    bool underFlowBin=false;
    bool showDMCRatio=true;
    bool showGrid=false;
    float markerSize=0.8;
    float lineWidth=2;

    bool summedSignal=false;
    bool stacking=true;

    bool cmsPrel=true;

    float xt=0.68;
    float yt=0.48;
    float st=0.039;
    string addText="";

    if(obs == "njets"){
        md.dp.setObservables("NJets" + region);
        int binning=1;
        if(region=="WZCR" || region == "FakeCR"){double rangeX[2]={0,4};bool logYScale=false;}
        else{double rangeX[2]={2,10};}
        //bool logYScale=true;
    }
    if(obs == "nbjets"){
        md.dp.setObservables("NBJets" + region);
        int binning=1;
        if(region=="WZCR" || region == "FakeCR"){double rangeX[2]={0,5};bool logYScale=false;}
        else{double rangeX[2]={0,5};}
        //bool logYScale=true;
    }
    if(obs == "met"){
        md.dp.setObservables("MET" + region);
        if(region=="WZCR" || region == "FakeCR"){int binning=10; double rangeX[2]={0,120};bool logYScale=false;}
        else{int binning=50; double rangeX[2]={0,500};}
        //bool logYScale=true;
    }
    if(obs == "ht"){
        md.dp.setObservables("HT" + region);
        if(region=="WZCR"){int binning=50; double rangeX[2]={0,200};bool logYScale=false;}
        else if(region=="FakeCR"){int binning=50; double rangeX[2]={0,400};bool logYScale=false;}
        else{int binning=60; double rangeX[2]={0,960};}
        //bool logYScale=true;
    }
    if(obs == "mt"){
        if(region!="WZCR"){gROOT->ProcessLine(".q");}
        md.dp.setObservables("MT" + region);
        int binning=10;
        double rangeX[2]={0,200};
        bool logYScale=false;
    }
    if(obs == "pt1"){
        md.dp.setObservables("pt_1st_lepton" + region);
        if(region=="WZCR"){int binning=10;}
        else int binning=20;
        double rangeX[2]={0,200};
        //bool logYScale=true;
    }
    if(obs == "pt2"){
        md.dp.setObservables("pt_2nd_lepton" + region);
        if(region=="WZCR"){int binning=10;}
        else int binning=20;
        double rangeX[2]={0,150};
        //bool logYScale=true;
    }   
    if(obs == "pt3"){
        md.dp.setObservables("pt_3rd_lepton" + region);
        if(region=="WZCR"){int binning=10;}
        else int binning=20;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "ftype"){
        md.dp.setObservables("fake_type" + region);
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "flavor"){
        md.dp.setObservables("flavor" + region);
        int binning=1;
        double rangeX[2]={0,4};
        //bool logYScale=true;
    }
    if(obs == "srs"){
        md.dp.setObservables("SRS" + region);
        int binning=1;
        double rangeX[2]={1,18};
        bool logYScale=false;
    }
    if(obs == "mu_multi"){
        md.dp.setObservables("mu_multiplicity" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "el_multi"){
        md.dp.setObservables("el_multiplicity" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "lep_multi"){
        md.dp.setObservables("lep_multiplicity" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "nfo"){
        md.dp.setObservables("nFO" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "lep1dxy"){
        md.dp.setObservables("lep1_dxy" + region);
        int binning=20;
        double rangeX[2]={-150,150};
        //bool logYScale=true;
    }
    if(obs == "lep1dz"){
        md.dp.setObservables("lep1_dz" + region);
        int binning=20;
        double rangeX[2]={-200,200};
        //bool logYScale=true;
    }
    if(obs == "lep1sip"){
        md.dp.setObservables("lep1_SIP3D" + region);
        int binning=20;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "lep2dxy"){
        md.dp.setObservables("lep2_dxy" + region);
        int binning=20;
        double rangeX[2]={-150,150};
        //bool logYScale=true;
    }
    if(obs == "lep2dz"){
        md.dp.setObservables("lep2_dz" + region);
        int binning=20;
        double rangeX[2]={-200,200};
        //bool logYScale=true;
    }
    if(obs == "lep2sip"){
        md.dp.setObservables("lep2_SIP3D" + region);
        int binning=20;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "lep3dxy"){
        md.dp.setObservables("lep3_dxy" + region);
        int binning=20;
        double rangeX[2]={-150,150};
        //bool logYScale=true;
    }
    if(obs == "lep3dz"){
        md.dp.setObservables("lep3_dz" + region);
        int binning=20;
        double rangeX[2]={-200,200};
        //bool logYScale=true;
    }
    if(obs == "lep3sip"){
        md.dp.setObservables("lep3_SIP3D" + region);
        int binning=20;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "lep3_charge"){
        md.dp.setObservables("chargeMult_3lep" + region);
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "lep4_charge"){
        md.dp.setObservables("chargeMult_4lep" + region);
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }


    //string autoBinFile="susybinninghigh";
    //md.dp.loadAutoBinning(autoBinFile);

    //Systematic uncertainties ********************************
    bool addSystematics=true;
  
    bool mcStatSyst=true;
    string systSources="";

    bool uncDet=false;

    string Norm="";
  
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    bool useXS=false;

    md.anConf.loadXSDB("XSectionsSpring16.db");
    
    map<string,float> LumisXS;
    
    md.anConf.loadKFDB("kFactorsSpring16.db");
    
    //via XSect
  
    map<string,float> KFactors;
    // if( md.isInitStatus() )
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

    
    float scale = 1.0;    
    
    //===============================================================
    // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
    //if( md.isInitStatus() ) {
/*
    //rare
    md.anConf.addSample( "GGHZZ4L"                              ,  "rare"        , kMagenta-7, scale    );
    md.anConf.addSample( "VHToNonbb"                            ,  "rare"        , kMagenta-7, scale   );
    md.anConf.addSample( "ZZTo4L"                               ,  "rare"        , kMagenta-7, scale    );
    md.anConf.addSample( "WWZ"                                  ,  "rare"        , kMagenta-7, scale    );
    md.anConf.addSample( "WZZ"                                  ,  "rare"        , kMagenta-7, scale    );
    md.anConf.addSample( "ZZZ"                                  ,  "rare"        , kMagenta-7, scale    );
    md.anConf.addSample( "TTTT"                                 ,  "rare"        , kMagenta-7, scale    );
    md.anConf.addSample( "tZq_ll"                               ,  "rare"        , kMagenta-7, scale    );

    //WZ
    md.anConf.addSample( "WZTo3LNu"                             ,  "WZ"          , kOrange, scale       );

    //X+gamma
    md.anConf.addSample( "TGJets"                               ,  "X+#gamma"    , kViolet+2, scale     );
    md.anConf.addSample( "TTGJets"                              ,  "X+#gamma"    , kViolet+2, scale    );
    md.anConf.addSample( "WGToLNuG"                             ,  "X+#gamma"    , kViolet+2, scale      );
    md.anConf.addSample( "ZGTo2LG"                              ,  "X+#gamma"    , kViolet+2, scale     );

    //md.anConf.addSample( "TGJets"                               ,  "TG"    , kMagenta     );
    //md.anConf.addSample( "WGToLNuG"                             ,  "WG"    , kMagenta+2     );
    //md.anConf.addSample( "ZGTo2LG"                              ,  "ZG"    , kBlue-10     );
    //md.anConf.addSample( "TTGJets"                              ,  "TTG"   , kBlue     );

*/


    //TTZ/H
    //md.anConf.addSample( "TTZ_LO"                               ,  "t#bar{t}Z LO"   , kGreen-6, scale      );
    //md.anConf.addSample( "TTZToLLNuNu"                          ,  "pseudodata"     , kBlack  , scale      );
    //md.anConf.addSample( "TTHnobb_pow"                          ,  "t#bar{t}Z/H" , kGreen-6, scale      );
    //md.anConf.addSample( "TTLLJets_m1to10"                      ,  "t#bar{t}Z/H" , kGreen-6, scale      );
    
    //TTW
    md.anConf.addSample( "TTW_LO"                               ,  "t#bar{t}W LO"   , kGreen+3, scale      );
    //md.anConf.addSample( "TTWToLNu"                             ,  "pseudodata"  , kBlack  , scale      );
/*

    //non-prompt
    //md.anConf.addSample( "TTJets"                               ,  "non-prompt"       , 18            );
    //md.anConf.addSample( "DYJetsToLL_M10to50"                   ,  "non-prompt"       , 18            );
    //md.anConf.addSample( "DYJetsToLL_M50"                       ,  "non-prompt"       , 18            );
    //md.anConf.addSample( "TToLeptons_sch"                       ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "TToLeptons_tch_powheg"                ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "TBarToLeptons_tch_powheg"             ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "TBar_tWch"                            ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "T_tWch"                               ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "WJetsToLNu"                           ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "WWTo2L2Nu"                            ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "ZZTo2L2Nu"                            ,  "non-prompt"       , 18      );

*/



    //non-prompt
/*    md.anConf.addSample( "TTJets"                               ,  "TT"       , kBlue-10            );
    md.anConf.addSample( "DYJetsToLL_M10to50"                   ,  "DY"       , kBlue-7            );
    md.anConf.addSample( "DYJetsToLL_M50"                       ,  "DY"       , kBlue-7            );
    md.anConf.addSample( "TToLeptons_sch"                       ,  "single top"       , kCyan      );
    md.anConf.addSample( "TToLeptons_tch_powheg"                ,  "single top"       , kCyan      );
    md.anConf.addSample( "TBarToLeptons_tch_powheg"             ,  "single top"       , kCyan      );
    md.anConf.addSample( "TBar_tWch"                            ,  "single top"       , kCyan      );
    md.anConf.addSample( "T_tWch"                               ,  "single top"       , kCyan      );
    md.anConf.addSample( "WJetsToLNu"                           ,  "WJets"       , 18      );
    md.anConf.addSample( "WWTo2L2Nu"                            ,  "other"       , kBlue+3      );
    md.anConf.addSample( "ZZTo2L2Nu"                            ,  "other"       , kBlue+3      );
*/

    //non-prompt predicted
    //md.anConf.addSample( "data:_Fake:DoubleEG_Run2016B_PromptReco_v2_runs_273150_274443"      , "non-prompt"          , 18, scale    );
    //md.anConf.addSample( "data:_Fake:DoubleMuon_Run2016B_PromptReco_v2_runs_273150_274443"    , "non-prompt"          , 18, scale    );
    //md.anConf.addSample( "data:_Fake:MuonEG_Run2016B_PromptReco_v2_runs_273150_274443"        , "non-prompt"          , 18, scale    );

    //signal
    if(sigs=="t"){
    md.anConf.addSample( "T1tttt_mGo1200_mChi800"                       ,  "T1tttt (1200) x10 sig"     , kBlue-3, 10 );
    md.anConf.addSample( "T1tttt_mGo1500_mChi100"                       ,  "T1tttt (1500) x10 sig"     , kBlue-3, 10  );
    //md.anConf.addSample( "T6ttWW_mSbot600_mCh425_mChi50"                ,  "T6ttWW (600) x10 sig"     , kMagenta+2 );
    //md.anConf.addSample( "T6ttWW_mSbot650_mCh150_mChi50"                ,  "T6ttWW (650) x10 sig"     , kMagenta+2 );
    //md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410 sig"     , kOrange+10  );
    }
    
    if(sigs=="q"){
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4WZ315 sig"  , kGreen+2  );
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4WZ325 sig"  , kMagenta  );
    md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4WZ12 sig"   , kRed-6  );
    md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4WZ15 sig"   , kRed+3  );
    //md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4ZZ315 sig"  , kGreen+3  );
    //md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4ZZ325 sig"  , kMagenta+2  );
    //md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4ZZ12 sig"   , kRed-9  );
    //md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4ZZ15 sig"   , kRed+1  );
    }
    
    //data
    if(data){
    md.anConf.addSample( "DoubleEG_Run2016B_PromptReco_v2_runs_273150_274443"      , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2016B_PromptReco_v2_runs_273150_274443"    , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2016B_PromptReco_v2_runs_273150_274443"        , "data"          , kBlack    );
    //md.anConf.addSample( "DoubleEG_Run2016B_PromptReco_v2_runs_274444_275125"      , "data"          , kBlack    );
    //md.anConf.addSample( "DoubleMuon_Run2016B_PromptReco_v2_runs_274444_275125"    , "data"          , kBlack    );
    //md.anConf.addSample( "MuonEG_Run2016B_PromptReco_v2_runs_274444_275125"        , "data"          , kBlack    );
    }


    //===============================================================

    //*********************************************************************²
    //Execution macro ******************************************************
 
    //Configuration ================
    //if( md.isInitStatus() ) {
  
    //md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
   
    // }
    
    
   string categs[32]={
        "OnZSR001", "OnZSR002", "OnZSR003", "OnZSR004",
        "OnZSR005", "OnZSR006", "OnZSR007", "OnZSR008",
        "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012",
        "OnZSR013", "OnZSR014", "OnZSR015", "OnZSR016", "OnZSR017",
    
        "OffZSR001", "OffZSR002", "OffZSR003", "OffZSR004", 
        "OffZSR005", "OffZSR006", "OffZSR007", "OffZSR008", 
        "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012",
        "OffZSR013", "OffZSR014", "OffZSR016"
    };


    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
    md.dp.setNormalization( Norm );
    md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal,
             mcOnly,cmsPrel, uncDet, closure, nlo_vs_lo, fixLeg);
    md.prepareDisplay();
    
    //external systematic uncertainties
    //md.addExternalSystUnc("WZ","test",0.50,-0.50 ,"global_OnZSR001" , "selected");

    md.doPlot();
    // md.doStatisticsPlot();
       
    
    md.getIntegral(0,400);
    md.getIntegral(400,600);
    md.getIntegral(600,10000);
    
    
    if(printTable){
    //print result table
    cout << "______________________________________________" <<endl;
    cout << "On-Z:" << endl;
    for(int i=0;i<17;i++){
        string sr= "global_";
        sr += categs[i];
        if(i==0) md.getStatistics(sr, true, true);
        else md.getStatistics(sr, true, false);
    }
    cout << "______________________________________________" <<endl;
    cout << "Off-Z:" << endl;
    for(int i=0;i<15;i++){
        string sr= "global_";
        sr += categs[i+17];
        if(i==0) md.getStatistics(sr, true, true);
        else md.getStatistics(sr, true, false);
    }
    }

    //md.getStatistics("global_OnZSR001");
    
    md.savePlot("SUSY3L");
    // md.dp.addText(xt,yt,st,addText);
    if(!manual) gROOT->ProcessLine(".q");
 
}
