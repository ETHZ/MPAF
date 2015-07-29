{
  if(Recompute) {
    MPAFDisplay md;
 
    //Bloody René Brun
    bool * rtmp= const_cast<bool*> pr;
    *rtmp = false;

  }
  else md.refresh();


  //general parameters ********************* general parameters
  string dir="FakeRatio";
  string fileName="FakeRatio_all_cut_relIso_lightjet_isosip_all_all"; // not needed for statistics
  //string fileList="phys14exerc"; // put command line that gives all files as in a "ls" command
  string fileList="FakeRatio_MR00_cut_relIso_b_isosip_all_all"; // put command line that gives all files as in a "ls" command
  string hName=""; // not needed for statistics

  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList, hName);
    md.anConf.configureData(false, 0, mcOnly);
    //}

  //observables **********************
  //string obs[6]={"","","","","",""};
    md.dp.setObservables("MR_LMuSIP");
  

  //Binning & title ************************* Binning & titre
  string yTitle="number of leptons";
  int binning=50;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0.,  0.4};
  double rangeX[2]={0., 10. };
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

  string autoBinFile="susybinninghigh";
  md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=false;
  
  bool mcStatSyst=true;
  string systSources="";

  bool uncDet=false;

  string Norm="norm";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=10000; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  map<string,float> LumisXS;

  LumisXS[ "QCD_Mu15_skimfake"                 ] = 4777926. / 381304.0; 
  LumisXS[ "QCD_Pt20to30_EMEnriched_skimfake"  ] = 1987127. / 4741100.0; 
  LumisXS[ "QCD_Pt30to80_EMEnriched_skimfake"  ] = 2000838. / 10410400.0; 
  LumisXS[ "QCD_Pt80to170_EMEnriched_skimfake" ] = 1959507. / 514922.0; 
  LumisXS[ "QCD_Pt20to30_bcToE_skimfake"       ] = 999926.  / 506925.0; 
  LumisXS[ "QCD_Pt30to80_bcToE_skimfake"       ] = 1852166. / 505648.0; 
  LumisXS[ "QCD_Pt80to170_bcToE_skimfake"      ] = 1000671. / 42813.75; 
  LumisXS[ "QCD_Pt170toInf_bcToE_skimfake"     ] = 1000221. / 5217.1; 
  LumisXS[ "TTJets_skimfake"                   ] = 25446993. / 809.1;

  ////LumisXS[ "WJetsToLNu_skim"                     ] = 10017462 / 20508.9; 
  //LumisXS[ "WJetsToLNu_HT100to200_skim"          ] = 5262265  / (1817.0   * 1.23);
  //LumisXS[ "WJetsToLNu_HT200to400_skim"          ] = 4936077  / ( 471.6   * 1.23); 
  //LumisXS[ "WJetsToLNu_HT400to600_skim"          ] = 4640594  / (  55.61  * 1.23);
  //LumisXS[ "WJetsToLNu_HT600toInf_skim"          ] = 237484   / (  18.81  * 1.23);
 
  ////LumisXS[ "DYJetsToLL_M50_skim"                 ] = 2829164  / 6024;
  //LumisXS[ "DYJetsToLL_M50_HT100to200_skim"      ] = 4054159  / ( 194.3   * 1.27);
  //LumisXS[ "DYJetsToLL_M50_HT200to400_skim"      ] = 4666496  / (  52.24  * 1.27);
  //LumisXS[ "DYJetsToLL_M50_HT400to600_skim"      ] = 4931372  / (   6.546 * 1.27);
  //LumisXS[ "DYJetsToLL_M50_HT600toInf_skim"      ] = 4493574  / (   2.179 * 1.27);

  //LumisXS[ "TTJets_skim"                         ] = 25446993 / 809.1;

  //LumisXS[ "TTWJets_skim"                        ] = 246521   / 0.6647;
  //LumisXS[ "TTZJets_skim"                        ] = 249275   / 0.8565;
  //LumisXS[ "WZJetsTo3LNu_skim"                   ] = 237484   / 2.29;

  //LumisXS[ "TBarToLeptons_sch_skim"              ] = 250000   / 0.44928; 
  //LumisXS[ "TBarToLeptons_tch_skim"              ] = 1999800  / 8.74476;
  //LumisXS[ "TBar_tWch_skim"                      ] = 971800   / 35.6;
  //LumisXS[ "T_tWch_skim"                         ] = 986100   / 35.6;
  //LumisXS[ "TToLeptons_sch_skim"                 ] = 500000   / 0.7776;
  //LumisXS[ "TToLeptons_tch_skim"                 ] = 3991000  / 14.6934;
=======
  //LumisXS[ "WJetsToLNu_skim"                     ] = 10017462 / 20508.9; 
  LumisXS[ "WJetsToLNu_HT100to200_skim"          ] = 5262265  / (1817.0   * 1.23);
  LumisXS[ "WJetsToLNu_HT200to400_skim"          ] = 4936077  / ( 471.6   * 1.23); 
  LumisXS[ "WJetsToLNu_HT400to600_skim"          ] = 4640594  / (  55.61  * 1.23);
  LumisXS[ "WJetsToLNu_HT600toInf_skim"          ] = 237484   / (  18.81  * 1.23);
 
  //LumisXS[ "DYJetsToLL_M50_skim"                 ] = 2829164  / 6024;
  LumisXS[ "DYJetsToLL_M50_HT100to200_skim"      ] = 4054159  / ( 194.3   * 1.27);
  LumisXS[ "DYJetsToLL_M50_HT200to400_skim"      ] = 4666496  / (  52.24  * 1.27);
  LumisXS[ "DYJetsToLL_M50_HT400to600_skim"      ] = 4931372  / (   6.546 * 1.27);
  LumisXS[ "DYJetsToLL_M50_HT600toInf_skim"      ] = 4493574  / (   2.179 * 1.27);

  LumisXS[ "TTJets_skim"                         ] = 25446993 / 809.1;

  LumisXS[ "TTWJets_skim"                        ] = 246521   / 0.6647;
  LumisXS[ "TTZJets_skim"                        ] = 249275   / 0.8565;
  LumisXS[ "WZJetsTo3LNu_skim"                   ] = 237484   / 2.29;

  LumisXS[ "TBarToLeptons_sch_skim"              ] = 250000   / 0.44928; 
  LumisXS[ "TBarToLeptons_tch_skim"              ] = 1999800  / 8.74476;
  LumisXS[ "TBar_tWch_skim"                      ] = 971800   / 35.6;
  LumisXS[ "T_tWch_skim"                         ] = 986100   / 35.6;
  LumisXS[ "TToLeptons_sch_skim"                 ] = 500000   / 0.7776;
  LumisXS[ "TToLeptons_tch_skim"                 ] = 3991000  / 14.6934;
>>>>>>> 68dbe48c3bf863a58c20c90e08059afe2a2f6a5f




  //via XSect
  
  map<string,float> KFactors;
     // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================
  // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
  //if( md.isInitStatus() ) {


  md.anConf.addSample( "TTJets_skimfake"                        , "t#bar{t}"    , kRed-6  ); 
  md.anConf.addSample( "QCD_Mu15_skimfake"                      , "QCD Mu"      , kBlue+2 ); 
  md.anConf.addSample( "QCD_Pt20to30_EMEnriched_skimfake"       , "QCD EM+BCtoE", kBlue-4 ); 
  md.anConf.addSample( "QCD_Pt30to80_EMEnriched_skimfake"       , "QCD EM+BCtoE", kBlue-4 ); 
  md.anConf.addSample( "QCD_Pt80to170_EMEnriched_skimfake"      , "QCD EM+BCtoE", kBlue-4 ); 
  md.anConf.addSample( "QCD_Pt20to30_bcToE_skimfake"            , "QCD EM+BCtoE", kBlue-4 ); 
  md.anConf.addSample( "QCD_Pt30to80_bcToE_skimfake"            , "QCD EM+BCtoE", kBlue-4 ); 
  md.anConf.addSample( "QCD_Pt80to170_bcToE_skimfake"           , "QCD EM+BCtoE", kBlue-4 ); 
  md.anConf.addSample( "QCD_Pt170toInf_bcToE_skimfake"          , "QCD EM+BCtoE", kBlue-4 ); 

  ////md.anConf.addSample( "WJetsToLNu_skim"                    , "W+Jets"  , kAzure-2 ); 
  //md.anConf.addSample( "WJetsToLNu_HT100to200_skim"         , "W+Jets"  , kAzure-2 ); 
  //md.anConf.addSample( "WJetsToLNu_HT200to400_skim"         , "W+Jets"  , kAzure-2 );  
  //md.anConf.addSample( "WJetsToLNu_HT400to600_skim"         , "W+Jets"  , kAzure-2 ); 
  //md.anConf.addSample( "WJetsToLNu_HT600toInf_skim"         , "W+Jets"  , kAzure-2 ); 
 
  ////md.anConf.addSample( "DYJetsToLL_M50_skim"                , "Z+Jets"  , kAzure+6 ); 
  //md.anConf.addSample( "DYJetsToLL_M50_HT100to200_skim"     , "Z+Jets"  , kAzure+6 ); 
  //md.anConf.addSample( "DYJetsToLL_M50_HT200to400_skim"     , "Z+Jets"  , kAzure+6 ); 
  //md.anConf.addSample( "DYJetsToLL_M50_HT400to600_skim"     , "Z+Jets"  , kAzure+6 ); 
  //md.anConf.addSample( "DYJetsToLL_M50_HT600toInf_skim"     , "Z+Jets"  , kAzure+6 ); 

  //md.anConf.addSample( "TTJets_skim"                        , "t#bar{t}", kBlue+1  ); 

  //md.anConf.addSample( "TTWJets_skim"                       , "rare"    , kOrange-2); 
  //md.anConf.addSample( "TTZJets_skim"                       , "rare"    , kOrange-2); 
  //md.anConf.addSample( "WZJetsTo3LNu_skim"                  , "rare"    , kOrange-2); 

  //md.anConf.addSample( "TBarToLeptons_sch_skim"             , "single-t", kViolet-3); 
  //md.anConf.addSample( "TBarToLeptons_tch_skim"             , "single-t", kViolet-3); 
  //md.anConf.addSample( "TBar_tWch_skim"                     , "single-t", kViolet-3); 
  //md.anConf.addSample( "T_tWch_skim"                        , "single-t", kViolet-3); 
  //md.anConf.addSample( "TToLeptons_sch_skim"                , "single-t", kViolet-3); 
  //md.anConf.addSample( "TToLeptons_tch_skim"                , "single-t", kViolet-3); 
  
   

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
  //md.getStatistics();
  //md.makeDataCard(fileList, "global", "SR b-jet multiplicity");
  md.savePlot("FakeRatio");
  // md.dp.addText(xt,yt,st,addText);

  //gROOT->ProcessLine(".q");

}
