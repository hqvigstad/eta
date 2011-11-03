void runEtaDataLocal()
{
  // for running with root only
  gSystem->Load("libCore.so");  
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libSTEERBase.so");
  gSystem->Load("libESD.so");
  gSystem->Load("libAOD.so"); 
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");

  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  gSystem->AddIncludePath("-I$ALICE_ROOT/PHOS");

  //gROOT->ProcessLine(".include $ALICE_ROOT/include");

  // Create tasks
  gROOT->LoadMacro("../EtaCandidate.cxx+g");
  gROOT->LoadMacro("../EtaPriCandidate.cxx+g");
  gROOT->LoadMacro("../EtaHistograms.cxx+g");
  gROOT->LoadMacro("../EtaConfig.cxx+g");
  gROOT->LoadMacro("../EtaAnalysis.cxx+g");
  gROOT->LoadMacro("../EtaTask.cxx+g");

  // Create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisManager");

  AliESDInputHandler* esdH = new AliESDInputHandler();
  mgr->SetInputEventHandler(esdH);
  // AliMCEventHandler* mcH = new AliMCEventHandler;
  // mcH->SetReadTR(kFALSE);
  // mgr->SetMCtruthEventHandler(mcH);



  EtaTask* task = new EtaTask("EtaTask");

  // Add tasks
  mgr->AddTask(task);

  // Create containers for input/output
  AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
  mgr->ConnectInput(task, 0, cinput);

  AliAnalysisDataContainer *PHOSOutput = mgr->CreateContainer("PHOSOutput", TList::Class(),    AliAnalysisManager::kOutputContainer, "EtaTask_output.root");
  mgr->ConnectOutput(task, 1, PHOSOutput);

  // Enable debug printouts
  mgr->SetDebugLevel(1);

  if (!mgr->InitAnalysis()) return;
  
  gROOT->LoadMacro("$ALICE_ROOT/PWG0/CreateESDChain.C");
  TChain* chain = CreateESDChain("files.txt", 2);

  mgr->PrintStatus();

  mgr->StartAnalysis("local", chain, 1000);
}
