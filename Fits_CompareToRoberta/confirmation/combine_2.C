void combine_2()
{
    TFile* f1 = new TFile("EvMix_020.root");
    TFile* f2 = new TFile("EvMix_2040.root");
    TFile* f3 = new TFile("EvMix_4060.root");
    TFile* f4 = new TFile("EvMix_6090.root");
    TFile* f5 = new TFile("EvMix_090.root");

    TH1D* h1 = (TH1D*)f1->Get("histo");
    TH1D* h2 = (TH1D*)f2->Get("histo");
    TH1D* h3 = (TH1D*)f3->Get("histo");
    TH1D* h4 = (TH1D*)f4->Get("histo");
    TH1D* h5 = (TH1D*)f5->Get("histo");

    TFile* fOutput = new TFile("fRobHistoEvMix.root", "RECREATE");
    fOutput->cd();

    h1->SetNameTitle("Roberta_Cent_0to20", "Roberta_Cent_0to20");
    h1->Write();

    h2->SetNameTitle("Roberta_Cent_20to40", "Roberta_Cent_20to40");
    h2->Write();

    h3->SetNameTitle("Roberta_Cent_40to60", "Roberta_Cent_40to60");
    h3->Write();

    h4->SetNameTitle("Roberta_Cent_60to90", "Roberta_Cent_60to90");
    h4->Write();

    h5->SetNameTitle("Roberta_Cent_0to90", "Roberta_Cent_0to90");
    h5->Write();

    fOutput->Close();

}