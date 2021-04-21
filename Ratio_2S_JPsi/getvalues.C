void getvalues()
{
    TFile* f1 = new TFile("systOnRatio_pT.root");
    TH1D* hStat = (TH1D*)f1->Get("StatonRatio");
    TH1D* hSys = (TH1D*)f1->Get("SystonRatio");

    for(Int_t i = 1; i<=hStat->GetNbinsX();i++)
    {
        cout<<hStat->GetBinContent(i)<<"    "<<hStat->GetBinError(i)<<"     "<<hSys->GetBinError(i)<<endl;

    }
}