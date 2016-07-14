MPAFDisplay md;

void susy3l_tt_closure() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="3l_closure"; //was treeName in LUNE susy_cut_lowpt
    string fileList="3l_closure"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = true;
    bool closure = true;
    bool nlo_vs_lo = false;
    bool fixLeg = true;
    bool scale = true;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
   
    string sigs = "none"; 
    bool data = false;
    bool manual = true;
    if(!manual){string region = "REGION";}
    else string region = "OnZBaseline";

    if(!manual){string obs = "VARIABLE" ;}    //njets, nbjets, met, ht, lep, zpeak, zpt, mt, pt1, pt2, pt3, mll
    else{string obs = "met";}
 
    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    bool logYScale=false;
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
        double rangeX[2]={2,10};
        //bool logYScale=true;
    }
    if(obs == "nbjets"){
        md.dp.setObservables("NBJets" + region);
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "met"){
        md.dp.setObservables("MET" + region);
        int binning=50;
        double rangeX[2]={0,350};
        //bool logYScale=true;
    }
    if(obs == "ht"){
        md.dp.setObservables("HT" + region);
        int binning=60;
        double rangeX[2]={0,1000};
        //bool logYScale=true;
    }
    if(obs == "pt1"){
        md.dp.setObservables("pt_1st_lepton" + region);
        int binning=10;
        double rangeX[2]={0,200};
        //bool logYScale=true;
    }
    if(obs == "pt2"){
        md.dp.setObservables("pt_2nd_lepton" + region);
        int binning=10;
        double rangeX[2]={0,150};
        //bool logYScale=true;
    }   
    if(obs == "pt3"){
        md.dp.setObservables("pt_3rd_lepton" + region);
        int binning=10;
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
        //bool logYScale=true;
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
    if(obs == "fake_type"){
        md.dp.setObservables("fake_type" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "weights"){
        md.dp.setObservables("applWeight" + region);
        int binning=1;
        double rangeX[2]={-.5,1.5};
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
    float lumi=10000; //pb-1 19470
    float energy=13; //TeV

    bool useXS=true;

    md.anConf.loadXSDB("XSectionsSpring16.db");
    
    map<string,float> LumisXS;
    
    md.anConf.loadKFDB("kFactorsSpring16.db");
    
    //via XSect
  
    map<string,float> KFactors;
    // if( md.isInitStatus() )
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

    if(scale){
        float scaleWJets = 154506.056;
        float scaleDY10 = 30156.34;
        float scaleDY50 = 15704.55;
        float scaleTTJets = 2120.02;
        float scaleTToLeptons_sch = 3.38;
    }
    else{
        float scaleWJets = 1;
        float scaleDY10 = 1;
        float scaleDY50 = 1;
        float scaleTTJets = 1;
    }
    
    //===============================================================
    // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
    //if( md.isInitStatus() ) {

    //single top
//    md.anConf.addSample( "TbarToLeptons_tch"                    ,  "single top"    , kCyan      );
    md.anConf.addSample( "TBar_tWch"                            ,  "single top"    , kCyan      );
    md.anConf.addSample( "T_tWch"                               ,  "single top"    , kCyan      );
//    md.anConf.addSample( "TToLeptons_sch_amcatnlo"              ,  "single top"    , kCyan      );
    md.anConf.addSample( "TToLeptons_sch"                       ,  "single top"    , kCyan, scaleTToLeptons_sch   );
  
    //W+Jets
    //md.anConf.addSample( "WJetsToLNu"                           ,  "W+jets"    , kBlue, scaleWJets      );

    //ttbar
    md.anConf.addSample( "TTJets"                             ,  "t#bar{t}"    , kBlue-10, scaleTTJets      );

    //Drell-Yan
    md.anConf.addSample( "DYJetsToLL_M10to50"                   ,  "DY"    , kBlue-7, scaleDY10     );
    md.anConf.addSample( "DYJetsToLL_M50"                       ,  "DY"    , kBlue-7, scaleDY50     );


//    md.anConf.addSample( "TTJets_DiLepton"                      ,  "TT"    , kRed-6      );
    //md.anConf.addSample( "_Fake:TTJets_DiLepton"                 ,  "pseudodata"    , kBlack      );


//    md.anConf.addSample( "_Fake:TbarToLeptons_tch"               ,  "pseudodata"    , kBlack      );
    md.anConf.addSample( "_Fake:TBar_tWch"                       ,  "pseudodata"    , kBlack      );
    md.anConf.addSample( "_Fake:T_tWch"                          ,  "pseudodata"    , kBlack      );
//    md.anConf.addSample( "_Fake:TToLeptons_sch_amcatnlo"         ,  "pseudodata"    , kBlack      );
    md.anConf.addSample( "_Fake:TToLeptons_sch"                  ,  "pseudodata"    , kBlack , scaleTToLeptons_sch  );

    //md.anConf.addSample( "_Fake:WJetsToLNu"                      ,  "pseudodata"    , kBlack, scaleWJets     );

    md.anConf.addSample( "_Fake:DYJetsToLL_M10to50"              ,  "pseudodata"    , kBlack, scaleDY10      );
    md.anConf.addSample( "_Fake:DYJetsToLL_M50"                  ,  "pseudodata"    , kBlack, scaleDY50      );

    md.anConf.addSample( "_Fake:TTJets"                          ,  "pseudodata"    , kBlack, scaleTTJets    );
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
             mcOnly,cmsPrel, uncDet, closure, nlo_vs_lo, fixLeg);
    md.prepareDisplay();
    md.doPlot();
    //md.doStatisticsPlot();
    md.savePlot("SUSY3L");
    //md.getStatistics("global_OffZBaseline");
    // md.dp.addText(xt,yt,st,addText);
    if(!manual) gROOT->ProcessLine(".q");
 
}
