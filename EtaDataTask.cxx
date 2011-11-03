/*
Eta Prime Analysis for the ALICE Experiment.
Copyright (C) 2011 Henrik Qvigstad <henrik.qvigstad@cern.ch>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation 
version 2.1 of the License.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

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
  delete fEtaAnalysis;
  delete fOutputList;
}

void EtaDataTask::UserCreateOutputObjects()
{
  fOutputList = new TList();
  fOutputList->SetOwner();
  
  EtaConfig* config = new EtaConfig;
  
  fEtaAnalysis = new EtaAnalysis(config);
  fEtaAnalysis->SetOutputList(fOutputList);
  PostData(1, fOutputList);

  delete config;
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

