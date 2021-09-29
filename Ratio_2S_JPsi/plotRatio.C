void plotRatio()
{
    // gStyle->SetErrorX(0);
    TFile* fSaved = new TFile("systOnRatio.root");
    TH1D* hSyst= (TH1D*)fSaved->Get("SystonRatio");
    TH1D* hStat= (TH1D*)fSaved->Get("StatonRatio");

    hStat->SetMarkerStyle(4);
    hStat->SetMarkerColor(kBlue);
    hStat->SetStats(0);
    hStat->GetYaxis()->SetTitle("BR x #psi (2S)/ BR x J/#psi");
    hStat->GetXaxis()->SetTitle("Centrality");
    hStat->GetXaxis()->SetBinLabel(1, "0-20");
    hStat->GetXaxis()->SetBinLabel(2, "20-40");
    hStat->GetXaxis()->SetBinLabel(3, "40-60");
    hStat->GetXaxis()->SetBinLabel(4, "60-90");
    hStat->GetXaxis()->SetBinLabel(5, "0-90");
    hStat->GetYaxis()->SetRangeUser(0,0.03);


    hStat->Draw("E, X0");

    hSyst->SetLineColor(kBlue);
    hSyst->SetMarkerColor(kBlue);
    hSyst->SetMarkerSize(0.01);
    hSyst->SetFillColor(kBlue);
    hSyst->SetFillStyle(0);
    hSyst->Draw("SAME, E2");

    TLatex* t1=new TLatex(0.3,0.8,"ALICE Inclusive J/#psi, #psi(2S) #rightarrow #mu^{+} #mu^{-}");
    t1->SetNDC();
    t1->SetTextSize(0.04);
    t1->Draw();

    TLatex* t2=new TLatex(0.3,0.72,"Pb-Pb #sqrt{s_{NN}} = 5.02 TeV");
    t2->SetNDC();
    t2->SetTextSize(0.04);
    t2->Draw();






}