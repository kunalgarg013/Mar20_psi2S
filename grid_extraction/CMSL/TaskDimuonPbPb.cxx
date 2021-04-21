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

//include root libraries
#include <iostream>
#include <TCanvas.h>
#include <TList.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TChain.h>
#include "TMath.h"
#include <TObjArray.h>
//include aliroot libraries
#include "AliLog.h"
#include "AliAnalysisManager.h"
#include "AliAODv0.h"
#include "AliVEvent.h"
#include "AliESDEvent.h"
#include "AliAODEvent.h"
#include "AliVVZERO.h"
#include "AliESDVZERO.h"
#include "AliAODVZERO.h"
#include "AliVVertex.h"
#include "AliESDVertex.h"
#include "AliAODVertex.h"
#include "AliAnalysisMuonUtility.h"
#include "AliAnalysisUtils.h"
#include "AliMuonTrackCuts.h"
#include "AliOADBMuonTrackCutsParam.h"
#include "AliCentrality.h"
#include "AliAODDimuon.h"
#include "AliVTrack.h"
#include "AliAODTrack.h"
#include "AliAODTracklets.h"
#include "AliAODHeader.h"
#include "AliESDMuonTrack.h"
#include "AliInputEventHandler.h"
#include "AliMultSelection.h"
#include "AliAODDimuon.h"
#include "TaskDimuonPbPb.h"

ClassImp(TaskDimuonPbPb)

//________________________________________________________________________
TaskDimuonPbPb::TaskDimuonPbPb()
: AliAnalysisTaskSE(),
fListEvent(0x0),
fMuonTrackCuts(0),
vectorMuon(0),
treeEventCentrality(0),
fFirstRun(0),
fLastRun(1)

{
  // Dummy constructor ALWAYS needed for I/O.
}

//________________________________________________________________________
TaskDimuonPbPb::TaskDimuonPbPb(const char *name, int firstRun, int lastRun)
: AliAnalysisTaskSE(name),
fListEvent(0x0),
fMuonTrackCuts(0),
vectorMuon(0),
treeEventCentrality(0),
fFirstRun(firstRun),
fLastRun(lastRun)

{

  // Input slot #0 works with a TChain - it is connected to the default input container
  DefineInput(0, TChain::Class());
  // Output slot #1 writes into a TH1 container
  DefineOutput(1, TObjArray::Class());                                            // for output objarray

}

//________________________________________________________________________
TaskDimuonPbPb::~TaskDimuonPbPb()
{
  // Destructor. Clean-up the output list, but not the histograms that are put inside
  // (the list is owner and will clean-up these histograms). Protect in PROOF case.
  if (fListEvent && !AliAnalysisManager::GetAnalysisManager()->IsProofMode()) {
    delete fListEvent;
  }

  // if(fUtils) delete fUtils;
}

//________________________________________________________________________
void TaskDimuonPbPb::NotifyRun()
{
  /// Set run number for cuts
  if ( fMuonTrackCuts ) fMuonTrackCuts->SetRun(fInputHandler);
}

//________________________________________________________________________
void TaskDimuonPbPb::UserCreateOutputObjects()
{
  //Create the event, single muon, dimuon histgrams, to do that, it is only needed to add the name of the histogram to the corresponding list, it will be created and the bins will be set according to the name


  //Event histograms
  fListEvent = new TObjArray(2000);
  fListEvent->SetOwner(kTRUE);
  fListEvent->SetName("ListEvent");

  treeEvents = new TTree("eventsTree","tree that contains information of the event");
  treeEvents->Branch("muon",&vectorMuon);
  treeEvents->Branch("eventCentrality",&treeEventCentrality);
  fListEvent->AddAtAndExpand(treeEvents,0);


  
  

  fMuonTrackCuts = new AliMuonTrackCuts("StandardMuonTrackCuts","StandardMuonTrackCuts");
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  fMuonTrackCuts->SetFilterMask (AliMuonTrackCuts::kMuEta | AliMuonTrackCuts::kMuThetaAbs  | AliMuonTrackCuts::kMuMatchLpt | AliMuonTrackCuts::kMuPdca);


  PostData(1, fListEvent);
}

//________________________________________________________________________
void TaskDimuonPbPb::UserExec(Option_t *)
{
  vectorMuon.clear();
  AliAODEvent *aod = 0;
  AliAODHeader *aodHeader = NULL;
  Float_t muonMass2 = AliAnalysisMuonUtility::MuonMass2();
  Bool_t isSelectedCMSLEvent = kFALSE;

  

  TString strFiredTriggers;
  aod = static_cast<AliAODEvent *>(InputEvent());
  if(aod){
    aodHeader = (AliAODHeader*)aod->GetHeader();
    strFiredTriggers = aod->GetFiredTriggerClasses();
  }
  else{
    AliError("ERROR: Could not retrieve ESD or AOD event !!");
    return;
  }



  int runNumber = aod->GetRunNumber();

  UInt_t IsSelected = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected());

  if (IsSelected & AliVEvent::kMuonSingleLowPt7) {
    if(strFiredTriggers.Contains("CMSL7-B-NOPF-MUFAST"))
    isSelectedCMSLEvent = kTRUE;
  }


  AliMultSelection *multSelection = (AliMultSelection * ) aod->FindListObject("MultSelection");
  Float_t lPercentile = multSelection->GetMultiplicityPercentile("V0M");
  Double_t centralityFromV0 = multSelection->GetMultiplicityPercentile("V0M", false);
  treeEventCentrality = centralityFromV0;
  if(centralityFromV0 > 90) return;


  
  if(isSelectedCMSLEvent){ //CMSL Trigger    //To normal task with ThnSparse, Add CMLL trigger with the condition as written down in notes
    std::vector<double> tempoVector;
    AliVEvent* aodesd = NULL;
    aodesd = static_cast<AliVEvent *>(InputEvent());

    int nTracks =0;
    nTracks = AliAnalysisMuonUtility::GetNTracks(aodesd);
    for (Int_t i = 0; i < nTracks; i++) {
      tempoVector.clear();
      AliVParticle *muonTrack = 0;
      muonTrack = AliAnalysisMuonUtility::GetTrack(i,aodesd);
      if ( !muonTrack ) {
        AliError(Form("ERROR: Could not retrieve AOD or ESD track %d", i));
        continue;
      }


      if (!fMuonTrackCuts->IsSelected(muonTrack)) continue;

      Float_t energy = muonTrack->P()*muonTrack->P() + muonMass2;
      energy = TMath::Sqrt(energy);


      tempoVector.push_back(muonTrack->Px());
      tempoVector.push_back(muonTrack->Py());
      tempoVector.push_back(muonTrack->Pz());
      tempoVector.push_back(energy);
      tempoVector.push_back(muonTrack->Charge());
      vectorMuon.push_back(tempoVector);
    }
    ((TTree*)fListEvent->UncheckedAt(0))->Fill();
  }


  PostData(1, fListEvent);


}

//________________________________________________________________________
void TaskDimuonPbPb::Terminate(Option_t *)
{
  fListEvent = dynamic_cast<TObjArray *>(GetOutputData(1));
  if (!fListEvent) { AliError("Could not retrieve TObjArray* fListEvent"); return; }

}
