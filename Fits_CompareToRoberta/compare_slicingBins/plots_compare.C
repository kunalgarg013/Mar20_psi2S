void compare_ratio(TH1F* h1, TH1F* h2)
{
    h1->Rebin(4);
    h2->Rebin(4);

    h1->Scale(1., "width");
    h2->Scale(1., "width");

    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(3);
    h2->SetMarkerColor(kMagenta);
    h2->SetMarkerStyle(4);
    h2->Divide(h1);
    h2->GetYaxis()->SetRangeUser(0.6,1.5);
    h2->GetXaxis()->SetRangeUser(2,6);
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
    legend1->AddEntry(h2,"Larger slices/Slices of 10","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();


    gPad->SaveAs(Form("Flipped/%s.pdf", h1->GetName()));
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
    legend1->AddEntry(h2,"Larger slices","p");
    legend1->AddEntry(h1,"Slices of 10","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();

    gPad->SetLogy();


    gPad->SaveAs(Form("Direct/%s.pdf", h1->GetName()));
}

void plots_compare()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);
    TFile* fKunal = new TFile("Subtracted_oqr.root");
    TFile* fKunalNew = new TFile("MixEvSubtracted_OQR.root");

    TH1F* hKBin1 = (TH1F*)fKunal->Get("Cent_0to20");
    TH1F* hKBin2 = (TH1F*)fKunal->Get("Cent_20to40");
    TH1F* hKBin3 = (TH1F*)fKunal->Get("Cent_40to60");
    TH1F* hKBin4 = (TH1F*)fKunal->Get("Cent_60to90");
    TH1F* hKBin5 = (TH1F*)fKunal->Get("Cent_0to90");

    TH1F* hKNBin1 = (TH1F*)fKunalNew->Get("Cent_0to20");
    TH1F* hKNBin2 = (TH1F*)fKunalNew->Get("Cent_20to40");
    TH1F* hKNBin3 = (TH1F*)fKunalNew->Get("Cent_40to60");
    TH1F* hKNBin4 = (TH1F*)fKunalNew->Get("Cent_60to90");
    TH1F* hKNBin5 = (TH1F*)fKunalNew->Get("Cent_0to90");





   /* compare_direct(hKBin1, hRBin1);
    compare_direct(hKBin2, hRBin2);
    compare_direct(hKBin3, hRBin3);
    compare_direct(hKBin4, hRBin4);
    compare_direct(hKBin5, hRBin5);
    compare_direct(hKBin6, hRBin6);
    compare_direct(hKBin7, hRBin7);
    compare_direct(hKBin8, hRBin8);
    compare_direct(hKBin9, hRBin9);
    compare_direct(hKInt, hRInt);   */

    /*compare_ratio(hKBin1, hKNBin1);
    compare_ratio(hKBin2, hKNBin2);
    compare_ratio(hKBin3, hKNBin3);
    compare_ratio(hKBin4, hKNBin4);
    compare_ratio(hKBin5, hKNBin5); */

    compare_ratio(hKNBin1, hKBin1);
    compare_ratio(hKNBin2, hKBin2);
    compare_ratio(hKNBin3, hKBin3);
    compare_ratio(hKNBin4, hKBin4);
    compare_ratio(hKNBin5, hKBin5);






}