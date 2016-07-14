#include "display/core/AnaConfig.hh"

using namespace std;


AnaConfig::AnaConfig() {

  _dir="";
  _path=string(getenv ("MPAF"))+"/workdir/root";

  _useXSect=true;
  _noData=false;
 
  _skiptree=false;

  _lumi=0;
  _runFilter=0;
  _runNum=0;

  _testNMax=(size_t)-1;

  _dbm = new DataBaseManager();
  
}

AnaConfig::~AnaConfig() {
  reset();
}


void AnaConfig::reset() {

  _dir="";
  _path=string(getenv ("MPAF"))+"/workdir/root";

  for(_itDs=_datasets.begin();_itDs!=_datasets.end();_itDs++)
    delete _itDs->second;
  
  _datasets.clear();
  _numDS.clear();

  _lumi=0;
  _runFilter=0;
  _runNum=0;

  _useXSect=true;
  _noData=false;
  _skiptree=false;
  
}

// void AnaConfig::setNMax(size_t testNMax) {
//   _testNMax = testNMax;
// }

// float AnaConfig::getWeight(int channel, int evt) {

//   if(evt==-1) return 0; //shield against initalization step
  
//   string chan = findDS(channel);
//   return getWeight(chan,evt);
// }


// float AnaConfig::getWeight(string chan, int evt) {

//   if(evt==-1) return 0; //shield against initalization step
//   return _datasets[chan]->findWeight(evt);
// }


// string AnaConfig::getSample(int channel, int evt) {

//   if(evt==-1) return ""; //shield against initalization step
  
//   string chan = findDS(channel);
//   return getSample(chan, evt);

//   cout<<" ********************** Warning Dataset "<<endl;
//   return "";
// }

// string AnaConfig::getSample(string chan, int evt) {

//   if(evt==-1) return ""; //shield against initalization step
  
//   _itDs=_datasets.find(chan);
//   if(_itDs!=_datasets.end()) {
//     return _itDs->second->findProcess(evt);
//   }
  
//   cout<<" ********************** Warning dataset : "<<chan<<endl;
//   return "";
// }

Dataset*
AnaConfig::getDataset(string name) {
  return  _datasets[ name ];
}

string 
AnaConfig::findDS(int channel) {

  _itNDS=_numDS.find(channel);
  if(_itNDS==_numDS.end()) {
    cout<<" Warning, no dataset for the channel "<<channel<<endl;
    return "";
  }
 
  return _itNDS->second;
}


string 
AnaConfig::findDSName(string channel) {

  map<string, Dataset* >::const_iterator itDs;
  for(itDs=_datasets.begin(); itDs!=_datasets.end();itDs++) {
    if(itDs->second->hasSample(channel)!=-1 )
      return itDs->first;
  }
  
  return "";  
}


string 
AnaConfig::findDSName(string channel, string crName) {

  map<string, Dataset* >::const_iterator itDs;
  for(itDs=_datasets.begin(); itDs!=_datasets.end();itDs++) {
    if(itDs->second->hasSample(channel)!=-1 && itDs->second->getSample(channel)->getCR()==crName )
      return itDs->first;
  }
  
  return "";  
}

vector<string> 
AnaConfig::findDSNames(string channel, string crName) {
  vector<string> names;
  map<string, Dataset* >::const_iterator itDs;
  for(itDs=_datasets.begin(); itDs!=_datasets.end();itDs++) {
    if(itDs->second->hasSample(channel)!=-1 && itDs->second->getSample(channel)->getCR()==crName )
      names.push_back(itDs->first);
  }
  
  return names; 
}


vector<string> 
AnaConfig::findDSNames(string channel) {
  vector<string> names;
  map<string, Dataset* >::const_iterator itDs;
  for(itDs=_datasets.begin(); itDs!=_datasets.end();itDs++) {
    if(itDs->second->hasSample(channel)!=-1)
      names.push_back(itDs->first);
  }
  
  return names; 
}


Dataset* 
AnaConfig::findDS(string channel) {
  string dsName = findDSName(channel);
  if(dsName!="")
    return getDataset(dsName);
  else
    return nullptr;
}

vector<Dataset*> 
AnaConfig::findDSS(string channel) {
  vector<string> dsNames = findDSNames(channel);
  vector<Dataset*> dss;

  for(unsigned int id=0;id<dsNames.size();id++)
    if(dsNames[id]!="") dss.push_back( getDataset(dsNames[id]) );

  return dss;
}




Dataset* 
AnaConfig::findDS(string channel, string crName) {
  string dsName = findDSName(channel, crName);
  if(dsName!="")
    return getDataset(dsName);
  else
    return nullptr;
}


vector<Dataset*> 
AnaConfig::findDSS(string channel, string crName) {
  vector<string> dsNames = findDSNames(channel, crName);
  vector<Dataset*> dss;

  for(unsigned int id=0;id<dsNames.size();id++)
    if(dsNames[id]!="") dss.push_back( getDataset(dsNames[id]) );

  return dss;
}


int
AnaConfig::findChan(string ds) {
  for(_itNDS=_numDS.begin();_itNDS!=_numDS.end();_itNDS++) {
  
    vector<string> samples = _datasets[ _itNDS->second ]->getSamples();
    for(size_t is=0;is<samples.size();is++) {
      if(ds == samples[is]) return _itNDS->first;
    }
  }

  cout<<" Warning, no channel for the dataset "<<ds<<endl;
  return -1;
}

void AnaConfig::configureLumi(map<string,float> LumisXS, map<string,float> Kfac, float l,bool useXS) {
  
  _xSecLumis = LumisXS;
  _kFactors = Kfac;
  _lumi =l;
  _useXSect = useXS;
  
}

void 
AnaConfig::configureNames(string dir, string rootFile, string fileList) {
  _dir = dir;
  _rootFile = rootFile;
  vector<string> filenames = listFiles((string)(getenv("MPAF")) + "/workdir/stats/" + dir + "/", fileList + ".dat");
  _statFileList = filenames;
  _hname = "nEvtProc";
  _hwgtname = "sumWgtProc";
}


void AnaConfig::configureData(bool runfilter, int runnum,bool MCOnly ) {
  _runFilter=runfilter;
  _runNum=runnum;

  _noData = MCOnly;
}

void
AnaConfig::loadXSDB(string dbname) {
  _dbm->loadDb("Xsections",dbname);
}

void
AnaConfig::loadKFDB(string dbname) {
  _dbm->loadDb("Kfactors",dbname);
}

void
AnaConfig::isHistoAnalysis() {
  _skiptree=true;
}

SampleId
AnaConfig::parseSampleId(string str) {
  SampleId sId;
  sId.norm = -1;
  sId.dd = false;
  sId.isData = false;
  sId.cr = "";
  sId.name = "";

  string tmpStr=str;
  //normalization ======
  size_t pn=str.find("=");
  if(pn!=string::npos) {
    sId.norm = atof( str.substr(pn+1, str.size()-pn-1).c_str() );
    tmpStr=str.substr(0, pn);
  }

  //data-driven ========
  size_t pd=tmpStr.find("data:");
  if(pd!=string::npos) {
    sId.dd = true;
    tmpStr=tmpStr.substr(5, tmpStr.size()-5);
  }
 
  //control region =====
  size_t pc=tmpStr.find(":");
  if(pc!=string::npos) {
    sId.cr = tmpStr.substr(0, pc);
    tmpStr=tmpStr.substr(pc+1, tmpStr.size()-pc-1);
  }
  
  //sample name ========
  sId.name=tmpStr;

  return sId;
}

void
AnaConfig::addUsefulVar(string var) {
  _usefulVars.push_back(var);
}

void
AnaConfig::addSample( string str, string sname, int col, float weight, bool loadH) {
 
  
  string dsName=sname;
  if(sname=="pseudodata") dsName="data";

  //parse the sample name
  SampleId sId=parseSampleId(str);
  if( sId.cr!="" ) {
    _csData.push_back( pair<string, float>(sId.name,sId.norm) );
  }

  //for setting data...
    
  _itDs=_datasets.find(dsName);
  
  if(_itDs==_datasets.end() ) {
    Dataset* ds=new Dataset(dsName,col);
    _datasets[ dsName ] = ds;
    _numDS[ _numDS.size() ] = dsName;
  }
  
  if(sname=="data" || sname=="Data")
    sId.isData=true;

  if(sname=="data" || sname=="Data" || sId.dd ) {
    // sId.dd=true;
    _datasets[ dsName ]->setUsefulVars(_usefulVars);
    _datasets[ dsName ]->addSample(sId, _path, _dir, _rootFile,
				   _hname+"/"+sId.name,_hwgtname+"/"+sId.name,0., 1.*weight, 1., 1., loadH);
    _dsnames.push_back(dsName);
 
    return;
  }

 
  
  //histogram analysis
  if(!_skiptree) {

    //find xSect/kFact/eqLumi
    float xSect=1.,kFact=1.,eqLumi=1.;
   
    _itXS=_xSecLumis.find(sId.name);
    if(_itXS==_xSecLumis.end()) {
      xSect =-1000; eqLumi=-1;
      
      //first, check if a Xsection DB is loaded
      if(_dbm->exists("Xsections"))
	xSect = _dbm->getDBValue("Xsections", sId.name);
      
      if(xSect==-1000) { //nothing found in DB
	cout<<" Be careful, no specified "
	    <<(string)((_useXSect)?" cross section":" equivalent luminosity")
	    <<" for "<<sId.name<<" , 1 by default *****======== "<<endl;
    
	//FIXME, set weight to 1 by compensating with the lumi
	xSect =1.; eqLumi=1.;
      }
    }
    else {
      if(_useXSect)
	{eqLumi=-1; xSect =_itXS->second;}
      else  
	{eqLumi=_itXS->second; xSect =-1;}
    }


    //k factors
    _itKF=_kFactors.find(sId.name);

    if(_itKF==_kFactors.end()) {
      
      //first, check if a kFactor DB is loaded
      if(_dbm->exists("Kfactors"))
	kFact = _dbm->getDBValue("Kfactors", sId.name);
      if(kFact!=1) { 
	cout<<"applying k factor " << kFact << " for dataset " <<  sId.name << endl;
      }
    }
    else {
      cout<< "no k factor found in database - using default 1" << endl;
      kFact =1;
    }
    
    _datasets[ dsName ]->setUsefulVars(_usefulVars);
    _datasets[ dsName ]->addSample(sId, _path, _dir, _rootFile,
				   _hname+"/"+sId.name, _hwgtname+"/"+sId.name, 
				   xSect, kFact*weight, _lumi, eqLumi, loadH);
    _dsnames.push_back(sname);
  }
  else {
    _datasets[ dsName ]->setUsefulVars(_usefulVars);
    _datasets[ dsName ]->addSample(sId, "", "", "", "", 0, 0, 0, 0, loadH);
    _dsnames.push_back(dsName);
  }
  
}


bool
AnaConfig::passRunFilter(int run) {
  if(!_runFilter) return true;
  if(run > _runNum ) return false;
  return true;
}


vector<string > 
AnaConfig::getDSNames() {
 
  vector<string> names;
  for(_itNDS=_numDS.begin();_itNDS!=_numDS.end();_itNDS++) {
    _itDs = _datasets.find( _itNDS->second );
    names.push_back( _itDs->second->getName() );
  }
  
  return names;
}

vector<pair<string, float> >
AnaConfig::getCSData() {
  return _csData;
}

bool
AnaConfig::isNoDataAna() {
  
  bool mcOnly;

  _itDs = _datasets.find("data");
  map<string, Dataset* >::iterator _itDs2;
  _itDs2 = _datasets.find("data");
  if( _itDs==_datasets.end() && _itDs2==_datasets.end() )
    mcOnly = true;
  else {
    mcOnly = _noData;
  }
  
  return mcOnly;
}


string
AnaConfig::getHName() {


  if(_hname.find("/")==(size_t)-1)
    {return _hname;}
  else {
    size_t p = _hname.find("/");

    return _hname.substr(p+1, _hname.size()-p-1);

  }

}

string
AnaConfig::getHwgtName() {


  if(_hwgtname.find("/")==(size_t)-1)
    {return _hwgtname;}
  else {
    size_t p = _hwgtname.find("/");

    return _hwgtname.substr(p+1, _hwgtname.size()-p-1);

  }

}


vector<string>
AnaConfig::listFiles(string dir, string files){

  vector<string> result;

  string command = "ls " + dir + files;
  FILE * pipe = popen(command.c_str(), "r");

  char buffer[128];
  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
      result.push_back(buffer);
    result[result.size()-1].erase(result[result.size()-1].find_last_not_of(" \n\r\t")+1);
  }

  pclose(pipe);
  return result;
}

