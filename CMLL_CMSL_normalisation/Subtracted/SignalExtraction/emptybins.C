void emptybins()
{
    TFile* f1 = new TFile("MixEvSubtracted_OQR.root");

    const Double_t cLow[]     = {0,  0,  20, 40, 60};
    const Double_t cHigh[]    = {90, 20, 40, 60, 90};

    TH1F* hSubtracted[10];
    TH1F* hMixedSubtracted[10];

    hSubtracted[0] = (TH1F*)f1->Get("Cent_0to90");
    hSubtracted[1] = (TH1F*)f1->Get("Cent_0to20");
    hSubtracted[2] = (TH1F*)f1->Get("Cent_20to40");
    hSubtracted[3] = (TH1F*)f1->Get("Cent_40to60");
    hSubtracted[4] = (TH1F*)f1->Get("Cent_60to90");





    for(Int_t i=0; i<5; i++)
    {
        hMixedSubtracted[i] = new TH1F(Form("Cent_%dto%d", (Int_t)cLow[i], (Int_t)cHigh[i]),"",1500, 0, 15);

    }

    // hSubtracted[1]->Draw();

    for(Int_t p=0; p<5; p++)
    {
        for(Int_t k=1; k<=200; k++)
        {
            hMixedSubtracted[p]->SetBinContent(k, 1);
            hMixedSubtracted[p]->SetBinError(k, 1e-6);
        }

        for(Int_t m=201; m<=1500; m++)
        {
            hMixedSubtracted[p]->SetBinContent(m, hSubtracted[p]->GetBinContent(m-200));
            hMixedSubtracted[p]->SetBinError(m, hSubtracted[p]->GetBinError(m-200));
        }


    }

    TFile* f2 = new TFile("ExtendedAxis_oqr_New.root", "RECREATE");

    f2->cd();
    for(Int_t l=0; l<5; l++)
    {
        hMixedSubtracted[l]->Write();
    }
    f2->Close();



}