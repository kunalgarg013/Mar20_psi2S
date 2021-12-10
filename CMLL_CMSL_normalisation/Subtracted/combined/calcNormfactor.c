void GetHistoSqrt(TH1F *histo) {
  int numberOfBins = histo->GetNbinsX();

  for(int iBin =1;iBin<=numberOfBins;iBin++){
    Double_t binContent = histo->GetBinContent(iBin);
    Double_t binError = histo->GetBinError(iBin);

    histo->SetBinContent(iBin,TMath::Sqrt(binContent));
    histo->SetBinError(iBin,TMath::Sqrt(binContent)*binError/binContent);
  }
}

Bool_t SetSparseRange(THnSparse* hSparse, Int_t ivar, Double_t varMin, Double_t varMax, const char* option)
{
  //
  /// Sets range in a smart way.
  /// Checks the bin limits.
  //

  TAxis* axis = hSparse->GetAxis(ivar);
  if ( ! axis ) {
    printf("Warning: Axis %i not found in %s", ivar, hSparse->GetName());
    return kFALSE;
  }

  TString opt(option);
  Int_t minVarBin = -1, maxVarBin = -1;
  if ( opt.Contains( "USEBIN", TString::kIgnoreCase ) ) {
    minVarBin = (Int_t)varMin;
    maxVarBin = (Int_t)varMax;
  }
  else {
    minVarBin = axis->FindBin(varMin);
    maxVarBin = axis->FindBin(varMax);
  }

  if ( axis->GetFirst() == minVarBin && axis->GetLast() == maxVarBin && axis->TestBit(TAxis::kAxisRange) ) return kFALSE;

  axis->SetRange(minVarBin, maxVarBin);

  TString outString = Form("%s new range: %.5f < %s < %.5f", hSparse->GetName(), axis->GetBinLowEdge(axis->GetFirst()), axis->GetTitle(), axis->GetBinUpEdge(axis->GetLast()));
  TString binLabel = axis->GetBinLabel(axis->GetFirst());
  if ( ! binLabel.IsNull() ) {
    outString += " ( ";
    for ( Int_t ibin = axis->GetFirst(); ibin <= axis->GetLast(); ibin++ ) {
      outString += Form("%s ", axis->GetBinLabel(ibin));
    }
    outString += ")";
  }
  printf("Info: %s\n",outString.Data());

  return kTRUE;
}

void calcNormfactor()
{

    gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
    //    TFile *f1 = new TFile("files/CMLL_AnalysisResults.root");//ok
    TFile *f1 = new TFile("../../CMLL/CMLL_oqr_AnalysisResults.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    ofstream datnorm("norm_factor_DoubleDiff.dat");

    TFile* fRacc = new TFile("rAcceptance_DoubleDiff.root", "RECREATE");

    const Double_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Double_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    const Int_t pTLow[]    = {0, 2, 4, 6};
    const Int_t pTHigh[]   = {2, 4, 6, 12};


    //TFile* f2                       = new TFile("files/mixingHisto.root");
    // TFile* f2                       = new TFile("CMSL/18qr_cmsl.root");
    TFile* f2                       = new TFile("SigMixed_pT.root");

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TH1F* hMixed[100][100];

    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TH1F* hMixedPlike[100][100];

    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TH1F* hMixedNlike[100][100];



    for(Int_t k=1; k<10; k++)
    {
      for(Int_t l=0; l<4; l++)
      {
        hMixed[k][l] =      (TH1F*)InvMassUnlike->Get(Form("histoInvMass_Cent%ito%i_Pt%ito%i;1", (Int_t)cLow[k], (Int_t)cHigh[k], (Int_t)pTLow[l], (Int_t)pTHigh[l]));
        hMixedPlike[k][l] = (TH1F*)InvMassPlike->Get(Form("histoInvMass_Cent%ito%i_Pt%ito%i;1", (Int_t)cLow[k], (Int_t)cHigh[k], (Int_t)pTLow[l], (Int_t)pTHigh[l]));
        hMixedNlike[k][l] = (TH1F*)InvMassNlike->Get(Form("histoInvMass_Cent%ito%i_Pt%ito%i;1", (Int_t)cLow[k], (Int_t)cHigh[k], (Int_t)pTLow[l], (Int_t)pTHigh[l]));

      }
    }


    THnSparse* hSparseDimuon[100][100];
    THnSparse* hSparseDimuonNeg[100][100];
    THnSparse* hSparseDimuonPlus[100][100];

    TH1F* hRFactor[100][100];
    Double_t NormFactor[100][100];
    TH1F* hRawPlusPlus[100][100];
    TH1F* hRawMinusMinus[100][100];
    TH1F* hRaw[100][100];

    for(Int_t k=1; k<10; k++)
    {
      for(Int_t l=0; l<4; l++)
      {

        hSparseDimuon[k][l]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
        hSparseDimuonNeg[k][l]  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
        hSparseDimuonPlus[k][l] = (THnSparse*)arr->FindObject("fSparseDimuonPlus");

        SetSparseRange(hSparseDimuonNeg[k][l], 3, cLow[k], cHigh[k] - 1e-6, "");
        SetSparseRange(hSparseDimuonNeg[k][l], 2, -4. , -2.5 -1e-6,  "");
        SetSparseRange(hSparseDimuonNeg[k][l], 0, pTLow[l] , pTHigh[l] -1e-6,  "");
        SetSparseRange(hSparseDimuonNeg[k][l], 1, 2 , 15 -1e-6,  "");

        SetSparseRange(hSparseDimuonPlus[k][l], 3, cLow[k], cHigh[k] - 1e-6, "");
        SetSparseRange(hSparseDimuonPlus[k][l], 2, -4. , -2.5 -1e-6,  "");
        SetSparseRange(hSparseDimuonPlus[k][l], 0, pTLow[l] , pTHigh[l] -1e-6,  "");
        SetSparseRange(hSparseDimuonPlus[k][l], 1, 2 , 15 -1e-6,  "");

        SetSparseRange(hSparseDimuon[k][l], 3, cLow[k], cHigh[k] - 1e-6, "");
        SetSparseRange(hSparseDimuon[k][l], 2, -4. , -2.5 -1e-6,  "");
        SetSparseRange(hSparseDimuon[k][l], 0, pTLow[l] , pTHigh[l] -1e-6,  "");
        SetSparseRange(hSparseDimuon[k][l], 1, 2 , 15 -1e-6,  "");


          /*====================================*/

          hRaw[k][l]            =   (TH1F*)hSparseDimuon[k][l]->Projection(1);
          hRawPlusPlus[k][l]    =   (TH1F*)hSparseDimuonPlus[k][l]->Projection(1);
          hRawMinusMinus[k][l]  =   (TH1F*)hSparseDimuonNeg[k][l]->Projection(1);
          hRaw[k][l]->Sumw2();
          hRawPlusPlus[k][l]->Sumw2();
          hRawMinusMinus[k][l]->Sumw2();

          hMixedPlike[k][l]->Multiply(hMixedNlike[k][l]);
          GetHistoSqrt(hMixedPlike[k][l]);
          hMixedPlike[k][l]->Scale(2.);

          hRFactor[k][l] = (TH1F*)hMixed[k][l]->Clone("RFactor");
          hRFactor[k][l]->Divide(hMixedPlike[k][l]);

          hRawPlusPlus[k][l]->Multiply((TH1F*)hRawMinusMinus[k][l]);

          GetHistoSqrt(hRawPlusPlus[k][l]);
          hRawPlusPlus[k][l]->Multiply((TH1F*)hRFactor[k][l]);
          hRawPlusPlus[k][l]->Scale(2.);

          int minMassBin = 0;
          minMassBin = hRaw[k][l]->FindBin(2);
          int maxMassBin = 0;
          maxMassBin = hRaw[k][l]->FindBin(8);


          NormFactor[k][l] = hRawPlusPlus[k][l]->Integral(minMassBin, maxMassBin)/(hMixed[k][l]->Integral(minMassBin, maxMassBin));
          //cout<<hRawPlusPlus[l]->Integral(minMassBin, maxMassBin)<<endl;
          datnorm<<NormFactor[k][l]<<", ";
          cout<<NormFactor[k][l]<<" Cent  "<<cLow[k]<<" "<<cHigh[k]<<"  pT  "<<pTLow[l]<<" "<<pTHigh[l]<<endl;
          // cout<<"Norm Factor =         "<<NormFactor[l]<<endl;

      }

    }





}