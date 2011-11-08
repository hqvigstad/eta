void runTagCreator() {
  TStopwatch timer;
  timer.Start();
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  //____________________________________________________//
  //_____________Setting up par files___________________//
  //____________________________________________________//
  gSystem->Load("libSTEERBase.so");
  gSystem->Load("libESD.so");
                                                                                                                                               
  gROOT->LoadMacro("CreateTags.C");
  CreateTags();

  timer.Stop();
  timer.Print();
}
