#include "EtaDataTask.h"

#include "EtaAnalysis.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TList.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "AliVEvent.h"
#include "AliESDEvent.h"
#include "AliESDVertex.h"
#include "AliESDCaloCluster.h"
#include "TRefArray.h"
#include "TArrayI.h"
#include "AliMCEvent.h"
#include "AliESDCaloCells.h"
//#include "AliPHOSGeometry.h"
//#include "TGeoManager.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

ClassImp(EtaDataTask);

EtaDataTask::EtaDataTask(const char* name)
  : AliAnalysisTaskSE(name),
    fEtaAnalysis(0),
    fOutputList(0)
{
  DefineOutput(1, TList::Class());
}


EtaDataTask::~EtaDataTask()
{
  return ;
}

void EtaDataTask::UserCreateOutputObjects()
{
  fOutputList = new TList();
  fOutputList->SetOwner();
  
  fEtaAnalysis = new EtaAnalysis(EtaConfig());
  fEtaAnalysis->SetOutputList(fOutputList);
  PostData(1, fOutputList);
  
  // TH1F* nClusters = 
  //   new TH1F("nClusters", "Two Cluster I. Mass", 30, 0, 30);
  // // TH1F* Pt = new TH1F("PHOS", "Two Cluster I. Mass", 200, 0, 1);
  // // PHOS->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV/c^2]");
  // // PHOS->GetYaxis()->SNetTitle("Counts");
  // fOutputList->Add( nClusters );

  // TH2F* fCEnergyvNCells = new TH2F("fCEnergyvNCells", "fCEnergyvNCells",
  // 				   500, 0, 50,
  // 				   50, 0, 50);
  // fOutputList->Add( fCEnergyvNCells );
}

Bool_t EtaDataTask::UserNotify()
{
  return kTRUE;
}
  
/* This member cleans up all the the event specific data,
 * and should be called either in the beginning or the end of
 * any deriving class.
 */
void EtaDataTask::UserExec(Option_t* )
{
  // double vertex[3];
  // GetVertex(vertex);
  
  // // Get Clusters
  // TRefArray* clusters = new TRefArray;
  // GetClusters( clusters );
  // FindTH1("nClusters")->Fill( clusters->GetEntries() );
  // TH2* fCEnergyvNCells = FindTH2("fCEnergyvNCells");
  // TIterator* iter = clusters->MakeIterator();
  // while( iter->Next() )
  //   iter->Fill( fCEnergyvNCells->E(), fCEnergyvNCells->GetNCells() );
  
  // // Get Tracks
  // TRefArray* tracks = new TRefArray;
  // GetTracks( tracks );

  AliESDEvent* event = GetEvent();
  fEtaAnalysis->ProcessEvent(event);
  
  PostData(1, fOutputList);
}

void EtaDataTask::Terminate(Option_t* )
{
  // new TCanvas;
  // FindTH1("fH2_GG_PtvIM")->Draw();
  // new TCanvas;
  // FindTH1("nClusters")->Draw();
}

AliESDEvent* EtaDataTask::GetEvent()
{
  AliVEvent *event = InputEvent();
  if (!event)
    AliFatal("Could not retrieve event");
  if(! event->InheritsFrom("AliESDEvent"))
      AliFatal("Event is not ESD");
  return ( (AliESDEvent*) event);
}


// void EtaDataTask::GetClusters(TRefArray* clusters)
// {
//   const AliESDEvent* event = GetEvent();
//   for(int i=0; i< event->GetNumberOfCaloClusters(); ++i)
//     {
//       clusters->Add( event->GetCaloCluster(i) );
//     }
// }


// void EtaDataTask::GetTracks(TRefArray* tracks)
// {
//   const AliESDEvent* event = GetEvent();
//   for(int i=0; i< event->GetNumberOfTracks(); ++i)
//     tracks->Add( event->GetTrack(i) );
// }



// const AliESDCaloCells* EtaDataTask::GetPHOSCells()
// {
//   AliESDCaloCells* cells = GetEvent()->GetPHOSCells();
//   if( ! cells)
//     AliFatal("Could not retreive PHOS Calo Cells");
//   return cells;
// }

// const TObject* EtaDataTask::FindOutputObject(const char* const  name, 
// 				const char* const clas)
// {
//   TObject* obj = fOutputList->FindObject(name);
//   if(! obj)
//     AliFatal("Can't find object in fOutputList");
//   if(! obj->InheritsFrom(clas) )
//     AliFatal("Object of name does not inherit from given class");
//   return obj;
// }

