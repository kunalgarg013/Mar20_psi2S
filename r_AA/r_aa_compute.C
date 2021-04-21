void r_aa_compute()
{
    TGraphErrors *gPsi2s = new TGraphErrors("sysPsi2s_cent.dat","%lg %lg %lg %lg");
    TGraphErrors *gPsi2s_pT = new TGraphErrors("sysPsi2s_pT.dat","%lg %lg %lg %lg");

    ofstream datsys("Psi2s_Raa.dat");
    ofstream datsys_pT("Psi2s_Raa_pT.dat");


    const Double_t cMean[]    = {45,  5, 15, 30, 50, 75};
    const Double_t cErr[]     = {45,  5,  5, 10, 10, 15};
    const Double_t pTMean[]   = {1,   2.5,  3.5,   5,   9};
    const Double_t pTWidth[]  = {2., 1., 1., 2., 6.};

    Int_t nPsi2s = gPsi2s->GetN();
    Int_t nPsi2s_pT = gPsi2s_pT->GetN();
    Float_t x[100], ex[100], y[100], ey[100];
    Double_t raa_stat[6]= {0, 0, 0, 0, 0, 0};
    Double_t raa_sys_cor[6] = {0, 0, 0, 0, 0, 0};
    Double_t raa_sys_uncor[6] = {0, 0, 0, 0, 0, 0};
    Double_t eff[6]={0, 0, 0, 0, 0, 0};
    Double_t y_aa[6]={0, 0, 0, 0, 0, 0};
    Double_t r_aa[6]={0, 0, 0, 0, 0, 0};
    Double_t raa_sys_int=0;

    Float_t x_pT[100], ex_pT[100], y_pT[100], ey_pT[100];
    Double_t raa_stat_pT[5]= {0, 0, 0, 0, 0};
    Double_t raa_sys_cor_pT[5] = {0, 0, 0, 0, 0};
    Double_t raa_sys_uncor_pT[5] = {0, 0, 0, 0, 0};
    Double_t eff_pT[5]={0, 0, 0, 0, 0};
    Double_t y_aa_pT[5]={0, 0, 0, 0, 0};
    Double_t r_aa_pT[5]={0, 0, 0, 0, 0};

    /* ===================Values needed===================================*/
    //Taa Values
    Double_t Taa_Cent[] = {6.281/1000, 23.26/1000, 14.4/1000, 6.927/1000, 2.049/1000, 0.3071/1000};
    Double_t Taa_Cent_Usys[] = {0.0643/1000, 0.168/1000, 0.126/1000, 0.0909/1000, 0.001303/1000};

    //ppRef vs Centrality
    Double_t ppRef = 0.865;
    Double_t ppRef_Ustat = 0.0635;  //Percentage
    Double_t ppRef_Usys = 0.115;

    Double_t ppRef_pT[] = {0.103, 0.18, 0.064, 0.0415, 0.00853};
    Double_t ppRef_pT_Ustat[] = {0.3145450488, 0.1055555556, 0.2187, 0.3020387015, 0.5121109773};
    Double_t ppRef_pT_Usys[] = {0.1928956524, 0.06666666667, 0.109375, 0.1449857209, 0.1982384155};

    //MC systematics
    Double_t tracking_sys = 0.03;
    Double_t trigger_sys  = 0.03;
    Double_t matching_sys = 0.01;
    Double_t fNorm_sys    = 0.005;
    Double_t mcInput_sys[]= {0.074, 0.077, 0.015, 0.014, 0.004, 0.0101};
    Double_t mcInput_sys_pT[]= {0.0438, 0.0389, 0.02689, 0.055, 0.125, 0.0525};

    Double_t cent_limit_sys[]= {0.057, 0.0014, 0.0014, 0.0022, 0.0022};

    Double_t BR = 0.8;

    Double_t n_mb[] = {51.95E8, 5.77E8, 5.77E8, 11.54E8, 11.54E8, 17.31E8};

    /* ===================Values needed===================================*/
    TFile* fAcc = new TFile("AccEffiValues.root");
    TH1F* hAcc_Cent  = (TH1F*)fAcc->Get("histoAccEffiVsCent");
    TH1F* hAcc_pT  = (TH1F*)fAcc->Get("histoAccEffiVsPt");

    //Raa vs Centrality
    for(Int_t ipoint = 0; ipoint < nPsi2s; ipoint++)
    {
        x[ipoint]   = gPsi2s->GetX() [ipoint];      //Mean Centrality
        ex[ipoint]  = gPsi2s->GetEX() [ipoint];     //Statistical uncertainty
        y[ipoint]   = gPsi2s->GetY() [ipoint];      //Mean Value
        ey[ipoint]  = gPsi2s->GetEY()[ipoint];      //systematic uncertainty
    }

    for(Int_t i=0; i<hAcc_Cent->GetNbinsX(); i++)
    {
        eff[i]= hAcc_Cent->GetBinContent(i+1);
        y_aa[i] = 100*y[i]/(BR*n_mb[i]*eff[i]);
        r_aa[i] = y_aa[i]/(ppRef*Taa_Cent[i]);
    }

    //Statistical and Systematic Uncertainties vs Centrality
    raa_stat[0] = TMath::Sqrt((ex[0]/100)*(ex[0]/100) + ppRef_Ustat*ppRef_Ustat);
    raa_sys_int = TMath::Sqrt((ey[0]/100)*(ey[0]/100)+ mcInput_sys[0]*mcInput_sys[0] +  tracking_sys*tracking_sys+ trigger_sys*trigger_sys + matching_sys*matching_sys+ fNorm_sys*fNorm_sys + cent_limit_sys[0]*cent_limit_sys[0] + Taa_Cent_Usys[0]*Taa_Cent_Usys[0] + ppRef_Usys*ppRef_Usys);

    for(Int_t k=1; k < 6; k++)
    {
        raa_stat[k] = ex[k]/100;
        raa_sys_uncor[k] = TMath::Sqrt((ey[k]/100)*(ey[k]/100) + cent_limit_sys[k]*cent_limit_sys[k] + Taa_Cent_Usys[k]*Taa_Cent_Usys[k]);

        raa_sys_cor[k] = TMath::Sqrt((ey[k]/100)*(ey[k]/100)+ mcInput_sys[k]*mcInput_sys[k] +  tracking_sys*tracking_sys + trigger_sys*trigger_sys + matching_sys*matching_sys + fNorm_sys*fNorm_sys  + ppRef_Usys*ppRef_Usys + ppRef_Ustat*ppRef_Ustat);

        datsys<< cMean[k]<<"    "<<r_aa[k]<<"   "<<raa_stat[k]*r_aa[k]<<"   "<<raa_sys_uncor[k]*r_aa[k]<<"  "<<raa_sys_cor[k]*r_aa[k]<<endl;
    }

    //========================End of Raa vs Centrality==============================



    //Raa vs pT
    for(Int_t ipoint = 0; ipoint < nPsi2s; ipoint++)
    {
        x_pT[ipoint]   = gPsi2s_pT->GetX() [ipoint];      //Mean pT
        ex_pT[ipoint]  = gPsi2s_pT->GetEX() [ipoint];     //Statistical uncertainty
        y_pT[ipoint]   = gPsi2s_pT->GetY() [ipoint];      //Mean Value
        ey_pT[ipoint]  = gPsi2s_pT->GetEY()[ipoint];      //systematic uncertainty
    }

    for(Int_t i=0; i<hAcc_pT->GetNbinsX(); i++)
    {
        eff_pT[i]  = hAcc_pT->GetBinContent(i+1);
        y_aa_pT[i] = 100*y_pT[i]/(BR*n_mb[0]*eff_pT[i]);
        r_aa_pT[i] = y_aa_pT[i]/(ppRef_pT[i]*Taa_Cent[0]*1.5*pTWidth[i]);
    }

    //Statistical and Systematic Uncertainties vs Centrality

    for(Int_t k=0; k < hAcc_pT->GetNbinsX()-1; k++)
    {
        raa_stat_pT[k] = TMath::Sqrt((ex_pT[k]/100)*(ex_pT[k]/100) + ppRef_pT_Ustat[k]*ppRef_pT_Ustat[k]);

        raa_sys_cor_pT[k] = TMath::Sqrt((ey_pT[k]/100)*(ey_pT[k]/100) + cent_limit_sys[0]*cent_limit_sys[0] + Taa_Cent_Usys[0]*Taa_Cent_Usys[0]);

        raa_sys_uncor_pT[k] = TMath::Sqrt((ey_pT[k]/100)*(ey_pT[k]/100)+ mcInput_sys_pT[k]*mcInput_sys_pT[k] +  tracking_sys*tracking_sys + trigger_sys*trigger_sys + matching_sys*matching_sys + ppRef_pT_Usys[k]*ppRef_pT_Usys[k]);

        datsys_pT<< pTMean[k]<<"    "<<r_aa_pT[k]<<"   "<<raa_stat_pT[k]*r_aa_pT[k]<<"   "<<raa_sys_uncor_pT[k]*r_aa_pT[k]<<"  "<<raa_sys_cor_pT[k]*r_aa_pT[k]<<endl;
    }











}