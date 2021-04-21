void plotRaa()
{
    Double_t pt[] = {0, 2, 3, 4, 6, 12};//2011 binning
    const Double_t cent[]    = {0, 10, 20, 40, 60, 90};
    Int_t    ncent  = sizeof(cent) / sizeof(cent[0]) - 1;
    Int_t    npt  = sizeof(pt) / sizeof(pt[0]) - 1;
    // TH1F *hRaa = new TH1F("hRaa", "hRaa", ncent, cent);
    // TH1F *hRaa_stat = new TH1F("hRaaStat", "hRaaStatT", ncent, cent);

    TH1F *hRaa = new TH1F("hRaa", "hRaa", npt, pt);
    TH1F *hRaa_stat = new TH1F("hRaaStat", "hRaaStatT", npt, pt);

    TGraphErrors *g = new TGraphErrors("Psi2s_Raa_pT.dat","%lg %lg %lg %lg");
    Int_t npoint = g->GetN();

    for(Int_t ipoint = 0; ipoint < npoint; ipoint++)
    {
        Float_t x  = g->GetX() [ipoint];
        Float_t ex  = g->GetEX() [ipoint];
        Float_t y  = g->GetY() [ipoint];
        Float_t ey = g->GetEY()[ipoint];
        Int_t bin = hRaa->FindBin(x);
        hRaa->SetBinContent(bin,y);
        hRaa->SetBinError  (bin,ex);

        hRaa_stat->SetBinContent(bin, y);
        hRaa_stat->SetBinError(bin, ey);
    }

    hRaa->SetMarkerStyle(4);
    hRaa->SetMarkerColor(kRed);
    hRaa->SetLineColor(kRed);
    hRaa->Sumw2();

    hRaa->SetMarkerStyle(20);
    hRaa->GetYaxis()->SetTitle("R_{AA}");
    hRaa->GetYaxis()->SetTitleOffset(1.5);
    hRaa->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    // hRaa->GetXaxis()->SetTitle("Centrality");
    hRaa->GetYaxis()->SetRangeUser(10e-10, 1);
    hRaa->SetTitle("");
    hRaa->GetYaxis()->SetRangeUser(0, 1);
    hRaa->Draw("E, X0");

    hRaa_stat->SetLineColor(kRed);
    hRaa_stat->SetMarkerColor(kRed);
    hRaa_stat->SetMarkerSize(0.01);
    hRaa_stat->SetFillColor(kRed);
    hRaa_stat->SetFillStyle(0);
    hRaa_stat->Draw("SAME, E2");

    TLatex* t1=new TLatex(0.3,0.8,"ALICE Inclusive J/#psi, #psi(2S) #rightarrow #mu^{+} #mu^{-}");
    t1->SetNDC();
    t1->SetTextSize(0.04);
    t1->Draw();

    TLatex* t2=new TLatex(0.3,0.72,"Pb-Pb #sqrt{s_{NN}} = 5.02 TeV");
    t2->SetNDC();
    t2->SetTextSize(0.04);
    t2->Draw();



}