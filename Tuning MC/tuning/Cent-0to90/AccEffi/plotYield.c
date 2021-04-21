void plotYield()
{

    Double_t pt[] = {0, 2, 3, 4, 6, 12};
    Int_t    npt  = sizeof(pt) / sizeof(pt[0]) - 1;
    TH1F *hbinraw = new TH1F("hbinraw", "hbinraw", npt, pt);
    TH1F *hbincorrected;
    TGraphErrors *g = new TGraphErrors("sysPsi2s_pT.dat","%lg %lg %lg %lg");
    Int_t npoint = g->GetN();

    for(Int_t ipoint = 0; ipoint < npoint; ipoint++)
    {
        Float_t x  = g->GetX() [ipoint];
        Float_t ex  = g->GetEX() [ipoint];
        Float_t y  = g->GetY() [ipoint];
        Float_t ey = g->GetEY()[ipoint];
        Int_t bin = hbinraw->FindBin(x);
        hbinraw->SetBinContent(bin,y);
        hbinraw->SetBinError  (bin,ey);
    }

    hbinraw->SetMarkerStyle(g->GetMarkerStyle());
    hbinraw->SetMarkerColor(g->GetMarkerColor());
    hbinraw->SetLineColor(g->GetLineColor());


    hbinraw->Sumw2();


    hbinraw->Sumw2();
    hbinraw->SetMarkerStyle(20);
    hbinraw->GetYaxis()->SetTitle("d^{2}N/dp_{T}dy [Gev/c]^{-1}");
    hbinraw->GetYaxis()->SetTitleOffset(1.5);
    hbinraw->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    // hbinraw->GetYaxis()->SetRangeUser(10e-10, 1);
    hbinraw->SetTitle("p_{T} Spectra");


    TFile *tf2 = new TFile("psi2s_pt_yield.root","recreate");
    hbinraw->Write();
}