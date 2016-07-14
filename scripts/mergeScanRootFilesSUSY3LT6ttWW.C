#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>

#include "TError.h"
#include "TFile.h"
#include "TF1.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"


void mergeScanRootFiles(string ofileName="/shome/mmarionn/MPAF/workdir/root/SSDL2015/mergedssdlScanV2.root"){



  // istringstream iss(files);
  // vector<string> tks;
  // copy(istream_iterator<string>(iss),
  //      istream_iterator<string>(),
  //      back_inserter<vector<string> >(tks));

  TFile* ofile=new TFile(ofileName.c_str(),"recreate");
  ofile->mkdir("nEvtProc");
  ofile->mkdir("sumWgtProc");

  for(int it=0;it<tks.size();it++) {
    cout<<tks[it]<<"   "<<it<<"/"<<tks.size()-1<<endl;
    TFile* f=new TFile(tks[it].c_str(), "read");
  
    TIter nextkey(f->GetListOfKeys());
    TKey *key;
    while ((key = ((TKey*)nextkey()))) {
      TObject* obj = key->ReadObj(); 
      //found a TDirectory which can be a variable
      if( (string)obj->IsA()->GetName()!=("TDirectoryFile") ) continue;
      
      string varName(obj->GetName());
      if(varName!="nEvtProc" && varName!="sumWgtProc") continue;

      TIter nextkeyD( ((TDirectory*)obj)->GetListOfKeys() );
      TKey *keyD;
      while ((keyD = ((TKey*)nextkeyD()))) {
	TObject* objD = keyD->ReadObj(); 
	if( objD==nullptr ) continue;
	
	TH1* htmp=(TH1*)((TH1*)objD->Clone());
	
	ofile->cd(varName.c_str());
	htmp->Write();

      }//samples

      // break;//no nee to run over everything if the nevtproc is found
    }//tdirectory
  }//files

  ofile->Close();
 gROOT->ProcessLine(".qqqqqqqqqqqqqqqqqqqqq");
}
