/*****************************************************************************
******************************************************************************
****************************************************************************** 
**                                                                          ** 
** The Multi-Purpose Analysis Framework                                     ** 
**                                                                          ** 
** Constantin Heidegger, Matthieu Marionneau                                ** 
**                                                                          ** 
****************************************************************************** 
****************************************************************************** 
*****************************************************************************/ 

#ifndef _HistoMan_
#define _HistoMan_

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>

#include "TError.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "tools/src/Format.cc"
#include "tools/src/HistoUtils.hh"


using namespace std;



class HistoManager {

private:
  
  //histograms
  map< string, hObs > _variables;
  map< string, hObs >::iterator _itVar; 
  map< string, hObs >::const_iterator _cItVar; 
  
  vector<string> _dsNames;
  size_t _nds;
  
  string _hname;
  
  //==============================================
  //Functions

public:

  //cosntructor & destructor

  HistoManager();
  virtual ~HistoManager();

  //initilaization
  void configAnalysis(vector<string> datasets);
  void addDataset(string dsname); 
 
  //reset
  void reset();
  void refresh();

  //Histogram access and booking
  
  void addVariable(string var, int nBin, float min, float max, 
		   string Xleg, bool isglb=true, bool prof=false, string type="m");
  void addVariable(string var, int nBin, vector<float> bins,
		   string Xleg, bool isglb=true, bool prof=false, string type="m");
  void addVariable(string var, int nBinX, float minX, float maxX,
		   int nBinY, float minY,
		   float maxY, string Xleg,string Yleg,
		   bool isglb=true, bool prof=false, string type="m");
  void addVariable(string var, int nBinX, vector<float> binsX, int nBinY,
		   vector<float> binsY,
		   string Xleg,string Yleg, bool isglb=true, bool prof=false, string type="m");
  
  void addVariableFromTemplate(string var, TH1* h, bool prof, 
			       bool is2D, string type);

  void fill(string var, int ds, float val, float weight=1.);
  void fill(string var, int ds, float valx, float valy, float weight);
  void fill(string var, int ds, string type, float value, float weight=1.,string dir="");
  
  void copyHisto( string var, int ds, TH1* h);

  //workflows and histos
  void setRelevantWFs(string var, vector<string> wfs);
  void setRelevantUncs(string var, vector<string> uncs);

  TH1* getHisto(string obs, int ds);
  const hObs* getHObs(string obs);
  
  vector<string> getObservables(bool allObs=false);
  
  //Prepare observables
  hObs preparehObs(string var, int nbinX, vector<float> bins, 
		   string Xleg,string Yleg,
		   string type, bool isglb, bool prof,
		   int nbinsY=-1, 
		   vector<float> binsY=vector<float>(0,0) );
   
  hObs preparehObsFromTemplate(string var, TH1* h, bool prof,
			       bool is2D, string type );

  //saving plots
  void savePlots(string path, const TCanvas* c, string advname);

  //systematic uncertainties
  vector<systM> getSystObs(string obs);
  systM findSysts(string var,string type);


  void saveHistos(string anName, string conName, std::map<std::string, int> cnts, std::map<std::string, double> wgtcnts);

  ClassDef(HistoManager,0)
};

#endif
  
