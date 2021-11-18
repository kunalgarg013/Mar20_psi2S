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
    const Int_t dpT[]      = {2, 2, 2, 6};
    const Int_t nCentBins = 5; // no of Centrality bins
    const Int_t npTBins = 4;







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

    Double_t NormFactor[10] = {0.272417, 0.360274, 0.277633, 0.202092, 0.137532, 0.0865217, 0.049875, 0.0263832, 0.0121269, 0.00483608};   //Ignore first value of the array.

    TH1F* hMixed[25];
    Int_t i=0;

    for(Int_t k=1; k<10; k++)
    {
        for(Int_t l=0;l<4;l++)
        {
            i= i+1;
            // cout<<i<<endl;
            hMixed[i] = (TH1F*)InvMassUnlike->Get(Form("histoInvMass_Cent%ito%i_Pt%ito%i;1", cLow[k], cHigh[k], pTLow[l], pTHigh[l]));
            cout<<Form("histoInvMass_Cent%ito%i_Pt%ito%i;1", cLow[k], cHigh[k], pTLow[l], pTHigh[l])<<"     "<<i<<endl;
            if(i>0 && i<5)hMixed[i]->Scale(NormFactor[1]);
            if(i>4 && i<9)hMixed[i]->Scale(NormFactor[2]);
            if(i>8 && i<13)hMixed[i]->Scale(NormFactor[3]);
            if(i>12 && i<17)hMixed[i]->Scale(NormFactor[4]);
            if(i>16 && i<21)hMixed[i]->Scale(NormFactor[5]);
            if(i>20 && i<25)hMixed[i]->Scale(NormFactor[6]);
            if(i>24 && i<29)hMixed[i]->Scale(NormFactor[7]);
            if(i>28 && i<33)hMixed[i]->Scale(NormFactor[8]);
            if(i>32 && i<37)hMixed[i]->Scale(NormFactor[9]);
        }
    }

    TH1F* hpTMixed[5];
    for(Int_t m=0; m<4; m++)
    {
        hpTMixed[m] = (TH1F*)hMixed[m+1]->Clone();
        hpTMixed[m]->Add(hMixed[m+5]);
        hpTMixed[m]->Add(hMixed[m+9]);
        hpTMixed[m]->Add(hMixed[m+13]);
        hpTMixed[m]->Add(hMixed[m+17]);
        hpTMixed[m]->Add(hMixed[m+21]);
        hpTMixed[m]->Add(hMixed[m+25]);
        hpTMixed[m]->Add(hMixed[m+29]);
        hpTMixed[m]->Add(hMixed[m+33]);
        fNew->cd();

        hpTMixed[m]->SetName(Form("pT_%dto%d", (Int_t)pTLow[m], (Int_t)pTHigh[m]));
        cout<<Form("pT_%dto%d", (Int_t)pTLow[m], (Int_t)pTHigh[m])<<"     "<<m<<endl;
        hpTMixed[m]->Write();

    }

    TFile *f1 = new TFile("../../CMLL/CMLL_oqr_AnalysisResults.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    THnSparse* hSparseDimuon[100];

    THnSparse* hSparseDimuonNeg  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonPlus = (THnSparse*)arr->FindObject("fSparseDimuonPlus");



    TH1F *hSig[5];

    TFile* fTest = new TFile("subtracted_pT.root", "RECREATE");
    for(Int_t i=0; i<4; i++)
    {
      hSparseDimuon[i]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
      SetSparseRange(hSparseDimuon[i], 2, -4., -2.5 -1e-6, "");
      SetSparseRange(hSparseDimuon[i], 3, 0, 90 -1e-6, "");
      SetSparseRange(hSparseDimuon[i], 1, 2, 15 -1e-6, "");
      SetSparseRange(hSparseDimuon[i], 0, pTLow[i], pTHigh[i] -1e-6, "");



        //Int_t MassMin = hSparseDimuon->GetAxis(1)->FindBin(0.);
        //Int_t MassMax = hSparseDimuon->GetAxis(1)->FindBin(10.- 1e-6);
        // hSparseDimuon->GetAxis(1)->SetRange(MassMin, MassMax); //Centrality Range
        // hSparseDimuon->GetAxis(1)->SetBit(TAxis::kAxisRange);

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



        //c1->SetLogy();

        hSig[i]->SetMarkerColor(kRed);
        hpTMixed[i]->SetMarkerColor(kGreen);


        cout<<hpTMixed[i]->GetName()<<"   MixedName"<<endl;
        hSig[i]->Add((TH1F*)hpTMixed[i], -1);
        hSig[i]->SetTitle(Form("pT_%dto%d", (Int_t)pTLow[i], (Int_t)pTHigh[i]));
        // hSig[i]->GetXaxis()->SetRangeUser(2., 15);

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
