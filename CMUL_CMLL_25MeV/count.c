Bool_t SetSparseRange(THnSparse* hSparse,Int_t ivar, Double_t varMin, Double_t varMax,const char* option)
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

void count()
{
    TFile* f1 = new TFile("CMUL_CMLL_25MeV.root");
     TObjArray *arr =(TObjArray*)f1->Get("ListEvent");



    const Double_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Double_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ofstream datnorm("Number_events_CMULL||CMLL.dat");


    THnSparse* hSparseDimuon[100];
    THnSparse* hSparseDimuonMM[100];
    THnSparse* hSparseDimuonPP[100];

    TH1F *hSigOpp[10];
    TH1F *hSigMM[10];
    TH1F *hSigPP[10];

    for(Int_t i=1; i<10; i++)
    {
        hSparseDimuon[i]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
        // hSparseDimuonMM[i]     = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
        // hSparseDimuonPP[i]     = (THnSparse*)arr->FindObject("fSparseDimuonPlus");


        // SetSparseRange(hSparseDimuon[i], 0, 0, 12 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 1, 2., 15 - 1e-6, "");
        // SetSparseRange(hSparseDimuon[i], 2, -4., -2.5 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 3, cLow[i], cHigh[i] - 1e-6, "");

        // SetSparseRange(hSparseDimuonMM[i], 0, 0, 12 - 1e-6, "");
        // SetSparseRange(hSparseDimuonMM[i], 1, 2., 15 - 1e-6, "");
        // SetSparseRange(hSparseDimuonMM[i], 2, -4., -2.5 - 1e-6, "");
        // SetSparseRange(hSparseDimuonMM[i], 3, cLow[i], cHigh[i] - 1e-6, "");

        // SetSparseRange(hSparseDimuonPP[i], 0, 0, 12 - 1e-6, "");
        // SetSparseRange(hSparseDimuonPP[i], 1, 2., 15 - 1e-6, "");
        // SetSparseRange(hSparseDimuonPP[i], 2, -4., -2.5 - 1e-6, "");
        // SetSparseRange(hSparseDimuonPP[i], 3, cLow[i], cHigh[i] - 1e-6, "");

        hSigOpp[i]=(TH1F*)hSparseDimuon[i]->Projection(1);//projection x
        // hSigMM[i]=(TH1F*)hSparseDimuonMM[i]->Projection(1);//projection x
        // hSigPP[i]=(TH1F*)hSparseDimuonPP[i]->Projection(1);//projection x

        datnorm<<hSigOpp[i]->GetEntries()<<"    "<<cLow[i]<<"   "<<cHigh[i]<<endl;



    }

}