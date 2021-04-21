void pT_plotRatio()
{
    // gStyle->SetErrorX(0);
    TFile* fSaved = new TFile("systOnRatio_pT.root");
    TH1D* hSyst= (TH1D*)fSaved->Get("SystonRatio");
    TH1D* hStat= (TH1D*)fSaved->Get("StatonRatio");

    hStat->SetMarkerStyle(4);
    hStat->SetMarkerColor(kBlue);
    hStat->SetStats(0);
    hStat->GetYaxis()->SetTitle("#psi (2S)/ J/#psi");
    hStat->GetXaxis()->SetTitle("dp_{T}");
    hStat->GetXaxis()->SetBinLabel(1, "0.3-2");
    hStat->GetXaxis()->SetBinLabel(2, "2-3");
    hStat->GetXaxis()->SetBinLabel(3, "3-4");
    hStat->GetXaxis()->SetBinLabel(4, "4-6");
    hStat->GetXaxis()->SetBinLabel(5, "6-12");
    hStat->GetXaxis()->SetBinLabel(6, "0.3-12");
    hStat->GetYaxis()->SetRangeUser(0,0.03);


    hStat->Draw("E, X0");

    hSyst->SetLineColor(kBlue);
    hSyst->SetMarkerColor(kBlue);
    hSyst->SetMarkerSize(0.01);
    hSyst->SetFillColor(kBlue);
    hSyst->SetFillStyle(0);
    hSyst->Draw("SAME, E2");

    TLatex* t1=new TLatex(0.3,0.83,"ALICE Inclusive J/#psi, #psi(2S) #rightarrow #mu^{+} #mu^{-}");
    t1->SetNDC();
    t1->SetTextSize(0.04);
    t1->Draw();

    TLatex* t2=new TLatex(0.3,0.75,"Pb-Pb #sqrt{s_{NN}} = 5.02 TeV");
    t2->SetNDC();
    t2->SetTextSize(0.04);
    t2->Draw();






}