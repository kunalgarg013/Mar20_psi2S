#include <iostream>
#include <iomanip>

void readEvents()
{
    TFile* fOutput = new TFile("outputEvent.root");
    TH1I* h1 = (TH1I*)fOutput->Get("histoCMULEventPerRun");
    ofstream CMULtot("CMULtot.txt");

    for(Int_t i=1;i<=h1->GetNbinsX();i++)
    {
        cout.precision(10);
        std::setprecision(10);
        // if(h1->GetBinContent(i)>0) {cout<<(Int_t)h1->GetBinCenter(i)<<"    "<<h1->GetBinContent(i)<<endl;}
        if(h1->GetBinContent(i)>0) {CMULtot<<(Int_t)h1->GetBinCenter(i)<<","<<(Int_t)h1->GetBinContent(i)<<endl;}
    }
}