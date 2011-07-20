static const char* gMode =  "full";
static const char* gDataDir =  "/alice/sim/LHC11b6/";
static const char* gPrefix = "";
static const char* gRunFile = "file.txt";

static const char* gWorkingDir = "EtaData";
static const char* gOutputDir = "output";

static TString gIncludeFiles = "EtaDataTask.cxx EtaDataTask.h EtaHandler.cxx EtaHandler.h  EtaCandidate.cxx EtaCandidate.h";
static TString gCompileFiles = "EtaCandidate.cxx EtaHandler.cxx EtaDataTask.cxx";
static TString gOutputFiles = 
  "EtaDataTask_output.1.root";

AliAnalysisGrid* CreateAlienHandler()
{
  // if (!AliAnalysisGrid::CreateToken()) return NULL;
  
  AliAnalysisAlien *plugin = new AliAnalysisAlien();
  
  // (can be "full", "test", "offline", "submit" or "terminate")
   plugin->SetRunMode(gMode);

   plugin->SetAPIVersion("V1.1x");
   plugin->SetROOTVersion("v5-28-00e-1");
   plugin->SetAliROOTVersion("v4-21-29-AN");

   // Declare input data to be processed.
   plugin->SetGridDataDir(gDataDir);
   plugin->SetDataPattern("*tag.root");
   
   plugin->AddRunNumber("119159");
   plugin->AddRunNumber("119161");

   
   plugin->SetGridWorkingDir(gWorkingDir);
   plugin->SetGridOutputDir(gOutputDir);

   plugin->SetAnalysisSource(gCompileFiles);
   plugin->SetAdditionalLibs(gIncludeFiles);
   //plugin->SetOutputFiles(gOutputFiles);

   //plugin->SetOutputArchive("log_archive.zip:stdout,stderr");
   plugin->SetAnalysisMacro("AnalysisEta.C");
   plugin->SetJDLName("TaskEta.jdl");

   plugin->SetSplitMaxInputFileNumber(100);
   plugin->SetMaxInitFailed(5);
   plugin->SetMasterResubmitThreshold(90);
   plugin->SetTTL(30000);
   plugin->SetInputFormat("xml-single");
   plugin->SetPrice(1);      
   plugin->SetSplitMode("se");

   plugin->SetMergeViaJDL(kTRUE);
   //plugin->SetOneStageMerging(kFALSE);
   //plugin->SetMaxMergeStages(2);
   plugin->SetOutputToRunNo(kTRUE);
   
   return plugin;
}
