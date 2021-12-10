void combine()
{
    TFile*f1 = new TFile("EvMix_LHCoqr_shared_old.root");
    TH1D* h1 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin0;1");
    TH1D* h2 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin1;1");
    TH1D* h3 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin2;1");
    TH1D* h4 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin3;1");
    TH1D* h5 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin4;1");
    TH1D* h6 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin5;1");
    TH1D* h7 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin6;1");
    TH1D* h8 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin7;1");
    TH1D* h9 = (TH1D*)f1->Get("hMassOS_MixSubtr_CentrBin8;1");


    h1->Sumw2();
    h2->Sumw2();
    h3->Sumw2();
    h4->Sumw2();
    h5->Sumw2();
    h6->Sumw2();
    h7->Sumw2();
    h8->Sumw2();
    h9->Sumw2();



    TFile* fNew = new TFile("MixEvSubtracted_OQR_30July.root", "RECREATE");

    TH1D* h21 = (TH1D*)h1->Clone("Cent_0to20");
    h21->Add(h2);
    h21->SetNameTitle("Cent_0to20", "Cent_0to20");

    TH1D* h22 = (TH1D*)h3->Clone("Cent_20to40");
    h22->Add(h4);
    h22->SetNameTitle("Cent_20to40", "Cent_20to40");

    TH1D* h23 = (TH1D*)h5->Clone("Cent_40to60");
    h23->Add(h6);
    h23->SetNameTitle("Cent_40to60", "Cent_40to60");

    TH1D* h24 = (TH1D*)h7->Clone("Cent_60to90");
    h24->Add(h8);
    h24->Add(h9);
    h24->SetNameTitle("Cent_60to90", "Cent_60to90");

    TH1D* h25 = (TH1D*)h1->Clone("Cent_0to90");
    h25->Add(h2);
    h25->Add(h3);
    h25->Add(h4);
    h25->Add(h5);
    h25->Add(h6);
    h25->Add(h7);
    h25->Add(h8);
    h25->Add(h9);
    h25->SetNameTitle("Cent_0to90", "Cent_0to90");





    fNew->cd();
    h21->Write();
    h22->Write();
    h23->Write();
    h24->Write();
    h25->Write();
}