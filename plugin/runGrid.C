void runGrid(const char* mode = "full",
  const TString eventType = "AOD"
)
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

  gROOT->LoadMacro("EtaCandidate.cxx+g");
  gROOT->LoadMacro("EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("EtaConfig.cxx+g");
  gROOT->LoadMacro("EtaHistograms.cxx+g");
  gROOT->LoadMacro("EtaAnalysis.cxx+g");
  gROOT->LoadMacro("EtaTask.cxx+g");

  // Create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("testAnalysis");

  // Create and configure the alien handler plugin
  gROOT->LoadMacro("CreateAlienHandler.C");
  AliAnalysisGrid *alienHandler = CreateAlienHandler(mode);  
  if (!alienHandler) return;
  mgr->SetGridHandler(alienHandler);

  AliInputEventHandler* inputEventHandler;
  if( eventType.EqualTo("ESD") )
    inputEventHandler = new AliESDnputHandler();
  if( eventType.EqualTo("AOD") )
    inputEventHandler = new AliAODInputHandler();
    
    
  mgr->SetInputEventHandler(inputEventHandler);

  // Add Physics Selection
  gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPhysicsSelection.C");
  AliPhysicsSelectionTask* physSelTask = AddTaskPhysicsSelection();
  
  
  // Add EtaTasks:
  AliAnalysisDataContainer *cinput0 = mgr->GetCommonInputContainer();
  float pts [] = {0.0, 0.5, 1.0, 2.0, 3.0};
  bool emcals [] = {false, true};
  bool phi7s [] = {false, true};
  for(int pti = 0; pti < 5; ++pti) {
    for(int emi = 0; emi < 2; ++emi) { 
      for(int phi = 0; phi < 2; ++phi) {
	const float pt = pts[pti];
	const bool em = emcals[emi];
	const bool phi7 = phi7s[phi];
	char hash[256];
	sprintf(hash, "pt:%.1f_emcal:%d_kPHI7:%d", pt, em, phi7);
	char name[256];
	sprintf(name, "etaTask_%s", hash);
	EtaTask *task = new EtaTask(name);
	EtaConfig conf;
	if(em)
	  conf.fEnableEMCAL = true;
	if(phi7)
	  task->SelectCollisionCandidates(AliVEvent::kPHI7);
	task->SetConfig(&conf);
	
	mgr->AddTask(task);
	mgr->ConnectInput(task, 0, cinput0);
	sprintf(name, "eta.%s.output1", hash);
	AliAnalysisDataContainer *outContainer = mgr->CreateContainer(name, TList::Class(),AliAnalysisManager::kOutputContainer,"eta.output.ESD.root");
	mgr->ConnectOutput(task, 1, outContainer);
      }
    }
  }

  // Enable debug printouts
  mgr->SetDebugLevel(1);

  if (!mgr->InitAnalysis())
    return;

  mgr->PrintStatus();
  // Start analysis in grid.
  mgr->StartAnalysis("grid");

  timer.Stop();
  timer.Print();
};
