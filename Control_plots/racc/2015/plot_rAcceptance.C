void plot_rAcceptance()
{
    TFile* f1 = new TFile("rAcceptance_2015.root");
    TH1F* hC0to10 = (TH1F*)f1->Get("Cent_0to10;1");

    TLine* l1 =  new TLine(0, 1, 10, 1);

    hC0to10->GetYaxis()->SetTitle("R^{acc}_{2015}");
    hC0to10->Draw();
    l1->SetLineColor(kRed);
    l1->Draw("SAME");

}