#include "TROOT.h"
#include "TFile.h"
#include "THnSparse.h"
#include "TMath.h"
#include "TString.h"

void SlimSparse()
{
  THnSparse *fhDimuon;
  THnSparse *fhDimuonLight;



    TFile *file = new TFile("15o/AnalysisResults.root", "read");

    TObjArray *arr =(TObjArray*)file->Get("ListEvent");
    THnSparse* hSparseDimuon  = (THnSparseF*)arr->FindObject("fSparseDimuon");

    const Int_t axis[4] = {2,3,4,5};

    fhDimuonLight = hSparseDimuon->Projection(4,axis,"e");
    fhDimuonLight->SetName("hSparseDimuonLight");




    TFile *SaveFile = new TFile("LHC15o_light.root","recreate");
    fhDimuonLight->Write();

    SaveFile->Close();
    delete SaveFile;
}
