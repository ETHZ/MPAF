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

#ifndef FakeRatioStudy_HH
#define FakeRatioStudy_HH

#include "analysis/core/MPAF.hh"

class FakeRatioStudy: public MPAF {

public:


  // Member Functions

  FakeRatioStudy(std::string);
  virtual ~FakeRatioStudy();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();
  void modifySkimming();

  void divideFRMap(string kr, string postpend);
  void divideFRMaps(string kr, string lep);
  void registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis);

  void collectKinematicObjects();
  bool goodJetSelection(int);
  bool looseElectronSelection(int);
  bool looseMuonSelection(int);
  bool tightElectronSelection(int);
  bool tightMuonSelection(int);
  bool vetoElectronSelection(int);
  bool vetoMuonSelection(int);

  bool electronCutId(int elIdx, int cat, float sip, bool tight = false, bool mvatight = false);
  bool electronMvaCut(int elIdx, bool tight = false);
  bool electronMvaId(int elIdx, int cat);
  bool isolationCut(int lepIdx, bool tight = false, int pdg = 13);
  bool muonCutId(int lepIdx, int cat, float sip, bool tight = false);
  bool muonMvaId(int lepIdx, int cat);

  bool bJetMatching(int);
  bool cJetMatching(int);
  int findHadrTau();
  bool fromHadrTau(int lepIdx, bool = false);
  bool heppyFake(int);
  bool jetFake(int);
  bool lightJetMatching(int);
  bool noJetMatching(int);
  bool noLeptonicDecay(string collection, int partIdx);
  void onlyFakes(CandList&, std::vector<int>&, bool = false);

  void setCut(std::string, float, std::string, float = 0); 
  void setMeasurementRegion();

  bool genMRSelection();
  bool mrSelection();
  bool skimSelection();
  bool syncSelection();

  void fillAvgJetPtRatio(int);
  void fillEventPlots(std::string);
  void fillLepPlots(std::string, Candidate*, int);
  void fillLeptonPlots(std::string);
  void fillJetPlots(std::string);
  void fillFRMaps(std::string, Candidate*, int);
  void fillFakeRatioMaps(std::string);
  void fillFakeRatioPlots(std::string);

  float HT();
  float ptIso(int);
  float ptMIso(int);
  float ptMIso1(int);
  float ptMIso2(int);
  int closestJet(int);
  float closestJetPt(int);
  int eventCharge();
  float overflowPt(float);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0, kTElId, kLElId, kVElId, kTMuId, kLMuId, kVMuId, kJetId};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  float _valCutNBJetsMR;
  std::string _cTypeNBJetsMR;
  float _upValCutNBJetsMR;

  int _nLEls;
  int _nLNTEls;
  int _nTEls;
  int _nVEls;
  int _nLLeps;
  int _nLNTLeps;
  int _nTLeps;
  int _nVLeps;
  int _nLMus;
  int _nLNTMus;
  int _nTMus;
  int _nVMus;
  int _nJets;

  CandList _lEls;
  CandList _lntEls;
  CandList _tEls;
  CandList _vEls;
  CandList _lMus;
  CandList _lntMus;
  CandList _tMus;
  CandList _vMus;
  CandList _lLeps;
  CandList _lntLeps;
  CandList _tLeps;
  CandList _vLeps;
  CandList _jets;

  vector<int> _lElIdx;
  vector<int> _lntElIdx;
  vector<int> _tElIdx;
  vector<int> _vElIdx;
  vector<int> _lLepIdx;
  vector<int> _lntLepIdx;
  vector<int> _tLepIdx;
  vector<int> _vLepIdx;
  vector<int> _lMuIdx;
  vector<int> _lntMuIdx;
  vector<int> _tMuIdx;
  vector<int> _vMuIdx;


  Candidate * _met; 
  float _HT;

  vector<float> _alpha;

  bool _mvaId;
  string _bvar;

  string _lepflav;
  string _lepiso;  
  string _mva;
  string _btag;
  string _MR; 
  string _fakes;
  string _xpol;
  string _htbin;
  string _etabin;
  string _lepptcut;


};


#endif
