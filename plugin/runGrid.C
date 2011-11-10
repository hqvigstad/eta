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
  AliAnalysisGrid *alienHandler = CreateAlienHandler();  
  if (!alienHandler) return;
  mgr->SetGridHandler(alienHandler);


  gROOT->LoadMacro("EtaCandidate.cxx+g");
  gROOT->LoadMacro("EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("EtaConfig.cxx+g");
  gROOT->LoadMacro("EtaHistograms.cxx+g");
  gROOT->LoadMacro("EtaAnalysis.cxx+g");
  gROOT->LoadMacro("EtaTask.cxx+g");

  AliAnalysisTask *etaTask = new EtaTask("");
  mgr->AddTask(etaTask);

  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);

  
  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("chist1", TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
  mgr->ConnectInput(etaTask, 0, cinput0);
  mgr->ConnectOutput(etaTask, 1, coutput1);
  
  // Enable debug printouts
  mgr->SetDebugLevel(2);

  if (!mgr->InitAnalysis())
    return;

  mgr->PrintStatus();
  // Start analysis in grid.
  mgr->StartAnalysis("grid");

  timer.Stop();
  timer.Print();
};
