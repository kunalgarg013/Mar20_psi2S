void DivideHisto(TH1* hD, TH1* hMC, TH1* hOut)
{
    hOut->GetYaxis()->SetRangeUser(0,10);
    for(Int_t i=1; i<=hD->GetNbinsX();i++)
        {
            // Double_t binwdith = hD->GetBinWidth(i);
            // cout<<binwdith<<endl;
            Double_t datapoint = 0;
            datapoint   =   hD->GetBinContent(i);
            datapoint = datapoint*100;
            Double_t IterationP = 0;
            IterationP  =   hMC->GetBinContent(i);

            datapoint   =   datapoint/IterationP;
            hOut->SetBinContent(i, datapoint);
            hOut->SetBinError(i,0.001);
            // cout<<datapoint<<"  "<<hD->GetBinCenter(i)<<endl;
        }

    hOut->Draw("E, SAME");
}


void ConfigHisto(TH1* hMC, TH1* hOut)
{

    for(Int_t i=1; i<=hMC->GetNbinsX();i++)
        {
            Double_t IterationP = 0;
            IterationP  =   hMC->GetBinContent(i);
            Double_t IterationPErr=0;
            IterationPErr= hMC->GetBinError(i);

            hOut->SetBinContent(i, IterationP);
            hOut->SetBinError(i,IterationPErr);
            // cout<<datapoint<<"  "<<hD->GetBinCenter(i)<<endl;
        }

    // hOut->Draw("E, SAME");
}


void compareData_to_Iterations()
{
    gStyle->Reset("Plain");
    gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
    gStyle->SetOptFit(1111);
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(1111);
    gStyle->SetPalette(1);


    TFile* fData    =   new TFile("psi2s_pt_yield.root");
    TH1D* hData     =   (TH1D*)fData->Get("hbinraw");

    TFile* fIt0     =   new TFile("iter-0/AccEffiValues.root");
    TFile* fIt1     =   new TFile("iter-1/AccEffiValues.root");
    TFile* fIt2     =   new TFile("iter-2/AccEffiValues.root");
    TFile* fIt3     =   new TFile("iter-3/AccEffiValues.root");


    TH1D*  hIt0     =   (TH1D*)fIt0->Get("histoRecPt");
    TH1D*  hIt1     =   (TH1D*)fIt1->Get("histoRecPt");
    TH1D*  hIt2     =   (TH1D*)fIt2->Get("histoRecPt");
    TH1D*  hIt3     =   (TH1D*)fIt3->Get("histoRecPt");


    TH1D* hOut1 = (TH1D*)hData->Clone();
    TH1D* hOut2 = (TH1D*)hData->Clone();
    TH1D* hOut3 = (TH1D*)hData->Clone();


    TH1D* hOut11 = (TH1D*)hData->Clone();
    TH1D* hOut21 = (TH1D*)hData->Clone();
    TH1D* hOut31 = (TH1D*)hData->Clone();


    hOut11->SetMarkerColor(1);
    hOut21->SetMarkerColor(2);
    hOut31->SetMarkerColor(3);


    hOut11->SetMarkerStyle(21);
    hOut21->SetMarkerStyle(23);
    hOut31->SetMarkerStyle(24);


    hOut11->SetMarkerSize(1.2);
    hOut21->SetMarkerSize(1.2);
    hOut31->SetMarkerSize(1.2);


    // DivideHisto(hData, hIt1, hOut1);
    // DivideHisto(hData, hIt2, hOut2);
    // DivideHisto(hData, hIt3, hOut3);
    // DivideHisto(hData, hIt4, hOut4);



    hData->Scale(100);


    hIt1->SetMarkerColor(1);
    hIt2->SetMarkerColor(2);
    hIt3->SetMarkerColor(3);

    hIt1->SetMarkerStyle(21);
    hIt2->SetMarkerStyle(23);
    hIt3->SetMarkerStyle(24);

    hIt1->SetMarkerSize(1.2);
    hIt2->SetMarkerSize(1.2);
    hIt3->SetMarkerSize(1.2);

    ConfigHisto(hIt1, hOut11);
    ConfigHisto(hIt2, hOut21);
    ConfigHisto(hIt3, hOut31);


    hOut11->SetMarkerColor(1);
    hOut21->SetMarkerColor(2);
    hOut31->SetMarkerColor(3);

    hOut11->SetMarkerStyle(21);
    hOut21->SetMarkerStyle(23);
    hOut31->SetMarkerStyle(24);

    hOut11->SetMarkerSize(1.2);
    hOut21->SetMarkerSize(1.2);
    hOut31->SetMarkerSize(1.2);


    // hData->Draw("p");
    hOut11->Draw("SAME");
    hData->Draw("p, SAME");
    hOut21->Draw("SAME");
    hOut31->Draw("SAME");


    /*hIt1->Draw("SAME");
    hIt2->Draw("SAME");
    hIt3->Draw("SAME");
    hIt4->Draw("SAME"); */


    TLegend *legend1 = new TLegend(0.47,0.3,0.685,0.55,NULL,"brNDC");
    legend1->SetFillColor(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(gStyle->GetTextSize()*0.82);
    /*legend1->AddEntry(hOut1,"Data/Iteration 1","p");
    legend1->AddEntry(hOut2,"Data/Iteration 2","p");
    legend1->AddEntry(hOut3,"Data/Iteration 3","p");
    legend1->AddEntry(hOut4,"Data/Iteration 4","p");    */

    legend1->AddEntry(hOut11,"Iteration 1","p");
    legend1->AddEntry(hOut21,"Iteration 2","p");
    legend1->AddEntry(hOut31,"Iteration 3","p");
    legend1->AddEntry(hData,"Data","p");
    legend1->SetTextSize(gStyle->GetTextSize()*0.9);
    legend1->Draw();



}
