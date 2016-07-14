#include "analysis/utils/Parser.hh"

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iterator>

using namespace std;

inPar
Parser::parseLine(string line) {

  istringstream iss(line);
  vector<string> tks;
  copy(istream_iterator<string>(iss),
       istream_iterator<string>(),
       back_inserter<vector<string> >(tks));


  inPar ip;  
  ip.type=Parser::kNone;
  if(tks.size()==0 || tks[0].substr(0,1)=="#" ) return ip;
  
  int type=Parser::kNone;
  if(tks[0]=="dir")
    type=Parser::kDir;
  if(tks[0]=="ans")
    type=Parser::kAN;
  if(tks[0]=="user")
    type=Parser::kUsr;
  if(tks[0]=="verb")
    type=Parser::kVbs;
  if(tks[0]=="skim")
    type=Parser::kSkim;
  if(tks[0]=="nmax")
    type=Parser::kNMax;
  if(tks[0]=="nskip")
    type=Parser::kSkip;
  if(tks[0]=="var")
    type=Parser::kVar;
  if(tks[0]=="histo")
    type=Parser::kHisto;
  if(tks[0]=="wgthisto")
    type=Parser::kWgtHisto;
  if(tks[0]=="tree")
    type=Parser::kTree;
  if(tks[0]=="ds")
    type=Parser::kDS;
  if(tks[0]=="ft")
    type=Parser::kFT;
  if(tks[0]=="summary")
    type=Parser::kSummary;
  if(tks[0]=="systOnly")
    type=Parser::kSyst;
  if(tks[0]=="counterOpt")
    type=Parser::kCounter;

  string val = tks[1];

  vector<string> opts;
  for(size_t i=2;i<tks.size();i++) {
    if(tks[i].substr(0,1)!="#")
      opts.push_back(tks[i]);
  }
  
  string id=tks[0];
  if(type==Parser::kVar || type==Parser::kDS || type==Parser::kFT)
    id = val;
  if(type==Parser::kDS) {
    for(size_t i=0;i<opts.size();i++) {
      if(opts[i].substr(0,4)=="pfx:") {
        id += opts[i].substr(4, opts[i].size()-4 );
        //val+= opts[i].substr(4, opts[i].size()-4 );
      }
    }
  }

  ip.type = type;
  ip.id = id;
  ip.val = val;
  ip.opts = opts;

  return ip;
}


MIPar
Parser::parseFile(string filename) {

  ifstream fDb( filename.c_str(), ios::in );
  
  MIPar mip;

  if(fDb) {
    string line;

    while(getline(fDb, line)) 
      {
	inPar p=parseLine(line);
	if(p.type==Parser::kNone) continue;
	mip[ p.id ] = p;
      }
    fDb.close();
  }
  else {
    cout<<"Error, configuration file "<<filename<<" does not exists, aborting..."<<endl;
    abort();
  }
  
  return mip;
}
