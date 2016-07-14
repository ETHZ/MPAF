#ifndef _AnaUtils_
#define _AnaUtils_

#include <assert.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <math.h>
#include <sstream>
#include <iomanip>

#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"

#include "tools/src/StatUtils.hh"
#include "tools/src/SystUtils.hh"
#include "tools/src/Format.cc"
#include "tools/src/Debug.cc"

using namespace std;

namespace AUtils {
  const static int kMC=0;
  const static int kGlobal=0;
  const static int kNominal=1;
};

struct categ{
  int id;
  string name;
  string uncTag;
  bool isUnc;
  bool isWF;
  vector<string> effNames;
};

struct EffST{

  float eff;
  
  map<string,float> systsU;
  map<string,float> systsD;

  // map<string,int> systNameU; 
  // map<string,int> systNameD; 

  float sumw;
  float sumw2;
  float N;

  float sumwTot;
  float sumw2Tot;
  float NTot;
  
};

//typedef map<string, unsigned int> effIdxs

//typedef vector<EffST> eIMap

typedef map<string, EffST> eIMap; //efficiencies for one dataset, one categ
typedef vector<eIMap > eMap; //efficiencies for one categ, all datasets
typedef vector<eMap> multiEMap;//efficiencies for all categs, all datasets
typedef eIMap::iterator itEIMap;
typedef eMap::iterator itEMap;
typedef multiEMap::iterator itMultiEMap;


class AnaUtils {

private:

  //Efficiencies
  multiEMap _effMap;
  itEMap _itEMap;
  itEIMap _itEIMap;
  itMultiEMap _itMEMap;

  //workflows
  int _nWF;
  int _curWF;
  bool _isMultiWF;
  vector<int> _multiWFs;
  std::map<string, int> _offsetUnc;

  //Acceptance
  bool _inAcc;
  bool _useAccForEff;

  bool _invCut;
  bool _skipCut;
  set<string> _nm1Var;
  set<string> _bkgFC;
  
  //internal names...
  vector<string> _dsNames;
  map<int, categ> _categories;
  map<int, categ>::const_iterator _itC;
  //map<int, vector<string> > _effNames; //key=categ
  //map<string, int>::const_iterator _itMSI;
  
  int _kGlobal;
  int _kMC;
  

  string _uncSrc;
  int _uncDir;

  //counters
  bool _disableCounter;
  string _singleCounter;

public:

  enum {kGeneral=0, kMono=1, kMulti=2, kMultiVeto=3};

public:
  
  AnaUtils();
  virtual ~AnaUtils();

  void setUncSrc(string uncSrc, int dir) {
    _uncSrc=uncSrc;
    _uncDir=dir;
  };

  template < typename T > inline
  bool makeCut(T value, T valcut, const string& type, int ids, const string& cName, float w, T valUp, T valDo, T seccut=0, int eCateg=AUtils::kGlobal) {

    bool mean = internalMakeCut<T>( value, valcut, type, ids, cName, w, seccut, eCateg, false);

    bool up=mean,down=mean;
   
    up =  simpleCut<T>( valUp, valcut, type, seccut);
    down =  simpleCut<T>( valDo, valcut, type, seccut);
    
    //setSystematics( ids, cName, _uncSrc, up, down, w);
    
    return mean;
  };

  template < typename T > inline
  bool makeCut( T value, T valcut, const string& type, int ids, const string& cName, float w, T seccut=0, int eCateg=AUtils::kGlobal, bool noRegister=false) {
    return internalMakeCut<T>(value, valcut,type,ids,cName,w,seccut, eCateg, noRegister);
  };

  bool makeCut( bool decision, int ids, const string& cName, float w,const string& type="=", int eCateg=AUtils::kGlobal, bool noRegister=false) {
    return internalMakeCut<bool>( decision, true, type, ids, cName, w, 0, eCateg, noRegister );
  };


  template < typename T > inline
  bool simpleCut( T value, T cut, const string& type, T seccut=0 ) {
    return internalMakeCut<T>( value, cut, type, 0, "dummy", 0, seccut, -1, true );
  };


  bool simpleCut( bool decision, const string& type="=") {
    return internalMakeCut<bool>( decision, true, type, 0, "dummy", 0, 0, -1, true );
  };

  
  const std::string invCut(const string& s);
  bool cbool(bool skip, bool namevar);


  //Efficiencies and yields
  void setEfficiency(int ids, const string& cName, int eCateg, float value, bool acc);
  void setEffFromStat(int ids, const string& cName, int eCateg, float sw, float esw, int ngen);
  void setSystematics( int ids, const string& cName, int iCateg, const string& sName, bool up, bool down, float w);
  void getSystematics(const string& ds, const string& lvl, const string& categ="");
  void getCategSystematics(const string& ds, const string& src, const string& lvl, const string& categ="", const string& vetos="", bool latex=false);
  void getYieldSysts(EffST eST, map<string,float>& rU, map<string,float>& rD,
		       float& totUp, float& totDown, float& central);
  float getYield(int ids, const string& cName, int icat);
  //workflows
  void setWFEfficiencies(int ids, const string& cName, float w, bool acc, const string& uncName="");
  void setWFSystematics(int ids, const string& cName, const string& sName,
			bool up, bool down, float w, const string& uncName="") ;

  void saveNumbers(const string& anName, const string& conName, std::map<string, int> cnts, std::map<string, double> wgtcnts);
  void printNumbers(ostream& o);

  void printTables(const string& categ="global", bool latexOnly = false, bool header = false);

  // =======
// 	vector<string> listFiles(string dir, string files);
  int findElement(vector<string> v, const string& e);
  vector< pair<string, vector<vector<map<string,float> > > > > 
  retrieveNumbers(const string& categ, const string& cname, int mcat, const string& opt="");
  
  vector<vector<vector<float> > > 
  retrieveSystematicNumbers(const string& dss, const string& src, const string& lvl,
			    const string& categ, const string& vetos);

  bool getDataCardLines(map<string,string>& lines, 
			shapeM& shapes, 
			vector<string> dsNames,
			const string& sigName,	const string& categ, const string& cname, int bin,
			map<string,vector<string> > intNuisPars,
			map<string,bool > nuisParExt,
			map<string,string> nuisParScheme,
			map<string,vector<string> > nuisParsVals);
 

  //void drawNumbers();
  
  void setSkipCut(vector<string> var, bool invCut); 

  void setDDCuts(vector<string> ddCuts);

  void setCounterOption(bool disableCounter, string singleCounter);

  void reset();

  void init();

  static hObs cloneHObs(const hObs* o1);

  void addDataset(const string& dsName); 
  void addCategory(int iCateg, const string& nCateg); 
  void addCategory(int iCateg, const string& nCateg, const string& uncTag);
  void addWorkflow(int iCateg, const string& nCateg); 
  void addAutoWorkflow(const string& eCateg);
  void setCurrentWorkflow(int wf);
  void setMultiWorkflow(vector<int> wfs);
  //int getUncWorkflow(string wf);

  int getCategId(const string& categ);
  int getCategUniqueId(const string& categ, const string& uncTag);
  int getNCateg() {return _categories.size(); };
  vector<string> getCategories();
  vector<string> getSelections(int ids, int icat);
  bool isUncCateg(int catId);

  static vector<string> parse(const string& str, const string& d);

private:

  template < typename T > inline
  bool internalMakeCut( T value, T valcut, const string& type, int ids, const string& cName, float w, T seccut=0, int eCateg=AUtils::kGlobal, bool noRegister=false) {

    bool accept;

    if(!cbool(_skipCut, _nm1Var.find(cName)!=_nm1Var.end() ) )
      { return true; }
    // if( !cbool( _invCut, _nm1Var.find(cName)!=_nm1Var.end() ) ) {
    //   type = invCut(type); }
   
    if(type=="<") {
      accept = (value < valcut);
    }
    else if(type=="<=") {
      accept = (value <= valcut);
    }
    else if( type==">") {
      accept = (value > valcut);
    }
    else if( type==">=") {
      accept = (value >= valcut);
    }
    else if( type=="=") {
      accept = (value == valcut);
    }
    else if(type=="!=") {
      accept = (value != valcut);
    }
    else if(type=="[]") {
      accept = (value >= valcut && value<= seccut );
    }
    else if(type=="][") {
      accept = (value > valcut && value< seccut );
    }
    else if(type=="]]") {
      accept = (value > valcut && value <= seccut );
    }
    else if(type=="[[") {
      accept = (value >= valcut && value < seccut );
    }
    else if(type=="[!]") {
      accept = !(value >= valcut && value <= seccut );
    }
    else if(type=="[![") {
      accept = !(value >= valcut && value < seccut );
    }
    else if(type=="]!]") {
      accept = !(value > valcut && value <= seccut );
    }
    else if(type=="]![") {
      accept = !(value > valcut && value < seccut );
    }

    else {
      accept =false; //cout<<" Warning cut :"<<type<<":"<<" for selection "<<cName<<endl;
    }  
    
    ids+=1;//0 booked for MC
    
    if(_disableCounter || (_singleCounter.size()!=0 && _singleCounter!=cName) ) 
      return accept;
    
    if(!noRegister || _dsNames[ids].find("GHO")!=(size_t)-1 ) {
      if(_uncSrc=="") {
    	if(eCateg!=_kGlobal) { //eff categories
	  setEfficiency(ids, cName, eCateg, w, accept);
    	}
    	else {
	  if( (_nWF==1 || _curWF!=-100) && !_isMultiWF) { //single workflow
	    setEfficiency(ids, cName, (_curWF==-100)?eCateg:_curWF , w, accept);
    	  }
    	  else {//multiple workflows
	    setWFEfficiencies(ids, cName, w, accept);
    	  }
    	}
      }
      else {
	string uncName="Unc"+_uncSrc+((_uncDir==SystUtils::kUp)?"Up":"Do");
    	//separated workflow for uncertainty
	if( (_nWF==1 || _curWF!=-100) && !_isMultiWF) { //single workflow
	  setEfficiency(ids, cName, _curWF+_offsetUnc[uncName], w, accept);
	  //and systematic uncertainties
	  if(_uncDir==SystUtils::kUp)
	    setSystematics( ids, cName, _curWF+_offsetUnc[uncName], _uncSrc,accept,false, w);
	  else if(_uncDir==SystUtils::kDown)
	    setSystematics( ids, cName, _curWF+_offsetUnc[uncName], _uncSrc,false,accept, w);
	}
	else {//multiple workflows
	 
	  setWFEfficiencies(ids, cName, w, accept, uncName  );
	  if(_uncDir==SystUtils::kUp) {
	    setWFSystematics( ids, cName,_uncSrc,accept,false, w, uncName);
	  }
	  else if(_uncDir==SystUtils::kDown) {
	    setWFSystematics( ids, cName,_uncSrc,false,accept, w, uncName);
	  }
	}

      } 
    }
    if( _bkgFC.find(cName)!=_bkgFC.end() ) {
      accept=true;
    }  
    return accept;
  };


  void setNumbers(int ids,const string& cName, int eCateg,float w, bool acc);
  void setNumFromStat(int ids,const string& cName, int iCateg, float sw, float esw, int ngen);

  vector<string> prepareDSNames(bool wMC, vector<int>& idxs);
  
  void internalAddCategory(int iCateg, const string& nCateg, const string& unctag, bool isWF); 


  ClassDef(AnaUtils,0)
  
};

#endif
