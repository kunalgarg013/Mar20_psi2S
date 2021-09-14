/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/*
 *This is a simple task which can serve as a template for tasks based on dimuon
 *analyses.
 *
 */

//-------------------------------------------------------------------------------------------------//
// needed root classes
#include "TMath.h"
#include <TCanvas.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <THnSparse.h>
#include <TH3.h>
#include <TList.h>
#include <TNtuple.h>
#include <TObjArray.h>
#include <TTree.h>
#include <iostream>

//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// needed root classes
#include "AliAODDimuon.h"
#include "AliAODEvent.h"
#include "AliAODHeader.h"
#include "AliAODTrack.h"
#include "AliAODTracklets.h"
#include "AliAODVZERO.h"
#include "AliAODVertex.h"
#include "AliAODv0.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisMuonUtility.h"
#include "AliAnalysisUtils.h"
#include "AliESDEvent.h"
#include "AliESDMuonTrack.h"
#include "AliESDVZERO.h"
#include "AliESDVertex.h"
#include "AliInputEventHandler.h"
#include "AliLog.h"
#include "AliMultSelection.h"
#include "AliMuonTrackCuts.h"
#include "AliOADBMuonTrackCutsParam.h"
#include "AliVEvent.h"
#include "AliVTrack.h"
#include "AliVVZERO.h"
#include "AliVVertex.h"
#include "AliMultSelection.h"
#include "AliVertexingHFUtils.h"

//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// This class header
#include "TaskDimuonPP.h"

//-------------------------------------------------------------------------------------------------//
ClassImp(TaskDimuonPP)
    //-------------------------------------------------------------------------------------------------//
    // Dummy constructor ALWAYS needed for I/O.
    TaskDimuonPP::TaskDimuonPP()
    : AliAnalysisTaskSE(), fListEvent(0x0), fMuonTrackCuts(0), fFirstRun(0),
      fLastRun(1) {}
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// Main custom constructor. Also, define the input and output slots of your
// objects
TaskDimuonPP::TaskDimuonPP(const char *name, int firstRun, int lastRun)
    : AliAnalysisTaskSE(name), fListEvent(0x0), fMuonTrackCuts(0),
      fFirstRun(firstRun), fLastRun(lastRun) {

  // Input slot #0 works with a TChain - it is connected to the default input
  // container
  DefineInput(0, TChain::Class());
  // Output slot #1 writes into a TH1 container
  DefineOutput(1, TObjArray::Class()); // for output objarray
}
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// Destructor. Clean-up the output list, but not the histograms that are put
// inside (the list is owner and will clean-up these histograms). Protect in
// PROOF case.
TaskDimuonPP::~TaskDimuonPP() {
  if (fListEvent && !AliAnalysisManager::GetAnalysisManager()->IsProofMode()) {
    delete fListEvent;
  }
}
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
void TaskDimuonPP::NotifyRun() {
  /// Set run number for the muon track cuts object
  if (fMuonTrackCuts)
    fMuonTrackCuts->SetRun(fInputHandler);
}
//-------------------------------------------------------------------------------------------------//


double TaskDimuonPP::WeightMaps(int runNumber)
{
  std::map<int,double> mymap;
  //LHC15o runList start

  mymap[295584] =   0.999355;
  mymap[295585] =   1.00209;
  mymap[295586] =   1.00018;
  mymap[295587] =   1.00101;
  mymap[295588] =   1.00055;
  mymap[295589] =   1.00067;
  mymap[295610] =   0.998005;
  mymap[295611] =   0.997254;
  mymap[295612] =   0.999851;
  mymap[295615] =   0.999307;
  mymap[295665] =   1.00196;
  mymap[295666] =   0.998681;
  mymap[295667] =   0.999509;
  mymap[295668] =   0.999292;
  mymap[295671] =   1.00139;
  mymap[295673] =   1.00161;
  mymap[295675] =   1.00078;
  mymap[295676] =   1.00029;
  mymap[295677] =   0.999053;
  mymap[295712] =   0.998653;
  mymap[295714] =   0.99894;
  mymap[295716] =   1.00022;
  mymap[295717] =   1.0005;
  mymap[295718] =   1.00085;
  mymap[295719] =   1.00342;
  mymap[295720] =   0.99741;
  mymap[295721] =   0.999014;
  mymap[295723] =   0.999865;
  mymap[295725] =   0.998391;
  mymap[295753] =   1.00023;
  mymap[295754] =   0.999697;
  mymap[295755] =   1.00047;
  mymap[295756] =   1.0007;
  mymap[295758] =   0.999151;
  mymap[295759] =   1.00002;
  mymap[295762] =   0.999289;
  mymap[295763] =   0.999889;
  mymap[295786] =   0.999096;
  mymap[295788] =   1.00032;
  mymap[295791] =   1.00023;
  mymap[295816] =   1.00036;
  mymap[295818] =   1.00483;
  mymap[295819] =   0.99941;
  mymap[295822] =   0.999734;
  mymap[295825] =   0.999783;
  mymap[295826] =   1.00024;
  mymap[295829] =   0.999562;
  mymap[295831] =   0.999351;
  mymap[295853] =   0.999749;
  mymap[295854] =   0.99978;
  mymap[295855] =   0.999267;
  mymap[295856] =   0.99992;
  mymap[295859] =   0.999808;
  mymap[295860] =   1.0004;
  mymap[295861] =   1.00034;
  mymap[295863] =   1.0017;
  mymap[295872] =   1.00175;
  mymap[295881] =   0.17409;
  mymap[295908] =   0.109303;
  mymap[295909] =   0.106392;
  mymap[295910] =   0.103509;
  mymap[295913] =   0.106342;
  mymap[295936] =   0.123445;
  mymap[295937] =   0.121187;
  mymap[295941] =   0.126516;
  mymap[295942] =   0.136361;
  mymap[295943] =   0.147811;
  mymap[295945] =   0.160867;
  mymap[295947] =   0.182286;
  mymap[296016] =   0.114029;
  mymap[296060] =   0.10782;
  mymap[296061] =   0.108488;
  mymap[296062] =   0.112018;
  mymap[296063] =   0.113762;
  mymap[296065] =   0.126852;
  mymap[296066] =   0.13792;
  mymap[296068] =   0.144129;
  mymap[296074] =   0.158111;
  mymap[296123] =   0.10374;
  mymap[296128] =   0.104845;
  mymap[296132] =   0.103151;
  mymap[296133] =   0.103177;
  mymap[296134] =   0.1043;
  mymap[296135] =   0.116539;
  mymap[296142] =   0.15734;
  mymap[296143] =   0.190693;
  mymap[296191] =   0.107545;
  mymap[296192] =   0.104904;
  mymap[296194] =   0.106469;
  mymap[296195] =   0.106168;
  mymap[296196] =   0.116574;
  mymap[296197] =   0.145788;
  mymap[296198] =   0.185303;
  mymap[296240] =   0.126284;
  mymap[296241] =   0.108887;
  mymap[296242] =   0.104757;
  mymap[296243] =   0.10482;
  mymap[296244] =   0.103994;
  mymap[296246] =   0.130636;
  mymap[296247] =   0.159566;
  mymap[296269] =   0.0999659;
  mymap[296270] =   0.100162;
  mymap[296273] =   0.0999937;
  mymap[296275] =   0.132949;
  mymap[296279] =   0.150728;
  mymap[296280] =   0.159069;
  mymap[296303] =   0.0994658;
  mymap[296304] =   0.0998738;
  mymap[296307] =   0.0999282;
  mymap[296309] =   0.129745;
  mymap[296312] =   0.169091;
  mymap[296375] =   0.100782;
  mymap[296376] =   0.0998139;
  mymap[296377] =   0.100338;
  mymap[296378] =   0.0998329;
  mymap[296379] =   0.132067;
  mymap[296380] =   0.16079;
  mymap[296381] =   0.217166;
  mymap[296383] =   0.30296;
  mymap[296414] =   0.0997123;
  mymap[296419] =   0.0996036;
  mymap[296420] =   0.13364;
  mymap[296423] =   0.157626;
  mymap[296424] =   0.186848;
  mymap[296433] =   0.205533;
  mymap[296472] =   0.223886;
  mymap[296509] =   0.0998428;
  mymap[296510] =   0.0999619;
  mymap[296511] =   0.0998016;
  mymap[296512] =   0.0999722;
  mymap[296514] =   0.0995817;
  mymap[296516] =   0.0999409;
  mymap[296547] =   0.100385;
  mymap[296548] =   0.100086;
  mymap[296549] =   0.0997442;
  mymap[296550] =   0.10007;
  mymap[296551] =   0.132875;
  mymap[296552] =   0.162754;
  mymap[296553] =   0.173577;
  mymap[296594] =   0.100508;
  mymap[296615] =   0.0999875;
  mymap[296616] =   0.0997027;
  mymap[296618] =   0.0997704;
  mymap[296619] =   0.0998732;
  mymap[296621] =   0.0996658;
  mymap[296622] =   0.100728;
  mymap[296623] =   0.099893;
  mymap[296690] =   0.0999156;
  mymap[296691] =   0.099844;
  mymap[296693] =   0.100173;
  mymap[296694] =   0.100316;
  mymap[296749] =   0.0998612;
  mymap[296750] =   0.0998046;
  mymap[296752] =   0.999131;
  mymap[296781] =   0.0991945;
  mymap[296784] =   0.10016;
  mymap[296785] =   0.100167;
  mymap[296786] =   0.0983362;
  mymap[296787] =   0.099403;
  mymap[296791] =   0.516389;
  mymap[296793] =   0.100268;
  mymap[296794] =   0.100304;
  mymap[296799] =   0.0998896;
  mymap[296835] =   0.0989553;
  mymap[296836] =   0.0992355;
  mymap[296838] =   0.0994271;
  mymap[296839] =   0.0998814;
  mymap[296848] =   0.100104;
  mymap[296849] =   0.0999525;
  mymap[296850] =   0.0998068;
  mymap[296851] =   0.100142;
  mymap[296852] =   0.100103;
  mymap[296890] =   0.100123;
  mymap[296894] =   0.100003;
  mymap[296899] =   0.0999318;
  mymap[296900] =   0.100127;
  mymap[296903] =   0.100725;
  mymap[296930] =   0.100411;
  mymap[296931] =   0.101319;
  mymap[296932] =   0.0994254;
  mymap[296934] =   0.0999138;
  mymap[296935] =   0.0998935;
  mymap[296938] =   0.0994895;
  mymap[296941] =   0.10023;
  mymap[296966] =   0.100233;
  mymap[296967] =   0.520445;
  mymap[296968] =   0.491768;
  mymap[296969] =   0.210959;
  mymap[296971] =   0.210444;
  mymap[296975] =   0.211519;
  mymap[296976] =   0.230861;
  mymap[296977] =   0.09996;
  mymap[296979] =   0.140353;
  mymap[297029] =   0.100195;
  mymap[297031] =   0.100222;
  mymap[297035] =   0.100624;
  mymap[297085] =   0.100087;
  mymap[297117] =   0.10011;
  mymap[297118] =   0.0998331;
  mymap[297119] =   0.100213;
  mymap[297123] =   0.0999524;
  mymap[297124] =   0.100383;
  mymap[297128] =   0.0995332;
  mymap[297129] =   0.100282;
  mymap[297132] =   0.0999328;
  mymap[297133] =   0.0999187;
  mymap[297193] =   0.100149;
  mymap[297194] =   0.0998722;
  mymap[297195] =   0.099958;
  mymap[297196] =   0.0995314;
  mymap[297218] =   0.0999304;
  mymap[297219] =   0.0999111;
  mymap[297221] =   0.0996967;
  mymap[297222] =   0.0997577;
  mymap[297277] =   0.100639;
  mymap[297278] =   0.100112;
  mymap[297310] =   0.0999433;
  mymap[297311] =   0.0995185;
  mymap[297312] =   0.100164;
  mymap[297315] =   0.100161;
  mymap[297317] =   0.100256;
  mymap[297363] =   0.10002;
  mymap[297366] =   0.0999504;
  mymap[297367] =   0.0998768;
  mymap[297372] =   0.0994421;
  mymap[297379] =   0.0998259;
  mymap[297380] =   0.100107;
  mymap[297403] =   0.0992347;
  mymap[297405] =   0.0995028;
  mymap[297406] =   0.100124;
  mymap[297408] =   0.102947;
  mymap[297413] =   0.0997592;
  mymap[297414] =   0.0999157;
  mymap[297415] =   0.0999731;
  mymap[297441] =   0.0994956;
  mymap[297442] =   0.0998338;
  mymap[297446] =   0.0998022;
  mymap[297450] =   0.0997924;
  mymap[297451] =   0.0996779;
  mymap[297452] =   0.100202;
  mymap[297479] =   0.0998824;
  mymap[297481] =   0.100117;
  mymap[297483] =   0.099964;
  mymap[297512] =   0.0999469;
  mymap[297537] =   0.100403;
  mymap[297540] =   0.100614;
  mymap[297541] =   0.100057;
  mymap[297542] =   0.0998414;
  mymap[297544] =   0.0999133;
  mymap[297557] =   0.100855;
  mymap[297558] =   0.0997634;
  mymap[297588] =   0.10019;
  mymap[297589] =   0.104814;
  mymap[297590] =   0.100299;
  mymap[297595] =   0.0997172;
  mymap[297623] =   0.100525;
  mymap[297624] =   0.0998906;


  return mymap[runNumber];

}





//-------------------------------------------------------------------------------------------------//
// Here you define your histograms and othe robjects and add them to their
// associated list.
void TaskDimuonPP::UserCreateOutputObjects() {

  // Histograms, tree, or THnsparse definitions
  fListEvent = new TObjArray(20);
  fListEvent->SetOwner(kTRUE);
  fListEvent->SetName("ListEvent");


Int_t bins[4] =    {300, 2000,  60, 100};
Double_t xmin[4] = {0.,   0.,  -5.,   0};
Double_t xmax[4] = {30.,  20., -2., 100};
fSparseDimuonOpp = new THnSparseF("fSparseDimuonOpp", "", 4, bins, xmin, xmax);
fSparseDimuonPlus = new THnSparseF("fSparseDimuonPlus", "", 4, bins, xmin, xmax);
fSparseDimuonNeg = new THnSparseF("fSparseDimuonNeg", "", 4, bins, xmin, xmax);


fSparseDimuonOpp->GetAxis(0)->SetBinLabel( 1, "DiMuonPt" );
fSparseDimuonOpp->GetAxis(1)->SetBinLabel( 2, "DiMuonIM" );
fSparseDimuonOpp->GetAxis(2)->SetBinLabel( 3, "DiMuonEta" );
fSparseDimuonOpp->GetAxis(3)->SetBinLabel( 4, "Centrality" );

fSparseDimuonPlus->GetAxis(0)->SetBinLabel( 1, "DiMuonPt" );
fSparseDimuonPlus->GetAxis(1)->SetBinLabel( 2, "DiMuonIM" );
fSparseDimuonPlus->GetAxis(2)->SetBinLabel( 3, "DiMuonEta" );
fSparseDimuonPlus->GetAxis(3)->SetBinLabel( 4, "Centrality" );

fSparseDimuonNeg->GetAxis(0)->SetBinLabel( 1, "DiMuonPt" );
fSparseDimuonNeg->GetAxis(1)->SetBinLabel( 2, "DiMuonIM" );
fSparseDimuonNeg->GetAxis(2)->SetBinLabel( 3, "DiMuonEta" );
fSparseDimuonNeg->GetAxis(3)->SetBinLabel( 4, "Centrality" );




fListEvent->Add(fSparseDimuonOpp);
fListEvent->Add(fSparseDimuonPlus);
fListEvent->Add(fSparseDimuonNeg);



/*==========================================================================================================================*/



  // To make the muon selection easier, this class can be used. Make sure to
  // call ->SetRun() function in the notifyRun() of this task.
  fMuonTrackCuts =
      new AliMuonTrackCuts("StandardMuonTrackCuts", "StandardMuonTrackCuts");
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  // Add the cuts to be used; the nominal values are already set in the
  // AliMuonTrackCuts task itself.
  fMuonTrackCuts->SetFilterMask(
      AliMuonTrackCuts::kMuEta | AliMuonTrackCuts::kMuThetaAbs |
      AliMuonTrackCuts::kMuMatchLpt | AliMuonTrackCuts::kMuPdca);

  PostData(1, fListEvent);
}
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
// Main function
void TaskDimuonPP::UserExec(Option_t *) {

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  // Initialisations and event selections
  AliAODEvent *aod = 0;
  AliAODHeader *aodHeader = NULL;
  Bool_t isSelectedCMULEvent = kFALSE;
  Bool_t isSelectedCMLLEvent = kFALSE;



  TString strFiredTriggers;
  aod = static_cast<AliAODEvent *>(InputEvent());
  if (aod) {
    aodHeader = (AliAODHeader *)aod->GetHeader();
    strFiredTriggers = aod->GetFiredTriggerClasses();
  } else {
    AliError("ERROR: Could not retrieve ESD or AOD event !!");
    return;
  }

   AliMultSelection *multSelection = (AliMultSelection * ) aod->FindListObject("MultSelection");
  Double_t eventCentrality = multSelection->GetMultiplicityPercentile("V0M", false);
  if(eventCentrality > 90) return;

  Int_t runNumber = aod->GetRunNumber();

  double weightCMLL = WeightMaps(runNumber);
  if(weightCMLL>1 || runNumber<290000){weightCMLL = 1;}

  UInt_t IsSelected =
      (((AliInputEventHandler *)(AliAnalysisManager::GetAnalysisManager()
                                     ->GetInputEventHandler()))
           ->IsEventSelected());

  // Make sure that the physics selection key (e.g kMuonUnlikeLowPt7) is valid
  // for the data sample you are analysing
  if (strFiredTriggers.Contains("CMUL7-B-NOPF-MUFAST") &&
      (IsSelected & AliVEvent::kMuonUnlikeLowPt7)) {
    isSelectedCMULEvent = kTRUE;
  }
  if (IsSelected & AliVEvent::kMuonLikeLowPt7) {
    if(strFiredTriggers.Contains("CMLL7-B-NOPF-MUFAST"))
    isSelectedCMLLEvent = kTRUE;
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//




  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  // Track selection and analysis
  if(isSelectedCMLLEvent || isSelectedCMULEvent)
  {
    Double_t weight = 1;
    if(isSelectedCMLLEvent && !isSelectedCMULEvent){weight = weightCMLL;}   //Define the WEIGHTS FOR CMLL events
    AliVEvent *aodesd = NULL;
    aodesd = static_cast<AliVEvent *>(InputEvent());
    TLorentzVector lvMuon1, lvMuon2, lvDimuon;
    int nTracks = AliAnalysisMuonUtility::GetNTracks(aodesd);

    for (Int_t iMuon1 = 0; iMuon1 < nTracks; iMuon1++) {
      AliVParticle *muonTrack1 = 0;
      muonTrack1 = AliAnalysisMuonUtility::GetTrack(iMuon1, aodesd);
      if (!muonTrack1) {
        AliError(Form("ERROR: Could not retrieve AOD or ESD track %d", iMuon1));
        continue;
      }
      if (!fMuonTrackCuts->IsSelected(muonTrack1))
        continue; // include cuts on pDCA, Eta, Rabs.
      TrackToLorentzVector(muonTrack1, lvMuon1);

      for (Int_t iMuon2 = iMuon1 + 1; iMuon2 < nTracks; iMuon2++) {
        AliVParticle *muonTrack2 = 0;
        muonTrack2 = AliAnalysisMuonUtility::GetTrack(iMuon2, aodesd);
        if (!muonTrack2) {
          AliError(Form("ERROR: Could not retrieve AOD or ESD track %d", iMuon2));
          continue;
        }
        if (!fMuonTrackCuts->IsSelected(muonTrack2))
          continue; // include cuts on pDCA, Eta, Rabs.
        TrackToLorentzVector(muonTrack2, lvMuon2);

        lvDimuon = lvMuon1 + lvMuon2;
        Double_t diMuonValues[4]= {lvDimuon.Pt(), lvDimuon.M(), lvDimuon.Rapidity(), eventCentrality};

        if (muonTrack1->Charge() != muonTrack2->Charge())
        {

          fSparseDimuonOpp->Sumw2();
          fSparseDimuonOpp->Fill(diMuonValues, 1./weight);

          fSparseDimuonOpp->GetAxis(0)->SetTitle("#mu#mu_{P_{t}} GeV/c" );
          fSparseDimuonOpp->GetAxis(1)->SetTitle("#mu#mu_{IM} GeV/c^{2}" );
          fSparseDimuonOpp->GetAxis(2)->SetTitle("#mu#mu_{Rapidity}" );
          fSparseDimuonOpp->GetAxis(3)->SetTitle("Event Centrality" );
        }
        if (muonTrack1->Charge() <0 && muonTrack2->Charge() <0 )
        {

          fSparseDimuonNeg->Sumw2();
          fSparseDimuonNeg->Fill(diMuonValues, 1./weight);

          fSparseDimuonNeg->GetAxis(0)->SetTitle("#mu#mu_{P_{t}} GeV/c" );
          fSparseDimuonNeg->GetAxis(1)->SetTitle("#mu#mu_{IM} GeV/c^{2}" );
          fSparseDimuonNeg->GetAxis(2)->SetTitle("#mu#mu_{Rapidity}" );
          fSparseDimuonNeg->GetAxis(3)->SetTitle("Event Centrality" );
        }
        if (muonTrack1->Charge()>0 && muonTrack2->Charge()>0 )
        {

          fSparseDimuonPlus->Sumw2();
          fSparseDimuonPlus->Fill(diMuonValues, 1./weight);

          fSparseDimuonPlus->GetAxis(0)->SetTitle("#mu#mu_{P_{t}} GeV/c" );
          fSparseDimuonPlus->GetAxis(1)->SetTitle("#mu#mu_{IM} GeV/c^{2}" );
          fSparseDimuonPlus->GetAxis(2)->SetTitle("#mu#mu_{Rapidity}" );
          fSparseDimuonPlus->GetAxis(3)->SetTitle("Event Centrality" );
        }


      }
    }
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


  PostData(1, fListEvent);
}
//------------------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------//
//Some finalisation steps can be added
void TaskDimuonPP::Terminate(Option_t *) {
  fListEvent = dynamic_cast<TObjArray *>(GetOutputData(1));
  if (!fListEvent) {
    AliError("Could not retrieve TObjArray* fListEvent");
    return;
  }
}
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
// Dummy function to get a TLorentzVector from a track
void TaskDimuonPP::TrackToLorentzVector(AliVParticle *muonTrack,
                                        TLorentzVector &lvMuon) {
  Double_t muonMass2 = AliAnalysisMuonUtility::MuonMass2();
  Double_t energy = TMath::Sqrt(muonTrack->P() * muonTrack->P() + muonMass2);
  lvMuon.SetPxPyPzE(muonTrack->Px(), muonTrack->Py(), muonTrack->Pz(), energy);
}
//------------------------------------------------------------------------------------------------//
