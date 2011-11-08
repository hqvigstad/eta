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
  gSystem->Load("libESD.so");
  gSystem->Load("libAOD.so");
  gSystem->Load("libANALYSIS.so");
  gSystem->Load("libANALYSISalice.so");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");

  //___________Compile analysis task using AClic____________//
  gROOT->LoadMacro("../tasks/EtaCandidate.cxx+g");
  gROOT->LoadMacro("../tasks/EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("../tasks/EtaHistograms.cxx+g");
  gROOT->LoadMacro("../tasks/EtaConfig.cxx+g");
  gROOT->LoadMacro("../tasks/EtaAnalysis.cxx+g");
  gROOT->LoadMacro("../tasks/EtaTask.cxx+g");
  
  //____________________________________________//
  AliTagAnalysis *TagAna = new AliTagAnalysis("ESD"); 
  TagAna->ChainLocalTags("tags");

  AliRunTagCuts *runCuts = new AliRunTagCuts();
  AliLHCTagCuts *lhcCuts = new AliLHCTagCuts();
  AliDetectorTagCuts *detCuts = new AliDetectorTagCuts();
  AliEventTagCuts *evCuts = new AliEventTagCuts();
  evCuts->SetMultiplicityRange(11,12);  
  
  TChain* chain = 0x0;
  chain = TagAna->QueryTags(runCuts,lhcCuts,detCuts,evCuts);

  //____________________________________________//
  // Make the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("TestManager");
  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);  

  //____________________________________________//
  // Add Eta Task
  EtaTask* etaTask = new EtaTask("EtaTask");
  mgr->AddTask(etaTask);
  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("chist1", TH1::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
  mgr->ConnectInput(etaTask, 0, cinput0);
  mgr->ConnectOutput(etaTask, 1, coutput1);
  
  //____________________________________________//
  mgr->SetDebugLevel(2);
  if (!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  mgr->StartAnalysis("local",chain);

  timer.Stop();
  timer.Print();
}