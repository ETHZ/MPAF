#ifndef _MPAFDisplay_
#define _MPAFDisplay_

#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <math.h>
#include <sstream>


#include "display/core/AnaConfig.hh"
#include "display/core/DisplayClass.hh"
#include "tools/src/AnaUtils.hh"
#include "tools/src/Dataset.hh"
#include "tools/src/DataBaseManager.hh"
#include "tools/src/Debug.cc"
#include "tools/src/HistoManager.hh"

struct CatId{
  string categ;
  string cname;
  string sname;
  bool useExt;
  string redCateg;
  string ext;
  string uncTag;
  int upVar;
};

struct ValId{
  float yield;
  float eyield;
  int gen;
};


class MPAFDisplay {

  //===== variables =====

private:

  bool _recompute;
  bool _auto;
  bool _histoSet;

  vector<string> _dsNames;

  string _currentObs;

  string _ids; //the current dataset
  int _inds; //the current dataset
  float _w; //the current global weight

  bool _isData;

  HistoManager* _hm;
  DataBaseManager* _dbm;
  AnaUtils* _au;

  //datacard stuff
  std::map<std::string, bool> _isSigDs;
  std::map<std::string, vector<string> > _nuisPars;
  std::map<std::string, vector<string> > _nuisParVals;
  std::map<std::string, string > _nuisParScheme;
  std::map<std::string, vector<string> >::const_iterator _itNp;

  std::map<std::string, bool > _nuisParExt;

  std::map<std::pair<std::string,std::string>, bool > _sfVals;

public:

  AnaConfig anConf;

  DisplayClass dp;

  //===== functions ====

private:

  void reset();
  void configure();


  void setNumbers();
  void setHistograms();

  vector<string> split(const string& s, char delim);
  string findDiff(const string& s1, const string& s2,
		  char delim, size_t& bl, size_t& bh);
  void readStatFile(string filename, int& icat);
  void storeStatNums(const Dataset* ds, float yield, float eyield, int gen,
		     int icat, string cname, string sname, string categ,
		     string uncTag, int upVar, string ext, bool skipNominal=false);
    
  void associateSystUncs();

public:

  MPAFDisplay();
  virtual ~MPAFDisplay();
  
  //void unlockStatus();

  void refresh();

  void prepareDisplay();
  
  void doPlot();

  void setObservables(string v1, string v2="", string v3="",
		      string v4="", string v5="", string v6="");
  void loadAutoBinning(string file);
    

  void getStatistics(string categ="nominal");
  void drawStatistics(string categ="nominal", string cname="", 
		      bool multiScheme=false, bool vetoOpt=false, string optCateg="");

  void addExternalSystUnc(string dsName, string unctag, float Up, float Do,
			  string categ="", string cname="");
  void getDetailSystematics(string categ, string lvl);
  void getCategSystematic(string src, string categ, string lvl, bool latex=false);

  void savePlot(string path, string advname="");
  void producePlots(string path);

  void saveHistos(std::string);

  void getYield(string ds, string lvl);

  void drawEfficiencies(string o1);
  void drawROCcurves(string o1);
  void multiROCcurves();


  void drawRatio(string o1, string o2 );
  void drawResiduals(string o1);
  void drawSignificance(string o1);
  void drawCumulativePlots(string o1);
  void drawDetailSyst(bool cumul);

  void getIntegral(float x1, float x2, float y1=0, float y2=1000000);
  
  void saveDataMCRatio(string fname,string hname);

  //data cards
  void addDataCardSample(string sName, string dsName, float w=1);
  void addDataCardSigSample(string sName, string dsName, float w=1);
  void addNuisanceParameter(string npName, string dss, string scheme,  string vals) ;
  void overwriteNuisanceParameter(string npName, string dss, string vals);
  vector<string> getExternalNuisanceParameters(string sigName);
  void makeSingleDataCard(string sigName, string categ, string cname, string cardName);
  void makeMultiDataCard(string sigName, vector<string> categs, 
			 string cname, string cardname);

  ClassDef(MPAFDisplay,0)

};


#endif
