#ifndef StPicoD0JetAnaMaker_h
#define StPicoD0JetAnaMaker_h

/***********************************************************************************
 **
 ** Taken from D0CorrelationV2Analyser Author: Leon He
 ** Modified by: Ondrej Lomicky
 **
 ************************************************************************************
 **
 ** Description: 
 **
 ************************************************************************************
 **s
 ** Log:
 **
 ********************************************
 *  A Maker to read a StPicoEvent and StPicoD0Event
 *  simultaneously and do analysis. 
 *
 *  Please write your analysis in the ::Make() function.
 *
 *  Authors:  Xin Dong        (xdong@lbl.gov)
 *            Michael Lomnitz (mrlomnitz@lbl.gov)
 *            Mustafa Mustafa (mmustafa@lbl.gov)
 *            Jochen Thaeder  (jmthader@lbl.gov)   
 *
 * **************************************************
 */
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "TChain.h"
#include "StMaker.h"
//
#include "StThreeVectorF.hh"
#include "TSpectrum.h"
#include "Math/Functor.h"
#include "Math/GSLMinimizer1D.h"
#include "TCanvas.h"
#include "TH1K.h"
#include "TH1D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TProfile.h"
#include "StiMaker/StKFVerticesCollection.h"
#include "StPhysicalHelixD.hh"
#include "TLorentzVector.h"
#include <set>
#include "phys_constants.h"
////#include "StJetFrameworkPicoBase.h"
//#ifdef FASTJET_VERSION

#ifndef __CINT__
namespace fastjet { 
	class PseudoJet; 
	class ClusterSequenceArea;
}
#endif


class StPrimaryVertex; 
class StEvent;
class StDcaGeometry; 

class TString;
class TFile;
class StPicoEvent;
class StKaonPion;
class StPicoDstMaker;
class StPicoDst;
class StPicoTrack;
class StRefMultCorr;
class StEmcADCtoEMaker;
class StBemcTables;



class StPicoD0JetAnaMaker : public StMaker
{
  private:

    TString mOutFileName;
    TFile* mOutputFile;
    StRefMultCorr* mGRefMultCorrUtil;
    StPicoDstMaker* mPicoDstMaker;
    Int_t mYear;
    StPicoDst *picoDst;

  public:
    StPicoD0JetAnaMaker(
            char const * name,
            char const * outName,
            StPicoDstMaker* picoDstMaker,
            StRefMultCorr* grefmultCorrUtil,
            Int_t pYear
    );
    virtual ~StPicoD0JetAnaMaker();

    virtual Int_t Init();
    virtual Int_t Make();
    virtual Int_t Finish();

    void setMaxDcaZHadronCorr(Bool_t tmpSetDcaZHadronCorr, Double_t tmpDcaZHadronCorr);
    void setMinPtHadronCorr(Float_t tmpMinPtHadronCorr);
    void setMassHadronCorr(Float_t tmpMassHadronCorr);
    void setNHitsFitHadronCorr(Float_t tmpNHitsFitHadronCorr);
    void setNHitsRatioHadronCorr(Float_t tmpNHitsRatioHadronCorr);
    
    
    Int_t getEntries() const;
    void setHadronCorr(Float_t corr);
    void setJetBgSubtraction(Bool_t tmpSetJetBgSub, Int_t tmpJetBgSubMethod);
    void setJetFixedSeed(Bool_t tmpSetJetFixedSeed, Int_t tmpJetFJSeed);
    void setOnlyTrackBasedJets(Bool_t OTBJets);
    void setTowerBadList(Int_t tmpTowerBadlist);
    void setTowerETRange(Float_t tmpTowerETMin, Float_t tmpTowerETMax);
    void setTowerMass(Float_t tmpTowerMass);
    void setTowerCalibrEnergy(Bool_t tmpSetTowerCalibrEnergy);
    void setFEventCut_vR(Double_t tmpVR);
    void setFEventCut_vZ(Double_t tmpVZ);
    void setFEventCut_vZVpdVZ(Double_t tmpVZVpdVZ);
    void setFDaughterTrackEta(Double_t tmpDaughterTrackEta);
    void setFDaughterTrackMinPT(Double_t tmpDaughterTrackMinPT);
    void setFDaughterTrackNHitsFit(Double_t tmpDaughterTrackNHitsFit);    
    void setFDaughterTrackHftRequired(Bool_t tmpDaughterTrackHftRequired);
    void setFRunBadlist(Int_t tmpRunBadlist);
    void setFEventCut_triggers(const std::set<Int_t>& tmpEventTriggers);
    void setFPionTpcNSigma(Double_t tmpPionTpcNSigma);
    void setFPionTofBetaDiff(Double_t tmpPionTofBetaDiff);
    void setFKaonTpcNSigma(Double_t tmpKaonTpcNSigma);
    void setFKaonTofBetaDiff(Double_t tmpKaonTofBetaDiff);    
    void setD0PTRange(Double_t tmpD0PTMin, Double_t tmpD0PTMax);
    void setD0MassRange(Double_t tmpD0MassMin, Double_t tmpD0MassMax);
    void setD0Eta(Bool_t tmpUseD0Eta, Double_t tmpD0Eta);
    void setJetRadius(Float_t tmpJetRadius);
    void setChargedTracksPTRange(Float_t tmpChargedTracksPTMin, Float_t tmpChargedTracksPTMax);
    void setChargedTracksEta(Float_t tmpChargedTracksEta);
    void setChargedTracksNHitsFit(Float_t tmpChargedTracksNHitsFit);
    void setChargedTracksNHitsRatio(Float_t tmpChargedTracksNHitsRatio);
    void setChargedTracksDCA(Float_t tmpChargedTracksDCA);
    void setChargedTracksMass(Float_t tmpChargedTracksMass);
    void setD0Mass(Bool_t tmpUseD0Mass, Double_t tmpD0Mass);
    void setGhostMaxrap(Float_t fGhostMaxrap);
    void setJetEta(Bool_t tmpSetJetEta, Double_t tmpJetEta);
    void setJetMaxNeutralPtFrac(Bool_t tmpSetJetMaxNeutralPtFrac, Double_t tmpJetMaxNeutralPtFrac);
    void setJetNHardestSkipped(Int_t tmpJetNHardestSkipped_010, Int_t tmpJetNHardestSkipped_1080);
    void setJetBgPhiModulation(Bool_t tmpSetPhiModulation);
  void CalculateEventPlane();
    Int_t EP_IsGoodTrack(StPicoTrack *trk, TVector3 pVertex);
    virtual Bool_t GetCaloTrackMomentum(StPicoDst *mPicoDst, TVector3 mPrimVtx, Int_t pionDaugId, Int_t kaonDaugId);
    virtual Double_t GetTowerCalibEnergy(Int_t TowerId);
    virtual Double_t vertexCorrectedEta(Double_t eta, Double_t vz);

    StEmcADCtoEMaker *mADCtoEMaker;
    StBemcTables     *mTables;

  private:

    StPicoD0JetAnaMaker() {}
    void readNextEvent();
    Int_t isD0PairCentrality_pt(StKaonPion const & kp, Int_t Centrality, Int_t mYear) const;
    Bool_t isGoodEvent(Int_t mYear, TH1D* hEventsCuts);
    Bool_t isMBTrigger(Int_t mYear);
    Bool_t isGoodTrack(StPicoTrack const*) const;
    Bool_t isGoodJetTrack(StPicoTrack const*,StPicoEvent const*) const; //my
    Bool_t isTpcPion(StPicoTrack const*) const;
    Bool_t isTpcKaon(StPicoTrack const*) const;
    Bool_t isTofKaon(StPicoTrack const* const, Float_t beta) const;
    Bool_t isTofPion(StPicoTrack const* const, Float_t beta) const;
    Float_t getTofBeta(StPicoTrack const*,StThreeVectorF const * pVtx,StPicoDst const* const picoDst) const;
    Bool_t IsBadEnergyRun(Int_t);
    #ifndef __CINT__
    std::vector<fastjet::PseudoJet> JetReconstructionICS(std::vector<fastjet::PseudoJet> fInputVectors, Int_t fCentrality, Double_t fR, Bool_t fBackSub, Double_t fEP_psi2, Int_t difiter);
    std::vector<fastjet::PseudoJet> JetReconstructionShape(std::vector<fastjet::PseudoJet> fInputVectors, Int_t fCentrality, Double_t fR, Bool_t fBackSub, Double_t fEP_psi2, Int_t difiter);
    fastjet::ClusterSequenceArea* fClustSeq = nullptr;
    #endif
    Float_t fGhostMaxrap;
    Int_t nJetsRemove;
    Float_t maxneutralfrac;
    Float_t fETMin;
    Float_t fETMax;
    Float_t fHadronCorr;
    Float_t fOnlyTrackBasedJets;
    Float_t maxdcazhadroncorr;
    const Double_t mBarrelRadius = 225.405;

TTree* Jets;
//StRefMultCorr* grefmultCorr;

///CHANGE!!!!
/*
    StJetFrameworkPicoBase *mBaseMaker;
        // bad and dead tower list
    std::set<Int_t>        badTowers;
    std::set<Int_t>        deadTowers;

    // bad run list
    std::set<Int_t>        badRuns;
    */
///CHANGE!!!!
//Event
Int_t runId;
Int_t eventId;
Int_t centrality;
Float_t weightCentrality;
Int_t gRefMult;
Float_t backgroundDensity;
Float_t backgroundDensityM;
Float_t psi2;
Float_t fAngul10half;
Float_t	fAngul11;
Float_t	fAngul11half;
Float_t	fAngul12;
Float_t	fAngul13;
Float_t	fAngulDisp;

//D0 meson
Int_t d0PdgSign;
Float_t d0Mass;
Float_t d0Pt;
Float_t d0Rapidity;
Float_t d0Eta;
Float_t d0Phi;

//Jet obsevables
Float_t jetEta;
Float_t jetPhi;
Float_t jetRapidity;
Float_t jetArea;
Float_t jetPt; 
Float_t lambda1_0_5;
Float_t lambda1_1;
Float_t lambda1_1_5;
Float_t lambda1_2;
Float_t lambda1_3;
Float_t momDisp;
Float_t z;
Int_t nJetConst;
Int_t nJetsInEvent;
Float_t jetD0DeltaR;
Float_t jetNeutralPtFrac;
Float_t jetTrackPtSum;

// Event histograms:
TH1D* hVtxZ;
TH2D* hVtxR;
TH1D* hVzDiff;
TH1D* hCentrality;
TH1D* hCentralityW;
TH1D* hEventsCuts;

// D0 histograms:
TH2D* hD0MassPtUnlike;
TH2D* hD0MassPtLike;
TH1D* hD0EtaUnlike;
TH1D* hD0EtaLike;
TH2D* hPionEtaVsPt;
TH2D* hKaonEtaVsPt;
TH2D* hNKaonsVsNPions;

// Topological cuts:
TH2D* hKaonDcaVsPtD0;
TH2D* hPionDcaVsPtD0;
TH2D* hDcaDaughtersVsPt;
TH2D* hD0DcaVsPt;
TH2D* hCosThetaVsPt;
TH2D* hD0DecayLengthVsPt;

// Daughter PID:
TH2D* hTofBetaDiffKaonVsPt;
TH2D* hTofBetaDiffPionVsPt;
TH2D* hBetaVsSPKaon;
TH2D* hBetaVsSPPion;
TH2D* hTpcNsigmaKaonVsPt;
TH2D* hTpcNsigmaPionVsPt;
TH2D* hDedxVsSPKaon;
TH2D* hDedxVsSPPion;
TH2D* hNHitsFitKaonVsD0Pt;
TH2D* hNHitsFitPionVsD0Pt;

//Jet constituents:
TH2D* hJetTracksDedx;
TH2D* hJetTracksDedxAfterCuts;
TH1D* hJetTracksPt;
TH2D* hJetTracksEtaPhi;
TH1D* hJetTracksNHitsFit;
TH1D* hJetTracksNHitsRatio;
TH1D* hJetTracksDCA;
TH1D* hJetNeutralPt;
TH2D* hJetNeutralEtaPhi;
TH2D* hJetNeutralEtBefAftHC;
TH2D* hJetNeutralECalibBefAft;
TH1D* hJetConstCharge;
TH2D* hJetConstRapPhi;
TH2D* hJetConstRapPhiICS;
TH2D* hJetConstEtaPhi;
TH2D* hJetConstEtaPhiICS;

//Neutral particles hadronic correction:
TH1D* hJetHadrCorrNHitsFit;
TH1D* hJetHadrCorrNHitsRatio;
TH1D* hJetHadrCorrDcaZ;
TH2D* hJetHadrCorrEtaVsPt;
TH1D* hJetHadrCorrE;



//Event plane calculation
Double_t fPsi_2;
Double_t fPsi_2_shifted;
Double_t fQ_1;
Double_t fQ_2;
Double_t fQ_1_rec;
Double_t fQ_2_rec;

//Run
Int_t fRunBadlist = 0;

//Event
Double_t fEventCut_vZ = 6; //cm
Double_t fEventCut_vR = 2; //cm
Double_t fEventCut_vZVpdVZ = 3; //cm
std::set<Int_t> fEventTriggers; 

//Pion
Double_t fPionTpcNSigma = 3; //nsigma
Double_t fPionTofBetaDiff = 0.03;

//Kaon
Double_t fKaonTpcNSigma = 2; //nsigma
Double_t fKaonTofBetaDiff = 0.03; 

//Daughter tracks
Double_t fDaughterTrackEta = 1;
Double_t fDaughterTrackMinPT = 1;
Double_t fDaughterTrackNHitsFit = 20;
Bool_t fDaughterTrackHftRequired = true;

//D0 cuts
Double_t fD0PTMin = 0;
Double_t fD0PTMax = 10;
Double_t fD0MassMin = 1.7;
Double_t fD0MassMax = 2.1;

Bool_t fUseD0Eta = false;
Double_t fD0Eta = 1.0;
Bool_t fSetD0Mass = false;
Double_t fD0RecoMass = 1.86484;

//Jet parameters
Double_t fJetRadius = 0.4;

//Charged tracks
Double_t fChargedTracksPTMin = 0.2;
Double_t fChargedTracksPTMax = 30.0;
Double_t fChargedTracksEta = 1;
Double_t fChargedTracksNHitsFit = 15.;
Double_t fChargedTracksNHitsRatio = 0.52;
Double_t fChargedTracksDCA = 3.;
Double_t fChargedTracksMass = M_PION_PLUS;

//Towers
Int_t fTowerBadlist = 0;
Double_t fTowerETMin = 0.2;
Double_t fTowerETMax = 30.0;
Double_t fTowerMass = 0.;
Bool_t fSetTowerCalibrEnergy = true;

//Hadronic correction
Double_t fMinPtHadronCorr = 0.2;
Bool_t fSetDcaZHadronCorr = true;
Double_t fDcaZHadronCorr = 3.0;
Double_t fMassHadronCorr = M_PION_PLUS;
Double_t fNHitsFitHadronCorr = 15;
Double_t fNHitsRatioHadronCorr = 0.52;

//Jets
Bool_t fSetJetEta = false;
Double_t fJetEta = 1. - 0.4;
Bool_t fSetJetMaxNeutralPtFrac = false;
Double_t fJetMaxNeutralPtFrac = 0.95;

Bool_t fSetJetBgSub = true;
Int_t fJetBgSubMethod = 2;
Int_t fJetNHardestSkipped_010 = 2;
Int_t fJetNHardestSkipped_1080 = 1; 
Bool_t fSetJetFixedSeed = false;
Int_t fJetFJSeed = 12345;

Float_t fPhiModulation = false;

ClassDef(StPicoD0JetAnaMaker, 1)

};

inline void StPicoD0JetAnaMaker::setFRunBadlist(Int_t tmpRunBadlist){
    fRunBadlist = tmpRunBadlist;
    //0 - Hanseul's //1 - Neil's
}

inline void StPicoD0JetAnaMaker::setFEventCut_vZ(Double_t tmpVZ){
    fEventCut_vZ = tmpVZ;
}
inline void StPicoD0JetAnaMaker::setFEventCut_vR(Double_t tmpVR){
    fEventCut_vR = tmpVR;
}
inline void StPicoD0JetAnaMaker::setFEventCut_vZVpdVZ(Double_t tmpVZVpdVZ){
    fEventCut_vZVpdVZ = tmpVZVpdVZ;
}
inline void StPicoD0JetAnaMaker::setFEventCut_triggers(const std::set<Int_t>& tmpEventTriggers){
 fEventTriggers = tmpEventTriggers;
}

//Daughter cuts
inline void StPicoD0JetAnaMaker::setFDaughterTrackEta(Double_t tmpDaughterTrackEta){
    fDaughterTrackEta = tmpDaughterTrackEta;
}

inline void StPicoD0JetAnaMaker::setFDaughterTrackMinPT(Double_t tmpDaughterTrackMinPT){
    fDaughterTrackMinPT = tmpDaughterTrackMinPT;
}

inline void StPicoD0JetAnaMaker::setFDaughterTrackNHitsFit(Double_t tmpDaughterTrackNHitsFit){
    fDaughterTrackNHitsFit = tmpDaughterTrackNHitsFit;
}

inline void StPicoD0JetAnaMaker::setFDaughterTrackHftRequired(Bool_t tmpDaughterTrackHftRequired){
    fDaughterTrackHftRequired = tmpDaughterTrackHftRequired;
}
    
inline void StPicoD0JetAnaMaker::setFPionTpcNSigma(Double_t tmpPionTpcNSigma){
    fPionTpcNSigma = tmpPionTpcNSigma;
}

inline void StPicoD0JetAnaMaker::setFPionTofBetaDiff(Double_t tmpPionTofBetaDiff){
    fPionTofBetaDiff = tmpPionTofBetaDiff;
}

inline void StPicoD0JetAnaMaker::setFKaonTpcNSigma(Double_t tmpKaonTpcNSigma){
    fKaonTpcNSigma = tmpKaonTpcNSigma;
}

inline void StPicoD0JetAnaMaker::setFKaonTofBetaDiff(Double_t tmpKaonTofBetaDiff){
    fKaonTofBetaDiff = tmpKaonTofBetaDiff;
}

inline void StPicoD0JetAnaMaker::setD0PTRange(Double_t tmpD0PTMin, Double_t tmpD0PTMax){
    fD0PTMin = tmpD0PTMin;
    fD0PTMax = tmpD0PTMax;
}

inline void StPicoD0JetAnaMaker::setD0MassRange(Double_t tmpD0MassMin, Double_t tmpD0MassMax){
    fD0MassMin = tmpD0MassMin;
    fD0MassMax = tmpD0MassMax;
}

inline void StPicoD0JetAnaMaker::setD0Mass(Bool_t tmpUseD0Mass, Double_t tmpD0Mass){
    fSetD0Mass = tmpUseD0Mass;
    fD0RecoMass = tmpD0Mass;
}

inline void StPicoD0JetAnaMaker::setD0Eta(Bool_t tmpUseD0Eta, Double_t tmpD0Eta){
    fUseD0Eta = tmpUseD0Eta;
    fD0Eta = tmpD0Eta;
}


//Jet cuts
inline void StPicoD0JetAnaMaker::setJetRadius(Float_t tmpJetRadius){
    fJetRadius = tmpJetRadius;
}

//Charged tracks
inline void StPicoD0JetAnaMaker::setChargedTracksPTRange(Float_t tmpChargedTracksPTMin, Float_t tmpChargedTracksPTMax){
    fChargedTracksPTMin = tmpChargedTracksPTMin;
    fChargedTracksPTMax = tmpChargedTracksPTMax;
}

inline void StPicoD0JetAnaMaker::setChargedTracksEta(Float_t tmpChargedTracksEta){
    fChargedTracksEta = tmpChargedTracksEta;
}

inline void StPicoD0JetAnaMaker::setChargedTracksNHitsFit(Float_t tmpChargedTracksNHitsFit){
    fChargedTracksNHitsFit = tmpChargedTracksNHitsFit;
}

inline void StPicoD0JetAnaMaker::setChargedTracksNHitsRatio(Float_t tmpChargedTracksNHitsRatio){
    fChargedTracksNHitsRatio = tmpChargedTracksNHitsRatio;
}

inline void StPicoD0JetAnaMaker::setChargedTracksDCA(Float_t tmpChargedTracksDCA){
    fChargedTracksDCA = tmpChargedTracksDCA;
}

inline void StPicoD0JetAnaMaker::setChargedTracksMass(Float_t tmpChargedTracksMass){
    fChargedTracksMass = tmpChargedTracksMass;
}


inline void StPicoD0JetAnaMaker::setTowerBadList(Int_t tmpTowerBadlist){
    fTowerBadlist = tmpTowerBadlist;
    //0 - Hanseul's //1 - Neil's
}

inline void StPicoD0JetAnaMaker::setTowerETRange(Float_t tmpTowerETMin, Float_t tmpTowerETMax){
    fTowerETMin = tmpTowerETMin;
    fTowerETMax = tmpTowerETMax;
}

inline void StPicoD0JetAnaMaker::setTowerMass(Float_t tmpTowerMass){
    fTowerMass = tmpTowerMass;
}

inline void StPicoD0JetAnaMaker::setTowerCalibrEnergy(Bool_t tmpSetTowerCalibrEnergy){
    fSetTowerCalibrEnergy = tmpSetTowerCalibrEnergy;
}

inline void StPicoD0JetAnaMaker::setMaxDcaZHadronCorr(Bool_t tmpSetDcaZHadronCorr, Double_t tmpDcaZHadronCorr){
    fSetDcaZHadronCorr = tmpSetDcaZHadronCorr;
    fDcaZHadronCorr = tmpDcaZHadronCorr;
}

inline void StPicoD0JetAnaMaker::setMinPtHadronCorr(Float_t tmpMinPtHadronCorr) {
    fMinPtHadronCorr = tmpMinPtHadronCorr;
}

inline void StPicoD0JetAnaMaker::setMassHadronCorr(Float_t tmpMassHadronCorr) {
    fMassHadronCorr = tmpMassHadronCorr;
}

inline void StPicoD0JetAnaMaker::setNHitsFitHadronCorr(Float_t tmpNHitsFitHadronCorr){
    fNHitsFitHadronCorr = tmpNHitsFitHadronCorr;
}

inline void StPicoD0JetAnaMaker::setNHitsRatioHadronCorr(Float_t tmpNHitsRatioHadronCorr){
    fNHitsRatioHadronCorr = tmpNHitsRatioHadronCorr;
}


inline void StPicoD0JetAnaMaker::setGhostMaxrap(Float_t fGhostMaxrap) {
    StPicoD0JetAnaMaker::fGhostMaxrap = fGhostMaxrap;
}

inline void StPicoD0JetAnaMaker::setJetNHardestSkipped(Int_t tmpJetNHardestSkipped_010, Int_t tmpJetNHardestSkipped_1080) {
    fJetNHardestSkipped_010 = tmpJetNHardestSkipped_010;
    fJetNHardestSkipped_1080 = tmpJetNHardestSkipped_1080;
}

inline void StPicoD0JetAnaMaker::setJetEta(Bool_t tmpSetJetEta, Double_t tmpJetEta){
    fSetJetEta = tmpSetJetEta;
    fJetEta = tmpJetEta;
}

inline void StPicoD0JetAnaMaker::setJetBgPhiModulation(Bool_t tmpSetPhiModulation){
    fPhiModulation = tmpSetPhiModulation;
}


inline void StPicoD0JetAnaMaker::setJetMaxNeutralPtFrac(Bool_t tmpSetJetMaxNeutralPtFrac, Double_t tmpJetMaxNeutralPtFrac){
    fSetJetMaxNeutralPtFrac = tmpSetJetMaxNeutralPtFrac;
    fJetMaxNeutralPtFrac = tmpJetMaxNeutralPtFrac;
}

inline void StPicoD0JetAnaMaker::setHadronCorr(Float_t corr) {
    fHadronCorr = corr;
}

inline void StPicoD0JetAnaMaker::setJetBgSubtraction(Bool_t tmpSetJetBgSub, Int_t tmpJetBgSubMethod){
  fSetJetBgSub = tmpSetJetBgSub;
  //0 - Area based, 1 - ICS, 2 - jet shape
  fJetBgSubMethod = tmpJetBgSubMethod;
}

inline void StPicoD0JetAnaMaker::setJetFixedSeed(Bool_t tmpSetJetFixedSeed, Int_t tmpJetFJSeed){
  fSetJetFixedSeed = tmpSetJetFixedSeed;
  fJetFJSeed = tmpJetFJSeed;
}


inline void StPicoD0JetAnaMaker::setOnlyTrackBasedJets(Bool_t OTBJets) {
    fOnlyTrackBasedJets = OTBJets;
}

#endif
