

void runGrid()
{
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

  // Create and configure the alien handler plugin
  gROOT->LoadMacro("CreateAlienHandler.C");
  AliAnalysisGrid *alienHandler = CreateAlienHandler();  
  if (!alienHandler) return;

  // Create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("testAnalysis");

  // Connect plug-in to the analysis manager
  mgr->SetGridHandler(alienHandler);

  gROOT->LoadMacro("EtaCandidate.cxx++g");   
  gROOT->LoadMacro("EtaHandler.cxx++g");   
  gROOT->LoadMacro("EtaDataTask.cxx++g");   
  AliAnalysisTask *task = new EtaDataTask("EtaDataTask");
  mgr->AddTask(task);
  
  if( true ){ // Use Physics Selection
    gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPhysicsSelection.C");
    AliPhysicsSelectionTask* physSelTask = AddTaskPhysicsSelection();
    yourTask->SetCollisionCandidates(AliVEvent::kMB) 
  }
  
  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);

// No need to create a chain - this is handled by the plug-in
//  gROOT->LoadMacro("$ALICE_ROOT/PWG0/CreateESDChain.C");
//  TChain* chain = CreateESDChain("ESD82XX_30K.txt", 10);

  // Create containers for input/output
  AliAnalysisDataContainer *cinput = 
    mgr->CreateContainer("input_container", TChain::Class(), 
			 AliAnalysisManager::kInputContainer);
  // AliAnalysisDataContainer *coutput0 = 
  //   mgr->CreateContainer("output_container_0", TTree::Class(), 
  // 			 AliAnalysisManager::kOutputContainer, 
  // 			 "EtaDataTask_output.0.root");
  AliAnalysisDataContainer *coutput1 = 
    mgr->CreateContainer("output_container_1", TList::Class(), 
			 AliAnalysisManager::kOutputContainer, 
			 "EtaDataTask_output.1.root");

  // Connect input/output
  mgr->ConnectInput(task, 0, mgr->GetCommonInputContainer());
  //mgr->ConnectOutput(task, 0, coutput0);
  mgr->ConnectOutput(task, 1, coutput1);

  // Enable debug printouts
  mgr->SetDebugLevel(1);

  if (!mgr->InitAnalysis())
    return;
  
  mgr->PrintStatus();
  // Start analysis in grid.
  mgr->StartAnalysis("grid");
};
