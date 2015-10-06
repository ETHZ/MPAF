#include "src/DataBaseManager.hh"



using namespace std;

DataBaseManager::DataBaseManager() {
  _strIdx=0;
}

DataBaseManager::~DataBaseManager() {
}

void
DataBaseManager::loadDb(string key,string dbName) {
  readDb(key,dbName);
}

void
DataBaseManager::loadDb(string key,string dbName, string hname) {
  readDbHisto(key,dbName,hname);
}


void
DataBaseManager::readDb(string key, string dbName) {

  bool header=true;
  int nV=0;
  int nE=0;
  int nN=0;
  vector<int> strIdxs;
  
  map<int, int* > idxs;
  
  string ndb= (string)getenv("MPAF")+"/workdir/database/"+dbName;
  ifstream fDb( ndb.c_str(), ios::in );

  if(fDb)
    {
      string line;
      while(getline(fDb, line)) 
        {
      //cout << line << endl;

      istringstream iss(line);
      vector<string> tks;
      copy(istream_iterator<string>(iss),
           istream_iterator<string>(),
           back_inserter<vector<string> >(tks));

      if(line.size()<2 || line.substr(0,2)=="//") {

        if(header) {
          
          nN=tks.size();
          for(int is=0;is<nN;is++) {
        if(tks[is].find("v")!=(size_t)-1 || tks[is].find("V")!=(size_t)-1
           || tks[is].find("vs")!=(size_t)-1 || tks[is].find("VS")!=(size_t)-1)
          nV++;     
          
        if(tks[is].find("vs")!=(size_t)-1 || tks[is].find("VS")!=(size_t)-1)
          strIdxs.push_back(nV-1);
          }

          nE=tks.size()-nV-1;
          
          vector<vector<float> > tmp(nV,vector<float>(0,0)); 
          _cDbLim[key] = tmp;
          
          header=false;
        }
      
        continue;
      }
      else if(header) {
        cout<<" Error, no header in the database file : "<<dbName<<endl;
      }

      // now read the database =====================================

      for(int i=0;i<nV;i++) {
        
        float val = atof(tks[i].c_str());
        for(size_t idx=0;idx<strIdxs.size();idx++)
          if(strIdxs[idx] == i ) {
        val = _strIdx;
        _mStrIdx[tks[i]+key] = _strIdx;
        _strIdx++;
          }

        bool isReg=false;
        for(size_t ib=0;ib<_cDbLim[key][i].size();ib++) {
          if(_cDbLim[key][i][ib]==val ||
         fabs(_cDbLim[key][i][ib]-val) < 0.00001 ) isReg=true; // ... = condition does not perfectly work
        }

        if(!isReg) {
          _cDbLim[key][i].push_back( val );
        }
      }

    } //first reading to have the size
      
      //ugly :( why ROOT does not support vectors...
      int* nBins=new int(nV);
      double* min=new double(nV);
      double* max=new double(nV);

      for(int i=0;i<nV;i++) {
    _cDbLim[key][i].push_back( _cDbLim[key][i].back()+1 ); //last bin

    nBins[i] = _cDbLim[key][i].size();
    min[i] = _cDbLim[key][i][0];
    max[i] = _cDbLim[key][i].back();
      }
      
      
      _mDBs[ key ] = new THnSparseF(key.c_str(),key.c_str(),nV,nBins,min,max);
      _mDBEHs[ key ] = new THnSparseF((key+"EH").c_str(),(key+"EH").c_str(),nV,nBins,min,max);
      _mDBELs[ key ] = new THnSparseF((key+"EL").c_str(),(key+"EL").c_str(),nV,nBins,min,max);
      
      //size is registered, now fill the THnSpare
      fDb.clear();
      fDb.seekg (0, fDb.beg);
      
      while(getline(fDb, line)) 
    {
      
      istringstream iss(line);
      vector<string> tks;
      copy(istream_iterator<string>(iss),
           istream_iterator<string>(),
           back_inserter<vector<string> >(tks));
        
      if(line.size()<2 || line.substr(0,2)=="//") {
        continue;
      }

      int* vbin=new int[nV];
      
      for(int i=0;i<nV;i++) {
        
        float val = atof(tks[i].c_str());
        for(size_t idx=0;idx<strIdxs.size();idx++)
          if(strIdxs[idx] == i ) {
        val = _mStrIdx[tks[i]+key];
          }
        
        vbin[i] = StatUtils::findBin<float>(val, _cDbLim[key][i]);
      }
      
      _mDBs[ key ]->SetBinContent(vbin, atof(tks[nV].c_str()) ); //value
      idxs[  _mDBs[ key ]->GetBin( vbin ) ] = vbin;

      switch(nE) {

      case 0:
        _mDBEHs[ key ]->SetBinContent(vbin, 0 );
        _mDBELs[ key ]->SetBinContent(vbin, 0 );
        break;

      case 1:
        _mDBEHs[ key ]->SetBinContent(vbin, atof(tks[nV+1].c_str()) );
        _mDBELs[ key ]->SetBinContent(vbin, atof(tks[nV+1].c_str()) );
        break;

      case 2:
        _mDBEHs[ key ]->SetBinContent(vbin, atof(tks[nV+1].c_str()) );
        _mDBELs[ key ]->SetBinContent(vbin, atof(tks[nV+2].c_str()) );
        break;
        
      case 3:
        {
          float em = sqrt( pow( atof(tks[nV+1].c_str()), 2) + pow( atof(tks[nV+3].c_str()), 2) );
          float eM =  sqrt( pow( atof(tks[nV+2].c_str()), 2) + pow( atof(tks[nV+3].c_str()), 2) );
          _mDBEHs[ key ]->SetBinContent(vbin, em );
          _mDBELs[ key ]->SetBinContent(vbin, eM );
        break;
        }       

      default:
        cout<<"Error, database format unrecognized ( "<<dbName<<" ) "<<endl;
        abort();
        break;
      }
      
    }//getline

      fDb.close();
    }//file
  else {
    cout<<"Error, no such database : "<<dbName<<endl;
    abort();
  }

  _cDbIdx[ key]=idxs;

}



void
DataBaseManager::readDbHisto(string key, string dbName, string hname) {

  string ndb= (string)getenv("MPAF")+"/workdir/database/"+dbName;
  TFile* dbFile=new TFile( ndb.c_str() ,"READ");
 
  TObject* obj =dbFile->Get(hname.c_str());

  TString cName = obj->ClassName();

  int nV=0;
  // int nE=0;
  // int nN=0;

  map<int, int* > idxs;

  bool graph=false;

  if( ((string)cName).find("2")!=(size_t)-1) { //2D histo
    nV=2;
  }
  else if( ((string)cName).find("3")!=(size_t)-1) { //3D histo
    nV=3;
  }
  else if( ((string)cName).find("Graph")!=(size_t)-1) {//graph...
    nV=1; graph=true;
  }
  else{ //1D histo, or profile, or something strange that noone does but the W guys
    nV=1;  
  }

  //cout<< nV<<"   "<<cName<<((string)cName).find("2")<<endl;

  vector<vector<float> > tmp(nV,vector<float>(0,0)); 
  _cDbLim[key] = tmp;

  if(!graph) {
    for(int i=1;i<((TH1*)obj)->GetNbinsX()+2;i++) {
      _cDbLim[key][0].push_back( ((TH1*)obj)->GetXaxis()->GetBinLowEdge(i) );
    }  
  }
  else {
    double x(0.),y(0.),ex(0.);
    for(int i=0;i<((TGraph*)obj)->GetN();i++) {
      ((TGraph*)obj)->GetPoint(i,x,y);
      ex = ((TGraph*)obj)->GetErrorXlow(i);
      _cDbLim[key][0].push_back( x-ex );
    }
    _cDbLim[key][0].push_back( x+ex );  
  }

  if(nV>=2)     
    for(int i=1;i<((TH2*)obj)->GetNbinsY()+2;i++) {
      _cDbLim[key][1].push_back( ((TH2*)obj)->GetYaxis()->GetBinLowEdge(i) );
    }
  if(nV>=3)
    for(int i=1;i<((TH3*)obj)->GetNbinsZ()+2;i++) {
      _cDbLim[key][2].push_back( ((TH3*)obj)->GetZaxis()->GetBinLowEdge(i) );
    }
 
  //ok, now create and fill the DB
  
  //ugly :( why ROOT does not support vectors...
  int* nBins=new int(nV);
  double* min=new double(nV);
  double* max=new double(nV);

  for(int i=0;i<nV;i++) {
    nBins[i] = _cDbLim[key][i].size();
    min[i] = _cDbLim[key][i][0];
    max[i] = _cDbLim[key][i].back();
  }
     
  _mDBs[ key ] = new THnSparseF(key.c_str(),key.c_str(),nV,nBins,min,max);
  _mDBEHs[ key ] = new THnSparseF((key+"EH").c_str(),(key+"EH").c_str(),nV,nBins,min,max);
  _mDBELs[ key ] = new THnSparseF((key+"EL").c_str(),(key+"EL").c_str(),nV,nBins,min,max);

  switch(nV) {

  case 1:
    {
      if(!graph) {
    int nB= _cDbLim[key][0].size();
    for(int i=0;i<nB;i++ ) {
      int vbin[1]={ i };
      _mDBs[ key ]->SetBinContent( vbin,  (i<nB)?((TH1*)obj)->GetBinContent(vbin[0]+1 ):1. );
      _mDBEHs[ key ]->SetBinContent(vbin, (i<nB)?((TH1*)obj)->GetBinError( vbin[0]+1 ):1. );
      _mDBELs[ key ]->SetBinContent(vbin, (i<nB)?((TH1*)obj)->GetBinError( vbin[0]+1 ):1. );

      idxs[  _mDBs[ key ]->GetBin( vbin ) ] = vbin;
    }
      }
      else {
    int nB= _cDbLim[key][0].size();
    double x,y,ey;
    for(int i=0;i<nB;i++ ) {
      int vbin[1]={ i };
      ((TGraph*)obj)->GetPoint(i,x,y);
      ey = ((TGraph*)obj)->GetErrorY(i);
      _mDBs[ key ]->SetBinContent( vbin,  (i<nB)?y:1. );
      _mDBEHs[ key ]->SetBinContent(vbin, (i<nB)?ey:1. );
      _mDBELs[ key ]->SetBinContent(vbin, (i<nB)?ey:1. );

      idxs[  _mDBs[ key ]->GetBin( vbin ) ] = vbin;
    }
      }    
      break;
    }
  case 2:
    {
     int nBx= _cDbLim[key][0].size();
     int nBy= _cDbLim[key][1].size();
     for(int i=0;i<nBx;i++ ) {
       for(int j=0;j<nBy;j++ ) {
     int vbin[2]={ i, j };
     _mDBs[ key ]->SetBinContent( vbin, (i<nBx && j<nBy)?((TH2*)obj)->GetBinContent( vbin[0]+1, vbin[1]+1 ):1. );
     _mDBEHs[ key ]->SetBinContent( vbin, (i<nBx && j<nBy)?((TH2*)obj)->GetBinError( vbin[0]+1, vbin[1]+1 ):1. );
     _mDBELs[ key ]->SetBinContent( vbin, (i<nBx && j<nBy)?((TH2*)obj)->GetBinError( vbin[0]+1, vbin[1]+1 ):1. );
     
     idxs[  _mDBs[ key ]->GetBin( vbin ) ] = vbin;
       }//i    
     }//j
     break;
   }
  case 3:
    {
      int nBx= _cDbLim[key][0].size();
      int nBy= _cDbLim[key][1].size();
      int nBz= _cDbLim[key][2].size();
      for(int i=0;i<nBx;i++ ) {
    for(int j=0;j<nBy;j++ ) {
      for(int k=0;k<nBz;k++ ) {
        int vbin[3]={ i, j, k };
        _mDBs[ key ]->SetBinContent( vbin, (i<nBx && j<nBy && k<nBz)?((TH3*)obj)->GetBinContent( vbin[0]+1, vbin[1]+1, vbin[2]+1 ):1. );
        _mDBEHs[ key ]->SetBinContent( vbin, (i<nBx && j<nBy && k<nBz)?((TH3*)obj)->GetBinError( vbin[0]+1, vbin[1]+1, vbin[2]+1 ):1. );
        _mDBELs[ key ]->SetBinContent( vbin, (i<nBx && j<nBy && k<nBz)?((TH3*)obj)->GetBinError( vbin[0]+1, vbin[1]+1, vbin[2]+1 ):1. );

        idxs[  _mDBs[ key ]->GetBin( vbin ) ] = vbin;
      }//k    
    }//j
      }//i
      break;
    } 
  default:
    cout<<" error in root db treatment... "<<dbName<<"/"<<hname<<endl;
    abort();
    break;
  }

  _cDbIdx[ key]=idxs;
  
  dbFile->Close();
  
}

vector<vector<float> >
DataBaseManager::getDB(string key) {
  
  int nBins=_mDBs[ key ]->GetNbins();

  vector<vector<float> > db;

  //THnIter* _mDBs[ key ]->CreateIter();

  for(int ib=0;ib<nBins;ib++) {
    
    vector<float> vals;

    int* vbin=new int[ _cDbLim[key].size() ];
    vbin=_cDbIdx[ key ][ib];
    
    bool skip=false;
    for(size_t i=0;i<_cDbLim[key].size();i++) {
      if(vbin[i]==-1) {skip=true; break;}
    }
    
    if(skip) continue;

    for(size_t i=0;i<_cDbLim[key].size();i++)
      if(vbin[i]!=-1) vals.push_back( _cDbLim[key][ i ][ vbin[i] ] );

    vals.push_back( _mDBs[ key ]->GetBinContent( vbin ) );
    vals.push_back( _mDBEHs[ key ]->GetBinContent( vbin ) );
    vals.push_back( _mDBELs[ key ]->GetBinContent( vbin ) );
    
    db.push_back(vals);
  }
 

  return db;

}

bool
DataBaseManager::exists(string key) {
  std::map<std::string, THnSparseF*>::const_iterator it;
  it= _mDBs.find(key);
  return (it!=_mDBs.end());
}

float 
DataBaseManager::getDBValue(string key, float v1, float v2, float v3, float v4,
                float v5, float v6,float v7, float v8, float v9, float v10) {

  if(!exists(key) ) {
    cout<<"WARNING!! no database "<<key<<" registered! "<<endl;
    return 1;
  }

  float vals[10]={v1,v2,v3,v4,v5,v6,v7,v8,v9,v10};
  int vbin[10]={0,0,0,0,0,0,0,0,0,0};

  for(size_t i=0;i<_cDbLim[key].size();i++) {
    if(vals[i]!=-1000000) {
      vbin[i] = StatUtils::findBin<float>( vals[i], _cDbLim[key][i] );
      if(vbin[i]==-1) return 1;
    }
  }

  return _mDBs[ key ]->GetBinContent( vbin );
}


float 
DataBaseManager::getDBErrH(string key, float v1, float v2, float v3, float v4,
               float v5, float v6,float v7, float v8, float v9, float v10) {

  if(!exists(key) ) {
    cout<<"WARNING!! no database "<<key<<" registered! "<<endl;
    return 1;
  }

  float vals[10]={v1,v2,v3,v4,v5,v6,v7,v8,v9,v10};
  int vbin[10]={0,0,0,0,0,0,0,0,0,0};

  for(size_t i=0;i<_cDbLim[key].size();i++) {
    if(vals[i]!=-1000000) {
      vbin[i] = StatUtils::findBin( vals[i], _cDbLim[key][i] );
      if(vbin[i]==-1) return 1;
    }
    
  }
  
  return _mDBEHs[ key ]->GetBinContent( vbin );
}

float 
DataBaseManager::getDBErrL(string key, float v1, float v2, float v3, float v4,
               float v5, float v6,float v7, float v8, float v9, float v10) {

  if(!exists(key) ) {
    cout<<"WARNING!! no database "<<key<<" registered! "<<endl;
    return 1;
  }

  float vals[10]={v1,v2,v3,v4,v5,v6,v7,v8,v9,v10};
  int vbin[10]={0,0,0,0,0,0,0,0,0,0};

  for(size_t i=0;i<_cDbLim[key].size();i++) {
    if(vals[i]!=-1000000) {
      vbin[i] = StatUtils::findBin( vals[i], _cDbLim[key][i] );
      if(vbin[i]==-1) return 1;
    }
    
  }
  
  return _mDBELs[ key ]->GetBinContent( vbin );
}


float 
DataBaseManager::getDBValue(string key, string v1) {
  
  _mSIt = _mStrIdx.find(v1+key);
  if(_mSIt==_mStrIdx.end()) {
    cout<<"Warning, no value "<<v1<<" in database"<<key<<endl;
    return -1000;
  }

  return getDBValue(key, _mSIt->second);
}

float 
DataBaseManager::getDBErrL(string key, string v1) {
 _mSIt = _mStrIdx.find(v1+key);
  if(_mSIt==_mStrIdx.end()) {
    cout<<"Warning, no value "<<v1<<" in database"<<key<<endl;
    return -1000;
  }

  return getDBErrL(key, _mSIt->second);
}

float
DataBaseManager::getDBErrH(string key, string v1){
 _mSIt = _mStrIdx.find(v1+key);
  if(_mSIt==_mStrIdx.end()) {
    cout<<"Warning, no value "<<v1<<" in database"<<key<<endl;
    return -1000;
  }

  return getDBErrH(key, _mSIt->second);
}
