void plots_compare()
{
    TFile* f2015 = new TFile("2015/full_bins.root");
    TFile* f2018 = new TFile("2018/full_bins.root");

    TH1D* h2015 = (TH1D*)f2015->Get("Cent_0to10");
    TH1D* h2018 = (TH1D*)f2018->Get("Cent_0to10");

    Double_t k2015Area = h2015->Integral(h2015->GetXaxis()->FindBin(2), h2015->GetXaxis()->FindBin(15));
    h2015->Scale(1./k2015Area);

    Double_t k2018Area = h2018->Integral(h2018->GetXaxis()->FindBin(2), h2018->GetXaxis()->FindBin(15));
    h2018->Scale(1./k2018Area);


    h2015->SetMarkerColor(kRed);
    h2015->SetMarkerStyle(3);

    h2018->SetMarkerColor(kBlue);
    h2018->SetMarkerStyle(4);

    h2015->Rebin(2);
    h2018->Rebin(2);

    h2015->Draw("");
    h2018->Draw("SAME");





}