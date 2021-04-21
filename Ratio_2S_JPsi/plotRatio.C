void plotRatio()
{
    // gStyle->SetErrorX(0);
    TFile* fSaved = new TFile("systOnRatio.root");
    TH1D* hSyst= (TH1D*)fSaved->Get("SystonRatio");
    TH1D* hStat= (TH1D*)fSaved->Get("StatonRatio");

    hStat->SetMarkerStyle(4);
    hStat->SetMarkerColor(kBlue);
    hStat->SetStats(0);
    hStat->GetYaxis()->SetTitle("#psi (2S)/ J/#psi");
    hStat->GetXaxis()->SetTitle("d#eta/dch");
    hStat->GetXaxis()->SetBinLabel(1, "0-10");
    hStat->GetXaxis()->SetBinLabel(2, "10-20");
    hStat->GetXaxis()->SetBinLabel(3, "20-40");
    hStat->GetXaxis()->SetBinLabel(4, "40-60");
    hStat->GetXaxis()->SetBinLabel(5, "60-90");
    hStat->GetXaxis()->SetBinLabel(6, "0-90");
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