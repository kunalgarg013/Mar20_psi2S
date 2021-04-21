/*
 *simple DIMuon Analysis task
 *
 */
#ifndef ALIANALYSISTASKJPSIPP_H
#define ALIANALYSISTASKJPSIPP_H

class TH1F;
class TH2F;
class TH3F;
class TNtuple;
class TTree;
class TList;
class TObjArray;
class TArrayF;

class AliAnalysisManager;
class AliVEvent;
class AliMuonTrackCuts;
class AliAnalysisUtils;
class AliMultiInputEventHandler;
class AliMixInputEventHandler2;

#ifndef ALIANALYSISTASKSE_H
#include "AliAnalysisTaskSE.h"
#endif

class TaskDimuonPbPb : public AliAnalysisTaskSE {
public:
    TaskDimuonPbPb();
    TaskDimuonPbPb(const char *name, int firstRun, int lastRun);
    virtual ~TaskDimuonPbPb();
    virtual void     NotifyRun();
    virtual void     UserCreateOutputObjects();
    virtual void     UserExec(Option_t *option);
    virtual void     Terminate(Option_t *);


    private:

      AliMuonTrackCuts *fMuonTrackCuts;//!
      Int_t fFirstRun;
      Int_t fLastRun;

      TTree *treeEvents; //!
      std::vector<std::vector<double> > vectorMuon;

      Float_t treeEventCentrality;
      


      TObjArray *fListEvent; // list for the tree
      

    ClassDef(TaskDimuonPbPb, 2);
};

#endif
