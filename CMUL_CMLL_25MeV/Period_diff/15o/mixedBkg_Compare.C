void compare_ratio(TH1F* h1, TH1F* h2)
{
    h1->Rebin(2);
    h2->Rebin(2);

    // h1->Scale(1., "width");
    // h2->Scale(1., "width");

    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(3);
    h2->SetMarkerColor(kMagenta);
    h2->SetMarkerStyle(4);
    h2->Divide(h1);
    h2->GetYaxis()->SetRangeUser(0.8,1.25);
    // h2->GetXaxis()->SetRangeUser(2,6);
    h2->SetTitle(h1->GetName());
     h2->GetXaxis()->SetTitle("M_{#mu#mu}");
    h2->GetYaxis()->SetTitle("Ratio");
    h2->Draw();


    TLine* l1 = new TLine(0, 1, 15, 1);
    l1->SetLineColor(kRed);
    l1->Draw("SAME");

    TLegend *legend1 = new TLegend(0.65,0.6,0.85,0.8,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    legend1->AddEntry((TObject*)0,Form("%s", h1->GetName()), "C");
    // legend1->AddEntry(h2,"Slices of 10/Larger slices","p");
    legend1->AddEntry(h2,"Roberta/Kunal","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();


    gPad->SaveAs(Form("Ratios_Mixed_15o/%s.pdf", h1->GetName()));
}

void compare_direct(TH1F* h1, TH1F* h2)
{
    // h1->Rebin(5);
    // h2->Rebin(2);

    h1->Scale(1., "width");
    h2->Scale(1., "width");

    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(3);
    h2->SetMarkerColor(kBlue);
    h2->SetMarkerStyle(4);
    h2->Draw();
    h1->Draw("SAME");

    TLegend *legend1 = new TLegend(0.65,0.6,0.85,0.8,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    legend1->AddEntry((TObject*)0,Form("%s", h1->GetName()), "C");
    legend1->AddEntry(h2,"Roberta","p");
    legend1->AddEntry(h1,"Kunal","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();

    gPad->SetLogy();


    gPad->SaveAs(Form("Direct/%s.pdf", h1->GetName()));
}

void mixedBkg_Compare()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);

    TFile* fRoberta = new TFile("EvMix_LHC15o_shared.root");
    TFile* fKunal = new TFile("Mixed_Extended_15o.root");

    TH1F* hMixed[10];
    TH1F* hRBin[10];

    const Int_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Int_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    Double_t NormFactorK[10] = {0.134712, 0.178025, 0.137014, 0.0998525, 0.0674643, 0.0424527, 0.024451, 0.0131957, 0.00573372, 0.00250122};
    Double_t NormFactorR[10] = {0.1,      0.0893,   0.0640,   0.0447,    0.0295,    0.0183,    0.0104,   0.0056,    0.0024,     0.0010};

     for(Int_t i=1; i<10; i++)
    {
        hMixed[i] = (TH1F*)fKunal->Get(Form("Cent_%ito%i", cLow[i], cHigh[i]));
        hMixed[i]->Scale(NormFactorK[i]);
        hRBin[i]  = (TH1F*)fRoberta->Get(Form("hMassOS_Mix_CentrBin%i", i-1));
        // hRBin[i]->Scale(NormFactorR[i]);
    }

    /*compare_direct(hKBin1, hRBin1);
    compare_direct(hKBin2, hRBin2);
    compare_direct(hKBin3, hRBin3);
    compare_direct(hKBin4, hRBin4);
    compare_direct(hKBin5, hRBin5); */




    compare_ratio(hMixed[1], hRBin[1]);
    compare_ratio(hMixed[2], hRBin[2]);
    compare_ratio(hMixed[3], hRBin[3]);
    compare_ratio(hMixed[4], hRBin[4]);
    compare_ratio(hMixed[5], hRBin[5]);
    compare_ratio(hMixed[6], hRBin[6]);
    compare_ratio(hMixed[7], hRBin[7]);
    compare_ratio(hMixed[8], hRBin[8]);
    compare_ratio(hMixed[9], hRBin[9]);







}