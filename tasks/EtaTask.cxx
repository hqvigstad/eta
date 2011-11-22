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

#include "EtaTask.h"
#include "EtaConfig.h"

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
#include "AliMCEvent.h"
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

ClassImp(EtaTask);

EtaTask::EtaTask(const char* name)
  : AliAnalysisTaskSE(name),
    fEtaAnalysis(0),
    fOutputList(0)
{
  DefineOutput(1, TList::Class());

  fEtaAnalysis = new EtaAnalysis();
}


EtaTask::~EtaTask()
{
  delete fEtaAnalysis;
  delete fOutputList;
}

void EtaTask::UserCreateOutputObjects()
{
  fOutputList = new TList();
  fOutputList->SetOwner();

  EtaConfig* config = new EtaConfig;

  fEtaAnalysis->SetOutputList(fOutputList);
  PostData(1, fOutputList);

  delete config;
}

Bool_t EtaTask::UserNotify()
{
  return kTRUE;
}

void EtaTask::UserExec(Option_t* )
{
  AliESDEvent* event = GetEvent();
  AliMCEvent* mcEvent = MCEvent();
  fEtaAnalysis->ProcessEvent(event, mcEvent);

  PostData(1, fOutputList);
}

void EtaTask::Terminate(Option_t* )
{
  Printf("%s::Terminate:", GetName());
  fEtaAnalysis->Terminate();
}


void EtaTask::SetConfig(const EtaConfig* config)
{
  fEtaAnalysis->SetConfig(config);
}


AliESDEvent* EtaTask::GetEvent()
{
  AliVEvent *event = InputEvent();
  if (!event)
    AliFatal("Could not retrieve event");
  if(! event->InheritsFrom("AliESDEvent"))
      AliFatal("Event is not ESD");
  return ( (AliESDEvent*) event);
}


