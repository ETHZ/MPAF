#include "src/Dataset.hh"

using namespace std;

ClassImp(Dataset)


//____________________________________________________________________________
Dataset::Dataset():
_chain(0)
{
  _isData = false;
  _isDataDriven = false;
  config("", 1, kTree );
}


//____________________________________________________________________________
Dataset::Dataset(string name):
  _chain(0)
{
  _isData = false;
  _isDataDriven = false;
  config(name, 1, kTree );
}


//____________________________________________________________________________
Dataset::Dataset(string name, int color):
  _chain(0)
{

  _isData = false;
  _isDataDriven = false;
  config(name, color, kHisto);

}


//____________________________________________________________________________
void Dataset::config(string name, int color, int content) {

  _name = name;
  _color = color;
  _isGhost = false;
  _isDataDriven = false;
  _dsContentType = content;
}


//____________________________________________________________________________
Dataset::~Dataset() {
  delete _chain;
}

//____________________________________________________________________________
void Dataset::freeMemory() {
  delete _chain;
}

void
Dataset::setUsefulVars(vector<string> vars) {
  _usefulVars = vars;
}

//____________________________________________________________________________
void Dataset::addSample(const SampleId sId, string path, string dir, string objName, string hname, string hwgtname, float xSect, float kFact, float lumi, float eqLumi, bool loadH) {
  /*
    adds a sample to the dataset; the sample has a name encoded in sfullname,
    lies in the directory path/dir/, has a tree called objName or a histogram
    called hname (hwgtname is a histogram for the sum of processed weights
    corresponding to the sample), has cross section xSect, k-factor kFact, luminosity lumi
    and equivalent luminosity eqLumi (i.e. corrected for the number of events we're
    looping on)
    parameters: sfullname ("data:sname" or just "sname"), path, dir, objName, hname, hwgtname, xSect, kFact, lumi, eqLumi
    return: none
  */

  _isData = false;
  
  if(sId.isData)_isData=true;
  if(sId.dd) {
    //norm corresponds to a datadriven like stuff
    _isDataDriven=true;
  }

  //store the control region from which the sampleshould come from, if any
  // _crSamples[ sId.name ] = sId.cr;

  // //store the norm option
  // _crSamples[ sId.name ] = sId.norm!=-1;


  //protection against double loading in the same dataset
  for(size_t is=0;is<_samples.size();is++) {
    if(_samples[is].getName()==sId.name) {
      return;
    }
  }
	
  //Tree/chain initialisation =========
  if(isTreeType())
    if(_chain==NULL)
      _chain = new TChain(objName.c_str());

  //======
	
  //Looking for the tree if not data-driven
  //string tmpPath=isTreeType()?("data/"+path):"root"; //CH: why? what about absolute paths?
  string subdir=isTreeType()?"data":"root";
  string tmpFName=isTreeType()?(sId.name):objName;
  int nProcEvt = (hname=="")?-1:getNProcEvents(path, dir, subdir, tmpFName, hname);
  double sumProcWgt = (hwgtname=="")?-1:getSumProcWgts(path, dir, subdir, tmpFName, hwgtname);
  
  Sample s(sId, nProcEvt, sumProcWgt, xSect, kFact, eqLumi);
  _samples.push_back(s);
  
  //tree analysis 
  if(isTreeType()) {
    loadTree(path, dir, subdir, sId.name, objName);
	
    cout<<" Adding "<<sId.name<<"  to "<<_name
	<<"   :  nEvt "<<_chain->GetEntries()<<" ("<<nProcEvt
	<<" gen) "<<" ("<<sumProcWgt<<" genwgts)"<<" / w (/pb-1) = "<<s.getLumW()<<endl;
  }
  else {
    if(loadH) { //reading histograms only when needed (disabled for datacards)
      loadHistos(path, dir, subdir, objName, hname, sId.cr);
    }
    if(sId.norm==-1) {
      if(sId.cr=="" && sId.dd==false)
	cout<<" Adding "<<sId.name<<"  to "<<_name
	    <<"   : "<<" ("<<nProcEvt
	    <<" gen) "<<" ("<<sumProcWgt<<" genwgts)"<<" / w (/pb-1) = "<<s.getLumW()<<endl;
      else
	cout<<" Adding "<<sId.name<<" ("<<sId.cr<<")  to "<<_name
	    <<"   : "<<" ("<<nProcEvt
	    <<" gen) "<<" ("<<sumProcWgt<<" genwgts)"<<" / w (/pb-1) = "<<s.getLumW()<<endl;
    
    }
    else {
      cout<<" Adding "<<sId.name<<"  to "<<_name
	  <<"   : "<<" fixed normalization ("<<sId.norm<<")"<<endl;

    }

  }

}

void
Dataset::addFriend(string friendname){
  _friends.push_back(friendname);
}

int
Dataset::getNProcEvents(string path, string dir, string subdir, string fileName, string hname) {

  string NameF = goodFilePath(path, dir, fileName, subdir);

  TFile* file = TFile::Open( NameF.c_str() );
  if(file==nullptr) { cout<<" warning, unable to find the proper number of processed events"<<endl;return 1;}
  TH1* htmp = (TH1*)file->Get( hname.c_str() );
  int nProc=-1;
  if(htmp) {
    nProc = htmp->Integral(0,1001);
    delete htmp;
  }
  else nProc = -1;

  file->Close();
  delete file;

  return nProc;
}

double
Dataset::getSumProcWgts(string path, string dir, string subdir, string fileName, string hwgtname) {

  string NameF = goodFilePath(path, dir, fileName, subdir);
  
  TFile* file = TFile::Open( NameF.c_str() );
  if(file==nullptr) { cout<<" warning, unable to find the proper number of processed events"<<endl;return 1;}
  TH1* htmp = (TH1*)file->Get( hwgtname.c_str() );
  double nProc=-1;
  if(htmp) {
    nProc = htmp->Integral(0,1001);
    delete htmp;
  }
  else nProc = -1;
 
  file->Close();
  delete file;

  return nProc;
}



int
Dataset::getNProcEvents(/*int evt*/) const {
  //MM fixme, multiple sample handling not considered anymore, still useful?
  return _samples[0].getNProcEvts();

  // for(size_t iv=0;iv<_events.size();iv++) {
  //   if(evt>=_events[iv].first && evt<_events[iv].second) {
  //     return _samples[iv]->getNProcEvts();
  //   }
  // }
  // return -1;

}

double
Dataset::getSumProcWgts(/*int evt*/) const {
  //MM fixme, multiple sample handling not considered anymore, still useful?
  return _samples[0].getSumProcWgts();

  // for(size_t iv=0;iv<_events.size();iv++) {
  //   if(evt>=_events[iv].first && evt<_events[iv].second) {
  //     return _samples[iv]->getNProcEvts();
  //   }
  // }
  // return -1;

}

// float Dataset::computeWeight(float nEvts, float xSect, float kFact, float lumi, float& eqLumi) {
  
//   float weight=1.;

//   if(eqLumi==-1) { //means that Xsection used for reweigthing
//     eqLumi = nEvts/xSect;
//   }
  
//   weight =(1./eqLumi)*lumi*kFact;
//   return weight;
// }


// string 
// Dataset::findProcess(int evt ) {

//   for(size_t iv=0;iv<_events.size();iv++) {
//     if(evt>=_events[iv].first && evt<_events[iv].second) {
//       return _samples[iv].getName();
//     }
//   }
//   return "";
// }


// float
// Dataset::findWeight(int evt ) {
  
//   for(size_t iv=0;iv<_events.size();iv++) {
//     if(evt>=_events[iv].first && evt<_events[iv].second) {
//       return _weights[iv];
//     }
//   }
//   return 0;
// }


vector<string>
Dataset::getSamples() {
  vector<string> snames;
  for(size_t is=0;is<_samples.size();is++) {
    snames.push_back( _samples[is].getName() );
  }
  return snames;
}

const Sample*
Dataset::getSample(string sname) const {
  vector<string> snames;
  for(size_t is=0;is<_samples.size();is++) {
    if(sname==_samples[is].getName()) return &(_samples[is]);
  }
  return nullptr;
}


void 
Dataset::loadTree(string path, string dir, string subdir, string sname, string objName) {
  TFile* datafile(nullptr);

  string NameF = goodFilePath(path, dir, sname, subdir);

  datafile = TFile::Open(NameF.c_str());
  if(datafile==nullptr) { 
    cout<<" No such file "<<sname<<endl; return;
  }
    
  TTree* tmptree = (TTree*)datafile->Get( objName.c_str() );
 
  if(tmptree != nullptr ) {
    _chain->Add( (NameF+"/"+objName).c_str() ); 

    //cleaning friends if needed
    TList* lfriends = _chain->GetListOfFriends();
    TIter next(lfriends);
    TObject* fr = 0;
    while ((fr = next())) {
      _chain->RemoveFriend((TTree*)fr);
    }


    // adding friend-trees
    for (size_t ft=0; ft<_friends.size(); ft++){
      string NameFr = goodFilePath(path, dir, _friends[ft] + "/evVarFriend_" + sname, subdir);
      string name = _friends[ft]+" = sf/t";
      _chain->AddFriend((name).c_str(),(NameFr).c_str());
    } 
    //nEvent = tmptree->GetEntries();
  }
  else {
    cout<<" Error no correct tree in "<<sname<<" file, aborting"<<endl;
    abort();
  }    

  delete tmptree;
  delete datafile;
   
}

void 
Dataset::loadHistos(string path, string dir, string subdir, string filename, string hname, string optCat) {
  TFile* datafile(nullptr);
  

  string NameF = goodFilePath(path, dir, filename, subdir);
  datafile = TFile::Open(NameF.c_str());

  if(datafile==nullptr) {cout<<"warning, unable to load histograms"<<endl; return;}

  //scan the file to retrieve the histograms
  TIter nextkey(datafile->GetListOfKeys());
  TKey *key;
  while ((key = ((TKey*)nextkey()))) {
    TObject* obj = key->ReadObj(); 
    if( obj==nullptr ) continue;
      
    //found a TDirectory which can be a variable
    if( (string)obj->IsA()->GetName()!=("TDirectoryFile") ) continue;
      
    string varName(obj->GetName());
    map<string, TH1*> tmp;
    
    bool find=false;
    for(size_t i=0;i<_usefulVars.size();i++) {
      if(_usefulVars[i]==varName ||
	 _usefulVars[i]==varName+optCat ||
	 varName.find(_usefulVars[i]+"Unc")!=string::npos) {
	find=true; break;
      }
    }

    if(_usefulVars.size()!=0 && !find) continue; 
       // find(_usefulVars.begin(), _usefulVars.end(), varName)==_usefulVars.end() &&
       // find(_usefulVars.begin(), _usefulVars.end(), varName+optCat)==_usefulVars.end() &&
       // !findUnc ) continue;
    

    if(optCat!="") {
      size_t op=varName.find(optCat);
      if(op==string::npos) continue;
      else varName.erase(op,optCat.size());
    }

    TIter nextkeyD( ((TDirectory*)obj)->GetListOfKeys() );
    TKey *keyD;
    while ((keyD = ((TKey*)nextkeyD()))) {
      TObject* objD = keyD->ReadObj(); 
      if( objD==nullptr ) continue;
      
      if( ((string)(objD->IsA()->GetName())).substr(0,2)!=("TH") &&
	  ((string)(objD->IsA()->GetName())).substr(0,2)!=("TP") ) continue;

      //matching the samples needed for the dataset
      string sName( objD->GetName() );
      for(size_t is=0;is<_samples.size();is++) {
	if( sName!=_samples[is].getName() ) continue;
	   
	//histograms and not normalization file
	if(varName=="nEvtProc") continue;
	if(varName=="sumWgtProc") continue;
       
	
	if(_histos[ varName ].size()==0) { //initialization
	  tmp[ sName ] = (TH1*)((TH1*)objD->Clone());
	  _histos[ varName ]= tmp;
	}
	else {
	  _histos[ varName ][ sName ]= (TH1*)((TH1*)objD->Clone());
	}	  

	break;
	
      }
	
    } //loop keyD in directory
      
  } //loop key in file
    
  datafile->Close();
  delete datafile;
  
}

vector<string> 
Dataset::getObservables() {
  vector<string> names;
  for(map<string,map<string, TH1*> >::const_iterator it=_histos.begin();
      it!=_histos.end();it++) {
    names.push_back( it->first );
  }

  return names;
}

TH1*
Dataset::getHisto(string varName, string sName) {
  return _histos[ varName ][ sName ];
}


int
Dataset::hasSample(string sname) const {

  for(size_t is=0;is<_samples.size();is++) {
    if(_samples[is].getName()==sname)
      return is;
  }
  
  return -1;
}

float
Dataset::getWeight(string sname) const {
  int is = hasSample(sname);
  if(is==-1) return 0;
  return getWeight(is);
}

string
Dataset::goodPath(string path){

  if(path.find("psi.ch") != (size_t) -1) return "dcap://t3se01.psi.ch:22125/" + path;
  if(path.find("/eos/")  != (size_t) -1) return "root://eoscms.cern.ch/" + path;

  return path;

}

string
Dataset::goodFilePath(string path, string dir, string fileName, string subdir){
  // CH: path is the "dir" variable given in the config file
  //     dir  is the "dir" attribute given to the dataset (if so), whose name is fileName

  // remove the last slash because it's added in the logic below
  if(dir .length() > 0 && dir .substr(dir .length()-1,1) == "/") dir .erase(dir .length()-1);
  if(path.length() > 0 && path.substr(path.length()-1,1) == "/") path.erase(path.length()-1);

  // absolute dir
  if(dir.substr(0,1) == "/") 
    return goodPath(dir + "/"  + fileName + ".root"); 

  // dir on EOS with root://
  if(dir.find(":") != (size_t) -1 && dir.find("psi.ch") == (size_t) -1) 
    return dir + "/"  + fileName + ".root";
  
  // relative dir -> relative to path!
  if(dir != "") 
    path += "/" + dir;

  // path on EOS with root://
  if(path.find(":") != (size_t) -1 && path.find("psi.ch") == (size_t) -1) 
    return path + "/"  + fileName + ".root";

  // absolute path
  if(path.substr(0,1) == "/") 
    return goodPath(path + "/" + fileName + ".root");

  // ignore empty subdirs (in case data or root is already appended to path)
  if(subdir.length() > 0) 
    path = subdir + "/" + path;

  // relative path -> relative to MPAF/workdir! data or root given in subdir
  return string(getenv("MPAF")) + "/workdir/" + path + "/" + fileName + ".root";

}
