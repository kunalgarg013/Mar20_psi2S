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


void subMixing_pT()
{
    const Int_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Int_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    const Int_t pTLow[]    = {0, 2, 4, 6};
    const Int_t pTHigh[]   = {2, 4, 6, 12};


    gStyle->Reset("Plain");
    gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
    gStyle->SetOptFit(1111);
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(1111);
    gStyle->SetPalette(1);
    gStyle->SetCanvasColor(10);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetFrameLineWidth(1);
    gStyle->SetFrameFillColor(kWhite);
    gStyle->SetPadColor(10);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetHistLineWidth(1);
    gStyle->SetHistLineColor(kBlack);
    gStyle->SetFuncWidth(2);
    gStyle->SetFuncColor(kGreen);
    gStyle->SetLineWidth(2);
    gStyle->SetLabelSize(0.045,"xyz");
    gStyle->SetLabelOffset(0.01,"y");
    gStyle->SetLabelOffset(0.01,"x");
    gStyle->SetLabelColor(kBlack,"xyz");
    gStyle->SetTitleSize(0.05,"xyz");
    gStyle->SetTitleOffset(1.25,"y");
    gStyle->SetTitleOffset(1.2,"x");
    gStyle->SetTitleFillColor(kWhite);
    gStyle->SetTextSizePixels(26);
    gStyle->SetTextFont(42);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetLegendFillColor(kWhite);
    gStyle->SetLegendFont(42);



    /*====================================================================================*/
    //Reading from Input File
    TFile* f2                       = new TFile("SigMixed_pT.root");
    TFile* fNew =    new TFile("scaledpTmixed.root", "RECREATE");

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    Double_t NormFactor[100] = {0.291371, 0.293112, 0.297758, 0.301781, 0.224833, 0.224235, 0.227157, 0.231541, 0.16401, 0.161742, 0.164758, 0.167567, 0.11168, 0.109608, 0.112695, 0.109992, 0.0700583, 0.0691394, 0.0696915, 0.067676, 0.0403621, 0.0390281, 0.0379503, 0.0341203, 0.0207771, 0.0206714, 0.0198616, 0.0106848, 0.00940243, 0.00787674, 0.00536403, 0.00103493, 0.00286918, 0.00216516, 0.000429423, 0.00089874};   //Ignore first value of the array.
    TH1F* hTest[500][500];

    for(Int_t k=1; k<10; k++)
    {
        for(Int_t l=0;l<4;l++)
        {
            hTest[k][l] = (TH1F*)InvMassUnlike->Get(Form("histoInvMass_Cent%ito%i_Pt%ito%i;1", (Int_t)cLow[k], (Int_t)cHigh[k], (Int_t)pTLow[l], (Int_t)pTHigh[l]));
            hTest[k][l]->Sumw2();
            hTest[k][l]->Scale(NormFactor[4*(k-1) + l]);
        }
    }



    TH1F* hpTMixed[500];
    for(Int_t m=0; m<4; m++)
    {
        hpTMixed[m] = (TH1F*)hTest[1][m]->Clone();
        hpTMixed[m]->Add(hTest[2][m]);
        hpTMixed[m]->Add(hTest[3][m]);
        hpTMixed[m]->Add(hTest[4][m]);
        hpTMixed[m]->Add(hTest[5][m]);
        hpTMixed[m]->Add(hTest[6][m]);
        hpTMixed[m]->Add(hTest[7][m]);
        hpTMixed[m]->Add(hTest[8][m]);
        hpTMixed[m]->Add(hTest[9][m]);
        fNew->cd();

        hpTMixed[m]->SetName(Form("pT_%dto%d", (Int_t)pTLow[m], (Int_t)pTHigh[m]));
        // cout<<Form("pT_%dto%d", (Int_t)pTLow[m], (Int_t)pTHigh[m])<<"     "<<m<<endl;
        hpTMixed[m]->Write();

    }



    TFile *f1 = new TFile("../../CMLL/CMLL_oqr_AnalysisResults.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    THnSparse* hSparseDimuon[100];

    THnSparse* hSparseDimuonNeg  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonPlus = (THnSparse*)arr->FindObject("fSparseDimuonPlus");



    TH1F *hSig[500];

    TFile* fTest = new TFile("subtracted_pT.root", "RECREATE");
    for(Int_t i=0; i<4; i++)
    {
        hSparseDimuon[i]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");


        SetSparseRange(hSparseDimuon[i], 2, -4., -2.5 -1e-6, "");
        SetSparseRange(hSparseDimuon[i], 3, 0, 90 -1e-6, "");
        SetSparseRange(hSparseDimuon[i], 1, 2, 15 -1e-6, "");
        SetSparseRange(hSparseDimuon[i], 0, (Int_t)pTLow[i], (Int_t)pTHigh[i] -1e-6, "");

        hSig[i]=(TH1F*)hSparseDimuon[i]->Projection(1);//projection x


        hSig[i]->SetMarkerStyle(2);
        //hSig[i]->Draw("p");
        hSig[i]->GetXaxis()->SetLabelFont(42);
        hSig[i]->GetXaxis()->SetTitle("#it{M}_{#mu^{+}#mu^{-}} (GeV/#it{c}^{2})");
        hSig[i]->GetXaxis()->CenterTitle(true);
        hSig[i]->GetYaxis()->SetLabelFont(42);
        hSig[i]->GetYaxis()->SetTitle("Counts / #Delta #it{M} (#it{c}^{2}/GeV)");
        hSig[i]->GetYaxis()->CenterTitle(true);
        hSig[i]->Sumw2();
        hSig[i]->SetMarkerColor(kRed);
        hpTMixed[i]->SetMarkerColor(kGreen);

        hSig[i]->Add((TH1F*)hpTMixed[i], -1);

        fTest->cd();
        hSig[i]->SetName(Form("pT_%dto%d", (Int_t)pTLow[i], (Int_t)pTHigh[i]));
        hSig[i]->Write();

    }//End of for loop for pT bins================================================
    fTest->cd();

    TH1F* hTotal = (TH1F*)hSig[0]->Clone();
    hTotal->Add(hSig[1]);
    hTotal->Add(hSig[2]);
    hTotal->Add(hSig[3]);
    hTotal->SetTitle("pT_0to12");
    hTotal->SetName("pT_0to12");
    hTotal->Write();


    fTest->Close();

}
