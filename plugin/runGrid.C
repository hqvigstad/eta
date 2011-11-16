void runGrid(const char* mode = "test")
{
  TStopwatch timer;
  timer.Start();

  // Load common libraries
  gSystem->Load("libCore.so");  
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");   
  // Use AliRoot includes to compile our task
  gROOT->ProcessLine(".include $ALICE_ROOT/include");

  // Create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("testAnalysis");

  // Create and configure the alien handler plugin
  gROOT->LoadMacro("CreateAlienHandler.C");
  AliAnalysisGrid *alienHandler = CreateAlienHandler(mode);  
  if (!alienHandler) return;
  mgr->SetGridHandler(alienHandler);


  gROOT->LoadMacro("EtaCandidate.cxx+g");
  gROOT->LoadMacro("EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("EtaConfig.cxx+g");
  gROOT->LoadMacro("EtaHistograms.cxx+g");
  gROOT->LoadMacro("EtaAnalysis.cxx+g");
  gROOT->LoadMacro("EtaTask.cxx+g");

  AliAnalysisTask *etaTask = new EtaTask("etaTask");
  mgr->AddTask(etaTask);

  AliAnalysisTask *omegaTask = new EtaTask("omegaTask");
  EtaConfig omegaConf;
  omegaConf.fEtaMass = 0.134;
  omegaConf.fEtaMassDiffMax = omegaConf.fEtaMass*0.05;
  omegaTask->SetConfig(&omegaConf);
  mgr->AddTask(omegaTask);


  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);

  
  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer *etaout1= mgr->CreateContainer("eta.output.1", TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
  AliAnalysisDataContainer *omegaout1 = mgr->CreateContainer("omega.output.1", TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
  mgr->ConnectInput(etaTask, 0, cinput0);
  mgr->ConnectInput(omegaTask, 0, cinput0);
  mgr->ConnectOutput(etaTask, 1, etaout1);
  mgr->ConnectOutput(omegaTask, 1, omegaout1);
  
  // Enable debug printouts
  mgr->SetDebugLevel();

  if (!mgr->InitAnalysis())
    return;

  mgr->PrintStatus();
  // Start analysis in grid.
  mgr->StartAnalysis("grid");

  timer.Stop();
  timer.Print();
};
