void emptybins()
{
    TFile* f1 = new TFile("Subtracted_18r_25MeV.root");

    const Double_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Double_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    TH1F* hSubtracted[10];
    TH1F* hMixedSubtracted[10];

    hSubtracted[0] = (TH1F*)f1->Get("Cent_0to90");
    hSubtracted[1] = (TH1F*)f1->Get("Cent_0to10");
    hSubtracted[2] = (TH1F*)f1->Get("Cent_10to20");
    hSubtracted[3] = (TH1F*)f1->Get("Cent_20to30");
    hSubtracted[4] = (TH1F*)f1->Get("Cent_30to40");
    hSubtracted[5] = (TH1F*)f1->Get("Cent_40to50");
    hSubtracted[6] = (TH1F*)f1->Get("Cent_50to60");
    hSubtracted[7] = (TH1F*)f1->Get("Cent_60to70");
    hSubtracted[8] = (TH1F*)f1->Get("Cent_70to80");
    hSubtracted[9] = (TH1F*)f1->Get("Cent_80to90");




    for(Int_t i=0; i<10; i++)
    {
        hMixedSubtracted[i] = new TH1F(Form("Cent_%dto%d", (Int_t)cLow[i], (Int_t)cHigh[i]),"",600, 0, 15);

    }

    // hSubtracted[1]->Draw();

    for(Int_t p=0; p<10; p++)
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

    TFile* f2 = new TFile("ExtendedAxis_18r.root", "RECREATE");

    f2->cd();
    for(Int_t l=0; l<10; l++)
    {
        hMixedSubtracted[l]->Write();
    }
    f2->Close();



}