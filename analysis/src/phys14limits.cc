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


#include "analysis/src/phys14limits.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
phys14limits::phys14limits(std::string cfg){
  /* 
     constructs the phys14limits class 
     parameters: configuration_file
     return: none
  */
	
  startExecution(cfg);
  initialize();

}


//____________________________________________________________________________
phys14limits::~phys14limits(){
  /* 
     destructs the phys14limits class 
     parameters: none
     return: none
  */

}


//____________________________________________________________________________
void phys14limits::initialize(){
  /*
    initializes the phys14limits class
    parameters: none
    return: none
  */

  _vc->registerVar("run"                          );
  _vc->registerVar("lumi"                         );
  _vc->registerVar("evt"                          );
  _vc->registerVar("HLT_SingleMu"                 );
  _vc->registerVar("HLT_MuEG"                     );
  _vc->registerVar("HLT_TripleEl"                 );
  _vc->registerVar("HLT_DoubleEl"                 );
  _vc->registerVar("HLT_DoubleMu"                 );
  _vc->registerVar("nVert"                        );
  _vc->registerVar("nTrueInt"                     );
  _vc->registerVar("nTrueInt"                     );
  _vc->registerVar("nBJetPt40Medium"              );
  _vc->registerVar("puWeight"                     );
  _vc->registerVar("genWeight"                    );
  _vc->registerVar("nLepGood"                     );
  _vc->registerVar("LepGood_pt"                   );
  _vc->registerVar("LepGood_eta"                  );
  _vc->registerVar("LepGood_phi"                  );
  _vc->registerVar("LepGood_charge"               );
  _vc->registerVar("LepGood_tightCharge"          );
  _vc->registerVar("LepGood_pdgId"                );
  _vc->registerVar("LepGood_relIso03"             );
  _vc->registerVar("LepGood_relIso04"             );
  _vc->registerVar("LepGood_dxy"                  );
  _vc->registerVar("LepGood_dz"                   );
  _vc->registerVar("LepGood_sip3d"                );
  _vc->registerVar("LepGood_pfMuonId"             );
  _vc->registerVar("LepGood_tightId"              );
  _vc->registerVar("LepGood_looseIdSusy"          );
  _vc->registerVar("LepGood_convVeto"             );
  _vc->registerVar("LepGood_lostHits"             );
  _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1");
  _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1");
  _vc->registerVar("LepGood_eleCutId2012_full5x5" );
  //_vc->registerVar("LepGood_mvaSusyPHYS14"        , "AF");
  _vc->registerVar("LepGood_mvaSusy"              );
  _vc->registerVar("LepGood_mcMatchId"            );
  _vc->registerVar("LepGood_mcMatchAny"           );
  _vc->registerVar("met_pt"                       );
  _vc->registerVar("met_eta"                      );
  _vc->registerVar("met_phi"                      );
  _vc->registerVar("met_mass"                     );
  _vc->registerVar("nJet25"                       );
  _vc->registerVar("nJet40"                       );
  _vc->registerVar("nJet"                         );
  _vc->registerVar("Jet_id"                       );
  _vc->registerVar("Jet_pt"                       );
  _vc->registerVar("Jet_rawPt"                    );
  _vc->registerVar("Jet_eta"                      );
  _vc->registerVar("Jet_phi"                      );
  _vc->registerVar("Jet_mass"                     );
  _vc->registerVar("Jet_btagCSV"                  );

  _vc->registerVar("htJet40j"                     );
  _vc->registerVar("minMllAFAS"                   );
  _vc->registerVar("minMllAFOS"                   );
  _vc->registerVar("mZ1"                          );
  _vc->registerVar("nLepGood10"                   );

 
  //generator informations
  _vc->registerVar("nGenPart"                     );
  _vc->registerVar("GenPart_eta"                  );
  _vc->registerVar("GenPart_phi"                  );
  _vc->registerVar("GenPart_pdgId"                );
  
  //bjets
  _vc->registerVar("nBJetLoose25"                 );
  _vc->registerVar("nBJetMedium40"                );
  _vc->registerVar("nBJetMedium25"                );
  _vc->registerVar("nSoftBJetMedium25"            );

  //additional counter categories
  _au->addCategory( kElId         , "el Id"           );
  _au->addCategory( kSBElId       , "sideband el Id"  );
  _au->addCategory( kTVElId       , "tight veto El"   );
  _au->addCategory( kVElId        , "veto El"         );
  _au->addCategory( kMuId         , "muon Id"         );
  _au->addCategory( kMuId         , "sideband muon Id");
  _au->addCategory( kTVMuId       , "tight veto Mu"   );
  _au->addCategory( kVMuId        , "veto Mu"         );
  _au->addCategory( kJetId        , "jet Id"          );
  _au->addCategory( kBJetId       , "b-jet Id"        );
  _au->addCategory( kLMGVetoLepSel, "vetoLMGLepSel"   );
  _au->addCategory( kZVetoLepSel  , "vetoZLepSel"     );

  //extra input variables
  _lepflav = getCfgVarS("LEPFLAV");
  _PT      = getCfgVarS("PT"     );
  _SR      = getCfgVarS("SR"     );
  _usesb   = getCfgVarS("USESB"  );
  _fakes   = getCfgVarS("FAKES"  );
  
}


//____________________________________________________________________________
void phys14limits::modifyWeight() {
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
void phys14limits::run(){

  _els   .clear();
  _leps  .clear();
  _mus   .clear();
  _tVEls .clear();
  _tVLeps.clear();
  _tVMus .clear();
  _vEls  .clear();
  _vLeps .clear();
  _vMus  .clear();

  _elIdx   .clear();
  _lepIdx  .clear();
  _muIdx   .clear();
  _tVElIdx .clear();
  _tVLepIdx.clear();
  _tVMuIdx .clear();
  _vElIdx  .clear();
  _vLepIdx .clear();
  _vMuIdx  .clear();

  _jets  .clear();
  _bJets .clear();

  counter("denominator");

	
  // prepare event selection
  collectKinematicObjects();

  //bool is_ss_event = ssEventSelection();
  //if(!is_ss_event) return;
  //bool is_3l_event = vetoEventSelection("Electron", "Muon");

  //fillTestPlots();

  // basic event selection (triggers, 2 ss leptons, veto)
  //if(!skimSelection()) return;
  //if(!cernSelection()) return;
  if(!baseSelection()) return;

  //skim right after the basic selection
  //fillSkimTree();
  //return;
	
  // sr event selection
  if(!srSelection()) return;

  //// gen matching
  //if(!genSelection()) return;
  //  
  ////fillSkimTree();
  ////return;
  //// calling the modules
  //fillEventPlots("SR");
  //fillJetPlots("SR");
  //fillLeptonPlots("SR");

	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void phys14limits::defineOutput(){
  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 


  // this is now here but should be somewhere else!!!
  setSignalRegion();

  // Signal Region

  _hm->addVariable("test_HT"        , 1000,   0.0, 1000.0, "H_T [GeV]"            ); 
  _hm->addVariable("test_MLL"       , 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("test_vetoMll"   , 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("test_NBJets"    ,   20,   0.0,   20.0, "b-jet multiplicity"   );
  _hm->addVariable("test_NJets"     ,   20,   0.0,   20.0, "jet multiplicity"     );
  _hm->addVariable("test_NLeps"     ,   20,   0.0,   20.0, "lepton multiplicity"  );
  _hm->addVariable("test_nLepGood10"  ,   20,   0.0,   20.0, "lepton multiplicity"  );
  _hm->addVariable("test_mZ1"       , 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("test_minMllAFOS", 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("test_minMllAFAS", 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("test_nJet40"   ,   20,   0.0,   20.0, "jet multiplicity"   );
  _hm->addVariable("test_nBJetMedium25",   20,   0.0,   20.0, "b-jet multiplicity"     );


  _hm->addVariable("SR_LepCharge" ,   20, -10.0,   10.0, "lepton charge"        );
  _hm->addVariable("SR_HT"        , 1000,   0.0, 1000.0, "H_T [GeV]"            ); 
  _hm->addVariable("SR_MET"       , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"    );
  _hm->addVariable("SR_MLL"       , 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("SR_NBJets"    ,   20,   0.0,   20.0, "b-jet multiplicity"   );
  _hm->addVariable("SR_NElectrons",   20,   0.0,   20.0, "electron multiplicity");
  _hm->addVariable("SR_NJets"     ,   20,   0.0,   20.0, "jet multiplicity"     );
  _hm->addVariable("SR_NLeps"     ,   20,   0.0,   20.0, "lepton multiplicity"  );
  _hm->addVariable("SR_NMuons"    ,   20,   0.0,   20.0, "muon multiplicity"    );
  _hm->addVariable("SR_NVrtx"     ,   40,   0.0,   40.0, "vertex multiplicity"  );
  _hm->addVariable("SRHTBin_LepCharge" ,   20, -10.0,   10.0, "lepton charge"        );
  _hm->addVariable("SRHTBin_HT"        , 1000,   0.0, 1000.0, "H_T [GeV]"            ); 
  _hm->addVariable("SRHTBin_MET"       , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"    );
  _hm->addVariable("SRHTBin_MLL"       , 1000,   0.0, 1000.0, "m_{ll} [GeV]"         ); 
  _hm->addVariable("SRHTBin_NBJets"    ,   20,   0.0,   20.0, "b-jet multiplicity"   );
  _hm->addVariable("SRHTBin_NElectrons",   20,   0.0,   20.0, "electron multiplicity");
  _hm->addVariable("SRHTBin_NJets"     ,   20,   0.0,   20.0, "jet multiplicity"     );
  _hm->addVariable("SRHTBin_NLeps"     ,   20,   0.0,   20.0, "lepton multiplicity"  );
  _hm->addVariable("SRHTBin_NMuons"    ,   20,   0.0,   20.0, "muon multiplicity"    );
  _hm->addVariable("SRHTBin_NVrtx"     ,   40,   0.0,   40.0, "vertex multiplicity"  );
  _hm->addVariable("SR_ElDXY"     ,   50,   0.0,    0.5, "#||{dxy}(e) [cm]"     );
  _hm->addVariable("SR_ElEta"     ,  240,   0.0,    2.4, "#||{#eta(e)}"         );
  _hm->addVariable("SR_ElIso"     ,   50,   0.0,    1.0, "PF Iso (e)"           );
  _hm->addVariable("SR_ElMT"      , 1000,   0.0, 1000.0, "M_T(e) [GeV]"         );
  _hm->addVariable("SR_ElPt"      , 1000,   0.0, 1000.0, "P_T(e) [GeV]"         );
  _hm->addVariable("SR_MuDXY"     ,   50,   0.0,    0.5, "#||{dxy}(#mu) [cm]"   );
  _hm->addVariable("SR_MuEta"     ,  240,   0.0,    2.4, "#||{#eta(#mu)}"       );
  _hm->addVariable("SR_MuIso"     ,   50,   0.0,    1.0, "PF Iso (#mu)"         );
  _hm->addVariable("SR_MuMT"      , 1000,   0.0, 1000.0, "M_T(#mu) [GeV]"       );
  _hm->addVariable("SR_MuPt"      , 1000,   0.0, 1000.0, "P_T(#mu) [GeV]"       );
  _hm->addVariable("SR_JetCSVBTag",   50,   0.0,    1.0, "jet CSV B-Tag"        );
  _hm->addVariable("SR_JetPt"     , 1000,   0.0, 1000.0, "P_T(jet) [GeV]"       );
  _hm->addVariable("SR_LElSIP"    , 1000,   0.0,   10.0, "SIP(e)"               );
  _hm->addVariable("SR_LMuSIP"    , 1000,   0.0,   10.0, "SIP(#mu)"             );


  //fake background
  _hm->addVariable("FakeBkgrd",10,0,10,"nBjet");
  _hm->addVariable("FakeBkgrdUp",10,0,10,"nBjet");
  _hm->addVariable("FakeBkgrdDown",10,0,10,"nBjet");
  

}


//____________________________________________________________________________
void phys14limits::writeOutput(){

}


//____________________________________________________________________________
void phys14limits::modifySkimming(){
  // if adding variables in the skimming tree is needed...
}


/*****************************************************************************
******************************************************************************
** OBJECT SELECTIONS                                                        **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool phys14limits::bJetSelection(int jetIdx){
  /*
    does the selection of  b-jets
    parameters: jetIdx
    return: true (if the jet is a b-jet), false (else)
  */
	
  counter("BJetDenominator", kBJetId);

  if(!makeCut(goodJetSelection(jetIdx), "jet Id", "=", kBJetId) ) return false;
  if(!makeCut<float>(_vc->get("Jet_btagCSV", jetIdx), 0.679, ">=", "csv btag selection", 0, kBJetId) ) return false;

  return true;

}


//____________________________________________________________________________
void phys14limits::collectKinematicObjects(){
  /*
    collects all kinematic objects needed in the code, i.e. applies all object selections
    parameters: none
    return: none
  */
  
  for(int i = 0; i < _vc->get("nLepGood"); ++i){

    // electrons
    if(std::abs(_vc->get("LepGood_pdgId", i)) == 11){		  
      if(electronSelection(i)) {
        _els.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _elIdx.push_back(i);
        _leps.push_back( _els[ _els.size()-1 ] );
        _lepIdx.push_back(i);
      }
      if(sidebandElectronSelection(i)) {
        _sbEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _sbElIdx.push_back(i);
        _sbLeps.push_back( _sbEls[ _sbEls.size()-1 ] );
        _sbLepIdx.push_back(i);
      }
      if(tightVetoElectronSelection(i)) {
        _tVEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
                      _vc->get("LepGood_eta", i),
                      _vc->get("LepGood_phi", i),
                      _vc->get("LepGood_pdgId", i),
                      _vc->get("LepGood_charge", i),
                      0.0005) );
        _tVElIdx.push_back(i);
        _tVLeps.push_back( _tVEls[ _tVEls.size()-1 ] );
        _tVLepIdx.push_back(i);
      }
      else {
        if(vetoElectronSelection(i))  {
          _vEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					     _vc->get("LepGood_eta", i),
					     _vc->get("LepGood_phi", i),
					     _vc->get("LepGood_pdgId", i),
					     _vc->get("LepGood_charge", i),
					     0.0005) );
          _vElIdx.push_back(i);
          _vLeps.push_back( _vEls[ _vEls.size()-1 ] );
          _vLepIdx.push_back(i);
        }
      }		
    }

    // muons
    else if(std::abs(_vc->get("LepGood_pdgId", i)) == 13){
      if(muonSelection(i)) {
        _mus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _muIdx.push_back(i);
        _leps.push_back( _mus[ _mus.size()-1 ] );
        _lepIdx.push_back(i);
      }
      if(sidebandMuonSelection(i)) {
        _sbMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _sbMuIdx.push_back(i);
        _sbLeps.push_back( _sbMus[ _sbMus.size()-1 ] );
        _sbLepIdx.push_back(i);
      }
      if(tightVetoMuonSelection(i)) {
        _tVMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
                      _vc->get("LepGood_eta", i),
                      _vc->get("LepGood_phi", i),
                      _vc->get("LepGood_pdgId", i),
                      _vc->get("LepGood_charge", i),
                      0.105) );
        _tVMuIdx.push_back(i);
        _tVLeps.push_back( _tVMus[ _tVMus.size()-1 ] );
        _tVLepIdx.push_back(i);
      }
      else {
        if(vetoMuonSelection(i))  {
          _vMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					     _vc->get("LepGood_eta", i),
					     _vc->get("LepGood_phi", i),
					     _vc->get("LepGood_pdgId", i),
					     _vc->get("LepGood_charge", i),
					     0.105) );
          _vMuIdx.push_back(i);
          _vLeps.push_back( _vMus[ _vMus.size()-1 ] );
          _vLepIdx.push_back(i);
        }
      }
    }
  }
 
  _nEls    = _els   .size();
  _nLeps   = _leps  .size();
  _nMus    = _mus   .size();
  _nSBEls  = _sbEls .size();
  _nSBLeps = _sbLeps.size();
  _nSBMus  = _sbMus .size();
  _nTVEls  = _tVEls .size();
  _nTVLeps = _tVLeps.size();
  _nTVMus  = _tVMus .size();
  _nVEls   = _vEls  .size();
  _nVLeps  = _vLeps .size();
  _nVMus   = _vMus  .size();
  
  for(int i = 0; i < _vc->get("nJet40"); ++i){
    if(goodJetSelection(i)) {
      _jets.push_back( Candidate::create(_vc->get("Jet_pt", i),
					 _vc->get("Jet_eta", i),
					 _vc->get("Jet_phi", i) ) );
    }
  }

  _nJets  = _jets.size();

  _HT  = HT();
  _met = Candidate::create(_vc->get("met_pt"), _vc->get("met_phi") );

}


//____________________________________________________________________________
bool phys14limits::goodJetSelection(int jetIdx){
  /*
    does the selection of good jets, i.e. minimum selection of jets 
    parameters: jetIdx
    return: true (if the jet is good), false (else)
  */
  
  counter("JetDenominator", kJetId);

  if(!makeCut<float>(_vc->get("Jet_pt", jetIdx)       , 40.0, ">", "pt selection" , 0, kJetId) ) return false;
  //if(!makeCut<float>(fabs(_vc->get("Jet_eta", jetIdx)),  2.4, "<", "eta selection", 0, kJetId) ) return false;

  //// SF: here we require dR(j,every loose lepton) > 0.4
  //for(unsigned int il=0; il<_leps.size(); ++il){
  //  float dr = KineUtils::dR(_leps[il]->eta(), _vc->get("Jet_eta", jetIdx),
  //  		     _leps[il]->phi(), _vc->get("Jet_phi", jetIdx));
  //  if(!makeCut<float>(dr, 0.4, ">", "dR selection", 0, kJetId) ) return false;
  //}

  //for(unsigned int il=0; il<_vLeps.size(); ++il){
  //  float dr = KineUtils::dR(_vLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
  //  		     _vLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
  //  if(!makeCut<float>(dr, 0.4, ">", "dR selection", 0, kJetId) ) return false;
  //}

  return true;

}


//____________________________________________________________________________
bool phys14limits::electronSelection(int elIdx){
  /*
    does the selection of electrons
    parameters: elIdx
    return: true (if the electron is an electron), false (else)
  */


  counter("ElectronDenominator", kElId);
  
  if(!makeCut<float>( _vc->get("LepGood_pt"      , elIdx)          , 10.   , ">"  , "pt selection"      , 0    , kElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))     , 2.4   , "<"  , "eta selection"     , 0    , kElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))     , 1.4442, "[!]", "eta selection veto", 1.566, kElId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_sip3d"   , elIdx)          , 4     , "<"  , "SIP 3D"            , 0    , kElId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_relIso03", elIdx)          , 0.1   , "<"  , "Isolation "        , 0    , kElId)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz" , elIdx))      , 0.1   , "<"  , "dz selection"      , 0    , kElId)) return false;
  //if(!makeCut<int>( _vc->get("LepGood_tightId", elIdx), 1     , ">=" , "POG CB WP-M Id "   , 0    , kElId)) return false;
  if(!makeCut<int>( _vc->get("LepGood_eleCutId2012_full5x5", elIdx), 3     , ">=" , "POG CB WP-M Id "   , 0    , kElId)) return false;
  if(!makeCut<int>( _vc->get("LepGood_tightCharge", elIdx)         , 1     , ">"  , "charge selection"  , 0    , kElId)) return false;
  
  bool conv= (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kElId)) return false;

  //CH: nasty but simple: use (1) for SR, use (2+3) for SB  
  //if(!makeCut<float>( _vc->get("LepGood_relIso03", elIdx)          , 0.1   , "<"  , "Isolation "        , 0    , kElId)) return false;
  if(_vc->get("LepGood_mcMatchId", elIdx) == 0 && !makeCut<float>( _vc->get("LepGood_relIso03", elIdx), 0.1, "[]", "Isolation ", 0.5, kElId)) return false;
  else if(_vc->get("LepGood_mcMatchId", elIdx) != 0 && !makeCut<float>( _vc->get("LepGood_relIso03", elIdx), 0.1, "<", "Isolation ", 0, kElId)) return false;

  return true;

}


//____________________________________________________________________________
bool phys14limits::muonSelection(int muIdx){
  /*
    does the selection of muons
    parameters: muIdx
    return: true (if the muon is a muon), false (else)
  */

  counter("MuonDenominator", kMuId);
  
  if(!makeCut<float>( _vc->get("LepGood_pt"      , muIdx)    , 10., ">", "pt selection"   , 0, kMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_eta"     , muIdx)    , 2.4, "<", "eta selection"  , 0, kMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_sip3d"   , muIdx)    , 4  , "<", "SIP 3D"         , 0, kMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_relIso03", muIdx)    , 0.1, "<", "Isolation "     , 0, kMuId)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz", muIdx)) , 0.1, "<", "dz selection"  , 0, kMuId)) return false;
  //if(!makeCut<int>( _vc->get("LepGood_tightId"   , muIdx)    , 0  , ">", "POG CB WP-T Id", 0, kMuId)) return false;
  if(!makeCut<int>( _vc->get("LepGood_tightId"   , muIdx)    , 1  , ">=", "POG CB WP-T Id", 0, kMuId)) return false;
  
  //CH: nasty but simple: use (1) for SR, use (2+3) for SB  
  //if(!makeCut<float>( _vc->get("LepGood_relIso03", muIdx)          , 0.1   , "<"  , "Isolation "        , 0    , kMuId)) return false;
  if(_vc->get("LepGood_mcMatchId", muIdx) == 0 && !makeCut<float>( _vc->get("LepGood_relIso03", muIdx), 0.1, "[]", "Isolation ", 0.5, kMuId)) return false;
  else if(_vc->get("LepGood_mcMatchId", muIdx) != 0 && !makeCut<float>( _vc->get("LepGood_relIso03", muIdx), 0.1, "<", "Isolation ", 0, kMuId)) return false;
  return true;

}


//____________________________________________________________________________
bool phys14limits::sidebandElectronSelection(int elIdx){
  /*
    does the selection of electrons in the sideband
    parameters: elIdx
    return: true (if the electron is an electron), false (else)
  */


  counter("SidebandElectronDenominator", kSBElId);
  
  if(_fakes != "none" && !makeCut<int>(  _vc->get("LepGood_mcMatchId", elIdx) , 0, "=", "gen fake selection", 0, kSBElId)) return false;

  if(!makeCut<float>( _vc->get("LepGood_pt"      , elIdx)          , 10.   , ">"  , "pt selection"      , 0    , kSBElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))     , 2.4   , "<"  , "eta selection"     , 0    , kSBElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx))     , 1.4442, "[!]", "eta selection veto", 1.566, kSBElId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_sip3d"   , elIdx)          , 4     , "<"  , "SIP 3D"            , 0    , kSBElId)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz" , elIdx))      , 0.1   , "<"  , "dz selection"      , 0    , kSBElId)) return false;
  if(!makeCut<int>( _vc->get("LepGood_eleCutId2012_full5x5", elIdx), 3     , ">=" , "POG CB WP-M Id "   , 0    , kSBElId)) return false;
  if(!makeCut<int>( _vc->get("LepGood_tightCharge", elIdx)         , 1     , ">"  , "charge selection"  , 0    , kSBElId)) return false;
  
  bool conv= (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kSBElId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_relIso03", elIdx)    , 0.1, "[]", "Isolation "    , 0.5, kSBElId)) return false;

  return true;

}


//____________________________________________________________________________
bool phys14limits::sidebandMuonSelection(int muIdx){
  /*
    does the selection of muons in the sideband
    parameters: muIdx
    return: true (if the muon is a muon), false (else)
  */

  counter("MuonDenominator", kMuId);
  
  if(_fakes != "none" && !makeCut<int>(  _vc->get("LepGood_mcMatchId", muIdx) , 0, "!=", "gen not-fake selection", 0, kSBMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_pt"      , muIdx)    , 10., ">", "pt selection"   , 0, kSBMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_eta"     , muIdx)    , 2.4, "<", "eta selection"  , 0, kSBMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_sip3d"   , muIdx)    , 4  , "<", "SIP 3D"         , 0, kSBMuId)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz", muIdx)) , 0.1, "<", "dz selection"  , 0, kSBMuId)) return false;
  if(!makeCut<int>( _vc->get("LepGood_tightId"   , muIdx)    , 1  , ">=", "POG CB WP-T Id", 0, kSBMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_relIso03", muIdx)    , 0.1, "[]", "Isolation "    , 0.5, kSBMuId)) return false;
  
  return true;

}

//____________________________________________________________________________
bool phys14limits::tightVetoElectronSelection(int elIdx){
  /*
    does the selection of tight electrons for the mll veto
    parameters: elIdx
    return: true (if the electron is a tight electron), false (else)
  */

  counter("TightVetoElectronDenominator", kTVElId);

  if(!makeCut<float>( _vc->get("LepGood_pt"         , elIdx), 10. , ">" , "pt selection"    , 0, kTVElId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_sip3d"      , elIdx),  4  , "<" , "SIP 3D"          , 0, kTVElId)) return false;
  //if(!makeCut<float>( _vc->get("LepGood_relIso03"   , elIdx),  0.1, "<" , "isolation"       , 0, kTVElId)) return false;
  if(!makeCut<int>(   _vc->get("LepGood_tightId"    , elIdx),  2  , ">=", "POG CB WP-M Id"  , 0, kTVElId)) return false;
  if(!makeCut<int>(   _vc->get("LepGood_tightCharge", elIdx),  1  , ">" , "charge selection", 0, kTVElId)) return false;
  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kTVElId)) return false;
  
  return true;

}


//____________________________________________________________________________
bool phys14limits::tightVetoMuonSelection(int muIdx){
  /*
    does the selection of tight muons for the mll veto
    parameters: muIdx
    return: true (if the muon is a tight muon), false (else)
  */

  counter("TightVetoMuonDenominator", kTVMuId);
  
  if(!makeCut<float>( _vc->get("LepGood_pt"      , muIdx)    , 10., ">", "pt selection"  , 0, kTVMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_sip3d"   , muIdx)    , 4  , "<", "SIP 3D"        , 0, kTVMuId)) return false;
  //if(!makeCut<float>( _vc->get("LepGood_relIso03", muIdx)    , 0.1, "<", "isolation"     , 0, kTVMuId)) return false;
  if(!makeCut<int>(   _vc->get("LepGood_tightId" , muIdx)    , 0  , ">", "POG CB WP-T Id", 0, kTVMuId)) return false;
  
  return true;

}


//____________________________________________________________________________
bool phys14limits::vetoElectronSelection(int elIdx){
  /*
    does the selection of veto electrons
    parameters: elIdx
    return: true (if the electron is a veto electron), false (else)
  */

  counter("VetoElectronDenominator", kVElId);

  //if(!makeCut<float>( _vc->get("LepGood_pt", elIdx) , 10.0   , ">"  , "pt selection"    , 0    , kElVeto)) return false; 
  //if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), 2.4   , "<"  , "eta selection"   , 0    , kElVeto)) return false;
  //if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), 1.4442, "[!]", "eta selection veto" , 1.566, kElVeto)) return false;

  //bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  //if(!makeCut( conv, "conversion rejection", "=", kElVeto)) return false;

  
  return true;

}


//____________________________________________________________________________
bool phys14limits::vetoMuonSelection(int muIdx){
  /*
    does the selection of veto muons
    parameters: muIdx     
    return: true (if the muon is a veto muon), false (else)
  */

  counter("VetoMuonDenominator", kVMuId);

  //if(!makeCut<float>(  _vc->get("LepGood_pt"     , muIdx), 10.0, ">", "pt selection", 0, kMuVeto ) ) return false;
  //if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", muIdx)), 2.4   , "<"  , "eta selection"   , 0    , kMuVeto)) return false;
 
  //if(!makeCut<int>(   _vc->get("LepGood_pfMuonId", muIdx)     , 1   , "=", "POG Loose Id" , 0, kMuVeto) ) return false;
  //if(!makeCut<float>( _vc->get("LepGood_relIso03", muIdx)     , 0.2 , "<", "Isolation "   , 0, kMuVeto)) return false;
  //if(!makeCut<float>( std::abs(_vc->get("LepGood_dz" , muIdx)), 0.1 , "<", "dz selection" , 0, kMuVeto)) return false;
  //if(!makeCut<float>( std::abs(_vc->get("LepGood_dxy", muIdx)), 0.05, "<", "dxy selection", 0, kMuVeto)) return false;
  
  return true;

}






/*****************************************************************************
******************************************************************************
** KINEMATIC REGION DEFINITIONS                                             **
******************************************************************************
*****************************************************************************/



//____________________________________________________________________________
void phys14limits::setCut(std::string var, float valCut, std::string cType, float upValCut) {
  /*
    sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
    parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
    in case one cuts the variable in a range)
    return: none
  */


  // signal region
	
  if(var == "HTSR") {
    _valCutHTSR   = valCut;
    _cTypeHTSR    = cType;
    _upValCutHTSR = upValCut;
  }

  else if(var == "METSR") {
    _valCutMETSR   = valCut;
    _cTypeMETSR    = cType;
    _upValCutMETSR = upValCut;
  }

  else if(var == "HTCondSR") {
    _valCutHTCondSR   = valCut;
    _cTypeHTCondSR    = cType;
    _upValCutHTCondSR = upValCut;
  }
  
  else if(var == "METLowSR") {
    _valCutMETLowSR   = valCut;
    _cTypeMETLowSR    = cType;
    _upValCutMETLowSR = upValCut;
  }
  
  else if(var == "METHighSR") {
    _valCutMETHighSR   = valCut;
    _cTypeMETHighSR    = cType;
    _upValCutMETHighSR = upValCut;
  }

  else if(var == "NJetsSR") {
    _valCutNJetsSR   = valCut;
    _cTypeNJetsSR    = cType;
    _upValCutNJetsSR = upValCut;
  } 
	
  else if(var == "NBJetsSR") {
    _valCutNBJetsSR   = valCut;
    _cTypeNBJetsSR    = cType;
    _upValCutNBJetsSR = upValCut;
  } 
	

}



//____________________________________________________________________________
void phys14limits::setSignalRegion() {
  /*
    sets the cuts of the signal region (_SR)
    parameters: none
    return: none
  */

  _bvar = "nBJetMedium25";
  
  if(_SR == "SR00") {
    setCut("HTSR"     ,   80, ">" );
    setCut("METSR"    , -100, ">" );
    setCut("HTCondSR" ,  500, "<" );
    setCut("METHighSR",   30, ">" );
    setCut("METLowSR" , -100, ">" );
    setCut("NJetsSR"  ,    2, ">=");
    setCut("NBJetsSR" ,    0, "=");
  }
  
  else if(_SR == "SR10") {
    setCut("HTSR"     ,   80, ">" );
    setCut("METSR"    , -100, ">" );
    setCut("HTCondSR" ,  500, "<" );
    setCut("METHighSR",   30, ">" );
    setCut("METLowSR" , -100, ">" );
    setCut("NJetsSR"  ,    2, ">=");
    setCut("NBJetsSR" ,    1, "=" );
  }
  
  else if(_SR == "SR20") {
    setCut("HTSR"     ,   80, ">" );
    setCut("METSR"    , -100, ">" );
    setCut("HTCondSR" ,  500, "<" );
    setCut("METHighSR",   30, ">" );
    setCut("METLowSR" , -100, ">" );
    setCut("NJetsSR"  ,    2, ">=");
    setCut("NBJetsSR" ,    2, "=" );
  }
  else if(_SR == "SR30") {
    setCut("HTSR"     ,   80, ">" );
    setCut("METSR"    , -100, ">" );
    setCut("HTCondSR" ,  500, "<" );
    setCut("METHighSR",   30, ">" );
    setCut("METLowSR" , -100, ">" );
    setCut("NJetsSR"  ,    2, ">=");
    setCut("NBJetsSR" ,    3, ">=");
  }

  // CH: SUS-13-013 cuts
  else if(_SR == "SR01") {
    setCut("HTSR"     ,  200, "[]", 400);
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR02") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR03") {
    setCut("HTSR"     ,  200, "[]", 400 );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR04") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR05") {
    setCut("HTSR"     ,  200, "[]", 400);
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR06") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR07") {
    setCut("HTSR"     ,  200, "[]", 400 );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR08") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    0, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
 

  else if(_SR == "SR11") {
    setCut("HTSR"     ,  200, "[]", 400);
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR12") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR13") {
    setCut("HTSR"     ,  200, "[]", 400 );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR14") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR15") {
    setCut("HTSR"     ,  200, "[]", 400);
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR16") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR17") {
    setCut("HTSR"     ,  200, "[]", 400 );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR18") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    1, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
 

  else if(_SR == "SR21") {
    setCut("HTSR"     ,  200, "[]", 400);
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR22") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR23") {
    setCut("HTSR"     ,  200, "[]", 400 );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR24") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,   50, "[]", 120);
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR25") {
    setCut("HTSR"     ,  200, "[]", 400);
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR26") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    2, "[]",   3);
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR27") {
    setCut("HTSR"     ,  200, "[]", 400 );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }
  else if(_SR == "SR28") {
    setCut("HTSR"     ,  400, ">" );
    setCut("METSR"    ,  120, ">" );
    setCut("NJetsSR"  ,    4, ">=");
    setCut("NBJetsSR" ,    2, "=" );
    setCut("HTCondSR" ,    0, "<" );
    setCut("METHighSR", -100, ">" );
    setCut("METLowSR" , -100, ">" );
  }

 


}





/*****************************************************************************
******************************************************************************
** EVENT SELECTIONS                                                         **
******************************************************************************
*****************************************************************************/


bool phys14limits::cernSelection(){



  if(!makeCut( _vc->get("nLepGood10") >= 2, "new lepton multiplicity initial") ) return false;
  if(!makeCut( _vc->get("minMllAFAS") > 8, "new mll", "=") ) return false;
  if(!makeCut( _vc->get("minMllAFOS")<=0 || _vc->get("minMllAFOS")>12, "new veto part 2", "=") ) return false;
  if(!makeCut( _vc->get("mZ1")<76 || _vc->get("mZ1")>106, "new veto on 3 leptons"  , "=") ) return false;
  if(!makeCut<int>( _vc->get("nLepGood10"), 2, "=", "new lepton multiplicity") ) return false;

  if(!makeCut( std::abs(_vc->get("LepGood_pdgId", 0)) > 0 && 
               std::abs(_vc->get("LepGood_pdgId", 1)) > 0, "new sanity", "=")) return false;
  if(!makeCut( _vc->get("LepGood_charge",0)*_vc->get("LepGood_charge",1) > 0, "new same-sign", "=") ) return false;

  if(!makeCut( _vc->get("LepGood_pt", 0) > 25 && 
               _vc->get("LepGood_pt", 1) > 25, "new pt hh", "=") ) return false;
  if(!makeCut( std::max(_vc->get("LepGood_relIso03",0),
                        _vc->get("LepGood_relIso03",1)) < 0.1, "new iso", "=")) return false;
if(!makeCut( _vc ->get("LepGood_tightId",0) > (std::abs(_vc->get("LepGood_pdgId",0)) == 11) && 
              _vc->get("LepGood_tightId",1) > (std::abs(_vc->get("LepGood_pdgId",1)) == 11) , "Id") ) return false;
//  if(!makeCut( _vc->get("LepGood_tightId", 0) > (std::abs(_vc->get("LepGood_pdgId",0)) == 11) && 
//               _vc->get("LepGood_tightId", 1) > (std::abs(_vc->get("LepGood_pdgId",1)) == 11), "new tight id", "=") ) return false; 
  if(!makeCut( std::max(_vc->get("LepGood_sip3d",0),
                        _vc->get("LepGood_sip3d",1)) < 4, "new sip", "=")) return false;

  if(!makeCut((std::abs(_vc->get("LepGood_pdgId",0)) == 13 || 
    (_vc->get("LepGood_convVeto",0) && _vc->get("LepGood_lostHits",0) == 0 && _vc->get("LepGood_tightCharge",0) > 1)) && 
              (std::abs(_vc->get("LepGood_pdgId",1)) == 13 || 
    (_vc->get("LepGood_convVeto",1) && _vc->get("LepGood_lostHits",1) == 0 && _vc->get("LepGood_tightCharge",1) > 1)), 
    "new conversion rejection", "=") ) return false;

  if(!makeCut<float>( _vc->get("htJet40j"), 80, ">", "SR HT selection"              ) ) return false;
  if(!makeCut(_met->pt() > 30 || _vc->get("htJet40j") > 500, "SR HT-MET condition", "="  ) ) return false;
  if(!makeCut<int>(   _vc->get("nJet40"), 2, ">=", "SR jet-multiplicity"            ) ) return false;
  if(!makeCut<int>(   _vc->get("nBJetMedium25"), 0, "=", "SR b-jet-multiplicity"   ) ) return false;

  return true;
}


//____________________________________________________________________________
bool phys14limits::baseSelection(){
  /*
    implements the base selection that is fundamental for both the baseline 
    and the signal region selections
    parameters: none
    return: true (if event passes selection), false (else)
  */


  // triggers  
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleMu"), 1, "=", "HLT DoubleMu") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleEl"), 1, "=", "HLT DoubleEl") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_MuEG")    , 1, "=", "HLT MuEG"    ) ) return false;	

  // lepton multiplicity
  //int nleps = _nSBLeps;
  //if(_usesb == "SR") nleps = _nLeps;
  if(!makeCut<int>( _nLeps, 2, ">=", "lepton multiplicity and flavor" ) ) return false; 

  // veto on third lepton using all selected leptons
  if(!makeCut( mllVetoSelection(), "mll vetos", "=") ) return false;

  // selecting best same-sign pair 
  bool is_ss_event = ssEventSelection();
  if(!makeCut( is_ss_event , "same-sign selection", "=") ) return false;

  return true;

}


//____________________________________________________________________________
bool phys14limits::fromHadrTau(int lepIdx){
  /*
    looks if a lepton most-likely comes from a hadronic tau decay
    attention: this function assumes that every tau decays hadronically, make sure that it is so
  */

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
bool phys14limits::genSelection(){
  /*
	does the gen matching
  */

  int id1  = _vc->get("LepGood_mcMatchId" , _lep_idx1); 
  int id2  = _vc->get("LepGood_mcMatchId" , _lep_idx2); 
  int any1 = _vc->get("LepGood_mcMatchAny", _lep_idx1); 
  int any2 = _vc->get("LepGood_mcMatchAny", _lep_idx2); 

  if(_sampleName.find("fake") != (size_t) -1){
    if(id1 == 0 && id2 == 0) return false;
    if(id1 != 0 && id2 != 0) return false;
  }

  if(id1 == 0){
	if     (fromHadrTau(_lep_idx1)) counter("fakes from tau");
    else if(any1 == 5             ) counter("fakes from b");
    else if(any1 == 4             ) counter("fakes from c");
    else if(any1 <= 3             ) counter("fakes from light");
  }
  else if(id2 == 0){
	if     (fromHadrTau(_lep_idx2)) counter("fakes from tau");
    else if(any2 == 5             ) counter("fakes from b");
    else if(any2 == 4             ) counter("fakes from c");
    else if(any2 <= 3             ) counter("fakes from light");
  }

  return true;

}


//____________________________________________________________________________
bool phys14limits::skimSelection(){


  // lepton multiplicity
  if(!makeCut<int>( _nEls + _nMus, 2 , ">=", "lepton multiplicity and flavor" ) ) return false; 
  //if(!makeCut<float>( _HT        , 80, ">" , "SR HT selection"                ) ) return false;
  //if(!makeCut<int>( _nJets       , 2 , ">=", "SR jet multiplicity"            ) ) return false;

  return true;

}

//____________________________________________________________________________
bool phys14limits::srSelection(){


  if(!makeCut<float>( _HT       , _valCutHTSR    , _cTypeHTSR  , "SR HT selection" , _upValCutHTSR      ) ) return false;
  if(!makeCut<float>( _met->pt(), _valCutMETSR   , _cTypeMETSR , "SR MET selection", _upValCutMETSR      ) ) return false;

  if(_au->simpleCut( _HT, _valCutHTCondSR, _cTypeHTCondSR) ) {
    fillEventPlots("SRHTBin");
    if(!makeCut<float>( _met->pt(), _valCutMETHighSR, _cTypeMETHighSR, "SR MET (HT<500) selection", _upValCutMETHighSR ) ) return false;
  }
  else {
    if(!makeCut<float>( _met->pt(), _valCutMETLowSR , _cTypeMETLowSR , "SR MET (HT>500) selection" , _upValCutMETLowSR ) ) return false;
  }

  if(!makeCut<int>( _nJets         , _valCutNJetsSR , _cTypeNJetsSR , "SR jet multiplicity"  , _upValCutNJetsSR ) ) return false;
  if(!makeCut<int>(_vc->get(_bvar), _valCutNBJetsSR, _cTypeNBJetsSR, "SR b-jet multiplicity", _upValCutNBJetsSR) ) return false;

  //fillSkimTree(); 

  //if(!makeCut( mllVetoSelection(), "mll vetos", "=") ) return false;

  //cout << _vc->get("run") << ":" << _vc->get("lumi") << ":" << _vc->get("evt") << endl;



  return true;

} 



//____________________________________________________________________________
bool phys14limits::ssEventSelection(){
  /*
    checks, if the leptons that have been found in the kinematic region are same-sign
    parameters: none
    return: true (if the leptons all have same-sign), false (else)
  */

  CandList lc = _leps;
  //if(_usesb == "SR") lc = _leps;
  //else {
  //  lc = _leps;
  //  lc.reserve(lc.size() + distance(_sbLeps.begin(), _sbLeps.end()));
  //  lc.insert(lc.end(), _sbLeps.begin(), _sbLeps.end());
  //}

  // SF: CHOOSE a SS PAIR, maximizing the number of muons and then pT
  int charge = 0;
  int flavor = 0;
  int flavortmp = 0;
  bool isSS = false;
  for(unsigned int il1 = 0; il1 < lc.size(); ++il1){
    for(unsigned int il2 = il1+1; il2 < lc.size(); ++il2){
      charge    = lc[il1]->charge() * lc[il2]->charge();
      flavortmp = fabs(lc[il1]->pdgId())+fabs( lc[il2]->pdgId());
      if (charge < 0)         continue; // if the pair is OS skip
      if (flavor > flavortmp) continue; // if the new pair has less muons skip.
      
      if (_PT == "hh" && lc[il1]->pt()<25.) continue;
      if (_PT == "hh" && lc[il2]->pt()<25.) continue;
      
      if (_PT == "hl" && lc[il1]->pt()<25.) continue;
      if (_PT == "hl" && lc[il2]->pt()>25.) continue;

      if (_PT == "ll" && lc[il1]->pt()>25.) continue;
      if (_PT == "ll" && lc[il2]->pt()>25.) continue;
      
      flavor = flavortmp;
      _first  = lc[il1];   _lep_idx1 = il1;
      _second = lc[il2];   _lep_idx2 = il2; 
      isSS = true;
    }
  }


  // any other (also tight) lepton is pushed into the veto
  for(unsigned int il = 0; il < lc.size(); ++il){
    if(il != _lep_idx1 && il != _lep_idx2) 
      _vLeps.push_back(lc[il]);
  }

  
  if      (_lepflav=="mm"  && flavor==26 && isSS) return true;
  else if (_lepflav=="em"  && flavor==24 && isSS) return true;
  else if (_lepflav=="ee"  && flavor==22 && isSS) return true;
  else if (_lepflav=="all" && isSS)               return true;

  return false;
}


//____________________________________________________________________________
bool phys14limits::mllVetoSelection(){
  /*
	does the three mll vetos for all selected leptons
  */

//    if(_vc->get("run") == 1 && _vc->get("lumi") == 252987 && _vc->get("evt") == 25298612){
//DUMPVECTOR(_vLepIdx);
//DUMPVECTOR(_tVLepIdx);
//}

//  if(_vc->get("run") == 1 && _vc->get("lumi") == 252987 && _vc->get("evt") == 25298612)
//     cout << "here in case 0" << endl;

  for(unsigned int i = 0; i < _tVLeps.size(); ++i){
//    if(_vc->get("run") == 1 && _vc->get("lumi") == 252987 && _vc->get("evt") == 25298612)
//      cout << "looping on tV lepton " << i << " (" << _tVLeps[i]->pt() << "," << _tVLeps[i]->pdgId() << ", " << _tVLeps[i]->eta() << "," << _tVLeps[i]->phi() <<")" << endl;
    for(unsigned int j = i+1; j < _tVLeps.size(); ++j){
//      if(_vc->get("run") == 1 && _vc->get("lumi") == 252987 && _vc->get("evt") == 25298612)
//        cout << "adding tV lepton " << j << " (" << _tVLeps[j]->pt() << "," << _tVLeps[j]->pdgId() << ")" << endl;
//      if(mllLMGVeto(_tVLeps[i], _tVLeps[j])) return false;
      if(mllZVeto  (_tVLeps[i], _tVLeps[j])) return false;
    }
    for(unsigned int j = 0; j < _vLeps.size(); ++j){
//      if(_vc->get("run") == 1 && _vc->get("lumi") == 252987 && _vc->get("evt") == 25298612)
//        cout << "adding v lepton " << j << " (" << _vLeps[j]->pt() << "," << _vLeps[j]->pdgId() << ", " << _vLeps[j]->eta() << "," << _vLeps[j]->phi() << ")" << endl;
      if(mllLMGVeto(_tVLeps[i], _vLeps[j])) return false;
//      if(mllZVeto  (_tVLeps[i], _vLeps[j])) return false;
    }
  }
//  if(_vc->get("run") == 1 && _vc->get("lumi") == 252987 && _vc->get("evt") == 25298612)
//     cout << "here in case 0" << endl;

  return true;

}


//____________________________________________________________________________
bool phys14limits::mllLMGVeto(Candidate * cand, Candidate * veto){
  /*
	return true if the invariant mass of the two particles is not good and
	the event needs to be rejected
  */

 // counter("LowMassGammaVetoLepSel", kLMGVetoLepSel);

  // veto lepton pt
  if((std::abs(veto->pdgId()) == 11 && veto->pt() < 7) || (std::abs(veto->pdgId()) == 13 && veto->pt() < 5)) return false;

  float mll = 0;
  mll = Candidate::create(cand, veto) -> mass();

  // any sign -> low-mass veto
  if(mll <= 8.0) return true;
  //if(!makeCut<float>( mll , 8.0, ">", "MLL selection", kLMGVetoLepSel) ) return true;

  // opposite sign
  if(_au -> simpleCut(cand->charge(), veto->charge(), "=") ) return false;

  // opposite sign -> gamma star veto
  if(mll <= 12.0) return true;
  //if(!makeCut<float>( mll, 12.0, ">", "gamma star veto selection", kLMGVetoLepSel) ) return true;

  return false;

}


//____________________________________________________________________________
bool phys14limits::mllZVeto(Candidate * cand, Candidate * veto){
  /*
	return true if the invariant mass of the two particles is not good and
	the event needs to be rejected
  */

  // this stuff gives seg fault
  //counter("ZVetoLepSel", kZVetoLepSel);

  // veto lepton pt
  if(cand->pt() < 10 || veto->pt() < 10) return false;

  float mll = 0;
  mll = Candidate::create(cand, veto) -> mass();

  // opposite sign
  if(_au -> simpleCut(cand->charge(), veto->charge(), "=") ) return false;

  // same flavor -> Z veto
  if(_au -> simpleCut( std::abs(cand -> pdgId()), std::abs(veto -> pdgId()), "=") ) {
    if(mll >= 76.0 && mll <= 106.0) return true;
    //if(!makeCut(mll < 76.0 || mll > 106.0, "Z veto selection", "=", kZVetoLepSel) ) return true;
  }

  return false;

}



//____________________________________________________________________________
bool phys14limits::vetoEventSelection(){
  /*
    performs an essential part of the event selection in the 3l case, i.e.
    events are rejected if there are 3 leptons where two leptons form an
    opposite-sign same-flavor pair with some condition on mll and pt
    parameters: electron_label, muon_label (the labels of the selected electron and muon objects)
    return: true (if the event has such a pair, i.e. if the event shall be rejected), false (else)
  */

  counter("denominator", kVetoLepSel);

  for(unsigned int i = 0; i < _vLeps.size(); ++i){

    // search for OS pair with high-pt lepton
    if (_first->charge() == _vLeps[i] -> charge()) continue;

    float mll = 0;
    mll = Candidate::create(_vLeps[i], _first) -> mass();
    //fill("test_vetoMll"        , mll                  , _weight);

    // same flavor -> Z veto
    if(_au->simpleCut( fabs(_vLeps[i] -> pdgId()), fabs(_first -> pdgId()), "=") ) {
      if(makeCut(mll > 76.0 && mll < 106.0, "Z veto selection", "=", kVetoLepSel) ) return true;
    }

    // any flavor -> gamma star veto
    if(makeCut(mll < 12.0, "gamma star veto selection", "=", kVetoLepSel) ) return true;

    mll = Candidate::create(_vLeps[i], _second) -> mass(); 
    //fill("test_vetoMll"        , mll                  , _weight);
 
    // same flavor -> Z veto 
    if(_au->simpleCut( fabs(_vLeps[i] -> pdgId()), fabs(_second -> pdgId()), "=") ) {   
      if(makeCut(mll > 76.0 && mll < 106.0, "Z veto selection", "=", kVetoLepSel) ) return true; 
    } 
 
    // any flavor -> gamma star veto 
    if(makeCut(mll < 12.0, "gamma star veto selection", "=", kVetoLepSel) ) return true; 
 
  } 
 
  makeCut(true, "no veto event", "=", kVetoLepSel); 

  return false;

}





/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/


void phys14limits::fillTestPlots(){

  fill("test_HT"        , _HT                  , _weight);
  Candidate* Z = nullptr;
  Z = Candidate::create( _first, _second);
  fill("test_MLL"       , Z->mass()          , _weight);
  fill("test_NJets"     , _nJets              , _weight);
  fill("test_NBJets"    , _vc->get(_bvar)    , _weight);
  fill("test_NLeps"     , _nEls+_nMus         , _weight);
  fill("test_nLepGood10", _vc->get("nLepGood10"), _weight);
  fill("test_mZ1"       , _vc->get("mZ1"), _weight);
  fill("test_minMllAFOS", _vc->get("minMllAFOS"), _weight);
  fill("test_minMllAFAS", _vc->get("minMllAFAS"), _weight);
  fill("test_nJet40"   , _vc->get("nJet40"), _weight);
  fill("test_nBJetMedium25", _vc->get("nBJetMedium25"), _weight);

}


//____________________________________________________________________________
void phys14limits::fillEventPlots(std::string kr){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */
  
  Candidate* Z = nullptr;
  Z = Candidate::create( _first, _second);

  fill(kr + "_LepCharge" , eventCharge()       , _weight);
  fill(kr + "_HT"        , _HT                 , _weight);
  fill(kr + "_MET"       , _met->pt()          , _weight);
  fill(kr + "_MLL"       , Z->mass()           , _weight);
  fill(kr + "_NBJets"    , _vc->get(_bvar)    , _weight);
  fill(kr + "_NElectrons", _nEls               , _weight);
  fill(kr + "_NJets"     , _nJets              , _weight);
  fill(kr + "_NLeps"     , _nLeps              , _weight);
  fill(kr + "_NMuons"    , _nMus               , _weight);
  fill(kr + "_NVrtx"     , _vc->get("nVert")  , _weight);

}


//____________________________________________________________________________
void phys14limits::fillLeptonPlots(std::string kr){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  //CH: we only want to plot first and second lepton, not the veto ones
  CandList pLeps;
  pLeps.push_back(_first);
  pLeps.push_back(_second);

  vector<int> pIdx;
  pIdx.push_back(_lep_idx1);
  pIdx.push_back(_lep_idx2);

  for(int i = 0; i < pLeps.size(); ++i){
    string pp = "El";
    if(std::abs(pLeps[i] -> pdgId()) == 13) pp = "Mu";

    fill(kr + "_" + pp + "DXY", fabs(_vc->get("LepGood_dxy"     , pIdx[i])), _weight);
    fill(kr + "_" + pp + "Eta", fabs(_vc->get("LepGood_eta"     , pIdx[i])), _weight);
    fill(kr + "_" + pp + "Iso",      _vc->get("LepGood_relIso03", pIdx[i]) , _weight);
    fill(kr + "_" + pp + "Pt" ,      _vc->get("LepGood_pt"      , pIdx[i]) , _weight);
    fill(kr + "_" + pp + "MT" , Candidate::create( pLeps[i], _met) -> mass(), _weight);

    //CH: filling SIP for fakes in order to do the fitting of the composition
    if(_vc->get("LepGood_mcMatchId", pIdx[i]) == 0)
    fill(kr + "_L" + pp + "SIP",     _vc->get("LepGood_sip3d"   , pIdx[i]) , _weight);
  }

  //for(int i = 0; i < _nEls; ++i){
  //  fill(kr + "_ElDXY", fabs(_vc->get("LepGood_dxy"     , _elIdx[i])), _weight);
  //  fill(kr + "_ElEta", fabs(_vc->get("LepGood_eta"     , _elIdx[i])), _weight);
  //  fill(kr + "_ElIso",      _vc->get("LepGood_relIso03", _elIdx[i]) , _weight);
  //  fill(kr + "_ElPt" ,      _vc->get("LepGood_pt"      , _elIdx[i]) , _weight);
  //  fill(kr + "_ElMT" , Candidate::create( _els[i], _met) -> mass()   , _weight);
  //}

  //for(int i = 0; i < _nMus; ++i){
  //  fill(kr + "_MuDXY", fabs(_vc->get("LepGood_dxy"     , _muIdx[i])), _weight);
  //  fill(kr + "_MuEta", fabs(_vc->get("LepGood_eta"     , _muIdx[i])), _weight);
  //  fill(kr + "_MuIso",      _vc->get("LepGood_relIso03", _muIdx[i]) , _weight);
  //  fill(kr + "_MuPt" ,      _vc->get("LepGood_pt"      , _muIdx[i]) , _weight);
  //  fill(kr + "_MuMT" , Candidate::create( _mus[i], _met)->mass()     , _weight);
  //}

}


//____________________________________________________________________________
void phys14limits::fillJetPlots(std::string kr){
  /*
    fills the control plots for jets
    parameters: none
    return: none
  */


  for(int i = 0; i < _nJets; ++i){
    fill(kr + "_JetPt"     , _jets[i]->pt(), _weight);
    //    fill(kr + "_JetCSVBTag", _vc->get("Jet_btagCSV", i)                                       , _weight);
  }

}


//____________________________________________________________________________
int phys14limits::genMatchCateg(const Candidate* cand) {

  //loop over the number of generated leptons
  int nGenL = _vc->get("nGenPart");

  for(int ig = 0; ig < nGenL; ++ig) {
	
    if(Tools::dR(cand->eta(), _vc->get("GenPart_eta", ig),
		 cand->phi(), _vc->get("GenPart_phi", ig) ) < 0.05 ) { //to be tuned
		  
      // cout<<"matched lepton "<<cand.pdgId<<"  with "<<_vc->get("GenPart_pdgId",ig)<<" !!! "<<cand.pt<<"  "<<cand.eta<<"   "<<cand.phi<<"   "<<Tools::dR(cand.eta, _vc->get("GenPart_eta", ig),
      // cand.phi, _vc->get("GenPart_phi", ig) )<<endl;
		
      if( (abs(cand->pdgId()) != abs(_vc->get("GenPart_pdgId", ig)) ) && abs(_vc->get("GenPart_pdgId", ig)) != 13 ) return kMisMatchPdgId; //taus are exception to the rule
      else if(cand->pdgId()*_vc->get("GenPart_pdgId",ig) < 0 ) return kMisChargePdgId; //+*- = -...
      else return kGenMatched;
			
      break;
    } //dr matching
  } //gen loop
	
  return kNoGenMatch;
}

//____________________________________________________________________________
float 
phys14limits::HT(){
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
int 
phys14limits::eventCharge(){
  /*
    returns the total charge in the event as calculated from the electrons and
    leptons that have been selected
    parameters: electron_label, muon_label
    return: the total charge as int
  */

  int charge = 0;

  for(int i=0;i<_nEls;++i)
    charge += _els[i]->charge();

  for(int i=0;i<_nMus;++i)
    charge += _mus[i]->charge();

  return charge; 

}
