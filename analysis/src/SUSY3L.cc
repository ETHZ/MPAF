/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Jan Hoss, ETHZ, 12/2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#include "analysis/src/SUSY3L.hh"
#include <algorithm>
#include <sstream>
#include <iostream>

/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
SUSY3L::SUSY3L(std::string cfg){
    /* 
        constructs the SUSY3L class 
        parameters: configuration_file
        return: none
    */
	
    //_verbose->Class("SUSY3L");
    startExecution(cfg);
    initialize();
}


//____________________________________________________________________________
SUSY3L::~SUSY3L(){
    /* 
        destructs the SUSY3L class 
        parameters: none
        return: none
    */

}


//____________________________________________________________________________
void SUSY3L::initialize(){
    /*
        initializes the SUSY3L class
        parameters: none
        return: none
    */

    //trigger bits (i.e. decitions of each individual HLT line, in contrast to prcessed OR of a set of lines)
    //non-isolated triggers
    _vTR_lines.push_back("HLT_BIT_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v");
    _vTR_lines.push_back("HLT_BIT_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v");
    _vTR_lines.push_back("HLT_BIT_HLT_DoubleMu8_Mass8_PFHT300_v");
    //isolated triggers 2016
    _vTR_lines.push_back("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");                   //TODO: not in tree yet
    //_vTR_lines.push_back("HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");  
    _vTR_lines.push_back("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");     
    _vTR_lines.push_back("HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");       //TODO: not in tree yet
    _vTR_lines.push_back("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");      //has prescale 0 in column 1e34 

    //_vTR_lines.push_back("HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");  
    
    //isolated triggers 2015
    //_vTR_lines.push_back("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");                  //no longer in 2016 menu
    //_vTR_lines.push_back("HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    //_vTR_lines.push_back("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");  
    //_vTR_lines.push_back("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");      //has prescale 0 in column 1e34 
    //_vTR_lines.push_back("HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v");
    
    //tri-lepton trigger
    //_vTR_lines.push_back("HLT_BIT_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");
    //_vTR_lines.push_back("HLT_BIT_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    //_vTR_lines.push_back("HLT_BIT_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    //_vTR_lines.push_back("HLT_BIT_HLT_TripleMu_12_10_5_v");
    
    //register HLT trigger bit tree variables 
    registerTriggerVars();

    //event characteristics
    _vc->registerVar("run"                             );    //run number
    _vc->registerVar("lumi"                            );    //lumi section number
    _vc->registerVar("evt"                             );    //event number
    _vc->registerVar("isData"                          );    //identify data
    _vc->registerVar("nVert"                           );    //reco number of vertices
    _vc->registerVar("nTrueInt"                        );    //true number of vertices
   
    //leptons 
    _vc->registerVar("nLepGood"                        );    //number of leptons in event
    _vc->registerVar("LepGood_pdgId"                   );    //identifier for leptons (11: electron, 13: muon)
    _vc->registerVar("LepGood_pt"                      );    //pT of leptons
    _vc->registerVar("LepGood_eta"                     );    //eta of leptons track
    _vc->registerVar("LepGood_etaSc"                   );    //eta of leptons super cluster in Ecal
    _vc->registerVar("LepGood_phi"                     );    //phi of leptons
    _vc->registerVar("LepGood_charge"                  );    //charge of lepton +1 or -1
    _vc->registerVar("LepGood_relIso03"                );    //relative isolation of the lepton, cone dimensions?
    _vc->registerVar("LepGood_miniRelIso"              );    //relIso with pt dependent cone
    _vc->registerVar("LepGood_jetPtRatio"              );    //pt lepton over pt aka4 jet
    _vc->registerVar("LepGood_jetPtRatiov2"            );   //
    _vc->registerVar("LepGood_jetPtRel"                );    //
    _vc->registerVar("LepGood_jetPtRelv2"              );    //
    _vc->registerVar("LepGood_dz"                      );    //difference to reconstructed primary vertex in z direction
    _vc->registerVar("LepGood_dxy"                     );    //difference to reconstructed primary vertex in xy plane
    _vc->registerVar("LepGood_sip3d"                   );    //similar observable as dxy, also vertex cut
    _vc->registerVar("LepGood_tightCharge"             );    //indicates reliability of charge measurement, values 0,1,2
    _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1"   );    //indicates reliability of electron identification [-1;4]
    _vc->registerVar("LepGood_convVeto"                );    //0 (veto) or 1 (no veto), calculated from partner track
    _vc->registerVar("LepGood_lostHits"                );    //number of missing hits in pixel detector
    _vc->registerVar("LepGood_tightId"                 );    //0 or 1 (loose and tight criteria?)
    _vc->registerVar("LepGood_dEtaScTrkIn"             );    //delta eta between track and supercluster in Ecal
    _vc->registerVar("LepGood_dPhiScTrkIn"             );    //delta phi between track and supercluster in Ecal
    _vc->registerVar("LepGood_hadronicOverEm"          );    //
    _vc->registerVar("LepGood_sigmaIEtaIEta"           );    //
    _vc->registerVar("LepGood_eInvMinusPInv"           );    //
    _vc->registerVar("LepGood_mediumMuonId"            );    //mva medium wp muon identification
    _vc->registerVar("LepGood_mediumMuonID2016"        );
    _vc->registerVar("LepGood_mvaIdPhys14"             );    //mva electron ID
    _vc->registerVar("LepGood_mvaIdSpring15"           );    //updated mva electron ID
    _vc->registerVar("LepGood_ecalPFClusterIso"        );    
    _vc->registerVar("LepGood_hcalPFClusterIso"        );    
    _vc->registerVar("LepGood_dr03TkSumPt"             );    
    _vc->registerVar("LepGood_mcMatchId"               );    //MC truth information (1 gen-matched, 0 not)
    _vc->registerVar("LepGood_mvaSUSY"                 );    //lepton MVA ID
    _vc->registerVar("LepGood_mcMatchId"               );    
    _vc->registerVar("LepGood_mcPromptGamma"           );
    
    //taus
    _vc->registerVar("nTauGood"                        );    //number of taus in event
    _vc->registerVar("TauGood_pdgId"                   );    //identifier for taus (15)
    _vc->registerVar("TauGood_pt"                      );    //pT of tau
    _vc->registerVar("TauGood_eta"                     );    //eta of tau
    _vc->registerVar("TauGood_phi"                     );    //phi of tau
    _vc->registerVar("TauGood_charge"                  );    //charge of tau +1 or -1
    _vc->registerVar("TauGood_idAntiMu"                );     //tau muon discriminator
    _vc->registerVar("TauGood_idAntiE"                 );     //tau electron discriminator
    _vc->registerVar("TauGood_idDecayMode"             );     //
    _vc->registerVar("TauGood_isoCI3hit"               );     //


    vector<string> extsJEC({"","_jecUp","_jecDown"});
    for(unsigned int ie=0;ie<extsJEC.size();ie++) {

        //missing transverse energy
        _vc->registerVar("met"+extsJEC[ie]+"_pt"                          );     //missing tranvers momentum
        _vc->registerVar("met"+extsJEC[ie]+"_phi"                         );     //phi of missing transvers momentum

        //jets
        _vc->registerVar("nJet"+extsJEC[ie]                               );    //number of jets in the event
        _vc->registerVar("Jet"+extsJEC[ie]+"_pt"                          );    //pT of each of the nJet jets
        _vc->registerVar("Jet"+extsJEC[ie]+"_eta"                         );    //eta of each of the nJet jets
        _vc->registerVar("Jet"+extsJEC[ie]+"_phi"                         );    //phi of each of the nJet jets
        _vc->registerVar("Jet"+extsJEC[ie]+"_id"                          );    //jet identifier (>=1: 8TeV loose recommendation)
        _vc->registerVar("Jet"+extsJEC[ie]+"_btagCSV"                     );     //b-tagging quantity (-1 or [0;1]
        _vc->registerVar("Jet"+extsJEC[ie]+"_muEF"                        );     //fraction of muon pt in jet
        _vc->registerVar("Jet"+extsJEC[ie]+"_mass"                        );     //jet mass
        _vc->registerVar("Jet"+extsJEC[ie]+"_rawPt"                       );
        _vc->registerVar("Jet"+extsJEC[ie]+"_mcFlavour"                   );

        //discarded jets (because of leptons cleaning)
        _vc->registerVar("nDiscJet"+extsJEC[ie]                           );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_id"                      );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_pt"                      );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_rawPt"                   );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_eta"                     );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_phi"                     );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_mass"                    );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_btagCSV"                 );
        _vc->registerVar("DiscJet"+extsJEC[ie]+"_mcFlavour"               );

    }

    //forward jets
    _vc->registerVar("nJetFwd"                         );
    _vc->registerVar("JetFwd_pt"                       );
    _vc->registerVar("JetFwd_phi"                      );

    //HLT lines
    _vc->registerVar("HLT_DoubleMu"                    );     //HLT trigger path decition (1 fired, 0 else)
    _vc->registerVar("HLT_SingleMu"                    );
    _vc->registerVar("HLT_DoubleEl"                    );
    _vc->registerVar("HLT_SingleEl"                    );
    _vc->registerVar("HLT_MuEG"                        );
    _vc->registerVar("HLT_DoubleMuHT"                  );
    _vc->registerVar("HLT_DoubleElHT"                  );
    _vc->registerVar("HLT_TripleEl"                    );
    _vc->registerVar("HLT_TripleMu"                    );
    _vc->registerVar("HLT_DoubleMuEl"                  );
    _vc->registerVar("HLT_DoubleElMu"                  );
   
    //variables for validation plots
    _vc->registerVar("nLepGood10"                      );    //number of leptons in event with pt>10
    _vc->registerVar("mZ1"                             );    //
    _vc->registerVar("minMllAFAS"                      );    
    _vc->registerVar("htJet40j"                        );
    _vc->registerVar("nBJetLoose25"                    );
    _vc->registerVar("nBJetMedium25"                   );
    _vc->registerVar("nBJetTight40"                    );
    _vc->registerVar("nJet40"                          );
 
    //event filters 
    _vc->registerVar("hbheFilterNew25ns"               );
    _vc->registerVar("Flag_CSCTightHaloFilter"         );
    _vc->registerVar("Flag_eeBadScFilter"              );   
    _vc->registerVar("hbheFilterIso"                   );
    _vc->registerVar("Flag_goodVertices"               );
    _vc->registerVar("Flag_globalTightHalo2016Filter"  );
    _vc->registerVar("Flag_badChargedHadronFilter"     );
    _vc->registerVar("Flag_badMuonFilter"              );
 
    //weights
    _vc->registerVar("genWeight"                       );       //generator weight to account for negative weights in MCatNLO
    _vc->registerVar("vtxWeight"                       );       //number of vertices for pile-up reweighting 

    //scan variables
    _vc->registerVar("GenSusyMScan1"                   );
    _vc->registerVar("GenSusyMScan2"                   );
    _vc->registerVar("GenSusyMGluino");
    _vc->registerVar("GenSusyMNeutralino");

    //generator information
    _vc->registerVar("nGenPart"                        );
    _vc->registerVar("GenPart_pt"                      );
    _vc->registerVar("GenPart_eta"                     );
    _vc->registerVar("GenPart_phi"                     );
    _vc->registerVar("GenPart_pdgId"                   );
    _vc->registerVar("GenPart_motherId"                );
    _vc->registerVar("GenPart_mass"					   );
    _vc->registerVar("GenPart_charge"				   );
    _vc->registerVar("GenPart_status"				   );

    //LHE gen level weights                                                                                                                                                       
    _vc->registerVar("nLHEweight"                      );
    _vc->registerVar("LHEweight_id"                    );
    _vc->registerVar("LHEweight_wgt"                   );

    //SusyModule for common inputs and functions with RA5
    _susyMod = new SusyModule(_vc, _dbm);

    //categories
    int nCateg=77;
    _categs.resize(nCateg);
    string srs[77]={
     
    //signal regions
        "OnZSR001", "OnZSR002", "OnZSR003", "OnZSR004", "OnZSR005", "OnZSR006", "OnZSR007", "OnZSR008",
	    "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012", "OnZSR013", "OnZSR014", "OnZSR015", "OnZSR016", "OnZSR017",
	
	    "OffZSR001", "OffZSR002", "OffZSR003", "OffZSR004", "OffZSR005", "OffZSR006", "OffZSR007", "OffZSR008",
	    "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012", "OffZSR013", "OffZSR014", "OffZSR015", "OffZSR016", "OffZSR017",

    //signal application regions
        "OnZSR001_Fake", "OnZSR002_Fake", "OnZSR003_Fake", "OnZSR004_Fake", "OnZSR005_Fake", "OnZSR006_Fake", "OnZSR007_Fake", "OnZSR008_Fake",
	    "OnZSR009_Fake", "OnZSR010_Fake", "OnZSR011_Fake", "OnZSR012_Fake", "OnZSR013_Fake", "OnZSR014_Fake", "OnZSR015_Fake", "OnZSR016_Fake", "OnZSR017_Fake",

	    "OffZSR001_Fake", "OffZSR002_Fake", "OffZSR003_Fake", "OffZSR004_Fake", "OffZSR005_Fake", "OffZSR006_Fake", "OffZSR007_Fake", "OffZSR008_Fake",
	    "OffZSR009_Fake", "OffZSR010_Fake", "OffZSR011_Fake", "OffZSR012_Fake", "OffZSR013_Fake", "OffZSR014_Fake", "OffZSR015_Fake", "OffZSR016_Fake", "OffZSR017_Fake",
 
    //baseline regions
        "OnZBaseline", "OffZBaseline",

    //baseline appliction regions
        "OnZBaseline_Fake", "OffZBaseline_Fake",
    
    //global fake
        "Fake", 

    //WZ control region
        "WZCR", "WZCR_Fake",

    //fake control region
        "FakeCR", "FakeCR_Fake"

    };

    _categs.assign(srs, srs+nCateg);

    for(size_t ic=0;ic< _categs.size();ic++){
        _SR = _categs[ic];
        setSignalRegion();
        addWorkflow( ic+1, _categs[ic] );
    }

    //config file input variables
    _onZ = getCfgVarI("onZ", -1);
    _selectMuons = getCfgVarI("selectMuons", true);
    _selectElectrons = getCfgVarI("selectElectrons", true);
    _selectTaus = getCfgVarI("selectTaus", false);
    _BR = getCfgVarS("baselineRegion", "BR0");
    _FR = getCfgVarS("FR" , "FR2016"); 
    _categorization = getCfgVarI("categorization", 1);
    _doPlots = getCfgVarI("doPlots", 1);
    _doPlotsVerbose = getCfgVarI("doPlotsVerbose", 0);
    _doValidationPlots = getCfgVarI("doValidationPlots", 0);
    _fastSim = getCfgVarI("FastSim", 0);
    _closureByFlavor = getCfgVarI("closureByFlavor", 0);
    _closure = getCfgVarI("closure", 0);
    _exactlyThreeLep = getCfgVarI("exactlyThreeLep", 0);
    _debug = getCfgVarI("debug", 0);
    _runSystematics = getCfgVarI("runSystematics", 1);
    _susyProcessName = getCfgVarS("susyProcessName", "T1tttt");
    _LHESYS = getCfgVarI("LHESYS", 0);
    _useLepMVA = getCfgVarI("useLepMVA", 0);
    _doGenMatch = getCfgVarI("doGenMatch", 1);
    _version = getCfgVarI("version", 8);

    if(_fastSim) {
        //load signal cross section
        if(_susyProcessName=="T1tttt" || _susyProcessName=="T5qqqqVV" || _susyProcessName=="T5ttttdeg" || _susyProcessName=="T5tttt"){
            _dbm->loadDb(_susyProcessName+"Xsect", "GluinoGluinoXsect.db");
        }
        if(_susyProcessName=="T6ttWW"){
            _dbm->loadDb(_susyProcessName+"Xsect", "SbottomSbottomXsect.db");
        }
        //load number of generated events
        loadScanHistogram();
    }
    
    //FR databases
    if(_FR=="FO2C") {       // 2015 fake rate maps

        _dbm->loadDb("ElNIso"    , "160116_FR_withIdEmu.root", "FRElPtCorr_UCSX_non");
        _dbm->loadDb("MuNIso"    , "160116_FR_withIdEmu.root", "FRMuPtCorr_UCSX_non");

        _dbm->loadDb("ElNIsoMC"  , "160116_FR_withIdEmu.root", "FRElPtCorr_qcd_non");
        _dbm->loadDb("MuNIsoMC"  , "160116_FR_withIdEmu.root", "FRMuPtCorr_qcd_non");

        _dbm->loadDb("ElNIsoUp"  , "160116_FR_withIdEmu.root", "FRElPtCorr_UCSX_HI_non");
        _dbm->loadDb("MuNIsoUp"  , "160116_FR_withIdEmu.root", "FRMuPtCorr_UCSX_HI_non");
    
        _dbm->loadDb("ElNIsoMCUp", "160116_FR_withIdEmu.root", "FRElPtCorr_qcd_non");
        _dbm->loadDb("MuNIsoMCUp", "160116_FR_withIdEmu.root", "FRMuPtCorr_qcd_non");
    
        _dbm->loadDb("ElNIsoDo"  , "160116_FR_withIdEmu.root", "FRElPtCorr_UCSX_LO_non");
        _dbm->loadDb("MuNIsoDo"  , "160116_FR_withIdEmu.root", "FRMuPtCorr_UCSX_LO_non");

        _dbm->loadDb("ElNIsoMCDo", "160116_FR_withIdEmu.root", "FRElPtCorr_qcd_non");
        _dbm->loadDb("MuNIsoMCDo", "160116_FR_withIdEmu.root", "FRMuPtCorr_qcd_non");
    }

    else if(_FR=="FR2016"){
        _dbm->loadDb("ElNIso"    , "db2016/FakeRatio2016Bmu_RA7.root", "MR_RatElMapPtCorr_non/datacorrUCSX");
        _dbm->loadDb("MuNIso"    , "db2016/FakeRatio2016Bmu_RA7.root", "MR_RatMuMapPtCorr_non/datacorrUCSX");
        _dbm->loadDb("ElNIsoUp"  , "db2016/FakeRatio2016Bmu_RA7.root", "MR_RatElMapPtCorrHI_non/datacorrUCSX");
        _dbm->loadDb("MuNIsoUp"  , "db2016/FakeRatio2016Bmu_RA7.root", "MR_RatMuMapPtCorrHI_non/datacorrUCSX");
        _dbm->loadDb("ElNIsoDo"  , "db2016/FakeRatio2016Bmu_RA7.root", "MR_RatElMapPtCorrLO_non/datacorrUCSX");
        _dbm->loadDb("MuNIsoDo"  , "db2016/FakeRatio2016Bmu_RA7.root", "MR_RatMuMapPtCorrLO_non/datacorrUCSX");
    }


    //load lepton scale factors
    //fullSim muons
    //_dbm->loadDb("FullSimMuID", "lepSF_RA7/fullSim/muons/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root", "pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass" );
    //_dbm->loadDb("FullSimMuIP2D", "lepSF_RA7/fullSim/muons/TnP_MuonID_NUM_TightIP2D_DENOM_LooseID_VAR_map_pt_eta.root", "pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass" );
    //_dbm->loadDb("FullSimMuIP3D", "lepSF_RA7/fullSim/muons/TnP_MuonID_NUM_TightIP3D_DENOM_LooseID_VAR_map_pt_eta.root", "pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass" );
    //_dbm->loadDb("FullSimMuISO", "lepSF_RA7/fullSim/muons/TnP_MuonID_NUM_MultiIsoMedium_DENOM_MediumID_VAR_map_pt_eta.root", "pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_Medium_pass_&_tag_IsoMu20_pass" );
    //fullSim electrons
    //_dbm->loadDb("FullSimElIDandIP", "lepSF_RA7/fullSim/electrons/kinematicBinSFele.root", "MVATight_and_IDEmu_and_TightIP2D_and_TightIP3D" );
    //_dbm->loadDb("FullSimElISO", "lepSF_RA7/fullSim/electrons/kinematicBinSFele.root", "MultiIsoTight_vs_AbsEta" );
    //fastSim muons
    //_dbm->loadDb("FastSimMuID", "lepSF_RA7/fastSim/muons/sf_mu_mediumID.root", "histo3D" );
    //_dbm->loadDb("FastSimMuIP2D", "lepSF_RA7/fastSim/muons/sf_mu_tightIP2D.root", "histo3D" );
    //_dbm->loadDb("FastSimMuIP3D", "lepSF_RA7/fastSim/muons/sf_mu_tightIP3D.root", "histo3D" );
    //_dbm->loadDb("FastSimMuISO", "lepSF_RA7/fastSim/muons/sf_mu_multi.root", "histo3D" );
    //fastSim electrons
    //_dbm->loadDb("FastSimElIDandIP", "lepSF_RA7/fastSim/electrons/sf_el_tight2d3dIDEmu.root", "histo3D" );
    //_dbm->loadDb("FastSimElISO", "lepSF_RA7/fastSim/electrons/sf_el_multi.root", "histo3D" );
   
    
    //load pile-up weights 80X
    _dbm->loadDb("puWeights","db2016/puWeights_4fb.root","puw");
    _dbm->loadDb("puWeightsUp","db2016/puWeights_4fb_Up.root","puw");
    _dbm->loadDb("puWeightsDown","db2016/puWeights_4fb_Down.root","puw");
 
    //load pile-up weights 74X
    _dbm->loadDb("puWeights74X","pileupWeights.root","pileup");
    _dbm->loadDb("puWeights74XUp","pileupWeights.root","pileupUpXS");
    _dbm->loadDb("puWeights74XDown","pileupWeights.root","pileupDownXS");




    //systematic uncertainties
    if(_runSystematics){
        addManualSystSource("btag",SystUtils::kNone);
        addManualSystSource("jes",SystUtils::kNone);
        addManualSystSource("fakes_EWK",SystUtils::kNone);
        addManualSystSource("pu",SystUtils::kNone);
        //fastSim only
        addManualSystSource("isr",SystUtils::kNone);
   //     addManualSystSource("fs_lep",SystUtils::kNone);
   //     addManualSystSource("fs_hlt",SystUtils::kNone);
        addManualSystSource("fs_btag",SystUtils::kNone);
        //addManualSystSource("XSFS",SystUtils::kNone);
   //     addManualSystSource("scale",SystUtils::kNone);
    
        //uncertainties previously taken care of in display card 
        addManualSystSource("lumi",SystUtils::kNone);
        addManualSystSource("HLTEff",SystUtils::kNone);
        addManualSystSource("LepEff",SystUtils::kNone);
        addManualSystSource("rare",SystUtils::kNone);
        addManualSystSource("XG",SystUtils::kNone);
        addManualSystSource("ra7_WZ",SystUtils::kNone);
        addManualSystSource("ttzh_pdf",SystUtils::kNone);
        addManualSystSource("ttw_pdf",SystUtils::kNone);
        addManualSystSource("TTW",SystUtils::kNone);
        addManualSystSource("TTZH",SystUtils::kNone);
        addManualSystSource("fakes",SystUtils::kNone);
        addManualSystSource("ttzh_extr_htl",SystUtils::kNone);
        addManualSystSource("ttzh_extr_hth",SystUtils::kNone);
        addManualSystSource("ttz_lowM_extr_htl",SystUtils::kNone);
        addManualSystSource("ttz_lowM_extr_hth",SystUtils::kNone);
        addManualSystSource("ttw_extr_htl",SystUtils::kNone);
        addManualSystSource("ttw_extr_hth",SystUtils::kNone);
        addManualSystSource("wz_extr",SystUtils::kNone);
        addManualSystSource("ttzLO",SystUtils::kNone);
        addManualSystSource("ttwLO",SystUtils::kNone);
    }

}


//____________________________________________________________________________
void SUSY3L::modifyWeight() {
    /*
        modifies the event weight for every entry in the tree
        parameters: none
        return: none
    */ 
    
    if(_vc->get("isData") != 1){
        //generator weights
        int LHESYS = _LHESYS;
        float Xfactor = 1;
        if(_fastSim && (isInUncProc() &&  getUncName()=="scale") && SystUtils::kUp==getUncDir() ){
            LHESYS = 1009;
            Xfactor = getFastSimXFactor(1);
            }
	    if(_fastSim && (isInUncProc() &&  getUncName()=="scale") && SystUtils::kDown==getUncDir() ){
            LHESYS = 1005;
            Xfactor = getFastSimXFactor(-1);
        }
        if(!_closure){
        if(LHESYS == 0) {
            _weight *= _vc->get("genWeight");
            }
        else {
           _weight *= _susyMod->getLHEweight(LHESYS);
            _weight *= Xfactor;
        }}

	    //pile-up weights
        if(!_closure && _version == 8){
            string db="puWeights";
	        if((isInUncProc() &&  getUncName()=="pu") && SystUtils::kUp==getUncDir() ){db="puWeightsUp";}
	        if((isInUncProc() &&  getUncName()=="pu") && SystUtils::kDown==getUncDir() ){db="puWeightsDown";}
	        _weight *= _dbm->getDBValue(db, _vc->get("nTrueInt") ); 
            //_weight *= _susyMod->getPuWeight( _vc->get("nVert") );
        }
        if(!_closure && _version == 4){
            string db="puWeights74X";
	        if((isInUncProc() &&  getUncName()=="pu") && SystUtils::kUp==getUncDir() ){db="puWeights74XUp";}
	        if((isInUncProc() &&  getUncName()=="pu") && SystUtils::kDown==getUncDir() ){db="puWeights74XDown";}
	        _weight *= _dbm->getDBValue(db, _vc->get("nTrueInt") );
        }


    }

}


//____________________________________________________________________________
void SUSY3L::run(){
   
    //set cut values
    setBaselineRegion();

    //skim tree
    if(_skim) {
      if(_vc->get("nLepGood") >2) fillSkimTree();
      return; 
    }
    
    //increment event counter, used as denominator for yield calculation
    counter("denominator");

    if(_fastSim && !checkMassBenchmark()) return;
    
    //check what kind of MC sample is used
    checkSample();

    //event filter
    if(!passNoiseFilters()) return;
    counter("JME filters");

    //check HLT trigger decition, only let triggered events pass (no HLT info in fast sim)
    if(!_fastSim){
        if(!passHLTbit()) return;
    }
    counter("HLT");
    

    //minimal selection and collection of kinematic variables
    collectKinematicObjects();
  
    if(_runSystematics) systUnc();
   

    //event reweighting //////////////////////////////////////////////////////////
    //btag-scale factors
    if(!_vc->get("isData") && !_closure ) {
        if(!isInUncProc())  {
	        _btagW = _susyMod->bTagSF( _jets, _jetsIdx, _bJets, _bJetsIdx, 0, _fastSim, 0);
	        _weight *= _btagW;
        }
        else if(isInUncProc() && getUncName()=="btag" && getUncDir()==SystUtils::kUp )
	        _weight *= _susyMod->bTagSF( _jets, _jetsIdx, _bJets,_bJetsIdx, 1, _fastSim); 
        else if(isInUncProc() && getUncName()=="btag" && getUncDir()==SystUtils::kDown )
	        _weight *= _susyMod->bTagSF( _jets, _jetsIdx, _bJets, _bJetsIdx, -1, _fastSim); 
        else if(isInUncProc() && getUncName()=="fs_btag" && getUncDir()==SystUtils::kUp )
	        _weight *= _susyMod->bTagSF( _jets, _jetsIdx, _bJets, _bJetsIdx, 0, _fastSim, 1); 
        else if(isInUncProc() && getUncName()=="fs_btag" && getUncDir()==SystUtils::kDown )
	        _weight *= _susyMod->bTagSF( _jets, _jetsIdx, _bJets, _bJetsIdx, 0, _fastSim, -1); 
        else //other syst. variations
	        _weight *= _btagW;
    }
    counter("b-tag SF");

    //ISR variation for fastsim
    if(_fastSim){
        if(isInUncProc() && getUncName()=="isr" && getUncDir()==SystUtils::kUp ){
	        _susyMod->applyISRWeight(0, 1 , _weight); // up variation
        }
        else if(isInUncProc() && getUncName()=="isr" && getUncDir()==SystUtils::kDown ){
	        _susyMod->applyISRWeight(0, -1, _weight); // down variation
        }
    }
/*    
    //lepton scale factors
    if(!_vc->get("isData")){
        //fullSim scale factors, flat uncertainty added in display card
        if(!_fastSim) {
	        _weight*=_susyMod->applyLepSfRA7(_tightLepsPtCutMllCut);
        }
        //fastSim scale factors and flavor and pt dependent shape uncertainty
        else{
            _weight*=_susyMod->applyFastSimLepSfRA7(_tightLepsPtCutMllCut, _vc->get("nTrueInt"));
            // //uncertainties
	        if((isInUncProc() &&  getUncName()=="fs_lep") && SystUtils::kUp==getUncDir() )
	            _weight *= _susyMod->getVarWeightFastSimLepSFRA7(_tightLepsPtCutMllCut, 1);
	        if((isInUncProc() &&  getUncName()=="fs_lep") && SystUtils::kDown==getUncDir() )
	          _weight *= _susyMod->getVarWeightFastSimLepSFRA7(_tightLepsPtCutMllCut, -1);
        }
    } 
    counter("lepton SF");

    //HLT scale factors
    if(!_vc->get("isData") && _fastSim){
        //fastSim scale factors and flavor and pt dependent shape uncertainty
        _weight*=_susyMod->getWeightFastSimHltSFRA7(_tightLepsPtCutMllCut, _HT);
        // //uncertainties
	    if((isInUncProc() &&  getUncName()=="fs_hlt") && SystUtils::kUp==getUncDir() )
	        _weight *= _susyMod->getVarWeightFastSimHltSFRA7(_tightLepsPtCutMllCut, _HT, 1);
	    if((isInUncProc() &&  getUncName()=="fs_hlt") && SystUtils::kDown==getUncDir() )
	        _weight *= _susyMod->getVarWeightFastSimHltSFRA7(_tightLepsPtCutMllCut, _HT, -1);
    } 
    counter("HLT SF");
*/

    //end event reweighting ////////////////////////////////////////////////////
  
    setWorkflow(kGlobal);	

    //selections for validation plots
    if(_doValidationPlots) {
        if (ttbarSelection())   fillValidationHistos("ttbar");
        if (ZlSelection())      fillValidationHistos("Zl");
        if (WlSelection())      fillValidationHistos("Wl");
        if (ZMuMuSelection())   fillValidationHistos("ZMuMu");
        if (ZElElSelection())   fillValidationHistos("ZElEl");
    }
   
    //select events for WZ control region
    bool wzSel = wzCRSelection();
    bool wzFakeSel = wzCRFakeSelection();
    if(wzSel||wzFakeSel){return;}	
    setWorkflow(kGlobal);	
  
    //select events for fake control region in data
    fakeCRSelection();
    fakeCRFakeSelection();
    setWorkflow(kGlobal);	
  
    //limit run number to unblineded json
    //if(_vc->get("isData") == 1){
    //    if(_vc->get("run")>274240){return;}
    //}

    //baseline selection
    bool baseSel = multiLepSelection();
    if(!baseSel){return;}

    //signal event
    if(!_isFake){
        setWorkflow(kGlobal);
        advancedSelection( kGlobal );
    }
    //fake background event 
    else{
		//loop over all combinations of tight and fake leptons
        float sumTF = 0;
        for(unsigned int ic=0;ic<_combList.size();ic++) {
            int type = _combType[ic];
            if(type==kIsSingleFake){ sumTF += getTF_SingleFake(ic); }
            if(type==kIsDoubleFake){ sumTF += getTF_DoubleFake(ic); }
            if(type==kIsTripleFake){ sumTF += getTF_TripleFake(ic); }
            if(_doPlotsVerbose) fill("fake_type" , type+1       , _weight);
        }
        if(_doPlotsVerbose) fill("applWeight", sumTF, _weight);
        _weight *= sumTF;
	    setWorkflow(kGlobal_Fake);
        advancedSelection( kGlobal_Fake );
    
    }
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void SUSY3L::defineOutput(){
    /*
        defines and reserves all output that is produced in this class
        parameters: none
        return: none
    */
    
    //SR yields
    _hm->addVariable("SRS"  ,  17,  1,  18, "signal region"    );
    
    if(!_doPlots) return; 

    //event based observables
    _hm->addVariable("HT"        , 1000,   0.0, 1000.0, "H_{T} (GeV)"                                           );
    _hm->addVariable("MET"       , 1000,   0.0, 1000.0, "E^{miss}_{T} (GeV)"                                    );
    _hm->addVariable("NBJets"    ,   20,   0.0,   20.0, "N_{b-jet}"                                             );
    _hm->addVariable("NJets"     ,   20,   0.0,   20.0, "N_{jet}"                                               ); 
    _hm->addVariable("MT"               ,  400,    0.0,  400.0,    "M_{T} (GeV)"                               );
    _hm->addVariable("pt_1st_lepton"    ,  200,    0.0,  200.0,    "p_{T} leading lepton (GeV)"                );
    _hm->addVariable("pt_2nd_lepton"    ,  200,    0.0,  200.0,    "p_{T} sub-leading lepton (GeV)"            );
    _hm->addVariable("pt_3rd_lepton"    ,  200,    0.0,  200.0,    "p_{T} 3rd lepton (GeV)"                    );
    _hm->addVariable("flavor"           ,  5,      0.0,  5.0,      "flavor (N_{eee}/N_{#muee}/N_{#mu#mue}/N_{#mu#mu#mu}/N_{>3 leptons})" );
    _hm->addVariable("el_multiplicity"  ,  10,      0.0,   10.0,    "N_{el}"                                    );
    _hm->addVariable("mu_multiplicity"  ,  10,      0.0,   10.0,    "N_{#mu}"                                   );
    _hm->addVariable("lep_multiplicity" ,  10,      0.0,   10.0,    "N_{lep}"                                   );

    vector<string> wfs({"OnZBaseline","OffZBaseline",
	  "OnZBaseline_Fake", "OffZBaseline_Fake",
	  "Fake","WZCR","FakeCR","WZCR_Fake"});

    _hm->setRelevantWFs( "SRS" ,wfs);
    _hm->setRelevantWFs( "HT" ,wfs);
    _hm->setRelevantWFs( "MET" ,wfs);
    _hm->setRelevantWFs( "NBJets" ,wfs);
    _hm->setRelevantWFs( "NJets" ,wfs);
    _hm->setRelevantWFs( "MT" ,wfs);
    _hm->setRelevantWFs( "pt_1st_lepton" ,wfs);
    _hm->setRelevantWFs( "pt_2nd_lepton" ,wfs);
    _hm->setRelevantWFs( "pt_3rd_lepton" ,wfs);
    _hm->setRelevantWFs( "flavor" ,wfs);
    _hm->setRelevantWFs( "el_multiplicity" ,wfs);
    _hm->setRelevantWFs( "mu_multiplicity" ,wfs);
    _hm->setRelevantWFs( "lep_multiplicity" ,wfs);
    

    if(!_doPlotsVerbose) return; 
    
    //other observables
    _hm->addVariable("lowestOssfMll"    ,  400,     0.0,  400.0,    "smallest ossf pair mll (GeV)"              );
    _hm->addVariable("lep1_SIP3D"       , 100,       0.,    5.0,    "leading lepton SIP_{3D}"                   );
    _hm->addVariable("lep1_dxy"         , 400,    -200.,  200.0,    "leading lepton d_{xy} (#mum)"              );
    _hm->addVariable("lep1_dz"          , 800,    -400.,  400.0,    "leading lepton d_{z} (#mum)"               );
    _hm->addVariable("lep2_SIP3D"       , 100,       0.,    5.0,    "sub-leading lepton SIP_{3D}"               );
    _hm->addVariable("lep2_dxy"         , 400,    -200.,  200.0,    "sub-leading lepton d_{xy} (#mum)"          );
    _hm->addVariable("lep2_dz"          , 800,    -400.,  400.0,    "sub-leading lepton d_{z} (#mum)"           );
    _hm->addVariable("lep3_SIP3D"       , 100,       0.,    5.0,    "3rd lepton SIP_{3D}"                       );
    _hm->addVariable("lep3_dxy"         , 400,    -200.,  200.0,    "3rd lepton d_{xy} (#mum)"                  );
    _hm->addVariable("lep3_dz"          , 800,    -400.,  400.0,    "3rd lepton d_{z} (#mum)"                   );
   
    //on-Z only observables 
    _hm->addVariable("Zmass"            ,  250,     0.0,  250.0,    "Z candidate mass (GeV)"                    );
    _hm->addVariable("Zpt"              ,  250,     0.0,  250.0,    "Z candidate p_{T} (GeV)"                   );

    //auxiliary for fake estimartion
    _hm->addVariable("fake_type"        ,  5,     0.0,  5.0,    "N_{fakeable-not-tight leptons}"                    );
    _hm->addVariable("nFO"              ,  7,     0.0,  7.0,    "number of tight plus fakable-not-tight leptons"    );
    _hm->addVariable("nFakeComb"        ,  5,     0.0,  5.0,    "number of tight-fake-combinations per event"       );
    _hm->addVariable("ptRank"           ,  5,     0.0,  5.0,    "p_{T} rank of fake lepton in TTF events"           );
    _hm->addVariable("applWeight"       ,  100,  -5.0,  5.0,       "weigth of events in application region"    );
    
    _hm->addVariable("mcMatchId",  115,  -10.0,  105.0,    "LepGood_mcMatchId"                             );
    _hm->addVariable("chargeMult_3lep"  ,  5,     0.0,  5.0,    "same sign multiplicity"                            );
    _hm->addVariable("chargeMult_4lep"  ,  5,     0.0,  5.0,    "same sign multiplicity"                            );
  
    if(!_doValidationPlots) return; 
    
    //additional histograms  
    vector<string> reg;
    reg.push_back("ttbar");
    reg.push_back("ZMuMu");
    reg.push_back("ZElEl");
    reg.push_back("Zl");
    reg.push_back("Wl");
  
    for (size_t r=0; r<reg.size(); r++) {
        // lepton variables
        _hm->addVariable(reg[r]+"_lep1_jetPtRatio", 100, 0., 1.2, "leading lepton jet p_{T} ratio (GeV)", false);
        _hm->addVariable(reg[r]+"_lep1_jetPtRel"  , 100, 0., 40., "leading lepton jet p_{T} rel   (GeV)", false);
        _hm->addVariable(reg[r]+"_lep1_miniRelIso", 100, 0., 0.4, "leading lepton isolation", false);
        _hm->addVariable(reg[r]+"_lep1_Pt"        , 100, 0., 100, "leading lepton p_{T} (GeV)", false);
        _hm->addVariable(reg[r]+"_lep1_Eta"       , 100, 0., 2.5, "leading lepton #eta", false);
        _hm->addVariable(reg[r]+"_lep1_SIP3D"     , 100, 0., 5.0, "leading lepton SIP_{3D}", false);
        _hm->addVariable(reg[r]+"_lep1_dxy"       , 200, -0.2, 0.2, "leading lepton d_{xy} (cm)", false);
        _hm->addVariable(reg[r]+"_lep1_dz"        , 200, -0.2, 0.2, "leading lepton d_{z} (cm)", false);
        _hm->addVariable(reg[r]+"_lep2_jetPtRatio", 100, 0., 1.2, "subleading lepton jet p_{T} Ratio (GeV)", false);
        _hm->addVariable(reg[r]+"_lep2_jetPtRel"  , 100, 0., 40., "subleading lepton jet p_{T} Rel   (GeV)", false);
        _hm->addVariable(reg[r]+"_lep2_miniRelIso", 100, 0., 0.4, "subleading lepton isolation", false);
        _hm->addVariable(reg[r]+"_lep2_Pt"        , 100, 0., 100, "subleading lepton p_{T} (GeV)", false);
        _hm->addVariable(reg[r]+"_lep2_Eta"       , 100, 0., 2.5, "subleading lepton #eta", false);
        _hm->addVariable(reg[r]+"_lep2_SIP3D"     , 100, 0., 5.0, "subleading lepton SIP_{3D}", false);
        _hm->addVariable(reg[r]+"_lep2_dxy"       , 200, -0.2, 0.2, "subleading lepton d_{xy} (cm)", false);
        _hm->addVariable(reg[r]+"_lep2_dz"        , 200, -0.2, 0.2, "subleading lepton d_{z} (cm)", false);
  
        // event variables 
        _hm->addVariable(reg[r]+"_MET"            , 500, 0. , 500, "E_{T}^{miss} (GeV)", false);
        _hm->addVariable(reg[r]+"_mZ1"            , 300, 0. , 300, "best m_{l^{+}l^{-}} (GeV)", false);
        _hm->addVariable(reg[r]+"_htJet40j"       , 800, 0. , 800, "H_{T} (GeV)", false);
        _hm->addVariable(reg[r]+"_NBJetsLoose25"  ,   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 25 GeV, loose)", false);
        _hm->addVariable(reg[r]+"_NBJetsMedium25" ,   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 25 GeV, medium)", false);
        _hm->addVariable(reg[r]+"_NBJetsTight40"  ,   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 40 GeV, tight)", false);
        _hm->addVariable(reg[r]+"_NJets40"        ,   8,-0.5, 7.5, "N_{jets} (p_{T} > 40 GeV)", false);
    }
 
}


//____________________________________________________________________________
void SUSY3L::loadInput(){
    // define function in MPAF for loading histograms, text files, histograms from database 
}


//____________________________________________________________________________
void SUSY3L::writeOutput(){
    /*
        writes all output of this class to the disk
        paramters: none
        return: none
    */

    //_hm -> saveHistos("SUSY3L", _cfgName);
    //_au -> saveNumbers("SUSY3L", _cfgName);

}


//____________________________________________________________________________
void SUSY3L::modifySkimming(){
    // if adding variables to the skimmed tree is needed...
}


/******************************************************************************
*******************************************************************************
*** OBJECT SELECTIONS                                                        **
*******************************************************************************
******************************************************************************/

void SUSY3L::collectKinematicObjects(){

    /*
        collects all kinematic objects needed in the code, i.e. applies all object selections
        parameters: none
        return: none
    */
  
    // clear object category vectors from previous event
    _taus.clear();
    _tauIdx.clear();
    
    _looseLeps.clear();
    _looseLepsIdx.clear();
    
    _looseLepsPtCut.clear();
    _looseLepsPtCutIdx.clear();

    _looseLepsPtCorrCut.clear();
    _looseLepsPtCorrCutIdx.clear();
     
    _fakableLeps.clear();   
    _fakableLepsIdx.clear();   

    _fakableLepsPtCut.clear();   
    _fakableLepsPtCutIdx.clear();   
     
    _fakableNotTightLepsPtCut.clear();   
    _fakableNotTightLepsPtCutIdx.clear();   
    
    _fakableNotTightLepsPtCorrCut.clear();   
    _fakableNotTightLepsPtCorrCutIdx.clear();   
 
    _tightLepsPtCut.clear();
    _tightLepsPtCutIdx.clear();
 
    _tightLepsPtCutMllCut.clear();
    _tightLepsPtCutMllCutIdx.clear();

    _leps.clear();
    _lepsIdx.clear();

    _jets.clear();
    _jetsIdx.clear();
    _bJets.clear();
    _bJetsIdx.clear();
    _lepJets.clear();
    _lepJetsIdx.clear();
  
    _combList.clear();
    _combType.clear();
    _combIdxs.clear();

    //default values for global variables which are not computed for off-Z events
    _zMass = -999;
    _zPt = -999;
    _MT = -999;

    //select loose leptons (note: not equivalent to LepGood)
    for(size_t il=0;il<_vc->get("nLepGood"); il++) {
        bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;
        
        if(_selectMuons == false && isMu == true) continue;
        if(_selectElectrons == false && isMu == false) continue;

        Candidate* cand=Candidate::create(_vc->get("LepGood_pt", il),
                      _vc->get("LepGood_eta", il),
                      _vc->get("LepGood_phi", il),
                      _vc->get("LepGood_pdgId", il),
                      _vc->get("LepGood_charge", il),
                      isMu?0.105:0.0005);
   
        int wp=isMu?SusyModule::kLoose:SusyModule::kMedium;
        Candidate* candPtCorr=Candidate::create( _susyMod->conePt(il,wp),
                      _vc->get("LepGood_eta", il),
                      _vc->get("LepGood_phi", il),
                      _vc->get("LepGood_pdgId", il),
                      _vc->get("LepGood_charge", il),
                      isMu?0.105:0.0005); 
    
        if(!looseLepton(cand, il, cand->pdgId() ) ) continue;
        _looseLeps.push_back(cand);
        _looseLepsIdx.push_back(il);

        //(flavor dependent) pt cut
        if((isMu && cand->pt()>10) || (!isMu && cand->pt()>10)) {
            _looseLepsPtCut.push_back(cand);
            _looseLepsPtCutIdx.push_back(il);
        }

        //cone corrected pt for improved closure
        if((isMu && _susyMod->conePt(il,wp)>10 && cand->pt()>10 ) || (!isMu && _susyMod->conePt(il,wp)>10 && cand->pt()>10)) {
            _looseLepsPtCorrCut.push_back(candPtCorr);
            _looseLepsPtCorrCutIdx.push_back(il);
        }
   
    }  
 
    //select fakable leptons with pt cut (used for jet cleaning)
    for(size_t il=0;il<_looseLepsPtCut.size();il++){
        if(!fakableLepton(_looseLepsPtCut[il], _looseLepsPtCutIdx[il], _looseLepsPtCut[il]->pdgId(), true)) continue;
        _fakableLepsPtCut.push_back( _looseLepsPtCut[il] );
        _fakableLepsPtCutIdx.push_back( _looseLepsPtCutIdx[il] );
    } 
 
    //fakable-not-tight leptons
    for(size_t il=0;il<_looseLepsPtCut.size();il++){
        if(tightLepton(_looseLepsPtCut[il], _looseLepsPtCutIdx[il], _looseLepsPtCut[il]->pdgId())) continue;
        if(!fakableLepton(_looseLepsPtCut[il], _looseLepsPtCutIdx[il], _looseLepsPtCut[il]->pdgId(), true)) continue;
        _fakableNotTightLepsPtCut.push_back( _looseLepsPtCut[il] );
        _fakableNotTightLepsPtCutIdx.push_back( _looseLepsPtCutIdx[il] );
    } 

    //fakable-not-tight leptons, pt corrected
    for(size_t il=0;il<_looseLepsPtCorrCut.size();il++) {
        if(tightLepton(_looseLepsPtCorrCut[il], _looseLepsPtCorrCutIdx[il], _looseLepsPtCorrCut[il]->pdgId())) continue;
        if(!fakableLepton(_looseLepsPtCorrCut[il], _looseLepsPtCorrCutIdx[il], _looseLepsPtCorrCut[il]->pdgId(),false)) continue; 
        _fakableNotTightLepsPtCorrCut.push_back(_looseLepsPtCorrCut[il]);
	    _fakableNotTightLepsPtCorrCutIdx.push_back(_looseLepsPtCorrCutIdx[il]);
    }

    //tight lepton
    for(size_t il=0;il<_looseLepsPtCut.size();il++) {
        if(!tightLepton(_looseLepsPtCut[il], _looseLepsPtCutIdx[il], _looseLepsPtCut[il]->pdgId()))  continue;
        _tightLepsPtCut.push_back(_looseLepsPtCut[il]);
        _tightLepsPtCutIdx.push_back(_looseLepsPtCutIdx[il]);
    }

    int els = 0;
    int mus = 0;

    //tight leptons with low mll veto
    for(size_t il=0;il<_tightLepsPtCut.size();il++) {
        if(!_susyMod->passMllMultiVeto( _tightLepsPtCut[il], &_tightLepsPtCut, 0, 12, true) ) continue;
        //count muons and electrons
        if(std::abs(_tightLepsPtCut[il]->pdgId())==13){mus+=1;}
        if(std::abs(_tightLepsPtCut[il]->pdgId())==11){els+=1;}
        _tightLepsPtCutMllCut.push_back(_tightLepsPtCut[il]);
        _tightLepsPtCutMllCutIdx.push_back(_tightLepsPtCutIdx[il]);
    }
    _nMus = mus;
    _nEls = els;

    //select taus
    if(_selectTaus == true){ 
    // loop over all taus and apply selection
    for(int i = 0; i < _vc->get("nTauGood"); ++i){
        // check which of the taus have tau identifier 15 (actually not needed)
        if(std::abs(_vc->get("TauGood_pdgId",i)) == 15){
            //select taus
            if(tauSelection(i)){
                _taus.push_back( Candidate::create(_vc->get("TauGood_pt", i),
                                                   _vc->get("TauGood_eta", i),
                                                   _vc->get("TauGood_phi", i),
                                                   _vc->get("TauGood_pdgId", i),
                                                   _vc->get("TauGood_charge", i),
                                                   1.777) );     //tau mass
                _tauIdx.push_back(i);
            }
        }
    }
    }
    
    //number of taus in the event
    _nTaus = _taus.size();

    //clean jets
    _susyMod->cleanJets( &_fakableLepsPtCut, _jets, _jetsIdx, _bJets, _bJetsIdx,
		       _lepJets, _lepJetsIdx, _jetThreshold, _bjetThreshold, getUncName()=="jes", getUncDir() );
    _nJets = _jets.size();
    _nBJets = _bJets.size();
    
    //get hadronic activity
    _HT=_susyMod->HT( &(_jets) );
 
    //create met candidate for every event
    string ext="met";
    if((isInUncProc() &&  getUncName()=="jes") )
        ext += ((SystUtils::kUp==getUncDir())?"_jecUp":"_jecDown");
    _met = Candidate::create(_vc->get(ext+"_pt"), _vc->get(ext+"_phi") );
    _metPt = _met->pt();

}


//____________________________________________________________________________
bool SUSY3L::looseLepton(const Candidate* c, int idx, int pdgId) {
    /*
        selection of loose leptons
        parameters: position in LepGood, pdgId
        return: true (if leptons is selected as loose lepton), false (else)
    */
    
    if(abs(pdgId)==13) {//mu case
        if(c->pt() < 5) return false;
        if(!_susyMod->muIdSel(c, idx, SusyModule::kLoose, false, false, _useLepMVA) ) return false;
        if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false;
    }
    else {
        if(c->pt() < 7) return false;
        if(!_susyMod->elIdSel(c, idx, SusyModule::kLoose, SusyModule::kLoose, false, false, _useLepMVA) ) return false;
        if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false; 
        if(!_susyMod->elHLTEmulSel(idx, false ) ) return false; 
    }

    return true;
}



//____________________________________________________________________________
bool SUSY3L::fakableLepton(const Candidate* c, int idx, int pdgId, bool bypass){
    /*
        selection of fakable leptons (applying a selection that is tighter than the
        loose one but not as tight as the tight selection 
        parameters: idx (the position in the LepGood vector), pdgId, and boolean to choose
        electron trigger emulation cuts (HT trigger or not)
        return: true (if the lepton fulfills the fakable lepton selection, false (else)
    */

    if(abs(pdgId)==13) {//mu case
        if(!_susyMod->muIdSel(c, idx, SusyModule::kTight, false, false, _useLepMVA) ) return false;
        if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false;
    }
    else {
        if(!_susyMod->elIdSel(c, idx, SusyModule::kTight, SusyModule::kLoose, false, false, _useLepMVA) ) return false;
        if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false;
        if(!_susyMod->elHLTEmulSel(idx, false ) ) return false;
    }

    return true;
} 


//____________________________________________________________________________
bool SUSY3L::tightLepton(const Candidate* c, int idx, int pdgId){
    /*
        selection of tight leptons  
        parameters: the lepton candidate, idx (the position in the LepGood vector), pdgId
        return: true (if the lepton fulfills the tight lepton selection, false (else)
    */

    //use lepton MVA
    if(_useLepMVA){
        if(std::abs(pdgId)==13) {//mu case
            if(!_susyMod->muIdSel(c, idx, SusyModule::kTight, false, false, _useLepMVA) ) return false;
            if(!_susyMod->lepMVAIdSel(idx, SusyModule::kMediumMu) ) return false;
        }
        else {
            if(!_susyMod->elIdSel(c, idx, SusyModule::kTight, SusyModule::kLoose, false, false, _useLepMVA) ) return false;
            if(!_susyMod->lepMVAIdSel(idx, SusyModule::kMediumEl) ) return false;
        }   
    }
    //cut based
    else{
        if(std::abs(pdgId)==13) {//mu case
            if(!_susyMod->muIdSel(c, idx, SusyModule::kTight, false, false, _useLepMVA) ) return false;
            if(!_susyMod->multiIsoSel(idx, SusyModule::kLoose) ) return false;
        }
        else {
            if(!_susyMod->elIdSel(c, idx, SusyModule::kTight, SusyModule::kTight, false, false, _useLepMVA) ) return false;
            if(!_susyMod->multiIsoSel(idx, SusyModule::kMedium) ) return false;
        }
    }

    //gen matching
    if(_doGenMatch && _vc->get("isData")!=1 ){
        if(_promptSample && _vc->get("LepGood_mcMatchId",idx) ==0) return false;
    }

    return true;
}


//____________________________________________________________________________
bool SUSY3L::tauSelection(int tauIdx){
    /*
        selection of taus
        parameters: tauIdx
        return: true (if the lepton is identified as (hadronic) tau), false (else)
    */
   
    //define cuts for electrons
    float pt_cut = 20.;
    float eta_cut = 2.3;
    float deltaR = 0.3;
    
    //apply the cuts
    if(!( _vc->get("TauGood_pt", tauIdx) > pt_cut)) return false;
    if(!( std::abs(_vc->get("TauGood_eta", tauIdx)) < eta_cut)) return false;
    
    //remove taus which are within a cone of deltaR around selected electrons or muons
    //loop over all electron candidates
    //bool lepMatch = false;
    /*
    for(int ie=0; ie<_nEls; ++ie){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _els[ie]->eta(), _vc->get("TauGood_eta", tauIdx), _els[ie]->phi(), _vc->get("TauGood_phi", tauIdx));
        if(dr < deltaR){
            lepMatch = true; 
            break;
        }
    }
    //loop over all muon candidates
    for(int im=0; im<_nMus; ++im){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _mus[im]->eta(), _vc->get("TauGood_eta", tauIdx), _mus[im]->phi(), _vc->get("TauGood_phi", tauIdx));
        if(dr < deltaR) {
            lepMatch = true; 
            break;
        }
    }
    */
    //loop over all loose leptons
    for(int im=0; im<_vc->get("nLepGood"); ++im){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _vc->get("LepGood_eta",im), _vc->get("TauGood_eta", tauIdx), _vc->get("LepGood_phi",im), _vc->get("TauGood_phi", tauIdx));
        if(dr < deltaR) {
	    //lepMatch = true; 
            break;
        }
    }
     
    //enable to clean on tight objects
    //if(lepMatch) return false;
    return true;
}


/*******************************************************************************
* ******************************************************************************
* ** KINEMATIC REGION DEFINITIONS                                             **
* ******************************************************************************
* *****************************************************************************/

//____________________________________________________________________________
void SUSY3L::setBaselineRegion(){
    /*
        sets the cuts of the baseline region (_BR)
        parameters: none
        return: none
    */

    if(_BR == "BR0"){
        //_pt_cut_hardest_legs          = 20          ;     //harsher pT requirement for at least _nHardestLeptons (below)
        //_nHardestLeptons              = 1           ;     //number of leptons which need to fulfill harder pt cut
        //_pt_cut_hard_legs             = 15           ;     //harsher pT requirement for at least _nHardestLeptons (below)
        //_nHardLeptons                 = 1           ;     //number of leptons which need to fulfill harder pt cut
        _M_T_3rdLep_MET_cut           =  -1         ;     //minimum transverse mass of 3rd lepton and met in On-Z events
        setCut("NJets"              ,    2, ">=" )  ;     //number of jets in event
        setCut("NBJets"             ,    0, ">=" )  ;     //number of b-tagged jets in event
        _ZMassWindow                  = 15.         ;     //width around Z mass to define on- or off-Z events
        setCut("HT"                 ,   60, ">=")  ;     //sum of jet pT's
        setCut("MET"                ,   50, ">=")  ;     //missing transverse energy
        //setCut("MT2"                ,   55, "<" )   ;     //MT2 cut value
        _jetThreshold                 = 30.         ;     //jet threshold
        _bjetThreshold                = 25.         ;     //bjet threshold
    }

}

//____________________________________________________________________________
void SUSY3L::setSignalRegion() {
    
    //variables for SR categorization
    _val["NJ"] = &(_nJets);
    _val["NB"] = &(_nBJets);
    _val["HT"] = &(_HT);
    _val["MET"] = &(_metPt);

/*    //0 b-jets
    if( _SR== "OnZSR001" || _SR== "OffZSR001" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:50:150|HT:[[:60:400");
    }
    else if( _SR== "OnZSR002" || _SR== "OffZSR002" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:150:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR003" || _SR== "OffZSR003" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:50:150|HT:[[:400:600");
    }
    else if( _SR== "OnZSR004" || _SR== "OffZSR004" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:150:300|HT:[[:400:600");
    }

    //1 b-jet
    else if( _SR== "OnZSR005" || _SR== "OffZSR005" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:50:150|HT:[[:60:400");
    }
    else if( _SR== "OnZSR006" || _SR== "OffZSR006" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:150:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR007" || _SR== "OffZSR007" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:50:150|HT:[[:400:600");
    }
    else if( _SR== "OnZSR008" || _SR== "OffZSR008" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:150:300|HT:[[:400:600");
    }

    //2 b-jets
    else if( _SR== "OnZSR009" || _SR== "OffZSR009" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:50:150|HT:[[:60:400");
    }
    else if( _SR== "OnZSR010" || _SR== "OffZSR010" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:150:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR011" || _SR== "OffZSR01" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:50:150|HT:[[:400:600");
    }
    else if( _SR== "OnZSR012" || _SR== "OffZSR012" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:150:300|HT:[[:400:600");
    }

    //3 b-jets
    else if( _SR== "OnZSR013" || _SR== "OffZSR013" ) {
        setSelLine("NJ:>=:2|NB:>=:3|MET:[[:50:300|HT:[[:60:600");
    }

    //ultra high MET and HT region
    else if( _SR== "OnZSR014" || _SR== "OffZSR014" ) {
        setSelLine("NJ:>=:2|NB:>=:0|MET:[[:50:300|HT:>=:600");
    }
    else if( _SR== "OnZSR015" || _SR== "OffZSR015" ) {
        setSelLine("NJ:>=:2|NB:>=:0|MET:>=:300|HT:>=:60");
    }
  */
  
    //0 b-jets
    if( _SR== "OnZSR001" || _SR== "OffZSR001" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:50:150|HT:[[:60:400");
    }
    else if( _SR== "OnZSR002" || _SR== "OffZSR002" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:150:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR003" || _SR== "OffZSR003" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:50:150|HT:[[:400:600");
    }
    else if( _SR== "OnZSR004" || _SR== "OffZSR004" ) {
        setSelLine("NJ:>=:2|NB:=:0|MET:[[:150:300|HT:[[:400:600");
    }

    //1 b-jet
    else if( _SR== "OnZSR005" || _SR== "OffZSR005" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:50:150|HT:[[:60:400");
    }
    else if( _SR== "OnZSR006" || _SR== "OffZSR006" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:150:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR007" || _SR== "OffZSR007" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:50:150|HT:[[:400:600");
    }
    else if( _SR== "OnZSR008" || _SR== "OffZSR008" ) {
        setSelLine("NJ:>=:2|NB:=:1|MET:[[:150:300|HT:[[:400:600");
    }

    //2 b-jets
    else if( _SR== "OnZSR009" || _SR== "OffZSR009" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:50:150|HT:[[:60:400");
    }
    else if( _SR== "OnZSR010" || _SR== "OffZSR010" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:150:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR011" || _SR== "OffZSR01" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:50:150|HT:[[:400:600");
    }
    else if( _SR== "OnZSR012" || _SR== "OffZSR012" ) {
        setSelLine("NJ:>=:2|NB:=:2|MET:[[:150:300|HT:[[:400:600");
    }

    //3 b-jets
    else if( _SR== "OnZSR013" || _SR== "OffZSR013" ) {
        setSelLine("NJ:>=:2|NB:>=:3|MET:[[:50:300|HT:[[:60:600");
    }

    //ultra high MET and HT region

    //ON-Z
    else if( _SR== "OnZSR014" || _SR== "OffZSR014") {
        setSelLine("NJ:>=:2|NB:>=:0|MET:[[:50:150|HT:>=:600");
    }
    else if( _SR== "OnZSR015" || _SR== "OffZSR015" ) {
        setSelLine("NJ:>=:2|NB:>=:0|MET:[[:150:300|HT:>=:600");
    }
    else if( _SR== "OnZSR016" || _SR== "OffZSR016") {
        setSelLine("NJ:>=:2|NB:>=:0|MET:>=:300|HT:[[:60:400");
    }
    else if( _SR== "OnZSR017" || _SR== "OffZSR017") {
        setSelLine("NJ:>=:2|NB:>=:0|MET:>=:300|HT:>=:400");
    }

}


//____________________________________________________________________________
void SUSY3L::setSelLine(string str) {
    /*
        function for parsing the signal region definition strings
        parameters: string containing the selection variables and cuts
        return: none
    */

    //parsing full selection into variable selections
    stringstream ss(str);
    string item;
    string tk;
  
    vector<vector<string> > sel;
    while (std::getline(ss, item, '|')) {
        vector<string> vars(4,"");
        stringstream sssel( item );
        int n=0;
        while (std::getline(sssel, tk, ':')) {
            vars[n]= (tk);
            n++;
        }
        if(vars.size()==3){
            vars.push_back("");
        }
        sel.push_back(vars);
    }
    _sels[_SR].push_back( sel );
}


//____________________________________________________________________________
float SUSY3L::getFR(Candidate* cand, int idx) {
    /*
        extracts the fake rate of a lepton candiate from the fake rate map taking into account
        leptons pt and eta
        parameters: lepton candidate, idx of the candidate
        return: the fake rate of the candidate
    */

    string db;
    float ptM=10;
    //check candidate flavor
    if( std::abs(cand->pdgId())==13) db="Mu";
    else { db="El"; ptM=10;}
 
    //always use non-isolated maps 
    db+= "NIso";
    
    //check hadronic activty (different maps for high and low HT)
    //if(_HT<300) db+= "Iso";
    //db+= "Iso";
    //else db += "NIso";

    //distinguish data and mc
    //if(_vc->get("isData")!=1) db +="MC"; //TODO: enable as soon as MC FR maps are available!

    if(isInUncProc() && getUncName()=="fakes_EWK" && getUncDir()==SystUtils::kUp ) db+="Up";
    if(isInUncProc() && getUncName()=="fakes_EWK" && getUncDir()==SystUtils::kDown ) db+="Do";

    //get pt and eta of candidate
    float ptVal=cand->pt();
    float etaVal=std::abs(cand->eta());

    //flavor dependent multiIso working point
    int wp=std::abs(cand->pdgId())==11?SusyModule::kMedium:SusyModule::kLoose;

    if(_FR.find("C")!=string::npos) ptVal=std::max(_susyMod->conePt(idx,wp), (double)ptM);

    ptVal=std::max(ptVal, ptM);
  
    //get fake rate from database
    return _dbm->getDBValue(db, std::min( ptVal,(float)69.9), std::min(etaVal,(float)((std::abs(cand->pdgId())==11)?2.49:2.39) ) );

}


//____________________________________________________________________________
void SUSY3L::setCut(std::string var, float valCut, std::string cType, float upValCut) {
    /*
        sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
        parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
        in case one cuts the variable in a range)
        return: none
    */

    //baseline region
    if(var == "NJets") {
        _valCutNJetsBR   = valCut;
        _cTypeNJetsBR    = cType;
        _upValCutNJetsBR = upValCut;
    }
    else if(var == "NBJets") {
        _valCutNBJetsBR   = valCut;
        _cTypeNBJetsBR    = cType;
        _upValCutNBJetsBR = upValCut;
    }
    else if(var == "HT") {
        _valCutHTBR   = valCut;
        _cTypeHTBR    = cType;
        _upValCutHTBR = upValCut;
    }
    else if(var == "MET") {
        _valCutMETBR   = valCut;
        _cTypeMETBR    = cType;
        _upValCutMETBR = upValCut;
    }
    else if(var == "MT2") {
        _valCutMT2BR   = valCut;
        _cTypeMT2BR    = cType;
        _upValCutMT2BR = upValCut;
    }

}



/*******************************************************************************
* ******************************************************************************
* ** EVENT SELECTIONS                                                         **
* ******************************************************************************
* *****************************************************************************/

//____________________________________________________________________________
bool SUSY3L::multiLepSelection(){
    /*
        implements the basic multiLepton event selection 
        parameters: bool onZ, decides if on or off-Z selection 
        return: true (if event passes selection), false (else)
    */

    _isMultiLep = false;
    _isFake = false;
    bool pass = true;
    bool isFakeOnZ = false;
    vector<CandList> combListTemp;

    //require lepton which is not gen-matched for closure separated by flavors
    //if(_closureByFlavor!=0){
    //    pass = false;
    //    bool oneMu = false;
    //    int nFakes = 0;
    //    for(int i=0;i<_tightLepsPtCutMllCut.size();i++){
    //        if( std::abs(_tightLepsPtCutMllCut[i]->pdgId() == _closureByFlavor)){oneMu=true;}
    //        if( _vc->get("LepGood_mcMatchId" ,_tightLepsPtCutMllCutIdx[i]) == 0 ){nFakes+=1;}
    //    }
    //    if(nFakes==1 && oneMu){pass = true;}
    //}

    //require exactly 1 lepton which is not gen-matched for closure separated by flavors
    if(_closureByFlavor!=0){
        pass = false;
        int nFakes = 0;
        int nPrompt = 0;
        for(size_t i=0;i<_tightLepsPtCutMllCut.size();i++){
            if( std::abs(_tightLepsPtCutMllCut[i]->pdgId() == _closureByFlavor) &&  _vc->get("LepGood_mcMatchId" ,_tightLepsPtCutMllCutIdx[i]) ==0 ){nFakes+=1;}
            else if( _vc->get("LepGood_mcMatchId" ,_tightLepsPtCutMllCutIdx[i]) !=0 ){nPrompt+=1;}
        }
        if(nFakes==1 && nPrompt ==2){pass = true;}
    }
    
    counter("baseline denominator");
    
    bool onZ=false;
    //loop over on and off-Z regions
    for(int iz=0;iz<2;iz++){
        onZ=(bool)(1-iz);
        //if only on or off Z regions should be considered
        if( (_onZ==0 && onZ) || (_onZ==1 && !onZ) ) continue;
        
        if(onZ){setWorkflow(kOnZBaseline);}
        else{setWorkflow(kOffZBaseline);}
        counter("baseline denominator");

        //three or more tight leptons
        if((_exactlyThreeLep && _tightLepsPtCut.size()==3 && pass)||(!_exactlyThreeLep && _tightLepsPtCut.size()>=3 && pass)){
            counter("lepton multiplicity");
            if(!((_exactlyThreeLep && _tightLepsPtCutMllCut.size()==3)||(!_exactlyThreeLep && _tightLepsPtCutMllCut.size()>=3))) continue;
            counter("low mll veto");
            //require hard legs
            //if(!hardLeg(_tightLepsPtCutMllCut, _nHardestLeptons, _pt_cut_hardest_legs, _nHardLeptons, _pt_cut_hard_legs )) continue;
            if(!ptSelection(_tightLepsPtCutMllCut)) continue;
            counter("lepton pt selection");
            
            //Z selection
            bool passMass = false;
            bool passMT = false;
            bool isOnZ = false;

            for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++) {
                if(!_susyMod->passMllMultiVeto( _tightLepsPtCutMllCut[il], &_tightLepsPtCutMllCut, 76, 106, true) ){passMass = true;}
            }
            if(onZ && !passMass) continue;

            if(passMass){
                //compute MT of 3rd lepton with MET
                _zPair = _susyMod->findZCand( &_tightLepsPtCutMllCut, _ZMassWindow, _M_T_3rdLep_MET_cut);
                if(!(_zPair[0] == 0 && _zPair[1] == 0)){
                    passMT = true;
                    _zMass = Candidate::create(_zPair[0], _zPair[1])->mass();
                    _zPt = Candidate::create(_zPair[0], _zPair[1])->pt();
                    for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++) {
                        if(_tightLepsPtCutMllCut[il]==_zPair[0] || _tightLepsPtCutMllCut[il]==_zPair[1]) continue;
                        _MT = Candidate::create(_tightLepsPtCutMllCut[il], _met)->mass();
                        break;
                    }
                }
            }
            if(passMT && passMass){isOnZ=true;}
            if(onZ && isOnZ){
	            _isOnZ=true;
                _isMultiLep = true;
	            counter("Z selection");
            }
            else if(!onZ && !isOnZ){
	            _isOnZ=false;
                _isMultiLep = true;
	            counter("Z selection");
            }
            
            //lepton candidates
            sortSelectedLeps(_tightLepsPtCutMllCut, _tightLepsPtCutMllCutIdx);
        } 

        if(_isMultiLep){
            if(_tightLepsPtCutMllCut.size()>3){_flavor = 4;}
            else{_flavor=_nMus;}
        }
    
        setWorkflow(kGlobal);

        _combList = build3LCombFake(_tightLepsPtCutMllCut, _tightLepsPtCutMllCutIdx, _fakableNotTightLepsPtCut, _fakableNotTightLepsPtCutIdx, _fakableNotTightLepsPtCorrCut, _fakableNotTightLepsPtCorrCutIdx, _nHardestLeptons, _pt_cut_hardest_legs, _nHardLeptons, _pt_cut_hard_legs, onZ, _M_T_3rdLep_MET_cut, _exactlyThreeLep, _combIdxs, _combType );
        //save outcome since we have to run the loop again for the counters
        if(_combList.size()>0 && onZ){
            isFakeOnZ = true;
            combListTemp = _combList;
        }
        if(_combList.size()>0) _isFake = true;

    }//end loop over on/off-Z

    //if combinations got overwritten from off-Z, load on-Z data
    if(isFakeOnZ){
        _isFake = true;
        _combList = combListTemp;
    }

    if(_isMultiLep || _isFake) return true;

    return false;
}

//____________________________________________________________________________
void SUSY3L::advancedSelection(int WF){
    /*
    */
    
    // int offset = 0;
    // if(WF==kGlobal_Fake) offset=kOffZSR017;
   
    if(!_isFake){
        if(_isOnZ) setWorkflow(kOnZBaseline);
        else setWorkflow(kOffZBaseline);
    }    
    if(_isFake){
        if(_isOnZ) setWorkflow(kOnZBaseline_Fake);
        else setWorkflow(kOffZBaseline_Fake);
    }

    //require minimum number of jets
    if(!makeCut<int>( _nJets, _valCutNJetsBR, _cTypeNJetsBR, "jet multiplicity", _upValCutNJetsBR) ) return;
    //require minimum number of b-tagged jets
    if(!makeCut<int>( _nBJets, _valCutNBJetsBR, _cTypeNBJetsBR, "b-jet multiplicity", _upValCutNBJetsBR) ) return;
    //require minimum hadronic activity (sum of jet pT's)
    if(!makeCut<float>( _HT, _valCutHTBR, _cTypeHTBR, "hadronic activity", _upValCutHTBR) ) return;
    //require minimum missing transvers energy
    if(!makeCut<float>( _met->pt(), _valCutMETBR, _cTypeMETBR, "missing transverse energy", _upValCutMETBR) ) return;

    //extra cut for onZ to remove DY
    if(_isOnZ && _met->pt() < 70 && _HT < 400 && _nBJets<2) return;
 
    //long long int evt=_vc->get("evt");
    //if(_vc->get("isData") == 1 && _HT>400 && !_isFake) cout << _vc->get("run") << " " << _vc->get("lumi") << " " << evt << " " << _nMus << " " << _nEls << " " << _nTaus << " " << _nJets << " " << _nBJets <<  " " << _met->pt() << " " << _HT << " "  << _isOnZ  << " " << _isFake << endl;
    //if(_vc->get("isData") == 1 && _HT<400 && !_isFake) return;
    
    //gen matching
    if(!_vc->get("isData") && _doGenMatch && !_isFake) {
        if(!passGenSelection()) return;
        counter("gen matching");
    }
    counter("selected");
    fillHistos(true);

    setWorkflow(WF);

    counter("selected");
    
    fillHistos(true);

    //categorize events into signal regions
    if(_categorization){
        categorize();
      
        //workaround for asymmetric SR 
        if(getCurrentWorkflow()==32) setWorkflow(31);
        if(getCurrentWorkflow()==66) setWorkflow(65);
        if(getCurrentWorkflow()==34) setWorkflow(33);
        if(getCurrentWorkflow()==68) setWorkflow(67);
       
        
        int wf = getCurrentWorkflow();
        int offset = 0;
        if(!_isFake){
            if(_isOnZ){setWorkflow(kOnZBaseline);}
            else{setWorkflow(kOffZBaseline); offset = kOnZSR017;}
        }    
        if(_isFake){
            if(_isOnZ){setWorkflow(kOnZBaseline_Fake); offset = kOffZSR017;}
            else{setWorkflow(kOffZBaseline_Fake); offset = kOnZSR017_Fake;}
        }
        if(offset== kOnZSR017 && wf-offset == 16) fill( "SRS", wf-offset-1 , _weight );
        else fill( "SRS", wf-offset , _weight );
        
        setWorkflow(wf);
        if(getCurrentWorkflow()==kGlobal_Fake){cout << "WARNING " << offset <<  endl;}
        counter("signal region categorization");
        fillHistos(true);
        counter("selected");
    }

}

//____________________________________________________________________________
float SUSY3L::getTF_SingleFake(int ic){
    /*
        Function to extract transfer factor for TTF combination, 
        i.e. for single fake combinations
        parameters: number of fake-tight combination
        return: transfer factors for given combination
    */
    
    if(_combType[ic]!=kIsSingleFake){cout<<"WARNING: called 'getTFSingleFake' for wrong combination"<<endl; return 0;}
    //for single fake combinations with 3 leptons, always last entry is the fake
    float f3=getFR(_combList[ic][2], _combIdxs[ic][2]);
    //calculate transfer factor
    float tF = f3/(1-f3);
    
    return tF;

}


//____________________________________________________________________________
float SUSY3L::getTF_DoubleFake(int ic){
    /*
        Function to extract transfer factor for TFF combination, 
        i.e. for double fake combinations
        parameters: number of fake-tight combination
        return: transfer factors for given combination
    */

    if(_combType[ic]!=kIsDoubleFake){cout<<"WARNING: called 'getTFDoubleFake' for wrong combination"<<endl; return 0;}
    //for double fake combinations with 3 leptons, always last two entries are the fakes
    float f2=getFR(_combList[ic][1], _combIdxs[ic][1]);
    float f3=getFR(_combList[ic][2], _combIdxs[ic][2]);
    //calculate transfer factor
    float tF = - f2*f3/((1-f2)*(1-f3));
    
    return tF;

}

//____________________________________________________________________________
float SUSY3L::getTF_TripleFake(int ic) {
    /*
        Function to extract transfer factor for TFF combination, 
        i.e. for double fake combinations
        parameters: number of fake-tight combination
        return: transfer factors for given combination
    */

    if(_combType[ic]!=kIsTripleFake){cout<<"WARNING: called 'getTFTripleFake' for wrong combination"<<endl; return 0;}

    //get all 3 fake rates
    float f1=getFR(_combList[ic][0], _combIdxs[ic][0]);
    float f2=getFR(_combList[ic][1], _combIdxs[ic][1]);
    float f3=getFR(_combList[ic][2], _combIdxs[ic][2]);
    //calculate transfer factor
    float tF = (f1*f2*f3)/((1-f1)*(1-f2)*(1-f3));

    return tF;

}

//____________________________________________________________________________
bool SUSY3L::wzCRSelection(){
    /*
        selects events for the WZ control region to estimate the WZ background from data
        parameters: none
        return: true: if event passes selection, false: else
    */
    
    setWorkflow(kWZCR);
    
    if(!(_tightLepsPtCutMllCut.size()==3)) return false;
    counter("lepton multiplicity");
    //require hard legs
    //if(!hardLeg(_tightLepsPtCutMllCut, _nHardestLeptons, _pt_cut_hardest_legs, _nHardLeptons, _pt_cut_hard_legs )) return false;
    if(!ptSelection(_tightLepsPtCutMllCut)) return false;
    counter("lepton pt selection");
    //Z selection
    bool pass = false;
    for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++) {
        if(!_susyMod->passMllMultiVeto( _tightLepsPtCutMllCut[il], &_tightLepsPtCutMllCut, 76, 106, true) ){pass = true;}
    }
    if(!pass) return false;
    counter("Z selection");
    _zPair = _susyMod->findZCand( &_tightLepsPtCutMllCut, 15, 50);
    if(_zPair[0] == 0 && _zPair[1] == 0) return false;
    counter("MT cut");
    if(!( _nJets < 2)) return false;
    counter("jet multiplicity");
    if(!( _nBJets == 0)) return false;
    counter("b-jet multiplicity");
    if(!(_met->pt() > 30 && _met->pt() < 100)) return false;
    counter("MET selection");
    counter("selected");
  
    //compute MT of 3rd lepton with MET
    _zMass = Candidate::create(_zPair[0], _zPair[1])->mass();
    _zPt = Candidate::create(_zPair[0], _zPair[1])->pt();
    for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++) {
        if(_tightLepsPtCutMllCut[il]==_zPair[0] || _tightLepsPtCutMllCut[il]==_zPair[1]) continue;
        _MT = Candidate::create(_tightLepsPtCutMllCut[il], _met)->mass();
        break;
    }
   
    //get and sort lepton candidates 
    sortSelectedLeps(_tightLepsPtCutMllCut, _tightLepsPtCutMllCutIdx);
   
    fillHistos(false);
    setWorkflow(kGlobal); 
   
    return true; 
}


//____________________________________________________________________________
bool SUSY3L::wzCRFakeSelection(){
    /*
        selects events for the WZ application region to estimate the WZ background from data
        parameters: none
        return: true: if event passes selection, false: else
    */
    
    setWorkflow(kWZCR_Fake);
    
    if(!(_tightLepsPtCutMllCut.size() + _fakableNotTightLepsPtCut.size() == 3)) return false;
    counter("lepton multiplicity");
 
    //build fakable-not-tight - tight combinations for application region for WZ control region
    _combList = build3LCombFake(_tightLepsPtCutMllCut, _tightLepsPtCutMllCutIdx, _fakableNotTightLepsPtCut, _fakableNotTightLepsPtCutIdx, _fakableNotTightLepsPtCorrCut, _fakableNotTightLepsPtCorrCutIdx, _nHardestLeptons, _pt_cut_hardest_legs, _nHardLeptons, _pt_cut_hard_legs, true, 50., true, _combIdxs, _combType );
    
    //cuts on event variables 
    if(!( _nJets < 2)) return false;
    counter("jet multiplicity");
    if(!( _nBJets == 0)) return false;
    counter("b-jet multiplicity");
    if(!(_met->pt() > 30 && _met->pt() < 100)) return false;
    counter("MET selection");
    counter("selected");
  
    //get and sort lepton candidates 
    CandList clist;
    clist.insert(clist.end(), _tightLepsPtCutMllCut.begin(), _tightLepsPtCutMllCut.end() );
    clist.insert(clist.end(), _fakableNotTightLepsPtCut.begin(), _fakableNotTightLepsPtCut.end() );

    vector<unsigned int> idxs;
    idxs.insert(idxs.end(), _tightLepsPtCutMllCutIdx.begin(), _tightLepsPtCutMllCutIdx.end());
    idxs.insert(idxs.end(), _fakableNotTightLepsPtCutIdx.begin(), _fakableNotTightLepsPtCutIdx.end());

    sortSelectedLeps(clist, idxs);
    
    //event weighting with transfer factor
    float sumTF = 0;
    for(unsigned int ic=0;ic<_combList.size();ic++) {
        int type = _combType[ic];
        if(type==kIsSingleFake){ sumTF += getTF_SingleFake(ic); }
        if(type==kIsDoubleFake){ sumTF += getTF_DoubleFake(ic); }
        if(type==kIsTripleFake){ sumTF += getTF_TripleFake(ic); }
    }
    _weight *= sumTF;
       
    fillHistos(false);
    setWorkflow(kGlobal); 
   
    return true; 
}


//____________________________________________________________________________
void SUSY3L::fakeCRSelection(){
    /*
        selects events for the fake control region to control the fake rate method
        parameters: none
        return: true: if event passes selection, false: else
    */
    
    setWorkflow(kFakeCR);
    
    if(!(_tightLepsPtCutMllCut.size()==3)) return;
    counter("lepton multiplicity");
    //require hard legs
    //if(!hardLeg(_tightLepsPtCutMllCut, _nHardestLeptons, _pt_cut_hardest_legs, _nHardLeptons, _pt_cut_hard_legs )) return;
    if(!ptSelection(_tightLepsPtCutMllCut)) return;
    counter("lepton pt selection");
    //off-Z selection
    for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++) {
        if(!_susyMod->passMllMultiVeto( _tightLepsPtCutMllCut[il], &_tightLepsPtCutMllCut, 76, 106, true) ){return;}
    }
    counter("Z selection");

    if(!( _nJets >= 1 && _nJets <= 2)) return;
    counter("jet multiplicity");
    if(!( _nBJets >= 1)) return;
    counter("b-jet multiplicity");
    if(!(_met->pt() > 30 && _met->pt() < 50)) return;
    counter("MET selection");
    counter("selected");
  
    //get and sort lepton candidates 
    sortSelectedLeps(_tightLepsPtCutMllCut, _tightLepsPtCutMllCutIdx);
   
    fillHistos(false);
    setWorkflow(kGlobal); 
   
}


//____________________________________________________________________________
void SUSY3L::fakeCRFakeSelection(){
    /*
        selects events for the fake control application region to control the fake rate method
        parameters: none
        return: true: if event passes selection, false: else
    */
    
    setWorkflow(kFakeCR_Fake);
    
    if(!(_tightLepsPtCutMllCut.size() + _fakableNotTightLepsPtCut.size() == 3)) return;
    counter("lepton multiplicity");
 
    //build fakable-not-tight - tight combinations for application region for WZ control region
    _combList = build3LCombFake(_tightLepsPtCutMllCut, _tightLepsPtCutMllCutIdx, _fakableNotTightLepsPtCut, _fakableNotTightLepsPtCutIdx, _fakableNotTightLepsPtCorrCut, _fakableNotTightLepsPtCorrCutIdx, _nHardestLeptons, _pt_cut_hardest_legs, _nHardLeptons, _pt_cut_hard_legs, false, -1, true, _combIdxs, _combType );
    
    //cuts on event variables 
    if(!( _nJets >= 1 && _nJets <= 2)) return;
    counter("jet multiplicity");
    if(!( _nBJets >= 1)) return;
    counter("b-jet multiplicity");
    if(!(_met->pt() > 30 && _met->pt() < 50)) return;
    counter("MET selection");
    counter("selected");
 
    //get and sort lepton candidates 
    CandList clist;
    clist.insert(clist.end(), _tightLepsPtCutMllCut.begin(), _tightLepsPtCutMllCut.end() );
    clist.insert(clist.end(), _fakableNotTightLepsPtCut.begin(), _fakableNotTightLepsPtCut.end() );

    vector<unsigned int> idxs;
    idxs.insert(idxs.end(), _tightLepsPtCutMllCutIdx.begin(), _tightLepsPtCutMllCutIdx.end());
    idxs.insert(idxs.end(), _fakableNotTightLepsPtCutIdx.begin(), _fakableNotTightLepsPtCutIdx.end());

    sortSelectedLeps(clist, idxs);
    
    //event weighting with transfer factor
    float sumTF = 0;
    for(unsigned int ic=0;ic<_combList.size();ic++) {
        int type = _combType[ic];
        if(type==kIsSingleFake){ sumTF += getTF_SingleFake(ic); }
        if(type==kIsDoubleFake){ sumTF += getTF_DoubleFake(ic); }
        if(type==kIsTripleFake){ sumTF += getTF_TripleFake(ic); }
    }
    float restoreWeight = _weight;
    _weight *= sumTF;
       
    fillHistos(false);
    _weight = restoreWeight;

    setWorkflow(kGlobal); 
   
}
//____________________________________________________________________________
bool SUSY3L::ZMuMuSelection(){
    /*
        selects Z-> mu mu events for validation plots
        parameters: none
        return: true: if event passes selection, false: else
    */

    if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
    if (!(_vc->get("HLT_SingleMu"))) return false;
    if (_tightLepsPtCutMllCut.size() < 2) return false;
    _idxL1 = _tightLepsPtCutMllCutIdx[0];
    _idxL2 = _tightLepsPtCutMllCutIdx[1];
    if (!(_vc->get("LepGood_pdgId", _idxL1) == -_vc->get("LepGood_pdgId", _idxL2))) return false;
    if (abs(_vc->get("LepGood_pdgId", _idxL1)) != 13) return false;
    if (_vc->get("mZ1") < 60. || _vc->get("mZ1") > 120.) return false;
  
    if (_vc->get("LepGood_charge", _idxL1) < 0) {
        _idxL1 = _tightLepsPtCutMllCutIdx[0];
        _idxL2 = _tightLepsPtCutMllCutIdx[1];
    }
    else if (_vc->get("LepGood_charge", _idxL2) < 0) {
        _idxL1 = _tightLepsPtCutMllCutIdx[1];
        _idxL2 = _tightLepsPtCutMllCutIdx[0];
    }
  
    if (_vc->get("LepGood_pt", _idxL1) < 20) return false;
    if (_vc->get("LepGood_relIso03", _idxL1) > 0.2 ) return false;
    if (abs(_vc->get("LepGood_eta", _idxL1)) > 2.1) return false;

    return true;
}

//____________________________________________________________________________
bool SUSY3L::ZElElSelection(){
    /*
        selects Z-> el el events for validation plots
        parameters: none
        return: true: if event passes selection, false: else
    */

    if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
    if (!(_vc->get("HLT_SingleEl"))) return false;
    if (_tightLepsPtCutMllCut.size() < 2) return false;
    _idxL1 = _tightLepsPtCutMllCutIdx[0];
    _idxL2 = _tightLepsPtCutMllCutIdx[1];
    if (!(_vc->get("LepGood_pdgId", _idxL1) == -_vc->get("LepGood_pdgId", _idxL2))) return false;
    if (abs(_vc->get("LepGood_pdgId", _idxL1)) != 11) return false;
    if (_vc->get("mZ1") < 60. || _vc->get("mZ1") > 120.) return false;
  
    if (_vc->get("LepGood_charge", _idxL1) < 0) {
        _idxL1 = _tightLepsPtCutMllCutIdx[0];
        _idxL2 = _tightLepsPtCutMllCutIdx[1];
    }
    else if (_vc->get("LepGood_charge", _idxL2) < 0) {
        _idxL1 = _tightLepsPtCutMllCutIdx[1];
        _idxL2 = _tightLepsPtCutMllCutIdx[0];
    }
  
    if (_vc->get("LepGood_pt", _idxL1) < 30) return false;
    if (_vc->get("LepGood_relIso03", _idxL1) > 0.2 ) return false;
    if (abs(_vc->get("LepGood_eta", _idxL1)) > 2.1) return false;
  
    return true;
}



//____________________________________________________________________________
bool SUSY3L::ttbarSelection(){
    /*
        selects ttbar events for validation plots
        parameters: none
        return: true: if event passes selection, false: else
    */

    if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
    if (!(_vc->get("HLT_DoubleMu") || _vc->get("HLT_DoubleEl") || _vc->get("HLT_MuEG"))) return false;
    if (_tightLepsPtCutMllCut.size() < 2) return false;
    _idxL1 = _tightLepsPtCutMllCutIdx[0];
    _idxL2 = _tightLepsPtCutMllCutIdx[1];
    if (!(_vc->get("LepGood_pdgId", _idxL1) == -_vc->get("LepGood_pdgId", _idxL2) || abs(_vc->get("LepGood_pdgId", _idxL1)+_vc->get("LepGood_pdgId", _idxL2)) == 2)) return false;
    if (_vc->get("LepGood_pt", _idxL1) < 25. || _vc->get("LepGood_pt", _idxL2) < 15.) return false;
    if (_vc->get("minMllAFAS") < 12.) return false;
    if (_vc->get("nJet40") < 2) return false;
    if (!(_vc->get("nBJetMedium25") >= 1 || _vc->get("nBJetLoose25") == 2)) return false; 
    if (abs(_vc->get("mZ1")-91.2) < 10.)  return false;
  
    return true;
}


//____________________________________________________________________________
bool SUSY3L::ZlSelection(){
    /*
        selects Z->lepton events for validation plots
        parameters: none
        return: true: if event passes selection, false: else
    */

    if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
    if (!(_vc->get("HLT_DoubleMu") || _vc->get("HLT_DoubleEl") || _vc->get("HLT_MuEG"))) return false;
    if (_tightLepsPtCutMllCut.size() !=3 ) return false;
    _idxL1 = _tightLepsPtCutMllCutIdx[0];
    _idxL2 = _tightLepsPtCutMllCutIdx[1];
    _idxL3 = _tightLepsPtCutMllCutIdx[2];
    if (!(_vc->get("LepGood_pdgId", _idxL1) == -_vc->get("LepGood_pdgId", _idxL2))) return false;
    if (abs(_vc->get("mZ1")-91.2) > 15.) return false;
    Candidate* lep3=Candidate::create(_vc->get("LepGood_pt", _idxL3),
                    _vc->get("LepGood_eta", _idxL3),
                    _vc->get("LepGood_phi", _idxL3),
                    _vc->get("LepGood_pdgId", _idxL3),
                    _vc->get("LepGood_charge", _idxL3),
                    0.105);
    float mT= Candidate::create(lep3, _met)->mass();
  
    if (mT > 55.) return false;
    if (_vc->get("minMllAFAS") < 12.) return false;
    if (_vc->get("LepGood_pt", _idxL3) > 50.) return false;
    if (_vc->get("met_pt") > 60.) return false;

    _idxL2 = _idxL3;
    
    return true;
}

//____________________________________________________________________________
bool SUSY3L::WlSelection(){
    /*
        selects W->lepton events for validation plots
        parameters: none
        return: true: if event passes selection, false: else
    */

    if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
    if (!(_vc->get("HLT_SingleMu") || _vc->get("HLT_SingleEl"))) return false;
    if (_tightLepsPtCutMllCut.size() != 2) return false;
    _idxL1 = _tightLepsPtCutMllCutIdx[0];
    _idxL2 = _tightLepsPtCutMllCutIdx[1];
    if (_vc->get("LepGood_charge", _idxL1)*_vc->get("LepGood_charge", _idxL2) < 0) return false;
    bool charge= (_vc->get("LepGood_tightCharge",_idxL1) > (abs(_vc->get("LepGood_pdgId",_idxL1))==11)) && (_vc->get("LepGood_tightCharge",_idxL2) > (abs(_vc->get("LepGood_pdgId",_idxL2))==11));
    if (!charge) return false;
    Candidate* lep=Candidate::create(_vc->get("LepGood_pt", _idxL1),
                   _vc->get("LepGood_eta", _idxL1),
                   _vc->get("LepGood_phi", _idxL1),
                   _vc->get("LepGood_pdgId", _idxL1),
                   _vc->get("LepGood_charge", _idxL1),
                   0.105);
    float mT= Candidate::create(lep, _met)->mass();
    if (_vc->get("LepGood_sip3d",_idxL1) > 4) return false;
    if (_vc->get("LepGood_relIso03",_idxL1) > 0.05) return false;
    if (_vc->get("LepGood_miniRelIso",_idxL1) > 0.05) return false;
    if (_vc->get("nBJetMedium25") != 0) return false;
    if (_vc->get("met_pt") < 30.) return false;
    if (mT < 40.) return false;

    if ((abs(_vc->get("LepGood_pdgId",_idxL1))==11 && abs(_vc->get("LepGood_pdgId",_idxL2))==11) && (_vc->get("mZ1") > 76. && _vc->get("mZ1") < 106.))  return false;
  
    return true;
}


//____________________________________________________________________________
void SUSY3L::categorize(){
    /*
        switch to correct workflow if event is categorized to respective signal region
        parameters: none
        return: none
    */
    int offset = 0;
    if(!_isFake && _isOnZ) offset =1;
    else if(!_isFake && !_isOnZ) offset =1+kOnZSR017;
    else if(_isFake && _isOnZ) offset =1+kOffZSR017;
    else if(_isFake && !_isOnZ) offset =1+ kOnZSR017_Fake;
    
    string categ="";
    for(size_t ic=0;ic< (_categs.size()-6)/2;ic++){
        _SR = _categs[ic];
		if(testRegion() ) {setWorkflow(ic+offset); return;}
    }
    cout << "WARNING Baseline event not categorized. NJets/NBJets/HT/MET " << _nJets << " " << _nBJets << " " << _HT << " " << _metPt << endl;
    setWorkflow(kGlobal);
}


//____________________________________________________________________________
bool SUSY3L::testRegion(){
    /*
        categroizes events into signal regions defined in setSignalRegion()
        parameters: none
        return: none
    */

    bool passSel=true;

    for(size_t is=0;is<_sels[_SR].size();is++) {
        passSel=true;
        for(size_t ii=0;ii<_sels[_SR][is].size();ii++) {
            if(!_au->simpleCut<float>( (*(_val[_sels[_SR][is][ii][0] ])) , atof(_sels[_SR][is][ii][2].c_str() ), _sels[_SR][is][ii][1], atof(_sels[_SR][is][ii][3].c_str()) ) ) 
                {passSel=false;break;}
        }    
    }
    if(passSel) return true;

    return false;
}                               


//____________________________________________________________________________
vector<CandList> SUSY3L::build3LCombFake(const CandList tightLeps, vector<unsigned int> idxsT,
		        const CandList fakableLeps, vector<unsigned int> idxsL,
                const CandList fakableLepsPtCorr, vector<unsigned int> idxsLPtCorr,
                int nHardestLeptons, float pt_cut_hardest_legs, 
                int nHardLeptons, float pt_cut_hard_legs, bool onZ, float MT, bool exactlyThreeLep,
                vector< vector<int> >& combIdxs, vector<int>& combType ) {
    /*
        Function to build all possible combinations of 3 tight and fake leptons (excluding 3 tight combinations)
        On an event base the low invariant mass veto is applied, i.e. no ossf pait with mll<12 must be in the event
        Also on an event base the on/off-Z categorization is performed as for the signal regions. Additionally
        each combination has to fulfill the pt requirements for the 3 legs
        parameters: Candidate lists and their indexes of the tight leptons, the fakeable-not-tight leptons 
        and the fakable-not-tight leptons with cone corrected pt, the pt requirements for the different legs, 
        the boolean whether to select on or off-Z, MT cut of 3rd lep with MET, boolean to decide whether to select 
        exactly 3 lepton or larger eual 3 leptons, and the empty vector for the combinations indexes and types
        return: a vector of candidate lists of all allowed leptons combinations
    */

    //merge the leptons lists
    vector<CandList> vclist;
    CandList clist;
    clist.insert(clist.end(), tightLeps.begin(), tightLeps.end() );
    clist.insert(clist.end(), fakableLeps.begin(), fakableLeps.end() );

    CandList clistPtCorr;
    clistPtCorr.insert(clistPtCorr.end(), tightLeps.begin(), tightLeps.end() );
    clistPtCorr.insert(clistPtCorr.end(), fakableLepsPtCorr.begin(), fakableLepsPtCorr.end() );

    vector<unsigned int> idxs;
    idxs.insert(idxs.end(), idxsT.begin(), idxsT.end());
    idxs.insert(idxs.end(), idxsL.begin(), idxsL.end());

    vector<unsigned int> idxsPtCorr;
    idxsPtCorr.insert(idxsPtCorr.end(), idxsT.begin(), idxsT.end());
    idxsPtCorr.insert(idxsPtCorr.end(), idxsLPtCorr.begin(), idxsLPtCorr.end());

    vector<unsigned int> typeLeps(tightLeps.size(), 1);
    vector<unsigned int> tLepsFake(fakableLepsPtCorr.size(), 0);
    typeLeps.insert(typeLeps.end(), tLepsFake.begin(), tLepsFake.end() );

    int fakeRank = -1;
  
    //reject signal events (can make it up to here if they don't have other Z state which is tested in this iteration
    if(tightLeps.size()>=3){return vclist;}
   
    //require certain number of fakable leptons
    if((_exactlyThreeLep && clist.size()!=3)||(!_exactlyThreeLep && clist.size()<3)){return vclist;}

    //for separation of closure by flavors
    bool pass = true;
    if(_closureByFlavor!=0){
        pass = false;
        //only consider TTF events and require fake to be given flavor
        if((fakableLeps.size()==1) && (tightLeps.size()==2) && (std::abs(fakableLeps[0]->pdgId()) == _closureByFlavor)){pass = true;}
    }
    //enable to limit to TTF events    
    //if((fakableLeps.size()==1) && (tightLeps.size()==2) && (std::abs(fakableLeps[0]->pdgId()) == _closureByFlavor)){pass = true;}

    if(!pass){return vclist;}
    
    //low invariant mass veto
    for(size_t il=0;il<clist.size();il++) {
        if(!_susyMod->passMllMultiVeto( clist[il], &clist, 0, 12, true) ) {return vclist;}
    }
    
    //Z state categorization
    bool passZwindow = false;
    for(size_t il=0;il<clist.size();il++) {
        if(!_susyMod->passMllMultiVeto( clist[il], &clist, 76, 106, true) ){passZwindow = true; break;}
    }
    if(passZwindow){
        //MT requirement
        _zPair = _susyMod->findZCand( &clist, 15, MT);
        if(!(_zPair[0] == 0 && _zPair[1] == 0)){
            _isOnZ=true;
            //compute MT of 3rd lepton with MET
            _zMass = Candidate::create(_zPair[0], _zPair[1])->mass();
            _zPt = Candidate::create(_zPair[0], _zPair[1])->pt();
            for(size_t il=0;il<clist.size();il++) {
                if(clist[il]==_zPair[0] || clist[il]==_zPair[1]) continue;
                _MT = Candidate::create(clist[il], _met)->mass();
                break;
            }
        }
        else{
            //not on-Z if does not pass MT cut
            _isOnZ = false;
        }
    }
    else{
        //not on-Z if does not pass Z mass veto
        _isOnZ = false;
    }

    //return empty list of combinations of event does not pass Z selection
    if((onZ && !_isOnZ) || (!onZ && _isOnZ) )return vclist;
            
    _fEls = 0;
    _fMus = 0;
    for(size_t i=0;i<clistPtCorr.size();i++) {
        if(std::abs(clistPtCorr[i]->pdgId())==13){_fMus+=1;}
        if(std::abs(clistPtCorr[i]->pdgId())==11){_fEls+=1;}
    }
    if(clistPtCorr.size()>3){_flavor=4;}
    else{_flavor=_fMus;}
   
    //prepare all the combinations
    CandList tmpList(3,nullptr);
    for(size_t i1=0;i1<clistPtCorr.size();i1++) {
        for(size_t i2=0;i2<clistPtCorr.size();i2++) {
            for(size_t i3=0;i3<clistPtCorr.size();i3++) {
                if(i1>=i2 || i1>=i3 || i2>=i3) continue;
                tmpList[0] = clistPtCorr[i1];
                tmpList[1] = clistPtCorr[i2];
                tmpList[2] = clistPtCorr[i3];
                vector<int> tmp_idxsPtCorr;
                tmp_idxsPtCorr.push_back(idxsPtCorr[i1]);
                tmp_idxsPtCorr.push_back(idxsPtCorr[i2]);
                tmp_idxsPtCorr.push_back(idxsPtCorr[i3]);
                //if(!hardLeg(tmpList, nHardestLeptons, pt_cut_hardest_legs, nHardLeptons, pt_cut_hard_legs )) continue;
                if(!ptSelection(tmpList)) continue;
                //gen matching for MC closure: at least one lepton which is a fake or a conversion
                if(_fakeSample && _closure && _doGenMatch){
                    if(!genMatched(tmpList, tmp_idxsPtCorr)) continue;
                }
                vclist.push_back(tmpList);
                combIdxs.push_back(tmp_idxsPtCorr);

                int cType=typeLeps[i1]+typeLeps[i2]+typeLeps[i3];
                if(cType==0) combType.push_back(kIsTripleFake);
                if(cType==1) combType.push_back(kIsDoubleFake);
                if(cType==2){
                    combType.push_back(kIsSingleFake);
                    //for studying pt rank of fake lepton in TTF events
                    if(clistPtCorr[2]->pt() <= clistPtCorr[1]->pt() && clistPtCorr[2]->pt() <= clistPtCorr[0]->pt()){fakeRank = 3;}
                    else if(clistPtCorr[2]->pt() > clistPtCorr[1]->pt() && clistPtCorr[2]->pt() <= clistPtCorr[0]->pt()){fakeRank = 2;}
                    else if(clistPtCorr[2]->pt() <= clistPtCorr[1]->pt() && clistPtCorr[2]->pt() > clistPtCorr[0]->pt()){fakeRank = 2;}
                    else if(clistPtCorr[2]->pt() > clistPtCorr[1]->pt() && clistPtCorr[2]->pt() > clistPtCorr[0]->pt()){fakeRank = 1;}
                    else{fakeRank = 5;}
                }
                if(cType==3) {
                    cout<<"WARNING: a signal event is in the fake background application region! "<<endl;
                }
            } 
        }
    }

    //lepton candidates
    sortSelectedLeps(clistPtCorr, idxsPtCorr);
    if(_doPlotsVerbose){
        fill("nFO", clist.size(),   _weight);
        fill("nFakeComb", vclist.size(),    _weight);
        fill("ptRank", fakeRank,    _weight);
    }

    return vclist;
}


//____________________________________________________________________________
bool SUSY3L::hardLeg(CandList leptons, int n_hardestLeg, float cut_hardestLeg, int n_hardLeg, float cut_hardLeg){
    /*
        Checks if the event has at least _nHardestLeptons leptons
        (muon or electron) fullfilling a harsher pT cut and _nHardLeptons leptons fulfilling another lower cut
        return: true (if the event has _nHardestLeptons and _nHardLeptons with higher pT), false (else)
    */

    int nHardestLepCount = 0;
    int nHardLepCount = 0;

    for(size_t ie=0; ie<leptons.size(); ++ie){
        if(leptons[ie]->pt()>cut_hardLeg){
            nHardLepCount += 1;
            if(leptons[ie]->pt()>cut_hardestLeg){
                nHardestLepCount += 1;
            }
        }
    }
    //correct number of leptons of hardLeg requirement with required number of leptons with hardestLeg
    nHardLepCount -= _nHardLeptons;

    if(nHardestLepCount >= n_hardestLeg && nHardLepCount >= n_hardLeg) return true;

    return false;

}

//____________________________________________________________________________
bool SUSY3L::ptSelection(CandList leptons){
    /*
        Makes the pt selection of the leptons. Depending in whether the offline HT is below or above 400 GeV
        different flavor dependent pt cuts apply to the leading and subleading leg
        return: true (if the event fulfills pt selection), false (else)
    */

    
    //sort list of lepton by pt

    CandList leps_tmp;
    CandList leps_tmp2;
        
    for(size_t il=0;il<leptons.size();il++){
        leps_tmp.push_back(leptons[il]);
    }
    leptons.clear();

    while(leps_tmp.size()>0){
        float pt = -1;
        float pt_tmp = -1;
        size_t i_save = -1;
        for(size_t i=0; i < leps_tmp.size(); i++){
            pt_tmp = leps_tmp[i]->pt();
            if(pt_tmp > pt){
                pt = pt_tmp;
                i_save = i;
            }
        }
        for(size_t i=0; i < leps_tmp.size(); i++){
            if(i!=i_save){
                leps_tmp2.push_back(leps_tmp[i]);
            }
        }
        leptons.push_back(leps_tmp[i_save]);
            
        leps_tmp.clear();
        leps_tmp = leps_tmp2;
        leps_tmp2.clear();
    }

    //check that lepton list is pt ordered
    if(leptons[2]->pt()>leptons[1]->pt() || leptons[2]->pt()>leptons[0]->pt() || leptons[1]->pt()>leptons[0]->pt()){
        cout << "WARNING: lepton candidate list not pt ordered in ptSelection" << endl;
    }
    
    //offline HT below HT trigger plateau
    if(_HT<400){
        //leading leg
        if(std::abs(leptons[0]->pdgId())==13 && leptons[0]->pt()<20) return false;
        if(std::abs(leptons[0]->pdgId())==11 && leptons[0]->pt()<25) return false;
        //sub-leading leg
        if(std::abs(leptons[1]->pdgId())==13 && leptons[1]->pt()<10) return false;
        if(std::abs(leptons[1]->pdgId())==11 && leptons[1]->pt()<15) return false;
    }
    //offline HT above HT trigger plateau
    else{
        //leading leg
        if(std::abs(leptons[0]->pdgId())==13 && leptons[0]->pt()<10) return false;
        if(std::abs(leptons[0]->pdgId())==11 && leptons[0]->pt()<15) return false;
        //sub-leading leg
        if(std::abs(leptons[1]->pdgId())==13 && leptons[1]->pt()<10) return false;
        if(std::abs(leptons[1]->pdgId())==11 && leptons[1]->pt()<15) return false;
    }
   
/*      
    //offline HT below HT trigger plateau
    if(_HT<400){
        //leading leg
        if(std::abs(leptons[0]->pdgId())==13 && leptons[0]->pt()<20) return false;
        if(std::abs(leptons[0]->pdgId())==11 && leptons[0]->pt()<20) return false;
        //sub-leading leg
        if(std::abs(leptons[1]->pdgId())==13 && leptons[1]->pt()<15) return false;
        if(std::abs(leptons[1]->pdgId())==11 && leptons[1]->pt()<15) return false;
    }
    //offline HT above HT trigger plateau
    else{
        //leading leg
        if(std::abs(leptons[0]->pdgId())==13 && leptons[0]->pt()<20) return false;
        if(std::abs(leptons[0]->pdgId())==11 && leptons[0]->pt()<20) return false;
        //sub-leading leg
        if(std::abs(leptons[1]->pdgId())==13 && leptons[1]->pt()<15) return false;
        if(std::abs(leptons[1]->pdgId())==11 && leptons[1]->pt()<15) return false;
    }
*/    
   
    
    return true;

}

//____________________________________________________________________________
float SUSY3L::lowestOssfMll(CandList leps){
    /*
        Checks if event has an ossf lepton pair and computes the lowest invariant mass of all ossf pairs
        parameters: CandList of leptons for with the lowest ossf pair mll should be computed
        return: smallest mll of ossf lepton pair if a pair is found, -1 if no ossf pair is found
    */
    
  //bool pair_found = false;
    float mll = 99999;

    //loop over all possible combination of two leptons
    for(size_t il1=0; il1 < leps.size(); il1++) {
        for(size_t il2 = il1; il2 < leps.size(); il2++) {
            //continue if not an ossf pair
            if( leps[il1]->pdgId() != - leps[il2]->pdgId()) continue;
            //save mll if it is the smallest of all mll found so far
            float mll_tmp = Candidate::create(leps[il1], leps[il2])->mass();
            //pair_found = true;
            if(mll_tmp < mll){
                mll = mll_tmp;
            }
        }
    }   

    //in case no ossf pair is found 
    if(mll==99999){mll = -999;}
     
    return mll;
}


/*******************************************************************************
* ******************************************************************************
* ** EXECUTING TASKS                                                          **
* ******************************************************************************
* *****************************************************************************/

//____________________________________________________________________________
void SUSY3L::fillHistos(bool additionalPlots){
    /*
        fills plots
        parameters: none
        return: none
    */
    if(!_doPlots) return; 

    //event observables
    fill("HT"       , _HT                   , _weight);
    fill("MET"      , _met->pt()            , _weight);
    fill("NBJets"   , _nBJets               , _weight);
    fill("NJets"    , _nJets                , _weight);
    fill("MT"       , _MT                   , _weight);

    //lepton observables
    fill("pt_1st_lepton" , _leps[0]->pt()   , _weight);
    fill("pt_2nd_lepton" , _leps[1]->pt()   , _weight);
    fill("pt_3rd_lepton" , _leps[2]->pt()   , _weight);
    
    fill("flavor"   , _flavor               , _weight);
     
    if(!_isFake){
        fill("mu_multiplicity"  , _nMus         , _weight);
        fill("el_multiplicity"  , _nEls         , _weight);
        fill("lep_multiplicity" , _nMus+_nEls   , _weight);
    }
    if(_isFake){
        fill("mu_multiplicity"  , _fMus         , _weight);
        fill("el_multiplicity"  , _fEls         , _weight);
        fill("lep_multiplicity" , _fMus+_fEls   , _weight);
    }
    
    if(!_doPlotsVerbose) return; 

    fill("lep1_SIP3D" , _vc->get("LepGood_sip3d", _lepsIdx[0])                  , _weight);
    fill("lep1_dxy"   , _vc->get("LepGood_dxy"  , _lepsIdx[0])*10000            , _weight);
    fill("lep1_dz"    , _vc->get("LepGood_dz"   , _lepsIdx[0])*10000            , _weight);
    fill("lep2_SIP3D" , _vc->get("LepGood_sip3d", _lepsIdx[1])                  , _weight);
    fill("lep2_dxy"   , _vc->get("LepGood_dxy"  , _lepsIdx[1])*10000            , _weight);
    fill("lep2_dz"    , _vc->get("LepGood_dz"   , _lepsIdx[1])*10000            , _weight);
    fill("lep3_SIP3D" , _vc->get("LepGood_sip3d", _lepsIdx[2])                  , _weight);
    fill("lep3_dxy"   , _vc->get("LepGood_dxy"  , _lepsIdx[2])*10000            , _weight);
    fill("lep3_dz"    , _vc->get("LepGood_dz"   , _lepsIdx[2])*10000             , _weight);
 
    //on-Z observables
    fill("Zmass"    , _zMass                , _weight);
    fill("Zpt"      , _zPt                  , _weight);
 
    if(!additionalPlots) return;
   
    //other observables
    _lowOSSFMll = lowestOssfMll(_tightLepsPtCutMllCut);
    fill("lowestOssfMll"    , _lowOSSFMll   , _weight);
   

}

//____________________________________________________________________________
void SUSY3L::fillValidationHistos(string reg){
    /*
        fills validation plots
        parameters: selection for validation plots
        return: none
    */

    fill(reg+"_lep1_jetPtRatio", _vc->get("LepGood_jetPtRatiov2", _idxL1)           , _weight);
    fill(reg+"_lep1_jetPtRel"  , _vc->get("LepGood_jetPtRelv2", _idxL1)             , _weight);
    fill(reg+"_lep1_miniRelIso", _vc->get("LepGood_miniRelIso", _idxL1)             , _weight);
    fill(reg+"_lep1_Pt"        , _vc->get("LepGood_pt", _idxL1)                     , _weight);
    fill(reg+"_lep1_Eta"       , fabs(_vc->get("LepGood_eta", _idxL1))              , _weight);
    fill(reg+"_lep1_SIP3D"     , _vc->get("LepGood_sip3d", _idxL1)                  , _weight);
    fill(reg+"_lep1_dxy"       , _vc->get("LepGood_dxy", _idxL1)                    , _weight);
    fill(reg+"_lep1_dz"        , _vc->get("LepGood_dz", _idxL1)                     , _weight);
  
    fill(reg+"_lep2_jetPtRatio", _vc->get("LepGood_jetPtRatiov2", _idxL2)           , _weight);
    fill(reg+"_lep2_jetPtRel"  , _vc->get("LepGood_jetPtRelv2", _idxL2)             , _weight);
    fill(reg+"_lep2_miniRelIso", _vc->get("LepGood_miniRelIso", _idxL2)             , _weight);
    fill(reg+"_lep2_Pt"        , _vc->get("LepGood_pt", _idxL2)                     , _weight);
    fill(reg+"_lep2_Eta"       , fabs(_vc->get("LepGood_eta", _idxL2))              , _weight);
    fill(reg+"_lep2_SIP3D"     , _vc->get("LepGood_sip3d", _idxL2)                  , _weight);
    fill(reg+"_lep2_dxy"       , _vc->get("LepGood_dxy", _idxL2)                    , _weight);
    fill(reg+"_lep2_dz"        , _vc->get("LepGood_dz", _idxL2)                     , _weight);
    
    fill(reg+"_MET"            , _vc->get("met_pt")                                 , _weight);
    fill(reg+"_htJet40j"       , _vc->get("htJet40j")                               , _weight);
    fill(reg+"_mZ1"            , _vc->get("mZ1")                                    , _weight);
    fill(reg+"_NBJetsLoose25"  , _vc->get("nBJetLoose25")                           , _weight);
    fill(reg+"_NBJetsMedium25" , _vc->get("nBJetMedium25")                          , _weight);
    fill(reg+"_NBJetsTight40"  , _vc->get("nBJetTight40")                           , _weight);
    fill(reg+"_NJets40"        , _vc->get("nJet40")                                 , _weight);
    
}  

//____________________________________________________________________________
float SUSY3L::DeltaPhi(float phi1, float phi2){
    /*
        computes delta phi for two giveb phis taking into account the phi range
        parameters: phi1, phi2
        return: delta phi
    */

        float result = phi1 - phi2;
        while( result >   TMath::Pi() ) result -= TMath::TwoPi();
        while( result <= -TMath::Pi() ) result += TMath::TwoPi();
        
        return TMath::Abs(result);
       
       
}

//____________________________________________________________________________
float SUSY3L::M_T(float pt_lepton, float met, float phi_lepton, float phi_met){
    /*
        computes the transverse mass for a lepton and met
        parameters: pt_lepton, met, phi_lepton, phi_met
        return: transverse mass M_T
    */

        float deltaPhi = DeltaPhi(phi_lepton, phi_met);
        float m_t = 0;
        m_t = sqrt(2 * pt_lepton * met * (1 - cos(deltaPhi) ));
        return m_t;
}

//____________________________________________________________________________
float SUSY3L::MT2(Candidate* lep1, Candidate* lep2, Candidate* met, double mass_invisible){
    /*
        calculates the MT2 variable based on the mt2_bisect class
        parameters: 2 leptons candidates, the met candidate, and the mass of the invisible particles
        return: value of MT2
    */

        double pa[3]     = { lep1->mass()   , lep1->px()    , lep1->py()    };
        double pb[3]     = { lep2->mass()   , lep2->px()    , lep2->py()    };
        double pmiss[3]  = { 0              , met->px()     , met->py()     };
        
        mt2 mt2_event;
        mt2_event.set_momenta( pa, pb, pmiss );
        mt2_event.set_mn( mass_invisible );
        double mt2_value = mt2_event.get_mt2();

        return mt2_value;


}

//____________________________________________________________________________
void SUSY3L::sortSelectedLeps(CandList leps, std::vector<unsigned int> lepsIdx){
    /*
        sorts a list of lepton candates according to their pt
        parameters: the candidate list, the idx vector of the list
        return: none
    */
        CandList leps_tmp;
        CandList leps_tmp2;
        std::vector<unsigned int> lepsIdx_tmp;
        std::vector<unsigned int> lepsIdx_tmp2;
        
        for(size_t il=0;il<leps.size();il++){
            leps_tmp.push_back(leps[il]);
            lepsIdx_tmp.push_back(lepsIdx[il]);
        }
        _leps.clear();
        _lepsIdx.clear();

        while(leps_tmp.size()>0){
            float pt = -1;
            float pt_tmp = -1;
            size_t i_save = -1;
            for(size_t i=0; i < leps_tmp.size(); i++){
                pt_tmp = leps_tmp[i]->pt();
                if(pt_tmp > pt){
                    pt = pt_tmp;
                    i_save = i;
                }
            }
            for(size_t i=0; i < leps_tmp.size(); i++){
                if(i!=i_save){
                    leps_tmp2.push_back(leps_tmp[i]);
                    lepsIdx_tmp2.push_back(lepsIdx_tmp[i]);
                }
            }
            _leps.push_back(leps_tmp[i_save]);
            _lepsIdx.push_back(lepsIdx_tmp[i_save]);
            
            leps_tmp.clear();
            lepsIdx_tmp.clear();
            leps_tmp = leps_tmp2;
            lepsIdx_tmp = lepsIdx_tmp2;
            leps_tmp2.clear();
            lepsIdx_tmp2.clear();
        }
 
}

//____________________________________________________________________________
bool SUSY3L::passGenSelection(){
    /*
        checks if at least one lepton is fake or conversion at gen level for 
        simulation processes which are supposed to yield such leptons
        parameters: none
        return: true (if gen matched), false (else)
    */

    //data or MC sample yielding prompt leptons
    if(_vc->get("isData") || _promptSample){
        return true;
    }
    
    //fakes
    else if( _fakeSample && !_closure) {
        for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++){
            if(_vc->get("LepGood_mcMatchId",_tightLepsPtCutMllCutIdx[il])==0 && _vc->get("LepGood_mcPromptGamma",_tightLepsPtCutMllCutIdx[il])==0) return true;
        }
    }
    else if( _fakeSample && _closure) {
        for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++){
            if(_vc->get("LepGood_mcMatchId",_tightLepsPtCutMllCutIdx[il])==0) return true;
        }
    }
    //conversions
    else if( _convSample && !_closure){
        for(size_t il=0;il<_tightLepsPtCutMllCut.size();il++){
            if(_vc->get("LepGood_mcMatchId",_tightLepsPtCutMllCutIdx[il])==0 && _vc->get("LepGood_mcPromptGamma",_tightLepsPtCutMllCutIdx[il])==1) return true;
        }
 
    }

    return false;

}

//____________________________________________________________________________
bool SUSY3L::genMatched(const CandList leptons, vector<int> lepIdx){
    /*
        checks if at least one lepton is fake or conversion at gen level
        parameters: none
        return: true (if gen matched), false (else)
    */

    //data
    if(_vc->get("isData")){
        return true;
    }
 
    for(size_t il=0;il<leptons.size();il++){
        if(_vc->get("LepGood_mcMatchId", lepIdx[il])==0) return true;
    }

    return false;

}

//____________________________________________________________________________
void SUSY3L::checkSample(){
    /*
        tests if simulation sample is fakes, conversions or irreducible background
        parameters: none
        return: none
    */

    //samples yielding fakes
    if( _sampleName.find("DYJets")!=(size_t)-1 || _sampleName.find("TTJets")!=(size_t)-1 || _sampleName.find("WJets")!=(size_t)-1 || _sampleName.find("TTLep")!=(size_t)-1 || _sampleName.find("TToLeptons")!=(size_t)-1 || _sampleName.find("TBarToLeptons")!=(size_t)-1 || _sampleName.find("TBar_tWch")!=(size_t)-1 || _sampleName.find("T_tWch")!=(size_t)-1 || _sampleName.find("WWTo2L2Nu")!=(size_t)-1 || _sampleName.find("ZZTo2L2Nu")!=(size_t)-1) {
        _fakeSample = true;
        _convSample = false;
        _promptSample = false;
    }

    //samples yielding conversions
    else if( _sampleName.find("WGToLNuG")!=(size_t)-1 || _sampleName.find("ZGTo2LG")!=(size_t)-1 || _sampleName.find("TTGJets")!=(size_t)-1 || _sampleName.find("TGJets")!=(size_t)-1){
        _convSample = true;
        _fakeSample = false;
        _promptSample = false;

    }

    //samples yielding irreducible background
    else if(!_vc->get("isData")){
        _promptSample = true;
        _convSample = false;
        _fakeSample = false;
    }

}


//____________________________________________________________________________
void SUSY3L::registerTriggerVars(){
    /*
        register tree variables for trigger bits
        parameters: none
        return: none
    */

    for(unsigned int i=0;i<_vTR_lines.size();++i) 
        _vc->registerVar(_vTR_lines[i]);
}


//____________________________________________________________________________
bool SUSY3L::passHLTbit(){
    /*
        checks if the event has been triggerd by any of the HLT trigger lines
        parameters: none
        return: true (if event has been triggered), false (else)
    */
 
    //for 80X simulation return true
    if(_version == 8 && !_vc->get("isData")) return true;
    
    vector<string> lines;

    lines = _vTR_lines;

    for(unsigned int i = 0; i < lines.size(); ++i){
        if(_vc->get(lines[i]) == 1) {
            return true;
        }
    }

    return false;

}


//____________________________________________________________________________
bool SUSY3L::passNoiseFilters(){
    /*
        
    */

    if(_vc->get("Flag_badChargedHadronFilter"   ) == 0) return false;               
    if(_vc->get("Flag_badMuonFilter"            ) == 0) return false;               

    if(!_vc->get("isData")) return true;

    if(_vc->get("hbheFilterNew25ns"             ) == 0) return false;
    if(_vc->get("hbheFilterIso"                 ) == 0) return false;
    if(_vc->get("Flag_eeBadScFilter"            ) == 0) return false;
    if(_vc->get("Flag_goodVertices"             ) == 0) return false;
    if(_vc->get("Flag_globalTightHalo2016Filter") == 0) return false;
 
    return true;

}


//____________________________________________________________________________
bool SUSY3L::checkMassBenchmark(){

    // float M1=_vc->get("GenSusyMScan1");
    // float M2=_vc->get("GenSusyMScan2");
  float M1=_vc->get("GenSusyMGluino");
  float M2=_vc->get("GenSusyMNeutralino");

    ostringstream os,os1;
    os<<M1;
    os1<<M2;
    string s;
    if(_susyProcessName == "T1tttt") s="_"+os.str()+"_mN_"+os1.str();
    if(_susyProcessName == "T6ttWW") s="_"+os.str()+"_"+os1.str();
    if(_susyProcessName == "T5qqqqVV") s="_"+os.str()+"_"+os1.str();
    if(_susyProcessName == "T5ttttdeg") s="_"+os.str()+"_"+os1.str();
    
    if(_ie==0 && _susyProcessName == "T1tttt") {
      unsigned int p=_sampleName.find("_",8);
        unsigned int p1=_sampleName.find("_",p+1);
	unsigned int p1b=_sampleName.find("_",p1+1);
        unsigned int p2=_sampleName.find("_",p1b+1);
	//cout<<_sampleName<<"   "<<p<<"  "<<p1<<"  "<<p2<<"   "<<_sampleName.substr(p+1,p1-p-1)<<"  "<<_sampleName.substr(p1+1,p2-p1-1)<<endl;
        float m1=stof( _sampleName.substr(p+1,p1-p-1) );
        float m2=stof( _sampleName.substr(p1b+1,p2-p1b-1) );
        float xb = _hScanWeight->GetXaxis()->FindBin(m1);
        float yb = _hScanWeight->GetYaxis()->FindBin(m2);
        float zb = _hScanWeight->GetZaxis()->FindBin(0.);
	//cout<<m1<<"  "<<m2<<"  "<<_hScanWeight2D->GetBinContent(xb,yb)<<endl;
        //_nProcEvtScan=_hScanWeight2D->GetBinContent(xb,yb);
	_nProcEvtScan=_hScanWeight->GetBinContent(xb,yb,zb);
    }
 
    if(_ie==0 && (_susyProcessName == "T6ttWW" || _susyProcessName == "T5qqqqVV" || _susyProcessName == "T5ttttdeg")) {
        unsigned int p=_sampleName.find("_");
        unsigned int p1=_sampleName.find("_",p+1);
        unsigned int p2=_sampleName.size();
        float m1=stof( _sampleName.substr(p+1,p1-p-1) );
        float m2=stof( _sampleName.substr(p1+1,p2-p1-1) );
        float xb = _hScanWeight->GetXaxis()->FindBin(m1);
        float yb = _hScanWeight->GetYaxis()->FindBin(m2);
        float zb = _hScanWeight->GetZaxis()->FindBin(1);
  
        _nProcEvtScan=_hScanWeight->GetBinContent(xb,yb,zb);
    }

    if(_sampleName.find(s)==string::npos) return false;
 
    float XS = _dbm->getDBValue(_susyProcessName+"Xsect",M1);
    //cout<<XS<<"  "<<_nProcEvtScan<<endl;
    _weight *= XS/_nProcEvtScan;
    
    return true;

}


//____________________________________________________________________________
void SUSY3L::loadScanHistogram(){
  
    if(_fastSim){ 
        string mpafenv=string(getenv ("MPAF"))+"/workdir/database/histoScan"+_susyProcessName+"_2016.root";
        TFile* file=new TFile(mpafenv.c_str(),"read");
        _hScanWeight=(TH3D*)file->Get("CountSMS");
	_hScanWeight2D=(TH2D*)file->Get("CountSMS2D");
    }
}


//____________________________________________________________________________
float SUSY3L::getFastSimXFactor(float dir){

    if(std::abs(dir)!=1){cout << "Warning: wrong parameter for getFastSimXFactor, returning 1" << endl;}

    if(_susyProcessName == "T1tttt"){
        if(dir == 1) return 1.34;
        else return 0.7277;
    }
    if(_susyProcessName == "T6ttWW"){
        if(dir == 1) return 1.333;
        else return 0.7312;
    }
     if(_susyProcessName == "T5qqqqVV" || _susyProcessName == "T5ttttdeg"){
        if(dir == 1) return 1.34;
        else return 0.7275;
    }
    else{
        cout << "Warning: could not find X factors for susy model " << _susyProcessName << endl;
        return 1;
    }

}

//____________________________________________________________________________
void SUSY3L::systUnc(){

    //uncertanties
    float lumiUnc           = 0.027;
    float hltUnc            = 0.03;
    float lepUnc            = 0.06;
    float rareUnc           = 0.50;
    float xgUnc             = 0.50;
    float wzNormUnc         = 0.15;
    float ttzhPdfUnc        = 0.02;
    float ttzhLowMPdfUnc    = 0.06;
    float ttwPdfUnc         = 0.03;
    float ttzhXSUnc         = 0.11;
    float ttzhLowMXSUnc     = 0.33;
    float ttwXSUnc          = 0.13;
    float fakeUnc           = 0.30;
    float ttzhAccHtlUnc     = 0.05;
    float ttzhAccHthUnc     = 0.08;
    float ttzLowMAccHtlUnc  = 0.05;
    float ttzLowMAccHthUnc  = 0.08;
    float ttwAccHtlUnc      = 0.05;    
    float ttwAccHthUnc      = 0.18;
    float wzExtrHtlUnc      = 0.10;
    float wzExtrHthUnc      = 0.20;
    float wzExtrSR13Unc     = 0.30;
    float ttwNloLoHtlUnc    = 0.01;
    float ttwNloLoHtmUnc    = 0.13;
    float ttwNloLoHthUnc    = 0.30;
    float ttzNloLoHtlUnc    = 0.13;
    float ttzNloLoHtmUnc    = 0.06;
    float ttzNloLoHthUnc    = 0.70;



    bool lowHTregion = false;
    if(_HT>400 || _nBJets > 2 || _met->pt() > 300) lowHTregion = false;

    //flat uncertainties
    
    //uncertainties for all MC non-data driven MC backgrounds and signals
    if(_sampleName.find("GGHZZ4L") != string::npos || _sampleName.find("VHToNonbb") != string::npos ||_sampleName.find("ZZTo4L") != string::npos ||_sampleName.find("WWZ") != string::npos ||_sampleName.find("WZZ") != string::npos ||_sampleName.find("ZZZ") != string::npos ||_sampleName.find("TTTT") != string::npos ||_sampleName.find("tZq_ll") != string::npos ||_sampleName.find("TGJets") != string::npos ||_sampleName.find("TTGJets") != string::npos ||_sampleName.find("WGToLNuG") != string::npos ||_sampleName.find("ZGTo2LG") != string::npos ||_sampleName.find("TTZ") != string::npos || _sampleName.find("TTW") != string::npos || _sampleName.find("TTHnobb_pow") != string::npos || _sampleName.find("TTLLJets_m1to10") != string::npos || _sampleName.find("T1tttt") != string::npos || _sampleName.find("T6ttWW") != string::npos || _sampleName.find("T5qqqq") != string::npos || _fastSim){

        //lumi
        if((isInUncProc() &&  getUncName()=="lumi") && SystUtils::kUp   == getUncDir() ){_weight *= 1+lumiUnc;}
	    if((isInUncProc() &&  getUncName()=="lumi") && SystUtils::kDown == getUncDir() ){_weight *= 1-lumiUnc;}
	    //HLT
        if((isInUncProc() &&  getUncName()=="HLTEff") && SystUtils::kUp   == getUncDir() ){_weight *= 1+hltUnc;}
	    if((isInUncProc() &&  getUncName()=="HLTEff") && SystUtils::kDown == getUncDir() ){_weight *= 1-hltUnc;}
	    //lepton efficiency
        if((isInUncProc() &&  getUncName()=="LepEff") && SystUtils::kUp   == getUncDir() ){_weight *= 1+lepUnc;}
	    if((isInUncProc() &&  getUncName()=="LepEff") && SystUtils::kDown == getUncDir() ){_weight *= 1-lepUnc;}
    }

    //rare processes
    if(_sampleName.find("GGHZZ4L") != string::npos || _sampleName.find("VHToNonbb") != string::npos ||_sampleName.find("ZZTo4L") != string::npos ||_sampleName.find("WWZ") != string::npos ||_sampleName.find("WZZ") != string::npos ||_sampleName.find("ZZZ") != string::npos ||_sampleName.find("TTTT") != string::npos ||_sampleName.find("tZq_ll") != string::npos ){
        //rare x-section
        if((isInUncProc() &&  getUncName()=="rare") && SystUtils::kUp   == getUncDir() ){_weight *= 1+rareUnc;}
	    if((isInUncProc() &&  getUncName()=="rare") && SystUtils::kDown == getUncDir() ){_weight *= 1-rareUnc;}
	}

    //X+gamma
    if(_sampleName.find("TGJets") != string::npos ||_sampleName.find("TTGJets") != string::npos ||_sampleName.find("WGToLNuG") != string::npos ||_sampleName.find("ZGTo2LG") != string::npos ){
        //xg
        if((isInUncProc() &&  getUncName()=="XG") && SystUtils::kUp   == getUncDir() ){_weight *= 1+xgUnc;}
	    if((isInUncProc() &&  getUncName()=="XG") && SystUtils::kDown == getUncDir() ){_weight *= 1-xgUnc;}
	}

    //WZ
    if(_sampleName.find("WZTo3LNu") != string::npos ){
        //normalization
        if((isInUncProc() &&  getUncName()=="ra7_WZ") && SystUtils::kUp   == getUncDir() ){_weight *= 1+wzNormUnc;}
	    if((isInUncProc() &&  getUncName()=="ra7_WZ") && SystUtils::kDown == getUncDir() ){_weight *= 1-wzNormUnc;}
	    //extrapolation
        if((isInUncProc() &&  getUncName()=="wz_extr") && SystUtils::kUp==getUncDir() && lowHTregion) {_weight *= 1+wzExtrHtlUnc;}
        if((isInUncProc() &&  getUncName()=="wz_extr") && SystUtils::kDown==getUncDir() && lowHTregion) {_weight *= 1-wzExtrHtlUnc;}
        if((isInUncProc() &&  getUncName()=="wz_extr") && SystUtils::kUp==getUncDir() && !lowHTregion && _nBJets <3) {_weight *= 1+wzExtrHthUnc;}
        if((isInUncProc() &&  getUncName()=="wz_extr") && SystUtils::kDown==getUncDir() && !lowHTregion && _nBJets <3) {_weight *= 1-wzExtrHthUnc;}
        if((isInUncProc() &&  getUncName()=="wz_extr") && SystUtils::kUp==getUncDir() && _nBJets >=3) {_weight *= 1+wzExtrSR13Unc;}
        if((isInUncProc() &&  getUncName()=="wz_extr") && SystUtils::kDown==getUncDir() && _nBJets >=3) {_weight *= 1-wzExtrSR13Unc;}
    
    
    }

    //ttZH
    if(_sampleName.find("TTZ") != string::npos || _sampleName.find("TTHnobb_pow") != string::npos ){
        //pdf uncertanty
        if((isInUncProc() &&  getUncName()=="ttzh_pdf") && SystUtils::kUp   == getUncDir() ){_weight *= 1+ttzhPdfUnc;}
	    if((isInUncProc() &&  getUncName()=="ttzh_pdf") && SystUtils::kDown == getUncDir() ){_weight *= 1-ttzhPdfUnc;}
	    //x-section uncertanty
        if((isInUncProc() &&  getUncName()=="TTZH") && SystUtils::kUp   == getUncDir() ){_weight *= 1+ttzhXSUnc;}
	    if((isInUncProc() &&  getUncName()=="TTZH") && SystUtils::kDown == getUncDir() ){_weight *= 1-ttzhXSUnc;}
	    //acceptance, low mass
        if((isInUncProc() &&  getUncName()=="ttzh_extr_htl") && SystUtils::kUp==getUncDir() && lowHTregion) {_weight *= 1+ttzhAccHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttzh_extr_htl") && SystUtils::kDown==getUncDir() && lowHTregion) {_weight *= 1-ttzhAccHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttzh_extr_hth") && SystUtils::kUp==getUncDir() && !lowHTregion) {_weight *= 1+ttzhAccHthUnc;}
        if((isInUncProc() &&  getUncName()=="ttzh_extr_hth") && SystUtils::kDown==getUncDir() && !lowHTregion) {_weight *= 1-ttzhAccHthUnc;}
 
    
    }
    if(_sampleName.find("TTZ") != string::npos ){
        if((isInUncProc() &&  getUncName()=="ttzLO") && SystUtils::kUp==getUncDir() && _HT < 400) {_weight *= 1+ttzNloLoHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttzLO") && SystUtils::kDown==getUncDir() && _HT < 400) {_weight *= 1-ttzNloLoHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttzLO") && SystUtils::kUp==getUncDir() && _HT > 400 && _HT < 600) {_weight *= 1+ttzNloLoHtmUnc;}
        if((isInUncProc() &&  getUncName()=="ttzLO") && SystUtils::kDown==getUncDir() && _HT > 400 && _HT < 600) {_weight *= 1-ttzNloLoHtmUnc;}
        if((isInUncProc() &&  getUncName()=="ttzLO") && SystUtils::kUp==getUncDir() && _HT > 600) {_weight *= 1+ttzNloLoHthUnc;}
        if((isInUncProc() &&  getUncName()=="ttzLO") && SystUtils::kDown==getUncDir() && _HT > 600) {_weight *= 1-ttzNloLoHthUnc;}
    } 
    
    if( _sampleName.find("TTLLJets_m1to10") != string::npos  ){
        //pdf uncertanty, low mass
        if((isInUncProc() &&  getUncName()=="ttzh_pdf") && SystUtils::kUp   == getUncDir() ){_weight *= 1+ttzhLowMPdfUnc;}
	    if((isInUncProc() &&  getUncName()=="ttzh_pdf") && SystUtils::kDown == getUncDir() ){_weight *= 1-ttzhLowMPdfUnc;}
	    //x-section uncertanty, low mass
        if((isInUncProc() &&  getUncName()=="TTZH") && SystUtils::kUp   == getUncDir() ){_weight *= 1+ttzhLowMXSUnc;}
	    if((isInUncProc() &&  getUncName()=="TTZH") && SystUtils::kDown == getUncDir() ){_weight *= 1-ttzhLowMXSUnc;}
        //acceptance, low mass
        if((isInUncProc() &&  getUncName()=="ttz_lowM_extr_htl") && SystUtils::kUp==getUncDir() && lowHTregion) {_weight *= 1+ttzLowMAccHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttz_lowM_extr_htl") && SystUtils::kDown==getUncDir() && lowHTregion) {_weight *= 1-ttzLowMAccHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttz_lowM_extr_hth") && SystUtils::kUp==getUncDir() && !lowHTregion) {_weight *= 1+ttzLowMAccHthUnc;}
        if((isInUncProc() &&  getUncName()=="ttz_lowM_extr_hth") && SystUtils::kDown==getUncDir() && !lowHTregion) {_weight *= 1-ttzLowMAccHthUnc;}
        	
    }
    if( _sampleName.find("TTW") != string::npos  ){
        //pdf uncertanty
        if((isInUncProc() &&  getUncName()=="ttw_pdf") && SystUtils::kUp   == getUncDir() ){_weight *= 1+ttwPdfUnc;}
	    if((isInUncProc() &&  getUncName()=="ttw_pdf") && SystUtils::kDown == getUncDir() ){_weight *= 1-ttwPdfUnc;}
	     //x-section uncertanty
        if((isInUncProc() &&  getUncName()=="TTW") && SystUtils::kUp   == getUncDir() ){_weight *= 1+ttwXSUnc;}
	    if((isInUncProc() &&  getUncName()=="TTW") && SystUtils::kDown == getUncDir() ){_weight *= 1-ttwXSUnc;}
        //acceptance
        if((isInUncProc() &&  getUncName()=="ttw_extr_htl") && SystUtils::kUp==getUncDir() && lowHTregion) {_weight *= 1+ttwAccHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttw_extr_htl") && SystUtils::kDown==getUncDir() && lowHTregion) {_weight *= 1-ttwAccHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttw_extr_hth") && SystUtils::kUp==getUncDir() && !lowHTregion) {_weight *= 1+ttwAccHthUnc;}
        if((isInUncProc() &&  getUncName()=="ttw_extr_hth") && SystUtils::kDown==getUncDir() && !lowHTregion) {_weight *= 1-ttwAccHthUnc;}
        //LO vs NLO 
        if((isInUncProc() &&  getUncName()=="ttwLO") && SystUtils::kUp==getUncDir() && _HT < 400) {_weight *= 1+ttwNloLoHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttwLO") && SystUtils::kDown==getUncDir() && _HT < 400) {_weight *= 1-ttwNloLoHtlUnc;}
        if((isInUncProc() &&  getUncName()=="ttwLO") && SystUtils::kUp==getUncDir() && _HT > 400 && _HT < 600) {_weight *= 1+ttwNloLoHtmUnc;}
        if((isInUncProc() &&  getUncName()=="ttwLO") && SystUtils::kDown==getUncDir() && _HT > 400 && _HT < 600) {_weight *= 1-ttwNloLoHtmUnc;}
        if((isInUncProc() &&  getUncName()=="ttwLO") && SystUtils::kUp==getUncDir() && _HT > 600) {_weight *= 1+ttwNloLoHthUnc;}
        if((isInUncProc() &&  getUncName()=="ttwLO") && SystUtils::kDown==getUncDir() && _HT > 600) {_weight *= 1-ttwNloLoHthUnc;}
   
    }

    //Fake background
    if(_vc->get("isData") == 1 && _tightLepsPtCutMllCut.size() < 3){
        //normalization
        if((isInUncProc() &&  getUncName()=="fakes") && SystUtils::kUp   == getUncDir() ){_weight *= 1+fakeUnc;}
	    if((isInUncProc() &&  getUncName()=="fakes") && SystUtils::kDown == getUncDir() ){_weight *= 1-fakeUnc;}
    }

}
