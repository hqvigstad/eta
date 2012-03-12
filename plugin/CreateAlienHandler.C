
AliAnalysisGrid* CreateAlienHandler(const char* mode = "offline")
{

  //if (!AliAnalysisGrid::CreateToken()) return NULL;

   AliAnalysisAlien *plugin = new AliAnalysisAlien();
   
   plugin->SetRunMode(mode); // "full", "test", "offline", "submit" or "terminate"
   plugin->SetMergeViaJDL(kTRUE);
   plugin->SetOneStageMerging(kFALSE);
   plugin->SetMaxMergeStages(2);

   plugin->SetAPIVersion("V1.1x");
   plugin->SetROOTVersion("v5-30-03");
   plugin->SetAliROOTVersion("v5-02-16-AN");

   // add data through aliensh find procedure.
   //plugin->SetGridDataDir("/alice/sim/LHC11d2/");
   plugin->SetGridDataDir("/alice/data/2011/LHC11e");
   //plugin->SetDataPattern("*pass1/*ESDs.root");
   //plugin->SetDataPattern("*tag.root");
   //plugin->SetDataPattern("*pass1/*tag.root");
   plugin->SetDataPattern("*AOD.root");
   //plugin->AddRunNumber(119161);
   //plugin->AddRunNumber("000162740");
   //plugin->AddRunNumber("000161585");
   plugin->AddRunNumber("000162644");
   
   
   // Method 2: Declare existing data files 
   //plugin->AddDataFile("tag.xml");
   // plugin->AddDataFile("/alice/data/2008/LHC08c/000057657/raw/Run57657.Merged.RAW.tag.root");

   
   plugin->SetGridWorkingDir("eta");
   plugin->SetGridOutputDir("output"); // In this case will be $HOME/work/output

   // TString source = "";
   // source += "EtaCandidate.cxx ";
   // source += "EtaPriCandidate.cxx ";
   // source += "EtaConfig.cxx ";
   // source += "EtaOutput.cxx ";
   // source += "EtaAnalysis.cxx ";
   // source += "EtaTask.cxx ";
   // plugin->SetAnalysisSource(source);
   plugin->SetAnalysisSource("EtaCandidate.cxx EtaPriCandidate.cxx EtaConfig.cxx EtaOutput.cxx EtaAnalysis.cxx EtaTask.cxx");
   
   // TString libs = source;
   // libs += "EtaCandidate.h ";
   // libs += " EtaPriCandidate.h";
   // libs += " EtaConfig.h";
   // libs += " EtaOutput.h";
   // libs += " EtaAnalysis.h";
   // libs += " EtaTask.h";
   // plugin->SetAdditionalLibs(libs);
   plugin->SetAdditionalLibs("EtaCandidate.h EtaCandidate.cxx EtaPriCandidate.h EtaPriCandidate.cxx EtaConfig.h EtaConfig.cxx EtaOutput.h EtaOutput.cxx EtaAnalysis.h EtaAnalysis.cxx EtaTask.h EtaTask.cxx");

   plugin->SetDefaultOutputs(kTRUE);
   //plugin->SetDefaultOutputs(kFALSE);
   //plugin->SetOutputFiles("eta.output.ESD.root EventStat_temp.root");
   
   
   // Optionally define the files to be archived.
   // plugin->SetOutputArchive("log_archive.zip:stdout,stderr@ALICE::NIHAM::File root_archive.zip:*.root@ALICE::NIHAM::File");
   // plugin->SetOutputArchive("log_archive.zip:stdout,stderr");

   // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
   plugin->SetAnalysisMacro("EtaAnalysis.C");
   plugin->SetExecutable("runEtaAnalysis.sh");
   plugin->SetJDLName("EtaAnalysis.jdl");

   plugin->SetSplitMaxInputFileNumber(100);
   plugin->SetMaxInitFailed(5);
   plugin->SetMasterResubmitThreshold(90);
   plugin->SetTTL(43200);
   plugin->SetInputFormat("xml-single");
   plugin->SetPrice(1);      
   plugin->SetSplitMode("se");

   return plugin;
}
