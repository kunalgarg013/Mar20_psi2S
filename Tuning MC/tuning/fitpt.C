#include "TMinuit.h"


Double_t pT_shape(Double_t *x, Double_t *par)
{
  // power-law
  Double_t A = par[0];
  Double_t B = par[1];
  Double_t n1 = par[2];
  Double_t n2 = par[3];
  // pt
  Double_t pt = x[0];
  return (A * pt) / pow(1 + pow(pt / B, n1), n2);
}


void fitpt()
{
    TFile*f1 = new TFile("RawYields/NJpsi_Raw.root");

    TH1D* h1 = (TH1D*)f1->Get("histoPtYield_cent0to10;1");

    TF1* fFit = new TF1("fPtDistribution", pT_shape, h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax(), 4);
    fFit->SetParameter(0, h1->GetMaximum());
    fFit->SetParameter(1, -2.5);
    fFit->SetParameter(2, 6);
    fFit->SetParameter(3, 1);

    TString fitOpt = "SERQ";
    TFitResultPtr fitResultPtr;
    fitResultPtr = h1->Fit(fFit, fitOpt, "", 0, 12);

}