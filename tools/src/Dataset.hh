#ifndef _Dataset_
#define _Dataset_

#include <vector>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>

#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TChain.h"
#include "TObject.h"
#include "TKey.h"

#include "tools/src/Sample.hh"
#include "tools/src/Format.cc"

class Dataset {

private:

  std::string _name;
  bool _isData;
 
  std::vector<Sample> _samples;
  vector<pair<int,int> > _events;
  std::vector<float> _weights;
  std::vector<int> _nprocs;
	
  int _color;
	
  //for tChain part
  TChain* _chain;
	
  //for histogram part
  std::map<std::string, std::map<std::string, TH1*> > _histos;
	
  int _isFromCS;
  bool _isGhost;
	
  int _dsContentType;
  std::vector<std::string> _friends;

  std::vector<string> _usefulVars;

  // std::map<std::string, std::string> _crSamples;
  // std::map<std::string, bool> _isNormSamples;

  bool _isDataDriven;

public:

  enum {
    kTree = 0,
    kHisto
  };

  Dataset();
  Dataset(std::string name);
  Dataset(std::string name, int color);
	
  virtual ~Dataset();
	
  void freeMemory();

  void config(std::string name, int color, int content);
	
  void setName(std::string name){ _name=name;};
  void setColor(int ncol){ _color=ncol;};
	
  void addSample(SampleId sId, std::string path, std::string dir, 
		 std::string objName, std::string hname, std::string hwgtname, float xSect,
		 float kFact, float lumi, float eqLumi, bool loadH=true);

  void addFriend(std::string friendname);

  void setUsefulVars(std::vector<std::string> vars);

  //access functions 
  std::string getName() const { return _name;};
  int getColor(){ return _color;};
	
  bool isDataset(std::string name){return _name==name;};
  bool isPPcolDataset() const { return _isData;};

  int hasSample(string sname) const;
	
  bool isTreeType() { return _dsContentType==kTree;};
  bool isHistoType() { return _dsContentType==kHisto;};
	
  bool isDataDriven(){return _isDataDriven;};
  bool isFromCS(){return _isFromCS!=0;};
  int csCode(){return _isFromCS;};
	
  bool isGhost(){return _isGhost;};

  // std::string crSample(std::string sname){return _crSamples[sname];};
  // bool isNormSample(std:: string sname) {return _isNormSamples[sname];};

  //std::string findProcess(int event);
	
  //float findWeight(int event);
	
  float getWeight(int is) const {return _samples[is].getLumW(); };
  float getWeight(string sname) const;

  string goodPath(string path);
  string goodFilePath(string path, string dir, string fileName, string subdir = "data");
	
  TTree* getTree() {return _chain;};
  int getNEvents() { return _chain->GetEntries(); };
	
  int getNProcEvents(/*int evt*/) const;
  double getSumProcWgts(/*int evt*/) const;
	
  //void setNMax(size_t nmax);
	
  std::vector<std::string> getSamples();
  std::vector<std::string> getObservables();
  TH1* getHisto( std::string varName, std::string sName);

  const Sample* getSample(string sname) const;
  

private:

  void loadTree(std::string path, std::string dir, string subdir, std::string sname, std::string objName);
  void loadHistos(std::string path, std::string dir, string subdir, std::string sname, std::string hname, std::string optCat);

  // float computeWeight(float nEvts, float xSect, float kFact,
  // 		      float lumi, float& eqLumi);
  
  int getNProcEvents(string path, string dir, string subdir, string sname, string hname);
  double getSumProcWgts(string path, string dir, string subdir, string sname, string hwgtname);
  

  ClassDef(Dataset,0)
  
};

#endif
