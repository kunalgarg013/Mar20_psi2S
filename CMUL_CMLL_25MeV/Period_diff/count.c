void count()
{
    TFile* f1 = new TFile("CMUL_CMLL_25MeV.root");
     TObjArray *arr =(TObjArray*)f1->Get("ListEvent");



    const Double_t cLow[]     = {0,  0,  10, 20, 30, 40, 50, 60, 70, 80};
    const Double_t cHigh[]    = {90, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    THnSparse* hSparseDimuon[100];
    THnSparse* hSparseDimuonMM[100];
    THnSparse* hSparseDimuonPP[100];

    TH1F *hSigOpp[10];
    TH1F *hSigMM[10];
    TH1F *hSigPP[10];

    for(Int_t i=1; i<10; i++)
    {
        hSparseDimuon[i]     = (THnSparse*)arr->FindObject("fSparseDimuonOpp");
        hSparseDimuonMM[i]     = (THnSparse*)arr->FindObject("fSparseDimuonNeg");
        hSparseDimuonPP[i]     = (THnSparse*)arr->FindObject("fSparseDimuonPlus");


        SetSparseRange(hSparseDimuon[i], 0, 0, 12 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 1, 2., 15 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 2, -4., -2.5 - 1e-6, "");
        SetSparseRange(hSparseDimuon[i], 3, cLow[i], cHigh[i] - 1e-6, "");

        SetSparseRange(hSparseDimuonMM[i], 0, 0, 12 - 1e-6, "");
        SetSparseRange(hSparseDimuonMM[i], 1, 2., 15 - 1e-6, "");
        SetSparseRange(hSparseDimuonMM[i], 2, -4., -2.5 - 1e-6, "");
        SetSparseRange(hSparseDimuonMM[i], 3, cLow[i], cHigh[i] - 1e-6, "");

        SetSparseRange(hSparseDimuonPP[i], 0, 0, 12 - 1e-6, "");
        SetSparseRange(hSparseDimuonPP[i], 1, 2., 15 - 1e-6, "");
        SetSparseRange(hSparseDimuonPP[i], 2, -4., -2.5 - 1e-6, "");
        SetSparseRange(hSparseDimuonPP[i], 3, cLow[i], cHigh[i] - 1e-6, "");

        hSigOpp[i]=(TH1F*)hSparseDimuon[i]->Projection(1);//projection x
        hSigMM[i]=(TH1F*)hSparseDimuonMM[i]->Projection(1);//projection x
        hSigPP[i]=(TH1F*)hSparseDimuonPP[i]->Projection(1);//projection x




    }
    cout<<hSigOpp[1]->GetEntries()<<endl;;
}