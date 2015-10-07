#include "core/MPAFDisplay.hh"

ClassImp(MPAFDisplay)

using namespace std;

MPAFDisplay::MPAFDisplay() {

  _hm=new HistoManager();
  _dbm=new DataBaseManager();
  _au=new AnaUtils();
  _recompute=true;
}

MPAFDisplay::~MPAFDisplay() {
  reset();
  delete _hm;
}


void
MPAFDisplay::configure() {
  _dsNames = anConf.getDSNames();
 
  _hm->configAnalysis(_dsNames );
  
  for(size_t ids=0;ids<_dsNames.size();ids++) {
    dp.configure(_dsNames[ids], 
		 anConf.getDataset(_dsNames[ids])->getColor(),
		 anConf.getDataset(_dsNames[ids])->isGhost() );
    //Default, weight=1 for anyone
    dp.setWeight( _dsNames[ids], 1. );
  }

}

void
MPAFDisplay::reset() {
  _hm->reset();
  //  dp.reset();
  //  anConf.reset(); 
  //  _au->reset();
}




void 
MPAFDisplay::drawStatistics(string categ, string cname, bool multiScheme, bool vetoOpt, string opt){

  int scheme=AnaUtils::kGeneral;
  if(multiScheme) scheme=AnaUtils::kMulti;
  if(multiScheme && vetoOpt) scheme=AnaUtils::kMultiVeto;
  
  vector< pair<string, vector<vector<float> > > > numbers = _au->retrieveNumbers(categ,  cname, scheme, opt);
  
  vector<string> dsNames = _dsNames;
  dsNames.insert(dsNames.begin(), "MC");

  dp.drawStatistics( numbers, dsNames, (multiScheme && !vetoOpt && opt!="") );
}


void
MPAFDisplay::getStatistics(string categ) {
  _au->printTables(categ);
}


void
MPAFDisplay::getDetailSystematics(string categ, string lvl) {
  
  for(size_t id=0;id<_dsNames.size();id++) {
    _au->getSystematics(_dsNames[id], lvl, categ);
  }

}

void
MPAFDisplay::getCategSystematic(string src, string categ, string lvl, bool latex) {
 
  for(size_t id=0;id<_dsNames.size();id++) {
    _au->getCategSystematics(_dsNames[id],src, lvl, categ, latex);
  }

}


void 
MPAFDisplay::setNumbers() {
  if(!_recompute) return;
  
  for(size_t id=0;id<_dsNames.size();id++) {
    _au->addDataset(_dsNames[id]);
  }
  
  vector<string> statFiles = anConf.getObjList();
  string ctag = "";
  
  _sfVals.clear();
  _au->init();
  _au->addCategory( AUtils::kNominal, "nominal");
  int icat=2; //0 for global, 1 for nominal
  
  for(int i=(int)(statFiles.size())-1; i>=0; i--) {
    readStatFile( statFiles[i], icat);
  }

  //associate the systematic uncertainties to the proper categories
  associateSystUncs();

}

void
MPAFDisplay::readStatFile(string filename, int& icat) {
  
  if(filename=="") return;
 
  
  string ndb = filename;
  ifstream fDb( ndb.c_str(), ios::in );
  
  if(fDb)  {
    string line;
    
    string categ;
    string cname;
    string sname;
    string ext;
    string uncTag;
    float yield, eyield;
    int gen;
    
    vector<Dataset*> dss;
    vector<Dataset*> extDss;
   
    int upVar=SystUtils::kNone;
     
    while(getline(fDb, line)) {
	
      istringstream iss(line);
      vector<string> tks;
      copy(istream_iterator<string>(iss),
           istream_iterator<string>(),
           back_inserter<vector<string> >(tks));

   
      if(tks.size()==0 || line == "") continue; 
      
      //counters FIXME, done with rootfile for the moment
       if(tks[0]=="dsCnts" || tks[0]=="cnts" || tks[0]=="wgts" ) {
	 continue;
       }
       
      if(tks[0]=="categ") {
        categ="";
	ext="";
	
	
	for(size_t i=1;i<tks.size();i++) { //prevent from spaces in categ names
	  if(tks[i].find("Unc")!=string::npos) {
	    uncTag=tks[i].erase(0,3);
	    if(uncTag.find("Up")!=string::npos || uncTag.find("Do")!=string::npos)
	      uncTag=uncTag.substr(0, uncTag.size()-2  );
	    upVar=(tks[i].find("Up")==string::npos)?((tks[i].find("Do")==string::npos)?SystUtils::kNone:SystUtils::kDown):(SystUtils::kUp);
	  
	    break;
	  }
	  categ +=tks[i];
	}

	if(categ!="global" || uncTag!="") {
	  if(uncTag!="")
	    _au->addCategory(icat, categ);
	  else
	    _au->addCategory(icat, categ, uncTag);
	} 
        else {
	  icat=0;
	}
      }
      else if(tks[0]=="endcateg") { //fill the maps
	if(icat==0) icat +=2; // 1 is nominal
        else icat++;
      }
      else if(tks[0]=="selection") continue;
 
      else {
	
        size_t n=tks.size()-4;
        cname="";
        for(size_t i=0;i<n-1;i++)
          cname += tks[i]+" ";
	    cname += tks[n-1];

        sname = tks[n];
	if(categ.find("global_")!=string::npos) ext = categ.substr(7, categ.size()-7);
    	if(ext=="") {
	  dss=anConf.findDSS( sname );
	  //extDs=nullptr;
	}
	else {
	  dss=anConf.findDSS( sname );
	  //extDs=anConf.findDS( sname, ext );
	  extDss=anConf.findDSS( sname, ext );

	  //fixme, for cards need to overwrite the yields in the main category...
	  //dss=anConf.findDSS( sname );
	}
	//if(ds==nullptr) continue;
	
        yield  = atof( tks[n+1].c_str() );
        gen = atoi( tks[n+2].c_str() );
        eyield = atof( tks[n+3].c_str() );

	for(unsigned int i=0;i<dss.size();i++) {
	  //  cout<<"std ds "<<dss[i]->getName()<<"   "<<cname<<"   "<<sname<<"   "<<categ<<endl;
	  storeStatNums(dss[i], yield, eyield, gen, icat, cname, sname,
			categ, uncTag, upVar, ext);
	}

	//if(extDs==nullptr) continue;
	for(unsigned int i=0;i<extDss.size();i++) {
	  //cout<<"ext ds "<<extDss[i]->getName()<<"   "<<cname<<"   "<<sname<<"   "<<categ<<endl;
	  storeStatNums(extDss[i], yield, eyield, gen, icat, cname, sname, categ,
		      uncTag, upVar, ext);
	}
      }

    }
    fDb.close();
  }
  else {
    cout<<"Warning, statistics file "<<filename<<" not loaded"<<endl;
  }

}


void
MPAFDisplay::storeStatNums(const Dataset* ds, float yield, float eyield, int gen,
			   int icat, string cname, string sname, string categ,
			   string uncTag, int upVar, string ext) {

  int idx=-1;
  for(size_t id=0;id<_dsNames.size();id++ ) {
    if(ds!=nullptr && _dsNames[id]==ds->getName() ) {
      idx = id+1; 
      break;
    }
  }

  float w = ds->getWeight(sname)*anConf.getLumi();
  //cout<<idx<<"   "<<_dsNames.size()<<endl;
  // if(cname=="selected" && ext=="SR1A")
  //   cout<<idx<<"  "<<ds->getName()<<"  "<<_dsNames[idx-1]<<"   "<<w<<"   "<<yield<<" -> "<<yield*w<<"  "<<eyield/yield<<"   ->>> "<<ext<<"   "<<categ<<endl;
  yield *=w;
  eyield *=w;
 
  string var=(upVar==SystUtils::kUp)?"Up":"Do";
  std::pair<string,string> p(ds->getName(), cname+sname+categ+uncTag+var);
  if(_sfVals.find(p)!=_sfVals.end() ) return;
  _sfVals[p]=true;
  if(idx==-1) return;
  
  if(uncTag=="")
    _au->setEffFromStat(idx,cname,icat,yield,eyield,gen);
  else {
    //to store separately the unc yields
    //_au->setEffFromStat(idx,cname,icat,yield,eyield,gen);
    icat = _au->getCategId(categ);
    _au->setSystematics(idx, cname, icat, uncTag, upVar!=SystUtils::kDown,
			upVar!=SystUtils::kUp, yield);
  }  

  //nominal category ===================
  //identified category for nominal
  if( ds->getSample(sname)->getCR()!=ext ) return; 
  if(uncTag=="")
    _au->setEffFromStat(idx,cname,AUtils::kNominal,yield,eyield,gen);
  else 
    _au->setSystematics(idx, cname, AUtils::kNominal,uncTag,
			upVar!=SystUtils::kDown , upVar!=SystUtils::kUp, yield);
}

void
MPAFDisplay::associateSystUncs() {



}



void
MPAFDisplay::prepareDisplay(){

  configure();
  dp.setLumi( anConf.getLumi() );
  setNumbers();

}


void
MPAFDisplay::doPlot() {

  setHistograms();

  //See if a fit is needed for the normalization
  //ugly....
  string fitVar=dp.getFitVar();
  if(fitVar!="") {
    const hObs* wobs = _hm->getHObs( fitVar );
    if( wobs!=NULL)
      dp.initWeights(wobs); 
    else
      cout<<" Error, no observable of name : "<<fitVar<<" for fitting "<<endl;
  }
  
  //Find the observables and draw them
  //could be done in a better way...
  vector<string> obs_ = dp.getObservables();
  vector<const hObs*> Obs_;
  vector<vector<systM> > systs_;
  
  for(size_t io = 0; io < obs_.size(); ++io) {
    _currentObs = obs_[io];

    if( _hm->getHObs( obs_[io] )==NULL) {
      cout<<" Error, no observable of name : "<<obs_[io]<<endl;
      continue;
    }

    Obs_.push_back( _hm->getHObs( obs_[io] ) );
    systs_.push_back( _hm->getSystObs( obs_[io] ) );
  }  
  
  if(Obs_.size()!=0) {
    dp.setSystematicsUnc( systs_ );
    dp.plotDistributions( Obs_ );
  }

  _recompute=false;

}


void
MPAFDisplay::setHistograms() {

  //loop over the datasets, find the histograms, sum them
  // and store them into the HistoManager

  //do not need to reload everything at each iteration, but let's do it for the moment
  //  if(!_recompute) return;

  for(size_t ids=0;ids<_dsNames.size();ids++) {
    
    _ids = _dsNames[ids];
    _inds = ids;

    Dataset* ds=anConf.getDataset( _ids );
    string tmpDs= _ids;
    
    vector<string> obss = ds->getObservables();
    for(size_t io=0;io<obss.size();io++) {
      TH1* htmp(0);
      vector<string> samples= ds->getSamples();
      for(size_t is=0;is<samples.size(); is++) {
	float w = ds->getWeight(is);
	
	if(ds->getSample(samples[is])->isNorm()) {
	  w=ds->getSample(samples[is])->getNorm()/(anConf.getLumi()*ds->getHisto( obss[io], samples[is] )->Integral(0,1000000));
	} 
	
	if(is==0) {
	  htmp = ds->getHisto( obss[io], samples[is] );
	  htmp->Scale( w );
    }
	else {
	  htmp->Add( ds->getHisto( obss[io], samples[is] ), w);
    }
      } 

      _hm->copyHisto( obss[io] , _inds, htmp );
      delete htmp;
    
    }

  }//datasets

  //keep for later ideas for uncertainties
  // TH1* htmp(0); 
  // for(size_t ih=0;ih<ah.getNHistos();ih++) {
  //   htmp = ah.getHistogram(ih);
    
  //   _inds = anConf.findChan( htmp->GetName() );
    
  //   bool isUnc=((string)htmp->GetName()).find("Unc")!=(size_t)-1;
  //   if(isUnc) _hm->copyHisto( ah.getVar(), -10, htmp, ah.getXtitle() );
  //   if(_inds==-1) continue;
  //   _hm->copyHisto( ah.getVar(), _inds, htmp, ah.getXtitle() );
    
  // }
  // delete htmp;

  //  _recompute=false;

}


void
MPAFDisplay::drawRatio(string o1, string o2 ) {

  vector<const hObs*> Obs_;
  // vector<vector<systM> > systs_;
  
  Obs_.push_back( _hm->getHObs( o1 ) );
  Obs_.push_back( _hm->getHObs( o2 ) );

  if( Obs_[0]==NULL) {
    cout<<" Error, no observable of name : "<<o1<<endl;
    return;
  }
  if( Obs_[1]==NULL) {
    cout<<" Error, no observable of name : "<<o2<<endl;
    return;
  }

  // systs_.push_back( _hm->getSystObs( o1 ) );
  // systs_.push_back( _hm->getSystObs( o2 ) );
  
  //dp.setSystematicsUnc( systs_ );
  dp.ratioObservables( Obs_ );

}


void
MPAFDisplay::drawResiduals(string o1) {
  const hObs* Obs_;
  vector<vector<systM> > systs_;

  Obs_ =  _hm->getHObs( o1 );
  systs_.push_back( _hm->getSystObs( o1 ) );
  dp.setSystematicsUnc( systs_ );
  dp.residualData( Obs_ );
}

void
MPAFDisplay::drawSignificance(string o1) {
  const hObs* Obs_;
  vector<vector<systM> > systs_;

  Obs_ =  _hm->getHObs( o1 );

  if( Obs_==NULL) {
    cout<<" Error, no observable of name : "<<o1<<endl;
    return;
  }
  
  dp.showSignificance( Obs_ );
}

void
MPAFDisplay::drawCumulativePlots(string o1) {
  const hObs* Obs_;
  vector<vector<systM> > systs_;

  Obs_ =  _hm->getHObs( o1 );

  if( Obs_==NULL) {
    cout<<" Error, no observable of name : "<<o1<<endl;
    return;
  }
  
  dp.drawCumulativeHistos( Obs_ );
}

void
MPAFDisplay::drawEfficiencies(string o1) {
  const hObs* Obs_;
  
  Obs_ =  _hm->getHObs( o1 );

  if( Obs_==NULL) {
    cout<<" Error, no observable of name : "<<o1<<endl;
    return;
  }
  
  dp.drawEfficiency( Obs_ );
}


void
MPAFDisplay::drawROCcurves(string o1) {
  const hObs* Obs_;
  
  Obs_ =  _hm->getHObs( o1 );

  if( Obs_==NULL) {
    cout<<" Error, no observable of name : "<<o1<<endl;
    return;
  }
  
  dp.drawROCCurves( Obs_ );
}


void
MPAFDisplay::multiROCcurves() {
  vector<const hObs*> Obs_;
  vector<string> obs_ = dp.getObservables();
  
  for(size_t io=0;io<obs_.size();io++) {
    if( _hm->getHObs( obs_[io] )==NULL) {
      cout<<" Error, no observable of name : "<<obs_[io]<<endl;
      continue;
    }
    
    Obs_.push_back( _hm->getHObs( obs_[io] ) );
  }  
  
  dp.compaROCCurves( Obs_ );
}

void
MPAFDisplay::saveHistos(string o1) {
  const hObs* Obs_;
  Obs_ =  _hm->getHObs( o1 );

  if( Obs_==NULL) {
    cout<<" Error, no observable of name : "<<o1<<endl;
    return;
  }
   
  dp.saveHistos(o1, Obs_);

}

void
MPAFDisplay::saveDataMCRatio(string fname,string hname) {
  dp.saveDMCRWeight(fname,hname);
}


void
MPAFDisplay::savePlot(string path, string advname) {
  _hm->savePlots(path, dp.getCanvas(), advname);
  //save
}

void
MPAFDisplay::producePlots(string path) {
  
  gROOT->SetBatch(kTRUE);

  //vector<string> obss = _hm->getObservables();
  vector<string> obss = dp.getAutoVars();

  for(size_t is=0;is<obss.size();is++) {

    refresh();
    dp.setObservables( obss[is] );
    doPlot();
    savePlot(path);
  }
  gROOT->SetBatch(kFALSE);
}

void
MPAFDisplay::drawDetailSyst(bool cumul) {
  vector<vector<systM> > systs_;
  systs_.push_back( _hm->getSystObs( _currentObs ) );
  dp.setSystematicsUnc( systs_ );
  dp.drawDetailSystematics( cumul );
}

void
MPAFDisplay::getIntegral(float x1, float x2, float y1, float y2) {
  dp.getIntegral(x1, x2, y1, y2);
}

void
MPAFDisplay::refresh() {
  dp.reset();
  anConf.reset();
  _hm->reset();
}



vector<string> 
MPAFDisplay::split(const string& s, char delim) {

  vector<string> elems;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (!item.empty())
      elems.push_back(item);
  }
  return elems;
}

string
MPAFDisplay::findDiff(const string& s1, const string& s2,
		      char delim, size_t& bl, size_t& bh) {

  vector<string> sel1 = split(s1, delim);
  vector<string> sel2 = split(s2, delim);

  if(sel1.size() != sel2.size() ) {
    bl = 0;
    bh = sel1.size()-1;
    return s2;
  }

  string diff="";
  for(size_t ie=0;ie<sel1.size();ie++) {
    if(sel1[ie]==sel2[ie]) continue;

    diff += sel2[ie];
    bl = s1.find(sel1[ie]);
    bh = bl + sel1[ie].size();
  }
  
  return diff;
}

//==============================================================================
//datacard stuff================================================================

void
MPAFDisplay::addDataCardSample(string sName, string dsName) {
  
  _isSigDs[dsName]=false;
  if(dsName.find("data")!=string::npos) _isSigDs[dsName]=true;

  anConf.addSample(sName, dsName, 0, false);
}

void
MPAFDisplay::addDataCardSigSample(string sName, string dsName) {
  
  _isSigDs[dsName]=true;
  anConf.addSample(sName, dsName, 0);
}


void
MPAFDisplay::addNuisanceParameter(string npName, string dss, string scheme,  string vals) {
  
  //name parsing
  vector<string> dsList;
  size_t p=0;
  while(p!=string::npos) {
    size_t pi=dss.find(":",p);
    if(p==0) dsList.push_back( dss.substr(p,pi) );
    if(pi==string::npos) break;
    
    p = dss.find(":",pi+1);
    if(p==string::npos) {
      dsList.push_back( dss.substr(pi+1,dss.size()-pi-1 ) );
    } else {
      dsList.push_back( dss.substr(pi+1,p-pi-1 ) );
    }
  }
  
  _nuisPars[ npName ] = dsList;
  _nuisParScheme[ npName ] = scheme;
  _nuisParExt[ npName ]=false;

  if(vals=="") return;  

  //val parsing, external uncertainties ============================
  vector<string> valList;
  p=0;
  while(p!=string::npos) {
    size_t pi=vals.find(":",p);
    if(p==0) valList.push_back( vals.substr(p,pi) );
    if(pi==string::npos) break;    

    p = vals.find(":",pi+1);
    if(p==string::npos) {
      valList.push_back( vals.substr(pi+1,vals.size()-pi-1 ) );
    } else {
      valList.push_back( vals.substr(pi+1,p-pi-1 ) );
    }
  }
  //cout<<npName<<"   "<<valList.size()<<"   "<<dsList.size()<<"   "<<dsList[0]<<endl;
  _nuisParVals[ npName ] = valList;
  _nuisParExt[ npName ]=true;
}


vector<string>
MPAFDisplay::getExternalNuisanceParameters(string sigName) {
  
  //matching values
  vector<string> lines;
  //cout<<" ============================================== "<<_nuisParVals.size()<<endl;
  for(_itNp=_nuisParVals.begin();_itNp!=_nuisParVals.end();++_itNp) {
    string line="";
    int nd=0;
    for(unsigned int ids=0;ids<_dsNames.size();ids++) {
      if(_dsNames[ids]=="data") continue;
      if( find( _nuisPars[_itNp->first].begin(), _nuisPars[_itNp->first].end(), _dsNames[ids] )==_nuisPars[_itNp->first].end() ) {
	if(_dsNames[ids]!=sigName) {
	  line += "-\t";
	}
	else {
	  line = _itNp->first+"\t"+_nuisParScheme[_itNp->first]+"\t-\t"+line; //\t-
	}
      }
      else {
	if(_dsNames[ids]!=sigName) {
	  line += _itNp->second[nd]+"\t";
	}
	else {
	  line = _itNp->first+"\t"+_nuisParScheme[_itNp->first]+"\t"+_itNp->second[nd]+"\t"+line;
	}
	nd++;
      }
    } 
    lines.push_back(line);
  }
  return lines;
}


void
MPAFDisplay::makeSingleDataCard(string sigName, string categ, string cname, string cardName) {
  
  map<string,string> lines;
  bool isValidCard = _au->getDataCardLines(lines, _dsNames, sigName, categ, cname, 1, _nuisPars, _nuisParExt);

  if(!isValidCard) { 
    cout<<"Current datacard contains a null background+signal yield,"<<endl
	<<" card will not be readable by the Higgs Combination tool"<<endl;
    return;
  }

  //get all numbers =====
  int nBkgs=0;
  for(map<string,bool>::const_iterator it=_isSigDs.begin();it!=_isSigDs.end();++it) {
    if(!it->second) nBkgs++;
  }
  ostringstream osB; osB<<nBkgs;
  //int nNuis=_nuisPars.size();
  
  string dirname_ = (string)(getenv("MPAF"))+"/workdir/datacards/";
  ofstream card( (dirname_+cardName+".txt").c_str() , ios::out | ios::trunc );
  
  card<<"imax 1 number of channels"<<endl; 
  //card<<"jmax "+osB.str()+" number of backgrounds"<<endl; 
  card<<"jmax * number of backgrounds"<<endl; 
  card<<"kmax * number of nuisance parameters"<<endl; 
  card<<"---------------------------"<<endl; 
  card<<"bin\t1"<<endl;
  card<<"observation\t"<<lines["dataYield"]<<endl;
  card<<"---------------------------"<<endl; 
  card<<"bin\t\t"<<lines[ "bins" ]<<endl;
  card<<"process\t\t"<<lines[ "procNames" ]<<endl;
  card<<"process\t\t"<<lines[ "procNums" ]<<endl;
  card<<"rate\t\t"<<lines[ "yields" ]<<endl;
  card<<"---------------------------"<<endl; 

  // internal uncertainties ================================
  for(map<string,string>::const_iterator itU=lines.begin();itU!=lines.end();++itU) {
    if(itU->first.substr(0,2)!="NP") continue;
    if(_nuisParVals.find(itU->first.substr(3, itU->first.size()-3))!=_nuisParVals.end() ) continue;
    string name=itU->first.substr(3,itU->first.size()-3);
    //cout<<name<<"   "<<itU->second<<endl;
    card<<itU->second<<endl;
  }
  
  //external uncertainties =================================
  vector<string> extNuisParLines=getExternalNuisanceParameters(sigName);
  for(size_t ip=0;ip<extNuisParLines.size();ip++) {
    card<<extNuisParLines[ip]<<endl;
  }

  card.close();

}
