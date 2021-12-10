void emptybins_Mixed()
{
   TFile* fKunal = new TFile("Sig25MeV_18r.root");
    TDirectoryFile* unlikeArr       = (TDirectoryFile*)fKunal->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");

    const Int_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Int_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    TH1F* hSubtracted[10];
    TH1F* hMixedSubtracted[10];

   for(Int_t i=1; i<10; i++)
    {
        hSubtracted[i] = (TH1F*)InvMassUnlike->Get(Form("histoInvMass_Cent%ito%i_Pt0to12;1", cLow[i], cHigh[i]));
    }





    for(Int_t i=1; i<10; i++)
    {
        hMixedSubtracted[i] = new TH1F(Form("Cent_%dto%d", (Int_t)cLow[i], (Int_t)cHigh[i]),"",600, 0, 15);

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
            hMixedSubtracted[p]->SetBinContent(m, hSubtracted[p]->GetBinContent(m-80));
            hMixedSubtracted[p]->SetBinError(m, hSubtracted[p]->GetBinError(m-80));
        }


    }

    TFile* f2 = new TFile("Mixed_Extended_18r.root", "RECREATE");

    f2->cd();
    for(Int_t l=1; l<10; l++)
    {
        hMixedSubtracted[l]->Write();
    }
    f2->Close();



}