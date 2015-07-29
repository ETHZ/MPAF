#include "analysis/modules/SusyModule.hh"


SusyModule::SusyModule(VarClass* vc):
  _vc(vc)
{
  defineLeptonWPS();
}

SusyModule::~SusyModule() {

  delete _vc;
}


void
SusyModule::defineLeptonWPS() {

  _cLostHitWP.resize(kNWPs);
  _sipWP.resize(kNWPs);
  _dxyWP.resize(kNWPs);
  _dzWP.resize(kNWPs);
  _elMvaIdWP.resize(3);
  _multiIsoWP.resize(3);
  _ptWP.resize(2);

  for(int i=0;i<3;++i) {
    _elMvaIdWP[i].resize(kNWPs);
    _multiIsoWP[i].resize(kNWPs);
    if(i!=2) _ptWP[i].resize(kNWPs);
  }
  
  //conv rej ====================
  _cLostHitWP[kLoose] = 0; 
  _cLostHitWP[kTight] = 0; 

  //pt ============================
  _ptWP[kEl][kDenom] = 7 ; _ptWP[kMu][kDenom] = 5 ;
  _ptWP[kEl][kLoose] = 7 ; _ptWP[kMu][kLoose] = 5 ;
  _ptWP[kEl][kTight] = 10; _ptWP[kMu][kTight] = 10;

  //sip & IP ======================
  _sipWP[kLoose] = 4.0; 
  _sipWP[kTight] = 4.0; 
  
  _dxyWP[kLoose] = 0.05; //cm
  _dxyWP[kTight] = 0.05; //cm
  
  _dzWP[kLoose] = 0.1; //cm
  _dzWP[kTight] = 0.1; //cm


  //el mva id ======================
  _elMvaIdWP[kEBC][kLoose] = -0.11;
  _elMvaIdWP[kEBF][kLoose] = -0.35;
  _elMvaIdWP[kEE ][kLoose] = -0.55;

  _elMvaIdWP[kEBC][kTight] = 0.73;
  _elMvaIdWP[kEBF][kTight] = 0.57;
  _elMvaIdWP[kEE ][kTight] = 0.05;

  //multiIso =======================
  _multiIsoWP[kMiniIso][kDenom]      = 0.4 ; _multiIsoWP[kPtRatio][kDenom]      = 0   ; _multiIsoWP[kPtRel][kDenom]      = 0  ;
  _multiIsoWP[kMiniIso][kLoose]      = 0.4 ; _multiIsoWP[kPtRatio][kLoose]      = 0   ; _multiIsoWP[kPtRel][kLoose]      = 0  ;
  _multiIsoWP[kMiniIso][kMedium]     = 0.14; _multiIsoWP[kPtRatio][kMedium]     = 0.68; _multiIsoWP[kPtRel][kMedium]     = 6.7; 
  _multiIsoWP[kMiniIso][kTight]      = 0.10; _multiIsoWP[kPtRatio][kTight]      = 0.70; _multiIsoWP[kPtRel][kTight]      = 7  ;

  _multiIsoWP[kMiniIso][kSpecFakeEl] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeEl] = 0.70; _multiIsoWP[kPtRel][kSpecFakeEl] = 7  ;
  _multiIsoWP[kMiniIso][kSpecFakeMu] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeMu] = 0.68; _multiIsoWP[kPtRel][kSpecFakeMu] = 6.7;
}


//=====================================================
// lepton selection

bool
SusyModule::multiIsoSel(int idx, int wp) const {

  if( _vc->get("LepGood_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
      (_vc->get("LepGood_jetPtRatio", idx)>_multiIsoWP[kPtRatio][wp] ||
       _vc->get("LepGood_jetPtRel", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelCone(int idx, int wp) const {

  if( _vc->get("LepGood_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
      (conePt(idx)*_vc->get("LepGood_pt",idx) *_vc->get("LepGood_jetPtRatio", idx)>_multiIsoWP[kPtRatio][wp] ||
       _vc->get("LepGood_jetPtRel", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}

bool
SusyModule::invMultiIsoSel(int idx, int wp) const {
  
  if( _vc->get("LepGood_miniRelIso", idx)>_multiIsoWP[kMiniIso][wp]) return false;
  if( 1./_vc->get("LepGood_jetPtRel", idx) > (1/_multiIsoWP[kPtRel][wp] + _vc->get("LepGood_miniRelIso", idx)) ) return false;
  return true;
}

bool 
SusyModule::elMvaSel(int idx, int wp) const {

  int etaBin=-1;

  if     (std::abs(_vc->get("LepGood_eta", idx)) < 0.8  ) etaBin=0;
  else if(std::abs(_vc->get("LepGood_eta", idx)) < 1.479) etaBin=1;
  else if(std::abs(_vc->get("LepGood_eta", idx)) < 2.5  ) etaBin=2;

  if(_vc->get("LepGood_mvaIdPhys14", idx) <  _elMvaIdWP[etaBin][wp]  ) return false;
    
  return true;
}



bool
SusyModule::muIdSel(int idx, int wp) const {

  int wpIso = kDenom;

  if(         _vc->get("LepGood_pt"          , idx)  < _ptWP[kMu][wp]) return false;
  if(std::abs(_vc->get("LepGood_eta"         , idx)) >  2.4          ) return false;
  if(         _vc->get("LepGood_mediumMuonId", idx)  <= 0            ) return false;
  if(         _vc->get("LepGood_tightCharge" , idx)  <= 1            ) return false;
  if(         _vc->get("LepGood_sip3d"       , idx)  > _sipWP[wp]    ) return false;
  if(std::abs(_vc->get("LepGood_dz"          , idx)) > _dzWP[wp]     ) return false;
  if(std::abs(_vc->get("LepGood_dxy"         , idx)) > _dxyWP[wp]    ) return false;
  if(!multiIsoSel(idx, wpIso)                                        ) return false;

  return true;

}


bool
SusyModule::elIdSel(int idx, int wp, int mvaWp) const {

  int wpIso=kDenom;

  if(         _vc->get("LepGood_pt"         , idx)  < _ptWP[kEl][wp] ) return false;
  if(std::abs(_vc->get("LepGood_eta"        , idx)) > 2.5            ) return false;
  if(std::abs(_vc->get("LepGood_eta"        , idx)) > 1.4442 &&
     std::abs(_vc->get("LepGood_eta"        , idx)) < 1.566          ) return false;

  if(         _vc->get("LepGood_convVeto"   , idx)  != 1             ) return false;
  if(         _vc->get("LepGood_lostHits"   , idx)  > _cLostHitWP[wp]) return false;

  if(         _vc->get("LepGood_tightCharge", idx)  <= 1             ) return false;

  if(         _vc->get("LepGood_sip3d"      , idx)  > _sipWP[wp]     ) return false;
  if(std::abs(_vc->get("LepGood_dz"         , idx)) > _dzWP[wp]      ) return false;
  if(std::abs(_vc->get("LepGood_dxy"        , idx)) > _dxyWP[wp]     ) return false;
  if(!elMvaSel(idx, mvaWp)                                           ) return false;
  if(!multiIsoSel(idx, wpIso)                                        ) return false;

  //cout<<idx<<"   iso+sip"<<endl;

  // electron cleaning ==================
  // for(unsigned int il=0; il<_vc->get("nLepGood"); ++il){
  //   float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", idx),
  //                            _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", idx));
  //   if(std::abs(_vc->get("LepGood_pdgId"))==13 && dr<0.05 ) return false;
  // }
  //cout<<idx<<"   clean"<<endl;
  return true;
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

  //cout<<"Id "<<c1->pdgId()<<"  "<<c2->pdgId()<<"  "<< Candidate::create(c1,c2)->mass()<<"  "<<mllm<<"  "<<mllM<<endl;
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
    //cout<<" passng veto? "<<passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)<<endl;
    if(!passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)) return false;
  }
  return true;
}

CandList
SusyModule::bestSSPair(const CandList* leps, bool byflav,
		       bool bypassMV, float pTthr, int& idx1, int& idx2) {

//HACK: replaced nullptr with NULL
  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  if(leps->size()<=2) return (*leps);
  
  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      
      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr || leps->at(il2)->pt()<pTthr) continue; 

      if(!passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false) && !bypassMV) continue;

      if(leps->at(il1)->charge()!=leps->at(il2)->charge()) continue;

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
SusyModule::bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		       bool bypassMV, float pTthr, int& idx1, int& idx2) {

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;
  if(leps->size()<=1) {
    clist[0] = c1;
    clist[1] = leps->at(0);
    return clist;
  }
  
  for(unsigned int il=0;il<leps->size();il++) {
      
      //conditional pt threshold, could evolve in CERN code 
      if(c1->pt()<pTthr || leps->at(il)->pt()<pTthr) continue; 

      if(!passMllSingleVeto(c1, leps->at(il), 0, 8, false) && !bypassMV) continue;

      if(c1->charge()!=leps->at(il)->charge()) continue;

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


float
SusyModule::closestJetPt(int idx) const {

  return _vc->get("LepGood_pt", idx) / _vc->get("LepGood_jetPtRatio", idx);
}


float 
SusyModule::conePt(int idx, int isoWp) const {

  if(_vc->get("LepGood_jetPtRel", idx) > _multiIsoWP[kPtRel][isoWp] ) {
    return std::max(_vc->get("LepGood_pt", idx), (double) closestJetPt(idx) * _multiIsoWP[kPtRatio][isoWp] );
  }

  return _vc->get("LepGood_pt", idx)*(1 + std::max((double) 0., _vc->get("LepGood_miniRelIso", idx) - _multiIsoWP[kMiniIso][isoWp] ) );
}


void
SusyModule::cleanJets(CandList* leptons, 
		      CandList& cleanJets, vector<unsigned int>& jetIdxs,
		      CandList& cleanBJets, vector<unsigned int>& bJetIdxs ) {

  cleanJets.clear();
  cleanBJets.clear();
  jetIdxs.clear();
  bJetIdxs.clear();

  bool findLep=false;
  for(int ij=0;ij<_vc->get("nJet");ij++) {
    
    if(_vc->get("Jet_id",ij)<1) continue;

    Candidate* jet=Candidate::create(_vc->get("Jet_pt", ij),
				     _vc->get("Jet_eta", ij),
				     _vc->get("Jet_phi", ij) );
    
    //cout<<" pt: "<<jet->pt()<<"  eta: "<<jet->eta()<<"  phi: "<<jet->phi()<<"  "<<_vc->get("Jet_btagCSV",ij)<<endl;
    //jet->print( cout );
    findLep=false;
    for(unsigned int il=0;il<leptons->size();il++) {
      // cout<<"\t ====> "<<leptons->at(il)->pt()<<"   "
      // 	  <<leptons->at(il)->eta()<<"  "<<leptons->at(il)->phi()<<" --> "<<leptons->at(il)->dR( jet )<<endl;
      if( leptons->at(il)->dR( jet )<0.4 ) {findLep=true; continue;} 
    }
    if(findLep) continue;
    

    if(jet->pt()<25) continue;

    if(jet->pt()>40) {
      //cout<<" -------------> selected "<<endl;
      cleanJets.push_back(jet);
      jetIdxs.push_back(ij);
     
    }

    if(_vc->get("Jet_btagCSV",ij)<0.814) continue;
    
    cleanBJets.push_back(jet);
    bJetIdxs.push_back(ij);
  }

}
