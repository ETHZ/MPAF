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

#include "analysis/core/MPAF.hh"


#include <TObjArray.h>

/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
MPAF::MPAF(){
  /* 
     constructs the MPAF Class 
     parameters: none
     return: none
  */
	
  initialize();
	
}


//____________________________________________________________________________
MPAF::~MPAF(){
  /* 
     destructs the MPAF class
     parameters: none
     return: none
  */

  delete _vc;
  delete _hm;
  delete _dbm;
  delete _au;

}


//____________________________________________________________________________
void MPAF::initialize(){
  /*
    initializes the MPAF class, defining standard values of certain variables
    parameters: none
    return: none
  */

  _vc  = new VarClass();
  _hm  = new HistoManager();
  _dbm = new DataBaseManager();
  _au  = new AnaUtils();
  
  _vc->_su->init(_dbm);

  _fullSkim=true;
  _skim=false;

  _nEvtMax=-1;
  _nSkip=0;

  _wfNames[AUtils::kGlobal] = "";

  _hname="";
  _hwgtname="";
  _summary=false;
}


//____________________________________________________________________________
//void MPAF::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */  

//}


//____________________________________________________________________________
void MPAF::analyze(){
  /*
    does the loop over the data samples, reads the tree and calls run() at every
    iteration
    parameters: none
    return: none
  */
  TStopwatch stw;
  float timeCPU=0;
  float timeWall=0;
  int nE=0;

  //CH: this line has to be BEFORE the call of defineOutput!
  //FakeRatio and FRinSitu class needs to know the number of datasets before defining Output
  _numDS = _datasets.size();


  // define and book all outputs
  defineOutput();
  //copy the histograms for the different workflows
  addWorkflowHistos();


  // loop over given samples
  for(unsigned int i=0; i<_numDS; ++i){
  
    // open file
    _sampleName = _datasets[i]->getName();
  
    _inds = i;
    _isData = _datasets[i]->isPPcolDataset();
  
    _vc->reset();
    _vc->buildTree( _datasets[i]->getTree() , _skim&&_fullSkim );
    _vc->buildFriendTree( _datasets[i]->getTree() , _skim&&_fullSkim );
    
    //prepare skimmed file and tree
    if(_skim) {
      initSkimming();
    }
	
    // loop over entries
    _nEvts[i] = _datasets[i]->getNEvents();
    _nEvtsDs[i] = _nEvts[i];
    if(_nEvtMax != (size_t)-1) _nEvts[i] =  min(_nEvtMax+_nSkip,_nEvts[i]);
    
    cout<<" Starting processing dataset : "<<_sampleName<<"  (running on "<<_nEvts[i]<<" events)"<<endl;

    boost::progress_display show_progress( _nEvts[i] );
    for(_ie = _nSkip; _ie < _nEvts[i]; ++_ie) {
      ++show_progress;
      stw.Start();
      
      //reinitialization
      _weight = 1.;
      _wBack = _weight;
      _uncId = false;
      _unc = "";//reinitialization
      _au->setUncSrc("", SystUtils::kNone );
      _curWF = -100;//default workflow, all counters triggered 
      _au->setCurrentWorkflow(_curWF);

      // get tree entry, i.e. load branches
      _vc->setEvent(_ie);
      if(_skim&&_fullSkim)
        _datasets[i]->getTree()->GetEntry(_ie);

      // get event weight, PU reweight it if needed 
      modifyWeight();
      
      // do something at every entry	
      run();

      //alternate workflows for uncertainty sources
	  for(size_t iu=0;iu<_uncSrcs.size();iu++) {
	    //update the workflow
	    _curWF = -100;
	    _weight = _wBack;
	    modifyWeight();
	    if(iu==0) _vc->nextEvent();
	    else _vc->sameEvent();
	    _uncId = true;
	    _unc = _uncSrcs[iu];
	    _uDir = _uncDirs[iu];
	    string dir = (_uDir==SystUtils::kUp)?"Up":"Do";
	    //very ugly...
	    // _curWF = _au->getUncWorkflow("Unc"+_unc+dir);
	    //_offsetWF=_au->getUncWorkflow("Unc"+_unc+dir);
	    _au->setCurrentWorkflow(_curWF);
	    _au->setUncSrc(_unc, _uDir );
	    applySystVar( _vc->_su->getSystInfos(_unc, _uDir) );
	    run();
	    _vc->backPortAllVars();
	  }

      //destroy old Candidate pointers ======
      Candidate::reset();
      ObjectStore::clear();
      //===========================

      timeWall+=stw.RealTime();
      timeCPU+=stw.CpuTime();
      nE++;   
    }

    //write skimmed file
    if(_skim) {
      finalizeSkimming();
    }
		
    //cleaning memory
    _datasets[i]->freeMemory();
 
  }


  cout<<" +++ Execution frequency +++ "<<endl;
  cout<<"   Real time = "<<timeWall/nE<<" s/evt "<<"->"<<nE/timeWall<<" Hz"<<endl;
  cout<<"   CPU time = "<<timeCPU/nE<<" s/evt "<<"->"<<nE/timeCPU<<" Hz"<<endl<<endl;

  // write all outputs to disk
  internalWriteOutput();

  if(_summary)
    _au->printNumbers();
  
}

//____________________________________________________________________________
void MPAF::loadConfigurationFile(std::string cfg){
  /*
    loads the configuration file and reads the configuration variables
    parameters: configuratoin_file (path to the configuration file)
    return: none
  */

  _inputVars = Parser::parseFile(cfg);
  _nEvtMax = -1;
  string tName;
  vector<string> _friends;
  
  for(MIPar::const_iterator it=_inputVars.begin(); 
      it!=_inputVars.end();it++) {

    if(it->second.type==Parser::kAN) {
      _className = it->second.val;
    }
    if(it->second.type==Parser::kDir) {
      _inputPath=it->second.val;
    }
    if(it->second.type==Parser::kVbs) {
      // int vLvl=Tools::toVerbosityLevel(it->second.val);
      // _verbose->setVerbosityLevel(vLvl);
    }
    if(it->second.type==Parser::kSkim) {
      _skim    = true;
      if(it->second.val=="Limited") _fullSkim=false;
    }
    if(it->second.type==Parser::kNMax) {
      _nEvtMax = atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kSkip) {
      _nSkip = atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kTree) {
      tName = it->second.val;
    }
    if(it->second.type==Parser::kHisto) {
      _hname = it->second.val;
    }
    if(it->second.type==Parser::kWgtHisto) {
      _hwgtname = it->second.val;
    }
    if(it->second.type==Parser::kFT){
      _friends.push_back(it->second.val);
    }
    if(it->second.type==Parser::kSummary){
      _summary = atoi(it->second.val.c_str());
  }
    
  }

  //datasets
  for(MIPar::const_iterator it=_inputVars.begin(); 
      it!=_inputVars.end();it++) {
    
    if(it->second.type!=Parser::kDS) continue;
    
    string dsName=it->second.val;
    string pfx="";
    string dirName="";
    bool absdir=false;
    vector<string> friends;
    vector<string> opts= it->second.opts;
    if(opts.size()!=0) {
      for(size_t i=0;i<opts.size();i++) {
	if(opts[i].substr(0,4)=="pfx:") {
	  pfx=opts[i].substr(4, opts[i].size()-4 );
	}
        if(opts[i].substr(0,4)=="dir:") {
          dirName=opts[i].substr(4, opts[i].size()-4 );
        }
        if(opts[i].substr(0,7)=="absdir:") {
          dirName=opts[i].substr(7, opts[i].size()-7 );
          absdir=true;
        }
	if(opts[i].substr(0,3)=="ft:"){
	  friends.push_back(opts[i].substr(3, opts[i].size()-3 ));
	} 
      }
    }
    //adding postfix
    dsName+=pfx;

    _datasets.push_back(new Dataset(dsName));
    _nEvtsDs.push_back(0);
    _nEvts.push_back(0);
    
    SampleId sId;
    sId.name = it->second.val; //was val
    sId.cr = "";
    sId.dd =false;
    sId.norm = -1; 
    
    for (size_t ft=0; ft<_friends.size();ft++) {
      _datasets.back()->addFriend(_friends[ft]); 
    }

    for (size_t ft=0; ft<friends.size();ft++) {
      _datasets.back()->addFriend(friends[ft]);
    }

    if(!absdir)
      _datasets.back()->addSample(sId, _inputPath, dirName, tName, _hname, _hwgtname, 1.0, 1.0, 1.0, 1.0);
    else
      _datasets.back()->addSample(sId, "://"+dirName, "", tName, _hname, _hwgtname, 1.0, 1.0, 1.0, 1.0);
    
    _au->addDataset( dsName );
  }

  _au->init();

}


string
MPAF::getCfgVarS(string n, string def) {
  MIPar::const_iterator it;
  it=_inputVars.find(n);
  if(it==_inputVars.end()) return def;
  return _inputVars[n].opts[0];
}

int
MPAF::getCfgVarI(string n, int def) {
  MIPar::const_iterator it;
  it=_inputVars.find(n);
  if(it==_inputVars.end()) return def;
  return atoi(getCfgVarS(n, "").c_str() );
}

float
MPAF::getCfgVarF(string n, float def) {
  MIPar::const_iterator it;
  it=_inputVars.find(n);
  if(it==_inputVars.end()) return def;
  return atof(getCfgVarS(n, "").c_str() );
}

//____________________________________________________________________________
void MPAF::setConfigName(std::string cfg){
  /*
    saves the name of the configuration
    parameters: configuration_file
    return: none
  */

  size_t p = cfg.find_last_of("/");
  size_t q = cfg.find(".cfg");

  _cfgName = cfg.substr(p+1, q-p-1);

}


//____________________________________________________________________________
void MPAF::startExecution(std::string cfg){
  /*
    starts MPAF, i.e. loads the configuration file, checks the configuration,
    loads and sets some variables and prepares the output structure
    parameters: configuration_file (path to the configuration file)
    return: none
  */

  setConfigName(cfg);
  loadConfigurationFile(cfg);
  
  std::vector<std::string> dsNames;
  for(unsigned int i=0; i<_datasets.size(); ++i) {
    dsNames.push_back(_datasets[i]->getName());
  }

  _hm->configAnalysis( dsNames );

}





/*****************************************************************************
******************************************************************************
** PLACEHOLDERS AND FUNCTIONS TO BE USED BY SUB CLASSES                     **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void MPAF::run(){
  /*
    placeholder for running the analysis, performing the event selection and
    filling histograms per tree entry
    parameters: none
    return: none
  */

}

void MPAF::internalWriteOutput() {

  writeOutput();

  map<string, int> cnts;
  map<string, double> wgtcnts;
  for(unsigned int ids=0;ids<_datasets.size(); ++ids) {
    float fact=(float)_nEvts[ids]/_nEvtsDs[ids];
    cnts[ _datasets[ids]->getName() ] = _datasets[ids]->getNProcEvents() * fact;
    wgtcnts[ _datasets[ids]->getName() ] = _datasets[ids]->getSumProcWgts() * fact;
  }

  cout << "writing output to disk" << endl;

  _hm->saveHistos (_className, _cfgName, cnts, wgtcnts);
  _au->saveNumbers(_className, _cfgName, cnts, wgtcnts);


}


/*****************************************************************************
******************************************************************************
** INTERFACE TO HISTOGRAM MANAGER                                           **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void MPAF::fill(string var, float valx, float weight) {
  /*
    fills a histogram (var) with a value (valx) that has a weight (weight)
    parameters: var, valx, weight
    return: none
  */
  const hObs* obs = _hm->getHObs(var);
  
  if(obs->IsGlobal()) {  
    // IF HISTOGRAM IS GLOBAL DO AS USUAL:
    if(!_uncId) { //central value
      if(_curWF!=-100) { //single workflow
	_hm->fill( var+_wfNames[_curWF], _inds, valx, weight );
      }
      else { //multiple workflows
	for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
	  _hm->fill( var+_itWF->second, _inds, valx, weight );
	}
      }
      
    }
    else {
      if(_uDir==SystUtils::kUp)
	_hm->fill( var, _inds, _unc, valx, weight,"Up");
      //fillUnc(var,_unc,valx,weight,"Up");
      if(_uDir==SystUtils::kDown)
	_hm->fill( var, _inds, _unc, valx, weight,"Do");
      //fillUnc(var,_unc,valx,weight,"Do");
    }
  }
  else {  //for local HISTOS
    if(!_uncId) { //central value
      _hm->fill( var, _inds, valx, weight );
    }
    else {
      if(_uDir==SystUtils::kUp)
	_hm->fill( var, _inds, _unc, valx, weight,"Up");
      //fillUnc(var,_unc,valx,weight,"Up");
      if(_uDir==SystUtils::kDown)
	_hm->fill( var, _inds, _unc, valx, weight,"Do");
    }
  }

}


//____________________________________________________________________________
void MPAF::fill(string var, float valx, float valy, float weight) {
  /*
    fills a histogram (var) with values (valx, valy) that have a weight (weight)
    parameters: var, valx, valy, weight
    return: none
  */
  const hObs* obs = _hm->getHObs(var);
  
  if(obs->IsGlobal()) {  
    // IF HISTOGRAM IS GLOBAL DO AS USUAL:
    if(_curWF!=-100) { //single workflow
    _hm->fill( var+_wfNames[_curWF], _inds, valx, valy, weight );
    }
    else { //multiple workflows
      for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
	_hm->fill( var+_itWF->second, _inds, valx, valy, weight );
      }
    }
  }
  else {
    // IF HISTOGRAM IS GLOBAL DO AS USUAL:
    _hm->fill( var, _inds, valx, valy, weight );
  }
}


//____________________________________________________________________________
void MPAF::fillUnc(string var, string unc, float val, float weight, string dir) {
  /*
    ??
    parameters: 
    return: 
  */

  if(_isData) return;

  if(_curWF!=-100) { //single workflow
    _hm->fill( var+_wfNames[_curWF], _inds, unc, val, weight,dir);
  }
  else { //multiple workflows
    for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
      _hm->fill( var+_itWF->second, _inds, unc, val, weight,dir);
    }
  }
}


//____________________________________________________________________________
void MPAF::fillUnc(string var, string unc, float val, float weight, float wup, float wdo) {
  /*
    ??
    parameters: 
    return: 
  */

  fill(var, _inds, val, weight);

    //_hm->fill(var, _inds, val, weight );

  if(!_isData ) {
    fillUnc( var, unc, val, wup, "Up");
    fillUnc( var, unc, val, wup, "Do");
    // _hm->fill( var, unc, val, wup, "Up");
    // _hm->fill( var, unc, val, wdo, "Do");
  }
}





/*****************************************************************************
******************************************************************************
** INTERFACE TO DATABASE MANAGER                                            **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
float MPAF::getDBVal(string db, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10) {
  /*
    ??
    parameters: 
    return: 
  */
  
  if(!_uncId)
    return _dbm->getDBValue( db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 );
  //MM fixme
  // else
  //   return applySystDBVar( _vc->_su->getSystInfos(_unc, _uDir), db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
  else
    return 0;
}


//____________________________________________________________________________
float MPAF::getDBErrL(string db, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10) {
  /*
    ??
    parameters: 
    return: 
  */

  return _dbm->getDBErrL( db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 );

}


//____________________________________________________________________________
float MPAF::getDBErrH(string db, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10) {
  /*
    ??
    parameters: 
    return: 
  */

  return _dbm->getDBErrH(db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 );

}


//____________________________________________________________________________
void MPAF::loadDb(string key, string dbfile, string hname) {
  /*
    ??
    parameters: 
    return: 
  */

  // ASCII database per definition
  if(hname == "") 
    _dbm->loadDb(key, dbfile);
  else
    _dbm->loadDb(key, dbfile, hname);

}


//____________________________________________________________________________
bool MPAF::makeCut(bool decision, string cName, string type, int eCateg) {
  /*
    ??
    parameters: 
    return: 
  */
  return _au->makeCut(decision, _inds , cName, _weight, type, eCateg+_offsetWF, false);

}


//____________________________________________________________________________
void MPAF::counter(string cName, int eCateg) {
  /*
    ??
    parameters: 
    return: 
  */
  _au->makeCut(true, _inds , cName, _weight, "=", eCateg+_offsetWF, false);

}

void 
MPAF::setWorkflow(int wf) {
  _curWF=wf;
  _au->setCurrentWorkflow(wf);
}

void 
MPAF::setMultiWorkflow(vector<int> wf) {
  //_curWF ?? would need a full loop everywhere...
  _au->setMultiWorkflow(wf);
}

// skimming functions ======================================
void MPAF::initSkimming() {
  
  string opath = string(getenv ("MPAF"))+"/workdir/skims";
  FILE* test = fopen( opath.c_str(), "r" );
  if( test == 0 ) {
    string command_ = "mkdir -p " + opath; 
    assert( system( command_.c_str() ) == 0 );
  }
  else
    fclose( test );

  _oFile = new TFile( (opath+"/"+_sampleName+".root").c_str(),"RECREATE");
  _datasets[_inds]->getTree()->LoadTree(0);
  if(_fullSkim) {
    _skimTree = (TTree*)_datasets[_inds]->getTree()->CloneTree(0);
    //for friend tree merging
    _vc->linkFriendBranches(_skimTree);

    _hnSkim =new TH1I( _hname.c_str(), _hname.c_str(), 1, 0, 1);
    _hnSkim->SetBinContent(1,_datasets[_inds]->getNProcEvents() );

    _hnwSkim =new TH1D( _hwgtname.c_str(), _hwgtname.c_str(), 1, 0, 1);
    _hnwSkim->SetBinContent(1,_datasets[_inds]->getSumProcWgts() );
  }
  else {
    TString name = _datasets[_inds]->getTree()->GetName();
    _skimTree = new TTree( name, name );
  }
  _skimTree->SetDirectory( _oFile );
  
  modifySkimming();
    
}

void MPAF::finalizeSkimming() {

  _oFile->cd();
  _skimTree->Write();
  if(_hnSkim)
    _hnSkim->Write();
  if(_hnwSkim)
    _hnwSkim->Write();
  _oFile->Write();
  _oFile->Close();
}

// Workflow functions =======================================

void
MPAF::addWorkflow(int wfid, string wfName) {

  _wfNames[wfid] = wfName;
  _au->addWorkflow(wfid, wfName);
} 

void
MPAF::addWorkflowHistos() {

  if(_wfNames.size()==1) return;

  vector<string> obss = _hm->getObservables(true);
  
  for(unsigned int io=0;io<obss.size();io++) {
    const hObs* obs = _hm->getHObs(obss[io]);
    bool prof = obs->htype.find("P")!=string::npos;
    bool is2D = obs->htype.find("2D")!=string::npos;

    if (!obs->IsGlobal()) continue;  // don't declare histo if it's not declared as global

    for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
      if(_itWF->second=="") continue; //protection for global histo
      _hm->addVariableFromTemplate( obs->name+_itWF->second, obs->hs[0], prof, is2D, obs->type );
    }
  }  
}


// systematic uncertainties functions =======================

void
MPAF::addManualSystSource(string name, int dir) {
  //everything has to be done by hand
  addWSystSource(name, dir, "+", 0); 
}

void
MPAF::addWSystSource(string name, int dir, string type, float val) {
  vector<string> t;
  addSystSource(name, dir, type, t, val, true);
}

void
MPAF::addWSystSource(string name, int dir, string type, string db, string hname) {
  vector<string> t;
  addSystSource(name, dir, type, t, db, hname, true);
}

void
MPAF::addSystSource(string name, int dir, string type, vector<string> modVar,
			     float val, bool wUnc) {

  _au->addAutoWorkflow( "Unc"+name+"Up");
  _au->addAutoWorkflow( "Unc"+name+"Do");
  _uType[ name ] = wUnc;

  //check the direction
  if(dir!=SystUtils::kNone) {
    _uncSrcs.push_back(name);
    _uncDirs.push_back(dir);
    _vc->_su->addSystSource(name, dir, type, modVar, val);
  }
  else {
    //up variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kUp);
    _vc->_su->addSystSource(name, SystUtils::kUp, type, modVar, val);

    //down variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kDown);
    _vc->_su->addSystSource(name, SystUtils::kDown, type, modVar, val);
  }

}

void
MPAF::addSystSource(string name, int dir, string type, vector<string> modVar,
		    string db, string hname, bool wUnc) {
  
  _au->addAutoWorkflow( "Unc"+name+"Up");
  _au->addAutoWorkflow( "Unc"+name+"Do");
  _uType[ name ] = wUnc;

  //check the direction
  if(dir!=SystUtils::kNone) {
    _uncSrcs.push_back(name);
    _uncDirs.push_back(dir);
    _vc->_su->addSystSource(name, dir, type, modVar, db, hname);
  }
  else {
    //up variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kUp);
    _vc->_su->addSystSource(name, SystUtils::kUp, type, modVar, db, hname);
    
    //down variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kDown);
    _vc->_su->addSystSource(name, SystUtils::kDown, type, modVar, db, hname);
  }

}



void
MPAF::applySystVar(SystST s) {

  //weight variation, MM: incomplete ===========================
  // if(_uType[ _unc ]) {
  //   if(s.val!=-100) {
  //     //fixed variation
  //     SystUtils::systOp<float>(_unc, _uDir, s.type, _weight,  s.val );
  //   }  
  //   else {
  //     //db variation
  //     SystUtils::systOp<float>(_unc, _uDir, s.type, _weight, s.db, s.vars);
  //   }
  //   return;
  // }
  
  // variable variation =======================================
  if(s.val!=-100) {
    //fixed variation
    for(size_t iv=0;iv<s.modVar.size();iv++) //loop over variables
      _vc->applySystVar(_unc, _uDir, s.modVar[iv], s.val, s.type);
  }
  else {
    //db variation
    for(size_t iv=0;iv<s.modVar.size();iv++) //loop over variables
      _vc->applySystVar(_unc, _uDir, s.modVar[iv], s.vars, s.specVars, s.db, s.type);
  }

}

