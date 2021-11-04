void compare_ratio(TH1F* h1, TH1F* h2)
{
    h1->Rebin(5);
    h2->Rebin(2);

    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(3);
    h2->SetMarkerColor(kMagenta);
    h2->SetMarkerStyle(4);
    h2->Divide(h1);
    h2->GetYaxis()->SetRangeUser(0.8,1.25);
    h2->SetTitle(h1->GetName());
     h2->GetXaxis()->SetTitle("M_{#mu#mu}");
    h2->GetYaxis()->SetTitle("Kunal/Roberta");
    h2->Draw();


    TLine* l1 = new TLine(0, 1, 15, 1);
    l1->SetLineColor(kRed);
    l1->Draw("SAME");

    gPad->SaveAs(Form("Ratios/%s.pdf", h2->GetName()));
}

void compare_direct(TH1F* h1, TH1F* h2)
{
    h1->Rebin(5);
    h2->Rebin(2);

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


    gPad->SaveAs(Form("Direct/%s.pdf", h2->GetName()));
}

void plots_compare()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);
    TFile* fKunal = new TFile("extended_CMSL.root");
    TFile* fKunal2 = new TFile("extended_CMLL2.root");
    TFile* fRoberta = new TFile("EvMix_LHCoqr_shared.root");

    TH1F* hKBinMix0 = (TH1F*)fKunal->Get("Cent_0to10;1");
    TH1F* hKBinMix1 = (TH1F*)fKunal->Get("Cent_70to80;1");
    TH1F* hKBinMix2 = (TH1F*)fKunal->Get("Cent_80to90;1");
    TH1F* hKBinRaw0 = (TH1F*)fKunal2->Get("Cent_0to10;1");
    TH1F* hKBinRaw1 = (TH1F*)fKunal2->Get("Cent_70to80;1");
    TH1F* hKBinRaw2 = (TH1F*)fKunal2->Get("Cent_80to90;1");


    TH1F* hRBinMix0 = (TH1F*)fRoberta->Get("hMassOS_Mix_CentrBin0;1");
    TH1F* hRBinMix1 = (TH1F*)fRoberta->Get("hMassOS_Mix_CentrBin7;1");
    TH1F* hRBinMix2 = (TH1F*)fRoberta->Get("hMassOS_Mix_CentrBin8;1");
    TH1F* hRBinRaw0 = (TH1F*)fRoberta->Get("hMassOS_CMULCMLL_CentrBin0;1");
    TH1F* hRBinRaw1 = (TH1F*)fRoberta->Get("hMassOS_CMULCMLL_CentrBin7;1");
    TH1F* hRBinRaw2 = (TH1F*)fRoberta->Get("hMassOS_CMULCMLL_CentrBin8;1");





    compare_ratio(hKBinMix0, hRBinMix0);
    compare_ratio(hKBinMix1, hRBinMix1);
    compare_ratio(hKBinMix2, hRBinMix2);
    compare_ratio(hKBinRaw0, hRBinRaw0);
    compare_ratio(hKBinRaw1, hRBinRaw1);
    compare_ratio(hKBinRaw2, hRBinRaw2);

    // compare_direct(hKBinRaw0, hRBinRaw0);
    // compare_direct(hKBinRaw1, hRBinRaw1);
    // compare_direct(hKBinRaw2, hRBinRaw2);






}