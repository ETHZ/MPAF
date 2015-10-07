MPAFDisplay md;

void susy3l_data_25ns() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    //string fileName="3L_data_25ns"; //was treeName in LUNE susy_cut_lowpt
    string fileName="multiLep_OffZ"; //was treeName in LUNE susy_cut_lowpt
    //string fileList="3L_data_25ns"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string fileList="multiLep_OffZ"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = false;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
    string obs = "VARIABLE" ;    //njets, nbjets, met, ht, lep, zpeak, zpt, mt, mt2, pt1, pt2, pt3, mll, muonsip, muoniso, muondz, muondxy, muonptrel, muonptratio, elsip, eliso, eldz, eldxy, elptrel, elptratio
    string sigs = "none"; 
    bool data = true;

    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    bool logYScale=true;
    //double rangeX[2]={0,7};
    int xDiv[3]={8,6,0};
    int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
    bool logYScale=true;
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
        md.dp.setObservables("NJets");
        int binning=1;
        double rangeX[2]={0,7};
        //bool logYScale=true;
    }
    if(obs == "nbjets"){
        md.dp.setObservables("NBJets");
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "met"){
        md.dp.setObservables("MET");
        int binning=50;
        double rangeX[2]={0,500};
        //bool logYScale=true;
    }
    if(obs == "ht"){
        md.dp.setObservables("HT");
        int binning=0;
        double rangeX[2]={0,1000};
        //bool logYScale=true;
    }
    if(obs == "njets_wzcr"){
        md.dp.setObservables("NJetsWZCR");
        int binning=1;
        double rangeX[2]={0,7};
        //bool logYScale=true;
    }
    if(obs == "nbjets_wzcr"){
        md.dp.setObservables("NBJetsWZCR");
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "met_wzcr"){
        md.dp.setObservables("METWZCR");
        int binning=50;
        double rangeX[2]={0,500};
        //bool logYScale=true;
    }
    if(obs == "wzcr_ht"){
        md.dp.setObservables("HTWZCR");
        int binning=0;
        double rangeX[2]={0,1000};
        //bool logYScale=true;
    }
    if(obs == "lep"){
        //md.dp.setObservables("mu_multiplicity");
        //md.dp.setObservables("el_multiplicity");
        //md.dp.setObservables("tau_multiplicity");
        md.dp.setObservables("lep_multiplicity");
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "zpeak"){
        md.dp.setObservables("Zmass");
        int binning=2;
        double rangeX[2]={60,120};
        bool logYScale=false;
    }
    if(obs == "zpt"){
        md.dp.setObservables("Zpt");
        int binning=10;
        double rangeX[2]={0,200};
    }
    if(obs == "mt2"){
        md.dp.setObservables("MT2");
        int binning=0;
        double rangeX[2]={0,400};
        //bool logYScale=true;
    }
    if(obs == "mt"){
        md.dp.setObservables("MT");
        int binning=0;
        double rangeX[2]={0,200};
        //bool logYScale=true;
    }
    if(obs == "pt1"){
        md.dp.setObservables("pt_1st_lepton");
        int binning=0;
        double rangeX[2]={0,200};
        //bool logYScale=true;
    }
    if(obs == "pt2"){
        md.dp.setObservables("pt_2nd_lepton");
        int binning=0;
        double rangeX[2]={0,150};
        //bool logYScale=true;
    }   
    if(obs == "pt3"){
        md.dp.setObservables("pt_3rd_lepton");
        int binning=0;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "mll"){
        md.dp.setObservables("lowMll");
        int binning=0;
        double rangeX[2]={0,400};
        //bool logYScale=true;
    }
    if(obs == "muonsip"){
        md.dp.setObservables("muon_SIP3d");
        int binning=0;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "muoniso"){
        md.dp.setObservables("muon_miniRelIso");
        int binning=0;
        double rangeX[2]={0,0.4};
        //bool logYScale=true;
    }
    if(obs == "muondz"){
        md.dp.setObservables("muon_dz");
        int binning=0;
        double rangeX[2]={0,600};
        //bool logYScale=true;
    }
    if(obs == "muondxy"){
        md.dp.setObservables("muon_dxy");
        int binning=0;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "muonptrel"){
        md.dp.setObservables("muon_JetPtRel");
        int binning=0;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "muonptratio"){
        md.dp.setObservables("muon_JetPtRatio");
        int binning=0;
        double rangeX[2]={0,1.3};
        //bool logYScale=true;
    }
    if(obs == "elsip"){
        md.dp.setObservables("el_SIP3d");
        int binning=0;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "eliso"){
        md.dp.setObservables("el_miniRelIso");
        int binning=0;
        double rangeX[2]={0,0.4};
        //bool logYScale=true;
    }
    if(obs == "eldz"){
        md.dp.setObservables("el_dz");
        int binning=0;
        double rangeX[2]={0,600};
        //bool logYScale=true;
    }
    if(obs == "eldxy"){
        md.dp.setObservables("el_dxy");
        int binning=0;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "elptrel"){
        md.dp.setObservables("el_JetPtRel");
        int binning=0;
        double rangeX[2]={0,40};
        //bool logYScale=true;
    }
    if(obs == "elptratio"){
        md.dp.setObservables("el_JetPtRatio");
        int binning=0;
        double rangeX[2]={0,1.3};
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
    float lumi=121.6; //pb-1 19470
    float energy=13; //TeV

    bool useXS=false;

    md.anConf.loadXSDB("XSectionsSpring15.db");
    
    map<string,float> LumisXS;
    
    md.anConf.loadKFDB("kFactorsSpring15.db");
    
    //via XSect
  
    map<string,float> KFactors;
    // if( md.isInitStatus() )
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

    
    
    
    //===============================================================
    // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
    //if( md.isInitStatus() ) {
 
    md.anConf.addSample( "TTWToLNu"                          ,  "t#bar{t}W"          , kYellow   );
    md.anConf.addSample( "TTZToLLNuNu"                          ,  "t#bar{t}Z"          , kBlue     );
   
    md.anConf.addSample( "WZp8"                           ,  "WZ"              , kGreen    );
    md.anConf.addSample( "ZZp8"                           ,  "ZZ"              , kGreen+3  );

    //md.anConf.addSample( "GGHZZ4L"                          ,  "rare SM"            , kCyan     );
    //md.anConf.addSample( "TTH"                              ,  "rare SM"             , kCyan      );

  //t production
    //md.anConf.addSample( "TBarToLeptons_sch"                ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "TBarToLeptons_tch"                ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TBar_tWch"                        ,  "TW"    , kRed+3      );
    md.anConf.addSample( "TT_pow"                        ,  "TT"    , kRed+2      );
    md.anConf.addSample( "TToLeptons_sch"                   ,  "TT"    , kRed+2      );
    md.anConf.addSample( "TToLeptons_tch"                   ,  "TT"    , kRed+2      );
    md.anConf.addSample( "T_tWch"                           ,  "TW"    , kRed+3      );

  //W+Jets
    md.anConf.addSample( "WJetsToLNu"            ,  "WJets"    , kRed-6      );
    //md.anConf.addSample( "WJetsToLNu_HT200to400"            ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "WJetsToLNu_HT400to600"            ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "WJetsToLNu_HT600toInf"            ,  "non-prompt e/#mu"    , kRed      );

  //Drell-Yan
    //md.anConf.addSample( "DYJetsToLL_LO_M50_50ns"        ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "DYJetsToLL_M10to50"          ,  "DY"    , kRed     );
    md.anConf.addSample( "DYJetsToLL_M50"              ,  "DY"    , kRed     );
    //md.anConf.addSample( "DYJetsToLL_M50_HT200to400"        ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "DYJetsToLL_M50_HT400to600"        ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "DYJetsToLL_M50_HT600toInf"        ,  "non-prompt e/#mu"    , kRed      );


  //signal
    if(sigs=="t"){
    md.anConf.addSample( "SMS_T1tttt_2J_mGl1200_mLSP800"                ,  "T1t412 sig"     , kBlue-3 );
    md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100"                ,  "T1t415 sig"     , kBlue-7  );
    md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410 sig"     , kOrange+10  );
    }
    if(sigs=="q"){
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4WZ315 sig"  , kGreen+2  );
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4WZ325 sig"  , kMagenta  );
    md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4WZ12 sig"   , kRed-6  );
    md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4WZ15 sig"   , kRed+3  );
    md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4ZZ315 sig"  , kGreen+3  );
    md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4ZZ325 sig"  , kMagenta+2  );
    md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4ZZ12 sig"   , kRed-9  );
    md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4ZZ15 sig"   , kRed+1  );
    }
    
  //data
    if(data){
    md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_256630_256843"       , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v3_runs_256630_256843"              , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v3_runs_256630_256843"     , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v3_runs_256630_256843"            , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v3_runs_256630_256843"            , "data"          , kBlack    );
    }


//    md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_skim"  ,  "T5tttt (1000) * 20 sig" , kOrange-3 );
  //md.anConf.addSample( "T5ttttDeg_mGo1300_mStop300_mCh285_mChi280_skim"  ,  "T5tttt (1300) #cdot 20 sig" , kOrange+6 );
    // }
    //===============================================================

    //*********************************************************************²
    //Execution macro ******************************************************
 
    //Configuration ================
    //if( md.isInitStatus() ) {
  
    //md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
   
    // }

    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
    md.dp.setNormalization( Norm );
    md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal,
             mcOnly,cmsPrel, uncDet);
    md.prepareDisplay();
    md.doPlot();
    //md.doStatisticsPlot();
    md.savePlot("SUSY3L");
    // md.dp.addText(xt,yt,st,addText);
 
    gROOT->ProcessLine(".q");
}
