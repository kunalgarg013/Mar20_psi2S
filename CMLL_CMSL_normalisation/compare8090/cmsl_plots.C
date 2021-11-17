void Plots_2018()
{
    TFile* f1 = new TFile("18qr_cmsl.root");

    Double_t NormFactor18[10] = {0.428487, 0.569022, 0.43681, 0.31677, 0.216021, 0.135742, 0.0777926, 0.0404034, 0.0180295, 0.00566868};   //Ignore first value of the array.

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f1->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[100];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixed[6] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixed[7] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixed[8] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixed[9] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixed[0] = (TH1F*)hMixed[1]->Clone("Unlike_Cent0to90_18qr");
    hMixed[0]->Add(hMixed[2]);
    hMixed[0]->Add(hMixed[3]);
    hMixed[0]->Add(hMixed[4]);
    hMixed[0]->Add(hMixed[5]);
    hMixed[0]->Add(hMixed[6]);
    hMixed[0]->Add(hMixed[7]);
    hMixed[0]->Add(hMixed[8]);
    hMixed[0]->Add(hMixed[9]);

    hMixed[20] = (TH1F*)hMixed[1]->Clone("Unlike Cent0to20_18qr");
    hMixed[20]->Add(hMixed[2]);

    hMixed[1]->Scale(NormFactor18[1]);
    hMixed[2]->Scale(NormFactor18[2]);
    hMixed[3]->Scale(NormFactor18[3]);
    hMixed[4]->Scale(NormFactor18[4]);
    hMixed[5]->Scale(NormFactor18[5]);
    hMixed[6]->Scale(NormFactor18[6]);
    hMixed[7]->Scale(NormFactor18[7]);
    hMixed[8]->Scale(NormFactor18[8]);
    hMixed[9]->Scale(NormFactor18[9]);

    hMixed[30] = (TH1F*)hMixed[1]->Clone("Unlike_Cent0to90_18qr_Normalised");
    hMixed[30]->Add(hMixed[2]);
    hMixed[30]->Add(hMixed[3]);
    hMixed[30]->Add(hMixed[4]);
    hMixed[30]->Add(hMixed[5]);
    hMixed[30]->Add(hMixed[6]);
    hMixed[30]->Add(hMixed[7]);
    hMixed[30]->Add(hMixed[8]);
    hMixed[30]->Add(hMixed[9]);

    hMixed[40] = (TH1F*)hMixed[1]->Clone("Unlike Cent0to20_18qr_Normalised");
    hMixed[40]->Add(hMixed[2]);


    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f1->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TDirectoryFile* pTPlike         = (TDirectoryFile*)PlikeArr->Get("Pt");
    TDirectoryFile* RapPlike        = (TDirectoryFile*)PlikeArr->Get("Rapidity");

    TH1F* hMixedPlike[100];
    hMixedPlike[1] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedPlike[2] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedPlike[3] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedPlike[4] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedPlike[5] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedPlike[6] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedPlike[7] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedPlike[8] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedPlike[9] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixedPlike[0] = (TH1F*)hMixedPlike[1]->Clone("PPLike_Cent0to90_18qr");
    hMixedPlike[0]->Add(hMixedPlike[2]);
    hMixedPlike[0]->Add(hMixedPlike[3]);
    hMixedPlike[0]->Add(hMixedPlike[4]);
    hMixedPlike[0]->Add(hMixedPlike[5]);
    hMixedPlike[0]->Add(hMixedPlike[6]);
    hMixedPlike[0]->Add(hMixedPlike[7]);
    hMixedPlike[0]->Add(hMixedPlike[8]);
    hMixedPlike[0]->Add(hMixedPlike[9]);

    hMixedPlike[20] = (TH1F*)hMixedPlike[1]->Clone("PPlike Cent0to20_18qr");
    hMixedPlike[20]->Add(hMixedPlike[2]);



    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f1->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TDirectoryFile* pTNlike         = (TDirectoryFile*)NlikeArr->Get("Pt");
    TDirectoryFile* RapNlike        = (TDirectoryFile*)NlikeArr->Get("Rapidity");

    TH1F* hMixedNlike[100];
    hMixedNlike[1] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedNlike[2] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedNlike[3] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedNlike[4] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedNlike[5] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedNlike[6] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedNlike[7] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedNlike[8] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedNlike[9] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixedNlike[0] = (TH1F*)hMixedNlike[1]->Clone("MMLike_Cent0to90_18qr");
    hMixedNlike[0]->Add(hMixedNlike[2]);
    hMixedNlike[0]->Add(hMixedNlike[3]);
    hMixedNlike[0]->Add(hMixedNlike[4]);
    hMixedNlike[0]->Add(hMixedNlike[5]);
    hMixedNlike[0]->Add(hMixedNlike[6]);
    hMixedNlike[0]->Add(hMixedNlike[7]);
    hMixedNlike[0]->Add(hMixedNlike[8]);
    hMixedNlike[0]->Add(hMixedNlike[9]);

    hMixedNlike[20] = (TH1F*)hMixedNlike[1]->Clone("MMlike Cent0to20_18qr");
    hMixedNlike[20]->Add(hMixedNlike[2]);



    TFile* fOutput = new TFile("OutputCMSL.root", "RECREATE");

    fOutput->cd();
    hMixed[0]->Write();
    hMixed[20]->Write();
    hMixedNlike[0]->Write();
    hMixedNlike[20]->Write();
    hMixedPlike[0]->Write();
    hMixedPlike[20]->Write();
    hMixed[30]->Write();
    hMixed[40]->Write();
    fOutput->Close();





}

void Plots_2015()
{
    TFile* f1 = new TFile("15o_cmsl.root");

    Double_t NormFactor15[10] = {0.428487, 0.199, 0.153, 0.111, 0.075, 0.047, 0.027, 0.015, 0.0065, 0.0028};   //Ignore first value of the array.

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f1->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[100];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixed[6] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixed[7] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixed[8] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixed[9] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixed[0] = (TH1F*)hMixed[1]->Clone("Unlike_Cent0to90_15o");
    hMixed[0]->Add(hMixed[2]);
    hMixed[0]->Add(hMixed[3]);
    hMixed[0]->Add(hMixed[4]);
    hMixed[0]->Add(hMixed[5]);
    hMixed[0]->Add(hMixed[6]);
    hMixed[0]->Add(hMixed[7]);
    hMixed[0]->Add(hMixed[8]);
    hMixed[0]->Add(hMixed[9]);

    hMixed[20] = (TH1F*)hMixed[1]->Clone("Unlike Cent0to20_15o");
    hMixed[20]->Add(hMixed[2]);

    hMixed[1]->Scale(NormFactor15[1]);
    hMixed[2]->Scale(NormFactor15[2]);
    hMixed[3]->Scale(NormFactor15[3]);
    hMixed[4]->Scale(NormFactor15[4]);
    hMixed[5]->Scale(NormFactor15[5]);
    hMixed[6]->Scale(NormFactor15[6]);
    hMixed[7]->Scale(NormFactor15[7]);
    hMixed[8]->Scale(NormFactor15[8]);
    hMixed[9]->Scale(NormFactor15[9]);

    hMixed[30] = (TH1F*)hMixed[1]->Clone("Unlike_Cent0to90_15o_Normalised");
    hMixed[30]->Add(hMixed[2]);
    hMixed[30]->Add(hMixed[3]);
    hMixed[30]->Add(hMixed[4]);
    hMixed[30]->Add(hMixed[5]);
    hMixed[30]->Add(hMixed[6]);
    hMixed[30]->Add(hMixed[7]);
    hMixed[30]->Add(hMixed[8]);
    hMixed[30]->Add(hMixed[9]);

    hMixed[40] = (TH1F*)hMixed[1]->Clone("Unlike Cent0to20_15o_Normalised");
    hMixed[40]->Add(hMixed[2]);

    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f1->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TDirectoryFile* pTPlike         = (TDirectoryFile*)PlikeArr->Get("Pt");
    TDirectoryFile* RapPlike        = (TDirectoryFile*)PlikeArr->Get("Rapidity");

    TH1F* hMixedPlike[100];
    hMixedPlike[1] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedPlike[2] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedPlike[3] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedPlike[4] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedPlike[5] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedPlike[6] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedPlike[7] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedPlike[8] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedPlike[9] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixedPlike[0] = (TH1F*)hMixedPlike[1]->Clone("PPLike_Cent0to90_15o");
    hMixedPlike[0]->Add(hMixedPlike[2]);
    hMixedPlike[0]->Add(hMixedPlike[3]);
    hMixedPlike[0]->Add(hMixedPlike[4]);
    hMixedPlike[0]->Add(hMixedPlike[5]);
    hMixedPlike[0]->Add(hMixedPlike[6]);
    hMixedPlike[0]->Add(hMixedPlike[7]);
    hMixedPlike[0]->Add(hMixedPlike[8]);
    hMixedPlike[0]->Add(hMixedPlike[9]);

    hMixedPlike[20] = (TH1F*)hMixedPlike[1]->Clone("PPlike Cent0to20_15o");
    hMixedPlike[20]->Add(hMixedPlike[2]);



    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f1->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TDirectoryFile* pTNlike         = (TDirectoryFile*)NlikeArr->Get("Pt");
    TDirectoryFile* RapNlike        = (TDirectoryFile*)NlikeArr->Get("Rapidity");

    TH1F* hMixedNlike[100];
    hMixedNlike[1] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedNlike[2] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedNlike[3] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedNlike[4] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedNlike[5] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedNlike[6] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedNlike[7] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedNlike[8] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedNlike[9] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixedNlike[0] = (TH1F*)hMixedNlike[1]->Clone("MMLike_Cent0to90_15o");
    hMixedNlike[0]->Add(hMixedNlike[2]);
    hMixedNlike[0]->Add(hMixedNlike[3]);
    hMixedNlike[0]->Add(hMixedNlike[4]);
    hMixedNlike[0]->Add(hMixedNlike[5]);
    hMixedNlike[0]->Add(hMixedNlike[6]);
    hMixedNlike[0]->Add(hMixedNlike[7]);
    hMixedNlike[0]->Add(hMixedNlike[8]);
    hMixedNlike[0]->Add(hMixedNlike[9]);

    hMixedNlike[20] = (TH1F*)hMixedNlike[1]->Clone("MMlike Cent0to20_15o");
    hMixedNlike[20]->Add(hMixedNlike[2]);



    TFile* fOutput = new TFile("OutputCMSL.root", "UPDATE");

    fOutput->cd();
    hMixed[0]->Write();
    hMixed[20]->Write();
    hMixedNlike[0]->Write();
    hMixedNlike[20]->Write();
    hMixedPlike[0]->Write();
    hMixedPlike[20]->Write();
    hMixed[30]->Write();
    hMixed[40]->Write();
    fOutput->Close();

}

void Plots_combined()
{
    TFile* f1 = new TFile("oqr_cmsl.root");

    Double_t NormFactor[10] = {0.272417, 0.360274, 0.277633, 0.202092, 0.137532, 0.0865217, 0.049875, 0.0263832, 0.0121269, 0.00483608};   //Ignore first value of the array.

    TDirectoryFile* unlikeArr       = (TDirectoryFile*)f1->Get("DimuonHistosUnlike");
    TDirectoryFile* InvMassUnlike   = (TDirectoryFile*)unlikeArr->Get("InvMass");
    TDirectoryFile* pTUnlike        = (TDirectoryFile*)unlikeArr->Get("Pt");
    TDirectoryFile* RapUnlike       = (TDirectoryFile*)unlikeArr->Get("Rapidity");

    TH1F* hMixed[100];
    hMixed[1] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixed[2] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixed[3] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixed[4] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixed[5] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixed[6] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixed[7] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixed[8] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixed[9] = (TH1F*)InvMassUnlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixed[0] = (TH1F*)hMixed[1]->Clone("Unlike_Cent0to90");
    hMixed[0]->Add(hMixed[2]);
    hMixed[0]->Add(hMixed[3]);
    hMixed[0]->Add(hMixed[4]);
    hMixed[0]->Add(hMixed[5]);
    hMixed[0]->Add(hMixed[6]);
    hMixed[0]->Add(hMixed[7]);
    hMixed[0]->Add(hMixed[8]);
    hMixed[0]->Add(hMixed[9]);

    hMixed[20] = (TH1F*)hMixed[1]->Clone("Unlike Cent80to90");
    hMixed[20]->Add(hMixed[2]);

/*    hMixed[1]->Scale(NormFactor[1]);
    hMixed[2]->Scale(NormFactor[2]);
    hMixed[3]->Scale(NormFactor[3]);
    hMixed[4]->Scale(NormFactor[4]);
    hMixed[5]->Scale(NormFactor[5]);
    hMixed[6]->Scale(NormFactor[6]);
    hMixed[7]->Scale(NormFactor[7]);
    hMixed[8]->Scale(NormFactor[8]);
    hMixed[9]->Scale(NormFactor[9]);    */

    hMixed[30] = (TH1F*)hMixed[1]->Clone("Unlike_Cent0to90_Normalised");
    hMixed[30]->Add(hMixed[2]);
    hMixed[30]->Add(hMixed[3]);
    hMixed[30]->Add(hMixed[4]);
    hMixed[30]->Add(hMixed[5]);
    hMixed[30]->Add(hMixed[6]);
    hMixed[30]->Add(hMixed[7]);
    hMixed[30]->Add(hMixed[8]);
    hMixed[30]->Add(hMixed[9]);

    hMixed[40] = (TH1F*)hMixed[1]->Clone("Unlike Cent0to20_Normalised");
    hMixed[40]->Add(hMixed[2]);

    TDirectoryFile* PlikeArr        = (TDirectoryFile*)f1->Get("DimuonHistosPPLike");
    TDirectoryFile* InvMassPlike    = (TDirectoryFile*)PlikeArr->Get("InvMass");
    TDirectoryFile* pTPlike         = (TDirectoryFile*)PlikeArr->Get("Pt");
    TDirectoryFile* RapPlike        = (TDirectoryFile*)PlikeArr->Get("Rapidity");

    TH1F* hMixedPlike[100];
    hMixedPlike[1] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedPlike[2] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedPlike[3] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedPlike[4] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedPlike[5] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedPlike[6] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedPlike[7] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedPlike[8] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedPlike[9] = (TH1F*)InvMassPlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixedPlike[0] = (TH1F*)hMixedPlike[1]->Clone("PPLike_Cent0to90");
    hMixedPlike[0]->Add(hMixedPlike[2]);
    hMixedPlike[0]->Add(hMixedPlike[3]);
    hMixedPlike[0]->Add(hMixedPlike[4]);
    hMixedPlike[0]->Add(hMixedPlike[5]);
    hMixedPlike[0]->Add(hMixedPlike[6]);
    hMixedPlike[0]->Add(hMixedPlike[7]);
    hMixedPlike[0]->Add(hMixedPlike[8]);
    hMixedPlike[0]->Add(hMixedPlike[9]);

    hMixedPlike[20] = (TH1F*)hMixedPlike[1]->Clone("PPlike Cent0to20");
    hMixedPlike[20]->Add(hMixedPlike[2]);



    TDirectoryFile* NlikeArr        = (TDirectoryFile*)f1->Get("DimuonHistosMMLike");
    TDirectoryFile* InvMassNlike    = (TDirectoryFile*)NlikeArr->Get("InvMass");
    TDirectoryFile* pTNlike         = (TDirectoryFile*)NlikeArr->Get("Pt");
    TDirectoryFile* RapNlike        = (TDirectoryFile*)NlikeArr->Get("Rapidity");

    TH1F* hMixedNlike[100];
    hMixedNlike[1] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent0to10_Pt0to12;1");
    hMixedNlike[2] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent10to20_Pt0to12;1");
    hMixedNlike[3] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent20to30_Pt0to12;1");
    hMixedNlike[4] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent30to40_Pt0to12;1");
    hMixedNlike[5] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent40to50_Pt0to12;1");
    hMixedNlike[6] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent50to60_Pt0to12;1");
    hMixedNlike[7] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent60to70_Pt0to12;1");
    hMixedNlike[8] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent70to80_Pt0to12;1");
    hMixedNlike[9] = (TH1F*)InvMassNlike->Get("histoInvMass_Cent80to90_Pt0to12;1");

    hMixedNlike[0] = (TH1F*)hMixedNlike[1]->Clone("MMLike_Cent0to90");
    hMixedNlike[0]->Add(hMixedNlike[2]);
    hMixedNlike[0]->Add(hMixedNlike[3]);
    hMixedNlike[0]->Add(hMixedNlike[4]);
    hMixedNlike[0]->Add(hMixedNlike[5]);
    hMixedNlike[0]->Add(hMixedNlike[6]);
    hMixedNlike[0]->Add(hMixedNlike[7]);
    hMixedNlike[0]->Add(hMixedNlike[8]);
    hMixedNlike[0]->Add(hMixedNlike[9]);

    hMixedNlike[20] = (TH1F*)hMixedNlike[1]->Clone("MMlike Cent0to20");
    hMixedNlike[20]->Add(hMixedNlike[2]);



    TFile* fOutput = new TFile("OutputCMSL2.root", "RECREATE");

    fOutput->cd();
    hMixed[1]->Write();
    hMixed[8]->Write();
    hMixed[9]->Write();
    fOutput->Close();

}

void cmsl_plots()
{
    // Plots_2018();
    // Plots_2015();
    Plots_combined();


}