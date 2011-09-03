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
}

Bool_t EtaDataTask::UserNotify()
{
  return kTRUE;
}
  
void EtaDataTask::UserExec(Option_t* )
{
  AliESDEvent* event = GetEvent();
  fEtaAnalysis->ProcessEvent(event);
  
  PostData(1, fOutputList);
}

void EtaDataTask::Terminate(Option_t* )
{
  fEtaAnalysis->Terminate();
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

