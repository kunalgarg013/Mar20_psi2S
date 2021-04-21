void DrawPlots(TH1* h0, TH1* h1, TH1* h2, TH1*h3)
{
    TCanvas *canvas = new TCanvas("dN/dy", "", 1020, 800);
    h0->SetMarkerStyle(20);
    h0->SetMarkerColor(1);
    h0->SetMarkerSize(0.8);


    h1->SetMarkerStyle(21);
    h1->SetMarkerColor(2);
    h1->SetMarkerSize(0.8);

    h2->SetMarkerStyle(22);
    h2->SetMarkerColor(3);
    h2->SetMarkerSize(0.8);

    h3->SetMarkerStyle(23);
    h3->SetMarkerColor(4);
    h3->SetMarkerSize(0.8);

    // h4->SetMarkerStyle(24);
    // h4->SetMarkerColor(8);
    // h4->SetMarkerSize(0.8);


    // h0->GetXaxis()->SetTitle("Centrality");
    h0->GetYaxis()->SetTitle("AccxEff");
    h0->GetYaxis()->SetTitleOffset(1.5);

    h0->Draw("p");
    h1->Draw("SAME");
    h2->Draw("SAME");
    h3->Draw("SAME");
    // h4->Draw("SAME");
    // hCent_fin->Draw("SAME");


    TLegend * leg = new TLegend(.61,.55,.72,.78,"");
    leg->AddEntry(h0, "Iteration 0 ","p");
    leg->AddEntry(h1, "Iteration 1 ","p");
    leg->AddEntry(h2, "Iteration 2 ","p");
    leg->AddEntry(h3, "Iteration 3 ","p");
    // leg->AddEntry(h4, "Iteration 4 ","p");
    // leg->AddEntry(hCent_fin, "Iteration 5 ","p");
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetBorderSize(0);
    leg->SetBorderSize(0);
    leg->Draw("same");

    // canvas->SaveAs()
}


void compute_sys_iterator()
{
    TFile* f0 = new TFile("iter-0/AccEffiValues.root");
    TFile* f1 = new TFile("iter-1/AccEffiValues.root");
    TFile* f2 = new TFile("iter-2/AccEffiValues.root");
    TFile* f3 = new TFile("iter-3/AccEffiValues.root");
    // TFile* f4 = new TFile("iter-4/AccEffiValues.root");
    // TFile* f5 = new TFile("iter-5/AccEffiValues.root");

    TH1F * hRap_init    = (TH1F*)f0->Get("histoAccEffiVsRap");
    TH1F * hpT_init     = (TH1F*)f0->Get("histoAccEffiVsPt");
    // TH1F * hCent_init   = (TH1F*)f0->Get("histoAccEffiVsCent");

    TH1F * hRap_1       = (TH1F*)f1->Get("histoAccEffiVsRap");
    TH1F * hpT_1        = (TH1F*)f1->Get("histoAccEffiVsPt");
    // TH1F * hCent_1      = (TH1F*)f1->Get("histoAccEffiVsCent");

    TH1F * hRap_2       = (TH1F*)f2->Get("histoAccEffiVsRap");
    TH1F * hpT_2        = (TH1F*)f2->Get("histoAccEffiVsPt");
    // TH1F * hCent_2      = (TH1F*)f2->Get("histoAccEffiVsCent");

    TH1F * hRap_3       = (TH1F*)f3->Get("histoAccEffiVsRap");
    TH1F * hpT_3        = (TH1F*)f3->Get("histoAccEffiVsPt");
    // TH1F * hCent_3      = (TH1F*)f3->Get("histoAccEffiVsCent");

    /*TH1F * hRap_4       = (TH1F*)f4->Get("histoAccEffiVsRap");
    TH1F * hpT_4        = (TH1F*)f4->Get("histoAccEffiVsPt");
    TH1F * hCent_4      = (TH1F*)f4->Get("histoAccEffiVsCent");

    TH1F * hRap_fin     = (TH1F*)f5->Get("histoAccEffiVsRap");
    TH1F * hpT_fin      = (TH1F*)f5->Get("histoAccEffiVsPt");
    TH1F * hCent_fin    = (TH1F*)f5->Get("histoAccEffiVsCent"); */



    const Double_t RapMean[]   = {-3.75, -3.375, -3.125, -2.875, -2.625, -3.25};
    const Double_t pTMean[]    = {1, 2.5, 3.5, 5, 9, 6};
    const Double_t cMean[]     = {5, 15, 30, 50, 75, 45};

    ofstream datsysRap("sysPsi2sRap.dat");
    ofstream datsyspT("sysPsi2spT.dat");
    // ofstream datsysCent("sysPsi2sCent.dat");

    Double_t bRapIn[100]={0}, bRapFin[100]={0}, bpTIn[100]={0}, bpTFin[100]={0}, bCentIn[100]={0}, bCentFin[100]={0};
    Double_t diff_Rap[100], diff_pT[100], diff_Cent[100];

    for(Int_t i=0; i<hRap_init->GetNbinsX();i++)
    {
        bRapIn[i]   = hRap_init->GetBinContent(i+1);
        bRapFin[i]  = hRap_3->GetBinContent(i+1);
        Double_t bincenter = hRap_init->GetBinCenter(i+1);
        diff_Rap[i] = 100*(TMath::Abs(bRapIn[i]-bRapFin[i]))/bRapIn[i];

        datsysRap    <<  RapMean[i] << " "<< diff_Rap[i]  << endl;
    }


    for(Int_t i=0; i<hpT_init->GetNbinsX();i++)
    {
        bpTIn[i]   = hpT_init->GetBinContent(i+1);
        bpTFin[i]  = hpT_3->GetBinContent(i+1);
        diff_pT[i] = 100*(TMath::Abs(bpTIn[i]-bpTFin[i]))/bpTIn[i];
        Double_t bincenter = hpT_init->GetBinCenter(i+1);

        datsyspT    <<  pTMean[i] << " "<< diff_pT[i]  << endl;
    }

   /* for(Int_t i=0; i<hCent_init->GetNbinsX();i++)
    {
        bCentIn[i]   = hCent_init->GetBinContent(i+1);
        bCentFin[i]  = hCent_4->GetBinContent(i+1);
        diff_Cent[i] = 100*(TMath::Abs(bCentIn[i]-bCentFin[i]))/bCentIn[i];
        Double_t bincenter = hCent_init->GetBinCenter(i+1);

        datsysCent    <<  cMean[i] << " "<< diff_Cent[i]  << endl;
    }   */

    // hCent_init->GetXaxis()->SetTitle("Centrality");
    // hCent_init->GetYaxis()->SetTitle("AccxEff");

    hpT_init->GetXaxis()->SetTitle("#it{p}_{T}");
    hRap_init->GetXaxis()->SetTitle("y");

    // hCent_init->GetYaxis()->SetRangeUser(0.15, 0.2);
    hpT_init->GetYaxis()->SetRangeUser(0.05, 0.35);
    hRap_init->GetYaxis()->SetRangeUser(0.05, 0.3);

    // DrawPlots(hCent_init, hCent_1, hCent_2, hCent_3, hCent_4);
    DrawPlots(hpT_init, hpT_1, hpT_2, hpT_3);
    // DrawPlots(hRap_init, hRap_1, hRap_2, hRap_3);

}
