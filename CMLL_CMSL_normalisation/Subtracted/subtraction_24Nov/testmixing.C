void testmixing()
{
    TFile* f1 = new TFile("mixed_oqr_24Nov.root");
    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f1->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");


    TH1F* hMixed[100];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixed[6] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixed[7] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixed[8] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixed[9] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixed[1]->Scale(1./hMixed[1]->Integral(hMixed[1]->GetXaxis()->FindBin(2.), hMixed[1]->GetXaxis()->FindBin(8)));
    hMixed[2]->Scale(1./hMixed[2]->Integral(hMixed[2]->GetXaxis()->FindBin(2.), hMixed[2]->GetXaxis()->FindBin(8)));
    hMixed[3]->Scale(1./hMixed[3]->Integral(hMixed[3]->GetXaxis()->FindBin(2.), hMixed[3]->GetXaxis()->FindBin(8)));
    hMixed[4]->Scale(1./hMixed[4]->Integral(hMixed[4]->GetXaxis()->FindBin(2.), hMixed[4]->GetXaxis()->FindBin(8)));


    // hMixed[1]->Divide(hMixed[2]);
    hMixed[3]->Divide(hMixed[4]);
    hMixed[3]->GetYaxis()->SetRangeUser(0.75, 1.25);
    hMixed[3]->GetXaxis()->SetRangeUser(2, 6.5);

    hMixed[3]->SetTitle("InvMass_20to30/InvMass_30to40");
    hMixed[3]->GetXaxis()->SetTitle("#it{M}_{#mu^{+}#mu^{-}} (GeV/#it{c}^{2})");
    hMixed[3]->Draw();
}