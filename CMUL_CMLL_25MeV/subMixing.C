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

void subMixing()
{
    const Double_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Double_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    const Int_t nCentBins = 6; // no of Centrality bins

    Double_t dPt     = 12.;
    Int_t ptLow      =   0;
    Int_t ptHigh     =  12;


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
    TFile *f1 = new TFile("CMUL_CMLL_25MeV.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");

    TFile* f2                       = new TFile("SigMixed25MeV_OQR.root");

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[100];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixed[6] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixed[7] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixed[8] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixed[9] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent80to90_Pt0to12;1");


    Double_t NormFactor[10] = {0.267964, 0.354365, 0.27309, 0.198865, 0.135347, 0.0852303, 0.0491595, 0.0263443, 0.0126049, 0.00575059};

    /*------------------Reading from Input data for projection--------------------------*/

    THnSparse* hSparseDimuon[100];

    TH1F *hSig[10];

    TFile* fTest = new TFile("Subtracted_oqr_25MeV.root", "RECREATE");
    for(Int_t i=1; i<10; i++)
    {
        hSparseDimuon[i]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
        SetSparseRange(hSparseDimuon[i], 0, 0, 12 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 1, 2., 15 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 2, -4., -2.5 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 3, cLow[i], cHigh[i] - 1e-6, "");


        hSig[i]=(TH1F*)hSparseDimuon[i]->Projection(1);//projection x

        // hSig[i]->Draw();
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
        hMixed[i]->Scale(NormFactor[i]);
        hSig[i]->SetMarkerColor(kRed);
        hMixed[i]->SetMarkerColor(kGreen);



        hSig[i]->Add((TH1F*)hMixed[i], -1);
        hSig[i]->SetTitle(Form("Cent_%dto%d", (Int_t)cLow[i], (Int_t)cHigh[i]));



    }//End of for loop for cent bins================================================
    hSig[0] = (TH1F*)hSig[1]->Clone("fSparseDimuonOpp_proj_1;0");
    hSig[0]->SetNameTitle("Cent_0to90", "Cent_0to90");
    hSig[0]->Add(hSig[2]);
    hSig[0]->Add(hSig[3]);
    hSig[0]->Add(hSig[4]);
    hSig[0]->Add(hSig[5]);
    hSig[0]->Add(hSig[6]);
    hSig[0]->Add(hSig[7]);
    hSig[0]->Add(hSig[8]);
    hSig[0]->Add(hSig[9]);



    for(Int_t l=0; l<10; l++)
    {
        fTest->cd();
        hSig[l]->SetNameTitle(Form("Cent_%dto%d", (Int_t)cLow[l], (Int_t)cHigh[l]), Form("Cent_%dto%d", (Int_t)cLow[l], (Int_t)cHigh[l]));
        hSig[l]->Write();
    }
}
