void compare_ratio(TH1F* h1, TH1F* h2)
{
    h1->Rebin(2);
    h2->Rebin(2);

    h1->Scale(1., "width");
    h2->Scale(1., "width");

    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(3);
    h2->SetMarkerColor(kMagenta);
    h2->SetMarkerStyle(4);
    h2->Divide(h1);
    h2->GetYaxis()->SetRangeUser(0.8,1.25);
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
    legend1->AddEntry(h2,"Old/New","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();


    gPad->SaveAs(Form("Ratios_filetofile/%s.pdf", h1->GetName()));
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

void plots_com()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);
    TFile* fRoberta = new TFile("EvMix_LHCoqr_shared.root");
    TFile* fRobertaNew = new TFile("EvMix_LHCoqr_shared_old.root");

    TH1F* hKBin1 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin0;1");
    TH1F* hKBin2 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin1;1");
    TH1F* hKBin3 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin2;1");
    TH1F* hKBin4 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin3;1");
    TH1F* hKBin5 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin4;1");
    TH1F* hKBin6 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin5;1");
    TH1F* hKBin7 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin6;1");
    TH1F* hKBin8 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin7;1");
    TH1F* hKBin9 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin8;1");

    TH1F* hKNBin1 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin0;1");
    TH1F* hKNBin2 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin1;1");
    TH1F* hKNBin3 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin2;1");
    TH1F* hKNBin4 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin3;1");
    TH1F* hKNBin5 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin4;1");
    TH1F* hKNBin6 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin5;1");
    TH1F* hKNBin7 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin6;1");
    TH1F* hKNBin8 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin7;1");
    TH1F* hKNBin9 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin8;1");






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

    compare_ratio(hKBin1, hKNBin1);
    compare_ratio(hKBin2, hKNBin2);
    compare_ratio(hKBin3, hKNBin3);
    compare_ratio(hKBin4, hKNBin4);
    compare_ratio(hKBin5, hKNBin5);
    compare_ratio(hKBin6, hKNBin6);
    compare_ratio(hKBin7, hKNBin7);
    compare_ratio(hKBin8, hKNBin8);
    compare_ratio(hKBin9, hKNBin9);







}