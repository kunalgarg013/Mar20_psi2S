void compare()
{
    gStyle->SetOptStat(0000);
    TFile* fKunal  = new TFile("ResultsHistos_Run297315.root");
    // TDirectoryFile* unlikeArrK = (TDirectoryFile*)fKunal->Get("DimuonHistosPPLike;1");
    // TDirectoryFile* unlikeArrK = (TDirectoryFile*)fKunal->Get("DimuonHistosMMLike;1");
    TDirectoryFile* unlikeArrK = (TDirectoryFile*)fKunal->Get("DimuonHistosUnlike;1");
    TDirectoryFile* InvMassUnlikeK   = (TDirectoryFile*)unlikeArrK->Get("InvMass");


    TFile* fRoberta = new TFile("EvMixForComparison_297315_Roberta.root");

    TFile * fKunal2 = new TFile("cmll_histos2.root");

    TH1F* hCInvMass1 = (TH1F*)fRoberta->Get("hMassOS_Mix_CentrBin0;1");
    // TH1F* hCInvMass1 = (TH1F*)fRoberta->Get("hMassMM_Mix_CentrBin0;1;1");
    // TH1F* hCInvMass2 = (TH1F*)fRoberta->Get("histoInvMass_Cent0to10_Pt0.3to1;1");


    TH1F* hC_010_012 =  (TH1F*)hCInvMass1->Clone("");
    /*hC_010_012->Add(hCInvMass2);
    hC_010_012->Add(hCInvMass3);
    hC_010_012->Add(hCInvMass4);
    hC_010_012->Add(hCInvMass5);
    hC_010_012->Add(hCInvMass6);
    hC_010_012->Add(hCInvMass7);
    hC_010_012->Add(hCInvMass8);
    hC_010_012->Add(hCInvMass9);
    hC_010_012->Add(hCInvMass10);
    hC_010_012->Add(hCInvMass11);
    hC_010_012->Add(hCInvMass12);
    hC_010_012->Add(hCInvMass13);   */



    // TH1F* hK_010_012 = (TH1F*)InvMassUnlikeK->Get("histoInvMass_Cent0to10_Pt0to12;1");
    TH1F* hK_010_012 = (TH1F*)fKunal2->Get("h5");

    cout<<hC_010_012->GetNbinsX()<<" CL :   K   "<<hK_010_012->GetNbinsX()<<endl;

    // hC_010_012->Rebin(3);
    // hK_010_012->Rebin(5);

    // cout<<hC_010_012->GetNbinsX()<<" CL :   K   "<<hK_010_012->GetNbinsX()<<endl;

    hC_010_012->SetMarkerColor(kRed);
    hC_010_012->SetMarkerStyle(3);
    hC_010_012->SetMarkerSize(1.2);

    hK_010_012->SetMarkerColor(kBlue);
    hK_010_012->SetMarkerStyle(3);

    hC_010_012->Sumw2();
    hK_010_012->Sumw2();
    // hC_010_012->Divide(hK_010_012);

    // hC_010_012->GetYaxis()->SetRangeUser(0, 1.1);

    // hC_010_012->GetYaxis()->SetRangeUser(0,2);

    hK_010_012->Draw("SAME");
    hC_010_012->Draw("SAME");


    TLegend *legend1 = new TLegend(0.47,0.3,0.685,0.55,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    legend1->AddEntry((TObject*)0,"Unlike InvMass Cent0-10 Pt0-12", "C");
    legend1->AddEntry(hC_010_012,"Roberta","p");
    // legend1->AddEntry(hC_010_012,"Roberta/Kunal","p");
    legend1->AddEntry(hK_010_012,"Kunal","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();













}