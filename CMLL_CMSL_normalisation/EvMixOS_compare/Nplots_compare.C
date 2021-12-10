void compare_ratio(TH1F* h1, TH1F* h2)
{
    h1->Rebin(5);
    h2->Rebin(2);
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
    h2->Draw();


    TLine* l1 = new TLine(0, 1, 15, 1);
    l1->SetLineColor(kRed);
    l1->Draw("SAME");

    TLegend *legend1 = new TLegend(0.65,0.6,0.85,0.8,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    legend1->AddEntry((TObject*)0,Form("%s", h1->GetName()), "C");
    legend1->AddEntry(h2,"Kunal/Roberta","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();

    gPad->SaveAs(Form("Ratios/%s.pdf", h1->GetName()));
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
    legend1->AddEntry(h2,"Roberta Old","p");
    legend1->AddEntry(h1,"Roberta New","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    // legend1->Draw();

    gPad->SetLogy();


    gPad->SaveAs(Form("Direct/%s.pdf", h1->GetName()));
}

void Nplots_compare()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);
    TFile* fKunal = new TFile("ExtendedAxis_oqr_New.root");
    TFile* fRoberta = new TFile("fRobHistoEvMix.root");

    TH1F* hKBin1 = (TH1F*)fKunal->Get("Cent_0to20");
    TH1F* hKBin2 = (TH1F*)fKunal->Get("Cent_20to40");
    TH1F* hKBin3 = (TH1F*)fKunal->Get("Cent_40to60");
    TH1F* hKBin4 = (TH1F*)fKunal->Get("Cent_60to90");
    TH1F* hKBin5 = (TH1F*)fKunal->Get("Cent_0to90");

    TH1F* hRBin1 = (TH1F*)fRoberta->Get("Roberta_Cent_0to20;1");     //0 to 10
    TH1F* hRBin2 = (TH1F*)fRoberta->Get("Roberta_Cent_20to40;1");     // 10 to 20
    TH1F* hRBin3 = (TH1F*)fRoberta->Get("Roberta_Cent_40to60;1");     // 20 to 30
    TH1F* hRBin4 = (TH1F*)fRoberta->Get("Roberta_Cent_60to90;1");     // 30 to 40
    TH1F* hRBin5 = (TH1F*)fRoberta->Get("Roberta_Cent_0to90;1");     // 30 to 40



    // compare_direct(hKBin4, hR60_90);


    cout<<"Kunal  =   "<<hKBin1->GetNbinsX()<<"     Rob =    "<<hRBin1->GetNbinsX()<<endl;
    compare_ratio(hKBin1, hRBin1);
    compare_ratio(hKBin2, hRBin2);
    compare_ratio(hKBin3, hRBin3);
    compare_ratio(hKBin4, hRBin4);
    compare_ratio(hKBin5, hRBin5);







}