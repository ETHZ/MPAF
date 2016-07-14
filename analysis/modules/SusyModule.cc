#include "analysis/modules/SusyModule.hh"

SusyModule::SusyModule(VarClass* vc):
  _vc(vc),_dbm(nullptr)
{
  defineLeptonWPS();
  
}

SusyModule::SusyModule(VarClass* vc, DataBaseManager* dbm):
  _vc(vc), _dbm(dbm)
{
  defineLeptonWPS();
  loadDBs();
  loadBTagReader();
  loadBTagFastSimReader();
  initPUWeights();
}

SusyModule::~SusyModule() {

  delete _vc;
}

void
SusyModule::loadBTagFastSimReader() {

  // setup calibration readers
  string filename=(string) getenv("MPAF") + "/workdir/database/db2016/CSV_13TEV_T1tttt_1200_800_11_7_2016.csv";
  _calibFS=new BTagCalibration("csvFast", filename.c_str());
  _readerFS_b_cv=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
  _readerFS_b_up=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up"     );
  _readerFS_b_do=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down"   );
  _readerFS_c_cv=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
  _readerFS_c_up=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up"     );
  _readerFS_c_do=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down"   );
  _readerFS_l_cv=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
  _readerFS_l_up=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up"     );
  _readerFS_l_do=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down"   );
  _readerFS_b_cv->load(*_calibFS, BTagEntry::FLAV_B   , "fastsim");
  _readerFS_b_up->load(*_calibFS, BTagEntry::FLAV_B   , "fastsim");
  _readerFS_b_do->load(*_calibFS, BTagEntry::FLAV_B   , "fastsim");
  _readerFS_c_cv->load(*_calibFS, BTagEntry::FLAV_C   , "fastsim");
  _readerFS_c_up->load(*_calibFS, BTagEntry::FLAV_C   , "fastsim");
  _readerFS_c_do->load(*_calibFS, BTagEntry::FLAV_C   , "fastsim");
  _readerFS_l_cv->load(*_calibFS, BTagEntry::FLAV_UDSG, "fastsim");
  _readerFS_l_up->load(*_calibFS, BTagEntry::FLAV_UDSG, "fastsim");
  _readerFS_l_do->load(*_calibFS, BTagEntry::FLAV_UDSG, "fastsim");
}

void
SusyModule::loadBTagReader() {

  // setup calibration readers
  string filename=(string) getenv("MPAF") + "/workdir/database/db2016/CSVv2_4invfb.csv";
  _calib=new BTagCalibration("csvv2", filename.c_str());
  _reader_b_cv=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
  _reader_b_up=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up"     );
  _reader_b_do=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down"   );
  _reader_c_cv=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
  _reader_c_up=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up"     );
  _reader_c_do=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down"   );
  _reader_l_cv=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
  _reader_l_up=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up"     );
  _reader_l_do=new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down"   );
  _reader_b_cv->load(*_calib, BTagEntry::FLAV_B   , "mujets");
  _reader_b_up->load(*_calib, BTagEntry::FLAV_B   , "mujets");
  _reader_b_do->load(*_calib, BTagEntry::FLAV_B   , "mujets");
  _reader_c_cv->load(*_calib, BTagEntry::FLAV_C   , "mujets");
  _reader_c_up->load(*_calib, BTagEntry::FLAV_C   , "mujets");
  _reader_c_do->load(*_calib, BTagEntry::FLAV_C   , "mujets");
  _reader_l_cv->load(*_calib, BTagEntry::FLAV_UDSG, "comb"  );
  _reader_l_up->load(*_calib, BTagEntry::FLAV_UDSG, "comb"  );
  _reader_l_do->load(*_calib, BTagEntry::FLAV_UDSG, "comb"  );

}


void
SusyModule::loadDBs() {
 
  _dbm->loadDb("BTagEffUDSG","db2016/bTagEffs.root",(string)("eff_total_M_udsg") );
  _dbm->loadDb("BTagEffC","db2016/bTagEffs.root",(string)("eff_total_M_c") );
  _dbm->loadDb("BTagEffB","db2016/bTagEffs.root",(string)("eff_total_M_b") );

}

void
SusyModule::defineLeptonWPS() {

  _cLostHitWP.resize(kNWPs);
  _tChWP.resize(kNWPs);
  _sipWP.resize(kNWPs);
  _sipWPLepMVA.resize(kNWPs);
  _muIdWP.resize(kNWPs);
  _dxyWP.resize(kNWPs);
  _dzWP.resize(kNWPs);
  _elMvaIdWP.resize(3);
  _lepMVAIdWP.resize(12);
  _multiIsoWP.resize(3);
  _ptWP.resize(2);

  for(int i=0;i<3;++i) {
    _elMvaIdWP[i].resize(kNWPs);
    _multiIsoWP[i].resize(kNWPs);
    if(i!=2) _ptWP[i].resize(kNWPs);
  }
  
  //muId
  _muIdWP[kDenom] = 0; 
  _muIdWP[kLoose] = 0;//1000. 
  _muIdWP[kTight] = 1; 
  

  //conv rej ====================
  _cLostHitWP[kDenom] = 1; 
  _cLostHitWP[kLoose] = 1; 
  _cLostHitWP[kTight] = 0; 

  //pt ============================
  _ptWP[kEl][kDenom] = 7 ; _ptWP[kMu][kDenom] = 5 ;
  _ptWP[kEl][kLoose] = 7 ; _ptWP[kMu][kLoose] = 5 ;
  _ptWP[kEl][kTight] = 10; _ptWP[kMu][kTight] = 10;

  //sip & IP ======================
  _sipWP[kDenom] = 4.0; 
  _sipWP[kLoose] = 1000.0;//1000. 
  _sipWP[kTight] = 4.0; 
  
  _sipWPLepMVA[kDenom] = 8.0; 
  _sipWPLepMVA[kLoose] = 1000.0;//1000. 
  _sipWPLepMVA[kTight] = 8.0; 
  
  _dxyWP[kDenom] = 0.05; //cm
  _dxyWP[kLoose] = 0.05; //cm
  _dxyWP[kTight] = 0.05; //cm
  
  _dzWP[kDenom] = 0.1; //cm
  _dzWP[kLoose] = 0.1; //cm
  _dzWP[kTight] = 0.1; //cm

  //tight charge
  _tChWP[kLoose]=-1;
  _tChWP[kTight]=1;

  //el mva id ======================
  _elMvaIdWP[kEBC][kInSitu] = -0.363;
  _elMvaIdWP[kEBF][kInSitu] = -0.579;
  _elMvaIdWP[kEE ][kInSitu] = -0.623;

  _elMvaIdWP[kEBC][kInSituHT] = 0.051;
  _elMvaIdWP[kEBF][kInSituHT] = -0.261;
  _elMvaIdWP[kEE ][kInSituHT] = -0.403;

  _elMvaIdWP[kEBC][kLoose] = -0.70;
  _elMvaIdWP[kEBF][kLoose] = -0.83;
  _elMvaIdWP[kEE ][kLoose] = -0.92;

  _elMvaIdWP[kEBC][kLooseHT] = -0.155;
  _elMvaIdWP[kEBF][kLooseHT] = -0.56;
  _elMvaIdWP[kEE ][kLooseHT] = -0.76;

  _elMvaIdWP[kEBC][kTight] = 0.87;
  _elMvaIdWP[kEBF][kTight] = 0.60;
  _elMvaIdWP[kEE ][kTight] = 0.17;

  //multiIso =======================

  _multiIsoWP[kMiniIso][kDenom]      = 0.4 ; _multiIsoWP[kPtRatio][kDenom]      = 0   ; _multiIsoWP[kPtRel][kDenom]      = 0  ;
  _multiIsoWP[kMiniIso][kVLoose]     = 0.25; _multiIsoWP[kPtRatio][kVLoose]     = 0.67; _multiIsoWP[kPtRel][kVLoose]     = 6.0;
  _multiIsoWP[kMiniIso][kLoose]      = 0.20; _multiIsoWP[kPtRatio][kLoose]      = 0.69; _multiIsoWP[kPtRel][kLoose]      = 6.0;
  _multiIsoWP[kMiniIso][kMedium]     = 0.16; _multiIsoWP[kPtRatio][kMedium]     = 0.76; _multiIsoWP[kPtRel][kMedium]     = 7.2; 
  _multiIsoWP[kMiniIso][kTight]      = 0.12; _multiIsoWP[kPtRatio][kTight]      = 0.80; _multiIsoWP[kPtRel][kTight]      = 7.2;
  _multiIsoWP[kMiniIso][kVTight]     = 0.09; _multiIsoWP[kPtRatio][kVTight]     = 0.84; _multiIsoWP[kPtRel][kVTight]     = 7.2;

  _multiIsoWP[kMiniIso][kSpecFakeEl] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeEl] = 0.80; _multiIsoWP[kPtRel][kSpecFakeEl] = 7.2;
  _multiIsoWP[kMiniIso][kSpecFakeMu] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeMu] = 0.76; _multiIsoWP[kPtRel][kSpecFakeMu] = 7.2;

  //lepton MVA ID =======================
 
  _lepMVAIdWP[kVeryLooseMu]     = -0.90;
  _lepMVAIdWP[kLooseMu]         = -0.60;
  _lepMVAIdWP[kMediumMu]        = -0.20;
  _lepMVAIdWP[kTightMu]         = 0.15;
  _lepMVAIdWP[kVeryTightMu]     = 0.45;
  _lepMVAIdWP[kExtraTightMu]    = 0.65;

  _lepMVAIdWP[kVeryLooseEl]     = -0.30;
  _lepMVAIdWP[kLooseEl]         = 0.25;
  _lepMVAIdWP[kMediumEl]        = 0.50;
  _lepMVAIdWP[kTightEl]         = 0.65;
  _lepMVAIdWP[kVeryTightEl]     = 0.75;
  _lepMVAIdWP[kExtraTightEl]    = 0.85;

}

//=====================================================
// lepton selection

bool
SusyModule::multiIsoSel(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_miniRelIso"  , idx) < _multiIsoWP[kMiniIso][wp] &&
    (_vc->get(branch + "_jetPtRatiov2", idx) > _multiIsoWP[kPtRatio][wp] ||
     _vc->get(branch + "_jetPtRelv2"  , idx) > _multiIsoWP[kPtRel]  [wp] )) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelInSitu(int idx, int wp, string branch) const {

  // CH: wasn't my idea...
  if(_vc->get(branch + "_miniRelIso"  , idx) < _multiIsoWP[kMiniIso][wp] &&
     _vc->get(branch + "_jetPtRatiov2", idx) > _multiIsoWP[kPtRatio][wp]) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelCone(int idx, int wp, string branch) const {

  if( _vc->get(branch + "_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
      (conePt(idx, wp, branch)*_vc->get(branch + "_pt",idx) *_vc->get(branch + "_jetPtRatiov2", idx)>_multiIsoWP[kPtRatio][wp] ||
       _vc->get(branch + "_jetPtRelv2", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}

bool
SusyModule::invMultiIsoSel(int idx, int wp, string branch) const {
  
  if( _vc->get(branch + "_miniRelIso", idx)>_multiIsoWP[kMiniIso][wp]) return false;
  if( 1./_vc->get(branch + "_jetPtRelv2", idx) > (1/_multiIsoWP[kPtRel][wp] + _vc->get(branch + "_miniRelIso", idx)) ) return false;
  return true;
}

bool 
SusyModule::elMvaSel(int idx, int wp, string branch) const {

  int etaBin=-1;

  if     (std::abs(_vc->get(branch + "_eta", idx)) < 0.8  ) etaBin=0;
  else if(std::abs(_vc->get(branch + "_eta", idx)) < 1.479) etaBin=1;
  else if(std::abs(_vc->get(branch + "_eta", idx)) < 2.5  ) etaBin=2;

  if(_vc->get(branch + "_mvaIdSpring15", idx) <  _elMvaIdWP[etaBin][wp]  ) return false;
    
  return true;
}

bool
SusyModule::inSituFO(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_miniRelIso", idx) > 0.4) return false;
  if(1 / _vc->get(branch + "_jetPtRatiov2", idx) >= 1 / _multiIsoWP[kPtRatio][wp] + _vc->get(branch + "_miniRelIso", idx)) return false;
  //if(1 / _vc->get("LepGood_jetPtRatiov2", idx) >= 1 / _multiIsoWP[kPtRatio][wp] + _vc->get("LepGood_miniRelIso", idx) && _vc->get("LepGood_jetPtRelv2", idx) < _multiIsoWP[kPtRel][wp]) return false;

  return true;
}


bool
SusyModule::muIdSel(const Candidate* c, int idx, int wp, bool chCut, bool invSIP, bool LepMVA, string branch) const {

  int wpIso = kDenom;

  if(std::abs(c->eta())                                >  2.4          ) return false;
  if(     _vc->get(branch + "_mediumMuonID2016", idx)  <  _muIdWP[wp]  ) return false;
  if(chCut && _vc->get(branch + "_tightCharge" , idx)  <= _tChWP[wp]   ) return false;
  if(std::abs(_vc->get(branch + "_dxy"         , idx)) > _dxyWP[wp]    ) return false;
  if(std::abs(_vc->get(branch + "_dz"          , idx)) > _dzWP[wp]     ) return false;
  if(!multiIsoSel(idx, wpIso, branch)                                  ) return false;

  if(!LepMVA){
    if(invSIP){
      if(       _vc->get(branch + "_sip3d"       , idx)  < _sipWP[wp]    ) return false;
    }
    else {
      if(       _vc->get(branch + "_sip3d"       , idx)  > _sipWP[wp]    ) return false;
    }
  }
  else{
    if(invSIP){
      if(       _vc->get(branch + "_sip3d"       , idx)  < _sipWPLepMVA[wp]    ) return false;
    }
    else {
      if(       _vc->get(branch + "_sip3d"       , idx)  > _sipWPLepMVA[wp]    ) return false;
    }
  }

  return true;

}

bool
SusyModule::elIdSel(const Candidate* c, int idx, int wp, int mvaWp, bool chCut, bool invSIP, bool LepMVA, string branch) const {

  int wpIso=kDenom;

  if(std::abs(c->eta())                               > 2.5            ) return false; 
  if(         _vc->get(branch + "_convVeto"   , idx)  != 1             ) return false;
  if(         _vc->get(branch + "_lostHits"   , idx)  > _cLostHitWP[wp]) return false;

  if(chCut && _vc->get(branch + "_tightCharge", idx)  <= _tChWP[wp]    ) return false;
  if(std::abs(_vc->get(branch + "_dxy"        , idx)) > _dxyWP[wp]     ) return false;
  if(std::abs(_vc->get(branch + "_dz"         , idx)) > _dzWP[wp]      ) return false;
  if(!elMvaSel(idx, mvaWp, branch)                                     ) return false;
  if(!multiIsoSel(idx, wpIso, branch)                                  ) return false;

  if(!LepMVA){
    if(invSIP){
      if(       _vc->get(branch + "_sip3d"       , idx)  < _sipWP[wp]    ) return false;
    }
    else {
      if(       _vc->get(branch + "_sip3d"       , idx)  > _sipWP[wp]    ) return false;
    }
  }
  else{
    if(invSIP){
      if(       _vc->get(branch + "_sip3d"       , idx)  < _sipWPLepMVA[wp]    ) return false;
    }
    else {
      if(       _vc->get(branch + "_sip3d"       , idx)  > _sipWPLepMVA[wp]    ) return false;
    }
  }

  return true;

}

bool
SusyModule::elHLTEmulSel(int idx, bool withIso, string branch, bool v1) const {
  
  if(v1) {
    if(std::abs(_vc->get(branch + "_eta", idx)) < 1.479) {
      if(         _vc->get(branch + "_hadronicOverEm", idx)  > 0.08  ) return false;
      if(std::abs(_vc->get(branch + "_dEtaScTrkIn"   , idx)) > 0.01  ) return false;
      if(std::abs(_vc->get(branch + "_dPhiScTrkIn"   , idx)) > 0.04  ) return false;
      if(std::abs(_vc->get(branch + "_eInvMinusPInv" , idx)) > 0.01  ) return false;
      if(         _vc->get(branch + "_sigmaIEtaIEta" , idx)  > 0.011 ) return false;
    }
    else {
      if(         _vc->get(branch + "_hadronicOverEm", idx)  > 0.08  ) return false;
      if(std::abs(_vc->get(branch + "_dEtaScTrkIn"   , idx)) > 0.01  ) return false;
      if(std::abs(_vc->get(branch + "_dPhiScTrkIn"   , idx)) > 0.08  ) return false;
      if(std::abs(_vc->get(branch + "_eInvMinusPInv" , idx)) > 0.01  ) return false;
      if(         _vc->get(branch + "_sigmaIEtaIEta" , idx)  > 0.031 ) return false;
    }
    return true;
  }
  

    long int lumi = 1270;
    long int evt = 420400;
    bool debug = false;
  
    if(std::abs(_vc->get(branch + "_eta", idx)) < 1.479) {
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "entering emu sel (central)" << endl;}}
        if(         _vc->get(branch + "_hadronicOverEm", idx)  >= 0.10  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _hadronicOverEm" << endl;}}
        if(std::abs(_vc->get(branch + "_dEtaScTrkIn"   , idx)) >= 0.01  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _dEtaScTrkIn" << endl;}}
        if(std::abs(_vc->get(branch + "_dPhiScTrkIn"   , idx)) >= 0.04  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _dPhiScTrkIn" << endl;}}
        if(         _vc->get(branch + "_eInvMinusPInv" , idx)  <= -0.05  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _eInvMinusPInv" << endl;}}
        if(         _vc->get(branch + "_eInvMinusPInv" , idx)  >= 0.01  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _eInvMinusPInv" << endl;}}
        if(         _vc->get(branch + "_sigmaIEtaIEta" , idx)  >= 0.011 ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing trigger emulation" << endl;}}
    }
    else {
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "entering emu sel (central)" << endl;}}
        if(         _vc->get(branch + "_hadronicOverEm", idx)  >= 0.07  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _hadronicOverEm" << endl;}}
        if(std::abs(_vc->get(branch + "_dEtaScTrkIn"   , idx)) >= 0.008  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _dEtaScTrkIn" << endl;}}
        if(std::abs(_vc->get(branch + "_dPhiScTrkIn"   , idx)) >= 0.07  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _dPhiScTrkIn" << endl;}}
        if(         _vc->get(branch + "_eInvMinusPInv" , idx)  <= -0.05  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _eInvMinusPInv" << endl;}}
        if(         _vc->get(branch + "_eInvMinusPInv" , idx)  >= 0.005  ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing _eInvMinusPInv" << endl;}}
        if(         _vc->get(branch + "_sigmaIEtaIEta" , idx)  >= 0.03 ) return false;
                if(debug){if(_vc->get("evt") == evt && _vc->get("lumi") == lumi){cout << "passing trigger emulation" << endl;}}
    }
  
    if(!elMvaSel(idx, kLoose, branch)                                ) return false;
  
    if(withIso) {
        if(!elHLTEmulSelIso(idx, kLooseHT, branch)) return false;
    }

    return true;
}


bool
SusyModule::elHLTEmulSelIso(int idx, int mvaWP, string branch) const {

  if(_vc->get(branch + "_ecalPFClusterIso", idx) > 0.45 * _vc->get(branch + "_pt", idx) ) return false;
  if(_vc->get(branch + "_hcalPFClusterIso", idx) > 0.25 * _vc->get(branch + "_pt", idx) ) return false;
  if(_vc->get(branch + "_dr03TkSumPt"     , idx) > 0.2  * _vc->get(branch + "_pt", idx) ) return false;
  if(!elMvaSel(idx, mvaWP, branch)                                                      ) return false;

  return true;
}


bool
SusyModule::lepMVAIdSel(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_mvaSUSY", idx)  <  _lepMVAIdWP[wp]  ) return false;
  return true;

}

bool
SusyModule::invPtRelSel(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_jetPtRelv2", idx) < _multiIsoWP[kPtRel][wp]) return true;
  return false;

}




//===========================================================
bool
SusyModule::jetSel( int jetIdx) const {
  
  if(_vc->get("Jet_pt", jetIdx)<40.0) return false;
  return true;
}

float 
SusyModule::HT(const CandList* jets){
  float ht = 0;
  unsigned int nJets=jets->size();
  for(unsigned int i=0; i<nJets; ++i) 
    ht += jets->at(i)->pt();
  
  return ht;
}


//=============================================================
bool
SusyModule::mllVetoSelection(const Candidate* l1, const Candidate* l2,
			     const CandList* allLeps) const {
  
  for(unsigned int i = 0; i < allLeps->size(); ++i) {
    if(l1!=allLeps->at(i) && mllZVeto(l1, allLeps->at(i))) return false;
    if(l2!=allLeps->at(i) && mllZVeto(l2, allLeps->at(i))) return false;
    if(l1!=allLeps->at(i) && mllLMGVeto(l1, allLeps->at(i))) return false;
    if(l2!=allLeps->at(i) && mllLMGVeto(l2, allLeps->at(i))) return false;
  }
  
  return true;
}

bool 
SusyModule::mllLMGVeto(const Candidate* cand, const Candidate* veto) const {
  
  float mll = Candidate::create(cand, veto)->mass();

  if(mll <= 8.0) return true;
  if(cand->charge()==veto->charge() ) return false;
  if(mll <= 12.0) return true;

  return false;
}


bool 
SusyModule::mllZVeto(const Candidate* cand, const Candidate* veto) const {
 
  if(veto->pt() < 10) return false;
  float mll = Candidate::create(cand, veto)->mass();
  
  if(cand->charge()==veto->charge() ) return false;
  if(std::abs(cand->pdgId())==std::abs(veto->pdgId()) ) {
    if(mll >= 76.0 && mll <= 106.0) return true;
  }

  return false;
}


bool
SusyModule::passMllSingleVeto(const Candidate* c1, const Candidate* c2, 
			      float mllm, float mllM, bool ossf) {

  if( (c1->pdgId()== -c2->pdgId()) || !ossf) {
    float mll = Candidate::create(c1,c2)->mass();
    if(mll>mllm && mll<mllM) return false; 
  }
  return true;
}


bool
SusyModule::passMllMultiVeto(const Candidate* c1, const CandList* cands, 
			     float mllm, float mllM, bool ossf) {

  for(size_t il=0;il<cands->size();il++) {
    if( c1==cands->at(il) ) continue;
    if(!passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)) return false;
  }
  return true;
}

CandList
SusyModule::findZCand(const CandList* leps, float window, float MTcut) {
    
    float diff = 99999;
    size_t il1_save = -1;
    size_t il2_save = -1;
    CandList clist(2,nullptr);
    bool zFound = false;
    for(size_t il1=0;il1<leps->size()-1;il1++) {
        for(size_t il2=il1+1;il2<leps->size();il2++) {
            if(!(leps->at(il1)->pdgId() == -leps->at(il2)->pdgId())) continue;
            if(std::abs(91.-Candidate::create(leps->at(il1),leps->at(il2))->mass()) < window && std::abs(91.-Candidate::create(leps->at(il1),leps->at(il2))->mass()) < diff){
                Candidate* zCand = Candidate::create(leps->at(il1),leps->at(il2));
                diff = std::abs(91.-(zCand->mass()) );
                il1_save = il1;
                il2_save = il2;
                zFound = true;
            }
        }
    }
    if(zFound){ 
        for(size_t il=0;il<leps->size();il++) {
            if(il == il1_save || il == il2_save) continue;
            float mt = KineUtils::M_T(leps->at(il)->pt(), _vc->get("met_pt"), leps->at(il)->phi(), _vc->get("met_phi"));
            if(mt > MTcut){
                clist[0] = leps->at(il1_save);
                clist[1] = leps->at(il2_save);
            }
        }
    }
    return clist;
}


CandList
SusyModule::bestSSPair(const CandList* leps, bool byflav,
		       bool bypassMV, bool os, 
		       float pTthrMu, float pTthrEl,
		       int& idx1, int& idx2) {

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  float pTthr1,pTthr2;
  
  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      
      pTthr1 = (std::abs(leps->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr1 || leps->at(il2)->pt()<pTthr2) continue; 
      
      if(!passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false) && !bypassMV) continue;
      
      if( (leps->at(il1)->charge()!=leps->at(il2)->charge())!=os ) continue;
      
      int flav= (byflav?(std::abs(leps->at(il1)->pdgId()) + std::abs(leps->at(il2)->pdgId())):0);
      int st=leps->at(il1)->pt()+leps->at(il2)->pt();

      if(flav<tmpFlav) continue;
      
      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;
      
      tmpSt=st;
      clist[0]=leps->at(il1);
      clist[1]=leps->at(il2);
      idx1 = il1;
      idx2 = il2;
    
    }//il2
  }//il1

  return clist;
}

CandList
SusyModule::bestSSPair(const CandList* leps1, const CandList* leps2, bool byflav,
		       bool bypassMV, bool os, float pTthrMu, float pTthrEl,
		       int& idx1, int& idx2) {

  //LISTS HAVE TO BE COMPLEMENTARY, NO OVERLAPS!

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  float pTthr1,pTthr2;

  for(unsigned int il1=0;il1<leps1->size();il1++) {
    for(unsigned int il2=0;il2<leps2->size();il2++) {
      
      pTthr1 = (std::abs(leps1->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps2->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps1->at(il1)->pt()<pTthr1 || leps2->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(leps1->at(il1), leps2->at(il2), 0, 8, false) && !bypassMV) continue;

      if( (leps1->at(il1)->charge()!=leps2->at(il2)->charge())!=os ) continue;
      int flav= (byflav?(std::abs(leps1->at(il1)->pdgId()) + std::abs(leps2->at(il2)->pdgId())):0);
      int st=leps1->at(il1)->pt()+leps2->at(il2)->pt();

      if(flav<tmpFlav) continue;
      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;

      tmpSt=st;
      clist[0]=leps1->at(il1);
      clist[1]=leps2->at(il2);
      idx1 = il1;
      idx2 = il2;
    
    }//il2
  }//il1
  return clist;
}


CandList
SusyModule::bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		       bool bypassMV, bool os, float pTthrMu, float pTthrEl, 
		       int& idx1, int& idx2) {

  CandList clist(2,nullptr);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;
 
  float pTthr1,pTthr2;

  for(unsigned int il=0;il<leps->size();il++) {
      
    pTthr1 = (std::abs(c1->pdgId())==11)?pTthrEl:pTthrMu;
    pTthr2 = (std::abs(leps->at(il)->pdgId())==11)?pTthrEl:pTthrMu;

    //conditional pt threshold, could evolve in CERN code 
    if(c1->pt()<pTthr1 || leps->at(il)->pt()<pTthr2) continue; 

    if(!passMllSingleVeto(c1, leps->at(il), 0, 8, false) && !bypassMV) continue;

    if((c1->charge()!=leps->at(il)->charge())!=os) continue;

    int flav= (byflav?(std::abs(c1->pdgId()) + std::abs(leps->at(il)->pdgId())):0);
    int st=c1->pt()+leps->at(il)->pt();

    if(flav<tmpFlav) continue;

    if(flav>tmpFlav) tmpSt=0;
    tmpFlav=flav;
    if(st<tmpSt) continue;

    tmpSt=st;
    clist[0]=c1;
    clist[1]=leps->at(il);
    idx1 = 0;
    idx2 = il;
    
  }//il

  return clist;
}



vector<CandList>
SusyModule::buildSSPairs(const CandList* leps, vector<unsigned int> idxs,
			 bool byflav, bool bypassMV, bool os, 
			 float pTthrMu, float pTthrEl,
			 vector<int>& idx1, vector<int>& idx2) {

  vector<CandList> clist;
  float pTthr1,pTthr2;

  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      pTthr1 = (std::abs(leps->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      bool isMu=std::abs(_vc->get("LepGood_pdgId",idxs[il1]))==13;
      Candidate* c1=Candidate::create(_vc->get("LepGood_pt",idxs[il1]),
				      _vc->get("LepGood_eta",idxs[il1]),
				      _vc->get("LepGood_phi",idxs[il1]),
				      _vc->get("LepGood_pdgId",idxs[il1]),
				      _vc->get("LepGood_charge",idxs[il1]),
				      isMu?0.105:0.005 );

      isMu=std::abs(_vc->get("LepGood_pdgId",idxs[il2]))==13;
      Candidate* c2=Candidate::create(_vc->get("LepGood_pt",idxs[il2]),
				      _vc->get("LepGood_eta",idxs[il2]),
				      _vc->get("LepGood_phi",idxs[il2]),
				      _vc->get("LepGood_pdgId",idxs[il2]),
				      _vc->get("LepGood_charge",idxs[il2]),
				      isMu?0.105:0.005 );


      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr1 || leps->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(c1, c2, 0, 8, false) && !bypassMV) continue;
      if( (leps->at(il1)->charge()!=leps->at(il2)->charge())!=os ) continue;
    
      CandList tmp(2,NULL);
     
      tmp[0]=leps->at(il1);
      tmp[1]=leps->at(il2);

      clist.push_back(tmp);

      idx1.push_back(il1);
      idx2.push_back(il2);
      
    }//il2
  }//il1

  return clist;
}


vector<CandList>
SusyModule::buildSSPairs(const CandList* leps1, const CandList* leps2, 
			 vector<unsigned int> idxs1,
			 vector<unsigned int> idxs2,
			 bool byflav,
			 bool bypassMV, bool os, float pTthrMu, float pTthrEl,
			 vector<int>& idx1, vector<int>& idx2) {

  //LISTS HAVE TO BE COMPLEMENTARY, NO OVERLAPS!

  vector<CandList> clist;
  float pTthr1,pTthr2;

  vector<InternalCList> iCList;

  for(unsigned int il1=0;il1<leps1->size();il1++) {
    for(unsigned int il2=0;il2<leps2->size();il2++) {
      
      pTthr1 = (std::abs(leps1->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps2->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      bool isMu=std::abs(_vc->get("LepGood_pdgId",idxs1[il1]))==13;
      Candidate* c1=Candidate::create(_vc->get("LepGood_pt",idxs1[il1]),
				      _vc->get("LepGood_eta",idxs1[il1]),
				      _vc->get("LepGood_phi",idxs1[il1]),
				      _vc->get("LepGood_pdgId",idxs1[il1]),
				      _vc->get("LepGood_charge",idxs1[il1]),
				      isMu?0.105:0.005 );

      isMu=std::abs(_vc->get("LepGood_pdgId",idxs2[il2]))==13;
      Candidate* c2=Candidate::create(_vc->get("LepGood_pt",idxs2[il2]),
				      _vc->get("LepGood_eta",idxs2[il2]),
				      _vc->get("LepGood_phi",idxs2[il2]),
				      _vc->get("LepGood_pdgId",idxs2[il2]),
				      _vc->get("LepGood_charge",idxs2[il2]),
				      isMu?0.105:0.005 );

      //conditional pt threshold, could evolve in CERN code 
      if(leps1->at(il1)->pt()<pTthr1 || leps2->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(c1, c2, 0, 8, false) && !bypassMV) continue;
      if( (c1->charge()!=c2->charge())!=os ) continue;
      CandList tmp(2,NULL);
     
      tmp[0]=leps1->at(il1);
      tmp[1]=leps2->at(il2);

      InternalCList iclist;
      iclist.list = tmp;
      iclist.il1 = il1;
      iclist.il2 = il2;
      
      iCList.push_back(iclist);
    
    
    }//il2
  }//il1
  
  //ordering ================
  std::sort( iCList.begin(), iCList.end() );
  for(unsigned int il=0;il<iCList.size();++il) {
    clist.push_back(iCList[il].list);
    idx1.push_back(iCList[il].il1);
    idx2.push_back(iCList[il].il2);
  }
  //=========================
  

  return clist;
}


double
SusyModule::closestJetPt(int idx, string branch) const {

  return _vc->get(branch + "_pt", idx) / _vc->get(branch + "_jetPtRatiov2", idx);

}

const Candidate*
SusyModule::jetLepAware(const Candidate* lep) {
  
  float drTmp=1000;
  int idx=-1;
  string type="";
  Candidate* lepJet;
  vector<string> jetTypes({"Jet"});//,"DiscJet"});
  for(size_t it=0;it<jetTypes.size();it++) {
    string jType=jetTypes[it];
    
    for(int ij=0;ij<_vc->get("n"+jType);ij++) {
      Candidate* jet=Candidate::create(_vc->get(jType+"_rawPt", ij),
				       _vc->get(jType+"_eta", ij),
				       _vc->get(jType+"_phi", ij) );
     
      float dR=lep->dR( jet );
      if(dR<drTmp && jet->pt()>0.8*lep->pt()){
	drTmp=dR;
	lepJet=jet;
	idx=ij;
	type=jType;
      }
    }//loop jet
  }//jet types

  //=======================================
  TLorentzVector l=lep->p4();
  if(idx==-1) return lep;//no jet matched
  
  TLorentzVector j=lepJet->p4();
  if( (j-l).Rho()<0.0001) return lep; //only the lepton
  j = (j-l*(1/_vc->get(type+"_CorrFactor_L1")) )*_vc->get(type+"_CorrFactor_L1L2L3Res")+l;
  lepJet=Candidate::create(j.Pt(), j.Eta(), j.Phi() );
  return lepJet;

}

double
SusyModule::conePt(int idx, int isoWp, string branch) const {

  if(_vc->get(branch + "_jetPtRelv2", idx) > _multiIsoWP[kPtRel][isoWp] ) {
    return _vc->get(branch + "_pt", idx)*(1 + std::max((double) 0., _vc->get(branch + "_miniRelIso", idx) - _multiIsoWP[kMiniIso][isoWp] ) );
  }
  return std::max(_vc->get(branch + "_pt", idx), (double) closestJetPt(idx, branch) * _multiIsoWP[kPtRatio][isoWp] );
}

float
SusyModule::pTRatio(const Candidate* lep, const Candidate* jet) {
  return lep->pt()/jet->pt();
}


float
SusyModule::pTRel(const Candidate* lep, const Candidate* jet) {
  if( (jet->p4()-lep->p4()).Rho()<0.0001) return 0;
  return (jet->p4()-lep->p4()).Perp(lep->p4().Vect() );
}

double
SusyModule::Mt(Candidate* c1, Candidate* c2, int idx1, int idx2, string branch1, string branch2, int isoWp) const {

  return rawMt(c1, c2);
  //return coneMt(idx1, isoWp, c2);

}

double
SusyModule::rawMt(Candidate* c1, Candidate* c2) const {

  return coneMt(c1, c2, -1, -1);

}

double
SusyModule::coneMt(Candidate* c1, Candidate* c2, int idx1, int idx2, string branch1, string branch2, int isoWp) const {

  float pt1 = c1 -> pt();
  float pt2 = c2 -> pt();
  if(idx1 > -1) pt1 = conePt(idx1, isoWp, branch1);
  if(idx2 > -1) pt2 = conePt(idx2, isoWp, branch2);

  return sqrt(2 * pt1 * pt2 * (1. - cos(c1 -> phi() - c2 -> phi())));
  //return sqrt(2 * conePt(idx, isoWp) * met -> pt() * (1. - cos(Tools::AngleSubtraction(_vc->get("LepGood_phi", idx), met -> phi()))));

}


void 
SusyModule::awayJets(CandList* leptons, CandList& jets, vector<pair<string, unsigned int> >& jetIdxs, float dR) {

  for(unsigned int il = 0; il < leptons -> size(); ++il) {
    for(unsigned int ij = 0; ij < jets.size(); ++ij) {
      float dr = leptons->at(il)->dR( jets[ij] );
      if(dr < dR){
        jets   .erase(jets   .begin() + ij);
        jetIdxs.erase(jetIdxs.begin() + ij);
      }
    }
  }
}

void
SusyModule::cleanLeps(CandList& tightLeps, CandList* vetoLeps) {

  for(CandList::iterator it = tightLeps.begin(); it != tightLeps.end();) {
    int i = it - tightLeps.begin();
    if(!passMllMultiVeto( tightLeps[i], vetoLeps, 76, 106, true) ||
       !passMllMultiVeto( tightLeps[i], vetoLeps,  0,  12, true) ) 
      it = tightLeps.erase(it);
    else
      ++it;
  }
}


void
SusyModule::ptJets(CandList allJets, vector<pair<string, unsigned int> > allJetIdxs,
                   CandList& jets, vector<pair<string, unsigned int> >& jetIdxs, float thr){

  for(unsigned int i = 0; i < allJets.size(); ++i) {
    if(allJets[i] -> pt() > thr) {
      jets   .push_back(allJets   [i]);
      jetIdxs.push_back(allJetIdxs[i]);
    }
  }

}

void
SusyModule::cleanJets(CandList* leptons, 
		      CandList& cleanJets, vector<pair<string, unsigned int> >& jetIdxs,
		      CandList& cleanBJets, vector<pair<string, unsigned int> >& bJetIdxs,
		      CandList& lepJets, vector<pair<string, unsigned int> >& lepJetsIdxs,
		      float thr, float bthr,
		      bool isJESVar, int dir ) {

  cleanJets.clear();
  cleanBJets.clear();
  jetIdxs.clear();
  bJetIdxs.clear();

  lepJets.clear();
  lepJetsIdxs.clear();
  
  vector<string> jetTypes({"Jet","DiscJet"});
  CandList jets;
  vector<bool> bvals;
  vector<pair<string, unsigned int> > tmpIdxs;

  for(size_t it=0;it<jetTypes.size();it++) {
    string jType=jetTypes[it];
    
    string ext="";
    if(isJESVar) {
      ext=((SystUtils::kUp==dir)?"_jecUp":"_jecDown");
    }

    for(int ij=0;ij<_vc->get("n"+jType+ext);ij++) {
      if(_vc->get(jType+ext+"_id",ij)<1) continue;
      if(std::abs(_vc->get(jType+"_eta",ij))>2.4) continue; //introduced in RA7 sync round 3
      
      Candidate* jet=Candidate::create(_vc->get(jType+ext+"_pt", ij),
				       _vc->get(jType+ext+"_eta", ij),
				       _vc->get(jType+ext+"_phi", ij) );

      jets.push_back(jet);
      bvals.push_back( _vc->get(jType+ext+"_btagCSV",ij)<0.80 );//0.814
      tmpIdxs.push_back(make_pair(jType+ext, ij));
    }
  }

  map<Candidate*, std::pair<float,Candidate*> > cmap;
  map<Candidate*, std::pair<float,Candidate*> >::const_iterator it;

  for(unsigned int il=0;il<leptons->size();il++) {
    for(unsigned int ij=0;ij<jets.size();ij++) {
      float dR=leptons->at(il)->dR( jets[ij] );
      it = cmap.find(leptons->at(il));
      if(it==cmap.end() ) {
        cmap[ leptons->at(il) ] =std::make_pair(dR, jets[ij] );
      }
      else if(dR<it->second.first) {
        cmap[ leptons->at(il) ] =std::make_pair(dR, jets[ij] );
      }
    }
  }

  bool pass=true;
  for(unsigned int ij=0;ij<jets.size();ij++) {

    pass=true;
    for(unsigned int il=0;il<leptons->size();il++) {
      it = cmap.find(leptons->at(il));

      if(it->second.first > 0.4 ) continue;
      if(it->second.second == jets[ij] ) {pass=false; break;}
    }
    
    if(!pass) { 
      lepJetsIdxs.push_back(tmpIdxs[ij]);
      continue;
    }

    if(jets[ij]->pt()<bthr) continue;
    
    if(jets[ij]->pt()>thr) {
      cleanJets.push_back(jets[ij] );
      jetIdxs.push_back(tmpIdxs[ij]);
    }
    
    if(bvals[ij]) continue;
    
    cleanBJets.push_back(jets[ij]);
    bJetIdxs.push_back(tmpIdxs[ij]);
  } //loop jets



}

//LHE weights
double
SusyModule::getLHEweight(int LHEsysID){

  int tmp_nlhe=_vc->get("nLHEweight");
  for (int i=0; i<tmp_nlhe; i++) {
    int tmp_lhe_id = _vc->get("LHEweight_id", i);
    if (tmp_lhe_id == LHEsysID) {
      double tmp_lhe_wgt = _vc->get("LHEweight_wgt", i);
      return tmp_lhe_wgt;
    } 
  }
  return 1.0;

}


void
SusyModule::correctFlipRate(float& rate, float eta){
  rate *= 1.1918;
}


// Scale factors ====================================
void
SusyModule::applyHLTSF(const string& hltLine, float& weight){

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  weight *= _dbm->getDBValue("hltSF", hltLine);
}

void 
SusyModule::applyHLTSF(const string& hltLine, const CandList& cands, float& weight) {

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  if(hltLine=="HLT_DoubleEG") {
    weight *= _dbm->getDBValue("hltDEG", std::abs(cands[0]->eta()), cands[0]->pt(), cands[1]->eta(), cands[1]->pt() );
  }
  else if(hltLine=="HLT_DoubleMu") {
    weight *= _dbm->getDBValue("hltDMu", std::abs(cands[0]->eta()), cands[0]->pt(), cands[1]->eta(), cands[1]->pt() );
  }
  else if(hltLine=="HLT_SingleEle") {
    weight *= _dbm->getDBValue("hltSEle", std::abs(cands[0]->eta()), cands[0]->pt() );
  }
  else if(hltLine=="HLT_SingleMu") {
    weight *= _dbm->getDBValue("hltSMu", std::abs(cands[0]->eta()), cands[0]->pt() );
  }


}

void 
SusyModule::applyLepSF(const CandList& cands, float& weight) {

  for(unsigned int ic=0;ic<cands.size();ic++) {
    applySingleLepSF(cands[ic], weight);
  }

}


void 
SusyModule::applySingleLepSF(const Candidate* cand, float& weight) {

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  switch(std::abs(cand->pdgId())) {
  case 11: {weight *= _dbm->getDBValue("eleSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  case 13: {weight *= _dbm->getDBValue("muSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  case 15: {weight *= _dbm->getDBValue("tauSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  }

}

float
SusyModule::getFastSimLepSF(Candidate* lep1, Candidate* lep2, int nVert){

  string db1 = "FastSimElSF"; 
  string db2 = "FastSimElSF";
  
  float max1 = 2.49;
  float max2 = 2.49;
  
  if(std::abs(lep1 -> pdgId()) == 13) { db1 = "FastSimMuSF"; max1 = 2.39; }
  if(std::abs(lep1 -> pdgId()) == 13) { db2 = "FastSimMuSF"; max2 = 2.39; }
  
  return _dbm -> getDBValue(db1, std::min(lep1->pt(), (float) 199.9), std::min(std::abs(lep1->eta()), max1), std::min(nVert, 39))
       * _dbm -> getDBValue(db1, std::min(lep2->pt(), (float) 199.9), std::min(std::abs(lep2->eta()), max2), std::min(nVert, 39));
       
}

float
SusyModule::applyLepSfRA7(const CandList& cands){

    if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}
    float sf = 1.;
    float maxPt = 119.9;
    float maxEta = 2.39;
    const Candidate* cand;
    for(size_t il=0; il<cands.size();il++){
        cand = cands[il];
        int flavor = cand->pdgId();
        if(std::abs(flavor)==11){
            sf *= _dbm->getDBValue("FullSimElIDandIP", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta));
            sf *= _dbm->getDBValue("FullSimElISO", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta));
        }
        else if(std::abs(flavor) == 13){
            sf *= _dbm->getDBValue("FullSimMuID", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta));
            sf *= _dbm->getDBValue("FullSimMuIP2D", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta));
            sf *= _dbm->getDBValue("FullSimMuIP3D", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta));
            sf *= _dbm->getDBValue("FullSimMuISO", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta));
        }
        
        if(sf==0){cout << "Warning! lepton scale factor is 0, check pt and eta for db lookup" << endl;
            cout << "flavor: " << cand->pdgId() << endl;
            cout << "pt: " << cand->pt() << endl;
            cout << "eta: " << cand->eta() << endl;
            cout << "SF: " << sf << endl;}
    }
    return sf;

}

float 
SusyModule::applyFastSimLepSfRA7(const CandList& cands, int pileup){

    if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}
    float sf = 1.;
    float maxPt = 119.9;
    float maxEta = 2.39;
    int maxPU = 39;
    const Candidate* cand;
    for(size_t il=0; il<cands.size();il++){
        cand = cands[il];
        int flavor = cand->pdgId();
        if(std::abs(flavor)==11){
            sf *= _dbm->getDBValue("FastSimElIDandIP", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta), std::min(pileup, maxPU));
            sf *= _dbm->getDBValue("FastSimElISO", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta), std::min(pileup, maxPU));
        }
        else if(std::abs(flavor) == 13){
            sf *= _dbm->getDBValue("FastSimMuID", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta), std::min(pileup, maxPU));
            sf *= _dbm->getDBValue("FastSimMuIP2D", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta), std::min(pileup, maxPU));
            sf *= _dbm->getDBValue("FastSimMuIP3D", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta), std::min(pileup, maxPU));
            sf *= _dbm->getDBValue("FastSimMuISO", std::min(cand->pt(), maxPt), std::min((std::abs(cand->eta())),maxEta), std::min(pileup, maxPU));
        }
        if(sf==0){cout << "Warning! fastSim lepton scale factor is 0, check pt, eta and pile-up for db lookup" << endl;
            cout << "flavor: " << cand->pdgId() << endl;
            cout << "pt: " << cand->pt() << endl;
            cout << "eta: " << cand->eta() << endl;
            cout << "pileup: " << pileup << endl;
            cout << "SF: " << sf << endl;}
    }
    return sf;

}

float
SusyModule::bTagSF(CandList& jets , 
		   vector<pair<string, unsigned int> >& jetIdx,
                   CandList& bJets, 
		   vector<pair<string, unsigned int> >& bJetIdx, int st, 
		   bool fastSim, int fsst){
  // put st = -1 / 0 / +1 for down / central / up
  // put fsst = -1 / 0 / +1 for down / central / up for fast-fullSim CF

  //long int _evt = 326295;
  //long int _lumi = 986;

  float pdata = 1.0;
  float pmc   = 1.0;

  for(unsigned int i=0;i<jets.size(); ++i) {
    bool find=false;
    unsigned int  flavor = 2;
    if(std::abs(_vc->get( (string)(jetIdx[i].first+"_mcFlavour") , jetIdx[i].second)) == 5) flavor = 0; // b jet
    else if(std::abs(_vc->get( (string)(jetIdx[i].first+"_mcFlavour") , jetIdx[i].second)) == 4) flavor = 1; // c jet
    
    for(unsigned int iv=0;iv<bJets.size();iv++) {
      if(jetIdx[i].first==bJetIdx[iv].first && jetIdx[i].second==bJetIdx[iv].second) { find=true; break;}
    }

    /*if(_vc->get("evt") == _evt && _vc->get("lumi")== _lumi){
        cout << "jet pt : " << _vc->get("Jet_pt", i) << endl;
        cout << "jet MC flavor : " << _vc->get("Jet_mcFlavour", i) << endl;
        cout << "flavor: " << flavor << endl;
        cout << "find: " << find << endl;
    }*/



    float fsSF=1.;
    if(fastSim) fsSF=bTagMediumScaleFactorFastSim(jets[i], flavor, fsst);
    // cout<<fsSF<<endl;
      //fsSF=1;

    if(find){
      pdata*=bTagMediumEfficiency(jets[i], flavor) * 
	bTagMediumScaleFactor(jets[i], flavor, st)*fsSF;
      pmc*=bTagMediumEfficiency(jets[i], flavor)*fsSF;
     /*if(_vc->get("evt") == _evt && _vc->get("lumi")== _lumi){
        cout << "if find" << endl;
        cout << "eff: " << bTagMediumEfficiency(jets[i], flavor) << endl;
        cout << "SF: " << bTagMediumScaleFactor(jets[i], flavor, st) << endl;
    }*/

   
    
    }
    else {
      pdata*=(1-bTagMediumEfficiency(jets[i], flavor) * 
	      bTagMediumScaleFactor(jets[i], flavor, st)*fsSF);
      pmc*=(1-bTagMediumEfficiency(jets[i], flavor)*fsSF);
       /*if(_vc->get("evt") == _evt && _vc->get("lumi")== _lumi){
        cout << "if !find" << endl;
        cout << "eff: " << bTagMediumEfficiency(jets[i], flavor) << endl;
        cout << "SF: " << bTagMediumScaleFactor(jets[i], flavor, st) << endl;
    }*/


  
    }
  }

  //cout<<"pd " <<pdata<<"  "<<pmc<<endl;
  if(pmc != 0) return pdata/pmc;
  return 1.0;

}

float
SusyModule::bTagMediumEfficiency(Candidate* jet, unsigned int flavor){
  
  // b jet
  if(flavor == 0){
    return _dbm->getDBValue("BTagEffB", bTagPt(jet->pt()), std::abs(jet->eta()));
  }

  // c jet
  else if(flavor == 1){
    return _dbm->getDBValue("BTagEffC", bTagPt(jet->pt()), std::abs(jet->eta()));
  }

  // light
  else {
    return _dbm->getDBValue("BTagEffUDSG", bTagPt(jet->pt()), std::abs(jet->eta()));
  }
  
} 

float
SusyModule::bTagMediumScaleFactor(Candidate* jet, unsigned int flavor, int st){

  BTagCalibrationReader* reader = nullptr;
  BTagEntry::JetFlavor fl = BTagEntry::FLAV_UDSG;

  // mujets for b jets
  if(flavor == 0){
    fl = BTagEntry::FLAV_B;
    if     (st == 0) reader = _reader_b_cv;
    else if(st == 1) reader = _reader_b_up;
    else             reader = _reader_b_do;
  }
  // mujets for c jets
  else if(flavor == 1){
    fl = BTagEntry::FLAV_C;
    if     (st == 0) reader = _reader_c_cv;
    else if(st == 1) reader = _reader_c_up;
    else             reader = _reader_c_do;
  }
  // comb for light jets
  else {
    if     (st == 0) reader = _reader_l_cv;
    else if(st == 1) reader = _reader_l_up;
    else             reader = _reader_l_do;
  }
 
  
  float sf = reader->eval(fl, jet -> eta(), std::max((float)30.,std::min((float)669.,jet->pt())));
  return sf;

} 

float
SusyModule::bTagMediumScaleFactorFastSim(Candidate* jet, unsigned int flavor, int st) {

  BTagCalibrationReader* reader = nullptr;
  BTagEntry::JetFlavor fl = BTagEntry::FLAV_UDSG;
  
  // mujets for b jets
  if(flavor == 0){
    fl = BTagEntry::FLAV_B;
    if     (st == 0) reader = _readerFS_b_cv;
    else if(st == 1) reader = _readerFS_b_up;
    else             reader = _readerFS_b_do;
  }
  // mujets for c jets
  else if(flavor == 1){
    fl = BTagEntry::FLAV_C;
    if     (st == 0) reader = _readerFS_c_cv;
    else if(st == 1) reader = _readerFS_c_up;
    else             reader = _readerFS_c_do;
  }
  // comb for light jets
  else {
    if     (st == 0) reader = _readerFS_l_cv;
    else if(st == 1) reader = _readerFS_l_up;
    else             reader = _readerFS_l_do;
  }
 
  float sf = reader->eval(fl, jet -> eta(), std::max((float)30.,std::min((float)799.,jet->pt())));
  return sf;

} 


float
SusyModule::bTagPt(float rawPt){
  if(rawPt>600) return 600;
  if(rawPt < 30) return 30;
  return rawPt;
}


// ------------------ SF stuff from Giuseppe -------------------


float 
SusyModule::GCtriggerScaleFactor(int pdgId1, int pdgId2, float pt1, float pt2, float ht) {
  if (ht>300) {
    if ((abs(pdgId1)+abs(pdgId2))==22) return 1.;
    if ((abs(pdgId1)+abs(pdgId2))==26) return 0.985*0.985;
    if ((abs(pdgId1)+abs(pdgId2))==24) return 0.985;
  } else {
    if ((abs(pdgId1)+abs(pdgId2))==22) return 0.997*0.997*0.998;
    if ((abs(pdgId1)+abs(pdgId2))==26) return 0.982*0.985*0.973;
    if ((abs(pdgId1)+abs(pdgId2))==24) {
      if (abs(pdgId1)==11) {
	if (pt1>pt2) return 0.997*0.985;
	else return 0.997*0.982;
      } else {
	if (pt1>pt2) return 0.997*0.982;
	else return 0.997*0.985;
      }
    }
  }
  return 0.;
}

float 
SusyModule::GCelectronScaleFactorHighHT(float pt, float eta) {
   if (pt>=10 && pt<20 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.800833;
   if (pt>=10 && pt<20 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 1.09259;
   if (pt>=10 && pt<20 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 1.38004;
   if (pt>=10 && pt<20 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 1.06353;
   if (pt>=10 && pt<20 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 1.01303;
   if (pt>=20 && pt<30 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.951939;
   if (pt>=20 && pt<30 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.978131;
   if (pt>=20 && pt<30 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 1.00001;
   if (pt>=20 && pt<30 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 0.944541;
   if (pt>=20 && pt<30 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.958243;
   if (pt>=30 && pt<40 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.974265;
   if (pt>=30 && pt<40 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.979292;
   if (pt>=30 && pt<40 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.978247;
   if (pt>=30 && pt<40 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 0.973954;
   if (pt>=30 && pt<40 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.982194;
   if (pt>=40 && pt<50 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.979367;
   if (pt>=40 && pt<50 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.984915;
   if (pt>=40 && pt<50 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.989583;
   if (pt>=40 && pt<50 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 1.00021;
   if (pt>=40 && pt<50 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.995648;
   if (pt>=50 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.980086;
   if (pt>=50 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.980024;
   if (pt>=50 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.986589;
   if (pt>=50 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 0.984587;
   if (pt>=50 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.995184;
   return 0.;
}
float 
SusyModule::GCelectronScaleFactorLowHT(float pt, float eta) {
   if (pt>=10 && pt<20 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.81309;
   if (pt>=10 && pt<20 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 1.09402;
   if (pt>=10 && pt<20 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 1.38969;
   if (pt>=10 && pt<20 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 1.05715;
   if (pt>=10 && pt<20 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 1.01151;
   if (pt>=20 && pt<30 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.952485;
   if (pt>=20 && pt<30 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.978021;
   if (pt>=20 && pt<30 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.999009;
   if (pt>=20 && pt<30 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 0.947156;
   if (pt>=20 && pt<30 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.957892;
   if (pt>=30 && pt<40 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.974451;
   if (pt>=30 && pt<40 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.978913;
   if (pt>=30 && pt<40 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.979384;
   if (pt>=30 && pt<40 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 0.973866;
   if (pt>=30 && pt<40 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.981911;
   if (pt>=40 && pt<50 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.979478;
   if (pt>=40 && pt<50 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.984782;
   if (pt>=40 && pt<50 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.990569;
   if (pt>=40 && pt<50 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 1.00085;
   if (pt>=40 && pt<50 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.996501;
   if (pt>=50 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.980182;
   if (pt>=50 && std::abs(eta)>=0.8 && std::abs(eta)<1.442 ) return 0.979994;
   if (pt>=50 && std::abs(eta)>=1.442 && std::abs(eta)<1.566 ) return 0.988436;
   if (pt>=50 && std::abs(eta)>=1.566 && std::abs(eta)<2 ) return 0.984572;
   if (pt>=50 && std::abs(eta)>=2 && std::abs(eta)<2.5 ) return 0.995253;
   return 0.;
}
float 
SusyModule::GCmuonScaleFactor(float pt, float eta) {
   if (pt>=10 && pt<20 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.950673;
   if (pt>=10 && pt<20 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.959971;
   if (pt>=10 && pt<20 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.96344;
   if (pt>=10 && pt<20 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.97954;
   if (pt>=20 && pt<25 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.968778;
   if (pt>=20 && pt<25 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.985696;
   if (pt>=20 && pt<25 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.986646;
   if (pt>=20 && pt<25 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.961432;
   if (pt>=25 && pt<30 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.986112;
   if (pt>=25 && pt<30 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.982328;
   if (pt>=25 && pt<30 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.981606;
   if (pt>=25 && pt<30 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.964637;
   if (pt>=30 && pt<40 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.989584;
   if (pt>=30 && pt<40 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.990363;
   if (pt>=30 && pt<40 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.989629;
   if (pt>=30 && pt<40 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.954459;
   if (pt>=40 && pt<50 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.990997;
   if (pt>=40 && pt<50 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.990606;
   if (pt>=40 && pt<50 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.991023;
   if (pt>=40 && pt<50 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.951617;
   if (pt>=50 && pt<60 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.987545;
   if (pt>=50 && pt<60 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.989335;
   if (pt>=50 && pt<60 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.99151;
   if (pt>=50 && pt<60 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.94982;
   if (pt>=60 && std::abs(eta)>=0 && std::abs(eta)<0.9 ) return 0.992751;
   if (pt>=60 && std::abs(eta)>=0.9 && std::abs(eta)<1.2 ) return 0.9878;
   if (pt>=60 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.988131;
   if (pt>=60 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.958638;
   return 0.;
}

float 
SusyModule::GCleptonScaleFactor(int pdgId, float pt, float eta, float ht) {
  if (abs(pdgId)==13) return GCmuonScaleFactor(pt, eta);
  else if (abs(pdgId)==11){
    if(ht>300) return GCelectronScaleFactorHighHT(pt, eta);
    else       return GCelectronScaleFactorLowHT(pt, eta);
  }
  return 0.;
}

float 
SusyModule::GCeventScaleFactor(int pdgId1, int pdgId2, float pt1, float pt2, float eta1, float eta2, float ht) {
  return GCtriggerScaleFactor(pdgId1, pdgId2, pt1, pt2, ht) * 
         GCleptonScaleFactor (pdgId1, pt1, eta1, ht) * 
         GCleptonScaleFactor(pdgId2, pt2, eta2, ht);
}




// ------------------ SF stuff from Laurent -------------------

double 
SusyModule::LTFastSimTriggerEfficiency(double HT, double l1_Pt, int l1_pdgId, double l2_Pt, int l2_pdgId) {
  double pt1, pt2; 
  //Sort leptons: electrons first, then muon
  //Amongst the same flavor, sort by pt

  if(abs(l1_pdgId) == abs(l2_pdgId)){
    pt1 = (l1_Pt>l2_Pt)? l1_Pt: l2_Pt ; 
    pt2 = (l1_Pt>l2_Pt)? l2_Pt: l1_Pt ; 
  }
  else{
    pt1= (abs(l1_pdgId)< abs(l2_pdgId))? l1_Pt:l2_Pt; 
    pt2= (abs(l1_pdgId)< abs(l2_pdgId))? l2_Pt:l1_Pt; 
  } 



  if(HT>80 && HT<=150){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.901454;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.942286;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.957884;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.915385;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.934807;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.95;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.957918;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.9128;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.955773;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.96567;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.969886;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.976102;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.915323;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.94704;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.963359;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.967742;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.983276;
      if(pt1>100. && pt2>100.) return 0.986301;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.873717;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.870614;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.896967;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.895973;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.923441;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.934142;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.928716;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.93617;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.921466;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.934702;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.93576;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.936442;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.942179;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.942545;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.941558;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.928756;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.943327;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.952617;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.951613;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.955859;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.954449;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.960159;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.942029;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.957756;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.949438;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.95452;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.952258;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.95515;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.949413;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.959654;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.937931;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.962076;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.969893;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.961538;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.950055;
      if(pt1>100. && pt2>100.) return 0.968534;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.945614;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.950939;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.951076;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.960113;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.928707;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.958694;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.957458;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.956865;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.958692;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.945736;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.953125;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.960789;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.958855;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.955881;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.955658;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.940191;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.946869;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.957447;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.961307;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.958892;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.950298;
      if(pt1>100. && pt2>100.) return 0.935943;
    }
    else return 0;
  }
  if(HT>150 && HT<=300){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.902316;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.935867;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.952381;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.896133;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.940891;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.954545;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.960618;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.919115;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.94696;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.957937;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.969733;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.975612;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.910321;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.949509;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.966376;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.97209;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.97965;
      if(pt1>100. && pt2>100.) return 0.983429;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.868211;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.882721;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.883999;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.870219;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.926146;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.912413;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.926985;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.914962;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.927951;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.934032;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.940945;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.933834;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.93512;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.941769;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.940374;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.933817;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.946082;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.950611;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.946244;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.947135;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.948951;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.947566;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.939487;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.949677;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.947852;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.955468;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.952626;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.953233;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.952798;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.938119;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.951521;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.955197;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.94905;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.953109;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.949548;
      if(pt1>100. && pt2>100.) return 0.944965;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.944513;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.952299;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.956522;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.95232;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.944979;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.955279;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.957053;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.956792;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.953535;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.94373;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.951135;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.955552;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.956778;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.956169;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.952121;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.946903;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.959514;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.95028;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.951219;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.947489;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.942206;
      if(pt1>100. && pt2>100.) return 0.943656;
    }
    else return 0;
  }
  if(HT>300 && HT<=350){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.6;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.722222;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.657143;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.817518;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.825503;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.892655;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.927083;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.906475;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.929825;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.980519;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.888889;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.945137;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.966245;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.976082;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.978176;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.918699;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.951049;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.973422;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.989583;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.984314;
      if(pt1>100. && pt2>100.) return 0.989761;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.641509;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.741379;
      if(pt1>15. && pt1<=20. && pt2>20. && pt2<=25.) return 0.662162;
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.735714;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.844444;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.905063;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.860759;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.793651;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.71;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.681818;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.73516;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.838889;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.917782;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.875598;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.847826;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.811111;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.854545;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.886076;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.933649;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.928333;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.923754;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.894737;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.940476;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.943878;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.913333;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.94837;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.944198;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.954023;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.951654;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.957895;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.96118;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.961295;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.959322;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.959381;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.957878;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.958042;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.956989;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.960591;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.972665;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.970976;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.971081;
      if(pt1>100. && pt2>100.) return 0.969887;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>10. && pt1<=15. && pt2>10. && pt2<=15.) return 0.866667;
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.684783;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.678571;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.740741;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.722222;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.62963;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.70283;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.710037;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.790323;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.672131;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.862637;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.82716;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.87619;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.837174;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.886447;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.915663;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.921283;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.919075;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.912069;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.919419;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.921429;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.903955;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.925197;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.937984;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.927711;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.913858;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.93019;
      if(pt1>100. && pt2>100.) return 0.939806;
    }
    else return 0;
  }
  if(HT>350 && HT<=400){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 1;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.945946;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 1;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.830769;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.943182;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.961538;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.855072;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.910448;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.953488;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.961039;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.856481;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.950758;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.965577;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.971483;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.975381;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.945205;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.92233;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.959276;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.979675;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.979167;
      if(pt1>100. && pt2>100.) return 0.983806;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.96875;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.95;
      if(pt1>15. && pt1<=20. && pt2>20. && pt2<=25.) return 0.846154;
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.829787;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.901099;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.902778;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.85;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 1;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.916667;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.966102;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.858156;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.921875;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.934579;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.93985;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.915663;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.95935;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.924242;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.942373;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.955466;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.933896;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.92053;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.894118;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.959677;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.957143;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.94386;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.946154;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.962079;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.964912;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.955479;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.959302;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.960494;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.96792;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.962169;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.959751;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.944964;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.971429;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.95092;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.961783;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.961957;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.9701;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.971144;
      if(pt1>100. && pt2>100.) return 0.963893;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>10. && pt1<=15. && pt2>10. && pt2<=15.) return 0.944444;
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.928571;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.794118;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.935484;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.915663;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.911765;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.91453;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.908537;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.909091;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.925134;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.946565;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.921212;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.940887;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.941691;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.936047;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.95679;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.940803;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.926554;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.940257;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.944498;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.948026;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.954248;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.978378;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.932642;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.948546;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.951157;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.937548;
      if(pt1>100. && pt2>100.) return 0.936061;
    }
    else return 0;
  }
  if(HT>400 && HT<=800){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.888889;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.886792;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.943662;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.864198;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.915541;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.941748;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.891667;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.968198;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.953285;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.966049;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.911622;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.929006;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.959006;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.967981;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.975743;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.894928;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.945865;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.961408;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.974609;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.983743;
      if(pt1>100. && pt2>100.) return 0.986499;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.918919;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.902098;
      if(pt1>15. && pt1<=20. && pt2>20. && pt2<=25.) return 0.884848;
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.860947;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.894558;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.892045;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.873303;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.92;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.916201;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.912621;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.921801;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.917738;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.935759;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.928398;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.93949;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.949029;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.958057;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.947429;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.942286;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.948181;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.947034;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.962121;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.944297;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.953684;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.970954;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.95526;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.958278;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.956614;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.960707;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.965243;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.959032;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.956389;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.96952;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.961897;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.955745;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.956522;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.966025;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.969052;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.966071;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.965698;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.966688;
      if(pt1>100. && pt2>100.) return 0.964623;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>10. && pt1<=15. && pt2>10. && pt2<=15.) return 0.971429;
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.949495;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.908257;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.94086;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.897638;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.9375;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.947846;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.94188;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.936202;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.938897;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.920635;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.922481;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.944805;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.944674;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.946087;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.95036;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.941913;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.940397;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.949603;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.947381;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.945082;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.942308;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.94385;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.943507;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.940537;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.946047;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.942713;
      if(pt1>100. && pt2>100.) return 0.937208;
    }
    else return 0;
  }
  if(HT>800 && HT<=1600){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.777778;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.846774;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.882353;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.869732;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.924471;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.942675;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.904382;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.917763;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.937591;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.962644;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.857143;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.899065;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.947368;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.943478;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.963075;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.863839;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.898723;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.941104;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.953275;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.968577;
      if(pt1>100. && pt2>100.) return 0.977384;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.861314;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.896341;
      if(pt1>15. && pt1<=20. && pt2>20. && pt2<=25.) return 0.873494;
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.87106;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.863372;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.885152;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.881298;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.901786;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.92;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.939252;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.940397;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.917275;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.923379;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.918803;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.925816;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.949109;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.956;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.944328;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.941514;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.939907;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.940453;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.961538;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.934896;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.951945;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.945175;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.946953;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.956379;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.953683;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.9583;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.960645;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.961644;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.964843;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.959388;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.96071;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.955142;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.954833;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.957529;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.970267;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.970022;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.968966;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.966912;
      if(pt1>100. && pt2>100.) return 0.961464;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>10. && pt1<=15. && pt2>10. && pt2<=15.) return 0.961039;
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.954128;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.930233;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.931818;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.943333;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.971098;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.940206;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.939935;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.957516;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.952646;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.93819;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.954098;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.945545;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.95264;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.94462;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.937914;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.953266;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.948914;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.946694;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.948549;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.947672;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.939743;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.946653;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.948159;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.949451;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.941121;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.940587;
      if(pt1>100. && pt2>100.) return 0.934288;
    }
    else return 0;
  }
  if(HT>1600 && HT<=2500){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.25;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.833333;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.714286;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.8125;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.884615;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.740741;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.842105;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.862069;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 1;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.6375;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.75;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.812183;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.82439;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.835784;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.69697;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.764706;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.8;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.815;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.876033;
      if(pt1>100. && pt2>100.) return 0.921606;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.916667;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.818182;
      if(pt1>15. && pt1<=20. && pt2>20. && pt2<=25.) return 0.8;
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.894737;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.9;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.806818;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.79798;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.733333;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.761905;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.9375;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.74359;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.892857;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.842105;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.871795;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.903226;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.805556;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.931035;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.922222;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.951613;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.892193;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.913208;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.961538;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.965517;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.938776;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.924242;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.967213;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.937255;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.933086;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.915789;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.985816;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.96748;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.937086;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.956364;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.946429;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.939227;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.961165;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.974576;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.954887;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.958477;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.95189;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.959932;
      if(pt1>100. && pt2>100.) return 0.964207;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>10. && pt1<=15. && pt2>10. && pt2<=15.) return 0.857143;
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.95;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.857143;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 1;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.818182;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.916667;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.941176;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.957447;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.947368;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.980769;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 1;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.93617;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.959184;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.97;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.963636;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.943925;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.958333;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.934426;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.960212;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.968661;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.957143;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.953846;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.953488;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.955056;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.949853;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.948586;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.945442;
      if(pt1>100. && pt2>100.) return 0.938983;
    }
    else return 0;
  }
  if(HT>2500){
    if(abs(l1_pdgId)+abs(l2_pdgId) ==22){
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.5;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 0.75;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.555556;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.411765;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.75;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.5;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.875;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.73913;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.833333;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.454545;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.5;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.66129;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.698413;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.736625;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.352941;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.537313;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.566929;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.721311;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.77027;
      if(pt1>100. && pt2>100.) return 0.808362;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==24){
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.8;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 0.8;
      if(pt1>15. && pt1<=20. && pt2>20. && pt2<=25.) return 0.5;
      if(pt1>15. && pt1<=20. && pt2>25. && pt2<=35.) return 0.727273;
      if(pt1>15. && pt1<=20. && pt2>35. && pt2<=45.) return 0.666667;
      if(pt1>15. && pt1<=20. && pt2>45. && pt2<=100.) return 0.781818;
      if(pt1>15. && pt1<=20. && pt2>100.) return 0.676056;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.833333;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 0.888889;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 1;
      if(pt1>20. && pt1<=25. && pt2>25. && pt2<=35.) return 0.777778;
      if(pt1>20. && pt1<=25. && pt2>35. && pt2<=45.) return 0.894737;
      if(pt1>20. && pt1<=25. && pt2>45. && pt2<=100.) return 0.8;
      if(pt1>20. && pt1<=25. && pt2>100.) return 0.746835;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.933333;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.777778;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.894737;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.875;
      if(pt1>25. && pt1<=35. && pt2>35. && pt2<=45.) return 0.866667;
      if(pt1>25. && pt1<=35. && pt2>45. && pt2<=100.) return 0.842424;
      if(pt1>25. && pt1<=35. && pt2>100.) return 0.803922;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 0.888889;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 1;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 0.833333;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.822222;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 0.925;
      if(pt1>35. && pt1<=45. && pt2>45. && pt2<=100.) return 0.865497;
      if(pt1>35. && pt1<=45. && pt2>100.) return 0.861446;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.877551;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.854839;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.939759;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.935294;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.913979;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.927419;
      if(pt1>45. && pt1<=100. && pt2>100.) return 0.903614;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.984375;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.934211;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.986842;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.976331;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.927273;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.94825;
      if(pt1>100. && pt2>100.) return 0.944633;
    }
    else if(abs(l1_pdgId)+abs(l2_pdgId) ==26){
      if(pt1>10. && pt1<=15. && pt2>10. && pt2<=15.) return 1;
      if(pt1>15. && pt1<=20. && pt2>10. && pt2<=15.) return 0.9;
      if(pt1>15. && pt1<=20. && pt2>15. && pt2<=20.) return 1;
      if(pt1>20. && pt1<=25. && pt2>10. && pt2<=15.) return 0.888889;
      if(pt1>20. && pt1<=25. && pt2>15. && pt2<=20.) return 1;
      if(pt1>20. && pt1<=25. && pt2>20. && pt2<=25.) return 1;
      if(pt1>25. && pt1<=35. && pt2>10. && pt2<=15.) return 0.888889;
      if(pt1>25. && pt1<=35. && pt2>15. && pt2<=20.) return 0.9;
      if(pt1>25. && pt1<=35. && pt2>20. && pt2<=25.) return 0.96;
      if(pt1>25. && pt1<=35. && pt2>25. && pt2<=35.) return 0.970588;
      if(pt1>35. && pt1<=45. && pt2>10. && pt2<=15.) return 1;
      if(pt1>35. && pt1<=45. && pt2>15. && pt2<=20.) return 0.958333;
      if(pt1>35. && pt1<=45. && pt2>20. && pt2<=25.) return 1;
      if(pt1>35. && pt1<=45. && pt2>25. && pt2<=35.) return 0.9375;
      if(pt1>35. && pt1<=45. && pt2>35. && pt2<=45.) return 1;
      if(pt1>45. && pt1<=100. && pt2>10. && pt2<=15.) return 0.94186;
      if(pt1>45. && pt1<=100. && pt2>15. && pt2<=20.) return 0.968085;
      if(pt1>45. && pt1<=100. && pt2>20. && pt2<=25.) return 0.941176;
      if(pt1>45. && pt1<=100. && pt2>25. && pt2<=35.) return 0.930736;
      if(pt1>45. && pt1<=100. && pt2>35. && pt2<=45.) return 0.957547;
      if(pt1>45. && pt1<=100. && pt2>45. && pt2<=100.) return 0.936118;
      if(pt1>100. && pt2>10. && pt2<=15.) return 0.979381;
      if(pt1>100. && pt2>15. && pt2<=20.) return 0.93578;
      if(pt1>100. && pt2>20. && pt2<=25.) return 0.942623;
      if(pt1>100. && pt2>25. && pt2<=35.) return 0.927126;
      if(pt1>100. && pt2>35. && pt2<=45.) return 0.926087;
      if(pt1>100. && pt2>45. && pt2<=100.) return 0.952656;
      if(pt1>100. && pt2>100.) return 0.932476;
    }
    else return 0;
  }

  return 0;
}


float
SusyModule::getVarWeightFastSimLepSF(const Candidate* l1, 
				     const Candidate* l2, int dir) {

  float unc=1;
  if(std::abs(l1->pdgId())==11) {
    if(l1->pt()<20) unc+=0.10*dir;
    else if(l1->pt()<30) unc+=0.10*dir;
    else if(l1->pt()<200) unc+=0.05*dir;
  }
  if(std::abs(l1->pdgId())==13) {
    if(l1->pt()<20) unc+=0.10*dir;
    else if(l1->pt()<30) unc+=0.03*dir;
    else if(l1->pt()<200) unc+=0.03*dir;
  }
  
  float unc2=1;
  if(std::abs(l2->pdgId())==11) {
    if(l2->pt()<20) unc2+=0.10*dir;
    else if(l2->pt()<30) unc2+=0.10*dir;
    else if(l2->pt()<200) unc2+=0.05*dir;
  }
  if(std::abs(l2->pdgId())==13) {
    if(l2->pt()<20) unc2+=0.10*dir;
    else if(l2->pt()<30) unc2+=0.03*dir;
    else if(l2->pt()<200) unc2+=0.03*dir;
  }
  
  return unc*unc2;

}

float
SusyModule::getVarWeightFastSimLepSFRA7(const CandList& cands, int dir) {

    float totUnc = 1.;
    for(size_t il = 0;il<cands.size();il++){
        const Candidate* cand = cands[il];
        float unc = 1.;
        if(std::abs(cand->pdgId())==11) {
            if(cand->pt()<20) unc+=0.10*dir;
            else if(cand->pt()<30) unc+=0.08*dir;
            else unc+=0.05*dir;
        }
        if(std::abs(cand->pdgId())==13) {
            if(cand->pt()<20) unc+=0.03*dir;
            else if(cand->pt()<30) unc+=0.01*dir;
            else unc+=0.01*dir;
        }
        totUnc *= unc;
    }
    return totUnc;
}

float
SusyModule::getWeightFastSimHltSFRA7(const CandList& cands, float HT) {

    int nEl = 0;
    bool lowPtEl = false;
    for(size_t il = 0;il<cands.size();il++){
        const Candidate* cand = cands[il];
        if(std::abs(cand->pdgId())==11){
            nEl +=1;
            if(cand->pt()<15. && HT < 400) lowPtEl = true;
        }
    }
    if(nEl>=3) return 0.97;
    else if(lowPtEl) return 0.93;
    else return 1.;

}


float
SusyModule::getVarWeightFastSimHltSFRA7(const CandList& cands, float HT, int dir) {

    int nEl = 0;
    bool lowPtEl = false;
    for(size_t il = 0;il<cands.size();il++){
        const Candidate* cand = cands[il];
        if(std::abs(cand->pdgId())==11){
            nEl +=1;
            if(cand->pt()<15. && HT < 400) lowPtEl = true;
        }
    }
    if(nEl>=3) return 1+dir*0.05;
    else if(lowPtEl) return 1+dir*0.05;
    else return 1+dir*0.03;

}

float 
SusyModule::getPuWeight(unsigned int nvtx) {
  if(nvtx>_puWeights.size()-1) return 1;
  return _puWeights[nvtx];
}

void
SusyModule::initPUWeights() {

  _puWeights.push_back(1.0);
  _puWeights.push_back(3.153000427291265);
  _puWeights.push_back(2.4535501340758543);
  _puWeights.push_back(2.353696182351581);
  _puWeights.push_back(2.3718057802881676);
  _puWeights.push_back(2.3508262193470397);
  _puWeights.push_back(2.291773427755106);
  _puWeights.push_back(2.129929297304804);
  _puWeights.push_back(1.9422796094930384);
  _puWeights.push_back(1.7126175249202766);
  _puWeights.push_back(1.4622401225778663);
  _puWeights.push_back(1.2063711142884181);
  _puWeights.push_back(0.9608504360968657);
  _puWeights.push_back(0.7484941355600901);
  _puWeights.push_back(0.5769889517104192);
  _puWeights.push_back(0.4315759540480359);
  _puWeights.push_back(0.3195820162866148);
  _puWeights.push_back(0.2306052595765186);
  _puWeights.push_back(0.1691819686464576);
  _puWeights.push_back(0.12324466445693416);
  _puWeights.push_back(0.08833641123547825);
  _puWeights.push_back(0.06306193566475429);
  _puWeights.push_back(0.047857788612281564);
  _puWeights.push_back(0.034655984107483044);
  _puWeights.push_back(0.02358209210941948);
  _puWeights.push_back(0.019535383939466185);
  _puWeights.push_back(0.01500976654907348);
  _puWeights.push_back(0.009407396052837736);
  _puWeights.push_back(0.006332906010381258);
  _puWeights.push_back(0.008524617116368491);
  _puWeights.push_back(0.003145186350322339);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.006930381551001214);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(0.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);
  _puWeights.push_back(1.0);

}



void
SusyModule::applyISRWeight(unsigned int process, int var, float& weight) {
  // process = 0 (gluino-gluino production)
  // var = 0 (central), -1 (down), +1 (up)

  CandList collection;
  if(process==0) collection = collectGenParticles(1000021, 3);
  //cout<<" number of gluinos "<<collection.size()<<endl;
  if(collection.size()!=2) return;

  Candidate* cand=Candidate::create(collection[0],collection[1]);

  float pt=cand->pt();
  isrWeight(var, pt, weight);

}


void
SusyModule::isrWeight(int var, float pt, float& weight){
  // var = 0 (central), -1 (down), +1 (up)

  // down variation
  if(var == -1){
    if     (pt > 600) weight *= 0.7;
    else if(pt > 400) weight *= 0.85;
  }

  // up variation
  else if(var == 1){
    if     (pt > 600) weight *= 1.3;
    else if(pt > 400) weight *= 1.15;
  }

}


CandList
SusyModule::collectGenParticles(int pdgId, int status){

  CandList list;
  for(unsigned int i = 0; i < _vc->get("nGenPart"); ++i){
    if(std::abs(_vc->get("GenPart_pdgId",i)) == pdgId)
      list.push_back(Candidate::create(_vc->get("GenPart_pt"    , i), 
                                       _vc->get("GenPart_eta"   , i),
                                       _vc->get("GenPart_phi"   , i),
				       _vc->get("GenPart_pdgId"   , i),
				       _vc->get("GenPart_charge", i),
				       _vc->get("GenPart_mass"  , i)
				       ));
  }
  return list;
}

