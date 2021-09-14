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
    TFile *f1 = new TFile("CMLL/CMLL_2018_AnalysisResults.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    ofstream datnorm("norm_factor_2018.dat");

    TFile* fRacc = new TFile("rAcceptance_2018.root", "RECREATE");

    const Double_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Double_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    Double_t dPt     = 12.;
    Int_t ptLow      =   0;
    Int_t ptHigh     =  12;


    //TFile* f2                       = new TFile("files/mixingHisto.root");
    TFile* f2                       = new TFile("CMSL/18qr_cmsl.root");
    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[10];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixed[6] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixed[7] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixed[8] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixed[9] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

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


    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TDirectoryFile* pTPlike         = (TDirectoryFile*)PlikeArr->Get("Pt");
    TDirectoryFile* RapPlike        = (TDirectoryFile*)PlikeArr->Get("Rapidity");

    TH1F* hMixedPlike[10];
    hMixedPlike[1] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedPlike[2] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedPlike[3] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedPlike[4] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedPlike[5] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedPlike[6] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedPlike[7] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedPlike[8] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedPlike[9] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

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

    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TDirectoryFile* pTNlike         = (TDirectoryFile*)NlikeArr->Get("Pt");
    TDirectoryFile* RapNlike        = (TDirectoryFile*)NlikeArr->Get("Rapidity");

    TH1F* hMixedNlike[10];
    hMixedNlike[1] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedNlike[2] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedNlike[3] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedNlike[4] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedNlike[5] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedNlike[6] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedNlike[7] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedNlike[8] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedNlike[9] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

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


    THnSparse* hSparseDimuon     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
    THnSparse* hSparseDimuonNeg  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonPlus = (THnSparse*)arr->FindObject("fSparseDimuonPlus");

    TH1F* hRFactor[10];
    Double_t NormFactor[10];
    TH1F* hRawPlusPlus[10];
    TH1F* hRawMinusMinus[10];
    TH1F* hRaw[10];

    for(Int_t l=0; l<10; l++)
    {

      SetSparseRange(hSparseDimuonNeg, 3, cLow[l], cHigh[l] - 1e-6, "");
      SetSparseRange(hSparseDimuonNeg, 2, -4. , -2.5 -1e-6,  "");
      SetSparseRange(hSparseDimuonNeg, 0, 0 , 12 -1e-6,  "");
      SetSparseRange(hSparseDimuonNeg, 1, 2 , 15 -1e-6,  "");

      SetSparseRange(hSparseDimuonPlus, 3, cLow[l], cHigh[l] - 1e-6, "");
      SetSparseRange(hSparseDimuonPlus, 2, -4. , -2.5 -1e-6,  "");
      SetSparseRange(hSparseDimuonPlus, 0, 0 , 12 -1e-6,  "");
      SetSparseRange(hSparseDimuonPlus, 1, 2 , 15 -1e-6,  "");

      SetSparseRange(hSparseDimuon, 3, cLow[l], cHigh[l] - 1e-6, "");
      SetSparseRange(hSparseDimuon, 2, -4. , -2.5 -1e-6,  "");
      SetSparseRange(hSparseDimuon, 0, 0 , 12 -1e-6,  "");
      SetSparseRange(hSparseDimuon, 1, 2 , 15 -1e-6,  "");


        /*====================================*/

        hRaw[l]            =   (TH1F*)hSparseDimuon->Projection(1);
        hRawPlusPlus[l]    =   (TH1F*)hSparseDimuonPlus->Projection(1);
        hRawMinusMinus[l]  =   (TH1F*)hSparseDimuonNeg->Projection(1);
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
        datnorm<<NormFactor[l]<<endl;
        // cout<<"Norm Factor =         "<<NormFactor[l]<<endl;

        fRacc->cd();
        hRFactor[l]->GetYaxis()->SetRangeUser(0.7, 1.1);
        hRFactor[l]->GetXaxis()->SetTitle("M_{#mu#mu} GeV/c^{2}");
        hRFactor[l]->SetName(Form("Cent_%dto%d", (Int_t)cLow[l], (Int_t)cHigh[l]));
        hRFactor[l]->Write();


    }





}