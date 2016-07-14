void PrintXfactor(char* path1, char* file1, char* ma1, char* ma2)
{
/*
root -q -b  TTWToLNu.root ~/Anal_Macros/MacrosMPAF/PrintXfactor.C 
*/
  //std::string path = "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-12-04-21-54-00";
  //std::string file = "T1tttt-1000-0-.root";
  
  std::string path = path1;
  std::string file = file1;
  std::string mass1 = ma1;
  std::string mass2 = ma2;
  int m1 = atoi(mass1.c_str());
  int m2 = atoi(mass2.c_str());

  //gROOT->SetBatch();
  std::string file = "dcap://t3se01.psi.ch:22125/" + path + '/'+ file;
  std::cout << file << std::endl;

  TFile *_file0 = TFile::Open(file.c_str());

  TH1F* hNom = new TH1F("hNom", "hNom", 1, 0, 2);
  TH1F* hUp = new TH1F("hUp", "hUp", 1, 0, 2);
  TH1F* hDw = new TH1F("hDw", "hDw", 1, 0, 2);

  TString n = gDirectory->GetName();
  n.ReplaceAll(".root", "");
  
  //tree->Scan("LHEweight_id[0]");//[0] corersponds to ID 1001; [4] to 1005; [8] to 1009
    
  tree->Draw("1>>hNom", "LHEweight_wgt[0]");
  tree->Draw("1>>hUp", "LHEweight_wgt[4]");
  tree->Draw("1>>hDw", "LHEweight_wgt[8]");
  
  double Xup = 0;
  double Xdw = 0;
  
  double nom = hNom->GetBinContent(1);
  double up = hUp->GetBinContent(1);
  double dw = hDw->GetBinContent(1);
  if (up != 0) Xup = nom/up;
  if (dw != 0) Xdw = nom/dw;
  
  std::ofstream out; 
  std::cout.rdbuf(out.rdbuf());  
  
  out.open("T1tttt_X_factors.txt",ios::app);    // open file for appending
  assert (!out.fail( ));
  
  int dirup = 10;
  int dirdown = 20;
    //std::cout << n << "\t" << nom << "\t" << up << "\t" << dw << "\t" << Xup << "\t" << Xdw << std::endl; 
  std::cout << dirup << "\t" << mass1 << "\t" << mass2 << "\t" << "\t" << Xup << "\n";// << std::endl; 
  std::cout << dirdown << "\t" <<mass1 << "\t" << mass2 << "\t" << "\t" << Xdw << "\n";// << std::endl; 
}
