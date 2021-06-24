void compare_dscaling()
{
    TFile* fMoh = new TFile("downscaling_factors_2018.root");

    TFile* fLaure = new TFile("downscaling_laure.root");

    TH1F* hMoh = (TH1F*)fMoh->Get("hDS");
    TH1F* hLaure = (TH1F*)fLaure->Get("hDS");

    /*TH1F* hRatio = (TH1F*)hMoh->Clone("");
    Double_t ratio[500] = {0};
    for(Int_t i=1; i<= hMoh->GetNbinsX();i++)
    {
        if(hMoh->GetBinCenter(i) == hLaure->GetBinCenter(i))
        {ratio[i] = hMoh->GetBinContent(i)/hLaure->GetBinContent(i);}
        hRatio->SetBinContent(i, ratio[i]);
    }
    hRatio->GetYaxis()->SetRangeUser(0.8, 1.2);
    hRatio->Draw(); */

    hMoh->Divide(hLaure);
    hMoh->GetYaxis()->SetRangeUser(0.9, 1.1);
    hMoh->SetMarkerSize(1.2);
    hMoh->SetMarkerStyle(2);
    hMoh->SetMarkerColor(kRed);
    hMoh->Draw("P");

    TLegend *legend1 = new TLegend(0.47,0.3,0.685,0.55,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    // legend1->AddEntry((TObject*)0,"NNlike InvMass Cent0-10", "C");
    legend1->AddEntry(hMoh,"DS Mohammad/ DS Laure","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();

}