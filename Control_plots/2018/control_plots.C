    void control_plots()
{
    gStyle->SetOptStat(0000);
    const Double_t cLow[]     = {0};
    const Double_t cHigh[]    = {10};

    const Double_t pTLow[]    = {0,  0, 2, 3, 4, 6 };
    const Double_t pTHigh[]   = {12, 2, 3, 4, 6, 12};

    const Double_t rapLow[]   = {-4,   -4,    -3.5, -3.25, -3,  -2.75};
    const Double_t rapHigh[]  = {-2.5, -3.5, -3.25, -3,    -2.75, -2.5};

    TString strRapLow[]  = {"-4",   "-4",     "-3.5",  "-3.25",       "-3",    "-2.75"};
    TString strRapHigh[] = {"-2.5", "-3.5" ,  "-3.25",     "-3",    "-2.75",     "-2.5"};

    TFile* f2                       = new TFile("inSignalRangecmsl2018.root");

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[7];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)pTUnlike->Get("histoPt_Cent0to10_Pt0to12;");
    hMixed[3] = (TH1F*)RapUnlike->Get("histoRapidity_Cent0to10_Pt0to12;");

    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TDirectoryFile* pTPlike         = (TDirectoryFile*)PlikeArr->Get("Pt");
    TDirectoryFile* RapPlike        = (TDirectoryFile*)PlikeArr->Get("Rapidity");

    TH1F* hMixedPlike[7];
    hMixedPlike[1] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedPlike[2] = (TH1F*)pTPlike->Get("histoPt_Cent0to10_Pt0to12;1");
    hMixedPlike[3] = (TH1F*)RapPlike->Get("histoRapidity_Cent0to10_Pt0to12;1");


    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TDirectoryFile* pTNlike         = (TDirectoryFile*)NlikeArr->Get("Pt");
    TDirectoryFile* RapNlike        = (TDirectoryFile*)NlikeArr->Get("Rapidity");

    TH1F* hMixedNlike[7];
    hMixedNlike[1] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedNlike[2] = (TH1F*)pTNlike->Get("histoPt_Cent0to10_Pt0to12;1");
    hMixedNlike[3] = (TH1F*)RapNlike->Get("histoRapidity_Cent0to10_Pt0to12;1");


    TFile *f1 = new TFile("cmll_2018.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");

    Double_t NormFactor = 0.443648;

    // THnSparse* hSparseDimuon     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
    THnSparse* hSparseDimuon     = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonNeg  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonPlus = (THnSparse*)arr->FindObject("fSparseDimuonPlus");

    TH1F *hSig[7];

    Int_t RapMin = hSparseDimuon->GetAxis(2)->FindBin(-4. + 1e-6);
    Int_t RapMax = hSparseDimuon->GetAxis(2)->FindBin(-2.5 - 1e-6);
    Int_t CenMin = hSparseDimuon->GetAxis(3)->FindBin(0  + 1e-6);
    Int_t CenMax = hSparseDimuon->GetAxis(3)->FindBin(10 - 1e-6);

    Int_t MassMin = hSparseDimuon->GetAxis(1)->FindBin(2. + 1e-6);
    Int_t MassMax = hSparseDimuon->GetAxis(1)->FindBin(5.- 1e-6);

    Int_t Plow   = hSparseDimuon->GetAxis(0)->FindBin(0. + 1e-6);
    Int_t Pmax   = hSparseDimuon->GetAxis(0)->FindBin(12. - 1e-6);

    //projection from THnSparse
    // hSparseDimuon->GetAxis(0)->SetRange(Plow, Pmax); //Pt Cuts for Muon 2
    // hSparseDimuon->GetAxis(0)->SetBit(TAxis::kAxisRange);
    // hSparseDimuon->GetAxis(2)->SetRange(RapMin, RapMax); //Rapidity cut on Dimuon
    // hSparseDimuon->GetAxis(2)->SetBit(TAxis::kAxisRange);
    hSparseDimuon->GetAxis(3)->SetRange(CenMin, CenMax); //Centrality Range
    hSparseDimuon->GetAxis(3)->SetBit(TAxis::kAxisRange);

    hSparseDimuon->GetAxis(1)->SetRange(MassMin, MassMax); //Centrality Range
    hSparseDimuon->GetAxis(1)->SetBit(TAxis::kAxisRange);

    hSig[1]=(TH1F*)hSparseDimuon->Projection(1);//InvMass x

    hSig[2]=(TH1F*)hSparseDimuon->Projection(0);// pT

    hSig[3]=(TH1F*)hSparseDimuon->Projection(2);//Rapidity x

    // hSig[1]->Rebin(2);

    // hSig[2]->Rebin(10);
    // hMixed[2]->Rebin(10);

    // hMixed[3]->Rebin(2);

    hMixed[1]->Scale(NormFactor);
    hMixed[2]->Scale(NormFactor);
    hMixed[3]->Scale(NormFactor);

    /*Double_t kMixIntegralP = hMixedPlike[2]->Integral(hMixedPlike[2]->GetXaxis()->FindBin(0.05), hMixedPlike[2]->GetXaxis()->FindBin(12)-1);
    hMixedPlike[2]->Scale(1./kMixIntegralP);
    Double_t kMixIntegralN = hMixedNlike[2]->Integral(hMixedNlike[2]->GetXaxis()->FindBin(0.05), hMixedNlike[2]->GetXaxis()->FindBin(12)-1);
    hMixedNlike[2]->Scale(1./kMixIntegralN);

    Double_t kRawIntegral = hSig[2]->Integral(hSig[2]->GetXaxis()->FindBin(0.05), hSig[2]->GetXaxis()->FindBin(12)-1);
    hSig[2]->Scale(1./kRawIntegral);    */


    Double_t kMixIntegralP = hMixedPlike[3]->Integral(hMixedPlike[3]->GetXaxis()->FindBin(-4.), hMixedPlike[3]->GetXaxis()->FindBin(-2.5)-1);
    hMixedPlike[3]->Scale(1./kMixIntegralP);
    Double_t kMixIntegralN = hMixedNlike[3]->Integral(hMixedNlike[3]->GetXaxis()->FindBin(-4.), hMixedNlike[3]->GetXaxis()->FindBin(-2.5)-1);
    hMixedNlike[3]->Scale(1./kMixIntegralN);

    Double_t kRawIntegral = hSig[3]->Integral(hSig[3]->GetXaxis()->FindBin(-4.), hSig[3]->GetXaxis()->FindBin(-2.5)-1);
    hSig[3]->Scale(1./kRawIntegral);

    // cout<<hMixedPlike[3]->GetXaxis()->FindBin(-2.5)<<endl;




    // hSig[1]->Divide(hMixedNlike[1]);
    // hSig[2]->Divide(hMixed[2]);
    // hSig[3]->Divide(hMixedPlike[3]);
    hSig[3]->Divide(hMixedNlike[3]);


    hSig[2]->SetMarkerStyle(2);
    hSig[2]->SetMarkerColor(kRed);

    hMixed[2]->SetMarkerStyle(3);
    hMixed[2]->SetMarkerColor(kBlue);

    hMixedNlike[2]->SetMarkerStyle(3);
    hMixedNlike[2]->SetMarkerColor(kBlue);

    hMixedPlike[2]->SetMarkerStyle(3);
    hMixedPlike[2]->SetMarkerColor(kBlue);
    hSig[3]->SetMarkerStyle(2);
    hSig[3]->SetMarkerColor(kRed);

    hMixed[3]->SetMarkerStyle(3);
    hMixed[3]->SetMarkerColor(kBlue);

    hMixedNlike[3]->SetMarkerStyle(3);
    hMixedNlike[3]->SetMarkerColor(kBlue);

    hMixedPlike[3]->SetMarkerStyle(3);
    hMixedPlike[3]->SetMarkerColor(kBlue);



    // hSig[1]->GetXaxis()->SetRangeUser(2, 5);
    hSig[3]->GetYaxis()->SetRangeUser(0.5, 1.5);
    hSig[3]->Draw("SAME");
    // hMixedNlike[3]->Draw("SAME");
    // hMixedPlike[3]->Draw("SAME");

    TLegend *legend1 = new TLegend(0.47,0.3,0.685,0.65,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    // legend1->AddEntry((TObject*)0,"PPlike pT Cent0-10", "C");
    legend1->AddEntry((TObject*)0,"NNlike Rapidity Cent0-10", "C");
    legend1->AddEntry(hSig[2],"Raw","p");
    legend1->AddEntry(hMixedNlike[2],"Mix Normalised","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    // legend1->Draw();

    // TFile* fControl = new TFile("fControl_2018.root", "RECREATE");
    // hSig[1]->Write();






}