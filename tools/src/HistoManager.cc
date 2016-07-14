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

#include "HistoManager.hh"

using namespace std;

ClassImp(HistoManager)




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
HistoManager::HistoManager() {
  /*
    constructs the HistoManager class
    parameters: none
    return: none
  */

  //TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);	
  TH1::SetDefaultSumw2(true);

}


//____________________________________________________________________________
HistoManager::~HistoManager() {
  /*
    destructs the HistoManager class
    parameters: none
    return: none
  */

}


//initilaization
//____________________________________________________________________________
void HistoManager::configAnalysis(vector<string> datasets) {

  _dsNames = datasets;
  _nds = datasets.size(); 

}


//add dataset
//____________________________________________________________________________
void HistoManager::addDataset(string dsname) {

  _dsNames.push_back(dsname);
  _nds = _dsNames.size();

}


//Histogram access and booking
//____________________________________________________________________________
void HistoManager::addVariable(string var, int nBin, float min, float max, string Xleg, bool isglb, bool prof, string type) {

  //Protection against overdeclaration
 
  _itVar = _variables.find(var);
  if(_itVar!=_variables.end()) {
    cout<<" Take care : "<< var <<" already declared "<<endl;
    return;
  }

  vector<float> bins(2,-1);
  bins[0] = min; bins[1] = max;
  hObs tmp;
  tmp = preparehObs(var, nBin, bins, Xleg,"", type, isglb, prof);
  _variables[ var ]= tmp;
  
}


//____________________________________________________________________________
void HistoManager::addVariable(string var, int nBin, vector<float> bins, string Xleg, bool isglb, bool prof, string type) {
  
  //Protection against overdeclaration
  _itVar = _variables.find(var);
  if(_itVar!=_variables.end()) {
    cout<<" Take care : "<< var <<" already declared "<<endl;
    return;
  }

  hObs tmp;
  tmp = preparehObs( var, nBin, bins, Xleg,"", type, isglb, prof);
  _variables[ var ]= tmp;
 
}

//____________________________________________________________________________
void
HistoManager::addVariable(string var, int nBinX, float minX, float maxX, int nBinY, float minY,
			  float maxY, string Xleg, string Yleg, bool isglb, bool prof, string type) {

  //Protection against overdeclaration
  _itVar = _variables.find(var);
  if(_itVar!=_variables.end()) {
    cout<<" Take care : "<< var <<" already declared "<<endl;
    return;
  }

  vector<float> binsX(2,-1);
  vector<float> binsY(2,-1);

  binsX[0]=minX; binsX[1]=maxX;
  binsY[0]=minY; binsY[1]=maxY;

  hObs tmp;
  tmp = preparehObs(var, nBinX, binsX, Xleg,Yleg, type, isglb, prof, nBinY, binsY);
  _variables[ var ]= tmp;

}

//____________________________________________________________________________
void
HistoManager::addVariableFromTemplate(string var, TH1* h,  bool prof, 
				      bool is2D, string type) {

  //Protection against overdeclaration
  _itVar = _variables.find(var);
  if(_itVar!=_variables.end()) {
    cout<<" Take care : "<< var <<" already declared "<<endl;
    return;
  }
  hObs tmp;
  tmp = preparehObsFromTemplate(var, h, prof, is2D, type);
  _variables[ var ]= tmp;
}

//____________________________________________________________________________
void
HistoManager::addVariable(string var, int nBinX, vector<float> binsX, int nBinY,
			  vector<float> binsY, string Xleg, string Yleg,
			  bool isglb, bool prof, string type) {

  //Protection against overdeclaration
  _itVar = _variables.find(var);
  if(_itVar!=_variables.end()) {
    cout<<" Take care : "<< var <<" already declared "<<endl;
    return;
  }
  hObs tmp;
  tmp = preparehObs(var, nBinX, binsX, Xleg, Yleg, type, isglb, prof, nBinY, binsY);
  _variables[ var ]= tmp;

}



//____________________________________________________________________________
hObs HistoManager::preparehObs(string var, int nbinsX, vector<float> bins, string Xleg,
			       string Yleg, string type, bool isglb, bool prof, int nbinsY, vector<float> binsY ) {
  
  bool twoDim = (nbinsY != -1);
	
  hObs otmp;
	  
  otmp.nBX = nbinsX;
  otmp.nBY = nbinsY;
  otmp.binsX = bins;
  otmp.binsY = binsY;
	
  otmp.titleX = Xleg;
  otmp.titleY = Yleg;
  otmp.name = var;
  otmp.type = type;
  otmp.SetGlobal(isglb);
  otmp.htype = (prof?(twoDim?"2DP":"1DP"):(twoDim?"2D":"1D"));
	
  for(size_t id=0;id<_nds;id++) {
	
    string nameH = var + "_" + _dsNames[id];
    otmp.hs.push_back(NULL);
	
    // normal histos, no profiles	
    if(!prof) {

      // one dimensional
      if(!twoDim) {

	// no var bin
	if(bins.size() == 2) { 
	  TH1F* htmp = new TH1F(nameH.c_str(), var.c_str(), nbinsX, bins[0], bins[1]);
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  otmp.hs[id] = (htmp);
	}
	else {
	  float tmpB[ bins.size() ];
	  for(size_t ib = 0; ib < bins.size(); ++ib)
	    tmpB[ib] = bins[ib];
	  TH1F* htmp = new TH1F(nameH.c_str(), var.c_str(), nbinsX, tmpB);
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  otmp.hs[id] = (htmp);
	}
      }

      // two dimensional
      else {
	if(bins.size()==2) { //no var Bin
	  TH2F* htmp=new TH2F(nameH.c_str(), var.c_str(), nbinsX, bins[0], bins[1], nbinsY, binsY[0], binsY[1] );
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  htmp->GetYaxis()->SetTitle( Yleg.c_str() );
	  otmp.hs[id]=(htmp);
	}
	else {
	 
	  float* tmpBX= new float[ bins.size() ];
	  for(size_t ib=0;ib<bins.size();ib++) tmpBX[ib]=bins[ib];
	  float* tmpBY= new float[ binsY.size() ];
	  for(size_t ib=0;ib<binsY.size();ib++) tmpBY[ib]=binsY[ib];

	  TH2F* htmp=new TH2F(nameH.c_str(), var.c_str(), nbinsX, tmpBX, nbinsY, tmpBY);
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  htmp->GetYaxis()->SetTitle( Yleg.c_str() );
	  otmp.hs[id]=(htmp);

	  delete tmpBX;
	  delete tmpBY;
	}
      }
    } // now profile
    else {
      if(!twoDim) {
	if(bins.size()==2) { //no var Bin
	  TProfile* htmp=new TProfile(nameH.c_str(), var.c_str(), nbinsX, bins[0], bins[1]);
	  otmp.hs[id]=(htmp);
	}
	else {
	  float tmpB[ bins.size() ];
	  for(size_t ib=0;ib<bins.size();ib++) tmpB[ib]=bins[ib];
	  TProfile* htmp=new TProfile(nameH.c_str(), var.c_str(), nbinsX, tmpB);
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  otmp.hs[id]=(htmp);
	}
      }
      else { //two dim histos
	if(bins.size()==2) { //no var Bin
	  TProfile2D* htmp=new TProfile2D(nameH.c_str(), var.c_str(), nbinsX, bins[0], bins[1], nbinsY, binsY[0], binsY[1] );
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  otmp.hs[id]=(htmp);
	}
	else {
	  double* tmpBX= new double[ bins.size() ];
	  for(size_t ib=0;ib<bins.size();ib++) tmpBX[ib]=bins[ib];
	  double* tmpBY= new double[ binsY.size() ];
	  for(size_t ib=0;ib<binsY.size();ib++) tmpBY[ib]=binsY[ib];
	  TProfile2D* htmp=new TProfile2D(nameH.c_str(), var.c_str(), nbinsX, tmpBX, nbinsY, tmpBY);
	  htmp->GetXaxis()->SetTitle( Xleg.c_str() );
	  htmp->GetYaxis()->SetTitle( Yleg.c_str() );
	  otmp.hs[id]=(htmp);

	  delete tmpBX;
	  delete tmpBY;
	}
      }//2D histos
    } //profile
    
  }// number ds
  
  return otmp;

}


//____________________________________________________________________________
hObs HistoManager::preparehObsFromTemplate(string var, TH1* h, bool prof, bool is2D, string type ) {


  bool twoDim = is2D;
  hObs otmp;
	  
  otmp.titleX = h->GetXaxis()->GetTitle();
  otmp.titleY = h->GetYaxis()->GetTitle();
  otmp.name  = var;
  otmp.type  = type;
  otmp.SetGlobal(false);
  otmp.htype = (prof?(twoDim?"2DP":"1DP"):(twoDim?"2D":"1D"));
	
  for(size_t id=0;id<_nds;id++) {
	
    string nameH = var + "_" + _dsNames[id];
    otmp.hs.push_back(NULL);
	
    // normal histos, no profiles
    if(!prof) { 

      // one dimensional
      if(!twoDim) {
	TH1F* htmp = (TH1F*) h->Clone(); 
	htmp->Reset("ICEM");
	htmp->SetName( nameH.c_str() );
	htmp->SetTitle( var.c_str() );
	otmp.hs[id] = (htmp);
      }
  
      // two dimensional
      else { 
	TH2F* htmp = (TH2F*) h->Clone(); 
	htmp->Reset("ICEM");
	htmp->SetName( nameH.c_str() );
	htmp->SetTitle( var.c_str() );
	otmp.hs[id] = (htmp);
      }
    } 

    // profile histos
    else {

      // one dimensional
      if(!twoDim) {
	TProfile* htmp = (TProfile*) h->Clone(); 
	htmp->Reset("ICEM");
	htmp->SetName( nameH.c_str() );
	htmp->SetTitle( var.c_str() );
	otmp.hs[id] = (htmp);
      }

      // two dimensional
      else {
	TProfile2D* htmp = (TProfile2D*) h->Clone(); 
	htmp->Reset("ICEM");
	htmp->SetName( nameH.c_str() );
	htmp->SetTitle( var.c_str() );
	otmp.hs[id] = (htmp);
      }
    } 
  }
  
  vector<float> tmp;
  otmp.nBX   = otmp.hs[0]->GetNbinsX();
  otmp.nBY   = twoDim?otmp.hs[0]->GetNbinsY():0;
  otmp.binsX = HistoUtils::getXbinning(otmp.hs[0]);
  otmp.binsY = twoDim?(HistoUtils::getYbinning( ((TH2*)otmp.hs[0]))):tmp;
	
  return otmp;

}


//____________________________________________________________________________
TH1* HistoManager::getHisto(string obs, int ds) {

  _cItVar = _variables.find(obs);

  if( _cItVar != _variables.end() ) {	

    if( _cItVar->second.type != "u" )
      _hname = _cItVar->second.name;
	
    return _cItVar->second.hs[ds];
  }
  return NULL;

}


//____________________________________________________________________________
const hObs* HistoManager::getHObs(string obs) {
 
  _cItVar = _variables.find(obs);

  if( _cItVar != _variables.end() ) {	
    if( _cItVar->second.type != "u" )
      _hname = _cItVar->second.name;
    return &(_cItVar->second);
  }

  return NULL;
}


//____________________________________________________________________________
vector<string> HistoManager::getObservables(bool allObs) {

  vector<string> names;
  for(_cItVar = _variables.begin(); _cItVar != _variables.end(); ++_cItVar)
    if(allObs || _cItVar->second.type != "u" )
      names.push_back( _cItVar->first );

  return names;
}


//____________________________________________________________________________
vector<systM> HistoManager::getSystObs(string obs) {

  vector<systM> systs;
	
  systs.push_back( findSysts(obs,"") );
  systs.push_back( findSysts(obs,"Up") );
  systs.push_back( findSysts(obs,"Do") );
	
  return systs;

}


//____________________________________________________________________________
void HistoManager::copyHisto(string var, int ds, TH1* htmp ) {
  /*
    adds a histogram (htmp) to a variable (var) of the dataset (ds)
    parameters: var, ds, htmp
    return: none
  */

  //root is crazy with binning limits, don't know why...
  gErrorIgnoreLevel = 3000;
	
  //uncertainties
  string uVar = var;
  bool isUnc = uVar.find("Unc")!=(size_t)-1;// ds==-10;
  
  //protection against unc. variations in data
  if( isUnc && (_dsNames[ds]=="data" || _dsNames[ds]=="Data") )
    return;

  if(isUnc) {
    //   var = uVar; 
    ds = 0;
  }
  
  _itVar = _variables.find(var);
	
  // variable does not exist => create it first
  if( _itVar == _variables.end() ) { 
	  
    //test the nature of the histogram
    if     ( (string)(htmp->ClassName()) == "TH1F") 
      addVariableFromTemplate(var, htmp, false, false, isUnc?"u":"" );
		
    else if( (string)(htmp->ClassName()) == "TProfile") 
      addVariableFromTemplate(var, htmp, true, false, isUnc?"u":"" );
		
    else if( (string)(htmp->ClassName()) == "TH2F")
      addVariableFromTemplate(var, htmp, false, true, isUnc?"u":"" );
		
    else if( (string)(htmp->ClassName()) == "TProfile2D") 
      addVariableFromTemplate(var, htmp, false, true, isUnc?"u":"" );
			
    _itVar = _variables.find(var);
  }

  //cout<<var<<"   "<<htmp<<"  "<<ds<<endl;
  _itVar->second.hs[ds]->Add( htmp );
	
  gErrorIgnoreLevel = kError;

}



//____________________________________________________________________________
void HistoManager::fill(string var, int ds, float val, float weight) {
  /*
    fills a variable (var) from a dataset (ds) with value (val) that has a weight (weight)
    parameters: var, ds, val, weight
    return: none
  */
  _itVar = _variables.find(var);
  
  if( _itVar == _variables.end() ) {
    cout << " Error, no such variable declared, " << var << endl;
    return;
  }
  else
    _itVar->second.hs[ds]->Fill(val, weight);
}


//____________________________________________________________________________
void HistoManager::fill(string var, int ds, float valx, float valy, float weight) {
  /*
    fills a two-dimensional variable (var) with values (valx, valy) that have a weight (weight)
    parameters: var, ds, valx, valy, weight
    return: none
  */

  _itVar= _variables.find(var);
	
  if( _itVar == _variables.end() ) {
    cout << " Error, no such variable declared, " << var << endl;
    return;
  }
  else {
    if( _itVar->second.htype.find("P") != (size_t) -1 )
      dynamic_cast<TProfile*>(_itVar->second.hs[ds])->Fill(valx, valy, weight);
    else
      dynamic_cast<TH2*>(_itVar->second.hs[ds])->Fill(valx, valy, weight); //to be checked...
  }
}


//____________________________________________________________________________
void HistoManager::fill(string var, int ds, string type, float value, float weight, string dir) {
  /*
    fills a variable (var) of type (type) with value (value) that has a weight (weight)
    parameters: var, type (possible values??), value, weight, dir (direction of uncertainty, possible values??)
    return: none
  */

  _cItVar = _variables.find(var);
  if(_cItVar == _variables.end() ) {
    cout << " Error, no such variable declared, " << var << endl;
    return;
  }

  else {
	  
    string nameH=var + "Unc" + type + dir;
		
    _itVar = _variables.find(nameH);
    if( _itVar == _variables.end() ) {

      bool isGbl=_variables[var].IsGlobal();
      if(!_itVar->second.isRelevantUnc(type)) return;

      if( _cItVar->second.binsX.size() == 2) {
	addVariable(nameH, _cItVar->second.nBX, _cItVar->second.binsX[0], _cItVar->second.binsX[1],
		    _cItVar->second.titleX, isGbl, (_cItVar->second.htype.find("P") != (size_t) -1), "u");
      }
      else {
	addVariable(nameH, _cItVar->second.nBX, _cItVar->second.binsX, 
		    _cItVar->second.titleX, isGbl, (_cItVar->second.htype.find("P") != (size_t) -1), "u");
      }
      //and point to the good object
      _itVar = _variables.find(nameH);
    }
    _itVar->second.hs[ds]->Fill(value, weight);
  }
  
}

//____________________________________________________________________________
void
HistoManager::setRelevantWFs(string var, vector<string> wfs) {
  _itVar = _variables.find(var);
  if(_itVar == _variables.end() ) {
    cout << " Error, no such variable declared, " << var << endl;
    return;
  }

  _itVar->second.setRelevantWFs(wfs);
}

void
HistoManager::setRelevantUncs(string var, vector<string> uncs) {
  _itVar = _variables.find(var);
  if(_itVar == _variables.end() ) {
    cout << " Error, no such variable declared, " << var << endl;
    return;
  }
  _itVar->second.setRelevantUncs(uncs);
}


//____________________________________________________________________________
void HistoManager::saveHistos(string anName, string conName, map<string, int> cnts, map<string, double> wgtcnts) {
  /*
    creates a root file and stores all variables in it; if the file already
    exists, it renames the existing file to the same name plus the timestamp
    postpended
    parameters: anName (the name of the class), conName (name of configuration)
    return: none
  */

	
  // testing write permission on output directory

  string dirname_ =  (string)(getenv("MPAF")) + "/workdir/root/" + anName;
  FILE* test = fopen( dirname_.c_str(), "r" );

  if( test == 0 ) {
    string command_ = "mkdir -p " + dirname_; 
    assert( system( command_.c_str() ) == 0 );
  }

  else
    fclose( test );


  // Create the root files for the histograms
  // if it already exists, the existing one is renamed via timestamp

  string ofilename_ = dirname_ + "/" + conName + ".root";
  test = fopen( ofilename_.c_str(), "r" );
  if( test != 0 )	{
    fclose( test );
    TDatime datime_;
    cout << "File " << ofilename_ << " already exists, save it." << endl;;
    string command_ = "mv " + ofilename_ + " " + ofilename_ + "_"; 
    ostringstream os;
    os <<datime_.Get();
    command_ += os.str();
    assert( system( command_.c_str() ) == 0 );
  }


  // Storing the histograms in the root file

  cout << "Writing histograms in : " << ofilename_;
  TFile* ofile  = new TFile( ofilename_.c_str(), "RECREATE" );

  vector<string> obss = getObservables(true);

  for(size_t io=0; io<obss.size(); ++io) {

    string obs=obss[io];
		
    ofile->mkdir( obs.c_str() );
    ofile->cd( obs.c_str() );
    
    for(size_t ids = 0; ids < _dsNames.size(); ++ids) {
      TH1* htmp = (TH1*) getHisto(obs, ids)->Clone();
      //protection against negative yields in histo bins
      if(false){
      for(int bin =0; bin < htmp->GetNbinsX()+2;bin++){
          if(htmp->GetBinContent(bin)<0){
              float mean = htmp->GetBinContent(bin);
              float err = htmp->GetBinError(bin);
              htmp->SetBinContent(bin,0);
              float err_new = sqrt(err*err+(std::abs(mean)*std::abs(mean)));
              htmp->SetBinError(bin,err_new);
          }
      }
      }
      htmp->SetName( _dsNames[ids].c_str() );
      htmp->Write();     

      delete htmp;
    }
    ofile->cd();
  }

  //counter histograms
  ofile->mkdir("nEvtProc");
  ofile->cd("nEvtProc");
  map<string, int>::const_iterator it;
  for(size_t ids = 0; ids < _dsNames.size(); ++ids) {
    
    it = cnts.find( _dsNames[ids] );
    if(it==cnts.end() ) continue;

    TH1I* htmp= new TH1I(_dsNames[ids].c_str(), _dsNames[ids].c_str(), 1,0, 1);
    htmp->SetBinContent(1, it->second );
    htmp->Write();     
    delete htmp;
  }

  //counter histograms
  ofile->mkdir("sumWgtProc");
  ofile->cd("sumWgtProc");
  map<string, double>::const_iterator it2;
  for(size_t ids = 0; ids < _dsNames.size(); ++ids) {
    
    it2 = wgtcnts.find( _dsNames[ids] );
    if(it2==wgtcnts.end() ) continue;

    TH1D* htmp= new TH1D(_dsNames[ids].c_str(), _dsNames[ids].c_str(), 1,0, 1);
    htmp->SetBinContent(1, it2->second );
    htmp->Write();     
    delete htmp;
  }

  
  ofile->cd();
  ofile->Write();
  ofile->Close();
}


//____________________________________________________________________________
void HistoManager::savePlots(string path,const TCanvas* c,
			     string advname) {

  string extension[4]={"pdf","eps","png","root"};

  string Name=_hname;

  if(advname!="")
    Name=advname;

  string base = string( getenv("MPAF") )+"/workdir/plots/";
  
  string name1 = base + path + "/"+extension[0]+"/" + Name + "."+extension[0];
  string name2 = base + path + "/"+extension[1]+"/" + Name + "."+extension[1];
  string name3 = base + path + "/"+extension[2]+"/" + Name + "."+extension[2];
  string name4 = base + path + "/"+extension[3]+"/" + Name + "."+extension[3];
 
  FILE *test_;
  for(int i=0;i<4;i++) {
    TString dirname_ = base + path +"/"+extension[i];
    if(i==1)
      cout<<" Dirname "<<dirname_<<endl;
    test_=fopen( dirname_.Data(), "r" );
    if( test_==0 ) {
  	TString command_ = TString("mkdir -p ") + dirname_; 
  	system( command_.Data());
      }
    else
      fclose( test_ );
  }
  
  c->SaveAs(name1.c_str() );
  c->SaveAs(name2.c_str() );
  c->SaveAs(name3.c_str() );
  c->SaveAs(name4.c_str() );

}


//____________________________________________________________________________
void
HistoManager::reset() {

  for(_itVar=_variables.begin();_itVar!=_variables.end();_itVar++) {
    for(size_t ih=0;ih<_itVar->second.hs.size();ih++)
      delete _itVar->second.hs[ ih ];
    
    _itVar->second.hs.clear();
  }
  _variables.clear();
  _dsNames.clear();
  
  _nds=0;
  _hname="";

}

void
HistoManager::refresh() {

  for(_itVar=_variables.begin();_itVar!=_variables.end();_itVar++) {
    for(size_t ih=0;ih<_itVar->second.hs.size();ih++)
      delete _itVar->second.hs[ ih ];
    
    _itVar->second.hs.clear();
  }
  _variables.clear();

}

//systematic uncertainties


//____________________________________________________________________________
systM
HistoManager::findSysts(string var,string type) { //for uncertainties

  systM vars;
  
  vector<string> names;
  for(_itVar=_variables.begin();_itVar!=_variables.end();_itVar++) {

    string name = (*_itVar).first;
    if( (name).find(var+"Unc")==(size_t)-1) continue;
      
    if(type=="Up" && name.substr( name.size()-2,2 ) =="Up") {
      names.push_back(name);
    }
    if(type=="Do" && name.substr( name.size()-2,2 ) =="Do") {
      names.push_back(name);
    }
    if(type=="" && name.substr( name.size()-2,2 ) !="Up"
       && name.substr( name.size()-2,2 ) !="Do"
       ) {
      names.push_back(name);
    }
  }//loop
  
  //No idea of why it is needed to make that in two time...
  for(size_t in=0;in<names.size();in++) {
    vars[ names[in] ] = (TH1*)getHisto( names[in] ,0)->Clone();
  }
 
  return vars;
}




