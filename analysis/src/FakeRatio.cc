/*****************************************************************************
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


#include "analysis/src/FakeRatio.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
FakeRatio::FakeRatio(std::string cfg){
  /* 
     constructs the FakeRatio class 
     parameters: configuration_file
     return: none
  */
  
  startExecution(cfg);
  initialize();

}


//____________________________________________________________________________
FakeRatio::~FakeRatio(){
  /* 
     destructs the FakeRatio class 
     parameters: none
     return: none
  */

}


//____________________________________________________________________________
void FakeRatio::initialize(){
  /*
    initializes the FakeRatio class
    parameters: none
    return: none
  */

  //Tree Variables
  _bvar  = "nBJetMedium25";
  _leps  = "LepGood";
  _jets  = "Jet"; 
  _mets  = "met";
  _nvert = "nVert";

  //Tree Branches
  _vc->registerVar("run"                           , "I" );
  _vc->registerVar("lumi"                          , "I" );
  _vc->registerVar("evt"                           , "I" );
  _vc->registerVar("HLT_SingleMu"                  , "F" );
  _vc->registerVar("HLT_MuEG"                      , "F" );
  _vc->registerVar("HLT_TripleEl"                  , "F" );
  _vc->registerVar("HLT_DoubleEl"                  , "F" );
  _vc->registerVar("HLT_DoubleMu"                  , "F" );
  _vc->registerVar(_nvert                          , "I" );
  _vc->registerVar("nTrueInt"                      , "I" );
  _vc->registerVar("puWeight"                      , "F" );
  _vc->registerVar("genWeight"                     , "F" );
  _vc->registerVar("n" + _leps                     , "I" );
  _vc->registerVar(_leps + "_pt"                   , "AF");
  _vc->registerVar(_leps + "_eta"                  , "AF");
  _vc->registerVar(_leps + "_phi"                  , "AF");
  _vc->registerVar(_leps + "_charge"               , "AI");
  _vc->registerVar(_leps + "_tightCharge"          , "AI");
  _vc->registerVar(_leps + "_mediumMuonId"         , "AI");
  _vc->registerVar(_leps + "_mvaIdPhys14"          , "AF");
  _vc->registerVar(_leps + "_pdgId"                , "AI");
  _vc->registerVar(_leps + "_relIso03"             , "AF");
  _vc->registerVar(_leps + "_relIso04"             , "AF");
  _vc->registerVar(_leps + "_jetPtRatio"           , "AF");
  _vc->registerVar(_leps + "_jetPtRel"             , "AF");
  _vc->registerVar(_leps + "_miniRelIso"           , "AF");
  _vc->registerVar(_leps + "_dxy"                  , "AF");
  _vc->registerVar(_leps + "_dz"                   , "AF");
  _vc->registerVar(_leps + "_sip3d"                , "AF");
  _vc->registerVar(_leps + "_pfMuonId"             , "AI");
  _vc->registerVar(_leps + "_tightId"              , "AI");
  _vc->registerVar(_leps + "_looseIdSusy"          , "AI");
  _vc->registerVar(_leps + "_convVeto"             , "AI");
  _vc->registerVar(_leps + "_lostHits"             , "AI");
  _vc->registerVar(_leps + "_eleCutIdCSA14_50ns_v1", "AI");
  _vc->registerVar(_leps + "_eleCutIdCSA14_50ns_v1", "AI");
  _vc->registerVar(_leps + "_eleCutId2012_full5x5" , "AI");
  _vc->registerVar(_leps + "_mvaSusyPHYS14"        , "AF");
  _vc->registerVar(_leps + "_mvaSusy"              , "AF");
  _vc->registerVar(_leps + "_mcMatchId"            , "AI");
  _vc->registerVar(_leps + "_mcMatchAny"           , "AI");
  _vc->registerVar(_leps + "_jetBTagCSV"           , "AF");
  _vc->registerVar(_mets + "_pt"                   , "F" );
  _vc->registerVar(_mets + "_eta"                  , "F" );
  _vc->registerVar(_mets + "_phi"                  , "F" );
  _vc->registerVar(_mets + "_mass"                 , "F" );
  _vc->registerVar("n" + _jets                     , "I" );
  _vc->registerVar(_jets + "_id"                   , "AI");
  _vc->registerVar(_jets + "_pt"                   , "AF");
  _vc->registerVar(_jets + "_rawPt"                , "AF");
  _vc->registerVar(_jets + "_eta"                  , "AF");
  _vc->registerVar(_jets + "_phi"                  , "AF");
  _vc->registerVar(_jets + "_mass"                 , "AF");
  _vc->registerVar(_jets + "_btagCSV"              , "AF");
  
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
  _au->addCategory( kDenEls  , "Denominator Electrons");
  _au->addCategory( kNumEls  , "Numerator Electrons"  );
  _au->addCategory( kVetEls  , "Veto Electrons"       );
  _au->addCategory( kDenMus  , "Denominator Muons"    );
  _au->addCategory( kNumMus  , "Numerator Muons"      );
  _au->addCategory( kVetMus  , "Veto Muons"           );
  _au->addCategory( kGoodJets, "Good Jets"            );

  //SusyModule
  _susyMod = new SusyModule(_vc);

}


//____________________________________________________________________________
void FakeRatio::modifyWeight() {
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
void FakeRatio::run(){


  _denEls .clear();
  _denLeps.clear();
  _denMus .clear();
  _numEls .clear();
  _numLeps.clear();
  _numMus .clear();
  _vetEls .clear();
  _vetLeps.clear();
  _vetMus .clear();

  _goodJets.clear();

  _denElsIdx .clear();
  _denLepsIdx.clear();
  _denMusIdx .clear();
  _numElsIdx .clear();
  _numLepsIdx.clear();
  _numMusIdx .clear();

  counter("denominator");

	
  // prepare event selection
  collectKinematicObjects();
	
	
  // skimming
  //if(!skimSelection()) return;
  //fillSkimTree();
  //return;


  // measurement region selection
  if(!mrSelection()) return;

	
  // calling the modules
  fillEventPlots   ();
  fillFakeRatioMaps();
  fillJetPlots     ();
  fillLeptonPlots  ();

	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::divideFRMap(string kr, string postpend){

  for(unsigned int i=0; i<_numDS; ++i){
    TH1 * denom = _hm -> getHisto(kr + "_Den" + postpend, i);
    TH1 * num   = _hm -> getHisto(kr + "_Rat" + postpend, i);
    num -> Divide(denom);
  }
 
}


//____________________________________________________________________________
void FakeRatio::divideFRMaps(){

  divideFRMap("MR", "ElMapPt"    );
  divideFRMap("MR", "ElMapPtJet" );
  divideFRMap("MR", "ElMapPtCorr");
  divideFRMap("MR", "MuMapPt"    );
  divideFRMap("MR", "MuMapPtJet" );
  divideFRMap("MR", "MuMapPtCorr");
} 


//____________________________________________________________________________
void FakeRatio::registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nbins, bmin, bmax, axis);

} 


//____________________________________________________________________________
void FakeRatio::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);

}


//____________________________________________________________________________
void FakeRatio::defineOutput(){
  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 


  // bins
  float FR_bins_eta_el[4] = { 0.0, 1.0, 2.0, 2.5};
  float FR_bins_eta_mu[4] = { 0.0, 1.0, 2.0, 2.4};
  float FR_bins_pt[6]     = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};

  vector<float> bins_eta_el = Tools::toVector(FR_bins_eta_el);
  vector<float> bins_eta_mu = Tools::toVector(FR_bins_eta_mu);
  vector<float> bins_pt     = Tools::toVector(FR_bins_pt    );

  // leptons
  string MR_els[3]  = {"MR_DenEl", "MR_NumEl", "MR_RatEl"};
  string MR_leps[4] = {"MR_DenEl", "MR_NumEl", "MR_DenMu", "MR_NumMu"};
  string MR_mus[3]  = {"MR_DenMu", "MR_NumMu", "MR_RatMu"};

  vector<string> els  = Tools::toVector(MR_els);
  vector<string> leps = Tools::toVector(MR_leps);
  vector<string> mus  = Tools::toVector(MR_mus);


  // Setting Measurement Region
  setMeasurementRegion();

  // Measurement Region
  _hm->addVariable("MR_HT"         , 1000,   0.0, 1000.0, "H_T [GeV]"                            ); 
  _hm->addVariable("MR_MET"        , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  _hm->addVariable("MR_NumJets"    ,   20,   0.0,   20.0, "jet multiplicity"                     );
  _hm->addVariable("MR_NumBJets"   ,   20,   0.0,   20.0, "b-jet multiplicity"                   );
  _hm->addVariable("MR_NumDenEls"  ,   20,   0.0,   20.0, "denominator electron multiplicity"    );
  _hm->addVariable("MR_NumDenLeps" ,   20,   0.0,   20.0, "denominator lepton multiplicity"      );
  _hm->addVariable("MR_NumDenMus"  ,   20,   0.0,   20.0, "denominator muon multiplicity"        );
  _hm->addVariable("MR_NumNumEls"  ,   20,   0.0,   20.0, "numerator electron multiplicity"      );
  _hm->addVariable("MR_NumNumLeps" ,   20,   0.0,   20.0, "numerator lepton multiplicity"        );
  _hm->addVariable("MR_NumNumMus"  ,   20,   0.0,   20.0, "numerator muon multiplicity"          );
  _hm->addVariable("MR_NumVrtx"    ,   40,   0.0,   40.0, "vertex multiplicity"                  );
  _hm->addVariable("MR_JetCSVBTag" ,   50,   0.0,    1.0, "jet CSV B-Tag"                        );
  _hm->addVariable("MR_JetPt"      , 1000,   0.0, 1000.0, "P_T(jet) [GeV]"                       );

  registerLepPlots(leps, "DXY"    , 5000, 0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(leps, "DZ"     , 5000, 0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(leps, "SIP"    , 1000, 0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(leps, "Eta"    ,  240, 0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(leps, "RelIso" ,   50, 0.0,    1.0, "PF RelIso (lep)"                      );
  registerLepPlots(leps, "MiniIso",   50, 0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(leps, "MT"     , 1000, 0.0, 1000.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(leps, "Pt"     , 1000, 0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(leps, "PtJet"  , 1000, 0.0, 1000.0, "P_T(jet closest to lep) [GeV]"        );
  registerLepPlots(leps, "PtCorr" , 1000, 0.0, 1000.0, "cone corr. P_T(lep) [GeV]"            );
  registerLepPlots(leps, "PtRel"  , 1000, 0.0, 1000.0, "PtRel(lep)"                           );


  // electron maps

  // FO2 electrons
  // FO1 muons
 
  registerLepPlots(els, "MapPt"     , bins_pt.size()-1, bins_pt, bins_eta_el.size()-1, bins_eta_el, "P_T(e) [GeV]"               , "#||{#eta}(e)"); 
  registerLepPlots(els, "MapPtJet"  , bins_pt.size()-1, bins_pt, bins_eta_el.size()-1, bins_eta_el, "P_T(jet closest to e) [GeV]", "#||{#eta}(e)"); 
  registerLepPlots(els, "MapPtCorr" , bins_pt.size()-1, bins_pt, bins_eta_el.size()-1, bins_eta_el, "cone corr. P_T(e) [GeV]"    , "#||{#eta}(e)"); 

  registerLepPlots(mus, "MapPt"     , bins_pt.size()-1, bins_pt, bins_eta_mu.size()-1, bins_eta_mu, "P_T(#mu) [GeV]"               , "#||{#eta}(#mu)"); 
  registerLepPlots(mus, "MapPtJet"  , bins_pt.size()-1, bins_pt, bins_eta_mu.size()-1, bins_eta_mu, "P_T(jet closest to #mu) [GeV]", "#||{#eta}(#mu)"); 
  registerLepPlots(mus, "MapPtCorr" , bins_pt.size()-1, bins_pt, bins_eta_mu.size()-1, bins_eta_mu, "cone corr. P_T(#mu) [GeV]"    , "#||{#eta}(#mu)"); 

}



//____________________________________________________________________________
void FakeRatio::writeOutput(){
  /*
    writes all output of this class to the disk
    paramters: none
    return: none
  */

  divideFRMaps();

  //_hm->saveHistos ("FakeRatio", _cfgName);
  //_au->saveNumbers("FakeRatio", _cfgName);

}


//____________________________________________________________________________
void FakeRatio::modifySkimming(){
  // if adding variables in the skimming tree is needed...
}


/*****************************************************************************
******************************************************************************
** OBJECT SELECTIONS                                                        **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::collectKinematicObjects(){
  /*
    collects all kinematic objects needed in the code, i.e. applies all object selections
    parameters: none
    return: none
  */
  
  for(int i = 0; i < _vc->get("n" + _leps); ++i){

    bool den = false;
    bool num = false;

    // electrons
    if(std::abs(_vc->get(_leps + "_pdgId", i)) == 11){		  
      if(denominatorElectronSelection(i)) {
        _denEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.0005) );
        _denElsIdx .push_back(i);
        _denLeps   .push_back( _denEls[ _denEls.size()-1 ] );
        _denLepsIdx.push_back(i);
        den = true;
      }
      if(numeratorElectronSelection(i)) {
        _numEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.0005) );
        _numElsIdx .push_back(i);
        _numLeps   .push_back( _numEls[ _numEls.size()-1 ] );
        _numLepsIdx.push_back(i);
        num = true;
      }
      if(!den && !num) {
        if(vetoElectronSelection(i))  {
          _vetEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					     _vc->get(_leps + "_eta", i),
					     _vc->get(_leps + "_phi", i),
					     _vc->get(_leps + "_pdgId", i),
					     _vc->get(_leps + "_charge", i),
					     0.0005) );
          _vetLeps.push_back( _vetEls[ _vetEls.size()-1 ] );
        }
      }		
    }

    // muons
    else if(std::abs(_vc->get(_leps + "_pdgId", i)) == 13){
      if(denominatorMuonSelection(i)) {
        _denMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.105) );
        _denMusIdx .push_back(i);
        _denLeps   .push_back( _denMus[ _denMus.size()-1 ] );
        _denLepsIdx.push_back(i);
        den = true;
      }
      if(numeratorMuonSelection(i)) {
        _numMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.105) );
        _numMusIdx .push_back(i);
        _numLeps   .push_back( _numMus[ _numMus.size()-1 ] );
        _numLepsIdx.push_back(i);
        num = true;
      }
      if(!den && !num) {
        if(vetoMuonSelection(i))  {
          _vetMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					     _vc->get(_leps + "_eta", i),
					     _vc->get(_leps + "_phi", i),
					     _vc->get(_leps + "_pdgId", i),
					     _vc->get(_leps + "_charge", i),
					     0.105) );
          _vetLeps.push_back( _vetMus[ _vetMus.size()-1 ] );
        }
      }
    }
  }

  _nDenEls  = _denEls .size();
  _nDenLeps = _denLeps.size();
  _nDenMus  = _denMus .size();
  _nNumEls  = _numEls .size();
  _nNumLeps = _numLeps.size();
  _nNumMus  = _numMus .size();
 
  for(int i = 0; i < _vc->get("n" + _jets); ++i){
    if(goodJetSelection(i)) {
      _goodJets.push_back( Candidate::create(_vc->get(_jets + "_pt", i),
					                     _vc->get(_jets + "_eta", i),
					                     _vc->get(_jets + "_phi", i) ) );
      
    }
  }

  _nJets  = _goodJets.size();
  
  _HT  = _susyMod -> HT( &(_goodJets) );
  _met = Candidate::create(_vc->get(_mets + "_pt"), _vc->get(_mets + "_phi") );

}


//____________________________________________________________________________
bool FakeRatio::goodJetSelection(int jetIdx){
  /*
    does the selection of good jets, i.e. minimum selection of jets 
    parameters: jetIdx
    return: true (if the jet is good), false (else)
  */
  
  counter("GoodJets", kGoodJets);

  if(!makeCut<float>(         _vc->get(_jets + "_pt" , jetIdx) , 40.0, ">" , "pt selection"   , 0, kGoodJets)) return false;
  if(!makeCut<float>(std::abs(_vc->get(_jets + "_eta", jetIdx)),  2.4, "<" , "eta selection"  , 0, kGoodJets)) return false;
  if(!makeCut<float>(         _vc->get(_jets + "_id" , jetIdx) ,  1  , ">=", "pog pf loose id", 0, kGoodJets)) return false;
  
  // CH: away-jet requirement
  for(unsigned int il=0; il<_denLeps.size(); ++il){
    float dr = KineUtils::dR(_denLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _denLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(!makeCut<float>(dr, 1.0, ">", "dR selection", 0, kGoodJets) ) return false;
  }

  // CH: this is jet-lepton cleaning: removing the closest jet to the loose lepton if dR < 0.4
  float dr_cache = 999999.;
  for(unsigned int il=0; il<_denLeps.size(); ++il){
    float dr = KineUtils::dR(_denLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _denLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  for(unsigned int il=0; il<_vetLeps.size(); ++il){
    float dr = KineUtils::dR(_vetLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _vetLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.4, ">", "dR selection, jet-lepton cleaning", 0, kGoodJets) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::denominatorElectronSelection(int elIdx){

  counter("DenominatorElectrons", kDenEls);

  // CH: FO2 selection for electrons
  // extrapolation in ElMvaId and mini isolation

  if(!makeCut<float>(         _vc->get("LepGood_pt"         , elIdx) , 10.   , ">"  , "pt selection"      , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kDenEls)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"      , elIdx) , 4.0   , "<"  , "SIP 3D"            , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"         , elIdx)), 0.1   , "<"  , "dz selection"      , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"        , elIdx)), 0.05  , "<"  , "dxy selection"     , 0    , kDenEls)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection"  , 0    , kDenEls)) return false;

  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);

  if(!makeCut( conv                                              , "conversion rejection", "=", kDenEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSel(elIdx, SusyModule::kDenom), "isolation"           , "=", kDenEls)) return false; 
  if(!makeCut( _susyMod -> elMvaSel   (elIdx, SusyModule::kLoose), "electron mva"        , "=", kDenEls)) return false;    

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kDenEls) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::denominatorMuonSelection(int muIdx){

  counter("DenominatorMuons", kDenMus);
  
  //CH: FO1 for muons
  //extrapolation in isolation only

  if(!makeCut<float>(         _vc->get("LepGood_pt"          , muIdx) , 10.  , ">", "pt selection"  , 0, kDenMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "eta selection" , 0, kDenMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID", 0, kDenMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20" , 0, kDenMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"        , 0, kDenMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"  , 0, kDenMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection" , 0, kDenMus)) return false;

  if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kDenom), "isolation", "=", kDenMus)) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::numeratorElectronSelection(int elIdx){

  counter("NumeratorElectrons", kNumEls);

  if(!makeCut<float>(         _vc->get("LepGood_pt"         , elIdx) , 10.   , ">"  , "pt selection"      , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kNumEls)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"      , elIdx) , 4.0   , "<"  , "SIP 3D"            , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"         , elIdx)), 0.1   , "<"  , "dz selection"      , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"        , elIdx)), 0.05  , "<"  , "dxy selection"     , 0    , kNumEls)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection"  , 0    , kNumEls)) return false;

  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);

  if(!makeCut( conv                                              , "conversion rejection", "=", kNumEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSel(elIdx, SusyModule::kTight), "isolation"           , "=", kNumEls)) return false; 
  if(!makeCut( _susyMod -> elMvaSel   (elIdx, SusyModule::kTight), "electron mva"        , "=", kNumEls)) return false;    

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kNumEls) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::numeratorMuonSelection(int muIdx){

  counter("NumeratorMuons", kNumMus);

  if(!makeCut<float>(         _vc->get("LepGood_pt"          , muIdx) , 10.  , ">", "pt selection"  , 0, kNumMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "eta selection" , 0, kNumMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID", 0, kNumMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20" , 0, kNumMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"        , 0, kNumMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"  , 0, kNumMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection" , 0, kNumMus)) return false;

  if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kTight), "isolation", "=", kNumMus)) return false;
 
  return true;

}


//____________________________________________________________________________
bool FakeRatio::vetoElectronSelection(int elIdx){
  // selection of veto electrons

  counter("VetoElectrons", kVetEls);

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("n" + _leps); ++il){
    float dr = KineUtils::dR(_vc->get(_leps + "_eta", il), _vc->get(_leps + "_eta", elIdx),
			                 _vc->get(_leps + "_phi", il), _vc->get(_leps + "_phi", elIdx));
    if(std::abs(_vc->get(_leps + "_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kVetEls) ) return false;
  
  return true;

}


//____________________________________________________________________________
bool FakeRatio::vetoMuonSelection(int muIdx){
  // selection of veto muons

  counter("VetoMuons", kVetMus);
  
  return true;

}




/*****************************************************************************
******************************************************************************
** KINEMATIC REGION DEFINITIONS                                             **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::setCut(std::string var, float valCut, std::string cType, float upValCut) {
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
void FakeRatio::setMeasurementRegion() {
  /*
    sets the cuts of the measurement region (MR)
    parameters: none
    return: none
  */


  // CH: currently not used, keep it for later
  //if(_MR == "all") {
  //  setCut("NBJetsMR", 0, ">=");
  //} 
  //else if(_MR == "MR00") {
  //  setCut("NBJetsMR", 0, "=");
  //}
  //else if(_MR == "MR01") {
  //  setCut("NBJetsMR", 1, "=");
  //}
  //else if(_MR == "MR02") {
  //  setCut("NBJetsMR", 2, "=");
  //}
  //else if(_MR == "MR03") {
  //  setCut("NBJetsMR", 3, ">=");
  //}


}



/*****************************************************************************
******************************************************************************
** EVENT SELECTIONS                                                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FakeRatio::skimSelection(){

  if(!makeCut<int>( _nDenLeps, 1, ">=", "lepton multiplicity and flavor") ) return false;
  if(!makeCut<int>( _nJets   , 1, ">=", "jet multiplicity"              ) ) return false; 

  return true;

}


//____________________________________________________________________________
bool FakeRatio::mrSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015


  // lepton multiplicity
  if(!makeCut<int>( _nDenLeps    , 1   , "=" , "lepton multiplicity and flavor")) return false;

  //CH: RA5 guys select muon pt later on
  if     (_sampleName.find("Mu15") != std::string::npos && _denLeps[0] -> pt() < 15.) return false;
  else if(_sampleName.find("Mu5")  != std::string::npos && _denLeps[0] -> pt() > 15.) return false;
 
  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity"              )) return false; 

  // MET 
  if(!makeCut<float>( _met->pt() , 20.0, "<" , "MET selection"                 )) return false;

  // MT
  Candidate* MT = nullptr;
  MT = Candidate::create( _denLeps[0], _met);
  if(!makeCut<float>( MT->mass() , 20.0, "<" , "MT selection"                  )) return false;

  return true;

}




/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::fillEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  fill("MR_HT"        , _HT                 , _weight);
  fill("MR_MET"       , _met->pt()          , _weight);
  fill("MR_NumBJets"  , _vc->get(_bvar)     , _weight);
  fill("MR_NumDenEls" , _denEls .size()     , _weight);
  fill("MR_NumDenLeps", _denLeps.size()     , _weight);
  fill("MR_NumDenMus" , _denMus .size()     , _weight);
  fill("MR_NumJets"   , _nJets              , _weight);
  fill("MR_NumNumEls" , _numEls .size()     , _weight);
  fill("MR_NumNumLeps", _numLeps.size()     , _weight);
  fill("MR_NumNumMus" , _numMus .size()     , _weight);
  fill("MR_NumVrtx"   , _vc->get(_nvert)    , _weight);

}


//____________________________________________________________________________
void FakeRatio::fillFRMaps(string prepend, Candidate * lep, int lepIdx, int wp){

  fill(prepend + "MapPt"    , overflowPt(_vc->get(_leps + "_pt", lepIdx)) , std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
  fill(prepend + "MapPtJet" , overflowPt(_susyMod -> closestJetPt(lepIdx)), std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
  fill(prepend + "MapPtCorr", overflowPt(_susyMod -> conePt(lepIdx, wp))  , std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);

}


//____________________________________________________________________________
void FakeRatio::fillFakeRatioMaps(){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */

  for(int i = 0; i < _denEls.size(); ++i) { fillFRMaps("MR_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _denMus.size(); ++i) { fillFRMaps("MR_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(int i = 0; i < _numEls.size(); ++i) { fillFRMaps("MR_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight );
                                            fillFRMaps("MR_RatEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _numMus.size(); ++i) { fillFRMaps("MR_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium);
                                            fillFRMaps("MR_RatMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillLepPlots(string prepend, Candidate * lep, int lepIdx, int wp){
  /*
    fills the control plots for leptons PER LEPTON
  */  

  fill(prepend + "Pt"     ,          _vc->get(_leps + "_pt"        , lepIdx) , _weight);
  fill(prepend + "Eta"    , std::abs(_vc->get(_leps + "_eta"       , lepIdx)), _weight);
  fill(prepend + "DXY"    , std::abs(_vc->get(_leps + "_dxy"       , lepIdx)), _weight);
  fill(prepend + "DZ"     , std::abs(_vc->get(_leps + "_dz"        , lepIdx)), _weight);
  fill(prepend + "SIP"    ,          _vc->get(_leps + "_sip3d"     , lepIdx) , _weight);
  fill(prepend + "RelIso" ,          _vc->get(_leps + "_relIso03"  , lepIdx) , _weight);
  fill(prepend + "MiniIso",          _vc->get(_leps + "_miniRelIso", lepIdx) , _weight);
  fill(prepend + "PtRel"  ,          _vc->get(_leps + "_jetPtRel"  , lepIdx) , _weight);
  fill(prepend + "MT"     , Candidate::create( lep, _met) -> mass()          , _weight);
  fill(prepend + "PtJet"  , _susyMod -> closestJetPt(lepIdx)                 , _weight);
  fill(prepend + "PtCorr" , _susyMod -> conePt(lepIdx, wp)                   , _weight);

}


//____________________________________________________________________________
void FakeRatio::fillLeptonPlots(){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  for(int i = 0; i < _denEls.size(); ++i) { fillLepPlots("MR_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _denMus.size(); ++i) { fillLepPlots("MR_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(int i = 0; i < _numEls.size(); ++i) { fillLepPlots("MR_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _numMus.size(); ++i) { fillLepPlots("MR_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillJetPlots(){
  /*
    fills the control plots for jets
    parameters: none
    return: none
  */


  for(int i = 0; i < _nJets; ++i){
    fill("MR_JetPt"     , _goodJets[i]->pt(), _weight);
  }

}




//____________________________________________________________________________
float FakeRatio::overflowPt(float rawPt){

	if(rawPt >= 70.) return 60.;

	return rawPt;
}

