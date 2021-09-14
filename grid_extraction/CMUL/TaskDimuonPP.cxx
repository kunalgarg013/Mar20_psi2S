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
      fLastRun(1), fHistoTotalEventsPerRun(0), fHistoCMULEventsPerRun(0),
      fHistoDimuonInvMass(0) {}
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// Main custom constructor. Also, define the input and output slots of your
// objects
TaskDimuonPP::TaskDimuonPP(const char *name, int firstRun, int lastRun)
    : AliAnalysisTaskSE(name), fListEvent(0x0), fMuonTrackCuts(0),
      fFirstRun(firstRun), fLastRun(lastRun), fHistoTotalEventsPerRun(0),
      fHistoCMULEventsPerRun(0), fHistoDimuonInvMass(0) {

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

//-------------------------------------------------------------------------------------------------//
// Here you define your histograms and othe robjects and add them to their
// associated list.
void TaskDimuonPP::UserCreateOutputObjects() {

  // Histograms, tree, or THnsparse definitions
  fListEvent = new TObjArray(20);
  fListEvent->SetOwner(kTRUE);
  fListEvent->SetName("ListEvent");

  fHistoTotalEventsPerRun = new TH1I("fHistoTotalEventsPerRun", "",
                                     fLastRun - fFirstRun, fFirstRun, fLastRun);
  fHistoTotalEventsPerRun->Sumw2();
  fListEvent->Add(fHistoTotalEventsPerRun);

  fHistoCMULEventsPerRun = new TH1I("fHistoCMULEventsPerRun", "",
                                    fLastRun - fFirstRun, fFirstRun, fLastRun);

  fHistoCMULEventsPerRun->Sumw2();
  fListEvent->Add(fHistoCMULEventsPerRun);

  fHistoDimuonInvMass = new TH1F("fHistoDimuonInvMass", "", 400, 0, 20);
  fHistoDimuonInvMass->Sumw2();
  fListEvent->Add(fHistoDimuonInvMass);


Int_t bins[7] =    {300, 300,  300, 2000,  60, 100, fLastRun - fFirstRun};
Double_t xmin[7] = {0.,   0.,   0.,   0., -5.,   0, (Double_t)fFirstRun};
Double_t xmax[7] = {30., 30.,  30.,  20., -2., 100, (Double_t)fLastRun};
fSparseDimuon = new THnSparseF("fSparseDimuon", "", 7, bins, xmin, xmax);


fSparseDimuon->GetAxis(0)->SetBinLabel( 1, "Muon1Pt" );
fSparseDimuon->GetAxis(1)->SetBinLabel( 2, "Muon2Pt" );
fSparseDimuon->GetAxis(2)->SetBinLabel( 3, "DiMuonPt" );
fSparseDimuon->GetAxis(3)->SetBinLabel( 4, "DiMuonIM" );
fSparseDimuon->GetAxis(4)->SetBinLabel( 5, "DiMuonEta" );
fSparseDimuon->GetAxis(5)->SetBinLabel( 6, "Centrality" );
fSparseDimuon->GetAxis(6)->SetBinLabel( 7, "RunNumber" );



fListEvent->Add(fSparseDimuon);



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
  fHistoTotalEventsPerRun->Fill(runNumber);

  UInt_t IsSelected =
      (((AliInputEventHandler *)(AliAnalysisManager::GetAnalysisManager()
                                     ->GetInputEventHandler()))
           ->IsEventSelected());

  // Make sure that the physics selection key (e.g kMuonUnlikeLowPt7) is valid
  // for the data sample you are analysing
  if (strFiredTriggers.Contains("CMUL7-B-NOPF-MUFAST") &&
      (IsSelected & AliVEvent::kMuonUnlikeLowPt7)) {
    isSelectedCMULEvent = kTRUE;
    fHistoCMULEventsPerRun->Fill(runNumber);
  } else {
    return;
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//




  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  // Track selection and analysis

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
      if (muonTrack1->Charge() == muonTrack2->Charge())
        continue;

      // Here you can fill the dimuon containers:
      fHistoDimuonInvMass->Fill(lvDimuon.M());

      Double_t diMuonValues[7]= {lvMuon1.Pt(), lvMuon2.Pt(), lvDimuon.Pt(), lvDimuon.M(), lvDimuon.Eta(), eventCentrality, (Double_t)runNumber};
      fSparseDimuon->Sumw2();
      fSparseDimuon->Fill(diMuonValues);

      fSparseDimuon->GetAxis(0)->SetTitle("#mu1_{P_{t}} GeV/c" );
      fSparseDimuon->GetAxis(1)->SetTitle("#mu2_{P_{t}} GeV/c" );
      fSparseDimuon->GetAxis(2)->SetTitle("#mu#mu_{P_{t}} GeV/c" );
      fSparseDimuon->GetAxis(3)->SetTitle("#mu#mu_{IM} GeV/c^{2}" );
      fSparseDimuon->GetAxis(4)->SetTitle("#mu#mu_{#eta}" );
      fSparseDimuon->GetAxis(5)->SetTitle("Event Centrality" );
      fSparseDimuon->GetAxis(6)->SetTitle("Run Number" );



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
