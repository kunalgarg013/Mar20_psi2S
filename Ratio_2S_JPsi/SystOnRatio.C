/*void GetMean(TH1* hRatio[6], Double_t* kSum[6], Double_t kMean[6], Int_t counter[6])
{
    for(Int_t i = 0; i<6; i++)
    {
        Double_t kRatio[100] = {0};

       for(Int_t k = 0; k<hRatio[i]->GetNbinsX(); k++)
       {
            kRatio[k] = hRatio[i]->GetBinContent(k+1);

            if(kRatio[k]>0){
                kSum[i] += kRatio[k];

                counter[i]++;
            }

       }
        kMean[i] = kSum[i]/counter[i];

        return kMean[6];
    }

}   */

void SystOnRatio()
{
    TFile* fRatio = new TFile("Ratio_2s_Jpsi.root");
    TH1D* hRatio[6];

    hRatio[0]   = (TH1D*)fRatio->Get("0_10_Ratio");
    hRatio[1]   = (TH1D*)fRatio->Get("10_20_Ratio");
    hRatio[2]   = (TH1D*)fRatio->Get("20_40_Ratio");
    hRatio[3]   = (TH1D*)fRatio->Get("40_60_Ratio");
    hRatio[4]   = (TH1D*)fRatio->Get("60_90_Ratio");
    hRatio[5]   = (TH1D*)fRatio->Get("0_90_Ratio");


    Double_t kSum[6]= {0}, kMean[6]={0};
    Int_t counter[6] = {0};

    for(Int_t i = 0; i<6; i++)
    {
        Double_t kRatio[100] = {0};

       for(Int_t k = 0; k<hRatio[i]->GetNbinsX(); k++)
       {
            kRatio[k] = hRatio[i]->GetBinContent(k+1);

            if(kRatio[k]>0){
                kSum[i] += kRatio[k];

                counter[i]++;
            }

       }
        kMean[i] = kSum[i]/counter[i];
        // cout<<"Mean ="<<kMean[i]<<endl;
    }
    // GetMean(hRatio[6], kSum[6], kMean[6], counter[6]);

    Double_t kRMS[6]={0};
    Double_t kSyst[6]={0};
    Double_t kStat[6] ={0};

    TH1D* hSystOnRatio = new TH1D("SystonRatio", "SystOnRatio", 6, 0, 6);
    TH1D* hStatOnRatio = new TH1D("StatonRatio", "StatOnRatio", 6, 0, 6);
    Double_t centRanges[][2] = {{0,10}, {10,20}, {20,40}, {40,60},{60, 90}, {0,90}}; //Centrality Differential
    TString rangeName;
    std::vector<TString> rangeOfTests;

    for(Int_t p=0; p<6;p++)
    {
        Double_t kInStat[100]={0};
        Double_t kDiff[100]={0};
        Int_t counter[6] ={0};

        for(Int_t q=0; q<hRatio[p]->GetNbinsX();q++)
        {
            if(hRatio[p]->GetBinContent(q+1)>0) {
                kDiff[q] = TMath::Abs(kMean[p] - (hRatio[p]->GetBinContent(q+1)));
                kInStat[q] = hRatio[p]->GetBinError(q+1);
                counter[p]++;

                // cout<<kDiff[q]<<endl;
            }


        }
        rangeName.Form("Cent_%g-%gAndPt_0-12AndRap_-4to-2.5", centRanges[p][0], centRanges[p][1]);
        rangeOfTests.push_back(rangeName);


        kRMS[p]  = TMath::RMS(counter[p], kDiff );
        kStat[p] = TMath::Mean(counter[p], kInStat);
        cout<<kStat[p]<<endl;
        // cout<<"RMS  ="<<kRMS[p]<<"  Mean  ="<<kMean[p]<<endl;
        hSystOnRatio->SetBinContent(p+1, kMean[p]);
        hStatOnRatio->SetBinContent(p+1, kMean[p]);
        hSystOnRatio->SetBinError(p+1, kRMS[p]);
        hStatOnRatio->SetBinError(p+1, kStat[p]);
        hSystOnRatio->GetXaxis()->SetBinLabel(p + 1, rangeName);
        hStatOnRatio->GetXaxis()->SetBinLabel(p + 1, rangeName);

    }

    hSystOnRatio->Draw();

    TFile* fSave = new TFile("systOnRatio.root", "RECREATE");
    fSave->cd();
    hSystOnRatio->Write();
    hStatOnRatio->Write();
    fSave->Close();







}