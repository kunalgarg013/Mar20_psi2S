#include "Common.C"

void GetFitResults(TH3F *histoFitResults, TString rangeName, TString testName, std::vector<double> &fitResults, std::vector<double> &fitResults_err)
{
  if (!histoFitResults)
  {
    cout << "Fit Results file not found" << endl;
    return;
  }
  int xBinInHistoFitResults = histoFitResults->GetXaxis()->FindFixBin(rangeName.Data());
  if (xBinInHistoFitResults == -1)
  {
    cout << "Range not found" << endl;
    return;
  }
  int yBinInHistoFitResults = histoFitResults->GetYaxis()->FindFixBin(testName.Data());
  if (yBinInHistoFitResults == -1)
  {
    cout << "test not found" << endl;
    return;
  }

  for (Int_t iVariable = 0; iVariable < numberOfFitVariables; iVariable++)
  {
    fitResults.push_back(histoFitResults->GetBinContent(xBinInHistoFitResults, yBinInHistoFitResults, iVariable + 1));
    fitResults_err.push_back(histoFitResults->GetBinError(xBinInHistoFitResults, yBinInHistoFitResults, iVariable + 1));
  }
}

void ratio_2s_jpsi()
{
    TFile* fJPsiEff         = new TFile("Eff_JPsi_Centrality.root");
    TFile* fPsi2SEff        = new TFile("Eff_Psi2S_Centrality.root");

    TH1D* hEffJPsi          = (TH1D*)fJPsiEff->Get("EffVsCentrality_JPsi");
    TH1D* hEffPsi2S         = (TH1D*)fPsi2SEff->Get("EffVsCentrality_Psi2S");



    TFile* fFitResults      = new TFile("FitResults.root");
    TH3F* histoFitResults   = (TH3F*)fFitResults->Get("histoFitResults");

    TH1D* nBins             = histoFitResults->ProjectionX();
    TH1D* nBins2            = histoFitResults->ProjectionY();
    TH1D* nBins3            = histoFitResults->ProjectionZ();


    Double_t BR_JPsi        = 0.59;
    Double_t BR_Psi2S       = 0.8;

    Double_t nJpsi[1000], nPsi2S[1000];
    Double_t nRatio[1000];

    //------------------------Selections-----------------------//
    Double_t rapRanges[][2] = {{-4, -2.5}};
    int numberOfRapRanges = sizeof(rapRanges) / sizeof(rapRanges[0]);

    Double_t centRanges[][2] = {{0,20}, {20,40}, {40,60},{60, 90}, {0,90}}; //Centrality Differential
    // Double_t centRanges[][2] = {{60, 90}}; //Centrality Differential
    int numberOfCentRanges = sizeof(centRanges) / sizeof(centRanges[0]);

    Double_t ptRanges[][2] = {{0,12}};         //No mixing integrated pT
    int numberOfPtRanges = sizeof(ptRanges) / sizeof(ptRanges[0]);
    //---------------------------------------------------------//

    //------------------Fit configurations---------------------//
    Int_t arrayOfBkgdFunctions[] = {kExpoPol2, kDoubleExpo, kVWG2};
    int numberOfBkgdFunctions = sizeof(arrayOfBkgdFunctions) / sizeof(arrayOfBkgdFunctions[0]);

    Int_t arrayOfSigFunctions[] = {kCB21S, kNA601S};
    int numberOfSigFunctions = sizeof(arrayOfSigFunctions) / sizeof(arrayOfSigFunctions[0]);

    Int_t arrayOfTailsSets[] = {kMCGeant3, kData13TeV};
    int numberOfTailsSets = sizeof(arrayOfTailsSets) / sizeof(arrayOfTailsSets[0]);

    Double_t arrayOfPsi2sWidth[] = {1.01,1.05};
    int numberOfPsi2sWidth = sizeof(arrayOfPsi2sWidth) / sizeof(arrayOfPsi2sWidth[0]);

    Double_t arrayOfFitRanges[][2] = {{2.2, 4.5},{2.4,4.7} };
    int numberOfFitRanges = sizeof(arrayOfFitRanges) / sizeof(arrayOfFitRanges[0]);

    std::vector<TString> vectorOfTests;
    std::vector<TString> rangeOfTests;
    TString rangeName;
    TString testName;

    TH1D* hRatio[6];

    for(Int_t i=0; i<numberOfCentRanges; i++)
    {
        hRatio[i] = new TH1D(Form("%g_%g_Ratio", centRanges[i][0], centRanges[i][1]),Form("%g_%g_Ratio", centRanges[i][0], centRanges[i][1]), 50, 0, 50 );
    }

    for (int iCentBin = 0; iCentBin < numberOfCentRanges; iCentBin++)
    {
        Int_t iTest= 1;
        rangeName.Form("Cent_%g-%gAndPt_0-12AndRap_-4to-2.5", centRanges[iCentBin][0], centRanges[iCentBin][1]);
        rangeOfTests.push_back(rangeName);

        for (int iBkgd = 0; iBkgd < numberOfBkgdFunctions; iBkgd++)
        {
            for (int iSig = 0; iSig < numberOfSigFunctions; iSig++)
            {
                for (int iTails = 0; iTails < numberOfTailsSets; iTails++)
                {
                    if ((arrayOfSigFunctions[iSig] == kNA601S) && (arrayOfTailsSets[iTails] == kData13TeV))
                        continue;
                    for (int iFitRange = 0; iFitRange < numberOfFitRanges; iFitRange++)
                    {
                        for (int iPsi2sWidth = 0; iPsi2sWidth < numberOfPsi2sWidth; iPsi2sWidth++)
                        {

                            testName.Form("%s_%s_%s_%gto%g_width%g", arrayFunctionNames[arrayOfBkgdFunctions[iBkgd]].Data(), arrayFunctionNames[arrayOfSigFunctions[iSig]].Data(), arrayTailsNames[arrayOfTailsSets[iTails]].Data(), arrayOfFitRanges[iFitRange][0], arrayOfFitRanges[iFitRange][1], arrayOfPsi2sWidth[iPsi2sWidth]);
                            vectorOfTests.push_back(testName);

                            std::vector<double> testFitResults, testFitResults_err;
                            GetFitResults(histoFitResults, rangeName, testName, testFitResults, testFitResults_err);
                            // cout<<testFitResults[5]<<endl;
                            Int_t numberOfTests = (int)vectorOfTests.size();



                            if(rangeName == rangeOfTests[iCentBin])
                            {
                                if(testFitResults[4] > 2 || testFitResults[6] !=3 || testFitResults[5]!=0)   continue;
                                Double_t relativeErr = TMath::Sqrt( TMath::Power(testFitResults_err[0]/testFitResults[0], 2) + TMath::Power(testFitResults_err[1]/testFitResults[1],2));

                                Double_t AbsErr = relativeErr*testFitResults[1]/testFitResults[0];

                                hRatio[iCentBin]->SetBinContent(iTest+1, testFitResults[1]/testFitResults[0]);
                                hRatio[iCentBin]->SetBinError(iTest+1, AbsErr);
                                hRatio[iCentBin]->GetXaxis()->SetBinLabel(iTest + 1, testName);
                                iTest++;
                            }
                        }
                    }
                }
            }
        }
    }

    //0-90 Eff Jpsi = 0.10088                psi(2s)= 0.1312
    hRatio[5]->Scale(BR_JPsi/BR_Psi2S);
    // hRatio[4]->Scale(0.10088/0.1312);

    for(Int_t i=0; i<4;i++)
    {
        // hRatio[i]->Scale(hEffJPsi->GetBinContent(i+1)/hEffPsi2S->GetBinContent(i+1));
        hRatio[i]-> Scale(BR_JPsi/BR_Psi2S);
    }


    TFile* fSave = new TFile("Ratio_2s_Jpsi_23Sep21.root", "RECREATE");
    fSave->cd();
    hRatio[0]->Write();
    hRatio[1]->Write();
    hRatio[2]->Write();
    hRatio[3]->Write();
    hRatio[4]->Write();
    fSave->Close();








}