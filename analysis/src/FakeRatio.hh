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

#ifndef FakeRatio_HH
#define FakeRatio_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class FakeRatio: public MPAF {

public:


  // Member Functions

  FakeRatio(std::string);
  virtual ~FakeRatio();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();
  void modifySkimming();

  void divideFRMap(string kr, string postpend);
  void divideFRMaps();
  void registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis);

  void collectKinematicObjects();
  bool goodJetSelection(int);
  bool denominatorElectronSelection(int);
  bool denominatorMuonSelection(int);
  bool numeratorElectronSelection(int);
  bool numeratorMuonSelection(int);
  bool vetoElectronSelection(int);
  bool vetoMuonSelection(int);

  void setCut(std::string, float, std::string, float = 0);
  void setMeasurementRegion();

  bool mrSelection();
  bool skimSelection();

  void fillEventPlots();
  void fillLepPlots(std::string, Candidate*, int, int = SusyModule::kTight);
  void fillLeptonPlots();
  void fillJetPlots();
  void fillFRMaps(std::string, Candidate*, int, int = SusyModule::kTight);
  void fillFakeRatioMaps();

  float overflowPt(float);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0, kDenEls, kDenMus, kNumEls, kNumMus, kVetEls, kVetMus, kGoodJets};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  float _valCutNBJetsMR;
  std::string _cTypeNBJetsMR;
  float _upValCutNBJetsMR;

  int _nDenEls;
  int _nDenLeps;
  int _nDenMus;
  int _nNumEls;
  int _nNumLeps;
  int _nNumMus;
  int _nVetEls;
  int _nVetLeps;
  int _nVetMus;
  int _nJets;

  CandList _denEls;
  CandList _denLeps;
  CandList _denMus;
  CandList _numEls;
  CandList _numLeps;
  CandList _numMus;
  CandList _vetEls;
  CandList _vetLeps;
  CandList _vetMus;
  CandList _goodJets;

  vector<int> _denElsIdx;
  vector<int> _denLepsIdx;
  vector<int> _denMusIdx;
  vector<int> _numElsIdx;
  vector<int> _numLepsIdx;
  vector<int> _numMusIdx;
  vector<int> _vetElsIdx;
  vector<int> _vetLepsIdx;
  vector<int> _vetMusIdx;

  Candidate * _met;
  float _HT;

  string _bvar;
  string _nvert;
  string _leps;
  string _jets;
  string _mets;

  SusyModule* _susyMod;

};


#endif
