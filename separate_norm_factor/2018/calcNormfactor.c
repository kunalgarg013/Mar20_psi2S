void GetHistoSqrt(TH1F *histo) {
  int numberOfBins = histo->GetNbinsX();

  for(int iBin =1;iBin<=numberOfBins;iBin++){
    Double_t binContent = histo->GetBinContent(iBin);
    Double_t binError = histo->GetBinError(iBin);

    histo->SetBinContent(iBin,TMath::Sqrt(binContent));
    histo->SetBinError(iBin,TMath::Sqrt(binContent)*binError/binContent);
  }
}

void calcNormfactor()
{

    gROOT->ProcessLine("gErrorIgnoreLevel = 2002;");
    //    TFile *f1 = new TFile("files/CMLL_AnalysisResults.root");//ok
    TFile *f1 = new TFile("cmll_2018.root");//ok
    TObjArray *arr =(TObjArray*)f1->Get("ListEvent");
    ofstream datnorm("norm_factor_2018.dat");

    const Double_t cLow[]     = {0,  0,  10, 20, 40, 60};
    const Double_t cHigh[]    = {90, 10, 20, 40, 60, 90};

    Double_t dPt     = 12.;
    Int_t ptLow      =   0;
    Int_t ptHigh     =  12;


    //TFile* f2                       = new TFile("files/mixingHisto.root");
    TFile* f2                       = new TFile("cmsl_2018.root");
    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f2->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[6];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to40_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to60_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to90_Pt0to12;1");

    hMixed[0] = (TH1F*)hMixed[1]->Clone("histoInvMass_Cent0to90_Pt0to12;1");
    hMixed[0]->Sumw2();
    hMixed[0]->Add(hMixed[2]);
    hMixed[0]->Add(hMixed[3]);
    hMixed[0]->Add(hMixed[4]);
    hMixed[0]->Add(hMixed[5]);


    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TDirectoryFile* pTPlike         = (TDirectoryFile*)PlikeArr->Get("Pt");
    TDirectoryFile* RapPlike        = (TDirectoryFile*)PlikeArr->Get("Rapidity");

    TH1F* hMixedPlike[6];
    hMixedPlike[1] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedPlike[2] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedPlike[3] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent20to40_Pt0to12;1");
    hMixedPlike[4] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent40to60_Pt0to12;1");
    hMixedPlike[5] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent60to90_Pt0to12;1");

    hMixedPlike[0] = (TH1F*)hMixedPlike[1]->Clone("histoInvMass_Cent0to90_Pt0to12;1");
    hMixedPlike[0]->Sumw2();
    hMixedPlike[0]->Add(hMixedPlike[2]);
    hMixedPlike[0]->Add(hMixedPlike[3]);
    hMixedPlike[0]->Add(hMixedPlike[4]);
    hMixedPlike[0]->Add(hMixedPlike[5]);

    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f2->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TDirectoryFile* pTNlike         = (TDirectoryFile*)NlikeArr->Get("Pt");
    TDirectoryFile* RapNlike        = (TDirectoryFile*)NlikeArr->Get("Rapidity");

    TH1F* hMixedNlike[6];
    hMixedNlike[1] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedNlike[2] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedNlike[3] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent20to40_Pt0to12;1");
    hMixedNlike[4] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent40to60_Pt0to12;1");
    hMixedNlike[5] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent60to90_Pt0to12;1");

    hMixedNlike[0] = (TH1F*)hMixedNlike[1]->Clone("histoInvMass_Cent0to90_Pt0to12;1");
    hMixedNlike[0]->Sumw2();
    hMixedNlike[0]->Add(hMixedNlike[2]);
    hMixedNlike[0]->Add(hMixedNlike[3]);
    hMixedNlike[0]->Add(hMixedNlike[4]);
    hMixedNlike[0]->Add(hMixedNlike[5]);


    THnSparse* hSparseDimuon     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
    THnSparse* hSparseDimuonNeg  = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
    THnSparse* hSparseDimuonPlus = (THnSparse*)arr->FindObject("fSparseDimuonPlus");

    TH1F* hRFactor[6];
    Double_t NormFactor[6];
    TH1F* hRawPlusPlus[6];
    TH1F* hRawMinusMinus[6];
    TH1F* hRaw[6];

    for(Int_t l=0; l<6; l++)
    {


        Int_t CenMinNormN    = hSparseDimuonNeg->GetAxis(3)->FindBin(cLow[l]  + 1e-6);
        Int_t CenMaxNormN    = hSparseDimuonNeg->GetAxis(3)->FindBin(cHigh[l] - 1e-6);
        Int_t PlowNormN      = hSparseDimuonNeg->GetAxis(0)->FindBin(0.   + 1e-6);
        Int_t PmaxNormN      = hSparseDimuonNeg->GetAxis(0)->FindBin(12. - 1e-6);
        Int_t MassMinNormN   = hSparseDimuonNeg->GetAxis(1)->FindBin(0.);
        Int_t MassMaxNormN   = hSparseDimuonNeg->GetAxis(1)->FindBin(10.- 1e-6);
        Int_t RapMinN        = hSparseDimuonNeg->GetAxis(2)->FindBin(-4. + 1e-6);
        Int_t RapMaxN        = hSparseDimuonNeg->GetAxis(2)->FindBin(-2.5 - 1e-6);

        hSparseDimuonNeg->GetAxis(0)->SetRange(PlowNormN, PmaxNormN); //Pt Cuts for Muon 2
        hSparseDimuonNeg->GetAxis(0)->SetBit(TAxis::kAxisRange);
        hSparseDimuonNeg->GetAxis(3)->SetRange(CenMinNormN, CenMaxNormN); //Centrality Range
        hSparseDimuonNeg->GetAxis(3)->SetBit(TAxis::kAxisRange);
        hSparseDimuonNeg->GetAxis(1)->SetRange(MassMinNormN, MassMaxNormN); //InvMass Range
        hSparseDimuonNeg->GetAxis(1)->SetBit(TAxis::kAxisRange);
        hSparseDimuonNeg->GetAxis(2)->SetRange(RapMinN, RapMaxN); //Rapidity cut on Dimuon
        hSparseDimuonNeg->GetAxis(2)->SetBit(TAxis::kAxisRange);


        Int_t CenMinNormP    = hSparseDimuonPlus->GetAxis(3)->FindBin(cLow[l]  + 1e-6);
        Int_t CenMaxNormP    = hSparseDimuonPlus->GetAxis(3)->FindBin(cHigh[l] - 1e-6);
        Int_t PlowNormP      = hSparseDimuonPlus->GetAxis(0)->FindBin(0.   + 1e-6);
        Int_t PmaxNormP      = hSparseDimuonPlus->GetAxis(0)->FindBin(12. - 1e-6);
        Int_t MassMinNormP   = hSparseDimuonPlus->GetAxis(1)->FindBin(0.);
        Int_t MassMaxNormP   = hSparseDimuonPlus->GetAxis(1)->FindBin(10. - 1e-6);
        Int_t RapMinP        = hSparseDimuonPlus->GetAxis(2)->FindBin(-4. + 1e-6);
        Int_t RapMaxP        = hSparseDimuonPlus->GetAxis(2)->FindBin(-2.5 - 1e-6);

        hSparseDimuonPlus->GetAxis(0)->SetRange(PlowNormP, PmaxNormP); //Pt Cuts for Muon 2
        hSparseDimuonPlus->GetAxis(0)->SetBit(TAxis::kAxisRange);
        hSparseDimuonPlus->GetAxis(3)->SetRange(CenMinNormP, CenMaxNormP); //Centrality Range
        hSparseDimuonPlus->GetAxis(3)->SetBit(TAxis::kAxisRange);
        hSparseDimuonPlus->GetAxis(1)->SetRange(MassMinNormP, MassMaxNormP); //InvMass Range
        hSparseDimuonPlus->GetAxis(1)->SetBit(TAxis::kAxisRange);
        hSparseDimuonPlus->GetAxis(2)->SetRange(RapMinP, RapMaxP); //Rapidity cut on Dimuon
        hSparseDimuonPlus->GetAxis(2)->SetBit(TAxis::kAxisRange);

        /*====================================*/
        Int_t CenMinNormUnlike   = hSparseDimuon->GetAxis(3)->FindBin(cLow[l]  + 1e-6);
        Int_t CenMaxNormUnlike   = hSparseDimuon->GetAxis(3)->FindBin(cHigh[l] - 1e-6);
        Int_t PlowNormUnlike     = hSparseDimuon->GetAxis(0)->FindBin(0.   + 1e-6);
        Int_t PmaxNormUnlike     = hSparseDimuon->GetAxis(0)->FindBin(12. - 1e-6);
        Int_t MassMinNormUnlike  = hSparseDimuon->GetAxis(1)->FindBin(0.);
        Int_t MassMaxNormUnlike  = hSparseDimuon->GetAxis(1)->FindBin(10. - 1e-6);
        Int_t RapMinUnlike       = hSparseDimuon->GetAxis(2)->FindBin(-4. + 1e-6);
        Int_t RapMaxUnlike       = hSparseDimuon->GetAxis(2)->FindBin(-2.5 - 1e-6);

        hSparseDimuon->GetAxis(0)->SetRange(PlowNormUnlike, PmaxNormUnlike); //Pt Cuts for Muon 2
        hSparseDimuon->GetAxis(0)->SetBit(TAxis::kAxisRange);
        hSparseDimuon->GetAxis(3)->SetRange(CenMinNormUnlike, CenMaxNormUnlike); //Centrality Range
        hSparseDimuon->GetAxis(3)->SetBit(TAxis::kAxisRange);
        hSparseDimuon->GetAxis(1)->SetRange(MassMinNormUnlike, MassMaxNormUnlike); //InvMass Range
        hSparseDimuon->GetAxis(1)->SetBit(TAxis::kAxisRange);
        hSparseDimuon->GetAxis(2)->SetRange(RapMinUnlike, RapMaxUnlike); //Rapidity cut on Dimuon
        hSparseDimuon->GetAxis(2)->SetBit(TAxis::kAxisRange);
        /*====================================*/

        hRaw[l]            =   (TH1F*)hSparseDimuon->Projection(1);
        hRawPlusPlus[l]    =   (TH1F*)hSparseDimuonPlus->Projection(1);
        hRawMinusMinus[l]  =   (TH1F*)hSparseDimuonNeg->Projection(1);
        hRaw[l]->Sumw2();
        hRawPlusPlus[l]->Sumw2();
        hRawMinusMinus[l]->Sumw2();

        hMixedPlike[l]->Multiply(hMixedNlike[l]);
        GetHistoSqrt(hMixedPlike[l]);
        hMixedPlike[l]->Scale(2.);

        hRFactor[l] = (TH1F*)hMixed[l]->Clone("RFactor");
        hRFactor[l]->Divide(hMixedPlike[l]);

        hRawPlusPlus[l]->Multiply((TH1F*)hRawMinusMinus[l]);

        GetHistoSqrt(hRawPlusPlus[l]);
        hRawPlusPlus[l]->Multiply((TH1F*)hRFactor[l]);
        hRawPlusPlus[l]->Scale(2.);

        int minMassBin = hRaw[l]->FindBin(2);
        int maxMassBin = hRaw[l]->FindBin(8);


        NormFactor[l] = hRawPlusPlus[l]->Integral(minMassBin, maxMassBin)/(hMixed[l]->Integral(minMassBin, maxMassBin));
        //cout<<hRawPlusPlus[l]->Integral(minMassBin, maxMassBin)<<endl;
        datnorm<<cLow[l]<<" "<<cHigh[l]<<"  "<<NormFactor[l]<<endl;
        cout<<"Norm Factor =         "<<NormFactor[l]<<endl;




    }


}