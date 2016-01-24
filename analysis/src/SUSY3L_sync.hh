/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Jan Hoss, ETHZ, 12/2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef SUSY3L_sync_HH
#define SUSY3L_sync_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class SUSY3L_sync: public MPAF {

public:
    // Member Functions
    SUSY3L_sync(std::string);
    virtual ~SUSY3L_sync();

private:
    void initialize();

    void run();
    void defineOutput();
    void loadInput();
    void modifyWeight();
    void writeOutput();
    void modifySkimming();
    void collectKinematicObjects();
    
    bool tauSelection(int);
    bool looseLepton(const Candidate* c, int idx, int pdgId);
    bool fakableLepton(const Candidate* c, int idx, int pdgId, bool bypass);
    bool tightLepton(const Candidate* c, int idx, int pdgId);
    
    bool multiLepSelection();
    void advancedSelection(int WF);
    float getTF_SingleFake(int ic);
    float getTF_DoubleFake(int ic);
    float getTF_TripleFake(int ic);
    bool wzCRSelection();
    bool ZMuMuSelection();
    bool ttbarSelection();
    bool ZElElSelection();
    bool ZlSelection();
    bool WlSelection();
    void categorize();
    bool testRegion();
    vector<CandList> build3LCombFake(const CandList tightLeps, vector<unsigned int> idxsT,
		const CandList fakableLeps, vector<unsigned int> idxsL, const CandList fakableLepsPtCorr,
		vector<unsigned int> idxsLPtCorr, int nHardestLepton, float pt_cut_hardest_legs, 
        int nHardLeptons, float pt_cut_hard_legs, bool onZ,
        vector< vector<int> >& combIdxs, vector<int>& combType ); 
    void setBaselineRegion();
    void setSignalRegion();
    void setSelLine(string str);
    float getFR(Candidate* cand, int idx);
    void setCut(std::string, float, std::string, float = 0);
    bool hardLeg(CandList leptons, int n_hardestLeg, float cut_hardestLeg, int n_hardLeg, float cut_hardLeg);
    void fillHistos();
    void fillValidationHistos(string reg);
    float getMT2();
    void sortSelectedLeps(CandList leps, std::vector<unsigned int> lepsIdx);
    float lowestOssfMll(CandList leps);
    void registerTriggerVars();
    void readCSCevents();
    void readEESCevents();
    void readFilteredEvents(map< std::pair<int,std::pair<int,unsigned long int> > , unsigned int >&, vector<string>);

    bool passHLTbit();
    
    bool passNoiseFilters();
    bool passCSCfilter();
    bool passEESCfilter(); 
    
    void loadScanHistogram();
    bool checkMassBenchmark();

    float M_T(float, float, float, float);
    float DeltaPhi(float, float);
    float MT2(Candidate*, Candidate*, Candidate*, double);

    bool _selectMuons;
    bool _selectElectrons;
    bool _selectTaus;
    int _onZ; 
    bool _doPlots;
    bool _doValidationPlots;
    int _closureByFlavor;
    bool _exactlyThreeLep;
    bool _runSystematics;
    string _BR;
    string _SR;
    string _FR;
    int _fastSim;
    bool _debug;


private:

    //counter categories, 0 is ALWAYS global (even if not specified later)
  enum {kGlobal=0,
	
    kOnZSR001, kOnZSR002, kOnZSR003, kOnZSR004, kOnZSR005, kOnZSR006, kOnZSR007, kOnZSR008,
	kOnZSR009, kOnZSR010, kOnZSR011, kOnZSR012, kOnZSR013, kOnZSR014, kOnZSR015,

	kOffZSR001, kOffZSR002, kOffZSR003, kOffZSR004, kOffZSR005, kOffZSR006, kOffZSR007, kOffZSR008,
	kOffZSR009, kOffZSR010, kOffZSR011, kOffZSR012, kOffZSR013, kOffZSR014, kOffZSR015,
    
	kOnZSR001_Fake, kOnZSR002_Fake, kOnZSR003_Fake, kOnZSR004_Fake, kOnZSR005_Fake, kOnZSR006_Fake, kOnZSR007_Fake, kOnZSR008_Fake,
	kOnZSR009_Fake, kOnZSR010_Fake, kOnZSR011_Fake, kOnZSR012_Fake, kOnZSR013_Fake, kOnZSR014_Fake, kOnZSR015_Fake,
	
	kOffZSR001_Fake, kOffZSR002_Fake, kOffZSR003_Fake, kOffZSR004_Fake, kOffZSR005_Fake, kOffZSR006_Fake, kOffZSR007_Fake, kOffZSR008_Fake,
	kOffZSR009_Fake, kOffZSR010_Fake, kOffZSR011_Fake, kOffZSR012_Fake, kOffZSR013_Fake, kOffZSR014_Fake, kOffZSR015_Fake,

    kOnZBaseline, kOffZBaseline,

    kOnZBaseline_Fake, kOffZBaseline_Fake,
    
    kGlobal_Fake,
    
    kWZCR
    };

    enum {kIsSingleFake=0,kIsDoubleFake,kIsTripleFake };
    
    SusyModule* _susyMod;

    //cut variables
    float _valCutLepMultiplicityBR;
    float _pt_cut_hard_legs;
    int   _nHardLeptons;
    float _pt_cut_hardest_legs;
    int   _nHardestLeptons;
    float _M_T_3rdLep_MET_cut;
    float _multiIsoWP[5][3];
    float _valCutNJetsBR;
    float _valCutNBJetsBR;
    float _ZMassWindow;
    float _lowMllCut;
    float _valCutHTBR;
    float _valCutMETBR;
    float _valCutMllBR;
    float _valCutMT2BR;

    std::vector<std::string> _hltLines;
    
    std::string _cTypeLepMultiplicityBR;
    std::string _cTypeNJetsBR;
    std::string _cTypeNBJetsBR;
    std::string _cTypeHTBR;
    std::string _cTypeMETBR;
    std::string _cTypeMllBR;
    std::string _cTypeMT2BR;
    
    float _upValCutLepMultiplicityBR;
    float _upValCutNJetsBR;
    float _upValCutNBJetsBR;
    float _upValCutHTBR;
    float _upValCutMETBR;
    float _upValCutMllBR;
    float _upValCutMT2BR;
    
    //vectors for electron, muon, and tau candidates
    std::vector<int> _tauIdx;
    std::vector<unsigned int> _lepsIdx;
    std::vector<unsigned int> _looseLepsIdx;
    std::vector<unsigned int> _looseLepsPtCutIdx;
    std::vector<unsigned int> _looseLepsPtCorrCutIdx;
    std::vector<unsigned int> _fakableLepsIdx;
    std::vector<unsigned int> _fakableLepsPtCutIdx;
    std::vector<unsigned int> _fakableNotTightLepsPtCutIdx;
    std::vector<unsigned int> _fakableNotTightLepsPtCorrCutIdx;
    std::vector<unsigned int> _tightLepsPtCutIdx;
    std::vector<unsigned int> _tightLepsPtCutMllCutIdx;
    std::vector<std::pair<std::string, unsigned int> >  _jetsIdx;
    std::vector<std::pair<std::string, unsigned int> >  _bJetsIdx;
    std::vector<std::pair<std::string, unsigned int> >  _lepJetsIdx;

    //length of candiate vectors
    int _nEls;
    int _nMus;
    float _nTaus;
    float _nJets;
    float _nBJets;
    float _nleps;
    std::map<std::string,float*> _val;

    //list of object candidates
    CandList _els;
    CandList _mus;
    CandList _taus;
    CandList _jets;
    CandList _bJets;
    CandList _leps;
    CandList _looseLeps;
    CandList _looseLepsPtCut;
    CandList _looseLepsPtCorrCut;
    CandList _fakableLeps;
    CandList _fakableLepsPtCut;
    CandList _fakableNotTightLepsPtCut;
    CandList _fakableNotTightLepsPtCorrCut;
    CandList _tightLepsPtCut;
    CandList _tightLepsPtCutMllCut;
    CandList _lepJets;

    Candidate* _met;
    Candidate* _Z;
    CandList _zPair;
    Candidate* _l1Cand;
    Candidate* _l2Cand;
    
  	bool _isOnZ;

    float _HT;
    float _MT2;
    float _deltaR;
    float _lowOSSFMll;
    float _metPt;
    float _MT;
    float _zMass;
    float _zPt;
    int _idxL1;
    int _idxL2;
 
    float _btagW;
  
    std::map<std::string, std::vector<std::vector<std::vector<std::string> > > > _sels;
   
    float _jetThreshold;
    float _bjetThreshold;
   
    //HLT
    vector<string> _vTR_lines;
    
    vector<string> _categs;
    bool _categorization;
    bool _isMultiLep = false;
    bool _isFake = false;
    int _flavor = -1;

    //for fake background
    vector<CandList> _combList;
    vector< vector<int> > _combIdxs;
    vector<int> _combType;

    //for event filter
    map< std::pair<int,std::pair<int,unsigned long int> > , unsigned int > _filteredCSCEvents;
    map< std::pair<int,std::pair<int,unsigned long int> > , unsigned int > _filteredEESCEvents;

  	//scan
  	TH3D* _hScanWeight;
  	int _nProcEvtScan;

};

#endif
