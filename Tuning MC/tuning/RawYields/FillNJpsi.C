class RawDataVsCentrality
{
public:
  RawDataVsCentrality(double centMin, double centMax, std::vector<double> rapBins, std::vector<double> rapValues, std::vector<double> rapErrors, std::vector<double> ptBins, std::vector<double> ptValues, std::vector<double> ptErrors)
  {
    fCentMin = centMin;
    fCentMax = centMax;
    fRapBins = rapBins;
    fRapValues = rapValues;
    fRapErrors = rapErrors;
    fPtBins = ptBins;
    fPtValues = ptValues;
    fPtErrors = ptErrors;
  }
  RawDataVsCentrality()
  {
  }
  double fCentMin;
  double fCentMax;
  std::vector<double> fRapBins;
  std::vector<double> fPtBins;
  std::vector<double> fRapValues;
  std::vector<double> fRapErrors;
  std::vector<double> fPtValues;
  std::vector<double> fPtErrors;

  bool VerifyData()
  {
    if (fCentMax <= fCentMin)
    {
      cout << "Cent-min and cent-max seems to be switched" << endl;
      return false;
    }
    if (fRapBins.size() != fRapValues.size() + 1 || fRapBins.size() != fRapErrors.size() + 1 || fRapBins.size() == 0)
    {
      return false;
    }
    if (fPtBins.size() != fPtValues.size() + 1 || fPtBins.size() != fPtErrors.size() + 1 || fPtBins.size() == 0)
    {
      return false;
    }
    return true;
  }

  TH1F *MakeRapHisto()
  {
    TH1F *histoRapYield = new TH1F(Form("histoRapYield_cent%gto%g", fCentMin, fCentMax), "", fRapBins.size() - 1, &fRapBins[0]);
    for (int iRap = 0; iRap < fRapBins.size() - 1; iRap++)
    {
      Double_t rapidityBinWidth = (fRapBins[iRap + 1] - fRapBins[iRap]);
      histoRapYield->SetBinContent(iRap + 1, (fRapValues[iRap]) / rapidityBinWidth);
      Double_t error = fRapErrors[iRap]; // fRapValues[iRap];
      histoRapYield->SetBinError(iRap + 1, error / rapidityBinWidth);
    }
    return histoRapYield;
  }
  TH1F *MakePtHisto()
  {
    TH1F *histoPtYield = new TH1F(Form("histoPtYield_cent%gto%g", fCentMin, fCentMax), "", fPtBins.size() - 1, &fPtBins[0]);
    for (int iPt = 0; iPt < fPtBins.size() - 1; iPt++)
    {
      Double_t ptidityBinWidth = (fPtBins[iPt + 1] - fPtBins[iPt]);
      histoPtYield->SetBinContent(iPt + 1, (fPtValues[iPt]) / ptidityBinWidth);
      Double_t error = fPtErrors[iPt] ;// fPtValues[iPt];
      histoPtYield->SetBinError(iPt + 1, error / ptidityBinWidth);
    }
    return histoPtYield;
  }
};
void FillNJpsi()
{

  int const numberOfCentralityBins = 5;
  RawDataVsCentrality dataVsCentrality[numberOfCentralityBins];
  /*dataVsCentrality[0] = RawDataVsCentrality(0, 10, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {683, 749, 1070, 790, 275}, {224,	302,	346,	314,	187}, {0, 2, 3, 4, 6, 12}, {1117,	1526,	651,	491,	154}, {489,	296,	197,	156,	85});
  dataVsCentrality[1] = RawDataVsCentrality(10, 20, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {590,	650,	925,	685,	237}, {193,	262,	299,	272,	161}, {0, 2, 3, 4, 6, 12}, {966,	1320,	563,	425,	133}, {423,	256,	170,	135,	74});
  dataVsCentrality[2] = RawDataVsCentrality(20, 40, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {277,	300,	433,	321,	112}, {90, 121,	140,	127,	76}, {0, 2, 3, 4, 6, 12}, {453,	619,	264,	200,	63}, {198,	120,	79,	63,	35});
  dataVsCentrality[3] = RawDataVsCentrality(40, 60, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {156,	172,	245,	182,	64}, {51,	69,	79,	72,	43}, {0, 2, 3, 4, 6, 12}, {257,	351,	150,	113,	35}, {112,	68,	45,	36,	19});
  dataVsCentrality[4] = RawDataVsCentrality(60, 90, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {74,	81,	116,	86,	30}, {24,	32,	37,	34,	20}, {0, 2, 3, 4, 6, 12}, {121,	165,	70,	54,	17}, {53,	32,	21,	17,	9});  */

  dataVsCentrality[0] = RawDataVsCentrality(0, 10, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {1939,  2126,  3036,  2249, 780}, {636,  859,  982,  894, 532}, {0, 2, 3, 4, 6, 12}, {3171,  4331,  1846,  1396,  438}, {1390,  842,  559,  445,  244});
  dataVsCentrality[1] = RawDataVsCentrality(10, 20, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {1939,  2126,  3036,  2249, 780}, {636,  859,  982,  894, 532}, {0, 2, 3, 4, 6, 12}, {3171,  4331,  1846,  1396,  438}, {1390,  842,  559,  445,  244});
  dataVsCentrality[2] = RawDataVsCentrality(20, 40, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {1939,  2126,  3036,  2249, 780}, {636,  859,  982,  894, 532}, {0, 2, 3, 4, 6, 12}, {3171,  4331,  1846,  1396,  438}, {1390,  842,  559,  445,  244});
  dataVsCentrality[3] = RawDataVsCentrality(40, 60, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {1939,  2126,  3036,  2249, 780}, {636,  859,  982,  894, 532}, {0, 2, 3, 4, 6, 12}, {3171,  4331,  1846,  1396,  438}, {1390,  842,  559,  445,  244});
  dataVsCentrality[4] = RawDataVsCentrality(60, 90, {-4., -3.5, -3.25, -3., -2.75, -2.5}, {1939,  2126,  3036,  2249, 780}, {636,  859,  982,  894, 532}, {0, 2, 3, 4, 6, 12}, {3171,  4331,  1846,  1396,  438}, {1390,  842,  559,  445,  244});



  TFile *outputFile = TFile::Open("NJpsi_Raw.root", "recreate");
  outputFile->cd();
  for (int iCent = 0; iCent < numberOfCentralityBins; iCent++)
  {
    if (dataVsCentrality[iCent].VerifyData())
    {
      cout << Form("Filling histograms for centrality %g-%g", dataVsCentrality[iCent].fCentMin, dataVsCentrality[iCent].fCentMax) << endl;

      TH1F *histoVsPt = dataVsCentrality[iCent].MakePtHisto();
      histoVsPt->Write();
      delete histoVsPt;

      TH1F *histoVsRap = dataVsCentrality[iCent].MakeRapHisto();
      histoVsRap->Write();
      delete histoVsRap;
    }
  }

  outputFile->Close();
  delete outputFile;
}
