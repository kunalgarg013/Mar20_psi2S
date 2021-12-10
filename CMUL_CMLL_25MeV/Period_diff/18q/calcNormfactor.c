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
    TFile *f1 = new TFile("AnalysisResults.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    ofstream datnorm("norm_factor_25MeV_18q.dat");

    TFile* fRacc = new TFile("rAcceptance_25MeV_18q.root", "RECREATE");

    const Int_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Int_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};


    TFile* f2                       = new TFile("Sig25MeV_18q.root");
    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TH1F* hMixed[10];

    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TH1F* hMixedPlike[10];

    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TH1F* hMixedNlike[10];

    for(Int_t i=1; i<10; i++)
    {
      hMixed[i] = (TH1F*)InvMassUnlike->Get(Form("histoInvMass_Cent%ito%i_Pt0to12;1", cLow[i], cHigh[i]));
      hMixedPlike[i] = (TH1F*)InvMassPlike->Get(Form("histoInvMass_Cent%ito%i_Pt0to12;1", cLow[i], cHigh[i]));
      hMixedNlike[i] = (TH1F*)InvMassNlike->Get(Form("histoInvMass_Cent%ito%i_Pt0to12;1", cLow[i], cHigh[i]));

    }

    hMixed[0] = (TH1F*)hMixed[1]->Clone("histoInvMass_Cent0to90_Pt0to12;1");
    hMixed[0]->Sumw2();
    hMixed[0]->Add(hMixed[2]);
    hMixed[0]->Add(hMixed[3]);
    hMixed[0]->Add(hMixed[4]);
    hMixed[0]->Add(hMixed[5]);
    hMixed[0]->Add(hMixed[6]);
    hMixed[0]->Add(hMixed[7]);
    hMixed[0]->Add(hMixed[8]);
    hMixed[0]->Add(hMixed[9]);

    hMixedPlike[0] = (TH1F*)hMixedPlike[1]->Clone("histoInvMass_Cent0to90_Pt0to12;1");
    hMixedPlike[0]->Sumw2();
    hMixedPlike[0]->Add(hMixedPlike[2]);
    hMixedPlike[0]->Add(hMixedPlike[3]);
    hMixedPlike[0]->Add(hMixedPlike[4]);
    hMixedPlike[0]->Add(hMixedPlike[5]);
    hMixedPlike[0]->Add(hMixedPlike[6]);
    hMixedPlike[0]->Add(hMixedPlike[7]);
    hMixedPlike[0]->Add(hMixedPlike[8]);
    hMixedPlike[0]->Add(hMixedPlike[9]);

    hMixedNlike[0] = (TH1F*)hMixedNlike[1]->Clone("histoInvMass_Cent0to90_Pt0to12;1");
    hMixedNlike[0]->Sumw2();
    hMixedNlike[0]->Add(hMixedNlike[2]);
    hMixedNlike[0]->Add(hMixedNlike[3]);
    hMixedNlike[0]->Add(hMixedNlike[4]);
    hMixedNlike[0]->Add(hMixedNlike[5]);
    hMixedNlike[0]->Add(hMixedNlike[6]);
    hMixedNlike[0]->Add(hMixedNlike[7]);
    hMixedNlike[0]->Add(hMixedNlike[8]);
    hMixedNlike[0]->Add(hMixedNlike[9]);


    THnSparse* hSparseDimuon[100];
    THnSparse* hSparseDimuonNeg[100];
    THnSparse* hSparseDimuonPlus[100];

    TH1F* hRFactor[10];
    Double_t NormFactor[10];
    TH1F* hRawPlusPlus[10];
    TH1F* hRawMinusMinus[10];
    TH1F* hRaw[10];

    for(Int_t l=0; l<10; l++)
    {

      hSparseDimuon[l]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
      hSparseDimuonNeg[l]  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
      hSparseDimuonPlus[l] = (THnSparse*)arr->FindObject("fSparseDimuonPlus");

      SetSparseRange(hSparseDimuonNeg[l], 3, cLow[l], cHigh[l] - 1e-6, "");
      SetSparseRange(hSparseDimuonNeg[l], 2, -4. , -2.5 -1e-6,  "");
      SetSparseRange(hSparseDimuonNeg[l], 0, 0 , 12 -1e-6,  "");
      SetSparseRange(hSparseDimuonNeg[l], 1, 2 , 15 -1e-6,  "");

      SetSparseRange(hSparseDimuonPlus[l], 3, cLow[l], cHigh[l] - 1e-6, "");
      SetSparseRange(hSparseDimuonPlus[l], 2, -4. , -2.5 -1e-6,  "");
      SetSparseRange(hSparseDimuonPlus[l], 0, 0 , 12 -1e-6,  "");
      SetSparseRange(hSparseDimuonPlus[l], 1, 2 , 15 -1e-6,  "");

      SetSparseRange(hSparseDimuon[l], 3, cLow[l], cHigh[l] - 1e-6, "");
      SetSparseRange(hSparseDimuon[l], 2, -4. , -2.5 -1e-6,  "");
      SetSparseRange(hSparseDimuon[l], 0, 0 , 12 -1e-6,  "");
      SetSparseRange(hSparseDimuon[l], 1, 2 , 15 -1e-6,  "");


        /*====================================*/

        hRaw[l]            =   (TH1F*)hSparseDimuon[l]->Projection(1);
        hRawPlusPlus[l]    =   (TH1F*)hSparseDimuonPlus[l]->Projection(1);
        hRawMinusMinus[l]  =   (TH1F*)hSparseDimuonNeg[l]->Projection(1);
        hRaw[l]->Sumw2();
        hRawPlusPlus[l]->Sumw2();
        hRawMinusMinus[l]->Sumw2();

        hMixedPlike[l]->Multiply(hMixedNlike[l]);
        GetHistoSqrt(hMixedPlike[l]);
        hMixedPlike[l]->Scale(2.);

        hRFactor[l] = (TH1F*)hMixed[l]->Clone("RFactor");
        hRFactor[l]->Divide(hMixedPlike[l]);

        hRawPlusPlus[l]->Multiply((TH1F*)hRawMinusMinus[l]);

        GetHistoSqrt(hRawPlusPlus[l]);
        hRawPlusPlus[l]->Multiply((TH1F*)hRFactor[l]);
        hRawPlusPlus[l]->Scale(2.);

        int minMassBin = hRaw[l]->FindBin(2);
        int maxMassBin = hRaw[l]->FindBin(8);


        NormFactor[l] = hRawPlusPlus[l]->Integral(minMassBin, maxMassBin)/(hMixed[l]->Integral(minMassBin, maxMassBin));
        //cout<<hRawPlusPlus[l]->Integral(minMassBin, maxMassBin)<<endl;
        cout<<NormFactor[l]<<" Norm  "<<cLow[l]<<" "<<cHigh[l]<<endl;
        datnorm<<NormFactor[l]<<endl;
        // cout<<"Norm Factor =         "<<NormFactor[l]<<endl;

        fRacc->cd();
        hRFactor[l]->GetYaxis()->SetRangeUser(0.7, 1.1);
        hRFactor[l]->GetXaxis()->SetTitle("M_{#mu#mu} GeV/c^{2}");
        hRFactor[l]->SetName(Form("Cent_%dto%d", (Int_t)cLow[l], (Int_t)cHigh[l]));
        hRFactor[l]->Write();


    }





}