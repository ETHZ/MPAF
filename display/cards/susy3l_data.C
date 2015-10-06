//{

//    if(Recompute) {
//        MPAFDisplay md;
 
//        bool * rtmp= const_cast<bool*> pr;
//        *rtmp = false;

//    }
//    else 
//    md.refresh();

MPAFDisplay md;

void susy3l_data() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="3L_data"; //was treeName in LUNE susy_cut_lowpt
    string fileList="3L_data"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = false;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
    string obs ="zpeak";    //njets, nbjets, met, ht, lep, zpeak, mt2, pt, mll
    string sigs = "none"; 
    bool data = true;

    //observables **********************
    //string obs[6]={"","","","","",""};
    //md.dp.setObservables("Zmass");
    //md.dp.setObservables("deltaR_elmu");
    //md.dp.setObservables("BR_NJets");
    //md.dp.setObservables("BR_NBJets");
    //md.dp.setObservables("BR_HT");
    //md.dp.setObservables("BR_MET");
    //md.dp.setObservables("SR_NJets");
    //md.dp.setObservables("SR_NBJets");
    //md.dp.setObservables("SR_HT");
    //md.dp.setObservables("SR_MET");


    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    //double rangeX[2]={0,7};
    int xDiv[3]={8,6,0};
    int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
    bool logYScale=false;
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
        md.dp.setObservables("BR_NJets");
        int binning=1;
        double rangeX[2]={0,7};
    }
    if(obs == "nbjets"){
        md.dp.setObservables("BR_NBJets");
        int binning=1;
        double rangeX[2]={0,5};
    }
    if(obs == "met"){
        md.dp.setObservables("BR_MET");
        int binning=50;
        double rangeX[2]={0,500};
    }
    if(obs == "ht"){
        md.dp.setObservables("BR_HT");
        int binning=50;
        double rangeX[2]={0,800};
    }
    if(obs == "lep"){
        md.dp.setObservables("mu_multiplicity");
        md.dp.setObservables("el_multiplicity");
        md.dp.setObservables("tau_multiplicity");
        md.dp.setObservables("lep_multiplicity");
        int binning=1;
        double rangeX[2]={0,7};
        //bool logYScale=true;
    }
    if(obs == "zpeak"){
        md.dp.setObservables("Zmass");
        int binning=3;
        double rangeX[2]={0,200};
    }
    if(obs == "mt2"){
        md.dp.setObservables("MT2");
        int binning=10;
        double rangeX[2]={0,400};
        bool logYScale=true;
    }
    if(obs == "mt"){
        md.dp.setObservables("MT");
        int binning=10;
        double rangeX[2]={0,200};
        bool logYScale=true;
    }
    if(obs == "pt"){
        md.dp.setObservables("pt_1st_lepton");
        md.dp.setObservables("pt_2nd_lepton");
        md.dp.setObservables("pt_3rd_lepton");
        int binning=4;
        double rangeX[2]={0,200};
        bool logYScale=false;
    }
    if(obs == "mll"){
        md.dp.setObservables("lowMll");
        int binning=2;
        double rangeX[2]={0,400};
        bool logYScale=true;
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
    float lumi=42; //pb-1 19470
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
 

   
    md.anConf.addSample( "WZp8_50ns"                           ,  "WZ"              , kGreen    );
    md.anConf.addSample( "ZZp8_50ns"                           ,  "ZZ"              , kGreen+3  );

    //md.anConf.addSample( "TTZJets"                          ,  "t#bar{t}Z"          , kBlue     );

    //md.anConf.addSample( "TTWJets"                          ,  "t#bar{t}W"          , kYellow   );

    //md.anConf.addSample( "GGHZZ4L"                          ,  "rare SM"            , kCyan     );
    //md.anConf.addSample( "TTH"                              ,  "rare SM"             , kCyan      );

  //Drell-Yan
    //md.anConf.addSample( "DYJetsToLL_LO_M50_50ns"        ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "DYJetsToLL_M50_50ns"        ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "DYJetsToLL_M50_HT200to400"        ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "DYJetsToLL_M50_HT400to600"        ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "DYJetsToLL_M50_HT600toInf"        ,  "non-prompt e/#mu"    , kRed      );

  //t production
    //md.anConf.addSample( "TBarToLeptons_sch"                ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "TBarToLeptons_tch"                ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TBar_tWch_50ns"                        ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TTJets_LO_50ns"                           ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "TToLeptons_sch"                   ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "TToLeptons_tch_50ns"                   ,  "non-prompt e/#mu"    , kRed      );
    md.anConf.addSample( "T_tWch_50ns"                           ,  "non-prompt e/#mu"    , kRed      );

  //W+Jets
    md.anConf.addSample( "WJetsToLNu_50ns"            ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "WJetsToLNu_HT200to400"            ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "WJetsToLNu_HT400to600"            ,  "non-prompt e/#mu"    , kRed      );
    //md.anConf.addSample( "WJetsToLNu_HT600toInf"            ,  "non-prompt e/#mu"    , kRed      );

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
    md.anConf.addSample( "DoubleEG_Run2015B_17Jul2015_runs_251244_251562"       , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015B_v1_runs_251643_251883"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015B_17Jul2015_runs_251244_251562"     , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015B_v1_runs_251643_251883"            , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015B_17Jul2015_runs_251244_251562"         , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015B_v1_runs_251643_251883"                , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015B_17Jul2015_runs_251244_251562" , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015B_v1_runs_251643_251883"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015B_17Jul2015_runs_251244_251562"     , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015B_v1_runs_251643_251883"            , "data"          , kBlack    );
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
 
}
