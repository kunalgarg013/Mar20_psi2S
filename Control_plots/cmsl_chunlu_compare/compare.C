void compare()
{
    gStyle->SetOptStat(0000);
    TFile* fKunal  = new TFile("pdca_ResultsHistos_Run297315.root");
    // TDirectoryFile* unlikeArrK = (TDirectoryFile*)fKunal->Get("DimuonHistosPPLike;1");
    // TDirectoryFile* unlikeArrK = (TDirectoryFile*)fKunal->Get("DimuonHistosMMLike;1");
    TDirectoryFile* unlikeArrK = (TDirectoryFile*)fKunal->Get("DimuonHistosUnlike;1");
    TDirectoryFile* InvMassUnlikeK   = (TDirectoryFile*)unlikeArrK->Get("InvMass");


    TFile* fChunlu = new TFile("MixedResultsHistos_Run297315.root");
    // TDirectoryFile* unlikeArrC = (TDirectoryFile*)fChunlu->Get("DimuonHistosPPLike;1");
    // TDirectoryFile* unlikeArrC = (TDirectoryFile*)fChunlu->Get("DimuonHistosMMLike;1");
    TDirectoryFile* unlikeArrC = (TDirectoryFile*)fChunlu->Get("DimuonHistosUnlike;1");
    TDirectoryFile* InvMassUnlikeC   = (TDirectoryFile*)unlikeArrC->Get("InvMass");


    TH1F* hCInvMass1 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt0to0.3;1");
    TH1F* hCInvMass2 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt0.3to1;1");
    TH1F* hCInvMass3 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt1to2;1");
    TH1F* hCInvMass4 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt2to3;1");
    TH1F* hCInvMass5 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt3to4;1");
    TH1F* hCInvMass6 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt4to5;1");
    TH1F* hCInvMass7 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt5to6;1");
    TH1F* hCInvMass8 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt6to7;1");
    TH1F* hCInvMass9 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt7to8;1");
    TH1F* hCInvMass10 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt8to9;1");
    TH1F* hCInvMass11 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt9to10;1");
    TH1F* hCInvMass12 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt10to11;1");
    TH1F* hCInvMass13 = (TH1F*)InvMassUnlikeC->Get("histoInvMass_Cent0to10_Pt11to12;1");

    TH1F* hC_010_012 =  (TH1F*)hCInvMass1->Clone("");
    hC_010_012->Add(hCInvMass2);
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
    hC_010_012->Add(hCInvMass13);



    TH1F* hK_010_012 = (TH1F*)InvMassUnlikeK->Get("histoInvMass_Cent0to10_Pt0to12;1");

    cout<<hC_010_012->GetNbinsX()<<" CL :   K   "<<hK_010_012->GetNbinsX()<<endl;

    hC_010_012->Rebin(2);
    hK_010_012->Rebin(5);

    cout<<hC_010_012->GetNbinsX()<<" CL :   K   "<<hK_010_012->GetNbinsX()<<endl;

    hC_010_012->SetMarkerColor(kRed);
    hC_010_012->SetMarkerStyle(3);
    hC_010_012->SetMarkerSize(1.2);

    hK_010_012->SetMarkerColor(kBlue);
    hK_010_012->SetMarkerStyle(3);

    hC_010_012->Divide(hK_010_012);

    hC_010_012->GetYaxis()->SetRangeUser(0.9, 1.1);

    hC_010_012->Draw("");
    // hK_010_012->Draw("SAME");

    TLegend *legend1 = new TLegend(0.47,0.3,0.685,0.55,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    legend1->AddEntry((TObject*)0,"PPlike InvMass Cent0-10 Pt0-12", "C");
    legend1->AddEntry(hC_010_012,"Chun-Lu","p");
    legend1->AddEntry(hK_010_012,"Kunal","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    // legend1->Draw();













}