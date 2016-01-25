MPAFDisplay md;

void ssdlScan_BENCH() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="merged_2fb"; // not needed for statistics but provides the normalization
  string fileList="merged_2fb_T1tttt-MASS-"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=2160; //pb-1 19470
  float energy=13; //TeV

  bool useXS=true;

  md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;

  //via XSect
  map<string,float> KFactors;
  KFactors[ "_standard_prompt_ttW" ] = 1.0213;
  KFactors[ "_standard_prompt_ttZH" ] = 1.0213;
  KFactors[ "_standard_prompt_WWss" ] = 1.0213;
  KFactors[ "_standard_prompt_XG" ] = 1.0213;
  KFactors[ "_standard_prompt_Rares" ] = 1.0213;
  KFactors[ "T1tttt-MASS-" ] = 1.0213;

  // marco put this line here:
  // _standard_prompt_WZ: WZTo3LNu: 1.22*xsec ; FillColor=ROOT.kOrange, FakeRate="susy-multilepton/standard_sel.txt\,susy-multilepton/load_is_2_prompt_loop.txt", Label="WZ (prompt)", NormSystematic=0.3
  KFactors[ "_standard_prompt_WZ" ] = 1.22;

 

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================

  md.addDataCardSigSample("T1tttt-MASS-","T1tttt_BENCH");




  md.addDataCardSample("WZTo3LNu"                                                 , "WZ"      );
  md.addDataCardSample("TTWToLNu"                                                 , "ttW"     );
  md.addDataCardSample("TTZToLLNuNu"                                              , "ttHZ"    );
  md.addDataCardSample("TTLLJets_m1to10"                                          , "ttHZ"    );
  md.addDataCardSample("TTHnobb"                                                  , "ttHZ"    );
  md.addDataCardSample("WpWpJJ"                                                   , "WW"      );
  md.addDataCardSample("TTGJets"                                                  , "XG"      );
  md.addDataCardSample("TGJets"                                                   , "XG"      );
  md.addDataCardSample("WGToLNuG"                                                 , "XG"      );
  md.addDataCardSample("ZGTo2LG"                                                  , "XG"      );
  md.addDataCardSample("WWDouble"                                                 , "rares"   );
  md.addDataCardSample("ZZTo4L"                                                   , "rares"   );
  md.addDataCardSample("tZq_ll"                                                   , "rares"   );
  md.addDataCardSample("GGHZZ4L"                                                  , "rares"   );
  md.addDataCardSample("VHToNonbb"                                                , "rares"   );
  md.addDataCardSample("WWZ"                                                      , "rares"   );
  md.addDataCardSample("ZZZ"                                                      , "rares"   );
  md.addDataCardSample("WZZ"                                                      , "rares"   );
  md.addDataCardSample("TTTT"                                                     , "rares"   );
  md.addDataCardSample("DoubleEG_Run2015C_Oct05_runs_254231_254914"               , "data"    );
  md.addDataCardSample("DoubleEG_Run2015D_Oct05_runs_256630_258158"               , "data"    );
  md.addDataCardSample("DoubleEG_Run2015D_PromptV4_runs_258159_260627"            , "data"    );
  md.addDataCardSample("DoubleMuon_Run2015C_Oct05_runs_254231_254914"             , "data"    );
  md.addDataCardSample("DoubleMuon_Run2015D_Oct05_runs_256630_258158"             , "data"    );
  md.addDataCardSample("DoubleMuon_Run2015D_PromptV4_runs_258159_260627"          , "data"    );
  md.addDataCardSample("MuonEG_Run2015C_Oct05_runs_254231_254914"                 , "data"    );
  md.addDataCardSample("MuonEG_Run2015D_Oct05_runs_256630_258158"                 , "data"    );
  md.addDataCardSample("MuonEG_Run2015D_PromptV4_runs_258159_260627"              , "data"    );

  md.addDataCardSample("mId:DYJetsToLL_M10to50"                                   , "flip"    );
  md.addDataCardSample("mId:DYJetsToLL_M50"                                       , "flip"    );
  //md.addDataCardSample("mId:TTWToLNu"                                             , "flip", -1);
  //md.addDataCardSample("mId:TTZToLLNuNu"                                          , "flip", -1);
  //md.addDataCardSample("mId:TTLLJets_m1to10"                                      , "flip", -1);
  //md.addDataCardSample("mId:TTHnobb"                                              , "flip", -1);
  //md.addDataCardSample("mId:WZTo3LNu"                                             , "flip", -1);
  //md.addDataCardSample("mId:WpWpJJ"                                               , "flip", -1);
  //md.addDataCardSample("mId:TTGJets"                                              , "flip", -1);
  //md.addDataCardSample("mId:TGJets"                                               , "flip", -1);
  //md.addDataCardSample("mId:WGToLNuG"                                             , "flip", -1);
  //md.addDataCardSample("mId:ZGTo2LG"                                              , "flip", -1);
  //md.addDataCardSample("mId:WWDouble"                                             , "flip", -1);
  //md.addDataCardSample("mId:ZZTo4L"                                               , "flip", -1);
  //md.addDataCardSample("mId:tZq_ll"                                               , "flip", -1);
  //md.addDataCardSample("mId:GGHZZ4L"                                              , "flip", -1);
  //md.addDataCardSample("mId:VHToNonbb"                                            , "flip", -1);
  //md.addDataCardSample("mId:WWZ"                                                  , "flip", -1);
  //md.addDataCardSample("mId:ZZZ"                                                  , "flip", -1);
  //md.addDataCardSample("mId:WZZ"                                                  , "flip", -1);
  //md.addDataCardSample("mId:TTTT"                                                 , "flip", -1);

  md.addDataCardSample("data:Fake:DoubleEG_Run2015C_Oct05_runs_254231_254914"     , "fake"    );
  md.addDataCardSample("data:Fake:DoubleEG_Run2015D_Oct05_runs_256630_258158"     , "fake"    );
  md.addDataCardSample("data:Fake:DoubleEG_Run2015D_PromptV4_runs_258159_260627"  , "fake"    );
  md.addDataCardSample("data:Fake:DoubleMuon_Run2015C_Oct05_runs_254231_254914"   , "fake"    );
  md.addDataCardSample("data:Fake:DoubleMuon_Run2015D_Oct05_runs_256630_258158"   , "fake"    );
  md.addDataCardSample("data:Fake:DoubleMuon_Run2015D_PromptV4_runs_258159_260627", "fake"    );
  md.addDataCardSample("data:Fake:MuonEG_Run2015C_Oct05_runs_254231_254914"       , "fake"    );
  md.addDataCardSample("data:Fake:MuonEG_Run2015D_Oct05_runs_256630_258158"       , "fake"    );
  md.addDataCardSample("data:Fake:MuonEG_Run2015D_PromptV4_runs_258159_260627"    , "fake"    );
  //md.addDataCardSample("Fake:DYJetsToLL_M10to50"                                  , "fake", -1);
  //md.addDataCardSample("Fake:DYJetsToLL_M50"                                      , "fake", -1);
  md.addDataCardSample("Fake:TTWToLNu"                                            , "fake", -1);
  md.addDataCardSample("Fake:TTZToLLNuNu"                                         , "fake", -1);
  md.addDataCardSample("Fake:TTLLJets_m1to10"                                     , "fake", -1);
  md.addDataCardSample("Fake:TTHnobb"                                             , "fake", -1);
  md.addDataCardSample("Fake:WZTo3LNu"                                            , "fake", -1);
  md.addDataCardSample("Fake:WpWpJJ"                                              , "fake", -1);
  md.addDataCardSample("Fake:TTGJets"                                             , "fake", -1);
  md.addDataCardSample("Fake:TGJets"                                              , "fake", -1);
  md.addDataCardSample("Fake:WGToLNuG"                                            , "fake", -1);
  md.addDataCardSample("Fake:ZGTo2LG"                                             , "fake", -1);
  md.addDataCardSample("Fake:WWDouble"                                            , "fake", -1);
  md.addDataCardSample("Fake:ZZTo4L"                                              , "fake", -1);
  md.addDataCardSample("Fake:tZq_ll"                                              , "fake", -1);
  md.addDataCardSample("Fake:GGHZZ4L"                                             , "fake", -1);
  md.addDataCardSample("Fake:VHToNonbb"                                           , "fake", -1);
  md.addDataCardSample("Fake:WWZ"                                                 , "fake", -1);
  md.addDataCardSample("Fake:ZZZ"                                                 , "fake", -1);
  md.addDataCardSample("Fake:WZZ"                                                 , "fake", -1);
  md.addDataCardSample("Fake:TTTT"                                                , "fake", -1);

  
  //shape uncertainties
  md.addNuisanceParameter("JES","ttW:ttZH:WZ:WW:XG:rares:T1tttt_BENCH","shape","");
  md.addNuisanceParameter("BTAG","ttW:ttZH:WZ:WW:XG:rares:T1tttt_BENCH","shape","");
  md.addNuisanceParameter("tHTE","ttW:ttZH:WZ:WW:XG:rares:T1tttt_BENCH","shape","");

  md.addNuisanceParameter("EWKFR","fake","shape","");

  md.addNuisanceParameter("ttWAcc","ttW","shape","");
  md.addNuisanceParameter("ttHZAcc","ttHZ","shape","");

  md.addNuisanceParameter("BTAGFS","T1tttt_BENCH","shape","");
  md.addNuisanceParameter("LepEffFS","T1tttt_BENCH","shape","");
  md.addNuisanceParameter("ISR","T1tttt_BENCH","shape","");

  md.addNuisanceParameter("QCDScale","T1tttt_BENCH","shape","");

  //vector<string> cats(
  string cats[66]={
    "HHSR1","HHSR2","HHSR3","HHSR4","HHSR5","HHSR6","HHSR7","HHSR8",
    "HHSR9","HHSR10","HHSR11","HHSR12","HHSR13","HHSR14","HHSR15","HHSR16",
    "HHSR17","HHSR18","HHSR19","HHSR20","HHSR21","HHSR22","HHSR23","HHSR24",
    "HHSR25","HHSR26","HHSR27","HHSR28","HHSR29","HHSR30","HHSR31","HHSR32",

    "HLSR1","HLSR2","HLSR3","HLSR4","HLSR5","HLSR6","HLSR7","HLSR8",
    "HLSR9","HLSR10","HLSR11","HLSR12","HLSR13","HLSR14","HLSR15","HLSR16",
    "HLSR17","HLSR18","HLSR19","HLSR20","HLSR21","HLSR22","HLSR23","HLSR24",
    "HLSR25","HLSR26",

    "LLSR1","LLSR2","LLSR3","LLSR4","LLSR5","LLSR6","LLSR7","LLSR8"
  };

  //vector<string> dss; 
  string dss[7]={"ttW","ttHZ","WZ","WW","XG","rares","T1tttt_BENCH"};
  

  for(int isr=0;isr<66/*cats.size()*/;isr++) {
    md.addNuisanceParameter("pdfS"+cats[isr],"T1tttt_BENCH","shape","");

    md.addNuisanceParameter("flip"+cats[isr]+"stat","flip","shape","");
    md.addNuisanceParameter("fake"+cats[isr]+"stat","fake","shape","");
    for(size_t id=0;id<7/*dss.size()*/;id++) {
      md.addNuisanceParameter(dss[id]+cats[isr]+"stat",dss[id],"shape","");
    }
  }  

  
  //Flat uncertanties =================================
  //lumi
  md.addNuisanceParameter("lumi","ttW:ttHZ:WW:XG:rares:T1tttt_BENCH","lnN","1.046:1.046:1.046:1.046:1.046:1.046:1.046");
  //md.addNuisanceParameter("lumi","ttW:ttHZ:WW:XG:rares:T1tttt_BENCH","lnN","1.12:1.12:1.12:1.12:1.12:1.12:1.12");
  //experimental uncertainties
  md.addNuisanceParameter("lEff","ttW:ttHZ:WW:XG:rares:T1tttt_BENCH","lnN","1.04:1.04:1.04:1.04:1.04:1.04");
  md.addNuisanceParameter("tEff","ttW:ttHZ:WW:XG:rares:T1tttt_BENCH","lnN","1.02:1.02:1.02:1.02:1.02:1.02");
  //Data-driven methods
  md.addNuisanceParameter("chMID","flip","lnN","1.30");
  md.addNuisanceParameter("fratio","fake","lnN","1.30");
  //theoretical uncertainties
  md.addNuisanceParameter("wzTh","WZ","lnN","1.30");
  md.addNuisanceParameter("WWTh","ttW","lnN","1.50");
  md.addNuisanceParameter("TGTh","XG","lnN","1.50");
  md.addNuisanceParameter("rareTh","rares","lnN","1.50");
  
  md.addNuisanceParameter("ttWPdf","ttW","lnN","1.04");
  md.addNuisanceParameter("ttHZPdf","ttHZ","lnN","1.04");
  md.addNuisanceParameter("ttWXs","ttW","lnN","1.13");
  md.addNuisanceParameter("ttHZXs","ttHZ","lnN","1.11");
  md.addNuisanceParameter("fsHLT","T1tttt_BENCH","lnN","1.05");

  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
  int ncategs=66;
  // vector<string> categs(
  string categs[66]={"global_HHSR1","global_HHSR2","global_HHSR3","global_HHSR4",
		     "global_HHSR5","global_HHSR6","global_HHSR7","global_HHSR8",
		     "global_HHSR9","global_HHSR10","global_HHSR11","global_HHSR12",
		     "global_HHSR13","global_HHSR14","global_HHSR15","global_HHSR16",
		     "global_HHSR17","global_HHSR18","global_HHSR19","global_HHSR20",
		     "global_HHSR21","global_HHSR22","global_HHSR23","global_HHSR24",
		     "global_HHSR25","global_HHSR26","global_HHSR27","global_HHSR28",
		     "global_HHSR29","global_HHSR30","global_HHSR31","global_HHSR32",

		     "global_HLSR1","global_HLSR2","global_HLSR3","global_HLSR4",
		     "global_HLSR5","global_HLSR6","global_HLSR7","global_HLSR8",
		     "global_HLSR9","global_HLSR10","global_HLSR11","global_HLSR12",
		     "global_HLSR13","global_HLSR14","global_HLSR15","global_HLSR16",
		     "global_HLSR17","global_HLSR18","global_HLSR19","global_HLSR20",
		     "global_HLSR21","global_HLSR22","global_HLSR23","global_HLSR24",
		     "global_HLSR25","global_HLSR26",

		     "global_LLSR1","global_LLSR2","global_LLSR3","global_LLSR4",
		     "global_LLSR5","global_LLSR6","global_LLSR7","global_LLSR8",
  };
  vector<string> vcategs;
  for(int i=0;i<66;i++) {
    vcategs.push_back( categs[i] );
  }


  //external uncertainties ===================================
  //vector<float> AccTTW
  float AccTTW[66]={
      0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
      0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
      0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
      0.03,0.08,0.03,0.08,0.03,0.08,0.08,0.08,
    
      0.03,0.08,0.03,0.08,0.08,0.08,0.03,0.08,
      0.03,0.08,0.08,0.08,0.03,0.08,0.03,0.08,
      0.08,0.08,0.03,0.08,0.03,0.08,0.03,0.08,
      0.08,0.08,
    
      0.08,0.08,0.08,0.08,0.08,0.08,0.08,0.08,
  };
  
  //vector<float> AccTTHZ
  float AccTTHZ[66]={
    0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
    0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
    0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
    0.03,0.08,0.03,0.08,0.03,0.08,0.08,0.08,
    
    0.03,0.08,0.03,0.08,0.08,0.08,0.03,0.08,
    0.03,0.08,0.08,0.08,0.03,0.08,0.03,0.08,
    0.08,0.08,0.03,0.08,0.03,0.08,0.03,0.08,
    0.08,0.08,

    0.08,0.08,0.08,0.08,0.08,0.08,0.08,0.08,
  };
  
  // vector<float> EWKFake({
  //     0.10,0.06,0.10,0.03,0.09,0.10,0.05,0.10,
  // 	0.09,0.11,0.11,0.09,0.09,0.02,0.10,0.10,
  // 	0.20,0.03,0.10,0.05,0.05,0.10,0.10,0.10,
  // 	0.10,0.10,0.10,0.10,0.10,0.10,0.10,0.10,

  // 	0.03,0.01,0.10,0.02,0.01,0.10,0.02,0.01,
  // 	0.01,0.01,0.01,0.01,0.02,0.01,0.10,0.10,
  // 	0.01,0.10,0.10,0.10,0.10,0.10,0.10,0.10,
  // 	0.10,0.10,

  // 	0.10,0.01,0.10,0.10,0.10,0.10,0.10,0.10,
  // 	});

  //vector<float> HLTEff
  float HLTEff[66]={
    0,0.02,0,0.02,0.02,0.02,0.02,0.02,
    0,0.02,0,0.02,0.02,0.02,0.02,0.02,
    0,0.02,0,0.02,0.02,0.02,0.02,0.02,
    0,0.02,0,0.02,0,0.02,0.02,0.02,
    
    0,0.02,0,0.02,0.02,0.02,0,0.02,
    0,0.02,0.02,0.02,0,0.02,0,0.02,
    0.02,0.02,0,0.02,0,0.02,0,0.02,
    0.02,0.02,

    0.02,0.02,0.02,0.02,0.02,0.02,0.02,0.02
  };

  
  //  int nCateg=66; //47
  //  vector<string> _categs(nCateg,"");
 
  //qcd scale for signal
  TFile* iQCDFile=new TFile("/shome/cheidegg/t/runScanStuff/step5/QCDScales/scaleUnc-MASS-.root","read");
  TH1F* hQCDUp=(TH1F*)iQCDFile->Get("-MASS-ScaleUp");
  TH1F* hQCDDown=(TH1F*)iQCDFile->Get("-MASS-ScaleDown");
  

  for(size_t ic=0;ic<66/*categs.size()*/;ic++) {
     for(int isr=0;isr<66/*cats.size()*/;isr++) {
       if(categs[ic].substr(7, categs[ic].size()-7)==cats[isr])
	 md.addExternalSystUnc("T1tttt_BENCH","pdfS"+cats[isr],0.1, -0.1, categs[ic], "selected");
       else
	 md.addExternalSystUnc("T1tttt_BENCH","pdfS"+cats[isr],0., 0., categs[ic], "selected");
     }
     md.addExternalSystUnc("T1tttt_BENCH","QCDScale",hQCDUp->GetBinContent(ic+1), hQCDDown->GetBinContent(ic+1), categs[ic], "selected");

    //md.addExternalSystUnc("fake","frEwk",EWKFake[ic], -1*EWKFake[ic], categs[ic], "selected");
    md.addExternalSystUnc("ttW","ttWAcc",AccTTW[ic], -1*AccTTW[ic], categs[ic], "selected");
    md.addExternalSystUnc("ttHZ","ttHZAcc",AccTTHZ[ic], -1*AccTTHZ[ic], categs[ic], "selected");
    for(size_t id=0;id<7/*dss.size()*/;id++) {
      md.addExternalSystUnc(dss[id],"tHTE",HLTEff[ic], -1*HLTEff[ic], categs[ic], "selected");
    }
  }
  
  md.makeMultiDataCard("T1tttt_BENCH", vcategs, "selected", "ssdlScan_2fb_T1tttt_BENCH");


  gROOT->ProcessLine(".q");

}
