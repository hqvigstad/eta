void runLocal() {
  TStopwatch timer;
  timer.Start();
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
  gROOT->LoadMacro("../EtaCandidate.cxx+g");
  gROOT->LoadMacro("../EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("../EtaHistograms.cxx+g");
  gROOT->LoadMacro("../EtaConfig.cxx+g");
  gROOT->LoadMacro("../EtaAnalysis.cxx+g");
  gROOT->LoadMacro("../EtaTask.cxx++g");

  //____________________________________________//
  AliTagAnalysis *tagAna = new AliTagAnalysis("ESD"); 
  tagAna->ChainLocalTags("tags");

  AliRunTagCuts *runCuts = new AliRunTagCuts();
  AliLHCTagCuts *lhcCuts = new AliLHCTagCuts();
  AliDetectorTagCuts *detCuts = new AliDetectorTagCuts();
  AliEventTagCuts *evCuts = new AliEventTagCuts();
  // evCuts->SetMultiplicityRange(11,12);  
  
  TChain* chain = 0x0;
  chain = tagAna->QueryTags(runCuts, lhcCuts, detCuts, evCuts);

  //____________________________________________//
  // Make the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("TestManager");
  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);  

  //____________________________________________//
  // Eta Task
  EtaTask *etaTask = new EtaTask("etaTask");
  mgr->AddTask(etaTask);
  // Create containers for input/output
  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("coutput1", TList::Class(), AliAnalysisManager::kOutputContainer, "EtaTaskOutput.ESD.root");
  
  //____________________________________________//
  mgr->ConnectInput(etaTask,0,cinput0);
  mgr->ConnectOutput(etaTask,1,coutput1);
  mgr->SetDebugLevel(0);
  if (!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  mgr->StartAnalysis("local",chain);

  timer.Stop();
  timer.Print();
}
