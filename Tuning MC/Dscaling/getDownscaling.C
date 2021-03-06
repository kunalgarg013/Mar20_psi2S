void getDownscaling(Bool_t scal = kTRUE)
{

  // LHC18q
  Int_t nRuns = 147;
  Int_t runList[147] = {
	295584,295585,295586,295587,295588,295589,295610,295611,295612,295615,
	295665,295666,295667,295668,295671,295673,295675,295676,295677,295712,
	295714,295716,295717,295718,295719,295720,295721,295723,295725,295753,295754,
	295755,295756,295758,295759,295762,295763,295786,295788,295791,295816,
	295818,295819,295822,295825,295826,295829,295831,295853,295854,295855,
	295856,295859,295860,295861,295863,295872,295881,295908,295909,295910,295913,
	295936,295937,295941,295942,295943,295945,295947,296016,296060,296061,
	296062,296063,296065,296066,296068,296074,296123,296128,296132,296133,
	296134,296135,296142,296143,296191,296192,296194,296195,296196,296197,
	296198,296240,296241,296242,296243,296244,296246,296247,296269,296270,
	296273,296275,296279,296280,296303,296304,296307,296309,296312,296375,
	296376,296377,296378,296379,296380,296381,296383,296414,/*296415,*/296419,
	296420,296423,296424,296433,296472,296509,296510,296511,296512,296514,
	296516,296547,296548,296549,296550,296551,296552,296553,296594,296615,
	296616,296618,296619,296621,296622,296623
  };

  // Old run list for LHC18q
  // Int_t nRuns = 144;
  // Int_t runList[144] = {
  //   295584,295585,295586,295587,295588,295589,295610,295611,295612,295615,
  //   295665,295666,295667,295668,295671,295673,295675,295676,295677,295712,
  //   295714,295717,295718,295719,295720,295721,295723,295725,295753,295754,
  //   295755,295756,295758,295759,295762,295763,295786,295788,295791,295816,
  //   295818,295819,295822,295825,295826,295829,295831,295853,295854,295855,
  //   295856,295859,295860,295861,295863,295881,295908,295909,295910,295913,
  //   295936,295937,295941,295942,295943,295945,295947,296016,296060,296061,
  //   296062,296063,296065,296066,296068,296074,296123,296128,296132,296133,
  //   296134,296135,296142,296143,296191,296192,296194,296195,296196,296197,
  //   296198,296240,296241,296242,296243,296244,296246,296247,296269,296270,
  //   296273,296275,296279,296280,296303,296304,296307,296309,296312,296375,
  //   296376,296377,296378,296379,296380,296381,296383,296414,/*296415,*/296419,
  //   296420,296423,296424,296433,296472,296509,296510,296511,296512,296514,
  //   296516,296547,296548,296549,296550,296551,296552,296553,296594,296615,
  //   296616,296618,296621,296622,296623
  // };

  // LHC18r
  // Int_t nRuns = 110;
  // Int_t runList[110] = {
  //   296690, 296691, 296693, 296694, 296749, 296750, 296752, 296781, 296784, 296785,
  //   296786, 296787, /*296790,*/ 296791, 296793, 296794, 296799, 296835, 296836, 296838,
  //   296839, 296848, 296849, 296850, 296851, 296852, 296890, 296894, 296899, 296900,
  //   296903, 296930, 296931, 296932, 296934, 296935, 296938, 296941, 296966, 296967,
  //   296968, 296969, 296971, 296975, 296976, 296977, 296979, 297029, 297031, 297035,
  //   297085, 297117, 297118, 297119, 297123, 297124, 297128, 297129, 297132, 297133,
  //   297193, 297194, 297195, 297196, 297218, 297219, 297221, 297222, 297277, 297278,
  //   297310, 297311, 297312, 297315, 297317, /*297332,*/ /*297333,*/ /*297335,*/ /*297336,*/ 297363,
  //   297366, 297367, 297372, 297379, 297380, 297403, 297405, 297406, 297408, 297413,
  //   297414, 297415, 297441, 297442, 297446, 297450, 297451, 297452, 297479, 297481,
  //   297483, 297512, 297537, 297540, 297541, 297542, 297544, 297557, 297558, 297588,
  //   297589, 297590, 297595, 297623, 297624};

  TH1D *hDS = new TH1D("hDS","Downscaling factors",2041,295583.5,297624.5);

  AliCDBManager* man = AliCDBManager::Instance();
  man->SetDefaultStorage("raw://");
  for(Int_t irun = 0; irun < nRuns; ++irun) {
	Int_t run = runList[irun];
	man->SetRun(run);

	Double_t dsFactor = 0;
	AliTriggerConfiguration* cfg = (AliTriggerConfiguration*) man->Get("GRP/CTP/Config")->GetObject();
	if (!cfg) { printf("No GRP/CTP/Config object for run %i\n",run); return TObjArray(); }

	TObjArray classes = cfg->GetClasses();
	//	classes.Print();
	// CMLL
	AliTriggerClass* mllClass = (AliTriggerClass*) classes.FindObject("CMLL7-B-NOPF-MUFAST");
	AliTriggerClass* mulClass = (AliTriggerClass*) classes.FindObject("CMUL7-B-NOPF-MUFAST");

	if (!scal) {
  	mllClass->GetDownscaleFactor(dsFactor);
	}
	else {
  	// Get scalers
  	AliCDBEntry* entry = AliCDBManager::Instance()->Get("GRP/CTP/Scalers");
  	AliTriggerRunScalers* runscalers = dynamic_cast<AliTriggerRunScalers*> (entry->GetObject());
  	runscalers->CorrectScalersOverflow();

  	TObjArray* rec = (TObjArray*)runscalers->GetScalersRecordsESD();
  	Int_t Nent = (Int_t)rec->GetEntriesFast();

  	Double_t countMLLB, countMLLA, countMULB, countMULA;
  	{ // first
    AliTriggerScalersRecordESD* scalrecs = (AliTriggerScalersRecordESD*) rec->At(0);
    AliTriggerScalersESD *s0MLL = scalrecs->GetTriggerScalersForClass(mllClass->GetIndex());
    AliTriggerScalersESD *s0MUL = scalrecs->GetTriggerScalersForClass(mulClass->GetIndex());
    countMLLB = Double_t(s0MLL->GetLOCB());
	 countMLLA = Double_t(s0MLL->GetLOCA());
    countMULB = Double_t(s0MUL->GetLOCB());
	 countMULA = Double_t(s0MUL->GetLOCA());
  	}
  	{ // last
    AliTriggerScalersRecordESD* scalrecs = (AliTriggerScalersRecordESD*) rec->At(Nent-1);
    AliTriggerScalersESD *s0MLL = scalrecs->GetTriggerScalersForClass(mllClass->GetIndex());
    AliTriggerScalersESD *s0MUL = scalrecs->GetTriggerScalersForClass(mulClass->GetIndex());
    countMLLB = Double_t(s0MLL->GetLOCB()) - countMLLB;
	 countMLLA = Double_t(s0MLL->GetLOCA()) - countMLLA;
    countMULB = Double_t(s0MUL->GetLOCB()) - countMULB;
	 countMULA = Double_t(s0MUL->GetLOCA()) - countMULA;
  	}
  	printf("mll B=%f A=%f   mul B=%f A=%f\n",countMLLB,countMLLA,countMULB,countMULA);
  	dsFactor = (countMLLA/countMLLB) / (countMULA/countMULB);
	}

	printf("Run: %d  ds = %.4f\n",run,dsFactor);
	hDS->SetBinContent(hDS->GetXaxis()->FindBin((Double_t)run),dsFactor);
  }

  TFile fout("downscaling_factors_lhc18q.root","RECREATE");
  hDS->Write();
  fout.Close();
}
