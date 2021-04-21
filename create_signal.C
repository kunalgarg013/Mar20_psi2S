#include <vector>
#include "Riostream.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TTree.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TVector3.h"
#include "TSystem.h"
#include "TProfile.h"
#include "TColor.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "THnSparse.h"
#include "TGraphErrors.h"
#include "TMatrixDSym.h"
#include "TMinuit.h"
#include "TFitResult.h"
// #include "gMinuit.h"
// #include "gMinuit.h"
// #include "gMinuit.h"

void create_signal()
{

    const Double_t cLow[]     = {0,  0,  10, 20, 40, 60};
    const Double_t cHigh[]    = {90, 10, 20, 40, 60, 90};

    const Double_t pTLow[]    = {0,  0, 2, 3, 4, 6 };
    const Double_t pTHigh[]   = {12, 2, 3, 4, 6, 12};

    const Double_t rapLow[]   = {-4,   -4,    -3.5, -3.25, -3,  -2.75};
    const Double_t rapHigh[]  = {-2.5, -3.5, -3.25, -3,    -2.75, -2.5};

    TString strRapLow[]  = {"-4",   "-4",     "-3.5",  "-3.25",       "-3",    "-2.75"};
    TString strRapHigh[] = {"-2.5", "-3.5" ,  "-3.25",     "-3",    "-2.75",     "-2.5"};

    TFile *f1 = new TFile("updatedCMULAnalysisResults.root");//ok
    // TObjArray *arr =(TObjArray*)f1->Get("ListEvent");

    // THnSparse* hSparse     = (THnSparse*)f1->Get("hSparseDimuonLight");
    THnSparse* hSparseDimuon           = (THnSparse*)f1->Get("hSparseDimuonLight");

    double nCentBins = 6;
    double npTBins = 6;

    TFile* fSigHistos = new TFile("signalhistos_cent_pt_rap.root", "RECREATE");
    TH1D *hSig[200];
    Int_t l=0;

    //Axis: pt = 2, M = 3, Rap = 4, Cent = 5
    for(Int_t p=0; p<6;p++)
    {
        for(Int_t i=0; i<6; i++)
        {
            for(Int_t k=0; k<6; k++)
            {
                Int_t RapMin = hSparseDimuon->GetAxis(2)->FindBin(rapLow[p] + 1e-6);
                Int_t RapMax = hSparseDimuon->GetAxis(2)->FindBin(rapHigh[p] - 1e-6);
                Int_t CenMin = hSparseDimuon->GetAxis(3)->FindBin(cLow[i]  + 1e-6);
                Int_t CenMax = hSparseDimuon->GetAxis(3)->FindBin(cHigh[i] - 1e-6);

                Int_t MassMin = hSparseDimuon->GetAxis(1)->FindBin(0. + 1e-6);
                Int_t MassMax = hSparseDimuon->GetAxis(1)->FindBin(10.- 1e-6);

                Int_t Plow   = hSparseDimuon->GetAxis(0)->FindBin(pTLow[k] + 1e-6);
                Int_t Pmax   = hSparseDimuon->GetAxis(0)->FindBin(pTHigh[k] - 1e-6);


                //projection from THnSparse
                hSparseDimuon->GetAxis(0)->SetRange(Plow, Pmax); //Pt Cuts for Muon 2
                hSparseDimuon->GetAxis(0)->SetBit(TAxis::kAxisRange);
                hSparseDimuon->GetAxis(2)->SetRange(RapMin, RapMax); //Rapidity cut on Dimuon
                hSparseDimuon->GetAxis(2)->SetBit(TAxis::kAxisRange);
                hSparseDimuon->GetAxis(3)->SetRange(CenMin, CenMax); //Centrality Range
                hSparseDimuon->GetAxis(3)->SetBit(TAxis::kAxisRange);

                hSparseDimuon->GetAxis(1)->SetRange(MassMin, MassMax); //Centrality Range
                hSparseDimuon->GetAxis(1)->SetBit(TAxis::kAxisRange);

                hSig[l]=(TH1D*)hSparseDimuon->Projection(1);//projection x
                fSigHistos->cd();
                hSig[l]->SetName(Form("SignalHisto_Cent_%dto%d_pT_%dto%d_Rap%sto%s", (Int_t)cLow[i], (Int_t)cHigh[i], (Int_t)pTLow[k], (Int_t)pTHigh[k], strRapLow[p].Data(), strRapHigh[p].Data()));
                hSig[l]->Write();
                // cout<<l<<endl;
                l= l+1;

            }
        }
    }

}