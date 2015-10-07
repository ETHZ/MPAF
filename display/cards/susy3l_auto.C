{

    if(Recompute) {
        MPAFDisplay md;

        bool * rtmp= const_cast<bool*> pr;
        *rtmp = false;

    }
    else 
    md.refresh();




    string signal = "SIGNALMOD" ;
    //string signal = "T1t412";
    //string signal = "T1t415";
    //string signal = "T5t410";
    //string signal = "T5q4WZ315";
    //string signal = "T5q4WZ325";
    //string signal = "T5q4WZ12";
    //string signal = "T5q4WZ15";
    //string signal = "T5q4ZZ315";
    //string signal = "T5q4ZZ325";
    //string signal = "T5q4ZZ12";
    //string signal = "T5q4ZZ15";


    //general parameters ********************* general parameters
    string dir="SUSY3L";    // directory in workdir/stats
    string fileName="susy3l_SIGNALREGION_PAIRSTATE";
    string fileList="susy3l_SIGNALREGION_PAIRSTATE"; 
    string hName="";

    bool mcOnly = false;
  
    md.anConf.configureNames( dir, fileName, fileList);
    md.anConf.configureData(false, 0, mcOnly);
 

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
    int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    double rangeX[2]={0,7};
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

    //string autoBinFile="susybinninghigh";
    //md.dp.loadAutoBinning(autoBinFile);




    //Systematic uncertainties ********************************
    bool addSystematics=true;
  
    bool mcStatSyst=true;
    string systSources="";

    bool uncDet=false;

    string Norm="";
  
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=3000; //pb-1 19470
    float energy=13; //TeV

    bool useXS=false;

    md.anConf.loadXSDB("XSectionsPhys14.db");

    map<string,float> LumisXS;

    md.anConf.loadKFDB("kFactorsPhys14.db");
 
    //via XSect
    map<string,float> KFactors;
    
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

    //===============================================================
    
    md.anConf.addSample( "WZJetsTo3LNu"                     ,  "diboson"            , kGreen    );
    md.anConf.addSample( "ZZTo4L"                           ,  "diboson"            , kGreen    );

    md.anConf.addSample( "TTZJets"                          ,  "ttZ"                , kBlue     );

    md.anConf.addSample( "TTWJets"                          ,  "ttW"                , kYellow   );
    
    md.anConf.addSample( "TTH"                              ,  "rare"               , kCyan     );
    md.anConf.addSample( "GGHZZ4L"                          ,  "rare"               , kCyan     );
    
    //Drell-Yan
    md.anConf.addSample( "DYJetsToLL_M50_HT100to200"        ,  "fake"   , kRed      );
    md.anConf.addSample( "DYJetsToLL_M50_HT200to400"        ,  "fake"    , kRed      );
    md.anConf.addSample( "DYJetsToLL_M50_HT400to600"        ,  "fake"    , kRed      );
    md.anConf.addSample( "DYJetsToLL_M50_HT600toInf"        ,  "fake"    , kRed      );
    
    //t production
    md.anConf.addSample( "TBarToLeptons_sch"                ,  "fake"    , kRed      );
    md.anConf.addSample( "TBarToLeptons_tch"                ,  "fake"    , kRed      );
    md.anConf.addSample( "TBar_tWch"                        ,  "fake"    , kRed      );
    md.anConf.addSample( "TTJets"                           ,  "fake"    , kRed      );
    md.anConf.addSample( "TToLeptons_sch"                   ,  "fake"    , kRed      );
    md.anConf.addSample( "TToLeptons_tch"                   ,  "fake"    , kRed      );
    md.anConf.addSample( "T_tWch"                           ,  "fake"    , kRed      );
    
    //W+Jets
    md.anConf.addSample( "WJetsToLNu_HT100to200"            ,  "fake"    , kRed      );
    md.anConf.addSample( "WJetsToLNu_HT200to400"            ,  "fake"    , kRed      );
    md.anConf.addSample( "WJetsToLNu_HT400to600"            ,  "fake"    , kRed      );
    md.anConf.addSample( "WJetsToLNu_HT600toInf"            ,  "fake"    , kRed      );
    
    //signal
    if(signal=="T1t412"){
        md.anConf.addSample( "SMS_T1tttt_2J_mGl1200_mLSP800"    ,  "T1t412" , kViolet-3 );
    }
    if(signal=="T1t415"){
        md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100"    ,  "T1t415" , kOrange+3  );
    }
    if(signal=="T5t410"){
        md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410" , kGreen+3  );
    }
    if(signal=="T5q4WZ315"){
        md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"    ,  "T5q4WZ315" , kGreen+3  );
    }
    if(signal=="T5q4WZ325"){
        md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"    ,  "T5q4WZ325" , kGreen+3  );
    }
    if(signal=="T5q4WZ12"){
        md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"    ,  "T5q4WZ12" , kGreen+3  );
    }
    if(signal=="T5q4WZ15"){
        md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"    ,  "T5q4WZ15" , kGreen+3  );
    }
    if(signal=="T5q4ZZ315"){
        md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"    ,  "T5q4ZZ315" , kGreen+3  );
    }
    if(signal=="T5q4ZZ325"){
        md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"    ,  "T5q4ZZ325" , kGreen+3  );
    }
    if(signal=="T5q4ZZ12"){
        md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"    ,  "T5q4ZZ12" , kGreen+3  );
    }
    if(signal=="T5q4ZZ15"){
        md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"    ,  "T5q4ZZ15" , kGreen+3  );
    }




    md.addNuisanceParameter("fratio","fake","lnN","1.50");
    md.addNuisanceParameter("rNorm1","diboson","lnN","1.20");
    md.addNuisanceParameter("rNorm2","ttZ","lnN","1.20");
    md.addNuisanceParameter("rNorm3","ttW","lnN","1.20");
    md.addNuisanceParameter("rNorm4","rare","lnN","1.20");
    md.addNuisanceParameter("sigNorm",signal,"lnN","1.10");

   
    
    //===============================================================

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

    md.makeSingleDataCard(signal, "global", "SR MET selection", fileList+"_"+signal);


    //md.doStatisticsPlot();
    //md.savePlot("SUSY3L");
    // md.dp.addText(xt,yt,st,addText);
    
    gROOT->ProcessLine(".q");
}
