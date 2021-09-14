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
    TFile *f1 = new TFile("cmll_2018_secondAtt.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");

    TFile* f2                       = new TFile("cent_rob_comp_18qr.root");

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





    Double_t NormFactor[10] = {0.423339, 0.564418, 0.430453, 0.310624, 0.210907, 0.132104, 0.0756397, 0.0392725, 0.0174606, 0.00542014};   //Ignore first value of the array.





    Double_t evnts = 1.64e+8;

    /*------------------Reading from Input data for projection--------------------------*/


    THnSparse* hSparseDimuon     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
    THnSparse* hSparseDimuonNeg  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonPlus = (THnSparse*)arr->FindObject("fSparseDimuonPlus");

    if (!hSparseDimuon) {
    printf("cannot open find THnSparse");
    return;
    }

    TH1F *hSig[10];


    TFile* fTest = new TFile("subtracted_cent_diff.root", "RECREATE");
    for(Int_t i=1; i<10; i++)
    {

        Int_t RapMin = hSparseDimuon->GetAxis(2)->FindBin(-4. + 1e-6);
        Int_t RapMax = hSparseDimuon->GetAxis(2)->FindBin(-2.5 - 1e-6);

        Int_t CenMin = hSparseDimuon->GetAxis(3)->FindBin(cLow[i]  + 1e-6);
        Int_t CenMax = hSparseDimuon->GetAxis(3)->FindBin(cHigh[i] - 1e-6);

        Int_t MassMin = hSparseDimuon->GetAxis(1)->FindBin(2. + 1e-6);
        Int_t MassMax = hSparseDimuon->GetAxis(1)->FindBin(15.- 1e-6);

        Int_t Plow   = hSparseDimuon->GetAxis(0)->FindBin(0. + 1e-6);
        Int_t Pmax   = hSparseDimuon->GetAxis(0)->FindBin(12. - 1e-6);

        //projection from THnSparse
        hSparseDimuon->GetAxis(0)->SetRange(Plow, Pmax); //Pt Cuts for Muon 2
        hSparseDimuon->GetAxis(0)->SetBit(TAxis::kAxisRange);
        hSparseDimuon->GetAxis(2)->SetRange(RapMin, RapMax); //Rapidity cut on Dimuon
        hSparseDimuon->GetAxis(2)->SetBit(TAxis::kAxisRange);
        hSparseDimuon->GetAxis(3)->SetRange(CenMin, CenMax); //Centrality Range
        hSparseDimuon->GetAxis(3)->SetBit(TAxis::kAxisRange);

        hSparseDimuon->GetAxis(1)->SetRange(MassMin, MassMax); //Centrality Range
        hSparseDimuon->GetAxis(1)->SetBit(TAxis::kAxisRange);

        hSig[i]=(TH1F*)hSparseDimuon->Projection(1);//projection x

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
    hSig[0]->SetTitle("Cent_0to90");
    hSig[0]->Add(hSig[2]);
    hSig[0]->Add(hSig[3]);
    hSig[0]->Add(hSig[4]);
    hSig[0]->Add(hSig[5]);
    hSig[0]->Add(hSig[6]);
    hSig[0]->Add(hSig[7]);
    hSig[0]->Add(hSig[8]);
    hSig[0]->Add(hSig[9]);

    // hSig[2]->Draw();

    for(Int_t l=0; l<10; l++)
    {
        fTest->cd();
        hSig[l]->SetName(Form("Cent_%dto%d", (Int_t)cLow[l], (Int_t)cHigh[l]));
        hSig[l]->Write();
    }
}
