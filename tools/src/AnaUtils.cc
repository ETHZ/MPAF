#include "tools/src/AnaUtils.hh"

using namespace std;

ClassImp(AnaUtils)

AnaUtils::AnaUtils() {

  _kMC=AUtils::kMC;
  _kGlobal=AUtils::kGlobal;

  //MC initialization
  eMap tmp;
  _effMap.push_back( tmp );
  _dsNames.push_back("MC");
  
  _invCut=false;
  _skipCut=false;
  
  _uncSrc="";

  _useAccForEff=false;

  //workflows
  _nWF=1;
  _curWF=-100;
  _isMultiWF=false;
}

AnaUtils::~AnaUtils() {
}

bool AnaUtils::cbool(bool skip, bool bname) {

  if(!skip)
    return true;
  else{
    if(bname)
      return false;
    else return true;
  }
  
}

string 
AnaUtils::invCut(string type) {
  if(type=="<") {
    return ">=";
  }
  else if(type=="<=") {
    return ">";
  }
  else if( type==">") {
    return "<=";
  }
  else if( type==">=") {
    return "<";
  }
  else if( type=="=") {
    return "!=";
  }
  else if(type=="!=") {
    return "=";
  }
  else if(type=="[]") {
    return "]![";
  }
  else if(type=="][") {
    return "[!]";
  }
  else if(type=="[!]") {
    return "][";
  }
  else if(type=="]![") {
    return "[]";
  }
  else {
    cout<<" Warning cut "<<endl;
    return "=";
  }
} 


void
AnaUtils::setWFEfficiencies(int ids, string cName, float w, bool acc, string uncName ) {
  
  if(_isMultiWF) {
    for(unsigned int ic=0;ic<_multiWFs.size();ic++) {
      //bool nsyst=_categories[ic].isWF && uncName=="" && !_categories[ic].isUnc;
      //bool syst=_categories[ic].isUnc && uncName==_categories[ic].uncTag ;
      setEfficiency(ids, cName, ic, w, acc);
    }
  }
  else { //ALL workflows
    for(_itC=_categories.begin();_itC!=_categories.end();_itC++) {
      bool nsyst=_itC->second.isWF && uncName=="" && !_itC->second.isUnc;
      bool syst=_itC->second.isUnc && uncName==_itC->second.uncTag ;
      if( !nsyst && !syst) continue;
    
      setEfficiency(ids, cName, _itC->first , w, acc);
    }
  }

}


void AnaUtils::setEfficiency(int ids, string cName, int iCateg, float w, bool acc) {
  
  //  Acceptance
  if(_useAccForEff)
    if(!_inAcc) w=0;
  
  _itEIMap=_effMap[ ids ][iCateg].find( cName );
  if(_itEIMap==_effMap[ ids ][ iCateg ].end() ) {
    EffST tmp;
    tmp.eff = 0;
    tmp.sumw = 0; tmp.sumw2 = 0;
    tmp.N = 0;    
    tmp.sumwTot = 0; tmp.sumw2Tot = 0;
    tmp.NTot = 0;    
    
    _effMap[ ids ][ iCateg ][ cName ] = tmp;

    bool exists=false;
    for(size_t ic=0;ic<_categories[ iCateg ].effNames.size();ic++) {
      if(cName == _categories[ iCateg ].effNames[ic]) {exists=true; break;}
    }
    if(!exists)
      _categories[ iCateg ].effNames.push_back( cName );
  }
  
  if(_itEIMap==_effMap[ _kMC ][ iCateg ].end() ) {
    EffST tmp;
    tmp.eff = 0;
    tmp.sumw = 0; tmp.sumw2 = 0;
    tmp.N = 0;    
    tmp.sumwTot = 0; tmp.sumw2Tot = 0;
    tmp.NTot = 0;    

    _effMap[ _kMC ][ iCateg ][ cName ] = tmp;
  }

  setNumbers(ids, cName, iCateg, w, acc);

}


void AnaUtils::setEffFromStat(int ids, string cName, int iCateg, float sw, float esw, int ngen) {
 
  //  Acceptance
  // if(_useAccForEff)
  //   if(!_inAcc) w=0;
 
  _itEIMap=_effMap[ ids ][iCateg].find( cName );
  if(_itEIMap==_effMap[ ids ][ iCateg ].end() ) {
   
    EffST tmp;
    tmp.eff = 0;
    tmp.sumw = 0; tmp.sumw2 = 0;
    tmp.N = 0;    
    tmp.sumwTot = 0; tmp.sumw2Tot = 0;
    tmp.NTot = 0;    
 
    _effMap[ ids ][ iCateg ][ cName ] = tmp;

    bool exists=false;
    for(size_t ic=0;ic<_categories[ iCateg ].effNames.size();ic++)
      if(cName == _categories[ iCateg ].effNames[ic]) exists=true;

    if(!exists)
      _categories[ iCateg ].effNames.push_back( cName );
  }
  
  if(_itEIMap==_effMap[ _kMC ][ iCateg ].end() ) {
    EffST tmp;
    tmp.eff = 0;
    tmp.sumw = 0; tmp.sumw2 = 0;
    tmp.N = 0;    
    tmp.sumwTot = 0; tmp.sumw2Tot = 0;
    tmp.NTot = 0;    

    _effMap[ _kMC ][ iCateg ][ cName ] = tmp;
  }

  setNumFromStat(ids, cName, iCateg, sw, esw, ngen );

}

void AnaUtils::addDataset(string dsName) {
  
  _dsNames.push_back(dsName);
  eMap tmp;
  _effMap.push_back( tmp );
 
}

void
AnaUtils::init() {

  //first, check if the global instance exists
  // and if not, create it 
  if( _categories.find( _kGlobal )==_categories.end()) {
    categ cat;
    cat.id=0;
    cat.name="global";
    cat.uncTag="";
    cat.isUnc=false;
    cat.isWF=true;

    _categories[ _kGlobal ] = cat;
    vector<string> vtmp;
    _categories[ _kGlobal ].effNames = vtmp; 

    _offsetUnc[""]=0;

    for(size_t ids=0;ids<_dsNames.size();ids++) {
      eIMap tmp;
      _effMap[ ids ].push_back( tmp );
    }
  }
}


void
AnaUtils::internalAddCategory(int iCateg, string nCateg, string uncTag, bool isWF) {
  
  if(_categories.find(iCateg) !=_categories.end() ) return;

  categ cat;
  cat.id=iCateg;
  cat.name = nCateg;
  cat.uncTag = uncTag;
  cat.isUnc = !(uncTag=="");
  cat.isWF=isWF;
  
  _categories[ iCateg ] = cat;
  vector<string> vtmp;
  _categories[ iCateg ].effNames = vtmp; 
    
  for(size_t ids=0;ids<_dsNames.size();ids++) {
    eIMap tmp;
    _effMap[ ids ].push_back( tmp );
  }
  _nWF += (int)isWF;
}

void
AnaUtils::addWorkflow(int iCateg, string nCateg) {
  internalAddCategory(iCateg, "global_"+nCateg, "", true);
}


void
AnaUtils::addAutoWorkflow(string uncTag) {

  //single duplication ================
  // _isWF[ _nWF ] = false;
  // _uncWorkflow[eCateg]=_nWF;
  // internalAddCategory(_nWF, "global_"+eCateg);
  // _nWF = _isWF.size();

  //multi duplication, more appropriate for systematic uncertainties with the multi workflow stuff
  map<int,categ>::const_iterator it;
  map<int,categ>::const_iterator itend=_categories.end();
  
  _offsetUnc[uncTag]=_nWF;
  for(it = _categories.begin(); it!=itend; ++it) {

    if(it->second.isUnc) continue;
  
    internalAddCategory(_nWF, it->second.name, uncTag, false);
    _nWF +=1;
  }

}

void
AnaUtils::addCategory(int iCateg, string nCateg) {
  internalAddCategory(iCateg, nCateg, "", false);
}


void
AnaUtils::addCategory(int iCateg, string nCateg, string uncTag) {
  internalAddCategory(iCateg, nCateg, uncTag, true);
}

void
AnaUtils::setWFSystematics(int ids, string cName, string sName, bool up,
			   bool down, float w, string uncName) {
  
 if(_isMultiWF) {
    for(unsigned int ic=0;ic<_multiWFs.size();ic++) {
      if( _categories[ic].isWF && (uncName=="" || _categories[ic].uncTag!=uncName) )
	setSystematics(ids, cName, ic, sName, up, down, w);
    }
  }
 else {
   for(_itC=_categories.begin();_itC!=_categories.end();_itC++) {
     if( _itC->second.isWF && (uncName=="" || _itC->second.uncTag!=uncName) )
       setSystematics(ids, cName, _itC->first, sName, up, down, w);
   }
 }
}


void 
AnaUtils::setSystematics(int ids, string cName, int iCateg, string sName, bool up, bool down, float w) {

  bool accept[2] = {false,false};
  accept[0] = up;
  accept[1] = down;
  
  float val=w;
 
  _effMap[ ids ][ iCateg ][ cName ].systsU[ sName ] +=(accept[0]?val:0);
  _effMap[ ids ][ iCateg ][ cName ].systsD[ sName ] +=(accept[1]?val:0);
  
  if(_dsNames[ids]!="data" && _dsNames[ids]!="Data") {
    _effMap[ _kMC ][ iCateg ][ cName ].systsU[ sName ] +=(accept[0]?val:0);
    _effMap[ _kMC ][ iCateg ][ cName ].systsD[ sName ] +=(accept[1]?val:0);
  }

}

void
AnaUtils::getYieldSysts(EffST eST, map<string,float>& rU, map<string,float>& rD,
			float& totUp, float& totDown, float& central) {

  central = eST.sumw;

  float dU,dD;

  for(map<string,float>::const_iterator it=eST.systsU.begin();
      it != eST.systsU.end(); it++ ) {
    
    string n =  (*it).first;

    dU = it->second - central; //temporary variation variation
    dD = eST.systsD[ n ] - central;
    
    if( dU*dD > 0) { //same sign errors
      rU[ n ] = dU>=0?(dU>dD?(dU*dU):(dD*dD)):0;
      rD[ n ] = dU<0?(dU<dD?(dU*dU):(dD*dD)):0;
      
      totUp += rU[ n ];
      totDown += rD[ n ];
    }
    else { //opposite sign errors
      rU[ n ] = dU>=0?(dU*dU):(dD*dD);
      rD[ n ] = dU<0?(dU*dU):(dD*dD);
      totUp +=rU[ n ];
      totDown +=rD[ n ];
    }

  }

  totUp = sqrt(totUp);
  totDown = sqrt(totDown);

  for(map<string,float>::const_iterator it= rU.begin();it!=rU.end();it++) {
    rU[ it->first ] = sqrt(rU[ it->first ]);
    rD[ it->first ] = sqrt(rD[ it->first ]);    
  }

}

float
AnaUtils::getYield(int ids, string cName, int icat) {

  return _effMap[ ids ][ icat ][ cName ].sumw;
}

void
AnaUtils::getSystematics(string ds, string lvl, string categ) {

  int ids = -1;
  for(size_t i=0;i<_dsNames.size();i++) 
    if(ds==_dsNames[i]) {ids=i; break;}

  if(ids==-1) {
    cout<<" Error, no ["<<ds<<"] dataset available for printing uncertainties "<<endl;
    return;
  }

  int iCat = getCategId(categ);
  if(iCat==-1) {
    cout<<" Error, no ["<<categ<<"] category available for printing uncertainties "<<endl;
    return;
  }

  
  _itEIMap=_effMap[ ids ][ iCat ].find(lvl);
  if(_itEIMap==_effMap[ ids ][ iCat ].end() ) {
    cout<<" Error, no ["<<lvl<<"] selection available for printin uncertainties "<<endl;
    return;
  }

  EffST eST=_itEIMap->second;
  float central;
  
  float totUp=0,totDown=0;
  map<string,float> rU, rD;

  //retrieve systematic uncertainties
  getYieldSysts(eST, rU, rD, totUp, totDown, central);
  

  cout<<setprecision(2)<<fixed;
  cout<<" ************************************************************* "<<endl;
  cout<<" Detail of uncertainties on ("<<ds<<") yield, at the ("<<
    categ<<":"<<lvl<<") selection level "<<endl;

  cout<<setw(30)<<"   uncertainty source\t"<<"\t"<<" yield "<<endl;
  cout<<setw(30)<<"   statistical\t"<<"\t"<<central<<" +- "<<sqrt(eST.sumw2)
      <<" ( "<<sqrt(eST.sumw2)*100./central<<" %)"<<endl;
  
  for(map<string,float>::const_iterator it= rU.begin();it!=rU.end();it++) {
    string name="   "+it->first+"\t";
    if( fabs((it->second)-(rD[ it->first]) )>0.01*central ) { //asymetric
      cout<<setw(30)<<name<<"\t"<<" + "<<(it->second)*100/central
  	  <<" - "<<rD[ it->first]*100/central<<" %   (+"
  	  <<it->second<<" -"<<rD[ it->first]<<" events)"<<endl;
    }
    else { //symetric
      cout<<setw(30)<<name<<"\t"<<" +- "<<max((it->second),rD[ it->first])*100/central
  	  <<" % (+"<<it->second<<" -"<<rD[ it->first]<<" events)"<<endl;
    }

  }
  cout<<"------------------------------------- "<<endl;
  if(fabs(totUp-totDown)>0.01*central) { //asymetric
    cout<<setw(30)<<"   total"<<"\t"<<" + "<<totUp*100/central
  	<<" - "<<totDown*100/central<<" %   (+"
  	<<totUp<<" -"<<totDown<<" events)"<<endl; 
  }
  else { //symetric
    cout<<setw(30)<<"   total systematics"<<"\t"<<" +- "<<max(totUp,totDown)*100/central
  	<<" % (+"<<totUp<<" -"<<totDown<<" events)"<<endl;
  }


}


void
AnaUtils::getCategSystematics(string ds, string src, string lvl, string categ, bool latex) {

  int ids = -1;
  for(size_t i=0;i<_dsNames.size();i++) 
    if(ds==_dsNames[i]) {ids=i; break;}

  if(ids==-1) {
    cout<<" Error, no ["<<ds<<"] dataset available for printing uncertainties "<<endl;
    return;
  }
  
  cout<<endl<<" ======================= "<<setw(12)<<ds <<" ("<<src<<") ======================== "<<endl;

  for(_itC=_categories.begin();_itC!=_categories.end();++_itC) {

    string cname=_itC->second.name;
    if(cname.find(categ)==string::npos) continue;

    _itEIMap=_effMap[ ids ][ _itC->second.id ].find(lvl);
    if(_itEIMap==_effMap[ ids ][ _itC->second.id ].end()) continue;
    
    EffST eST=_itEIMap->second;
    float central;
    
    float totUp=0,totDown=0;
    map<string,float> rU, rD;
    
    //retrieve systematic uncertainties
    getYieldSysts(eST, rU, rD, totUp, totDown, central);
    cout<<setprecision(2)<<fixed;
    if(cname.find("global")!=string::npos) cname.erase(0,7);
    if(!latex)
      cout<<setw(10)<<cname<<"\t"<<setw(5)<<central<<" +- "<<setw(5)<<sqrt(eST.sumw2)<<"\t";
    else
      cout<<setw(10)<<cname<<" & "<<setw(5)<<central<<" $\\pm$ "<<setw(5)<<sqrt(eST.sumw2)<<"  &  ";

  
    float yup;
    float ydown;
    if(src=="total") {
      yup=totUp;
      ydown=totDown;
    } else {
      yup=rU[ src];
      ydown=rD[ src];
    }
    float rup=yup*100/central;
    float rdown=ydown*100/central;
    if(central==0) { rup=0; rdown=0;}
    
    if(!latex) {
      if( fabs(rup-rdown)>0.01*central ) { //asymetric
	cout<<" + "<<setw(5)<<rup<<" - "<<setw(5)<<rdown<<" %  (+"
	    <<setw(5)<<yup<<" -"<<setw(5)<<ydown<<" events)"<<endl;
      }
      else { //symetric
	cout<<" +- "<<setw(5)<<max(rup,rdown)<<" %         (+-      "<<setw(5)<<max(yup,ydown)<<" events)"<<endl;
      }
    }
    else {
      if( fabs(rup-rdown)>0.01*central ) { //asymetric
	cout<<" +"<<setw(5)<<rup<<"/-"<<setw(5)<<rdown
	    <<" & +"<<setw(5)<<yup<<"/-"<<setw(5)<<ydown<<" \\\\ "<<endl;
      }
      else { //symetric
	cout<<" $\\pm$ "<<setw(5)<<max(rup,rdown)<<" & $\\pm$"<<setw(5)<<max(yup,ydown)<<" \\\\ "<<endl;
      }
    }
  
  }//categds

}



void 
AnaUtils::saveNumbers(string anName, string conName,  map<string, int> cnts,  map<string, double> wgtcnts) {

  // testing write permission on output directory
  cout << endl;
  string dirname_ =  (string)(getenv("MPAF")) + "/workdir/stats/" + anName;
  FILE* test = fopen( dirname_.c_str(), "r" );
  if( test == 0 ) {
    string command_ = "mkdir -p " + dirname_; 
    assert( system( command_.c_str() ) == 0 );
  }
  else
    fclose( test );
	
  string ofilename_ = dirname_ + "/" + conName + ".dat";
  test = fopen( ofilename_.c_str(), "r" );
  if( test != 0 )	{
    fclose( test );
    TDatime datime_;
    cout << "File " << ofilename_ << " already exists, save it." << endl;
    string command_ = "mv " + ofilename_ + " " + ofilename_ + "_"; 
    ostringstream os;
    os << datime_.Get();
    command_ += os.str();
    assert( system( command_.c_str() ) == 0 );
  }

  //now storing the output
  ofstream ofile( ofilename_.c_str(), ios::out | ios::trunc );
  if(!ofile) {
    cout << "Error writing stat file " << endl; 
    return;
  }

  vector<int> idxs;
  vector<string> dsNames = prepareDSNames(false, idxs);
 
  // print global efficiencies at the beginning======================
  vector<int> catNames;
  bool hasGlobEff = false;
  for(_itC = _categories.begin(); _itC != _categories.end(); ++_itC) {
    if( _itC->second.name == "global" && !_itC->second.isUnc) {
      hasGlobEff = true; 
      continue; 
    }
    catNames.push_back( _itC->first ); 
  }

  if(hasGlobEff) {
    //catNames.push_back( _kGlobal );
    catNames.insert(catNames.begin(), _kGlobal );
  }

  for(size_t ic = 0; ic < catNames.size(); ++ic) {
    int icat = catNames[ic];
    ofile<<"categ\t"<<_categories[icat].name;
    if(_categories[icat].isUnc)   ofile<<"\t"<<_categories[icat].uncTag<<endl;
    else ofile<<endl;
    bool header = true;

    // to skip the simulation in a first time
    for(size_t ic = 0; ic < _categories[icat].effNames.size(); ++ic) { //cuts

      _itEIMap = _effMap[ _kMC ][icat].find( _categories[icat].effNames[ ic ] );
	
      // out of the loop if no MC
      if(_itEIMap == _effMap[ _kMC ][icat].end() ) 
	break; 

      if(header){
	ofile << "\tselection\tdataset\tyield (unweighted)\tyield error" << endl; //\tnum gen evts
	header = false;
      }
      
      // to skip the simulation summary
      for(size_t id = 0; id < dsNames.size(); ++id) { //datasets
	int ids = idxs[id];

	map<string,EffST>::iterator itm;
	{ // simulation detail
	  // cut name
	  ofile << "\t" << _itEIMap -> first;
	  // dataset name
	  ofile << "\t" << dsNames[id]; 
	  // yields
	  itm = _effMap[ids][icat].find( _itEIMap -> first );
	  
	  if(itm == _effMap[ids][icat].end()) 
	    ofile << "\t0\t0\t0 ";
	  //ofile << " - ";

	  else {
	    if(itm -> second.sumw > 0.000001 ) { 
	      ostringstream os, os2, os3;
	      os<< setprecision(10) << itm -> second.sumw; // fixed << setprecision(4)
	      os2<< itm -> second.N; // fixed << setprecision(0) <<
	      os3<< sqrt(itm -> second.sumw2); // fixed << setprecision(4) <<
	      
	      ofile << "\t" << os.str() << "\t" << os2.str() << "\t" << os3.str();
	    }
	    else
	      ofile << "\t0\t0\t0 ";
	    						
	    // number of selected events unweighted
	    //ofile << fixed << setprecision(0) << " (" << itm -> second.N << ")" << fixed << setprecision(4);
	  }

	  ofile << endl;
	}
      } // datasets
    } // cuts

    ofile << "endcateg\t" << _categories[icat].name << endl << endl;
  } // categories


  //MM, gen event counters to be added for automatic normalization in yields/stats
  string dsStr="dsCnts\t";
  string dsCntStr="cnts\t";
  string dsWgtCntStr="wgts\t";
  map<string, int>::const_iterator it;
  map<string, double>::const_iterator it2;
  for(size_t id = 0; id < dsNames.size(); ++id) { //datasets
    it = cnts.find( dsNames[id] );
    if(it==cnts.end() ) continue;

    it2 = wgtcnts.find( dsNames[id] );
    if(it2==wgtcnts.end() ) continue;

    ostringstream os; os<<it->second;
    ostringstream oswgt; oswgt<<it2->second;
    
    dsStr += dsNames[id]+"\t";
    dsCntStr += os.str()+"\t";
    dsWgtCntStr += oswgt.str()+"\t";
  }
  
  ofile<< dsStr <<endl;
  ofile<< dsCntStr<<endl;
  ofile<< dsWgtCntStr<<endl<<endl;


  ofile.close();
}


void AnaUtils::printNumbers() {
  
  //move MC at the end
  vector<string> dsNames;
  bool hasData = _dsNames.back()=="data" || _dsNames.back()=="Data";
  size_t nds=_dsNames.size();
  
  for(size_t ids=1;ids<(hasData?nds-1:nds);ids++) {
    dsNames.push_back(_dsNames[ids]);
  }
  //dsNames.push_back(_dsNames[0]); //MC disabled for that function as unweighted yields are printed
  if(hasData)
    dsNames.push_back(_dsNames.back());

  // print global efficiencies at the end======================
  vector<int> catNames;
  bool hasGlobEff=false;
  for(_itC = _categories.begin(); _itC != _categories.end(); ++_itC) {
    if(_itC->first == _kGlobal) {hasGlobEff=true; continue; }
    catNames.push_back(  _itC->first ); 
  }
  if(hasGlobEff)
    catNames.push_back( _kGlobal );

  for(size_t ic=0;ic<catNames.size();ic++) {
    int icat = catNames[ic];
    
    cout<<endl<<endl;
    cout<<" ===================================================================== "<<endl;
    
    if(_categories[ icat ].isUnc) cout<<" ============= Efficiency category : "<<setw(17)<<_categories[ icat ].name<<" ("<<setw(9)<<_categories[ icat ].uncTag<<") ==="<<endl;
    else cout<<" ============= Efficiency category : "<<setw(17)<<_categories[ icat ].name<<" ==============="<<endl;
      
    cout<<" ===================================================================== "<<endl;

    for(size_t id=0;id<dsNames.size();id++) { //datasets
      string dsName = dsNames[id];
      //but id = 0 is MC
      int ids=id+1;
    
      //need last object for change of weights
      float tmpswtot=-1;
      float tmpNTot=-1;
    
      cout<<endl<< "Begin efficiencies for "<<dsName<<"   "<<_effMap[ids][icat].size()<<"  ********* "<<endl;
    
      string initName;
      for(size_t ic=0;ic<_categories[ icat ].effNames.size();ic++) { //cut
    
	_itEIMap = _effMap[ids][icat].find( _categories[icat].effNames[ ic ] );
	if(ic==0) initName = _categories[ icat ].effNames[ ic ];
	if(_itEIMap == _effMap[ids][icat].end() ) continue;
    
	//get total value
	float eff = _itEIMap->second.sumw / _itEIMap->second.sumwTot;
	float error = StatUtils::BinomError( _itEIMap->second.NTot, eff);

	//get High and low values for total systematics (if available)
	float central;
	float totUp=0,totDown=0;
	map<string,float> rU, rD;
	getYieldSysts(_itEIMap->second, rU, rD, totUp, totDown, central);
	
	float effL = totDown / _itEIMap->second.sumwTot;
	float effH = totUp / _itEIMap->second.sumwTot;

	//fix for change of weight
     
	if(_itEIMap->second.sumwTot != tmpswtot && tmpswtot!=-1 ) {
	  eff = _itEIMap->second.sumw / tmpswtot;
	  if(eff>1) eff=1.;
	  error = StatUtils::BinomError( tmpNTot, eff);
	  effL = totDown /tmpswtot;
	  effH = totUp /tmpswtot;
	}
         
	//FIXME -> if no systematic called, let remove them
	if( effL ==0 && effH==0 ) 
	  effL = eff;
	if( effH ==0 && effH==0 )
	  effH = eff;
      
	float systL = fabs(eff-effH); //inverted for the good direction
	float systH = fabs(eff-effL);

	//==========================================================
	float globEff = _itEIMap->second.sumw/_effMap[ids][icat][ initName ].sumwTot;
      	//FIXME ugly protection against a change of weight
	if(globEff>1) globEff=1;
      
	float globErr = StatUtils::BinomError( _effMap[ids][icat][ initName ].sumwTot, globEff);      
	cout<<setprecision(3)<<fixed;
	cout<<" --> "<<setw(30)<<_itEIMap->first<<"\t  = "<<eff<<" +- "<<error;
	if( effL !=0 || effH!=0 ) 
	  cout<<" (+ "<<systH<<" - "<<systL;
	cout<<" \t\t "<<_itEIMap->second.sumw<<"  / "
	    <<((tmpswtot==-1)?_itEIMap->second.sumwTot:tmpswtot);
	cout<<"  ("<<_itEIMap->second.N<<" / "<<((tmpNTot==-1)?_itEIMap->second.NTot:tmpNTot)<<")";
	cout<<"  ---> \t = "<<globEff*100<<" +- "<<globErr*100<<endl;
      
	tmpswtot =  _itEIMap->second.sumw;
	tmpNTot = _itEIMap->second.N;

      } //cuts
    
    } //datasets
  
  }//categories
  
  cout<<endl<<endl;

}

int
AnaUtils::getCategId(string categ) {
  int icat=-1;
  int n=_categories.size();

  for(int ic=-1;ic<n;ic++) {
    if(_categories[ic].name==categ) {
      icat = _categories[ic].id;
      break;
    }
  }
  return icat;
}

int
AnaUtils::getCategUniqueId(string categ, string uncTag) {
  int icat=-1;
  int n=_categories.size();

  for(int ic=-1;ic<n;ic++) {
    if(_categories[ic].name==categ &&
       _categories[ic].uncTag==uncTag) {
      icat = _categories[ic].id;
      break;
    }
  }
  return icat;
}



vector<string> 
AnaUtils::getCategories() {
  
  vector<string> vs;
  map<int, categ>::const_iterator it;
  for(it=_categories.begin(); it!=_categories.end();it++) {
    
    if(it->second.isUnc) continue;
   
    vs.push_back( it->second.name );
  }  

  return vs;
}

bool
AnaUtils::isUncCateg(int id) {
  //int id=getCategId(categ);
  return _categories[id].isUnc;
}

vector<string>
AnaUtils::getSelections(int ids, int icat) {

  vector<string> vs;
  for(size_t ic=0;ic<_categories[ icat ].effNames.size();ic++) {
    _itEIMap = _effMap[ ids ][ icat ].find( _categories[ icat ].effNames[ ic ] );
    if(_itEIMap == _effMap[ _kMC ][ icat ].end()) continue;
    vs.push_back(_categories[ icat ].effNames[ic]);
  }
  
  return vs;
}

vector<string> 
AnaUtils::prepareDSNames(bool wMC, vector<int>& idxs) {
  //move MC at the end
  vector<string> dsNames;
  bool hasData = _dsNames.back()=="data" || _dsNames.back()=="Data";
  size_t nds=_dsNames.size();
  
  for(size_t ids=1;ids<(hasData?nds-1:nds);ids++) {
    dsNames.push_back(_dsNames[ids]);
    idxs.push_back(ids);
  }
  if(wMC) {
    dsNames.push_back(_dsNames[0]);
    idxs.push_back(0);
  }
  if(hasData) {
    dsNames.push_back(_dsNames.back());
    idxs.push_back(nds-1);
  }
  
  return dsNames;
}


void
AnaUtils::printTables(string categ) {
  
  int icat= getCategId(categ);
  
  vector<int> idxs;
  vector<string> dsNames = prepareDSNames(true, idxs);
  bool hasData = _dsNames.back()=="data" || _dsNames.back()=="Data";
  
  //Numbers =======================================================
  cout<<endl<<endl;
  //For Latex
  
  bool header=true;
  //start from one to skip the simulation in a first time
  for(size_t ic=0;ic<_categories[ icat ].effNames.size();ic++) { //cuts

    _itEIMap = _effMap[ _kMC ][ icat ].find( _categories[ icat ].effNames[ ic ] );
    if(_itEIMap == _effMap[ _kMC ][ icat ].end() ) break; //out of the loop if no MC

    if(header) {
      cout<<" Cut  "<<fixed<<setprecision(2);
      for(size_t ids=0;ids<dsNames.size();ids++) { //_itEMap
        cout<<" & "<<dsNames[ ids ]<<"   ";
      }
      cout<<" \\\\ "<<endl;
      header=false;
    }

    cout<<_categories[ icat ].effNames[ ic ]<<" ";

    //start from one to skip the simulation summary
    for(size_t id=0;id<dsNames.size();id++) { //datasets _itEMap
      int ids=idxs[id];
      
      cout<<" & ";
      { //simulation detail
        _itEIMap=_effMap[ ids ][ icat ].find( _categories[ icat ].effNames[ ic ] );

        if(_itEIMap==_effMap[ ids ][ icat ].end()) 
          cout<<" - ";
        else {
          if(_itEIMap->second.sumw>0.000001 ) {
            cout<<_itEIMap->second.sumw;
            cout<<" $\\pm$ "<<sqrt(_itEIMap->second.sumw2);
          }
          else
            cout<<" - "; 
        }
        
        if(dsNames[id]=="data" || dsNames[id]=="Data" ||
           (!hasData && (dsNames[id]=="MC" || (size_t)ids==dsNames.size() ) ) )
          cout<<" \\\\ "<<endl;
      }
      
    }//datasets
  }//cuts


  cout<<endl<<endl;
  

  //For Visu

  header=true;
  //to skip the simulation in a first time
  for(size_t ic=0;ic<_categories[icat].effNames.size();ic++) { //cuts
    
    _itEIMap = _effMap[ _kMC ][icat].find( _categories[icat].effNames[ ic ] );
    if(_itEIMap == _effMap[_kMC][icat].end() ) break; //out of the loop if no MC

    if(header) {
      cout<<setw(15)<<" Cut                "<<fixed<<setprecision(2)<<"\t";
      for(size_t ids=0;ids<dsNames.size();ids++) {
    	cout<<setw(20)<<dsNames[ids]<<"\t";
      }
      cout<<endl;
      header=false;
    }

    cout<<setw(20)<<_categories[icat].effNames[ ic ]<<"\t";

    //to skip the simulation summary
    for(size_t id=0;id<dsNames.size();id++) { //datasets
      int ids = idxs[id];
      { //simulation detail
        _itEIMap=_effMap[ ids ][ icat ].find( _categories[icat].effNames[ ic ] );
        if(_itEIMap==_effMap[ ids ][ icat ].end()) 
          cout<<setw(20)<<" - ";
	else {
          if(_itEIMap->second.sumw>0.000001 ) {
            
            ostringstream os,os2;
            os <<fixed<<setprecision(2)<<_itEIMap->second.sumw;
            os2 <<fixed<<setprecision(2)<<sqrt(_itEIMap->second.sumw2);
        
            string tmps=os.str()+" +- "+os2.str();
            cout<<setw(20)<<tmps;
          }
          else
            cout<<" - "; 
        }
        
        if(dsNames[id]=="data" || dsNames[id]=="Data" || 
           (!hasData && (dsNames[id]=="MC" || (size_t)ids==dsNames.size() ) ) )  
          cout<<endl;
        else
          cout<<"\t";
      }
      
    }//datasets
  }//cuts

}


int 
AnaUtils::findElement(vector<string> v, string e){

  vector<string>::iterator i = find(v.begin(), v.end(), e);
  if(i == v.end()) return -1;
  return distance( v.begin(), i );

}

//selection:<nom, ds:nums> 
vector< pair<string, vector<vector<map<string,float> > > > >
AnaUtils::retrieveNumbers(string categ, string cname, int scheme, string opt) {
  vector< pair<string, vector<vector<map<string,float> > > > > onums;
  if(categ=="") return onums;

  istringstream iss(opt);
  vector<string> opts;
  copy(istream_iterator<string>(iss),
       istream_iterator<string>(),
       back_inserter<vector<string> >(opts));

  //first, retrieve the ids to be used =================

  vector<pair<int,string> > catIds; //icateg:selection
  vector<pair<int,string> > catIdsOpt; //icateg:selection for optional categ scheme
  
  if(scheme==kMono) { //one category, one selection -> limit tool
    int icat= getCategId(categ);
    pair<int, string> p(icat, cname);
    catIds.push_back( p );
  }
  if(scheme>=kMulti) {//several categories, one selection -> yield comparison
    for(_itC=_categories.begin();_itC!=_categories.end();++_itC) {
      if(_itC->second.isUnc) continue;

      if(_itC->second.name.find(categ)!=string::npos) {
	int icat= getCategId(_itC->second.name);
	pair<int, string> p(icat, cname);

	bool findOpt=false;
	for(unsigned int io=0;io<opts.size();io++) {
	  if(_itC->second.name.find(opts[io])!=string::npos)
	    findOpt=true;
	}

	if(!findOpt){
	  catIds.push_back(p);
	}
	else if(opt=="") { // empty option categ
	  catIds.push_back(p);
	}

       }
    }
    
    if(opt!="" && scheme==kMulti)
      catIds.insert (catIds.end(),catIdsOpt.begin(),catIdsOpt.end());
  }
  if(scheme==kGeneral) {//one category, several selections -> yield evolution
    int icat= getCategId(categ);
    for(unsigned int is=0;is<_categories[icat].effNames.size();is++) {
      pair<int, string> p(icat, _categories[icat].effNames[is]);
      catIds.push_back( p );
    }
  }

  vector<int> idxs;
  vector<string> dsNames = prepareDSNames(true, idxs);
  
  //second, retrieve the numbers for the main stream
  for(size_t id=0;id<catIds.size();id++) {
    int icat = catIds[id].first;
    string sel = catIds[id].second;
    pair<string, vector<vector<map<string,float> > > > p;
    vector<vector<map<string,float> > > v(dsNames.size(),vector<map<string,float> >(5, map<string,float>() ));

    //naming scheme =========================
    if(scheme>=kMulti) { //only the extension
      size_t p0= _categories[icat].name.find(categ);
      p.first=_categories[icat].name.substr(p0+categ.size(), categ.size()-p0-1);
    }
    else p.first=sel;
      
    p.second=v;

    _itEIMap = _effMap[ _kMC ][ icat ].find( sel );
    if( _itEIMap==_effMap[ _kMC ][ icat ].end() ) {
      cout<<"WARNING, no such selection name : ["<<cname<<"] in categ "<<categ
	  <<" ("<<_categories[icat].name<<"), please check name"<<endl;
      onums.push_back( p );
      continue;
    }
   
    for(size_t id=0;id<dsNames.size();id++) { //datasets
      int ids = idxs[id];

      //simulation detail
      _itEIMap=_effMap[ ids ][ icat ].find( sel );
      if(_itEIMap==_effMap[ ids ][ icat ].end() ) {
	p.second[ids][0]["tot"] = 0.; //no data for this point and this dataset
	p.second[ids][1]["tot"] = 0.;
	p.second[ids][2]["tot"] = 0.;
	p.second[ids][3]["tot"] = 0.;
	p.second[ids][4]["tot"] = 0.;
      }
      else {

	float central;
	float totUp=0,totDown=0;
	map<string,float> rU, rD;
	getYieldSysts(_itEIMap->second, rU, rD, 
		      totUp, totDown, central);
	
	p.second[ids][0]["tot"] = _itEIMap->second.sumw;
	p.second[ids][1]["tot"] = sqrt(_itEIMap->second.sumw2);
	p.second[ids][4]["tot"] = _itEIMap->second.N;


	p.second[ids][2] = rU;
	p.second[ids][3] = rD;
	p.second[ids][2]["tot"] = totUp;
	p.second[ids][3]["tot"] = totDown;
      }
    }
    onums.push_back(p);
  } //catids

  return onums;
}


bool
AnaUtils::getDataCardLines(map<string,string>& lines,
			   shapeM& shapes, 
			   vector<string> dsNames, string sigName,
			   string categ, string cname, int bin,
			   map<string,vector<string> > intNuisPars,
			   map<string,bool > nuisParExt,
			   map<string,string> nuisParScheme,
			   map<string,vector<string> > nuisParVals ) {
  
  vector<pair<string, vector<vector<map<string,float> > > > > numbers=retrieveNumbers(categ, cname, kMono);

  if(numbers.size()==0) return false; //case where no data are available

  // yield lines =================================================================
  float sumBkg=0;
  float sumSig=0;
  float sumData=0;
  
  string procNameLine="";
  string procNumLine="";
  string yieldLine="";
  string dataYield="";
  string binLine="";

  int nBkg=1;
  for(unsigned int ids=1;ids<dsNames.size()+1;ids++) {//0 is MC
    
    ostringstream osB; osB<<bin;  
    if(dsNames[ids-1]!=sigName && dsNames[ids-1].find("sig")==string::npos && 
       dsNames[ids-1].find("data")==string::npos) {
      sumBkg+= (numbers[0].second[ids][0]["tot"]);
      
      binLine += osB.str()+"\t";
      ostringstream os;
      float y=((numbers[0].second[ids][0]["tot"]==0)?0.0001:numbers[0].second[ids][0]["tot"]);
      if(y<0) y=0.0001;
      os<<setprecision(4)<< y;
      yieldLine += os.str()+"\t";
      procNameLine += dsNames[ids-1]+"\t";
    
      //=======
      ostringstream os2;
      os2<<nBkg;
      procNumLine += os2.str()+"\t";
      nBkg++;

    }
    else if(dsNames[ids-1]==sigName) {
      //cout<<sigName<<" --> "<<numbers[0].second[ids][0]["tot"]<<endl;
      binLine += osB.str()+"\t";
      sumSig = numbers[0].second[ids][0]["tot"];
    }
    else if(dsNames[ids-1].find("data")!=string::npos) {
      sumData = numbers[0].second[ids][0]["tot"];
    }
  }
  
  lines[ "bins" ] = binLine;

  //adding the signal =======================
  lines[ "procNames" ] = sigName+"\t"+procNameLine;
  lines[ "procNums" ] = "0\t"+procNumLine;
  
  ostringstream os;
  os<<setprecision(4)<<sumSig;
  lines[ "yields" ] = os.str()+"\t"+yieldLine;
  // =================================================================
  // adding the data =================
  ostringstream os2;
  os2<<setprecision(4)<<sumData;
  lines[ "dataYield" ] = os2.str(); 
  // =================================================================
  // and the nuisance parameters
  for(map<string,vector<string> >::const_iterator it=intNuisPars.begin();
      it!=intNuisPars.end(); it++) {
    string line="";
    map<string, vector<float> > tmpMap;
    float central;
    
    if(it->first.find("stat")!=string::npos) continue; //syst from stat ucnertainties
    if(nuisParExt[ it->first ] == true ) continue;
    if(it->first.find("_OW")!=string::npos) continue;

    bool exists=false;
    for(unsigned int ids=1;ids<dsNames.size()+1;ids++) {
      exists=false;
      if(dsNames[ids-1]=="") continue; //total MC?
      if(dsNames[ids-1].find("data")!=string::npos) continue;
      
      vector<float> vals;
      for(unsigned int ids2=0;ids2<it->second.size();ids2++) {
	
	if(dsNames[ids-1]==it->second[ids2] ) {
	  exists=true;
	  float vUp=-1, vDo=1;
	  if(numbers[0].second[ids][2].find(it->first)!=numbers[0].second[ids][2].end()) {
	    central=numbers[0].second[ids][0]["tot"];
	    if(numbers[0].second[ids][0]["tot"]>0) {
	      vUp = numbers[0].second[ids][2][it->first]/numbers[0].second[ids][0]["tot"];
	      vDo = numbers[0].second[ids][3][it->first]/numbers[0].second[ids][0]["tot"];
	      // cout<<it->first<<"  "<<dsNames[ids-1]<<" -->  "<<numbers[0].second[ids][2][it->first]<<"  "<<numbers[0].second[ids][3][it->first]<<"  "<<numbers[0].second[ids][0]["tot"]<<" --> "<<numbers[0].second[ids][0]["tot"]*(1+vUp)<<"  "<<numbers[0].second[ids][0]["tot"]*(1-vDo)<<" --> "<<(1-vDo)<<" "<<(1+vUp)<<" // "<<vUp<<"  "<<vDo<<endl;
	    }
	    else { //arbitrary 100% for now
	      if(numbers[0].second[ids][2][it->first]==0) vUp=0;
	      else vUp=1;

	      if(numbers[0].second[ids][3][it->first]==0) vDo=0;
	      else vDo=1;
	      // vUp = 1;// numbers[0].second[ids][2][it->first]/numbers[0].second[ids][2][it->first];
	      // vDo = 1;//numbers[0].second[ids][3][it->first]/numbers[0].second[ids][3][it->first];
	    }
	  }

	  ostringstream osU, osD;
	  map<string,vector<string> >::const_iterator it2=intNuisPars.find(it->first+"_OW");
	  if(it2!=intNuisPars.end() && 
	     find( intNuisPars[it->first].begin(), intNuisPars[it->first].end(), _dsNames[ids-1] )==intNuisPars[it->first].end() ) {
	    for(unsigned int id=0;id<it->second.size();++id) {
	      if(dsNames[ids-1]==it->second[id]) {
		vDo=atof(nuisParVals[ it2->first ][id].c_str() );
		vUp=atof(nuisParVals[ it2->first ][id].c_str() );
	      }
	    }
	  }
	  
	  if(std::abs(vUp)<0.001 && vUp!=0) vUp=0.001*(vUp/std::abs(vUp));
	  if(std::abs(vDo)<0.001 && vDo!=0) vDo=0.001*(vDo/std::abs(vDo));
	  
	  central=(central<=0)?0.0001:central;
	  vals.push_back( central );
	  if(central!=0.0001) {
	    vals.push_back( (1+vUp)*central );
	    vals.push_back( (1-vDo)*central );
	  }
	  else { //poisson, cannot work w/o N gen events
	    float w=std::abs(numbers[0].second[ids][0]["tot"])/numbers[0].second[ids][4]["tot"];
	    vals.push_back( 1.84*w ); 
	    vals.push_back( 0.0001 );
	  }
	  tmpMap[ dsNames[ids-1] ]=vals;


	  if(vDo>=1) vDo=0.999;
	  //cout<<" --> "<<(1+vUp)<<"  "<<(1-vDo)<<endl;
	  osU<<fixed<<setprecision(3)<<(1+vUp);
	  osD<<fixed<<setprecision(3)<<(1-vDo);
	  string tmpU=osU.str();
	  string tmpD=osD.str();

	  if(nuisParScheme[it->first]!="shape") {
	    if(dsNames[ids-1]!=sigName) {
	      line+=osD.str()+"/"+osU.str()+"\t";
	    }
	    else {
	      line=osD.str()+"/"+osU.str()+"\t"+line;
	    }
	  } else {				
	    if(dsNames[ids-1]!=sigName) {
	      line+="1\t";
	    }
	    else {
	      line="1\t"+line;
	    }
	  }
	
	}//find ds
      }//dsname 2
      
      if(!exists) {
	line+="-\t";
	central = numbers[0].second[ids][0]["tot"];
	central=(central<=0)?0.0001:central;
	vals.push_back( central );
	vals.push_back( central );
	vals.push_back( central );
	tmpMap[ dsNames[ids-1] ]=vals;
      }
    }//dsName

    //adding the header ==========================
    if(nuisParScheme[it->first]!="shape") {
      lines[ "NP_"+it->first ] = it->first+"\tlnN\t"+line;
    } else {
      lines[ "NP_"+it->first ] = it->first+"\tshape\t"+line;
      shapes[ it->first ] = tmpMap;
    }
  }

  //=================================================================
  // and the stat uncertainty
  for(unsigned int ids=1;ids<dsNames.size()+1;ids++) {
    float unc= numbers[0].second[ids][1]["tot"]/numbers[0].second[ids][0]["tot"];
    float central=numbers[0].second[ids][0]["tot"];
    central=(central<=0)?0.0001:central;
    if(unc<0) unc*=-1;
    if(numbers[0].second[ids][0]["tot"]==0) unc=0;

    stringstream osN;
    osN<<setprecision(3)<<numbers[0].second[ids][4]["tot"];

    string line="";
    map<string, vector<float> > tmpMap;
    
    //single case
    //if(intNuisPars.find(dsNames[ids-1]+"stat")==intNuisPars.end() ) continue;

    //multicase
    bool exists=false;
    bool gmN=false;

    map<string,vector<string> >::const_iterator it;
    for( it=intNuisPars.begin();it!=intNuisPars.end(); it++) {
      if(nuisParExt[ it->first ] == true ) continue;
      if(it->first.find("_OW")!=string::npos) continue;
      if(it->first.find("stat")!=string::npos &&
	 it->first.find(dsNames[ids-1])!=string::npos ) {
	exists=true; 
	if(nuisParScheme[it->first]=="gmN") {
	  if(numbers[0].second[ids][4]["tot"]!=0)
	    unc = numbers[0].second[ids][0]["tot"]/numbers[0].second[ids][4]["tot"]; //effective rate
	  else
	    unc = 1;

	  cout<<numbers[0].second[ids][1]["tot"]<<"  "<<numbers[0].second[ids][0]["tot"]<<"  "<<sqrt(numbers[0].second[ids][4]["tot"])<<"  "<<numbers[0].second[ids][4]["tot"]<<endl;

	  gmN=true;
	}
	break;
      }
    }
    if(!exists) continue;
      
    map<string,vector<string> >::const_iterator it2=intNuisPars.find(it->first+"_OW");
    if(it2!=intNuisPars.end() && !gmN && 
       find( intNuisPars[it->first].begin(), intNuisPars[it->first].end(), _dsNames[ids-1] )==intNuisPars[it->first].end() ) {
      for(unsigned int id=0;id<it->second.size();++id) {
	if(dsNames[ids-1]==it->second[id])
	  unc=atof(nuisParVals[ it2->first ][id].c_str() );
      }
    }

    stringstream os;
    os<<setprecision(4)<<unc;

    
    for(unsigned int ids2=1;ids2<dsNames.size()+1;ids2++) {
      vector<float> vals;
      if(dsNames[ids2-1]==dsNames[ids-1]) {
	
	// cout<<it->first<<"  "<<dsNames[ids-1]<<" -->  "<<unc<<"  "<<numbers[0].second[ids][0]["tot"]<<"  "<<central<<" --> "<<numbers[0].second[ids][0]["tot"]*(1+unc)<<"  "<<numbers[0].second[ids][0]["tot"]*(1-unc)<<" --> "<<(1-unc)<<" "<<(1+unc)<<endl;
	central=numbers[0].second[ids2][0]["tot"];
	// if(dsNames[ids-1]=="T1tttt_1200_450")
	//   cout<<central<<"  "<<numbers[0].second[ids2][0]["tot"]<<endl;
	vals.push_back( central );
	vals.push_back( central*(1+unc) );
	vals.push_back( central*(1-unc) );
	tmpMap[ dsNames[ids2-1] ]=vals;

	if(gmN) {
	  if(dsNames[ids-1]!=sigName) {
	    line += os.str()+"\t";
	  } else {
	    line = os.str()+"\t"+line;
	  }
	}
	else if(nuisParScheme[it->first]=="lnN") {
	  if(dsNames[ids-1]!=sigName) {
	    if(os.str().size()>=3 && os.str().substr(2,1)==".") // very long numbers	
	      line += os.str().substr(0,4)+"\t";
	    else if(os.str()!="1" && os.str()!="0")
	      line+="1."+os.str().substr(2,3)+"\t";
	    else if(os.str()=="1")
	      line+=os.str()+"\t";
	    else
	      line+="1.00\t";
	  } else {
	    if(os.str().size()>=3 && os.str().substr(2,1)==".") // very long numbers	
	      line=os.str().substr(0,4)+"\t"+line;
	    else if(os.str()!="1" && os.str()!="0")
	      line="1."+os.str().substr(2,3)+"\t"+line;
	    else if(os.str()=="1")
	      line=os.str()+"\t"+line;
	    else
	      line="1.00\t"+line;
	  }
	} else { //shape
	  if(dsNames[ids-1]!=sigName) {
	    line+="1\t";
	  } else {
	    line="1\t"+line;
	  }
	}
      }
      else if(dsNames[ids2-1].find("data")==string::npos) {
	if(dsNames[ids2-1]!=sigName) {
	  line+="-\t";	
	} else {
	  line="-\t"+line;	
	}
	central=numbers[0].second[ids2][0]["tot"];
	central=(central<=0)?0.0001:central;
	vals.push_back( central );
	vals.push_back( central );
	vals.push_back( central );
	tmpMap[ dsNames[ids2-1] ]=vals;
      }
    }
    
    //single case
    if(nuisParScheme[it->first]=="lnN")
      lines[ "NP_"+dsNames[ids-1]+"stat" ] = it->first+"\tlnN\t"+line;
    else if(nuisParScheme[it->first]=="gmN")
      lines[ "NP_"+dsNames[ids-1]+"stat" ] = it->first+"\tgmN "+osN.str()+"\t"+line;
    else if(nuisParScheme[it->first]=="shape") {
      string nUnc=categ;
      if(categ.find("global_")!=string::npos) nUnc=categ.substr(7,categ.size()-7);
      lines[ "NP_"+dsNames[ids-1]+nUnc+"stat" ] = dsNames[ids-1]+nUnc+"stat"+"\tshape\t"+line;
      //cout<<" ==> "<<tmpMap[ dsNames[ids-1] ][1]<<"  "<<tmpMap[ dsNames[ids-1] ][2]<<endl;
      shapes[ dsNames[ids-1]+nUnc+"stat" ] = tmpMap;
    }
   
    //}
  }//dsnames
  if(sumBkg+sumSig==0) return false;
  return true;
}

void
AnaUtils::setSkipCut(vector<string> var, bool invCut) {

  if(!invCut)
    _skipCut=(var.size()!=0);
  if(var.size()!=0)
    _invCut=invCut;
  
  for(size_t i=0;i<var.size();i++)
    _nm1Var.insert(var[i]);
}

void 
AnaUtils::setCurrentWorkflow(int wf) {
  _curWF = wf;
  _isMultiWF=false;
}

void
AnaUtils::setMultiWorkflow(vector<int> wfs) {
  _multiWFs=wfs;
  _isMultiWF=true;
}

void AnaUtils::setNumbers(int ids,string cName, int iCateg, float w, bool acc) {
  


  _effMap[ ids ][ iCateg ][ cName ].NTot +=1;
  _effMap[ ids ][ iCateg ][ cName ].sumwTot +=w;
  _effMap[ ids ][ iCateg ][ cName ].sumw2Tot +=w*w;


  if(_dsNames[ids]!="data" && _dsNames[ids]!="Data" && 
     _dsNames[ids].find("sig")==(size_t)-1) {
    _effMap[ _kMC ][ iCateg ][ cName ].NTot +=1;
    _effMap[ _kMC ][ iCateg ][ cName ].sumwTot +=w;
    _effMap[ _kMC ][ iCateg ][ cName ].sumw2Tot +=w*w;
  }

  if(acc) {
    _effMap[ ids ][ iCateg ][ cName ].N +=1;
    _effMap[ ids ][ iCateg ][ cName ].sumw +=w;
    _effMap[ ids ][ iCateg ][ cName ].sumw2 +=w*w;

    if(_dsNames[ids]!="data" && _dsNames[ids]!="Data" && 
       _dsNames[ids].find("sig")==(size_t)-1) {
      _effMap[ _kMC ][ iCateg ][ cName ].N +=1;
      _effMap[ _kMC ][ iCateg ][ cName ].sumw +=w;
      _effMap[ _kMC ][ iCateg ][ cName ].sumw2 +=w*w;
    }

  }

}


void AnaUtils::setNumFromStat(int ids, string cName, int iCateg, float sw, float esw, int ngen) {
 
  _effMap[ ids ][ iCateg ][ cName ].NTot +=ngen;
  _effMap[ ids ][ iCateg ][ cName ].sumwTot +=sw;
  _effMap[ ids ][ iCateg ][ cName ].sumw2Tot +=esw*esw;

  if(_dsNames[ids]!="data" && _dsNames[ids]!="Data" && 
     _dsNames[ids].find("sig")==(size_t)-1) {
    _effMap[ _kMC ][ iCateg ][ cName ].NTot +=ngen;
    _effMap[ _kMC ][ iCateg ][ cName ].sumwTot +=sw;
    _effMap[ _kMC ][ iCateg ][ cName ].sumw2Tot +=esw*esw;
  }

  _effMap[ ids ][ iCateg ][ cName ].N +=ngen;
  _effMap[ ids ][ iCateg ][ cName ].sumw +=sw;
  _effMap[ ids ][ iCateg ][ cName ].sumw2 +=esw*esw;

  if(_dsNames[ids]!="data" && _dsNames[ids]!="Data" && 
     _dsNames[ids].find("sig")==(size_t)-1) {
    _effMap[ _kMC ][ iCateg ][ cName ].N +=ngen;
    _effMap[ _kMC ][ iCateg ][ cName ].sumw +=sw;
    _effMap[ _kMC ][ iCateg ][ cName ].sumw2 +=esw*esw;
  }

}


void 
AnaUtils::reset() {

  _effMap.clear();
  _dsNames.clear();
  _categories.clear();
  
  //MC initialization
  eMap tmp;
  _effMap.push_back( tmp );
  _dsNames[ _kMC ]="MC";

}


void
AnaUtils::setDDCuts(vector<string> ddcuts) {
  
  for(size_t i=0;i<ddcuts.size();i++) {
    _bkgFC.insert( ddcuts[i] );
  }

}



hObs 
AnaUtils::cloneHObs(const hObs* o1) {

  hObs o2;
  for(size_t ih=0;ih<o1->hs.size();ih++) {
    o2.hs.push_back((TH1*)o1->hs[ih]->Clone());
  } 
  
  o2.nBX = o1->nBX;
  o2.nBY = o1->nBY;
  o2.binsX = o1->binsX;
  o2.binsY = o1->binsY;
  
  o2.htype = o1->htype;
  o2.titleX = o1->titleX;
  o2.titleY = o1->titleY;
  o2.name = o1->name;
  o2.type = o1->type;
  
  return o2;
}


//====================================================
//====================================================
