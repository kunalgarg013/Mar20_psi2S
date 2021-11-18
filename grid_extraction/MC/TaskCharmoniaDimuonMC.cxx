/**************************************************************************
* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
*                                                                        *
* Author: The ALICE Off-line Project.                                    *
* Contributors are mentioned in the code where appropriate.              *
*                                                                        *
* Permission to use, copy, modify and distribute this software and its   *
* documentation strictly for non-commercial purposes is hereby granted   *
* without fee, provided that the above copyright notice appears in all   *
* copies and that both the copyright notice and this permission notice   *
* appear in the supporting documentation. The authors make no claims     *
* about the suitability of this software for any purpose. It is          *
* provided "as is" without express or implied warranty.                  *
**************************************************************************/

//include root libraries
#include <iostream>
#include <TCanvas.h>
#include <TList.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TChain.h>
#include "TMath.h"
#include <TObjArray.h>
#include "THnSparse.h"
#include <TClonesArray.h>
//include aliroot libraries
#include "AliLog.h"
#include "AliAnalysisManager.h"
#include "AliAODv0.h"
#include "AliVEvent.h"
#include "AliESDEvent.h"
#include "AliAODEvent.h"
#include "AliVVZERO.h"
#include "AliESDVZERO.h"
#include "AliAODVZERO.h"
#include "AliVVertex.h"
#include "AliESDVertex.h"
#include "AliAODVertex.h"
#include "AliAnalysisMuonUtility.h"
#include "AliAnalysisUtils.h"
#include "AliMuonTrackCuts.h"
#include "AliOADBMuonTrackCutsParam.h"
#include "AliCentrality.h"
#include "AliAODDimuon.h"
#include "AliVTrack.h"
#include "AliAODTrack.h"
#include "AliAODTracklets.h"
#include "AliAODHeader.h"
#include "AliESDMuonTrack.h"
#include "AliInputEventHandler.h"
#include "AliMultSelection.h"
#include "AliAODDimuon.h"
#include "TaskCharmoniaDimuonMC.h"
#include "AliAODMCHeader.h"
#include "AliAODMCParticle.h"
#include <map>

ClassImp(TaskCharmoniaDimuonMC)

    //________________________________________________________________________
    TaskCharmoniaDimuonMC::TaskCharmoniaDimuonMC()
    : AliAnalysisTaskSE(),
      fArrayMCParticles(),
      fListOutput(0x0),
      fMuonTrackCuts(0),
      fHnGenerated(0),
      fHnReconstructed(0),
      fFirstRun(0),
      fLastRun(0),
      fHistoEventSelection(0)
{
  // Dummy constructor ALWAYS needed for I/O.
}

//________________________________________________________________________
TaskCharmoniaDimuonMC::TaskCharmoniaDimuonMC(const char *name, int firstRun, int lastRun)
    : AliAnalysisTaskSE(name),
      fArrayMCParticles(),
      fListOutput(0x0),
      fMuonTrackCuts(0),
      fHnGenerated(0),
      fHnReconstructed(0),
      fFirstRun(firstRun),
      fLastRun(lastRun),
      fHistoEventSelection(0)
{
  // Input slot #0 works with a TChain - it is connected to the default input container
  DefineInput(0, TChain::Class());
  // Output slot #1 writes into a TH1 container
  DefineOutput(1, TObjArray::Class()); // for output objarray
}

//________________________________________________________________________
TaskCharmoniaDimuonMC::~TaskCharmoniaDimuonMC()
{
  // Destructor. Clean-up the output list, but not the histograms that are put inside
  // (the list is owner and will clean-up these histograms). Protect in PROOF case.
  if (fListOutput && !AliAnalysisManager::GetAnalysisManager()->IsProofMode())
  {
    delete fListOutput;
  }
}

//________________________________________________________________________
void TaskCharmoniaDimuonMC::NotifyRun()
{
  /// Set run number for cuts
  if (fMuonTrackCuts)
    fMuonTrackCuts->SetRun(fInputHandler);
}

double TaskCharmoniaDimuonMC::WeightMaps15o(int runNumber)
{
  std::map<int,double> mymap;
  //LHC15o runList start
  mymap[246994] = 0.000729243;
  mymap[246992] = 0.000257544;
  mymap[246990] = 0.00225601;
  mymap[246984] = 0.0024403;
  mymap[246982] = 0.000303625;
  mymap[246980] = 0.00420418;
  mymap[246950] = 0.00169276;
  mymap[246948] = 0.000525691;
  mymap[246946] = 0.00122007;
  mymap[246942] = 0.000612451;
  mymap[246938] = 0.000420259;
  mymap[246930] = 0.000340832;
  mymap[246872] = 0.000393746;
  mymap[246868] = 0.000675928;
  mymap[246866] = 0.000449894;
  mymap[246864] = 0.00138603;
  mymap[246860] = 0.000719922;
  mymap[246856] = 0.0007764;
  mymap[246852] = 0.000732778;
  mymap[246848] = 0.00100474;
  mymap[246846] = 0.000508009;
  mymap[246846] = 0.000868346;
  mymap[246844] = 0.000457697;
  mymap[246810] = 0.00146563;
  mymap[246808] = 0.000182167;
  mymap[246808] = 0.00153921;
  mymap[246806] = 0.0015043;
  mymap[246806] = 0.00189799;
  mymap[246804] = 0.000597597;
  mymap[246766] = 0.000196129;
  mymap[246764] = 0.000331576;
  mymap[246760] = 0.000702803;
  mymap[246760] = 0.000197109;
  mymap[246758] = 0.000974402;
  mymap[246758] = 0.000350593;
  mymap[246756] = 0.000847283;
  mymap[246752] = 0.00121869;
  mymap[246750] = 0.00124837;
  mymap[246676] = 0.000279585;
  mymap[246676] = 0.00136161;
  mymap[246496] = 0.000245616;
  mymap[246494] = 0.000802851;
  mymap[246488] = 0.00449449;
  mymap[246488] = 0.000416493;
  mymap[246434] = 0.00242221;
  mymap[246434] = 0.000253906;
  mymap[246432] = 0.00106696;
  mymap[246428] = 0.000270171;
  mymap[246424] = 0.00171034;
  mymap[246392] = 0.000107496;
  mymap[246392] = 8.68477e-05;
  mymap[246390] = 2.70563e-05;
  mymap[246276] = 0.000333079;
  mymap[246276] = 0.000703884;
  mymap[246272] = 0.0031178;
  mymap[246226] = 0.000775191;
  mymap[246222] = 0.00225858;
  mymap[246220] = 0.000424055;
  mymap[246218] = 0.00200106;
  mymap[246182] = 0.00131264;
  mymap[246182] = 0.00166243;
  mymap[246178] = 0.00048689;
  mymap[246154] = 0.00281691;
  mymap[246152] = 0.000285777;
  mymap[246152] = 0.00186772;
  mymap[246148] = 0.00326844;
  mymap[246116] = 0.00027271;
  mymap[246114] = 0.000879764;
  mymap[246090] = 0.00019772;
  mymap[246088] = 0.00838477;
  mymap[246054] = 0.00108089;
  mymap[246050] = 0.00201382;
  mymap[246048] = 0.000233979;
  mymap[246042] = 0.00297496;
  mymap[246038] = 0.00102812;
  mymap[246036] = 0.000118092;
  mymap[246012] = 0.000440322;
  mymap[246004] = 0.000357084;
  mymap[246002] = 0.00217727;
  mymap[245996] = 0.000282798;
  mymap[245964] = 0.00130709;
  mymap[245954] = 0.00120015;
  mymap[245952] = 0.0018445;
  mymap[245950] = 0.000342383;
  mymap[245834] = 0.000212956;
  mymap[245832] = 0.00118358;
  mymap[245830] = 0.00118306;
  mymap[245794] = 0.000415747;
  mymap[245786] = 0.000305744;
  mymap[245776] = 0.00103252;
  mymap[245766] = 0.0006691;
  mymap[245760] = 0.000807836;
  mymap[245752] = 0.000708537;
  mymap[245738] = 0.00117179;
  mymap[245732] = 0.00202748;
  mymap[245730] = 0.000698733;
  mymap[245706] = 0.000196091;
  mymap[245700] = 0.000670349;
  mymap[245692] = 0.00115561;
  mymap[245684] = 0.00243387;
  mymap[245554] = 0.00103332;
  mymap[245544] = 0.00119612;
  mymap[245542] = 0.000671154;
  mymap[245540] = 0.000427986;
  mymap[245536] = 0.0008119;
  mymap[245508] = 0.0009655;
  mymap[245506] = 0.000215983;
  mymap[245504] = 0.000387036;
  mymap[245502] = 0.000792217;
  mymap[245496] = 0.000626096;
  mymap[245450] = 0.000154646;
  mymap[245446] = 7.0279e-05;
  mymap[245410] = 9.954e-05;
  mymap[245410] = 0.000475716;
  mymap[245408] = 0.00110571;
  mymap[245402] = 0.000410872;
  mymap[245354] = 0.000912499;
  mymap[245348] = 0.000648348;
  mymap[245346] = 0.000163391;
  mymap[245346] = 0.00129563;
  mymap[245344] = 0.000391682;
  mymap[245260] = 0.000282602;
  mymap[245254] = 0.00018225;
  mymap[245234] = 0.000139837;
  mymap[245232] = 0.000601141;
  mymap[245232] = 0.000180581;
  mymap[245152] = 9.69231e-05;
  mymap[245152] = 8.65988e-05;
  mymap[245146] = 0.000797675;
  mymap[245146] = 0.000723019;
  mymap[245068] = 1.19608e-05;
  mymap[245066] = 1.30744e-05;
  mymap[245064] = 9.57265e-05;
  mymap[244984] = 1.70211e-05;
  mymap[244982] = 4.31222e-05;
  mymap[244980] = 2.8552e-05;
  mymap[244918] = 1.29387e-05;
  
  //LHC18q runList start
  mymap[295584]  =    3.16214e-05;
  mymap[295586]  =    4.43791e-05;
  mymap[295586]  =    0.000134711;
  mymap[295588]  =    6.20563e-05;
  mymap[295588]  =    7.6458e-05;
  mymap[295590]  =    0.000156812;
  mymap[295612]  =    0.000256237;
  mymap[295616]  =    3.26546e-05;
  mymap[295666]  =    0.000180905;
  mymap[295666]  =    0.000185809;
  mymap[295668]  =    5.53846e-05;
  mymap[295668]  =    7.44218e-05;
  mymap[295672]  =    0.00018545;
  mymap[295674]  =    0.000177192;
  mymap[295676]  =    7.40372e-05;
  mymap[295676]  =    0.000181958;
  mymap[295678]  =    0.000149746;
  mymap[295714]  =    0.000193374;
  mymap[295716]  =    0.00018957;
  mymap[295718]  =    0.000162871;
  mymap[295718]  =    0.000143864;
  mymap[295720]  =    0.000163195;
  mymap[295724]  =    0.00028096;
  mymap[295726]  =    0.00048861;
  mymap[295754]  =    0.000215875;
  mymap[295754]  =    0.000626051;
  mymap[295756]  =    0.000555845;
  mymap[295758]  =    0.00106334;
  mymap[295760]  =    0.000293509;
  mymap[295762]  =    0.000152177;
  mymap[295764]  =    0.000567592;
  mymap[295786]  =    0.000422951;
  mymap[295788]  =    0.00173553;
  mymap[295792]  =    0.000483137;
  mymap[295816]  =    0.00066635;
  mymap[295818]  =    8.04776e-05;
  mymap[295820]  =    0.00152139;
  mymap[295822]  =    0.00122613;
  mymap[295826]  =    0.000137707;
  mymap[295826]  =    0.000802064;
  mymap[295830]  =    0.00046816;
  mymap[295832]  =    0.0003891;
  mymap[295854]  =    0.000916443;
  mymap[295856]  =    0.000911953;
  mymap[295856]  =    0.000901918;
  mymap[295860]  =    0.00054087;
  mymap[295860]  =    0.000433238;
  mymap[295862]  =    0.000551011;
  mymap[295864]  =    0.00037372;
  mymap[295882]  =    0.000364922;
  mymap[295908]  =    0.00161644;
  mymap[295910]  =    0.000440153;
  mymap[295910]  =    0.0017567;
  mymap[295914]  =    0.00161848;
  mymap[295936]  =    0.000784776;
  mymap[295938]  =    0.000216677;
  mymap[295942]  =    0.000886395;
  mymap[295942]  =    0.00101833;
  mymap[295944]  =    0.000867544;
  mymap[295946]  =    0.00105508;
  mymap[295948]  =    0.00138777;
  mymap[296062]  =    0.000739525;
  mymap[296062]  =    0.00102647;
  mymap[296064]  =    0.00153627;
  mymap[296066]  =    0.00139229;
  mymap[296066]  =    0.00041372;
  mymap[296068]  =    0.00111242;
  mymap[296124]  =    0.000287954;
  mymap[296128]  =    0.000251438;
  mymap[296132]  =    0.00119093;
  mymap[296134]  =    0.000979251;
  mymap[296134]  =    0.00218494;
  mymap[296136]  =    0.00130706;
  mymap[296142]  =    0.000911352;
  mymap[296144]  =    0.000271795;
  mymap[296192]  =    0.00283014;
  mymap[296192]  =    0.000277315;
  mymap[296194]  =    0.00158573;
  mymap[296196]  =    0.000403333;
  mymap[296196]  =    0.000813683;
  mymap[296198]  =    0.000696033;
  mymap[296198]  =    0.000272788;
  mymap[296242]  =    0.00047325;
  mymap[296242]  =    0.000534183;
  mymap[296244]  =    0.00087092;
  mymap[296244]  =    0.00440428;
  mymap[296246]  =    0.000962014;
  mymap[296248]  =    0.000618811;
  mymap[296270]  =    0;
  mymap[296270]  =    0.000796405;
  mymap[296274]  =    0.0036494;
  mymap[296280]  =    0.000200993;
  mymap[296280]  =    0.000799284;
  mymap[296304]  =    0.00113586;
  mymap[296304]  =    0.0031931;
  mymap[296308]  =    0.00152407;
  mymap[296310]  =    0.00109511;
  mymap[296312]  =    0.00110592;
  mymap[296376]  =    0.000595714;
  mymap[296378]  =    0.00340505;
  mymap[296378]  =    0.0029849;
  mymap[296380]  =    0.00116026;
  mymap[296380]  =    0.0015921;
  mymap[296382]  =    0.000783451;
  mymap[296384]  =    0.000836702;
  mymap[296414]  =    0.00273299;
  mymap[296420]  =    0.00144322;
  mymap[296420]  =    0.000736697;
  mymap[296424]  =    0.000812345;
  mymap[296424]  =    0.000195075;
  mymap[296434]  =    0.00226881;
  mymap[296472]  =    0.000447622;
  mymap[296510]  =    0.0016745;
  mymap[296510]  =    0.00499076;
  mymap[296512]  =    0.0013924;
  mymap[296514]  =    0.000266765;
  mymap[296516]  =    0.000332014;
  mymap[296548]  =    0.000611702;
  mymap[296548]  =    0.000772428;
  mymap[296550]  =    0.00249321;
  mymap[296550]  =    0.0020381;
  mymap[296552]  =    0.00102826;
  mymap[296552]  =    0.000247039;
  mymap[296554]  =    0.000361106;
  mymap[296616]  =    0.000882667;
  mymap[296616]  =    0.000298607;
  mymap[296618]  =    0.00126489;
  mymap[296620]  =    0.000862247;
  mymap[296622]  =    0.000380752;
  mymap[296624]  =    0.00117627;

  //LHC18r runList start
  mymap[296690]  =    0.0038914;
  mymap[296692]  =    0.000372001;
  mymap[296694]  =    0.00268828;
  mymap[296750]  =    0.00482734;
  mymap[296750]  =    0.00415252;
  mymap[296752]  =    3.94093e-05;
  mymap[296782]  =    0.000465845;
  mymap[296784]  =    0.00169408;
  mymap[296786]  =    0.00105228;
  mymap[296786]  =    0.000411895;
  mymap[296788]  =    0.00165819;
  mymap[296792]  =    0.000392004;
  mymap[296794]  =    0.000714756;
  mymap[296794]  =    0.00127018;
  mymap[296800]  =    0.0011242;
  mymap[296836]  =    0.000792325;
  mymap[296838]  =    0.000285907;
  mymap[296840]  =    0.00155226;
  mymap[296848]  =    0.0011444;
  mymap[296850]  =    0.00596965;
  mymap[296850]  =    0.00141999;
  mymap[296852]  =    0.000437572;
  mymap[296852]  =    0.000477459;
  mymap[296890]  =    0.00444303;
  mymap[296894]  =    0.00257271;
  mymap[296900]  =    0.000963668;
  mymap[296900]  =    0.00125665;
  mymap[296904]  =    0.000424286;
  mymap[296930]  =    0.000713819;
  mymap[296932]  =    0.000265603;
  mymap[296932]  =    0.000484221;
  mymap[296934]  =    0.00106973;
  mymap[296936]  =    0.00141725;
  mymap[296938]  =    0.000520671;
  mymap[296942]  =    0.000915422;
  mymap[296966]  =    0.00173703;
  mymap[296968]  =    0.000413756;
  mymap[296968]  =    0.00163885;
  mymap[296970]  =    0.000962949;
  mymap[296972]  =    0.000347607;
  mymap[296976]  =    0.00372007;
  mymap[296976]  =    0.000560628;
  mymap[296980]  =    0.000432172;
  mymap[297030]  =    0.00389501;
  mymap[297032]  =    0.00325805;
  mymap[297036]  =    0.000698318;
  mymap[297086]  =    0.000549427;
  mymap[297118]  =    0.0013191;
  mymap[297118]  =    0.00136632;
  mymap[297120]  =    0.00150453;
  mymap[297124]  =    0.00188187;
  mymap[297124]  =    0.000355261;
  mymap[297128]  =    0.00132309;
  mymap[297130]  =    0.00155007;
  mymap[297132]  =    0.00154233;
  mymap[297134]  =    0.000642622;
  mymap[297194]  =    0.0043011;
  mymap[297194]  =    0.00585624;
  mymap[297196]  =    0.00118282;
  mymap[297218]  =    0.00359845;
  mymap[297220]  =    0.0057633;
  mymap[297222]  =    0.00154997;
  mymap[297222]  =    0.000730779;
  mymap[297278]  =    0.000342021;
  mymap[297310]  =    0.000368238;
  mymap[297312]  =    0.00136289;
  mymap[297316]  =    0.004348;
  mymap[297318]  =    0.00234402;
  mymap[297364]  =    0.00106626;
  mymap[297366]  =    0.00120803;
  mymap[297368]  =    0.00172895;
  mymap[297372]  =    0.0017831;
  mymap[297380]  =    0.00403873;
  mymap[297380]  =    0.00069634;
  mymap[297406]  =    0.000325639;
  mymap[297408]  =    0.00227592;
  mymap[297414]  =    0.00160692;
  mymap[297414]  =    0.00112748;
  mymap[297416]  =    0.00335798;
  mymap[297442]  =    0.00262964;
  mymap[297442]  =    0.00101017;
  mymap[297446]  =    0.00321448;
  mymap[297450]  =    0.000769786;
  mymap[297452]  =    0.000523057;
  mymap[297452]  =    0.000453582;
  mymap[297480]  =    0.00426266;
  mymap[297482]  =    0.00546445;
  mymap[297484]  =    0.00101786;
  mymap[297512]  =    0.000869816;
  mymap[297538]  =    0.00100537;
  mymap[297540]  =    0.000346018;
  mymap[297542]  =    0.00208743;
  mymap[297542]  =    0.000810224;
  mymap[297544]  =    0.0037066;
  mymap[297558]  =    0.000240339;
  mymap[297588]  =    0.0027701;
  mymap[297590]  =    0.00164178;
  mymap[297596]  =    0.000846657;



  return mymap[runNumber];
  
}
//________________________________________________________________________
void TaskCharmoniaDimuonMC::UserCreateOutputObjects()
{
  //Create the event, single muon, dimuon histgrams, to do that, it is only needed to add the name of the histogram to the corresponding list, it will be created and the bins will be set according to the name

  //Event histograms
  fListOutput = new TObjArray(2000);
  fListOutput->SetOwner(kTRUE);
  fListOutput->SetName("ListEvent");

  //DiMuon histograms
  Int_t nbinsDiMuon[6] = {2000, 240, 60, fLastRun - fFirstRun, 2, 900}; //mass,pt,rapidity,run,pdg
  Double_t xminDiMuon[6] = {0, 0, -5, (Double_t)fFirstRun, 0, 0}, xmaxDiMuon[6] = {10, 30, -2, (Double_t)fLastRun, 2, 90};

  fHnGenerated = new THnSparseD("fHnGenerated", "", 6, nbinsDiMuon, xminDiMuon, xmaxDiMuon, 1024 * 16);
  fHnGenerated->Sumw2();
  fListOutput->Add(fHnGenerated);

  fHnReconstructed = new THnSparseD("fHnReconstructed", "", 6, nbinsDiMuon, xminDiMuon, xmaxDiMuon, 1024 * 16);
  fHnReconstructed->Sumw2();
  fListOutput->Add(fHnReconstructed);

  fHistoEventSelection = new TH1I("fHistoEventSelection", "", 10, 0, 10);
  fHistoEventSelection->GetXaxis()->SetBinLabel(kAllEvents + 1, "total");
  fHistoEventSelection->GetXaxis()->SetBinLabel(kEventWithJpsi + 1, "With Jpsi");
  fHistoEventSelection->GetXaxis()->SetBinLabel(kEventWithPsi2s + 1, "With Psi2s");
  fHistoEventSelection->Sumw2();
  fListOutput->Add(fHistoEventSelection);

  fMuonTrackCuts = new AliMuonTrackCuts("StandardMuonTrackCuts", "StandardMuonTrackCuts");
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  fMuonTrackCuts->SetFilterMask(AliMuonTrackCuts::kMuEta | AliMuonTrackCuts::kMuThetaAbs | AliMuonTrackCuts::kMuPdca | AliMuonTrackCuts::kMuMatchLpt);
  fMuonTrackCuts->SetIsMC();

  PostData(1, fListOutput);
}

//________________________________________________________________________
void TaskCharmoniaDimuonMC::UserExec(Option_t *)
{

  Double_t weightCent[] = {0.1807986591, 0.1425980741, 0.1121553477, 0.0874950385, 0.0675836377, 0.05141380103, 0.03854072719, 0.02827104937, 0.02030387257, 0.01420747784, 0.009699285518, 0.006433920445, 0.004161508934, 0.002616478424, 0.001599976556, 0.0009416705848, 0.0005369013726, 0.0005369546195};
  Float_t muonMass2 = AliAnalysisMuonUtility::MuonMass2();
  
  

  AliAODEvent *aod = 0;
  AliAODHeader *aodHeader = NULL;
  Bool_t isAny = kFALSE;

  aod = static_cast<AliAODEvent *>(InputEvent());


  AliMultSelection *multSelection = (AliMultSelection * ) aod->FindListObject("MultSelection");
  Double_t eventCentrality = multSelection->GetMultiplicityPercentile("V0M", false);
  if(eventCentrality > 90) return;

    Int_t CentRange = eventCentrality/5;

  if (!aod)
  {
    AliError("ERROR: Could not retrieve ESD or AOD event !!");
    return;
  }



  TString strFiredTriggers;								//MODIFICATIN FOR PbPb
  aod = static_cast<AliAODEvent *>(InputEvent());
  if (aod) {
    aodHeader = (AliAODHeader *)aod->GetHeader();
    strFiredTriggers = aod->GetFiredTriggerClasses();
  } else {
    AliError("ERROR: Could not retrieve ESD or AOD event !!");
    return;
  }

  int runNumber = aod->GetRunNumber();
  fHistoEventSelection->Fill(kAllEvents);

  double weightCMULE = WeightMaps15o(runNumber);
  //cout<<weightCMULE<<"  "<<endl;

  UInt_t IsSelected =
      (((AliInputEventHandler *)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected());

  
  if (strFiredTriggers.Contains("CINT7-B-NOPF-MUFAST") &&		
      (IsSelected & AliVEvent::kAny)) {
    isAny = kTRUE;
  } else {
    return;
  }



  fArrayMCParticles = dynamic_cast<TClonesArray *>(InputEvent()->FindListObject(AliAODMCParticle::StdBranchName()));

  for (int iParticle = 0; iParticle < fArrayMCParticles->GetEntries(); iParticle++)
  {

    AliAODMCParticle *particle = (AliAODMCParticle *)fArrayMCParticles->At(iParticle);

    if (particle->GetStatus() == 21)
      continue;

    //Jpsi case
    if ((particle->GetPdgCode() == 443))
    {

      Double_t eventArray[6] = {};
      eventArray[0] = particle->GetCalcMass();
      eventArray[1] = particle->Pt();
      eventArray[2] = particle->Y();
      eventArray[3] = (Double_t)runNumber;
      eventArray[4] = 0.0;
      eventArray[5] = eventCentrality;

      fHnGenerated->Fill(eventArray, weightCMULE*weightCent[CentRange]);

      break;
    }
    else if ((particle->GetPdgCode() == 100443))
    {

      Double_t eventArray[6] = {};
      eventArray[0] = particle->GetCalcMass();
      eventArray[1] = particle->Pt();
      eventArray[2] = particle->Y();
      eventArray[3] = (Double_t)runNumber;
      eventArray[4] = 1.0;
      eventArray[5] = eventCentrality;

      fHnGenerated->Fill(eventArray, weightCMULE*weightCent[CentRange]);

      break;
    }
  }

  //reconstructed
  TLorentzVector lvRecFirstMuon, lvRecSecondMuon, lvRecDimuon;
  int numberOfTracks = aod->GetNumberOfTracks();

  for (Int_t iFirstMuon = 0; iFirstMuon < numberOfTracks; iFirstMuon++)
  {

    AliVTrack *firstMuon = aod->GetTrack(iFirstMuon);

    if (!fMuonTrackCuts->IsSelected(firstMuon))
      continue;

    int firstMuonIndex = WhichCharmonia(firstMuon->GetLabel());
    if (firstMuonIndex < 0)
      continue;
    for (Int_t iSecondMuon = iFirstMuon + 1; iSecondMuon < numberOfTracks; iSecondMuon++)
    {

      AliVTrack *secondMuon = aod->GetTrack(iSecondMuon);

      if (!fMuonTrackCuts->IsSelected(secondMuon))
        continue;

      int secondMuonIndex = WhichCharmonia(secondMuon->GetLabel());
      if (secondMuonIndex != firstMuonIndex)
        continue;

      Float_t energy = muonMass2 + firstMuon->P() * firstMuon->P();
      energy = TMath::Sqrt(energy);
      lvRecFirstMuon.SetPxPyPzE(firstMuon->Px(), firstMuon->Py(), firstMuon->Pz(), energy);

      energy = muonMass2 + secondMuon->P() * secondMuon->P();
      energy = TMath::Sqrt(energy);
      lvRecSecondMuon.SetPxPyPzE(secondMuon->Px(), secondMuon->Py(), secondMuon->Pz(), energy);

      lvRecDimuon = lvRecFirstMuon + lvRecSecondMuon;

      if (firstMuon->Charge() == secondMuon->Charge())
        continue;

      Double_t eventArray[6] = {};
      eventArray[0] = lvRecDimuon.M();
      eventArray[1] = lvRecDimuon.Pt();
      eventArray[2] = lvRecDimuon.Rapidity();
      eventArray[3] = (Double_t)runNumber;
      eventArray[4] = (Double_t)secondMuonIndex;
      eventArray[5] = eventCentrality;

      fHnReconstructed->Fill(eventArray, weightCMULE*weightCent[CentRange]);

    }
  }


  PostData(1, fListOutput);
}

//________________________________________________________________________
void TaskCharmoniaDimuonMC::Terminate(Option_t *)
{
  fListOutput = dynamic_cast<TObjArray *>(GetOutputData(1));
  if (!fListOutput)
  {
    AliError("Could not retrieve TObjArray* fListOutput");
    return;
  }
}

Int_t TaskCharmoniaDimuonMC::WhichCharmonia(int muonIndex)
{

  AliAODMCParticle *muonParticle = (AliAODMCParticle *)fArrayMCParticles->At(muonIndex);
  if (muonIndex < 0)
    return -99;
  if ((muonParticle->GetPdgCode() == 13) || (muonParticle->GetPdgCode() == -13))
  {

    int iMother = muonParticle->GetMother();
    while (iMother >= 0)
    {
      AliAODMCParticle *firstMother = (AliAODMCParticle *)fArrayMCParticles->At(iMother);
      int pdgCodeOfFirstMother = firstMother->GetPdgCode();
      if (pdgCodeOfFirstMother == 443)
      {
        return 0;
      }
      if (pdgCodeOfFirstMother == 100443)
      {
        return 1;
      }
      iMother = firstMother->GetMother();
    }
  }
  return -99;
}

