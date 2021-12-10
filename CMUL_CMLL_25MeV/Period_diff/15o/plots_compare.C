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
    h2->GetYaxis()->SetRangeUser(0.6,1.4);
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
    legend1->AddEntry(h2,"Roberta/Kunal","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();


    gPad->SaveAs(Form("Ratios_Subtracted_15o/%s.pdf", h1->GetName()));
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

void plots_compare()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);
    TFile* fRoberta = new TFile("ExtendedAxis_15o.root");
    TFile* fRobertaNew = new TFile("EvMix_LHC15o_shared.root");

    TH1F* hKBin1 = (TH1F*)fRoberta->Get("Cent_0to10");
    TH1F* hKBin2 = (TH1F*)fRoberta->Get("Cent_10to20");
    TH1F* hKBin3 = (TH1F*)fRoberta->Get("Cent_20to30");
    TH1F* hKBin4 = (TH1F*)fRoberta->Get("Cent_30to40");
    TH1F* hKBin5 = (TH1F*)fRoberta->Get("Cent_40to50");
    TH1F* hKBin6 = (TH1F*)fRoberta->Get("Cent_50to60");
    TH1F* hKBin7 = (TH1F*)fRoberta->Get("Cent_60to70");
    TH1F* hKBin8 = (TH1F*)fRoberta->Get("Cent_70to80");
    TH1F* hKBin9 = (TH1F*)fRoberta->Get("Cent_80to90");

    TH1F* hRBin1 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin0");
    TH1F* hRBin2 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin1");
    TH1F* hRBin3 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin2");
    TH1F* hRBin4 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin3");
    TH1F* hRBin5 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin4");
    TH1F* hRBin6 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin5");
    TH1F* hRBin7 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin6");
    TH1F* hRBin8 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin7");
    TH1F* hRBin9 = (TH1F*)fRobertaNew->Get("hMassOS_MixSubtr_CentrBin8");







    /*compare_direct(hKBin1, hRBin1);
    compare_direct(hKBin2, hRBin2);
    compare_direct(hKBin3, hRBin3);
    compare_direct(hKBin4, hRBin4);
    compare_direct(hKBin5, hRBin5); */




    compare_ratio(hKBin1, hRBin1);
    compare_ratio(hKBin2, hRBin2);
    compare_ratio(hKBin3, hRBin3);
    compare_ratio(hKBin4, hRBin4);
    compare_ratio(hKBin5, hRBin5);
    compare_ratio(hKBin6, hRBin6);
    compare_ratio(hKBin7, hRBin7);
    compare_ratio(hKBin8, hRBin8);
    compare_ratio(hKBin9, hRBin9);






}