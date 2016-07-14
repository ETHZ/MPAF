MPAFDisplay md;

void susy3l() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L_sync";
    string fileName="sync"; //was treeName in LUNE susy_cut_lowpt
    string fileList="sync"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = false;
    bool closure = false;
    bool fixLeg = true;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
    bool data = true;
    bool manual = true;
    if(!manual) string region = "REGION";
    else string region = "";

    if(!manual){string obs = "VARIABLE" ;}    //njets, nbjets, met, ht, lep, zpeak, zpt, mt, pt1, pt2, pt3, mll
    else{string obs = "lep3_charge";}
    
    string sigs;
    if(region=="OffZBaseline") sigs = "t"; 
    else if(region=="OnZBaseline") sigs = "q"; 
    else sigs = "non";
 

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
        double rangeX[2]={1,16};
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



    //string autoBinFile="susybinninghigh";
    //md.dp.loadAutoBinning(autoBinFile);

    //Systematic uncertainties ********************************
    bool addSystematics=true;
  
    bool mcStatSyst=true;
    string systSources="";

    bool uncDet=false;

    string Norm="";
  
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=2260; //pb-1 19470
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
 
    //rare
    md.anConf.addSample( "GGHZZ4L"                              ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "VHToNonbb"                            ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "ZZTo4L"                               ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "WWZ"                                  ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "WZZ"                                  ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "ZZZ"                                  ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "TTTT"                                 ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "tZq_ll"                               ,  "rare"        , kMagenta-7    );

    //WZ
    md.anConf.addSample( "WZTo3LNu"                             ,  "WZ"          , kOrange       );

    //X+gamma
    md.anConf.addSample( "TGJets"                               ,  "X+#gamma"    , kViolet+2     );
    md.anConf.addSample( "TTGJets"                              ,  "X+#gamma"    , kViolet+2     );
    md.anConf.addSample( "WGToLNuG"                             ,  "X+#gamma"    , kViolet+2     );
    md.anConf.addSample( "ZGTo2LG"                              ,  "X+#gamma"    , kViolet+2     );

    //TTZ/H
    md.anConf.addSample( "TTZToLLNuNu"                          ,  "t#bar{t}Z/H" , kGreen-6      );
    md.anConf.addSample( "TTHnobb"                              ,  "t#bar{t}Z/H" , kGreen-6      );
    md.anConf.addSample( "TTLLJets_m1to10"                      ,  "t#bar{t}Z/H" , kGreen-6      );
    
    //TTW
    md.anConf.addSample( "TTWToLNu"                             ,  "t#bar{t}W"   , kGreen+3      );
 
    //fakes
    md.anConf.addSample( "WJetsToLNu"                           ,  "non-prompt"       , 18     );
    
    md.anConf.addSample( "TbarToLeptons_tch"                    ,  "non-prompt"       , 18      );
    md.anConf.addSample( "TBar_tWch"                            ,  "non-prompt"       , 18      );
    md.anConf.addSample( "T_tWch"                               ,  "non-prompt"       , 18      );
    md.anConf.addSample( "TToLeptons_sch_amcatnlo"              ,  "non-prompt"       , 18      );
    md.anConf.addSample( "TToLeptons_tch"                       ,  "non-prompt"       , 18      );
    //md.anConf.addSample( "TTJets"                           ,  "fakes"       , 18      );
 
    md.anConf.addSample( "DYJetsToLL_M10to50"                   ,  "non-prompt"          , 18            );
    md.anConf.addSample( "DYJetsToLL_M50"                       ,  "non-prompt"          , 18            );
   
    md.anConf.addSample( "TT_pow"                               ,  "non-prompt"    , 18            );


    //signal
    if(sigs=="t"){
    md.anConf.addSample( "T1tttt_mGo1200_mChi800"                       ,  "T1tttt (1200) x10 sig"     , kBlue-3, 10 );
    md.anConf.addSample( "T1tttt_mGo1500_mChi100"                       ,  "T1tttt (1500) x10 sig"     , kBlue-3, 10 );
    md.anConf.addSample( "T6ttWW_mSbot600_mCh425_mChi50"                ,  "T6ttWW (600) x10 sig"     , kMagenta+2, 10 );
    md.anConf.addSample( "T6ttWW_mSbot650_mCh150_mChi50"                ,  "T6ttWW (650) x10 sig"     , kMagenta+2, 10 );
    //md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410 sig"     , kOrange+10  );
    }
    
    if(sigs=="q"){
    //md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4WZ315 sig"  , kGreen+2  );
    //md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4WZ325 sig"  , kMagenta  );
    md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_lep"       ,  "T5qqqqWZ (1200) x20 sig"   , kCyan+3, 20  );
    md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_lep"        ,  "T5qqqqWZ (1500) x20 sig"   , kCyan+3, 20  );
    //md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4ZZ315 sig"  , kGreen+3  );
    //md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4ZZ325 sig"  , kMagenta+2  );
    //md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4ZZ12 sig"   , kRed-9  );
    //md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4ZZ15 sig"   , kRed+1  );
    }
    
    //data
    if(data){
    md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_256630_257599"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_257600_258158"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_v4_runs_258159_258714_excl"         , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_v4_runs_258211_258750"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v3_runs_256630_257599"            , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v3_runs_257600_258158"            , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v4_runs_258159_258714_excl"       , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v4_runs_258211_258750"            , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v3_runs_256630_257599"                , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v3_runs_257600_258158"                , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v4_runs_258159_258714_excl"           , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v4_runs_258211_258750"                , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v3_runs_256630_257599"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v3_runs_257600_258158"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v4_runs_258159_258714_excl"   , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v4_runs_258211_258750"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v3_runs_256630_257599"            , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v3_runs_257600_258158"            , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v4_runs_258159_258714_excl"       , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v4_runs_258211_258750"            , "data"          , kBlack    );
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
             mcOnly,cmsPrel, uncDet, closure, fixLeg);
    md.prepareDisplay();
    md.doPlot();
    //md.doStatisticsPlot();
    md.savePlot("SUSY3L");
    // md.dp.addText(xt,yt,st,addText);
    if(!manual) gROOT->ProcessLine(".q");
 
}
