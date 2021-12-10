void emptybins()
{


    const Int_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Int_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    TFile* f1                       = new TFile("SigMixed25MeV_OQR.root");
    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f1->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TH1F* hMixed[100];


    for(Int_t i=1; i<10; i++)
    {
      hMixed[i] = (TH1F*)InvMassUnlike->Get(Form("histoInvMass_Cent%ito%i_Pt0to12;1", cLow[i], cHigh[i]));
    }

    TH1F* hMixedSubtracted[100];


    for(Int_t i=1; i<10; i++)
    {
        hMixedSubtracted[i] = new TH1F(Form("Cent_%dto%d", cLow[i], cHigh[i]),"",600, 0, 15);

    }

    // hSubtracted[1]->Draw();

    for(Int_t p=1; p<10; p++)
    {
        for(Int_t k=1; k<=80; k++)
        {
            hMixedSubtracted[p]->SetBinContent(k, 1);
            hMixedSubtracted[p]->SetBinError(k, 1);
        }

        for(Int_t m=81; m<=600; m++)
        {
            hMixedSubtracted[p]->SetBinContent(m, hMixed[p]->GetBinContent(m-80));
            hMixedSubtracted[p]->SetBinError(m, hMixed[p]->GetBinError(m-80));
        }


    }

    TFile* f2 = new TFile("ExtendedAxis_mixed_25MeV.root", "RECREATE");

    f2->cd();
    for(Int_t l=1; l<10; l++)
    {
        hMixedSubtracted[l]->Write();
    }
    f2->Close();



}