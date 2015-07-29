/****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, Matthieu Marionneau                                **
** CERN, Fall 2014                                                          **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/


#include "analysis/src/FakeRatioStudy.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
FakeRatioStudy::FakeRatioStudy(std::string cfg){
  /* 
     constructs the FakeRatioStudy class 
     parameters: configuration_file
     return: none
  */
  
  startExecution(cfg);
  initialize();

  _mvaId=false;
}


//____________________________________________________________________________
FakeRatioStudy::~FakeRatioStudy(){
  /* 
     destructs the FakeRatioStudy class 
     parameters: none
     return: none
  */

}


//____________________________________________________________________________
void FakeRatioStudy::initialize(){
  /*
    initializes the FakeRatioStudy class
    parameters: none
    return: none
  */

  _vc->registerVar("run"                          , "I" );
  _vc->registerVar("lumi"                         , "I" );
  _vc->registerVar("evt"                          , "I" );
  _vc->registerVar("HLT_SingleMu"                 , "F" );
  _vc->registerVar("HLT_MuEG"                     , "F" );
  _vc->registerVar("HLT_TripleEl"                 , "F" );
  _vc->registerVar("HLT_DoubleEl"                 , "F" );
  _vc->registerVar("HLT_DoubleMu"                 , "F" );
  _vc->registerVar("nVert"                        , "I" );
  _vc->registerVar("nTrueInt"                     , "I" );
  _vc->registerVar("puWeight"                     , "F" );
  _vc->registerVar("genWeight"                    , "F" );
  _vc->registerVar("nLepGood"                     , "I" );
  _vc->registerVar("LepGood_pt"                   , "AF");
  _vc->registerVar("LepGood_eta"                  , "AF");
  _vc->registerVar("LepGood_phi"                  , "AF");
  _vc->registerVar("LepGood_charge"               , "AI");
  _vc->registerVar("LepGood_tightCharge"          , "AI");
  _vc->registerVar("LepGood_mediumMuonId"         , "AI");
  //_vc->registerVar("LepGood_eleMVAId"             , "AI");
  _vc->registerVar("LepGood_mvaIdPhys14"          , "AF");
  _vc->registerVar("LepGood_pdgId"                , "AI");
  _vc->registerVar("LepGood_relIso03"             , "AF");
  _vc->registerVar("LepGood_relIso04"             , "AF");
  _vc->registerVar("LepGood_jetPtRatio"           , "AF");
  _vc->registerVar("LepGood_jetPtRel"             , "AF");
  _vc->registerVar("LepGood_miniRelIso"           , "AF");
  _vc->registerVar("LepGood_dxy"                  , "AF");
  _vc->registerVar("LepGood_dz"                   , "AF");
  _vc->registerVar("LepGood_sip3d"                , "AF");
  _vc->registerVar("LepGood_pfMuonId"             , "AI");
  _vc->registerVar("LepGood_tightId"              , "AI");
  _vc->registerVar("LepGood_looseIdSusy"          , "AI");
  _vc->registerVar("LepGood_convVeto"             , "AI");
  _vc->registerVar("LepGood_lostHits"             , "AI");
  _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1", "AI");
  _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1", "AI");
  _vc->registerVar("LepGood_eleCutId2012_full5x5" , "AI");
  _vc->registerVar("LepGood_mvaSusyPHYS14"        , "AF");
  _vc->registerVar("LepGood_mvaSusy"              , "AF");
  _vc->registerVar("LepGood_mcMatchId"            , "AI");
  _vc->registerVar("LepGood_mcMatchAny"           , "AI");
  _vc->registerVar("LepGood_jetBTagCSV"           , "AF");
  _vc->registerVar("met_pt"                       , "F" );
  _vc->registerVar("met_eta"                      , "F" );
  _vc->registerVar("met_phi"                      , "F" );
  _vc->registerVar("met_mass"                     , "F" );
  _vc->registerVar("nJet25"                       , "I" );
  _vc->registerVar("nJet40"                       , "I" );
  _vc->registerVar("nJet"                         , "I" );
  _vc->registerVar("Jet_id"                       , "AI");
  _vc->registerVar("Jet_pt"                       , "AF");
  _vc->registerVar("Jet_rawPt"                    , "AF");
  _vc->registerVar("Jet_eta"                      , "AF");
  _vc->registerVar("Jet_phi"                      , "AF");
  _vc->registerVar("Jet_mass"                     , "AF");
  _vc->registerVar("Jet_btagCSV"                  , "AF");
  _vc->registerVar("nDiscJet"                     , "I" );
  _vc->registerVar("DiscJet_id"                   , "AI");
  _vc->registerVar("DiscJet_pt"                   , "AF");
  _vc->registerVar("DiscJet_rawPt"                , "AF");
  _vc->registerVar("DiscJet_eta"                  , "AF");
  _vc->registerVar("DiscJet_phi"                  , "AF");
  _vc->registerVar("DiscJet_mass"                 , "AF");
  _vc->registerVar("DiscJet_btagCSV"              , "AF");
  
  //generator informations
  _vc->registerVar("nGenPart"                     , "I" );
  _vc->registerVar("GenPart_pt"                   , "AF");
  _vc->registerVar("GenPart_eta"                  , "AF");
  _vc->registerVar("GenPart_phi"                  , "AF");
  _vc->registerVar("GenPart_pdgId"                , "AI");
  _vc->registerVar("GenPart_motherId"             , "AI");
  _vc->registerVar("GenPart_grandmotherId"        , "AI");

  _vc->registerVar("nGenBHad"                     , "I" );
  _vc->registerVar("GenBHad_pt"                   , "AF"); 
  _vc->registerVar("GenBHad_eta"                  , "AF"); 
  _vc->registerVar("GenBHad_phi"                  , "AF"); 
  _vc->registerVar("GenBHad_pdgId"                , "AI"); 
 
  //bjets
  _vc->registerVar("nBJetLoose25"                 , "I" );
  _vc->registerVar("nBJetMedium40"                , "I" );
  _vc->registerVar("nBJetMedium25"                , "I" );
  _vc->registerVar("nSoftBJetMedium25"            , "I" );

  //additional counter categories
  _au->addCategory( kLElId, "loose El Id");
  _au->addCategory( kTElId, "tight El Id");
  _au->addCategory( kVElId, "veto El Id" );
  _au->addCategory( kLMuId, "loose Mu Id");
  _au->addCategory( kTMuId, "tight Mu Id");
  _au->addCategory( kVMuId, "veto Mu Id" );
  _au->addCategory( kJetId, "jet Id"     );

  //extra input variables
  _lepptcut = getCfgVarS("LEPPTCUT"); // lepton pt cut, if none given, we take default > 10GeV
  _lepflav = getCfgVarS("LEPFLAV"); // lepton flavor (all, e, m)
  _lepiso  = getCfgVarS("LEPISO" ); // lepton isolation (relIso, pTrel)
  _mva     = getCfgVarS("LEPID"  ); // lepton id (cut, cutnotmva, cutandmva, mva, mvanotcut, mvaandcut)
  _btag    = getCfgVarS("BTAG"   ); // btag (std, 40, 25, soft25, 15, IVF)
  _MR      = getCfgVarS("MR"     ); // measurement region (MR00, MR01, MR02, MR03)
  _fakes   = getCfgVarS("FAKES"  ); // source of fake leptons (none, all, b, c, light)
  _xpol    = getCfgVarS("DENXPOL"); // denominator extrapolation (isosip, sip, iso)
  _htbin   = getCfgVarS("HTBIN"  ); // additional HT bin (all, 0, 200, 400)
  _etabin  = getCfgVarS("ETABIN" ); // lepton eta bin (none, default, 09, 12, 15)
  
}


//____________________________________________________________________________
void FakeRatioStudy::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */ 
	
  //_weight = (i->second)->Getweight();
  // if(_PUReweighting) 
  //   _weight *= _vc->get("puWeight");

}


//____________________________________________________________________________
void FakeRatioStudy::run(){



  _lEls   .clear();
  _lntEls .clear();
  _tEls   .clear();
  _vEls   .clear();
  _lLeps  .clear();
  _lntLeps.clear();
  _tLeps  .clear();
  _vLeps  .clear();
  _lMus   .clear();
  _lntMus .clear();
  _tMus   .clear();
  _vMus   .clear();
  _jets   .clear();

  _lElIdx   .clear();
  _lntElIdx .clear();
  _tElIdx   .clear();
  _vElIdx   .clear();
  _lLepIdx  .clear();
  _lntLepIdx.clear();
  _tLepIdx  .clear();
  _vLepIdx  .clear();
  _lMuIdx   .clear();
  _lntMuIdx .clear();
  _tMuIdx   .clear();
  _vMuIdx   .clear();

  counter("denominator");

	
  // prepare event selection
  collectKinematicObjects();
	
	
  // skimming
  //if(!skimSelection()) return;
  //fillSkimTree();
  //return;


  // measurement region selection
  if(_fakes == "none"){
    //if(!mrSelection()) return;
    if(!syncSelection()) return;
  }
  else {
    if(!genMRSelection()) return;
  }

	
  // calling the modules
  fillEventPlots("MR");
  fillFakeRatioMaps("MR");
  //fillFakeRatioPlots("MR");
  fillJetPlots("MR");
  fillLeptonPlots("MR");

	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatioStudy::divideFRMap(string kr, string postpend){

  for(unsigned int i=0; i<_numDS; ++i){
    TH1 * denom = _hm -> getHisto(kr + "_L" + postpend, i);
    TH1 * num   = _hm -> getHisto(kr + "_R" + postpend, i);
    num -> Divide(denom);
  }
 
}


//____________________________________________________________________________
void FakeRatioStudy::divideFRMaps(string kr, string lep){

  divideFRMap(kr, lep + "Map"           );
  divideFRMap(kr, lep + "MapPt"         );
  divideFRMap(kr, lep + "MapPtIso"      );
  divideFRMap(kr, lep + "MapPtJet"      );
  divideFRMap(kr, lep + "MapPtMIso"     );
  divideFRMap(kr, lep + "MapPtMIso1"    );
  divideFRMap(kr, lep + "MapPtMIso2"    );
  divideFRMap(kr, lep + "SyncMapPt"     );
  divideFRMap(kr, lep + "SyncMapPtJet"  );
  divideFRMap(kr, lep + "SyncMapPtMIso" );
  divideFRMap(kr, lep + "SyncMapPtMIso2");
} 


//____________________________________________________________________________
void FakeRatioStudy::registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nbins, bmin, bmax, axis);

} 


//____________________________________________________________________________
void FakeRatioStudy::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);

}


//____________________________________________________________________________
void FakeRatioStudy::defineOutput(){
  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 

  //CH: this is a temporary solution to getting the average of LepGood_jetPtRatio
  //for the leptons passing the selection; in the future probably write it to 
  //a histogram and then load it from the database? 
  _alpha.push_back(0.777648); // QCD_Mu15
  _alpha.push_back(0.789777); // QCD_Pt20to30_EMEnriched
  _alpha.push_back(0.784572); // QCD_Pt20to30_bcToE
  _alpha.push_back(0.790092); // QCD_Pt30to50_Mu5
  _alpha.push_back(0.758326); // QCD_Pt30to80_EMEnriched
  _alpha.push_back(0.768774); // QCD_Pt30to80_bcToE
  _alpha.push_back(0.772373); // QCD_Pt50to80_Mu5
  _alpha.push_back(0.749572); // QCD_Pt80to120_Mu5
  _alpha.push_back(0.7386  ); // QCD_Pt80to170_EMEnriched
  _alpha.push_back(0.748716); // QCD_Pt80to170_bcToE

  // bins
  float FR_bins_eta_el_sync[4] = { 0.0, 1.0, 2.0, 2.5};
  float FR_bins_eta_mu_sync[4] = { 0.0, 1.0, 2.0, 2.4};
  float FR_bins_eta_lep[6]     = { 0.0, 0.5, 1.0, 1.5, 2.0, 2.5};
  float FR_bins_eta_el[3]      = { 0.0, 1.5, 2.4};
  float FR_bins_eta_mu[3]      = { 0.0, 0.9, 2.4};

  float FR_bins_pt_lep_sync[6] = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};
  float FR_bins_pt_lep[9]      = {10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0};
  float FR_bins_ptlep_lep[23]  = {10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0,
                                  55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0,
                                 100.0, 105.0, 110.0, 115.0, 120.0};
  float FR_bins_ptmiso_lep[6]  = {10.0, 25.0, 50.0, 75.0, 100.0, 125.0};

  vector<float> bins_eta_el_sync = Tools::toVector(FR_bins_eta_el_sync);
  vector<float> bins_eta_mu_sync = Tools::toVector(FR_bins_eta_mu_sync);
  vector<float> bins_eta_lep     = Tools::toVector(FR_bins_eta_lep    );
  vector<float> bins_eta_el      = Tools::toVector(FR_bins_eta_el     );
  vector<float> bins_eta_mu      = Tools::toVector(FR_bins_eta_mu     );

  vector<float> bins_pt_lep_sync = Tools::toVector(FR_bins_pt_lep_sync);
  vector<float> bins_pt_lep      = Tools::toVector(FR_bins_pt_lep     );
  vector<float> bins_ptlep_lep   = Tools::toVector(FR_bins_ptlep_lep  );
  vector<float> bins_ptmiso_lep  = Tools::toVector(FR_bins_ptmiso_lep );

  // leptons
  string MR_leps_den[6]        = {"MR_LEl", "MR_LNTEl", "MR_LLep", "MR_LNTLep", "MR_LMu", "MR_LNTMu"};
  string MR_leps_num[3]        = {"MR_TEl", "MR_TLep", "MR_TMu"};
  string MR_leps_rat[3]        = {"MR_REl", "MR_RLep" , "MR_RMu"};
  string MR_els[4]             = {"MR_LEl", "MR_LNTEl", "MR_TEl", "MR_REl"};
  string MR_mus[4]             = {"MR_LMu", "MR_LNTMu", "MR_TMu", "MR_RMu"};

  vector<string> leps_den      = Tools::toVector(MR_leps_den);
  vector<string> leps_num      = Tools::toVector(MR_leps_num);
  vector<string> leps_rat      = Tools::toVector(MR_leps_rat);
  vector<string> els_r         = Tools::toVector(MR_els     );
  vector<string> mus_r         = Tools::toVector(MR_mus     );

  vector<string> leps          = leps_den;
                 leps.insert(leps.end(), leps_num.begin(), leps_num.end());
  vector<string> leps_r        = leps;
                 leps.insert(leps.end(), leps_rat.begin(), leps_rat.end());


  // Setting Measurement Region
  setMeasurementRegion();

  // Measurement Region
  _hm->addVariable("MR_HT"         , 1000,   0.0, 1000.0, "H_T [GeV]"                            ); 
  _hm->addVariable("MR_MET"        , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  _hm->addVariable("MR_NBJets"     ,   20,   0.0,   20.0, "b-jet multiplicity"                   );
  _hm->addVariable("MR_NLEls"      ,   20,   0.0,   20.0, "loose electron multiplicity"          );
  _hm->addVariable("MR_NLNTEls"    ,   20,   0.0,   20.0, "loose not tight electron multiplicity");
  _hm->addVariable("MR_NTEls"      ,   20,   0.0,   20.0, "tight electron multiplicity"          );
  _hm->addVariable("MR_NVEls"      ,   20,   0.0,   20.0, "veto electron multiplicity"           );
  _hm->addVariable("MR_NJets"      ,   20,   0.0,   20.0, "jet multiplicity"                     );
  _hm->addVariable("MR_NLLeps"     ,   20,   0.0,   20.0, "loose lepton multiplicity"            );
  _hm->addVariable("MR_NLNTLeps"   ,   20,   0.0,   20.0, "loose not tight lepton multiplicity"  );
  _hm->addVariable("MR_NTLeps"     ,   20,   0.0,   20.0, "tight lepton multiplicity"            );
  _hm->addVariable("MR_NVLeps"     ,   20,   0.0,   20.0, "veto lepton multiplicity"             );
  _hm->addVariable("MR_NLMus"      ,   20,   0.0,   20.0, "loose muon multiplicity"              );
  _hm->addVariable("MR_NLNTMus"    ,   20,   0.0,   20.0, "loose not tight muon multiplicity"    );
  _hm->addVariable("MR_NTMus"      ,   20,   0.0,   20.0, "tight muon multiplicity"              );
  _hm->addVariable("MR_NVMus"      ,   20,   0.0,   20.0, "veto muon multiplicity"               );
  _hm->addVariable("MR_NVrtx"      ,   40,   0.0,   40.0, "vertex multiplicity"                  );
  _hm->addVariable("MR_JetCSVBTag" ,   50,   0.0,    1.0, "jet CSV B-Tag"                        );
  _hm->addVariable("MR_JetPt"      , 1000,   0.0, 1000.0, "P_T(jet) [GeV]"                       );

  registerLepPlots(leps, "DXY"    , 5000, 0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(leps, "DZ"     , 5000, 0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(leps, "SIP"    , 1000, 0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(leps, "Eta"    ,  240, 0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(leps, "Iso"    ,   50, 0.0,    1.0, "PF Iso (lep)"                         );
  registerLepPlots(leps, "MT"     , 1000, 0.0, 1000.0, "M_T(lep) [GeV]"                       );
  registerLepPlots(leps, "Pt"     , 1000, 0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(leps, "PtIso"  , 1000, 0.0, 1000.0, "P_T(lep)*(1+(pfRelIso-0.1)) [GeV]"    );
  registerLepPlots(leps, "PtMIso" , 1000, 0.0, 1000.0, "P_T(lep)*(1+(miniIso-cut)) [GeV]"     );
  registerLepPlots(leps, "PtMIso1", 1000, 0.0, 1000.0, "P_T(lep)*(1+(miniIso-cut)) [GeV]"     );
  registerLepPlots(leps, "PtMIso2", 1000, 0.0, 1000.0, "P_T(lep)*(1+(miniIso-cut)) [GeV]"     );
  registerLepPlots(leps, "PtJet"  , 1000, 0.0, 1000.0, "P_T(jet closest to lep) [GeV]"        );
  registerLepPlots(leps, "PtRel"  , 1000, 0.0, 1000.0, "PtRel(lep)"                           );


  // electron maps

  registerLepPlots(els_r, "Map"           , bins_pt_lep     .size()-1, bins_pt_lep     , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(e) [GeV]"                   , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "MapPt"         , bins_ptlep_lep  .size()-1, bins_ptlep_lep  , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(e) [GeV]"                   , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "MapPtIso"      , bins_ptlep_lep  .size()-1, bins_ptlep_lep  , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(e)*(1+(pfRelIso-0.1)) [GeV]", "#||{#eta}(e)"); 
  registerLepPlots(els_r, "MapPtJet"      , bins_ptlep_lep  .size()-1, bins_ptlep_lep  , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(jet closest to e) [GeV]"    , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "MapPtMIso"     , bins_ptmiso_lep .size()-1, bins_ptmiso_lep , bins_eta_el     .size()-1, bins_eta_el     , "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "MapPtMIso1"    , bins_ptmiso_lep .size()-1, bins_ptmiso_lep , bins_eta_el     .size()-1, bins_eta_el     , "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "MapPtMIso2"    , bins_ptmiso_lep .size()-1, bins_ptmiso_lep , bins_eta_el     .size()-1, bins_eta_el     , "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "SyncMapPt"     , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(e) [GeV]"                   , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "SyncMapPtJet"  , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(jet closest to e) [GeV]"    , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "SyncMapPtMIso" , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)"); 
  registerLepPlots(els_r, "SyncMapPtMIso2", bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)"); 

  // muon maps

  registerLepPlots(mus_r, "Map"           , bins_pt_lep     .size()-1, bins_pt_lep     , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(#mu) [GeV]"                   , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "MapPt"         , bins_ptlep_lep  .size()-1, bins_ptlep_lep  , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(#mu) [GeV]"                   , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "MapPtIso"      , bins_ptlep_lep  .size()-1, bins_ptlep_lep  , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(#mu)*(1+(pfRelIso-0.1)) [GeV]", "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "MapPtJet"      , bins_ptlep_lep  .size()-1, bins_ptlep_lep  , bins_eta_lep    .size()-1, bins_eta_lep    , "P_T(jet closest to #mu) [GeV]"    , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "MapPtMIso"     , bins_ptmiso_lep .size()-1, bins_ptmiso_lep , bins_eta_mu     .size()-1, bins_eta_mu     , "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "MapPtMIso1"    , bins_ptmiso_lep .size()-1, bins_ptmiso_lep , bins_eta_mu     .size()-1, bins_eta_mu     , "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "MapPtMIso2"    , bins_ptmiso_lep .size()-1, bins_ptmiso_lep , bins_eta_mu     .size()-1, bins_eta_mu     , "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "SyncMapPt"     , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(#mu) [GeV]"                   , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "SyncMapPtJet"  , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(jet closest to #mu) [GeV]"    , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "SyncMapPtMIso" , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)"); 
  registerLepPlots(mus_r, "SyncMapPtMIso2", bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)"); 



  //registerLepPlots(leps, "MapBJM"  , bins_pt.size()-1, bins_pt, bins_eta.size()-1, bins_eta, "P_T(lep)", "#||{#eta}(lep)"  ); 
 

}



//____________________________________________________________________________
void FakeRatioStudy::writeOutput(){
  /*
    writes all output of this class to the disk
    paramters: none
    return: none
  */

  divideFRMaps("MR", "El");
  divideFRMaps("MR", "Mu");

  //_hm->saveHistos ("FakeRatioStudy", _cfgName);
  //_au->saveNumbers("FakeRatioStudy", _cfgName);

}


//____________________________________________________________________________
void FakeRatioStudy::modifySkimming(){
  // if adding variables in the skimming tree is needed...
}


/*****************************************************************************
******************************************************************************
** OBJECT SELECTIONS                                                        **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatioStudy::collectKinematicObjects(){
  /*
    collects all kinematic objects needed in the code, i.e. applies all object selections
    parameters: none
    return: none
  */
  
  for(int i = 0; i < _vc->get("nLepGood"); ++i){

    bool loose = false;
    bool tight = false;

    // electrons
    if(std::abs(_vc->get("LepGood_pdgId", i)) == 11){		  
      if(looseElectronSelection(i)) {
        _lEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _lElIdx.push_back(i);
        _lLeps.push_back( _lEls[ _lEls.size()-1 ] );
        _lLepIdx.push_back(i);
        loose = true;
      }
      if(tightElectronSelection(i)) {
        _tEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _tElIdx.push_back(i);
        _tLeps.push_back( _tEls[ _tEls.size()-1 ] );
        _tLepIdx.push_back(i);
        tight = true;
      }
      if(loose && !tight) {
        _lntEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _lntElIdx.push_back(i);
        _lntLeps.push_back( _lntEls[ _lntEls.size()-1 ] );
        _lntLepIdx.push_back(i);
      }
      if(!loose && !tight) {
        if(vetoElectronSelection(i))  {
          _vEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					     _vc->get("LepGood_eta", i),
					     _vc->get("LepGood_phi", i),
					     _vc->get("LepGood_pdgId", i),
					     _vc->get("LepGood_charge", i),
					     0.0005) );
          _vLeps.push_back( _vEls[ _vEls.size()-1 ] );
        }
      }		
    }

    // muons
    else if(std::abs(_vc->get("LepGood_pdgId", i)) == 13){
      if(looseMuonSelection(i)) {
        _lMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _lMuIdx.push_back(i);
        _lLeps.push_back( _lMus[ _lMus.size()-1 ] );
        _lLepIdx.push_back(i);
        loose = true;
      }
      if(tightMuonSelection(i)) {
        _tMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _tMuIdx.push_back(i);
        _tLeps.push_back( _tMus[ _tMus.size()-1 ] );
        _tLepIdx.push_back(i);
        tight = true;
      }
      if(loose && !tight) {
        _lntMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _lntMuIdx.push_back(i);
        _lntLeps.push_back( _lntMus[ _lntMus.size()-1 ] );
        _lntLepIdx.push_back(i);
      }
      if(!loose && !tight) {
        if(vetoMuonSelection(i))  {
          _vMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					     _vc->get("LepGood_eta", i),
					     _vc->get("LepGood_phi", i),
					     _vc->get("LepGood_pdgId", i),
					     _vc->get("LepGood_charge", i),
					     0.105) );
          _vLeps.push_back( _vMus[ _vMus.size()-1 ] );
        }
      }
    }
  }

  _nLEls    = _lEls   .size();
  _nLNTEls  = _lntEls .size();
  _nTEls    = _tEls   .size();
  _nVEls    = _vEls   .size();
  _nLLeps   = _lLeps  .size();
  _nLNTLeps = _lntLeps.size();
  _nTLeps   = _tLeps  .size();
  _nVLeps   = _vLeps  .size();
  _nLMus    = _lMus   .size();
  _nLNTMus  = _lntMus .size();
  _nTMus    = _tMus   .size();
  _nVMus    = _vMus   .size();
  
  for(int i = 0; i < _vc->get("nJet"); ++i){
    if(goodJetSelection(i)) {
      _jets.push_back( Candidate::create(_vc->get("Jet_pt", i),
					                     _vc->get("Jet_eta", i),
					                     _vc->get("Jet_phi", i) ) );
      
    }
  }

  _nJets  = _jets.size();
  //_HT  = _susyMod->HT(_jets);
  _HT = HT(); 
  _met = Candidate::create(_vc->get("met_pt"), _vc->get("met_phi") );

}


//____________________________________________________________________________
bool FakeRatioStudy::goodJetSelection(int jetIdx){
  /*
    does the selection of good jets, i.e. minimum selection of jets 
    parameters: jetIdx
    return: true (if the jet is good), false (else)
  */
  
  counter("JetDenominator", kJetId);

  if(!makeCut<float>(         _vc->get("Jet_pt", jetIdx)  , 40.0, ">" , "pt selection"   , 0, kJetId) ) return false;
  if(!makeCut<float>(std::abs(_vc->get("Jet_eta", jetIdx)),  2.4, "<" , "eta selection"  , 0, kJetId) ) return false;
  if(!makeCut<float>(         _vc->get("Jet_id" , jetIdx) ,  1  , ">=", "pog pf loose id", 0, kJetId) ) return false;

  // CH: the requirement that dR(jet, every loose leption) > 1.0 in combination with
  // requirering EXACTLY one loose lepton in the measurement region, makes jet-lepton
  // cleaning obsolete
  
  for(unsigned int il=0; il<_lLeps.size(); ++il){
    float dr = KineUtils::dR(_lLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _lLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(!makeCut<float>(dr, 1.0, ">", "dR selection", 0, kJetId) ) return false;
  }

  // CH: this is jet-lepton cleaning: removing the closest jet to the loose lepton if dR < 0.4
  float dr_cache = 999999.;
  for(unsigned int il=0; il<_lLeps.size(); ++il){
    float dr = KineUtils::dR(_lLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _lLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  for(unsigned int il=0; il<_vLeps.size(); ++il){
    float dr = KineUtils::dR(_vLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _vLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.4, ">", "dR selection, jet-lepton cleaning", 0, kJetId) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::looseElectronSelection(int elIdx){
  /*
    does the selection of loose electrons
    parameters: elIdx
    return: true (if the electron is a loose electron), false (else)
  */

  counter("LooseElectronDenominator", kLElId);

  //CH: denominator is cut-based denominator for all IDs
  //CH: actually, we only take the tight ID (muons) / medium ID (electrons) on top of the LepGood preselection
  
  if(!makeCut<float>(          _vc->get("LepGood_pt" , elIdx)        , 10.   , ">"  , "pt selection"      , 0    , kLElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))       , 2.5   , "<"  , "eta selection"     , 0    , kLElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))       , 1.4442, "[!]", "eta selection veto", 1.566, kLElId)) return false;

  //CH: denominator is cut-based denominator for all IDs
  bool lepid = false;
  if  (_xpol == "isosip") lepid = electronCutId(elIdx, kLElId, 10.0, false, true );
  else                    lepid = electronCutId(elIdx, kLElId,  4.0, false, true );
  if  (_xpol == "isoid" ) lepid = electronCutId(elIdx, kLElId,  4.0, false, false); 
  if  (_mva  == "mva"   ) lepid = electronCutId(elIdx, kLElId, 10.0, false, false); 

  if(!makeCut( lepid, "lepton id", "=", kLElId)) return false;

  if(!makeCut<int>( _vc->get("LepGood_tightCharge", elIdx)           , 1     , ">"  , "charge selection"      , 0    , kLElId)) return false;
  
  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kLElId)) return false;

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kLElId) ) return false;


  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin", 1.2) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin", 1.5) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin", 2.4) ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin") ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, "<", "additional ETA bin") ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin") ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, "<", "additional ETA bin") ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin") ) return false;
  
  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::looseMuonSelection(int muIdx){
  /*
    does the selection of loose muons
    parameters: muIdx
    return: true (if the muon is a loose muon), false (else)
  */

  counter("LooseMuonDenominator", kLMuId);
  
  //CH: denominator is cut-based denominator for all IDs
  //CH: actually, we only take the tight ID (muons) / medium ID (electrons) on top of the LepGood preselection
  float cut = 10.;
  string ct = ">";
  float  up = 0;
  //if(_lepptcut == "mu15" && muIdx == 0){
  //  cut = 15.;
  //}
  //else if(_lepptcut == "mu5" && muIdx == 0){
  //  ct  = "[]";
  //  up  = 15.;
  //}

  //cout << "doing muon cut for " << muIdx << " with value " << cut << " and " << ct << endl;

  if(!makeCut<float>( _vc->get("LepGood_pt"         , muIdx)    , cut , ct , "pt selection"    , up, kLMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_eta"        , muIdx)    , 2.4 , "<", "eta selection"   , 0 , kLMuId)) return false;

  //CH: denominator is cut-based denominator for all IDs
  bool lepid = false;
  if  (_xpol == "isosip") lepid = muonCutId(muIdx, kLMuId, 10.0, false);
  else                    lepid = muonCutId(muIdx, kLMuId,  4.0, false);
  if  (_mva  == "mva"   ) lepid = muonCutId(muIdx, kLMuId, 10.0, false); 

  if(!makeCut( lepid, "lepton id", "=", kLMuId)) return false;


  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin", 1.2) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin", 1.5) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin", 2.4) ) return false;
  else if(_etabin == "08-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.8, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin") ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, "<", "additional ETA bin") ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin") ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, "<", "additional ETA bin") ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin") ) return false;
 
  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::tightElectronSelection(int elIdx){
  /*
    does the selection of tight electrons
    parameters: elIdx
    return: true (if the electron is a tight electron), false (else)
  */


  counter("TightElectronDenominator", kTElId);
 
  if(!makeCut<float>( _vc->get("LepGood_pt"      , elIdx)            , 10.   , ">"  , "pt selection"      , 0    , kTElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))       , 2.5   , "<"  , "eta selection"     , 0    , kTElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))       , 1.4442, "[!]", "eta selection veto", 1.566, kTElId)) return false;

  bool mvaid = electronMvaId(elIdx, kTElId);
  bool cutid = electronCutId(elIdx, kTElId, 4.0, true, true);
  bool lepid = false;

  if     (_mva == "mva"      ) lepid = mvaid;
  else if(_mva == "mvanotcut") lepid = mvaid && !cutid;
  else if(_mva == "mvaandcut") lepid = mvaid && cutid;
  else if(_mva == "cut"      ) lepid = cutid;
  else if(_mva == "cutnotmva") lepid = cutid && !mvaid;
  else if(_mva == "cutandmva") lepid = cutid && mvaid;
 
  if(!makeCut( lepid, "lepton id", "=", kTElId)) return false;

  if(!makeCut<int>( _vc->get("LepGood_tightCharge", elIdx)           , 1     , ">"  , "charge selection"  , 0    , kTElId)) return false;

  bool conv= (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kTElId)) return false; 

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kTElId) ) return false;

  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin", 1.2) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin", 1.5) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin", 2.4) ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin") ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, "<", "additional ETA bin") ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin") ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, "<", "additional ETA bin") ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin") ) return false;
  
  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::tightMuonSelection(int muIdx){
  /*
    does the selection of tight muons
    parameters: muIdx
    return: true (if the muon is a tight muon), false (else)
  */

  counter("TightMuonDenominator", kTMuId);
  float cut = 10.;
  string ct = ">";
  float  up = 0;
  //if(_lepptcut == "mu15" && muIdx == 0){
  //  cut = 15.;
  //}
  //else if(_lepptcut == "mu5"){
  //  ct  = "[]";
  //  up  = 15.;
  //}
  
  if(!makeCut<float>( _vc->get("LepGood_pt"      , muIdx)      , cut, ct , "pt selection"  , up, kTMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_eta"     , muIdx)      , 2.4, "<", "eta selection" , 0 , kTMuId)) return false;

  bool mvaid = muonMvaId(muIdx, kTMuId);
  bool cutid = muonCutId(muIdx, kTMuId, 4.0, true);
  bool lepid = false;

  if     (_mva == "mva"      ) lepid = mvaid;
  else if(_mva == "mvanotcut") lepid = mvaid && !cutid;
  else if(_mva == "mvaandcut") lepid = mvaid && cutid;
  else if(_mva == "cut"      ) lepid = cutid;
  else if(_mva == "cutnotmva") lepid = cutid && !mvaid;
  else if(_mva == "cutandmva") lepid = cutid && mvaid;
 
  if(!makeCut( lepid, "lepton id", "=", kTMuId)) return false;


  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin", 1.2) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin", 1.5) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin", 2.4) ) return false;
  else if(_etabin == "08-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.8, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin") ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, "<", "additional ETA bin") ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin") ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, "<", "additional ETA bin") ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin") ) return false;
 
  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::vetoElectronSelection(int elIdx){
  /*
    does the selection of veto electrons
    parameters: elIdx
    return: true (if the electron is a veto electron), false (else)
  */

  counter("VetoElectronDenominator", kVElId);

  //if(!makeCut<float>( _vc->get("LepGood_pt", elIdx), 10.0, "<", "pt selection", 0, kVElId)) return false; 

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kVElId) ) return false;
  
  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::vetoMuonSelection(int muIdx){
  /*
    does the selection of veto muons
    parameters: muIdx     
    return: true (if the muon is a veto muon), false (else)
  */

  counter("VetoMuonDenominator", kVMuId);
 
  //if(!makeCut<float>( _vc->get("LepGood_pt", muIdx), 10.0, "<", "pt selection", 0, kVMuId)) return false; 
  
  return true;

}



//____________________________________________________________________________
bool 
FakeRatioStudy::electronCutId(int elIdx, int cat, float sip, bool tight, bool mvatight){

  // CH: we do not extrapolate in ID, only sip and isolation 
  if(!makeCut(electronMvaCut(elIdx, mvatight) , "electron MVA Id", "=", cat)) return false;
  if(!makeCut(isolationCut  (elIdx, tight, 11), "isolation"      , "=", cat)) return false;
  
  if(!makeCut<float>(         _vc->get("LepGood_sip3d", elIdx) , sip , "<" , "SIP 3D"       , 0, cat)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"   , elIdx)), 0.1 , "<" , "dz selection" , 0, cat)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"  , elIdx)), 0.05, "<" , "dxy selection", 0, cat)) return false;

  return true;

}


//____________________________________________________________________________
bool
FakeRatioStudy::electronMvaCut(int elIdx, bool tight){

  float lepcut = 999.0;
  if(tight == true){
    if     (std::abs(_vc->get("LepGood_eta", elIdx)) < 0.8  ) lepcut =  0.73; 
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479) lepcut =  0.57; 
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 2.5  ) lepcut =  0.05; 
  }
  else {
    if     (std::abs(_vc->get("LepGood_eta", elIdx)) < 0.8  ) lepcut = -0.11; 
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479) lepcut = -0.35; 
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 2.5  ) lepcut = -0.55;     
    // CH: old denominator
    //if     (std::abs(_vc->get("LepGood_eta", elIdx)) < 0.8  ) lepcut =  0.35; 
    //else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479) lepcut =  0.20; 
    //else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 2.4  ) lepcut = -0.52; 
  }

  if(_vc->get("LepGood_mvaIdPhys14", elIdx) < lepcut) return false;

  return true;

}


//____________________________________________________________________________
bool 
FakeRatioStudy::electronMvaId(int elIdx, int cat){

  bool mvawp = false;
  if((_vc->get("LepGood_pt", elIdx) > 25 && _vc->get("LepGood_mvaSusy", elIdx) > 0   )
                                          || _vc->get("LepGood_mvaSusy", elIdx) > 0.53) mvawp = true;

  if(!makeCut( mvawp, "MVA WP", "=", cat)) return false;

  return true;

}


//____________________________________________________________________________
bool 
FakeRatioStudy::isolationCut(int lepIdx, bool tight, int pdg){
  /*
    does the isolation cut in different quantities: pfRelIso, pTrel, miniiso
  */

  if     (_lepiso == "pTrel"){
    if(tight  && (_vc->get("LepGood_jetPtRel", lepIdx) > 14. || _vc->get("LepGood_relIso03", lepIdx) < 0.1)) return true;
    if(!tight && (_vc->get("LepGood_jetPtRel", lepIdx) > 5.  || _vc->get("LepGood_relIso03", lepIdx) < 0.4)) return true;
  }

  else if(_lepiso == "miniiso"){ 
    if(tight  && _vc->get("LepGood_miniRelIso", lepIdx) < 0.05) return true;
    if(!tight && _vc->get("LepGood_miniRelIso", lepIdx) < 0.4 ) return true;
  }

  else if(_lepiso.find("mixiso") != string::npos){
    // Gio's medium WP
    float miniiso = 0.14;
    float ptratio = 0.68;
    float ptrel   = 6.7;
	if(_lepiso == "mixisoT") {
      miniiso = 0.1;
      ptratio = 0.7;
      ptrel   = 7.0;
    }
	else if(_lepiso == "mixisoVT") {
      miniiso = 0.075;
      ptratio = 0.725;
      ptrel   = 7.0;
    }
    else if(_lepiso == "mixisoHT") {
      miniiso = 0.05;
      ptratio = 0.725;
      ptrel   = 8.0;
    }

    if(tight && (_vc->get("LepGood_miniRelIso", lepIdx) < miniiso && 
                (_vc->get("LepGood_jetPtRel", lepIdx) > ptrel || _vc->get("LepGood_jetPtRatio", lepIdx) > ptratio))) return true;
    if(!tight && _xpol == "isofo3" && (_vc->get("LepGood_miniRelIso", lepIdx) < miniiso && 
                (_vc->get("LepGood_jetPtRel", lepIdx) > ptrel || 
                 _vc->get("LepGood_jetPtRatio", lepIdx) * ptMIso(lepIdx) / _vc->get("LepGood_pt", lepIdx) > ptratio))) return true;
    if(!tight && _xpol != "isofo3" && _vc->get("LepGood_miniRelIso", lepIdx) < 0.4) return true;
  }
  
  else {
    if(tight  && _vc->get("LepGood_relIso03", lepIdx) < 0.1) return true;
    if(!tight && _vc->get("LepGood_relIso03", lepIdx) < 0.5) return true;
  }

  return false;

}


//____________________________________________________________________________
bool 
FakeRatioStudy::muonCutId(int muIdx, int cat, float sip, bool tight){

  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx), 0   , ">", "medium muon ID"   , 0  , cat)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx), 1   , ">", "CUT error/pt < 20", 0  , cat)) return false;
  if(!makeCut(isolationCut(muIdx, tight, 13)                                    , "isolation"        , "=", cat)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d", muIdx)       , sip , "<", "SIP 3D"           , 0  , cat)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"   , muIdx))      , 0.1 , "<", "dz selection"     , 0  , cat)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"  , muIdx))      , 0.05, "<", "dxy selection"    , 0  , cat)) return false;

  return true;

}


//____________________________________________________________________________
bool 
FakeRatioStudy::muonMvaId(int muIdx, int cat){

  bool mvawp = false;
  if((_vc->get("LepGood_pt", muIdx) > 25 && _vc->get("LepGood_mvaSusy", muIdx) > 0   )
                                          || _vc->get("LepGood_mvaSusy", muIdx) > 0.53) mvawp = true;

  if(!makeCut(mvawp, "MVA WP", "=", cat)) return false;
  if(!makeCut<int>(_vc->get("LepGood_mediumMuonId", muIdx), 0, ">", "MVA medium muon ID"  , 0, cat)) return false;
  if(!makeCut<int>(_vc->get("LepGood_tightCharge" , muIdx), 1, ">", "MVA error/pt < 20", 0, cat)) return false;

  return true;

}



/*****************************************************************************
******************************************************************************
** GENERATOR INFORMATION                                                    **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FakeRatioStudy::bJetMatching(int lepIdx){
  /*
	matches the lepton to the closest jet (w.r.t. dR) and returns true if 
	this jet is a bJet (i.e. the lepton is a fake)
  */

  //CH: we take the tree variable rather than our own matched jet
  //int jetIdx = closestJet(lepIdx);
  //float btag = _vc->get("DiscJet_btagCSV", jetIdx);
  
  float btag = _vc->get("LepGood_jetBTagCSV", lepIdx);

  // combinedInclusiveSecondaryVertexV2BJetTags medium WP
  if(btag > 0.814) return true;

  return false;

}


//____________________________________________________________________________
bool FakeRatioStudy::cJetMatching(int lepIdx){

  float btag = _vc->get("LepGood_jetBTagCSV", lepIdx);
  if(btag > 0.423  && btag < 0.814) return true;

  return false;

}


//____________________________________________________________________________
int FakeRatioStudy::findHadrTau(){
  /*
    looks for Z->tautau, W->taunu decays in the gen particle collection of the event
    where all the taus decay hadronically
    parameters: none
    return: -1 (if no tau found), 
             0 (one or more taus found but at least one of them decays leptonically), 
             1 (hadr Z->tautau), 
             2 (hadr W+->tau+nu), 
             3 (hadr W-->tau-nu)
  */

  vector<int> ZIdx;
  vector<int> WIdx;
  vector<int> AntiWIdx;
  vector<int> TauIdx;
  vector<int> AntiTauIdx;
  vector<int> TauNuIdx;
  vector<int> AntiTauNuIdx;
 
  for(int i = 0; i < _vc->get("nGenPart"); ++i){
    if(_vc->get("GenPart_pdgId", i) ==  23) ZIdx        .push_back(i);
    if(_vc->get("GenPart_pdgId", i) ==  24) WIdx        .push_back(i);
    if(_vc->get("GenPart_pdgId", i) == -24) AntiWIdx    .push_back(i);
    if(_vc->get("GenPart_pdgId", i) ==  15) TauIdx      .push_back(i);
    if(_vc->get("GenPart_pdgId", i) == -15) AntiTauIdx  .push_back(i);
    if(_vc->get("GenPart_pdgId", i) ==  16) TauNuIdx    .push_back(i);
    if(_vc->get("GenPart_pdgId", i) == -16) AntiTauNuIdx.push_back(i);
  }

  if(TauIdx.size() == 0 && AntiTauIdx.size() == 0) return -1;

  for(int i = 0; i < TauIdx.size(); ++i)
    if(!noLeptonicDecay("GenPart", TauIdx[i]))
      return 0;

  for(int i = 0; i < AntiTauIdx.size(); ++i)
    if(!noLeptonicDecay("GenPart", AntiTauIdx[i]))
      return 0;

  if(ZIdx    .size() == TauIdx    .size() && ZIdx    .size() == AntiTauIdx  .size()) return 1;
  if(WIdx    .size() == AntiTauIdx.size() && WIdx    .size() == TauNuIdx    .size()) return 2;
  if(AntiWIdx.size() == TauIdx    .size() && AntiWIdx.size() == AntiTauNuIdx.size()) return 3;

  return -1;

}


//____________________________________________________________________________
bool FakeRatioStudy::fromHadrTau(int lepIdx, bool hadrTau){
  /*
    looks if a lepton most-likely comes from a hadronic tau decay
    attention: this function assumes that every tau decays hadronically, make sure that it is so
  */

  if(!hadrTau) return false;

  for(int i = 0; i < _vc->get("nGenPart"); ++i){
    int pdg = _vc->get("GenPart_pdgId", i);
    if(std::abs(pdg) == 15){
      float dr = KineUtils::dR(_vc->get("LepGood_eta", lepIdx), _vc->get("GenPart_eta", i),
                               _vc->get("LepGood_phi", lepIdx), _vc->get("GenPart_phi", i));
      if(dr < 0.3) 
        return true;
    }
  }

  return false;  

}


//____________________________________________________________________________
bool FakeRatioStudy::heppyFake(int lepIdx){
  /*
    does the matching to the fake source flavor via heppy's mcMatchAny
  */

  if     (_fakes == "b"    ) return (_vc->get("LepGood_mcMatchAny", lepIdx) == 5);
  else if(_fakes == "c"    ) return (_vc->get("LepGood_mcMatchAny", lepIdx) == 4);
  else if(_fakes == "light") return (_vc->get("LepGood_mcMatchAny", lepIdx) <= 3);

  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::jetFake(int lepIdx){
  /*
    does the matching to the fake source flavor via the btag of the closest jet
  */

  if     (_fakes == "bjet"    ) return bJetMatching(lepIdx);
  else if(_fakes == "cjet"    ) return cJetMatching(lepIdx);
  else if(_fakes == "lightjet") return lightJetMatching(lepIdx);

  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::lightJetMatching(int lepIdx){

  float btag = _vc->get("LepGood_jetBTagCSV", lepIdx);
  if(btag >= 0 && btag < 0.423) return true;

  return false;

}


//____________________________________________________________________________
bool FakeRatioStudy::noJetMatching(int lepIdx){

  float btag = _vc->get("LepGood_jetBTagCSV", lepIdx);
  if(btag < 0) return true;

  return false;

}


//____________________________________________________________________________
bool FakeRatioStudy::noLeptonicDecay(string collection, int partIdx){
  /*
    looks in a collection if a particle decays into leptons or not in terms of dR
  */

  for(int i = 0; i < _vc->get("n" + collection); ++i){
    unsigned int pdg = std::abs(_vc->get(collection + "_pdgId", i));
    float dr = KineUtils::dR(_vc->get(collection + "_eta", partIdx), _vc->get(collection + "_eta", partIdx),
    	                     _vc->get(collection + "_phi", i      ), _vc->get(collection + "_phi", i      ));
    if(pdg >= 11 && pdg <= 14 && dr < 0.3)
      return false;
  }

  return true;

}


//____________________________________________________________________________
void FakeRatioStudy::onlyFakes(CandList& list, vector<int>& idx, bool hadrTau){

  CandList n_list = list;
  vector<int> n_idx = idx;

  list.clear();
  idx.clear();

  for(int i = 0; i < n_list.size(); ++i){
    bool fromTau = fromHadrTau(n_idx[i], hadrTau);
    bool source = false;
    if(_fakes.find("jet") != std::string::npos) source = jetFake(n_idx[i]);
    else                                        source = heppyFake(n_idx[i]);

    // need to subtract the hadronic taus from all other sources
    if(_fakes == "tau") 
      source = fromTau;
    if(_fakes != "all" && _fakes != "tau" && source) 
      source = !fromTau;

	//cout << "fake of " << _vc->get("LepGood_mcMatchAny", n_idx[i]) << "," << fromTau << " = " << source << endl; 
	source == true;
    if(_vc->get("LepGood_mcMatchId", n_idx[i]) == 0 && source){ 
      list.push_back(n_list[i]);
      idx .push_back(n_idx [i]);
    }
  }  
}





/*****************************************************************************
******************************************************************************
** KINEMATIC REGION DEFINITIONS                                             **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatioStudy::setCut(std::string var, float valCut, std::string cType, float upValCut) {
  /*
    sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
    parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
    in case one cuts the variable in a range)
    return: none
  */


  // measurement region

  if(var == "NBJetsMR") {
    _valCutNBJetsMR   = valCut;
    _cTypeNBJetsMR    = cType;
    _upValCutNBJetsMR = upValCut;
  } 
	

}



//____________________________________________________________________________
void FakeRatioStudy::setMeasurementRegion() {
  /*
    sets the cuts of the measurement region (MR)
    parameters: none
    return: none
  */

  if(_mva=="mva" || _mva == "mvanotcut") _mvaId=true;


  if(_btag=="" || _btag=="std" || _btag=="40")
    _bvar = "nBJetMedium40";
  else if(_btag=="25" || _btag=="soft25")
    _bvar = "nBJetMedium25";
  else if(_btag=="15" || _btag=="IVF")
    _bvar = "nSoftBJetMedium25";
  else
    _bvar = "nBJetMedium40";

  if(_MR == "all") {
    setCut("NBJetsMR", 0, ">=");
  } 
  else if(_MR == "MR00") {
    setCut("NBJetsMR", 0, "=");
  }
  else if(_MR == "MR01") {
    setCut("NBJetsMR", 1, "=");
  }
  else if(_MR == "MR02") {
    setCut("NBJetsMR", 2, "=");
  }
  else if(_MR == "MR03") {
    setCut("NBJetsMR", 3, ">=");
  }
}



/*****************************************************************************
******************************************************************************
** EVENT SELECTIONS                                                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FakeRatioStudy::genMRSelection(){
  /*
	does a slimmer version of the MR selection by only requiring NLLeps == 1 and 
	NJets >= 1 and NBJets given by <MR value>
	in case of a sample where we should use fakes (pfx: fake) we only look at the
	fake loose lepton and remove all other leptons from the collections
  */ 

  // gen matching: if defined, only use the fake lepton, and remove all others from the collection
  if( _sampleName.find("fake") != (size_t) -1){

    //if(_fakes == "tau" && !makeCut( findHadrTau() > 0 , true, "=" , "hadronic tau decay")) return false;
	bool hadrTau = (findHadrTau() > 0);

    onlyFakes(_lEls   , _lElIdx   , hadrTau);
    onlyFakes(_lntEls , _lntElIdx , hadrTau);
    onlyFakes(_tEls   , _tElIdx   , hadrTau);
    onlyFakes(_lLeps  , _lLepIdx  , hadrTau);
    onlyFakes(_lntLeps, _lntLepIdx, hadrTau);
    onlyFakes(_tLeps  , _tLepIdx  , hadrTau);
    onlyFakes(_lMus   , _lMuIdx   , hadrTau);
    onlyFakes(_lntMus , _lntMuIdx , hadrTau);
    onlyFakes(_tMus   , _tMuIdx   , hadrTau);

  }  
  counter("genCateg selection");

  // lepton multiplicity
  if     (_lepflav=="all" && !makeCut<int>( _nLLeps          , 1   , ">=", "lepton multiplicity and flavor" ) ) return false; 
  else if(_lepflav=="e"   && !makeCut( _nLEls>=1 && _nLMus==0, true, "=" , "lepton multiplicity and flavor" ) ) return false;
  else if(_lepflav=="m"   && !makeCut( _nLEls==0 && _nLMus>=1, true, "=" , "lepton multiplicity and flavor" ) ) return false;

  // jet multiplicity
  //if(!makeCut<int>( _nJets         , 1              , ">="          , "jet multiplicity") ) return false; 
  if(!makeCut<int>( _vc->get("nJet40"), 1              , ">="          , "jet multiplicity") ) return false; 

  // b-jet multiplicity
  if(!makeCut<int>(_vc->get(_bvar), _valCutNBJetsMR, _cTypeNBJetsMR, "b-jet multiplicity", _upValCutNBJetsMR) ) return false;

  // additional HT selection
  if(_htbin == "0"   && !makeCut<float>(_HT, 200, "<" , "additional HT bin"     ) ) return false;
  if(_htbin == "200" && !makeCut<float>(_HT, 200, "[]", "additional HT bin", 400) ) return false;
  if(_htbin == "400" && !makeCut<float>(_HT, 400, ">" , "additional HT bin"     ) ) return false;

  // counting fakes
  if(std::abs(_lLeps[0]->pdgId()) == 11) counter("counting events with one fake electron");
  if(std::abs(_lLeps[0]->pdgId()) == 13) counter("counting events with one fake muon");


  //// counting Z->tautau, W->taunu in the event
  //bool foundZ         = false;
  //bool foundW         = false;
  //bool foundantiW     = false;
  //bool foundtau       = false;
  //bool foundtaunu     = false;
  //bool foundantitau   = false;
  //bool foundantitaunu = false;
  //bool foundZtautau   = false;
  //bool foundWataunu   = false; 
  //bool foundaWtauanu  = false;

  //for(int i = 0; i < _vc->get("nGenPart"); ++i){
  //  if(_vc->get("GenPart_pdgId", i) == 23 ) foundZ         = true;
  //  if(_vc->get("GenPart_pdgId", i) == 24 ) foundW         = true;
  //  if(_vc->get("GenPart_pdgId", i) == -24) foundantiW     = true;
  //  if(_vc->get("GenPart_pdgId", i) == 15 ) foundtau       = true;
  //  if(_vc->get("GenPart_pdgId", i) == -15) foundantitau   = true;
  //  if(_vc->get("GenPart_pdgId", i) == 16 ) foundtaunu     = true;
  //  if(_vc->get("GenPart_pdgId", i) == -16) foundantitaunu = true;
  //}

  //// counting events with one fake lepton and a Z->tau+tau-
  //if(foundZ && foundtau && foundantitau){ 
  //  foundZtautau = true;
  //  if(std::abs(_lLeps[0]->pdgId()) == 11) counter("counting events with one fake electron and Z->tau+tau-");
  //  if(std::abs(_lLeps[0]->pdgId()) == 13) counter("counting events with one fake muon and Z->tau+tau-");
  //}
  //
  //// counting events with one fake lepton and a W+->tau+nu
  //if(foundW && foundantitau && foundtaunu){ 
  //  foundWataunu = true;
  //  if(std::abs(_lLeps[0]->pdgId()) == 11) counter("counting events with one fake electron and W+->tau+nu");
  //  if(std::abs(_lLeps[0]->pdgId()) == 13) counter("counting events with one fake muon and W+->tau+nu");
  //}
  //
  //// counting events with one fake lepton and a W-->tau-nubar
  //if(foundantiW && foundtau && foundantitaunu){ 
  //  foundaWtauanu = true;
  //  if(std::abs(_lLeps[0]->pdgId()) == 11) counter("counting events with one fake electron and W-->tau-nubar");
  //  if(std::abs(_lLeps[0]->pdgId()) == 13) counter("counting events with one fake muon and W-->tau-nubar");
  //}

  // removing events with Z->tau+tau-, W+->tau+nu, W-->tau-nubar (= cleaning of hadronic tau decays)
  //if(!makeCut(!foundZtautau && !foundWataunu && !foundaWtauanu, true, "=", "cleaning hadronic tau decays from Z or W") ) return false; 


// looking for the source of muons
//if(std::abs(_lLeps[0]->pdgId()) == 13){
//cout << "-------- new event (" << _vc->get("run") << ":" << _vc->get("lumi") << ":" << _vc->get("evt") << ") -------" << endl;
//cout << "reco lepton: " << _lLepIdx[0] << ":" << _lLeps[0]->pdgId() << ":" << _lLeps[0]->pt() << ":" << _lLeps[0]->eta() << ":" << _lLeps[0]->phi() << endl;
//++mucounter;
//for(int i = 0; i < _vc->get("nGenPart"); ++i){
//  if(std::abs(_vc->get("GenPart_pdgId", i)) != 15) continue;
//  float dr = Tools::dR(_lLeps[0]->eta(), _vc->get("GenPart_eta",i),
//                       _lLeps[0]->phi(), _vc->get("GenPart_phi",i));
//  cout << "looping on GenPart " << i << ":" << _vc->get("GenPart_pdgId", i) << ":" << _vc->get("GenPart_pt",i) << ":" << _vc->get("GenPart_eta",i) << ":" << _vc->get("GenPart_phi",i) << ":" << dr << endl;
//}
//for(int i = 0; i < _vc->get("nGenBHad"); ++i){
//  float dr = Tools::dR(_lLeps[0]->eta(), _vc->get("GenBHad_eta",i),
//                       _lLeps[0]->phi(), _vc->get("GenBHad_phi",i));
//  cout << "looping on GenBHad " << i << ":" << _vc->get("GenBHad_pdgId", i) << ":" << _vc->get("GenBHad_pt",i) << ":" << _vc->get("GenBHad_eta",i) << ":" << _vc->get("GenBHad_phi",i) << ":" << dr << endl;
//}
//}

  return true;

}


//____________________________________________________________________________
bool FakeRatioStudy::mrSelection(){
  // measurement region as in SUS-13-013

  // triggers  
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleMu"), 1, "=", "HLT DoubleMu") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleEl"), 1, "=", "HLT DoubleEl") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_MuEG")    , 1, "=", "HLT MuEG"    ) ) return false;	

  // lepton multiplicity
  if     (_lepflav=="all" && !makeCut<int>( _nLLeps          , 1   , ">=", "lepton multiplicity and flavor" ) ) return false; 
  else if(_lepflav=="e"   && !makeCut( _nLEls>=1 && _nLMus==0, true, "=", "lepton multiplicity and flavor" ) ) return false;
  else if(_lepflav=="m"   && !makeCut( _nLEls==0 && _nLMus>=1, true, "=", "lepton multiplicity and flavor" ) ) return false;

  // veto leptons 
  if(!makeCut<int>( _nVLeps      , 0   , "=" , "lepton veto"     ) ) return false; 

  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity") ) return false; 

  // b-jet multiplicity
  if(!makeCut<int>(_vc->get(_bvar), _valCutNBJetsMR, _cTypeNBJetsMR, "b-jet multiplicity", _upValCutNBJetsMR) ) return false;

  // MET 
  if(!makeCut<float>( _met->pt() , 20.0, "<" , "MET selection"   ) ) return false;

  // MT
  Candidate* MT = nullptr;
  MT = Candidate::create( _lLeps[0], _met);
  if(!makeCut<float>( MT->mass() , 20.0, "<" , "MT selection"    ) ) return false;

  return true;

}

//____________________________________________________________________________
bool FakeRatioStudy::skimSelection(){

  // triggers  
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleMu"), 1, "=", "HLT DoubleMu") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleEl"), 1, "=", "HLT DoubleEl") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_MuEG")    , 1, "=", "HLT MuEG"    ) ) return false;	

  // lepton multiplicity
  if(!makeCut<int>( _nLLeps, 1, ">=", "lepton multiplicity and flavor" ) ) return false; 

  // jet multiplicity
  if(!makeCut<int>( _nJets , 1, ">=", "jet multiplicity") ) return false; 

  return true;

}

//____________________________________________________________________________
bool FakeRatioStudy::syncSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015


  // lepton multiplicity
  //if(!makeCut<int>( _nLMus, 1, ">=", "lepton multiplicity and flavor" ) ) return false; 
  if     (_lepflav=="all" && !makeCut<int>( _nLLeps          , 1   , "=", "lepton multiplicity and flavor" ) ) return false; 
  else if(_lepflav=="e"   && !makeCut( _nLEls==1 && _nLMus==0, true, "=", "lepton multiplicity and flavor" ) ) return false;
  else if(_lepflav=="m"   && !makeCut( _nLEls==0 && _nLMus==1, true, "=", "lepton multiplicity and flavor" ) ) return false;

  //if(_tLeps.size() == 1){
  //  cout << _vc->get("run") << ":" << _vc->get("lumi") << ":" << setprecision(10)<< _vc->get("evt") << endl;
  //}

  //CH: RA5 guys select lep pt later one
  if     (_lepptcut == "mu15" && _lLeps[0] -> pt() < 15.) return false;
  else if(_lepptcut == "mu5"  && _lLeps[0] -> pt() > 15.) return false;
 
  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity") ) return false; 

  // b-jet multiplicity
  //if(!makeCut<int>(_vc->get(_bvar), _valCutNBJetsMR, _cTypeNBJetsMR, "b-jet multiplicity", _upValCutNBJetsMR) ) return false;

  // MET 
  if(!makeCut<float>( _met->pt() , 20.0, "<" , "MET selection"   ) ) return false;

  // MT
  Candidate* MT = nullptr;
  MT = Candidate::create( _lLeps[0], _met);
  if(!makeCut<float>( MT->mass() , 20.0, "<" , "MT selection"    ) ) return false;

  return true;

}




/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatioStudy::fillEventPlots(std::string kr){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  fill(kr + "_HT"        , _HT                 , _weight);
  fill(kr + "_MET"       , _met->pt()          , _weight);
  fill(kr + "_NBJets"    , _vc->get(_bvar)    , _weight);
  fill(kr + "_NLEls"     , _lEls.size()        , _weight);
  fill(kr + "_NTEls"     , _tEls.size()        , _weight);
  fill(kr + "_NVEls"     , _vEls.size()        , _weight);
  fill(kr + "_NJets"     , _nJets              , _weight);
  fill(kr + "_NLLeps"    , _lLeps.size()       , _weight);
  fill(kr + "_NTLeps"    , _tLeps.size()       , _weight);
  fill(kr + "_NVLeps"    , _vLeps.size()       , _weight);
  fill(kr + "_NLMus"     , _lMus.size()        , _weight);
  fill(kr + "_NTMus"     , _tMus.size()        , _weight);
  fill(kr + "_NVMus"     , _vMus.size()        , _weight);
  fill(kr + "_NVrtx"     , _vc->get("nVert")  , _weight);

}


//____________________________________________________________________________
void FakeRatioStudy::fillFRMaps(string prepend, Candidate * lep, int lepIdx){

  fill(prepend + "Map"       , _vc->get("LepGood_pt", lepIdx), std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "MapPt"     , _vc->get("LepGood_pt", lepIdx), std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "MapPtIso"  , ptIso(lepIdx)                  , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "MapPtMIso" , ptMIso(lepIdx)                 , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "MapPtMIso1", ptMIso1(lepIdx)                , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "MapPtMIso2", ptMIso2(lepIdx)                , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "MapPtJet"  , closestJetPt(lepIdx)           , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);

  fill(prepend + "SyncMapPt"     , overflowPt(_vc->get("LepGood_pt", lepIdx)), std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "SyncMapPtJet"  , overflowPt(closestJetPt(lepIdx))          , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "SyncMapPtMIso" , overflowPt(ptMIso(lepIdx))                , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "SyncMapPtMIso2", overflowPt(ptMIso2(lepIdx))               , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  //if(bJetMatching(_lElIdx[i]))
  //  fill(kr + "_LElMapBJM" , _vc->get("LepGood_pt", _lElIdx[i] ), fabs(_vc->get("LepGood_eta", _lElIdx[i] )), _weight);

}


//____________________________________________________________________________
void FakeRatioStudy::fillFakeRatioMaps(std::string kr){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */


  for(int i = 0; i < _lEls  .size(); ++i) { fillFRMaps(kr + "_LEl"  , _lEls[i]  , _lElIdx[i]  ); }
  for(int i = 0; i < _lntEls.size(); ++i) { fillFRMaps(kr + "_LNTEl", _lntEls[i], _lntElIdx[i]); }
  for(int i = 0; i < _tEls  .size(); ++i) { fillFRMaps(kr + "_TEl"  , _tEls[i]  , _tElIdx[i]  ); 
                                            fillFRMaps(kr + "_REl"  , _tEls[i]  , _tElIdx[i]  ); }
  for(int i = 0; i < _lMus  .size(); ++i) { fillFRMaps(kr + "_LMu"  , _lMus[i]  , _lMuIdx[i]  ); }
  for(int i = 0; i < _lntMus.size(); ++i) { fillFRMaps(kr + "_LNTMu", _lntMus[i], _lntMuIdx[i]); }
  for(int i = 0; i < _tMus  .size(); ++i) { fillFRMaps(kr + "_TMu"  , _tMus[i]  , _tMuIdx[i]  ); 
                                            fillFRMaps(kr + "_RMu"  , _tMus[i]  , _tMuIdx[i]  ); }

}


//____________________________________________________________________________
void FakeRatioStudy::fillFakeRatioPlots(std::string kr){
  /*
    fills the fake ratio 1d-plots for leptons
    parameters: none
    return: none
  */


}


//____________________________________________________________________________
void FakeRatioStudy::fillLepPlots(string prepend, Candidate * lep, int lepIdx){
  /*
    fills the control plots for leptons PER LEPTON
  */  

  fill(prepend + "DXY"    , std::abs(_vc->get("LepGood_dxy"     , lepIdx)), _weight);
  fill(prepend + "DZ"     , std::abs(_vc->get("LepGood_dz"      , lepIdx)), _weight);
  fill(prepend + "SIP"    ,          _vc->get("LepGood_sip3d"   , lepIdx) , _weight);
  fill(prepend + "Eta"    , std::abs(_vc->get("LepGood_eta"     , lepIdx)), _weight);
  fill(prepend + "Iso"    ,          _vc->get("LepGood_relIso03", lepIdx) , _weight);
  fill(prepend + "Pt"     ,          _vc->get("LepGood_pt"      , lepIdx) , _weight);
  fill(prepend + "PtRel"  ,          _vc->get("LepGood_jetPtRel", lepIdx) , _weight);
  fill(prepend + "PtIso"  , ptIso       (lepIdx)                          , _weight);
  fill(prepend + "PtMIso" , ptMIso      (lepIdx)                          , _weight);
  fill(prepend + "PtMIso1", ptMIso1     (lepIdx)                          , _weight);
  fill(prepend + "PtMIso2", ptMIso2     (lepIdx)                          , _weight);
  fill(prepend + "PtJet"  , closestJetPt(lepIdx)                          , _weight);
  fill(prepend + "MT"     , Candidate::create( lep, _met) -> mass()       , _weight);

}


//____________________________________________________________________________
void FakeRatioStudy::fillLeptonPlots(std::string kr){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  for(int i = 0; i < _lEls   .size(); ++i) fillLepPlots(kr + "_LEl"   , _lEls   [i], _lElIdx   [i]);
  for(int i = 0; i < _lntEls .size(); ++i) fillLepPlots(kr + "_LNTEl" , _lntEls [i], _lntElIdx [i]);
  for(int i = 0; i < _tEls   .size(); ++i) fillLepPlots(kr + "_TEl"   , _tEls   [i], _tElIdx   [i]);
  for(int i = 0; i < _lLeps  .size(); ++i) fillLepPlots(kr + "_LLep"  , _lLeps  [i], _lLepIdx  [i]);
  for(int i = 0; i < _lntLeps.size(); ++i) fillLepPlots(kr + "_LNTLep", _lntLeps[i], _lntLepIdx[i]);
  for(int i = 0; i < _tLeps  .size(); ++i) fillLepPlots(kr + "_TLep"  , _tLeps  [i], _tLepIdx  [i]);
  for(int i = 0; i < _lMus   .size(); ++i) fillLepPlots(kr + "_LMu"   , _lMus   [i], _lMuIdx   [i]);
  for(int i = 0; i < _lntMus .size(); ++i) fillLepPlots(kr + "_LNTMu" , _lntMus [i], _lntMuIdx [i]);
  for(int i = 0; i < _tMus   .size(); ++i) fillLepPlots(kr + "_TMu"   , _tMus   [i], _tMuIdx   [i]);

  for(int i = 0; i < _tLeps  .size(); ++i) fillAvgJetPtRatio(_tLepIdx[i]);

}


//____________________________________________________________________________
void FakeRatioStudy::fillAvgJetPtRatio(int lepIdx){

  _averageJetPtRatio += _vc->get("LepGood_jetPtRatio", lepIdx);
  ++_numJetPtRatio;

}


//____________________________________________________________________________
void FakeRatioStudy::fillJetPlots(std::string kr){
  /*
    fills the control plots for jets
    parameters: none
    return: none
  */


  for(int i = 0; i < _nJets; ++i){
    fill(kr + "_JetPt"     , _jets[i]->pt(), _weight);
  }

}


//____________________________________________________________________________
float 
FakeRatioStudy::HT(){
  /*
    computes HT for a given list of selected jets
    parameters: jet_label
    return: HT
  */

  float ht = 0;

  for(int i = 0; i < _nJets; ++i) 
    ht += _jets[i]->pt();

  return ht;

}


//____________________________________________________________________________
float FakeRatioStudy::ptIso(int lepIdx){

  double min = 0.;
  float cut = 0.1;
  return _vc->get("LepGood_pt", lepIdx) * (1.0 + std::max(min, _vc->get("LepGood_relIso03", lepIdx) - cut));

}


//____________________________________________________________________________
float FakeRatioStudy::ptMIso(int lepIdx){

  //CH: this is pure miniIso corrected pt

  double min = 0.;
  float miniiso = 0.14;
  if     (_lepiso == "mixisoT" ) miniiso = 0.1;
  else if(_lepiso == "mixisoVT") miniiso = 0.075;
  else if(_lepiso == "mixisoHT") miniiso = 0.05;

  return _vc->get("LepGood_pt", lepIdx) * (1.0 + std::max(min, _vc->get("LepGood_miniRelIso", lepIdx) - miniiso));

}


//____________________________________________________________________________
float FakeRatioStudy::ptMIso1(int lepIdx){

  //CH: this is GiovanniP's miniIso corrected pt, see ECO meeting 31st of March 

  double min = 0.;
  float miniiso = 0.14;
  float ptrel = 6.7; 
  if     (_lepiso == "mixisoT") {
    miniiso = 0.1;
    ptrel = 7.0;
  }
  else if(_lepiso == "mixisoVT") {
    miniiso = 0.075;
    ptrel = 7.0;
  }
  else if(_lepiso == "mixisoHT") {
    miniiso = 0.05;
    ptrel = 8.0;
  }

  bool miso = true;
  if(_vc->get("LepGood_pt", lepIdx) > 25 && _vc->get("LepGood_jetPtRel", lepIdx) > ptrel)
    miso = false;

  //if(!miso) 
  //  return _alpha[_inds] * closestJetPt(lepIdx); 

  return _vc->get("LepGood_pt", lepIdx) * (1.0 + std::max(min, _vc->get("LepGood_miniRelIso", lepIdx) - miniiso));

}


//____________________________________________________________________________
float FakeRatioStudy::ptMIso2(int lepIdx){

  //CH: Giuseppe's cone correction see RA5 meeting 15th April

  double min = 0.;
  float miniiso = 0.14;
  float ptratio = 0.68;
  float ptrel = 6.7; 
  if     (_lepiso == "mixisoT") {
    miniiso = 0.1;
    ptratio = 0.7;
    ptrel = 7.0;
  }
  else if(_lepiso == "mixisoVT") {
    miniiso = 0.075;
    ptratio = 0.725;
    ptrel = 7.0;
  }
  else if(_lepiso == "mixisoHT") {
    miniiso = 0.05;
    ptratio = 0.725;
    ptrel = 8.0;
  }

  bool miso = false;
  if(_vc->get("LepGood_jetPtRel", lepIdx) > ptrel)
    miso = true;

  if(!miso) 
    return std::max(_vc->get("LepGood_pt", lepIdx), (double) closestJetPt(lepIdx) * ptratio);

  return _vc->get("LepGood_pt", lepIdx) * (1.0 + std::max(min, _vc->get("LepGood_miniRelIso", lepIdx) - miniiso));

}

//____________________________________________________________________________
//int FakeRatioStudy::closestJet(int lepIdx){
//
//  int closest = -1;
//  float dr_cache = 999.;
//  for(unsigned int i = 0; i < _vc->get("nDiscJet"); ++i){
//    float dr = Tools::dR(_vc->get("LepGood_eta", lepIdx), _vc->get("DiscJet_eta", i),
//                         _vc->get("LepGood_phi", lepIdx), _vc->get("DiscJet_phi", i));
//    if(dr < dr_cache && dr < 0.4){
//      dr_cache = dr;
//      closest = i;
//    } 
//  }
//  if(closest == -1){
//    for(unsigned int i = 0; i < _vc->get("nJet"); ++i){
//      float dr = Tools::dR(_vc->get("LepGood_eta", lepIdx), _vc->get("Jet_eta", i),
//                           _vc->get("LepGood_phi", lepIdx), _vc->get("Jet_phi", i));
//      if(dr < dr_cache && dr < 0.4){
//        dr_cache = dr;
//        closest = i;
//      } 
//    }
//  }
//
//  return closest;
//}


//____________________________________________________________________________
float FakeRatioStudy::closestJetPt(int lepIdx){

  return _vc->get("LepGood_pt", lepIdx) / _vc->get("LepGood_jetPtRatio", lepIdx);

  //CH: the trees do not contain all jets, see email discussion 9.03.2015
  //int cj = closestJet(lepIdx);
  //if(cj > -1) return _vc->get("Jet_pt", closestJet(lepIdx));
  //else        return _vc->get("LepGood_pt", lepIdx); 

  //return -1;

}


//____________________________________________________________________________
float FakeRatioStudy::overflowPt(float rawPt){

	if(rawPt >= 70.) return 60.;

	return rawPt;
}


//____________________________________________________________________________
//int 
//FakeRatioStudy::eventCharge(){
//  /*
//    returns the total charge in the event as calculated from the electrons and
//    leptons that have been selected
//    parameters: electron_label, muon_label
//    return: the total charge as int
//  */
//
//  int charge = 0;
//
//  for(int i=0;i<_nEls;++i)
//    charge += _els[i]->charge();
//
//  for(int i=0;i<_nMus;++i)
//    charge += _mus[i]->charge();
//
//  return charge; 
//
//}

