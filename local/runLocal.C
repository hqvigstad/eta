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
  gROOT->LoadMacro("../tasks/EtaCandidate.cxx+g");
  gROOT->LoadMacro("../tasks/EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("../tasks/EtaHistograms.cxx+g");
  gROOT->LoadMacro("../tasks/EtaConfig.cxx+g");
  gROOT->LoadMacro("../tasks/EtaAnalysis.cxx+g");
  gROOT->LoadMacro("../tasks/EtaTask.cxx+g");

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

  // Add Eta Task
  EtaTask* etaTask = new EtaTask("EtaTask");
  mgr->AddTask(etaTask);

  EtaTask *omegaTask = new EtaTask("omegaTask");
  EtaConfig omegaConf;
  omegaConf.fEtaMass = 0.134;
  omegaConf.fEtaMassDiffMax = omegaConf.fEtaMass*0.05;
  omegaTask->SetConfig(&omegaConf);
  mgr->AddTask(omegaTask);


  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer *etaout1= mgr->CreateContainer("eta.output.1", TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
  AliAnalysisDataContainer *omegaout1 = mgr->CreateContainer("omega.output.1", TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
  mgr->ConnectInput(etaTask, 0, cinput0);
  mgr->ConnectInput(omegaTask, 0, cinput0);
  mgr->ConnectOutput(etaTask, 1, etaout1);
  mgr->ConnectOutput(omegaTask, 1, omegaout1);

  //____________________________________________//
  mgr->SetDebugLevel(1);
  if (!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  mgr->StartAnalysis("local",chain);

  timer.Stop();
  timer.Print();
}
