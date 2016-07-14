#ifndef SSDL2015_HH
#define SSDL2015_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"
#include "analysis/utils/Tools.hh"

#include "TH3D.h"

class SSDL2015: public MPAF {

public:

  // Member Functions

  SSDL2015(std::string);
  virtual ~SSDL2015();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();

  //============================
  bool noIsoSel();
  bool oneIsoSel();
  bool twoIsoSel();
  void getFRProb();
  void getFRProb(int flag, float fr);
  std::vector<float> getFRs();
  float getProbAtLeastNIso(CandList fObjs, vector<unsigned int> idxs, int nIso);
  bool genMatchedMisCharge();
  int genMatchCateg(const Candidate* cand);
  bool genMatchedToFake(int id);

  bool passGenSelection();

  bool checkMassBenchmark();
  void loadScanHistogram();

  float getFR(Candidate* cand, int idx);
  
  void chargeFlipProb();

  TVector2 varyMET();
  Candidate* varyJetLepAware(Candidate* lep, int idx);

  //============================
  void retrieveObjects();
  bool ssLeptonSelection();
  void selectLeptons();

  //==============================
  void wzCRSelection();
  void setSignalRegions();
  void setSelLine(string str);
  //void setCut(string var, float valCut, string cType, float upValCut=0);
  
  //=============================
  //advanced fast selection
  bool testRegion();
  void categorize();
  
  int getMergedSR(int wf);


  bool passCERNSelection();
  bool looseLepton(const Candidate*c, int idx, int pdgId);
  bool tightLepton(const Candidate*c, int idx, int pdgId);
  bool fakableLepton(const Candidate*c, int idx, int pdgId, bool bypass);
  
  bool hltSelection();
  bool passHLT(std::string id);
  bool passHLTbit();
  
  bool passNoiseFilters();
  bool passCSCfilter();
  bool passEESCfilter();

  void advancedSelection(int WF);

  void dumpEvents();
  void skimTrees();

  //==============================
  // Validation regions
  bool ttbarSelection();
  bool ZMuMuSelection();
  bool ZEESelection();
  bool WlSelection(); 
  //  bool WOSlSelection(){return false;};
  bool ZlSelection();
  
  void fillhistos();
  void fillValidationHistos(std::string reg);

  bool checkDoubleCount();

  void registerTriggerVars();
  void readCSCevents();
  void readEESCevents();
  void readFilteredEvents(map< std::pair<int,std::pair<int,unsigned long int> > , unsigned int >&, vector<string>);
  
private: 

  enum {kIsOS=0,kIsFake, kIsDFake};

  //counter categories, 0 is ALWAYS global (even if not specified later
  //enum {kGlobal=0,kLowMETMT,kGenFake,kGenMisCharge,kOneIso,kNoIso, kSelId};
  enum {kGlobal=0,
	
	kSR1A, kSR2A, kSR3A, kSR4A, kSR5A, kSR6A, kSR7A, kSR8A,
	kSR9A, kSR10A, kSR11A, kSR12A, kSR13A, kSR14A, kSR15A, kSR16A,
	kSR17A, kSR18A, kSR19A, kSR20A, kSR21A, kSR22A, kSR23A, kSR24A,
	kSR25A, kSR26A, kSR27A, kSR28A, kSR29A, kSR30A, kSR31A, kSR32A,
	kSR33A,

	kSR1B, kSR2B, kSR3B, kSR4B, kSR5B, kSR6B, kSR7B, kSR8B,
	kSR9B, kSR10B, kSR11B, kSR12B, kSR13B, kSR14B, kSR15B, kSR16B,
	kSR17B, kSR18B, kSR19B, kSR20B, kSR21B, kSR22B, kSR23B, kSR24B,
	kSR25B, kSR26B, kSR27B,

	kSR1C, kSR2C, kSR3C, kSR4C, kSR5C, kSR6C, kSR7C, kSR8C,
    
	//kBR0H, kBR0M, kBR0L,
	kBR00H, kBR00M, kBR00L,
	kBR10H, kBR10M, kBR10L,
	kBR20H, kBR20M, kBR20L,
	kBR30H, kBR30M, kBR30L,
	
	kSR1A_Fake, kSR2A_Fake, kSR3A_Fake, kSR4A_Fake, kSR5A_Fake, kSR6A_Fake, kSR7A_Fake, kSR8A_Fake,
	kSR9A_Fake, kSR10A_Fake, kSR11A_Fake, kSR12A_Fake, kSR13A_Fake, kSR14A_Fake, kSR15A_Fake, kSR16A_Fake,
	kSR17A_Fake, kSR18A_Fake, kSR19A_Fake, kSR20A_Fake, kSR21A_Fake, kSR22A_Fake, kSR23A_Fake, kSR24A_Fake,
	kSR25A_Fake, kSR26A_Fake, kSR27A_Fake, kSR28A_Fake, kSR29A_Fake, kSR30A_Fake, kSR31A_Fake, kSR32A_Fake,  kSR33A_Fake,

	kSR1B_Fake, kSR2B_Fake, kSR3B_Fake, kSR4B_Fake, kSR5B_Fake, kSR6B_Fake, kSR7B_Fake, kSR8B_Fake,
	kSR9B_Fake, kSR10B_Fake, kSR11B_Fake, kSR12B_Fake, kSR13B_Fake, kSR14B_Fake, kSR15B_Fake, kSR16B_Fake,
	kSR17B_Fake, kSR18B_Fake, kSR19B_Fake, kSR20B_Fake, kSR21B_Fake, kSR22B_Fake, kSR23B_Fake, kSR24B_Fake,
	kSR25B_Fake, kSR26B_Fake,  kSR27B_Fake,

	kSR1C_Fake, kSR2C_Fake, kSR3C_Fake, kSR4C_Fake, kSR5C_Fake, kSR6C_Fake, kSR7C_Fake, kSR8C_Fake,

	
	kBR00H_Fake, kBR00M_Fake, kBR00L_Fake,
	kBR10H_Fake, kBR10M_Fake, kBR10L_Fake,
	kBR20H_Fake, kBR20M_Fake, kBR20L_Fake,
	kBR30H_Fake, kBR30M_Fake, kBR30L_Fake,


	
	kSR1A_mId, kSR2A_mId, kSR3A_mId, kSR4A_mId, kSR5A_mId, kSR6A_mId, kSR7A_mId, kSR8A_mId,
	kSR9A_mId, kSR10A_mId, kSR11A_mId, kSR12A_mId, kSR13A_mId, kSR14A_mId, kSR15A_mId, kSR16A_mId,
	kSR17A_mId, kSR18A_mId, kSR19A_mId, kSR20A_mId, kSR21A_mId, kSR22A_mId, kSR23A_mId, kSR24A_mId,
	kSR25A_mId, kSR26A_mId, kSR27A_mId, kSR28A_mId, kSR29A_mId, kSR30A_mId, kSR31A_mId, kSR32A_mId, kSR33A_mId,

	kSR1B_mId, kSR2B_mId, kSR3B_mId, kSR4B_mId, kSR5B_mId, kSR6B_mId, kSR7B_mId, kSR8B_mId,
	kSR9B_mId, kSR10B_mId, kSR11B_mId, kSR12B_mId, kSR13B_mId, kSR14B_mId, kSR15B_mId, kSR16B_mId,
	kSR17B_mId, kSR18B_mId, kSR19B_mId, kSR20B_mId, kSR21B_mId, kSR22B_mId, kSR23B_mId, kSR24B_mId,
	kSR25B_mId, kSR26B_mId,  kSR27B_mId,

	kSR1C_mId, kSR2C_mId, kSR3C_mId, kSR4C_mId, kSR5C_mId, kSR6C_mId, kSR7C_mId, kSR8C_mId,

	
	kBR00H_mId, kBR00M_mId, kBR00L_mId,
	kBR10H_mId, kBR10M_mId, kBR10L_mId,
	kBR20H_mId, kBR20M_mId, kBR20L_mId,
	kBR30H_mId, kBR30M_mId, kBR30L_mId,

	kGlobalFake,
	kGlobalmId,
	
	kWZCR
  };

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};
  // enum {kLoose=0,kTight,kVTight,kHTight,kNWPs};
  
  SusyModule* _susyMod;
  
  Candidate* _met;
  
  std::map<std::string,float*> _val;
  float _nBJets;
  float _mTmin;
  float _metPt;
  float _nJets;
  float _HT;

  int _flav;
  
  //MM ugly
  std::map<std::string, std::vector<std::vector<std::vector<std::string> > > > _sels;

  //HLT
  bool _hltDLHT;
  string _hltBit;

  vector<string> _vTR_lines_non_ee;
  vector<string> _vTR_lines_non_em;
  vector<string> _vTR_lines_non_mm;
  vector<string> _vTR_lines_iso_ee;
  vector<string> _vTR_lines_iso_em;
  vector<string> _vTR_lines_iso_mm;

  //charge misId
  bool _isOS;

  //fakes
  bool _isFake;
  bool _dFake;
  int _idxFake;

  CandList _looseLeps;
  std::vector<unsigned int>  _looseLepsIdx;

  CandList _looseLeps10;
  std::vector<unsigned int>  _looseLeps10Idx;

  CandList _looseLepsPtCut;
  std::vector<unsigned int>  _looseLepsPtCutIdx;

  // CandList _looseLepsVeto;
  // std::vector<unsigned int>  _looseLepsVetoIdx;

  CandList _looseLepsPtCutVeto;
  std::vector<unsigned int>  _looseLepsPtCutVetoIdx;

  CandList _looseLepsPtCorrCut;
  std::vector<unsigned int>  _looseLepsPtCorrCutIdx;
 
 CandList _looseLepsPtCorrCutVeto;
  std::vector<unsigned int>  _looseLepsPtCorrCutVetoIdx;


  CandList _jetCleanLeps10;
  std::vector<unsigned int>  _jetCleanLeps10Idx;

  CandList _fakableLepsPtCutVeto;
  std::vector<unsigned int>  _fakableLepsPtCutVetoIdx;
  
  CandList _tightLepsPtCut;
  std::vector<unsigned int>  _tightLepsPtCutIdx;

  CandList _tightLepsPtCutVeto;
  std::vector<unsigned int>  _tightLepsPtCutVetoIdx;

  CandList _tightLepsOSPtCut;
  std::vector<unsigned int>  _tightLepsOSPtCutIdx;

  CandList _allJets;
  std::vector<std::pair<std::string, unsigned int> >  _allJetsIdx;

  CandList _jets;
  std::vector<std::pair<std::string, unsigned int> >  _jetsIdx;
  
  CandList _bJets;
  std::vector<std::pair<std::string, unsigned int> >  _bJetsIdx;


  CandList _lepJets;
  std::vector<std::pair<std::string, unsigned int> >  _lepJetsIdx;
  
  unsigned int _nLooseLeps;
 

  int _nIso;
  int _nSelPair2Iso;
  int _nSelPair1Iso;
  int _nSelPair0Iso;

  Candidate * _l1Cand;
  Candidate * _l2Cand;
  int _idxL1;
  int _idxL2; 
 

  string _lepflav;
  string _leppt;
  string _leptl;
  string _SR;
  string _FR;
  int _LHESYS;
  int _fastSim;

  int _fakeEl;
  int _fakeMu;
  int _nDFake;
  int _nSFake;
  int _nCharge;
  int _nOther;


  vector<string> _categs;
  bool _categorization;
  bool _mergeSRs;
  bool _DoValidationPlots;

  bool _computeSystematics;
  bool _onlyMainSR;
  bool _dumpEvents;

  int _runMax;

  ofstream* _ofileDump;

  bool _skimmedEvt;

  vector<TVector2> _uncleanJets;
  vector<TVector2> _uncleanDiscJets;
  vector<TVector2> _uncleanFwdJets;

  float _btagW;

  //background pairs===============
  vector<CandList> _auxPairs;
  vector<int> _auxFlags;
  vector<vector<int> > _auxIdxs;

  // vector<unsigned int> _events;
  // void fillEvents();

  //double counting====
  map< std::pair<int,std::pair<int,unsigned long int> > , std::pair<string,int> > _events;
  map< std::pair<int,std::pair<int,unsigned long int> > , std::pair<string,int> >::iterator _itEvt;

  //CSC events
  map< std::pair<int,std::pair<int,unsigned long int> > , unsigned int > _filteredCSCEvents;
  map< std::pair<int,std::pair<int,unsigned long int> > , unsigned int > _filteredEESCEvents;

  vector<float> _jetLepACorFactor;

  vector<float> _theoryTTV;

  //scan =======
  TH3D* _hScanWeight;
  int _nProcEvtScan;

};



#endif
