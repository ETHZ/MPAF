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

#ifndef MPAF_HH
#define MPAF_HH

#include "TFile.h"
#include "TH1I.h"
#include "TTree.h"
#include "TStopwatch.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <map>
#include <time.h>
#include <boost/timer.hpp>
#include <boost/progress.hpp>

#include "analysis/core/VarClass.hh"
#include "analysis/utils/CustomTypes.cc"
#include "analysis/utils/Debug.cc"
#include "analysis/utils/KineUtils.hh"
#include "analysis/utils/Parser.hh"
#include "analysis/utils/Tools.hh"
#include "analysis/utils/SystemUtils.hh"
#include "analysis/utils/Verbose.hh"
#include "analysis/utils/mt2_bisect.h"


#include "analysis/tools/Candidate.hh"
#include "analysis/tools/CandFwd.hh"


#include "tools/src/DataBaseManager.hh"
#include "tools/src/Dataset.hh"
#include "tools/src/HistoManager.hh"
#include "tools/src/AnaUtils.hh"



class MPAF {


  // Public Non-Template Methods

public:

  MPAF();
  MPAF(string cfg);
  virtual ~MPAF();

  void analyze();

  // Protected Non-Template Methods

protected:

  void startExecution(std::string);
  
  // varclass functions
  void fill(string var, float valx, float weight = 1.);
  void fill(string var, float valx, float valy, float weight);
  void fillUnc(string var, string unc, float val, float weight, string dir = "");
  void fillUnc(string var, string unc, float val, float weight, float wup, float wdo);

  // database functions
  void loadDb(string key, string dbfile, string hname = "");
  float getDBVal(string db, float v1 = -100000, float v2 = -100000, float v3 = -100000, 
		 float v4 = -100000, float v5 = -100000, float v6 = -100000, 
		 float v7 = -100000, float v8 = -100000, float v9 = -100000, 
		 float v10 = -100000);
  float getDBErrL(string db, float v1 = -100000, float v2 = -100000, float v3 = -100000,
		  float v4 = -100000, float v5 = -100000, float v6 = -100000,
		  float v7 = -100000, float v8 = -100000, float v9 = -100000, 
		  float v10 = -100000);
  float getDBErrH(string db, float v1 = -100000, float v2 = -100000, float v3 = -100000,
		  float v4 = -100000, float v5 = -100000, float v6 = -100000,
		  float v7 = -100000, float v8 = -100000, float v9 = -100000,
		  float v10 = -100000);
 
  string getCfgVarS(string n, string def);
  int getCfgVarI(string n, int def);
  float getCfgVarF(string n, float def);

  //counters and selection functions
  template <typename T> inline
  bool makeCut(T value, T valcut, string type, string cName, T seccut=0, int eCateg = AUtils::kGlobal) {
    return _au -> makeCut<T>(value, valcut, type, _inds
			     , cName, _weight, seccut, eCateg+_offsetWF, false);
  };
  bool makeCut(bool decision, string cName, string type = "=", int eCateg = AUtils::kGlobal);
  void counter(string cName, int eCateg = AUtils::kGlobal);

  //workflows
  void addWorkflow(int wfid, string wfName);
  int getCurrentWorkflow() {return _curWF;};
  void setWorkflow(int wf);
  void setMultiWorkflow(vector<int> wf);
  
  // virtual functions for the classes
  virtual void defineOutput()=0;
  virtual void modifyWeight()=0;
  virtual void run()=0;
  virtual void writeOutput()=0;
  
  //skimming functions
  virtual void modifySkimming()=0;
  template < typename T > void addSkimBranch(string name,T* val) {
    _skimTree->Branch( name.c_str(), val );
  };
  void fillSkimTree() { if(_skim) _skimTree->Fill();};

  //datasets
  const Dataset* getCurrentDS() const {return _datasets[_inds];};

  //uncertainties
  void addSystSource(string name, int dir, string type, vector<string> modVar, 
		     float val, bool wUnc=false);
  void addSystSource(string name, int dir, string type, vector<string> modVar,
		     string db, string hname, bool wUnc=false);
  void addWSystSource(string name, int dir, string type, float val);
  void addWSystSource(string name, int dir, string type, string db, string hname);
  void addManualSystSource(string name, int dir);

  bool isInUncProc() {return _uncId;};
  string getUncName() { return _unc;};
  int getUncDir() { return _uDir;};

  // Private Non-Template Methods
	
private:

  void loadConfigurationFile(std::string);
  void setConfigName(std::string);
  
  void initialize();

  void initSkimming();
  void finalizeSkimming();

  void internalWriteOutput();
  void writeSummary();

  void addWorkflowHistos();

  
  void applySystVar(SystST s);
  //MM fixme
  // float applySystDBVar(SystST s, string db, float v1, float v2, float v3, float v4,
  // 		       float v5,float v6,float v7,float v8,float v9, float v10);


  // Protected Members

protected:

  bool _isData;
  TTree * _RootTree;
  VarClass * _vc;
  DataBaseManager* _dbm;
  HistoManager* _hm;
  AnaUtils* _au;

  bool _skim;

  MIPar _inputVars;

  size_t _ie;
  std::string _sampleName;
  float _weight;

  std::string _cfgName;
 
  // CH: FakeRatio and FRinSitu need dataset access for reweighting...
  unsigned int _numDS;
  std::vector <Dataset*> _datasets;


  // Private Members
 
private:

  vector<unsigned int> _nEvtsDs;
  vector<unsigned int> _nEvts; 
  unsigned int _nEvtMax; 
  unsigned int _nSkip; 
  bool _summary;

  int _inds;

  std::map<std::string, std::string> _sampleOption;
  
  //skimming variables
  TFile* _oFile;
  TTree* _skimTree;
  TH1I* _hnSkim;
  TH1D* _hnwSkim;


 
  bool _fullSkim;

  // Configuration File Variables
  std::string _inputPath;
  std::string _className;

  std::string _hname;
  std::string _hwgtname;

  //workflows
  int _curWF;
  std::map<int, std::string> _wfNames;
  std::map<int, std::string>::const_iterator _itWF;
  int _offsetWF;

  //uncertainties
  string _unc;
  bool _uncId;
  int _uDir;
  float _wBack;
  vector<string> _uncSrcs;
  vector<int> _uncDirs;
  map<string, bool> _uType;
  
  bool _systVarOnly;
  string _systSource;
  int _systDir;

};


#endif
