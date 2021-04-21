void readTHnSparse()
{

    const Double_t cLow[]     = {0,  0,  10, 20, 40, 60};
    const Double_t cHigh[]    = {90, 10, 20, 40, 60, 90};

    const Int_t nCentBins = 6; // no of Centrality bins

    Double_t dPt     = 12.;
    Int_t ptLow      =   0;
    Int_t ptHigh     =  12;

    TFile* f1 = new TFile("updatedCMULAnalysisResults.root");
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    THnSparse* hSparseDimuon     = (THnSparse*)arr->FindObject("fSparseDimuon");


    TH1F *hSig[6];


        Int_t RapMin = hSparseDimuon->GetAxis(4)->FindBin(-4. + 1e-6);
        Int_t RapMax = hSparseDimuon->GetAxis(4)->FindBin(-2.5 - 1e-6);
        Int_t CenMin = hSparseDimuon->GetAxis(5)->FindBin(0  + 1e-6);
        Int_t CenMax = hSparseDimuon->GetAxis(5)->FindBin(90 - 1e-6);

        Int_t MassMin = hSparseDimuon->GetAxis(3)->FindBin(0. + 1e-6);
        Int_t MassMax = hSparseDimuon->GetAxis(3)->FindBin(10.- 1e-6);

        Int_t Plow   = hSparseDimuon->GetAxis(2)->FindBin(0. + 1e-6);
        Int_t Pmax   = hSparseDimuon->GetAxis(2)->FindBin(12. - 1e-6);

        //projection from THnSparse
        // hSparseDimuon->GetAxis(2)->SetRange(Plow, Pmax); //Pt Cuts for Muon 2
        // hSparseDimuon->GetAxis(2)->SetBit(TAxis::kAxisRange);

        hSparseDimuon->GetAxis(4)->SetRange(RapMin, RapMax); //Rapidity cut on Dimuon
        hSparseDimuon->GetAxis(4)->SetBit(TAxis::kAxisRange);

        // hSparseDimuon->GetAxis(5)->SetRange(CenMin, CenMax); //Centrality Range
        // hSparseDimuon->GetAxis(5)->SetBit(TAxis::kAxisRange);

        // hSparseDimuon->GetAxis(3)->SetRange(MassMin, MassMax); //Centrality Range
        // hSparseDimuon->GetAxis(3)->SetBit(TAxis::kAxisRange);

        hSig[1]=(TH1F*)hSparseDimuon->Projection(3);//projection x


        hSig[1]->SetMarkerStyle(2);
        //hSig[i]->Draw("p");
        hSig[1]->GetXaxis()->SetLabelFont(42);
        hSig[1]->GetXaxis()->SetTitle("#it{M}_{#mu^{+}#mu^{-}} (GeV/#it{c}^{2})");
        hSig[1]->GetXaxis()->CenterTitle(true);
        hSig[1]->GetYaxis()->SetLabelFont(42);
        hSig[1]->GetYaxis()->SetTitle("Counts / #Delta #it{M} (#it{c}^{2}/GeV)");
        hSig[1]->GetYaxis()->CenterTitle(true);


        hSig[1]->Sumw2();

        // hSig[1]->Rebin(5);
        hSig[1]->Draw("p");
        // hRob->Rebin(2);
        // cout<<hRob->GetBinWidth(2)<<endl;

        // TFile* fNew = new TFile("thnsparseCuts.root", "UPDATE");
        // fNew->cd();
        // hSig[1]->SetNameTitle("h7", "CMUL_PS_C0_etamu_y_Rabs_C090_matching_pdca");
        // hSig[1]->Write();
        // hRob->SetMarkerColor(kRed);
        // hRob->SetMarkerStyle(4);
        // hRob->SetMarkerSize(1.2);
        // hRob->Draw("SAME, p");
        // hSig[1]->Draw("p");


        TLegend *legend1 = new TLegend(0.47,0.3,0.685,0.55,NULL,"brNDC");
        legend1->SetFillColor(0);
        legend1->SetBorderSize(0);
        legend1->SetTextSize(gStyle->GetTextSize()*0.82);
        // legend1->AddEntry((TObject*)0,, "C");
        // legend1->AddEntry(hRob,"Roberta ","p");
        legend1->AddEntry(hSig[1],"Kunal OS_CMUL7_090_StdPhysSelectionCuts","p");
        legend1->SetTextSize(gStyle->GetTextSize()*0.9);
        // legend1->Draw();



}