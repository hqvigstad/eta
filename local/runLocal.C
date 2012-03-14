void runLocal() {
  TStopwatch timer;
  timer.Start();
  gSystem->Load("libCore.so");
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  //____________________________________________________//
  //_____________Setting up required packages___________//
  //____________________________________________________//
  gSystem->Load("libSTEERBase.so");
  gSystem->Load("libSTEER.so");
  gSystem->Load("libESD.so");
  gSystem->Load("libAOD.so");
  gSystem->Load("libANALYSIS.so");
  gSystem->Load("libANALYSISalice.so");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");

  //___________Compile analysis task using AClic____________//
  gROOT->LoadMacro("EtaCandidate.cxx+g");
  gROOT->LoadMacro("EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("EtaOutput.cxx+g");
  gROOT->LoadMacro("EtaConfig.cxx+g");
  gROOT->LoadMacro("EtaAnalysis.cxx+g");
  gROOT->LoadMacro("EtaTask.cxx+g");

  //____________________________________________//
  // chain using tags
//   AliTagAnalysis *tagAna = new AliTagAnalysis("ESD");
//   tagAna->ChainLocalTags("tags");
// 
//   AliRunTagCuts *runCuts = new AliRunTagCuts();
//   AliLHCTagCuts *lhcCuts = new AliLHCTagCuts();
//   AliDetectorTagCuts *detCuts = new AliDetectorTagCuts();
//   AliEventTagCuts *evCuts = new AliEventTagCuts();
//   // evCuts->SetMultiplicityRange(11,12);
//   TChain* chain = 0x0;
//   chain = tagAna->QueryTags(runCuts, lhcCuts, detCuts, evCuts);

  //____________________________________________//
  // chain using list of files.
  gROOT->LoadMacro("$ALICE_ROOT/PWGUD/macros/CreateESDChain.C");
  TChain* chain = CreateESDChain("files.txt", 2);

  
  //____________________________________________//
  // Make the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("TestManager");
  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);
  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();

  
  float pts [] = {0.0, 0.5, 1.0, 2.0, 3.0};
  bool emcals [] = {false, true};
  for(int pti = 0; pti < 5; ++pti)
    for(int emi = 0; emi < 2; ++emi) {
	const float pt = pts[pti];
	const bool em = emcals[emi];
	char hash[256];
	sprintf(hash, "p%.1f_e%d", pt, em);
	char name[256];
	sprintf(name, "etaTask_%s", hash);
	EtaTask *task = new EtaTask(name);
	EtaConfig conf;
	conf.fDistToBadCellMin = -1;
	if(em)
	  conf.fEnableEMCAL = true;
	task->SetConfig(&conf);
	
	mgr->AddTask(task);
	mgr->ConnectInput(task, 0, cinput0);
	sprintf(name, "eta.%s.output1", hash);
	AliAnalysisDataContainer *outContainer = mgr->CreateContainer(name, TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
	mgr->ConnectOutput(task, 1, outContainer);
    }

  //____________________________________________//
  mgr->SetDebugLevel(1);
  if (!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  mgr->StartAnalysis("local",chain);

  timer.Stop();
  timer.Print();
}
