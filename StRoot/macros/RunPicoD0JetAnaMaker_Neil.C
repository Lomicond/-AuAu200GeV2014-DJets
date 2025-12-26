#ifndef __CINT__
#include "TString.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <cstdio>
#include <string>
#include <TROOT.h>
#include <TSystem.h>
#include "TChain.h"
#include "StChain/StMaker.h"
#include "StChain/StChain.h"
#include "StPicoEvent/StPicoMcVertex.h"
#include "StRefMultCorr/CentralityMaker.h"
#include "StRefMultCorr/StRefMultCorr.h"
#include "StPicoD0JetAnaMaker/StPicoD0JetAnaMaker.h"
#include "St_db_Maker/St_db_Maker.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StarClassLibrary/phys_constants.h"
using namespace std;

#else
class StChain;
#endif
class StJetFrameworkPicoBase;

StChain *chain;


void loadSharedLibraries();
void loadSharedAnalysisLibraries();
void progres(double N, double D);

void RunPicoD0JetAnaMaker_Neil(string pico="testPico.list",
 string outFileName="Test_AnaMaker.root"/*, string badRunListFileName = "picoList_bad_MB.list"*/,int pYear = 2014, bool Testing = true)
{
   //Check STAR Library. Please set SL_version to the original star library used in the production from http://www.star.bnl.gov/devcgi/dbProdOptionRetrv.pl
   string SL_version;
   string RefMult = "grefmult";
   string Runcode;
   string prodID;
   if (pYear==2016){
      SL_version = "SL20c";
      Runcode = "Run16_AuAu200_VpdMB5";
      prodID = "P16ij";
   } else if (pYear==2014){
      SL_version = "SL22c";
      Runcode = "Run14_AuAu200_VpdMB5";
      prodID = "P16id";
   }else {
      cout << "\033[0;31m Not valid year.\033[0m"<<endl;
      exit(0);
   }

   int nEntries = 300000;
   
   

   if(Testing){
   pico=Form("TestLists/testPico_%.d.list",pYear);
   outFileName=Form("Test_AnaMaker_%.d.root",pYear);
   pico="TestLists/Run14_SL22c.list";
   }

   string env_SL = getenv("STAR");
   if (env_SL.find(SL_version) == string::npos)
   {
      cout << "\033[0;31mEnvironment Star Library does not match the requested library: \033[0m" << "\033[0;32m" << SL_version << "\033[0m";
      cout << "\033[0;31m for run: \033[0m" << "\033[0;32m" << pYear << "\033[0m";
      cout << "\033[0;31m in RunPicoTowerTest_short.C. Exiting...\033[0m" << endl;
      exit(1);
   }

   gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
   loadSharedLibraries();
   gSystem->Load("StBTofUtil");
   gSystem->Load("StPicoPrescales");
   gROOT->LoadMacro("StRoot/macros/loadSharedAnalysisLibrariesJet.C");
   loadSharedAnalysisLibraries();
   chain = new StChain();

//////
    // create base class maker pointer
    /*
    StJetFrameworkPicoBase *baseMaker = new StJetFrameworkPicoBase("baseClassMaker");
    baseMaker->SetRunFlag(StJetFrameworkPicoBase::Run14_AuAu200_MB);                  // run flag (year)
    baseMaker->SetRejectBadRuns(kFALSE);             // switch to load and than omit bad runs
    baseMaker->SetBadRunListVers(StJetFrameworkPicoBase::fBadRuns_w_missing_HT);          // switch to select specific bad run version file
    baseMaker->SetBadTowerListVers(9990200);
    baseMaker->SetUsePrimaryTracks(kFALSE);       // use primary tracks
    //cout<<baseMaker->GetName()<<endl;  // print name of class instance
*/
//////
   StRefMultCorr* grefmultCorrUtil = new StRefMultCorr(RefMult, Runcode, prodID);
   //StRefMultCorr* grefmultCorrUtil = new StRefMultCorr("grefmult_P16id");
   //::kgrefmult_P16id
   
   StPicoDstMaker* picoDstMaker = new StPicoDstMaker(StPicoDstMaker::IoRead, pico.c_str(), "picoDstMaker");

   StMessMgr *msg = StMessMgr::Instance();
   msg->SwitchOff("Could not make BEMC detector");
   St_db_Maker *dbMaker = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb","StarDb");

   StEmcADCtoEMaker *adc = new StEmcADCtoEMaker();
   StPicoD0JetAnaMaker*  picoD0JetAnaMaker = new StPicoD0JetAnaMaker("picoD0JetAnaMaker", outFileName.c_str(), picoDstMaker,grefmultCorrUtil,pYear);

   // -------------- Run cuts ---------------------------
   /**/picoD0JetAnaMaker->setFRunBadlist(1); //0 - 2014 Hanseul's //1 - 2014 Neil's //StCuts.cxx //CHANGE

   // -------------- Event cuts -------------------------
   picoD0JetAnaMaker->setFEventCut_vZ(6); //=< abs(v_z) [cm]
   picoD0JetAnaMaker->setFEventCut_vR(2); //=< sqrt(v_x^2 + v_y^2)[cm]
   picoD0JetAnaMaker->setFEventCut_vZVpdVZ(3); // =< abs(v_z^{VPD} - v_z) [cm]
   //V_x!=0 && v_y!=0 && v_z!=0 //Hardcoded
   std::set<int>* triggers = new std::set<int>(); //Triggers 2014
	triggers->insert(450005);
	triggers->insert(450015);
	triggers->insert(450025);
	triggers->insert(450050);
	triggers->insert(450060);
   picoD0JetAnaMaker->setFEventCut_triggers(*triggers);
   
   // ---------------Daughter D0 cuts-------------------
   picoD0JetAnaMaker->setFDaughterTrackEta(1); // abs(eta) <
   picoD0JetAnaMaker->setFDaughterTrackMinPT(0.6); // > [GeV/c]
   picoD0JetAnaMaker->setFDaughterTrackNHitsFit(20); // >=
   picoD0JetAnaMaker->setFDaughterTrackHftRequired(true); //PXL 1 && PXL 2 && (IST || SSD) 
     
   //Pions
   picoD0JetAnaMaker->setFPionTpcNSigma(3.0); //nsigma
   picoD0JetAnaMaker->setFPionTofBetaDiff(0.03); //abs(1/beta - 1/beta_{exp}) <
   
   //Kaons
   picoD0JetAnaMaker->setFKaonTpcNSigma(2.0); //nsigma
   picoD0JetAnaMaker->setFKaonTofBetaDiff(0.03); //abs(1/beta - 1/beta_{exp}) <
   
   //Rest in StCuts.cxx   
   
   // ---------------D0 cuts-----------------------------
   picoD0JetAnaMaker->setD0PTRange(0,10); // <= p_{T}^{D^0} [GeV/c] <=
   picoD0JetAnaMaker->setD0MassRange(1.7,2.1); // <= m^{D^0} [GeV/c^2] <=
   picoD0JetAnaMaker->setD0Eta(false, 1); //true = used eta cut: abs(eta) <; false = not used
   /**/picoD0JetAnaMaker->setD0Mass(true, 0.13957); // true = input is used; false = reconstructed mass used for energy calc //CHANGE

   // ---------------Jet cuts----------------------------
   //Charged tracks
   picoD0JetAnaMaker->setChargedTracksPTRange(0.2,30.0); // < p_{T} [GeV/c] <
   picoD0JetAnaMaker->setChargedTracksEta(1.); // abs(eta) <
   picoD0JetAnaMaker->setChargedTracksNHitsFit(15); // nHitsFit >= 
   picoD0JetAnaMaker->setChargedTracksNHitsRatio(0.52); // nHitsFit/nHitsMax >=
   picoD0JetAnaMaker->setChargedTracksDCA(3.0); // abs(DCA) < [cm]
   picoD0JetAnaMaker->setChargedTracksMass(0.13957); //pion+ 0.13957 [GeV/c^2]
   
   //Tower inputs
   picoD0JetAnaMaker->setOnlyTrackBasedJets(false); //Trackbased = D0 + charged tracks
   /**/picoD0JetAnaMaker->setTowerCalibrEnergy(false); //true = Hanseul's energy calibration; false = production calibration (bad for 14) //CHANGE
   /**/picoD0JetAnaMaker->setTowerBadList(1); //0 - 2014 Hanseul's //1 - 2014 Neil's //JetInfo.h //CHANGE
   picoD0JetAnaMaker->setTowerETRange(0.2,30); // < E_T [GeV] <=
   /**/picoD0JetAnaMaker->setTowerMass(0.13957); // gamma [GeV/c^2] //CHANGE
   
   //Hadronic correction
   picoD0JetAnaMaker->setHadronCorr(1.); // 1. = 100%
   picoD0JetAnaMaker->setMinPtHadronCorr(0.2); // p_{T} >= [GeV/c]; maximum not set
   picoD0JetAnaMaker->setNHitsFitHadronCorr(15); // nHitsFit >= 
   picoD0JetAnaMaker->setNHitsRatioHadronCorr(0.52); // nHitsFit/nHitsMax >=
   /**/picoD0JetAnaMaker->setMaxDcaZHadronCorr(false, 3.0); // true = dca_z, false = dca; <= [cm] //CHANGE
   picoD0JetAnaMaker->setMassHadronCorr(0.13957); //pion+ 0.13957 [GeV/c^2]
   
   //Jets
   Double_t jetRadius = 0.4;
   picoD0JetAnaMaker->setJetRadius(jetRadius); // Jet resolution parameter
   picoD0JetAnaMaker->setJetEta(false, 1.0 - jetRadius); // false = not used; abs(eta) <= //Postponed to later analysis
   picoD0JetAnaMaker->setJetMaxNeutralPtFrac(false, 0.95); // false = not used; abs(eta) <= //Postponed to later analysis
   
   //Fastjet
   /**/picoD0JetAnaMaker->setJetFixedSeed(true, 12345); // false = random seed, true = second parameter is the seed //Change
   
   //Background calculation
   picoD0JetAnaMaker->setJetBgSubtraction(true, 2); // true = bg subtraction; method: 0 - Area based, 1 - ICS, 2 - jet shape
   /**/picoD0JetAnaMaker->setJetNHardestSkipped(2, 2); // First: 0-10%; Second: 10-80% //CHANGE
   picoD0JetAnaMaker->setJetBgPhiModulation(false);

   //???
   picoD0JetAnaMaker->setGhostMaxrap(1.0);


   chain->Init();
  
   if(!Testing) nEntries = picoDstMaker->chain()->GetEntries();  
   else if (nEntries>picoDstMaker->chain()->GetEntries()) nEntries = picoDstMaker->chain()->GetEntries();

   cout << "nEntries: " << nEntries << endl;
   //--------------------------------------------------------   
   for (int iEvent = 0; iEvent < nEntries; ++iEvent)
   {
      chain->Clear();
      int iret = chain->Make();
      if(Testing && iEvent%200==0) progres(iEvent,nEntries);
      if (iret)
      {
         cout << "Bad return code!" << iret << endl;
         break;
      }
   }
   if(Testing &&nEntries%200!=0) progres(nEntries,nEntries);
   //--------------------------------------------------------

   chain->Finish();
   delete chain;


}
void progres(double citatel, double jmenovatel){
      int Ndilky=50;
      int proc=floor(citatel/jmenovatel*Ndilky);
      
      cout << "\r"<< flush;
      cout << "  │" << flush;
      for (int i=1; i<=proc; i++){
      cout <<"█"<<flush; 
      }
      for (int j=proc+1; j<=Ndilky;j++){
      cout <<  "░"<<flush;
      }
      cout << "│ " << flush;
      if(citatel!=jmenovatel){
         cout << Form("Completed: %.2f",citatel/jmenovatel*100.)<<"% "<<flush;
      }
               
      else{
         cout << Form("\033[1;32m Completed: %.2f \033[0m",citatel/jmenovatel*100.)<<"\033[1;32m%\033[0m"<<endl;
      }
      return;
    }
