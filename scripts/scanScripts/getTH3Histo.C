#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TH3D.h>
#include <string>

using namespace std;

void getTH3Histo(){

  ifstream ifile("/shome/cheidegg/d/MPAF/scripts/scanScripts/filesScan", ios::in );
  
  TH3D* h3(0);
  
  if(ifile) {
    string line;
    bool first=true;
    while(getline(ifile, line)) 
      {
	cout<<line<<endl;
    if(line.find("psi.ch") != (size_t) -1) line = "dcap://t3se01.psi.ch:22125/" + line;
	TFile* file=TFile::Open(line.c_str());
	cout<<file<<endl;
	TH3D* htmp=(TH3D*)file->Get("CountSMS");
	cout<<htmp<<endl;
	if(first) {
	  first=false;
	  h3=(TH3D*)(htmp->Clone());
	  h3->SetDirectory(0);
	} else  {
	  // cout<<h3<<"  "<<htmp<<endl;
	  // cout<<htmp->Integral()<<endl;
	  // cout<<h3->Integral()<<endl;
	  h3->Add( (TH3D*)htmp->Clone() );
	  //cout<<" oh yeah "<<endl;
	}
	//cout<<"youpi "<<endl;
	delete htmp;
	delete file;
      }
    ifile.close();
  }
  
  TFile* ofile=new TFile("histoScanT1tttt.root","recreate");
  ofile->cd();
  h3->Write();
  ofile->Write();
  ofile->Close();

}
