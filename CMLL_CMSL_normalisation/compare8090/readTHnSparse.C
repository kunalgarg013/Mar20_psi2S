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

void Sparse_2018()
{

    TFile* f1 = new TFile("CMLL_2018_AnalysisResults.root");
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    THnSparse* hSparseDimuonUnlike     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
    THnSparse* hSparseDimuonPPlike     = (THnSparse*)arr->FindObject("fSparseDimuonPlus");
    THnSparse* hSparseDimuonMMlike     = (THnSparse*)arr->FindObject("fSparseDimuonNeg");


    TH1F *hSig[100];

    SetSparseRange(hSparseDimuonUnlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike, 3, 0, 90 - 1e-6, "");
    hSig[1]=(TH1F*)hSparseDimuonUnlike->Projection(3);//projection x
    hSig[1]->SetNameTitle("IM_2018_Unlike_Cent0to90", "IM_2018_Unlike_Cent0to90");


    SetSparseRange(hSparseDimuonUnlike, 3, 0, 20 - 1e-6, "");
    hSig[2]=(TH1F*)hSparseDimuonUnlike->Projection(3);//projection x
    hSig[2]->SetNameTitle("IM_2018_Unlike_Cent0to20", "IM_2018_Unlike_Cent0to20");

    SetSparseRange(hSparseDimuonPPlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonPPlike, 3, 0, 90 - 1e-6, "");
    hSig[3]=(TH1F*)hSparseDimuonPPlike->Projection(3);//projection x
    hSig[3]->SetNameTitle("IM_2018_PPlike_Cent0to90", "IM_2018_PPlike_Cent0to90");

    SetSparseRange(hSparseDimuonPPlike, 3, 0, 20 - 1e-6, "");
    hSig[4]=(TH1F*)hSparseDimuonPPlike->Projection(3);//projection x
    hSig[4]->SetNameTitle("IM_2018_PPlike_Cent0to20", "IM_2018_PPlike_Cent0to20");

    SetSparseRange(hSparseDimuonMMlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonMMlike, 3, 0, 90 - 1e-6, "");
    hSig[5]=(TH1F*)hSparseDimuonMMlike->Projection(3);//projection x
    hSig[5]->SetNameTitle("IM_2018_MMlike_Cent0to90", "IM_2018_MMlike_Cent0to90");

    SetSparseRange(hSparseDimuonMMlike, 3, 0, 20 - 1e-6, "");
    hSig[6]=(TH1F*)hSparseDimuonMMlike->Projection(3);//projection x
    hSig[6]->SetNameTitle("IM_2018_MMlike_Cent0to20", "IM_2018_MMlike_Cent0to20");


    TFile* fOutput = new TFile("Output_CMLL.root", "RECREATE");
    fOutput->cd();
    hSig[1]->Write();
    hSig[2]->Write();
    hSig[3]->Write();
    hSig[4]->Write();
    hSig[5]->Write();
    hSig[6]->Write();
    fOutput->Close();

}

void Sparse_2015()
{

    TFile* f1 = new TFile("CMLL_2015_AnalysisResults.root");
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    THnSparse* hSparseDimuonUnlike     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
    THnSparse* hSparseDimuonPPlike     = (THnSparse*)arr->FindObject("fSparseDimuonPlus");
    THnSparse* hSparseDimuonMMlike     = (THnSparse*)arr->FindObject("fSparseDimuonNeg");


    TH1F *hSig[100];

    SetSparseRange(hSparseDimuonUnlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike, 3, 0, 90 - 1e-6, "");
    hSig[1]=(TH1F*)hSparseDimuonUnlike->Projection(3);//projection x
    hSig[1]->SetNameTitle("IM_2015_Unlike_Cent0to90", "IM_2015_Unlike_Cent0to90");


    SetSparseRange(hSparseDimuonUnlike, 3, 0, 20 - 1e-6, "");
    hSig[2]=(TH1F*)hSparseDimuonUnlike->Projection(3);//projection x
    hSig[2]->SetNameTitle("IM_2015_Unlike_Cent0to20", "IM_2015_Unlike_Cent0to20");

    SetSparseRange(hSparseDimuonPPlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonPPlike, 3, 0, 90 - 1e-6, "");
    hSig[3]=(TH1F*)hSparseDimuonPPlike->Projection(3);//projection x
    hSig[3]->SetNameTitle("IM_2015_PPlike_Cent0to90", "IM_2015_PPlike_Cent0to90");

    SetSparseRange(hSparseDimuonPPlike, 3, 0, 20 - 1e-6, "");
    hSig[4]=(TH1F*)hSparseDimuonPPlike->Projection(3);//projection x
    hSig[4]->SetNameTitle("IM_2015_PPlike_Cent0to20", "IM_2015_PPlike_Cent0to20");

    SetSparseRange(hSparseDimuonMMlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonMMlike, 3, 0, 90 - 1e-6, "");
    hSig[5]=(TH1F*)hSparseDimuonMMlike->Projection(3);//projection x
    hSig[5]->SetNameTitle("IM_2015_MMlike_Cent0to90", "IM_2015_MMlike_Cent0to90");

    SetSparseRange(hSparseDimuonMMlike, 3, 0, 20 - 1e-6, "");
    hSig[6]=(TH1F*)hSparseDimuonMMlike->Projection(3);//projection x
    hSig[6]->SetNameTitle("IM_2015_MMlike_Cent0to20", "IM_2015_MMlike_Cent0to20");


    TFile* fOutput = new TFile("Output_CMLL.root", "UPDATE");
    fOutput->cd();
    hSig[1]->Write();
    hSig[2]->Write();
    hSig[3]->Write();
    hSig[4]->Write();
    hSig[5]->Write();
    hSig[6]->Write();
    fOutput->Close();

}

void Sparse_combined()
{

    TFile* f1 = new TFile("CMLL_oqr_AnalysisResults.root");
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    THnSparse* hSparseDimuonUnlike     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");


    TH1F *hSig[100];
    SetSparseRange(hSparseDimuonUnlike, 0, 0, 12. - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike, 3, 70, 80 - 1e-6, "");
    hSig[1]=(TH1F*)hSparseDimuonUnlike->Projection(1);//projection x
    hSig[1]->SetNameTitle("IM_Unlike_Cent70to80", "IM_Unlike_Cent70to80");

    TFile* f2 = new TFile("CMLL_oqr_AnalysisResults.root");
    TObjArray *arr2 =(TObjArray*)f2->Get("ListEvent");
    THnSparse* hSparseDimuonUnlike2     = (THnSparse*)arr2->FindObject("fSparseDimuonOpp");



    SetSparseRange(hSparseDimuonUnlike2, 0, 0, 12. - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike2, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike2, 3, 80, 90 - 1e-6, "");
    hSig[2]=(TH1F*)hSparseDimuonUnlike2->Projection(1);//projection x
    hSig[2]->SetNameTitle("IM_Unlike_Cent80to90", "IM_Unlike_Cent80to90");

    TFile* f0 = new TFile("CMLL_oqr_AnalysisResults.root");
    TObjArray *arr0 =(TObjArray*)f0->Get("ListEvent");
    THnSparse* hSparseDimuonUnlike0     = (THnSparse*)arr0->FindObject("fSparseDimuonOpp");

    SetSparseRange(hSparseDimuonUnlike0, 0, 0, 12. - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike0, 2, -4., -2.5 - 1e-6, "");
    SetSparseRange(hSparseDimuonUnlike0, 3, 0, 10 - 1e-6, "");
    hSig[3]=(TH1F*)hSparseDimuonUnlike0->Projection(1);//projection x
    hSig[3]->SetNameTitle("IM_Unlike_Cent0to10", "IM_Unlike_Cent0to10");



    TFile* fOutput = new TFile("Output_CMLL2.root", "RECREATE");
    fOutput->cd();
    hSig[1]->Write();
    hSig[2]->Write();
    hSig[3]->Write();
    fOutput->Close();

}

void readTHnSparse()
{
    // Sparse_2018();
    // Sparse_2015();
    Sparse_combined();
}