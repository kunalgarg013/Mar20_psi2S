void control_plots()
{
    const Double_t cLow[]     = {0,  0,  10, 20, 40, 60};
    const Double_t cHigh[]    = {90, 10, 20, 40, 60, 90};

    const Double_t pTLow[]    = {0,  0, 2, 3, 4, 6 };
    const Double_t pTHigh[]   = {12, 2, 3, 4, 6, 12};

    const Double_t rapLow[]   = {-4,   -4,    -3.5, -3.25, -3,  -2.75};
    const Double_t rapHigh[]  = {-2.5, -3.5, -3.25, -3,    -2.75, -2.5};

    TString strRapLow[]  = {"-4",   "-4",     "-3.5",  "-3.25",       "-3",    "-2.75"};
    TString strRapHigh[] = {"-2.5", "-3.5" ,  "-3.25",     "-3",    "-2.75",     "-2.5"};


    TFile *f1 = new TFile("updatedCMULAnalysisResults.root");
    THnSparse* hSparseDimuon = (THnSparse*)f1->Get("hSparseDimuonLight");


}