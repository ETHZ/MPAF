#ifndef _Sample_
#define _Sample_

#include <vector>
#include <stdlib.h>
#include <string>
#include <map>
#include "TROOT.h"

#include "tools/src/Format.cc"

using namespace std;

class Sample {

private:

  string _name;
  int _nProcEvents;
  double _sumProcWgts;
  
  float _xSection;
  float _kFactor;
  
  float _eqLumi;

  float _weight; //weight for 1 pb-1

  bool _isNorm;

  SampleId _sId;

public:

  Sample();
  Sample(SampleId sId, int nProcEvt, double sumProcWgt, 
	 float xSect, float kfact, float eqLumi);

  virtual ~Sample();

  void setName(string N){ _name=N;};
  void setNProcEvts(int n){ _nProcEvents=n;};
  void setSumProcWgts(double w){ _sumProcWgts=w;};

  void setXSect(float XS) { _xSection=XS;};
  void setKFact(float KF) { _kFactor=KF;};
  void setEqLum(float L) { _eqLumi=L;};

  void setLumW(float w) { _weight=w;};
  
  //access functions
  
  string getName() const { return _sId.name;};
  int getNProcEvts() const { return _nProcEvents;};
  double getSumProcWgts() const { return _sumProcWgts;};
  
  float getXSect() const {return _xSection;};
  float getKFact() const {return _kFactor;};
  float getEqLum() const {return _eqLumi;};

  float getLumW() const {return _weight;}; //weight for 1 pb-1

  float getNorm() const {return _sId.norm;};
  bool isNorm() const {return _sId.norm!=-1;};

  string getCR() const {return _sId.cr;};
  bool isDD() const {return _sId.dd;};

private:

  void computeWeight();

  ClassDef(Sample,0)  
};

#endif
