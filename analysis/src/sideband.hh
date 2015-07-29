/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef sideband_HH
#define sideband_HH

#include "analysis/core/MPAF.hh"

class sideband: public MPAF {

public:


  // Member Functions

  sideband(std::string);
  virtual ~sideband();


private:

  void initialize();

  void run();
  void defineOutput();
  void loadInput();
  void modifyWeight();
  void writeOutput();
  void modifySkimming();

  void registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis);

  void collectKinematicObjects();
  bool goodJetSelection(int);
  bool looseElectronSelection(int);
  bool looseMuonSelection(int);
  bool tightElectronSelection(int);
  bool tightMuonSelection(int);
  bool vetoElectronSelection(int);
  bool vetoMuonSelection(int);

  bool barrelEtaCut(Candidate * lep);
  bool electronCutId(int elIdx, int cat, float sip, bool tight = false, bool mvatight = false);
  bool electronMvaCut(int elIdx, bool tight = false);
  bool electronMvaId(int elIdx, int cat);
  bool isolationCut(int lepIdx, bool tight = false, int pdg = 11);
  bool muonCutId(int lepIdx, int cat, float sip, bool tight = false);
  bool muonMvaId(int lepIdx, int cat);

  int findHadrTau();
  bool fromHadrTau(int);
  bool heppyFake(int);
  bool noLeptonicDecay(string collection, int partIdx);
  void onlyFakes(CandList&, vector<int>&);

  void setCut(std::string, float, std::string, float = 0); 
  void setSidebandRegion();

  bool baseSelection();
  bool genSelection();
  bool mllVetoSelection();
  bool mllLMGVeto(Candidate * cand, Candidate * veto);
  bool mllZVeto(Candidate * cand, Candidate * veto);
  bool skimSelection();
  bool sbSelection();
  bool ssEventSelection();
  bool vetoEventSelection();

  void fillEventPlots(std::string);
  void fillLepPlots(std::string, Candidate*, int);
  void fillLeptonPlots(std::string);
  void fillJetPlots(std::string);
  bool writeSIP(int lepIdx);

  int genMatchCateg(const Candidate*);

  float HT();
  float ptIso(int);
  float closestJetPt(int);
  int eventCharge();

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later)
  enum {kGlobal=0, kLElId, kTElId, kVElId, kLMuId, kTMuId, kVMuId, kJetId, kVetoLepSel, kLMGVetoLepSel, kZVetoLepSel};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  float _valCutHTSB;
  float _valCutMETSB;
  float _valCutHTCondSB;
  float _valCutMETHighSB;
  float _valCutMETLowSB;
  float _valCutNJetsSB;
  float _valCutNBJetsSB;

  std::string _cTypeHTSB;
  std::string _cTypeMETSB;
  std::string _cTypeHTCondSB;
  std::string _cTypeMETHighSB;
  std::string _cTypeMETLowSB;
  std::string _cTypeNJetsSB;
  std::string _cTypeNBJetsSB;

  float _upValCutHTSB;
  float _upValCutMETSB;
  float _upValCutHTCondSB;
  float _upValCutMETHighSB;
  float _upValCutMETLowSB;
  float _upValCutNJetsSB;
  float _upValCutNBJetsSB;
	
  std::vector<int> _lElIdx;
  std::vector<int> _lLepIdx;
  std::vector<int> _lMuIdx;
  std::vector<int> _lntElIdx;
  std::vector<int> _lntLepIdx;
  std::vector<int> _lntMuIdx;
  std::vector<int> _tElIdx;
  std::vector<int> _tLepIdx;
  std::vector<int> _tMuIdx;
  std::vector<int> _vElIdx;
  std::vector<int> _vLepIdx;
  std::vector<int> _vMuIdx;

  int _nLEls;
  int _nLLeps;
  int _nLMus;
  int _nLNTEls;
  int _nLNTLeps;
  int _nLNTMus;
  int _nTEls;
  int _nTLeps;
  int _nTMus;
  int _nVEls;
  int _nVLeps;
  int _nVMus;
  int _nJets;

  CandList _lEls;
  CandList _lLeps;
  CandList _lMus;
  CandList _lntEls;
  CandList _lntLeps;
  CandList _lntMus;
  CandList _tEls;
  CandList _tLeps;
  CandList _tMus;
  CandList _vEls;
  CandList _vLeps;
  CandList _vMus;
  CandList _jets;
  Candidate * _met;

  Candidate * _first;
  Candidate * _second;
  int _lep_idx1;
  int _lep_idx2; 
 
  float _HT;


  string _btag;
  string _etabin;
  string _fakes;
  string _lepflav;
  string _lepid;
  string _lepiso;
  string _leppt;
  string _leptl;
  string _SB;

};


#endif
