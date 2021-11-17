void emptybins()
{
    TFile* f1 = new TFile("OutputCMSL2.root");
    // TFile* f1 = new TFile("Output_CMLL2.root");

    const Double_t cLow[]     = {0, 70, 80};
    const Double_t cHigh[]    = {10, 80, 90};

    TH1F* hSubtracted[10];
    TH1F* hMixedSubtracted[10];

    hSubtracted[0] = (TH1F*)f1->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hSubtracted[1] = (TH1F*)f1->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hSubtracted[2] = (TH1F*)f1->Get("histoInvMass_Cent80to90_Pt0to12;1");

    // hSubtracted[0] = (TH1F*)f1->Get("IM_Unlike_Cent0to10;1");
    // hSubtracted[1] = (TH1F*)f1->Get("IM_Unlike_Cent70to80;1");
    // hSubtracted[2] = (TH1F*)f1->Get("IM_Unlike_Cent80to90;1");



    for(Int_t i=0; i<3; i++)
    {
        hMixedSubtracted[i] = new TH1F(Form("Cent_%dto%d", (Int_t)cLow[i], (Int_t)cHigh[i]),"",1500, 0, 15);

    }

    // hSubtracted[1]->Draw();

    for(Int_t p=0; p<3; p++)
    {
        for(Int_t k=1; k<=200; k++)
        {
            hMixedSubtracted[p]->SetBinContent(k, 1);
            hMixedSubtracted[p]->SetBinError(k, 1);
        }

        for(Int_t m=201; m<=1500; m++)
        {
            hMixedSubtracted[p]->SetBinContent(m, hSubtracted[p]->GetBinContent(m-200));
            hMixedSubtracted[p]->SetBinError(m, hSubtracted[p]->GetBinError(m-200));

            // hMixedSubtracted[p]->SetBinContent(m, hSubtracted[p]->GetBinContent(m));
            // hMixedSubtracted[p]->SetBinError(m, hSubtracted[p]->GetBinError(m));
        }


    }

    TFile* f2 = new TFile("extended_CMSL2.root", "RECREATE");
    // TFile* f2 = new TFile("extended_CMLL2.root", "RECREATE");

    f2->cd();
    for(Int_t l=0; l<3; l++)
    {
        hMixedSubtracted[l]->Write();
    }
    f2->Close();



}