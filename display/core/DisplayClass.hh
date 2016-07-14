#ifndef _Display_
#define _Display_


#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <set>
#include <math.h>
#include <sstream>
#include <string>

#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TPad.h"
#include "TMath.h"
#include "TROOT.h"
#include "TProfile.h"
#include "TPaveText.h"
#include "TMarker.h"
#include "TPolyLine.h"

#include "tools/src/Debug.cc"
#include "tools/src/Format.cc"
#include "tools/src/StatUtils.hh"
#include "display/core/Renorm.hh"

using namespace std;

class DisplayClass {

private:


  TCanvas* _c;
  TLegend* _leg;
  TLegend* _leg2;
  vector<vector<TPad*> > _pads;


  TCanvas* _cSyst;
  TPad* _padleft;
  TPad* _padright;


  set<string> _normOpts; 

  float _lumi;
  float _energy;

  vector<string> _vars;
  size_t _nvars;
  
  float _wline;

  vector<string> _names;

  map<string, int> _colors;
  map<string, int>::const_iterator _itCol;

  map<string, bool> _ghosts;
  vector<int> _iNs;
  
  //binning
  int _gBin;
  int _gBckBin;
  int _binningSave;

  //temporary plots (used in ratio too)
  TH1* _empty;
  TH1* _hMC;
  TH1* _hData;
  TGraphAsymmErrors* _gData;
  vector<TH1*> _hClones;
  vector<TH1*> _hClonesNoStack;
  vector<TH1*> _hSigClones;
  vector<vector<systM> > _systMUnc;
  vector<systM> _csystM;

  vector<TGraphAsymmErrors*> _mcUncert;

  size_t _nh;
  size_t _nhmc;
  size_t _nhsig;
  size_t _ihd;
  
  //Legend stuff
  vector<vector<vector<float> > > _hCoords;
  int _wpad;
  int _hpad;
  float _xdlim;
  float _ydlim;
  float _xulim;
  float _yulim;
  
  //X and Y binning, internal binning options
  float _xmin;
  float _xmax;
  float _ymin;
  float _ymax;
  bool _userYScale;

  float _xCoordSave[2];

  std::map<std::string, std::vector<float> > _autoBins;
  vector<string> _autoVars;
  
  //titles
  string _xtitle;
  string _ytitle;

  //global Weights
  map<string, float> _gWeights;
  map<string, float> _saveWeights;
  map<string, float>::const_iterator _itW;
  map<string, bool> _absNorm;

  float _datNorm;

  string _fitStr;
  Renorm* _fitNorm;

  //style
  bool _showRatio;
  bool _rmLabel;
  bool _overflow;
  bool _underflow;
  bool _logYScale;
  bool _showGrid;
  bool _noStack;
  bool _addSyst;
  bool _mcSyst;

  bool _sSignal;
  
  int _Xdiv[3];
  int _Ydiv[3];
  
  float _wLine;
  float _mSize;

  // bool _switchRMS;
  // string _errOpt;

  // mc/data boolean
  bool _mcOnly;
  bool _dOnly;
  bool _lockData;
  
  //other flags
  bool _closure;
  bool _nlo_vs_lo;
  bool _fixLeg;

  //uncertainties
  bool _uncDet;
  vector<string> _uncNames;
  bool _mcSystComputed;
  
  bool _comSyst;

  //plot format
  bool _is1D;
  bool _is2D;
  bool _isProf;

  //Misc
  bool _prel;
  bool _cumulative;
  
  vector<string> _cNames;
  
public:

  DisplayClass();
  virtual ~DisplayClass();

  void reset();
  void softReset();
  void refreshHistos();

  void configureDisplay(string YTitle, double rangeY[2], 
			double rangeX[2], bool logYscale,
			int Xdiv[3], int Ydiv[3], 
			int gbin, int bckbin, 
			bool OverFlowBin, bool UnderFlowBin,
			bool ShowDMCRatio, bool ShowGrid,
			bool stacking,
			bool AddSystematics, bool mcStatSyst,
			float MarkerSize, float LineWidth,
			bool sSignal, bool mcOnly,
			bool cmsPrel, bool uncDet=false, bool closure=false, bool nlo_vs_lo=false, bool fixLeg=false); //,bool switchRMS, string errorOpt

  void setObservables(string v1, string v2="", string v3="",
		      string v4="", string v5="", string v6="");

  vector<string> getObservables() { return _vars;};

  void loadHistoDB( );

  void setLumi(float lumi){_lumi=lumi;};
  void setLumiAndEnergy(float lumi, float energy){_lumi=lumi; _energy=energy;};

  void setNormalization(string norm);
  void setFitStr(string str);
  string getFitVar();

  void plotDataMCRatio(string obs, bool removelabel);
  void plotRatio(string var1, string var2, string ds);
 
  void plotDistributions(vector<const hObs*> theObs);
  void ratioObservables(vector<const hObs*> theObs);

  void saveDMCRWeight(string fname, string hname);

  void drawCumulativeHistos(const hObs* theObs);
  void residualData(const hObs* theObs);

  void showSignificance(const hObs* theObs);

  void saveHistos(string hname, const hObs* theObs);
  
  void prepareStatistics( vector<pair<string,vector<vector<map<string,float> > > > > vals, vector<string> dsnames, bool isMultiScheme);
  void drawStatistics( vector<pair<string,vector<vector<map<string,float> > > > > vals, vector<string> dsnames, bool isMultiScheme);
  void drawDetailSystematics(bool cumul);
  void drawStatVsSystematics(vector<vector<vector<float> > > numbers, string src);


  void addText(float x, float y, float s, string text);
  void addLine(float x1, float y1, float x2, float y2, int style, int col, int size);
  
  void getIntegral(float x1, float x2, float y1=0, float y2=1000000);
  void printInteg(float x1, float x2, float y1, float y2);

  void getSystUnc( TGraphAsymmErrors* mcUnc);

  void configure(string dsname, int col, bool isGhost);
  void setWeight(string dsname, float w, bool absNorm=false);
  void initWeights(const hObs* theobs);

  void loadAutoBinning(string filename);
  vector<string> getAutoVars() {return _autoVars;};

  const TCanvas* getCanvas() { return _c;}; 

  void checkData();
  void isNoData();

  void setSystematicsUnc( vector<vector<systM> > systs );
 
  void drawROCCurves(const hObs* theObs);
  void drawEfficiency(const hObs* theObs);
  void compaROCCurves(vector<const hObs*> obss);
  
private:


  vector<vector<TPad*> > preparePads();
  vector<vector<TPad*> > preparePadsWithRatio();
  void preparePadsForSystDetail();
  
  TPolyLine* PolyLineFromGraph(vector<TGraph*> graphs);
  TPolyLine* PolyLineFromGraph(TGraph* graph);
  
  void plotDistribution(const string& htype, const string& type,
			int iobs);
  void drawDistribution();
  void prepareHistograms(const hObs* theobs);
 
  void drawDataMCRatio();
  
  void changeGeVToTeV(TH1*& h,string xtitle, string ytitle, 
		      float xmin, float xmax, float ymin, 
		      float ymax, string htype, bool& xAxTeV,
		      bool& yAxTev);

  void computeSystematics( bool isProf, bool cumul=0);

  void cmsPrel();
  
  //void prepareLegend();
  void adjustLegend(int iobs, bool skipCoords=false);
  void getLegendCoordinate(TH1*h, float& pxd, float& pyd, float& pxu,
			   float& pyu,float& fo, int iobs);
  float graphVal(float x,int ih, int iobs);
  void graphConstraint(size_t ih, int iobs, float& xd, float& xu, float& yd,
		       float& yu,float& f, float dx, float dy);

  ClassDef(DisplayClass,0)  

};

#endif


