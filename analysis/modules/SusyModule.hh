#ifndef SusyModule_hh
#define SusyModule_hh

#include "analysis/core/VarClass.hh"
#include "analysis/tools/Candidate.hh"
#include "analysis/utils/KineUtils.hh"
#include "analysis/utils/mt2_bisect.h"

#include "tools/src/DataBaseManager.hh"

class SusyModule {

public:

  SusyModule(VarClass* vc);
  SusyModule(VarClass* vc, DataBaseManager* dbm);
  ~SusyModule();

  
  bool elMvaSel(int elIdx, int wp) const;
  bool muIdSel(int idx, int wp) const;
  bool elIdSel(int idx, int wp, int mvaWp = kTight) const;
  bool multiIsoSel(int idx, int wp) const;
  bool multiIsoSelCone(int idx, int wp) const;
  bool invMultiIsoSel(int idx, int wp) const;
  bool jetSel(int jetIdx) const;
  float HT(const CandList* jets);

  void cleanJets(CandList* leptons, 
		 CandList& cleanJets, vector<unsigned int>& jetIdxs,
		 CandList& cleanBJets, vector<unsigned int>& bJetIdxs );

  bool mllVetoSelection(const Candidate* l1, const Candidate* l2,
			const CandList* allLeps) const ;
  bool mllLMGVeto(const Candidate* cand, const Candidate* veto) const;
  bool mllZVeto(const Candidate* cand, const Candidate* veto) const;
  
  bool passMllSingleVeto(const Candidate* c1, const Candidate* c2, 
			 float mllm, float mllM, bool ossf);
  bool passMllMultiVeto(const Candidate* c1, const CandList* cands, 
			float mllm, float mllM, bool ossf);
  
  CandList bestSSPair(const CandList* leps, bool byflav,
		      bool bypassMV, float pTthr, int& idx1, int& idx2);
  CandList bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		      bool bypassMV, float pTthr, int& idx1, int& idx2);
  
  float closestJetPt(int idx) const;
  float conePt(int idx, int isoWp = kTight) const; 

  void applyHLTSF(const string& hltLine, const vector<Candidate*>& cands, float& weight);
  void applyLepSF(const CandList& cands, float& weight);
  void applySingleLepSF(const Candidate* cand, float& weight);

  enum {kDenom=0,
	kVLoose,
	kLoose,
	kMedium,
	kTight,
	kVTight,
	kSpecFakeEl,
	kSpecFakeMu,
	kNWPs};

  enum {kMiniIso=0,kPtRatio,kPtRel};
  enum {kEBC=0,kEBF,kEE};
  enum {kEl=0,kMu};

  

private:

  void defineLeptonWPS();
  void loadDBs();
  //const
  VarClass* _vc;
  DataBaseManager* _dbm;

  vector<float> _cLostHitWP;
  vector<float> _dxyWP;
  vector<float> _dzWP;
  vector<float> _isoWP;
  vector<float> _miniIsoWP;
  vector<float> _ptRelWP;
  vector<float> _sipWP;

  vector<vector<float> > _elMvaIdWP;
  vector<vector<float> > _multiIsoWP;
  vector<vector<float> > _ptWP;

};

#endif
