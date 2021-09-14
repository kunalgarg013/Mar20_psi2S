void plots_compare()
{
    gStyle->SetOptStat(0000);
    // gStyle->SetOptTitle(0);
    TFile* fKunal = new TFile("full_bins.root");
    TFile* fRoberta = new TFile("EvMix_LHC18qr.root");

    TH1F* hKBin1 = (TH1F*)fKunal->Get("Cent_0to10");
    TH1F* hKBin2 = (TH1F*)fKunal->Get("Cent_10to20");
    TH1F* hKBin3 = (TH1F*)fKunal->Get("Cent_20to30");
    TH1F* hKBin4 = (TH1F*)fKunal->Get("Cent_30to40");
    TH1F* hKBin5 = (TH1F*)fKunal->Get("Cent_40to50");
    TH1F* hKBin6 = (TH1F*)fKunal->Get("Cent_50to60");
    TH1F* hKBin7 = (TH1F*)fKunal->Get("Cent_60to70");
    TH1F* hKBin8 = (TH1F*)fKunal->Get("Cent_70to80");
    TH1F* hKBin9 = (TH1F*)fKunal->Get("Cent_80to90");

    TH1F* hRBin1 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin0;1");
    TH1F* hRBin2 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin1;1");
    TH1F* hRBin3 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin2;1");
    TH1F* hRBin4 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin3;1");
    TH1F* hRBin5 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin4;1");
    TH1F* hRBin6 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin5;1");
    TH1F* hRBin7 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin6;1");
    TH1F* hRBin8 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin7;1");
    TH1F* hRBin9 = (TH1F*)fRoberta->Get("hMassOS_MixSubtr_CentrBin8;1");


    hKBin7->Rebin(5);
    hRBin7->Rebin(2);
    hKBin7->SetMarkerColor(kRed);
    hKBin7->SetMarkerStyle(3);
    hRBin7->SetMarkerColor(kMagenta);
    hRBin7->SetMarkerStyle(4);
    hRBin7->Divide(hKBin7);
    hRBin7->GetYaxis()->SetRangeUser(0,2);
    hRBin7->SetTitle("Cent: 60,70");
    hRBin7->Draw();
    // hKBin4->Draw("SAME");

    TLegend *legend1 = new TLegend(0.47,0.4,0.685,0.55,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    // legend1->AddEntry((TObject*)0,"PPlike pT Cent0-10", "C");
    // legend1->AddEntry((TObject*)0,"Cent:(0,10)", "C");
    legend1->AddEntry(hRBin1,"Roberta","p");
    legend1->AddEntry(hKBin1,"Kunal","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    // legend1->Draw();

    TLine* l1 = new TLine(0, 1, 15, 1);
    l1->SetLineColor(kRed);
    l1->Draw("SAME");


}