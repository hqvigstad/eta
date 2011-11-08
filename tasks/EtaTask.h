#ifndef ETATASK_H
#define ETATASK_H
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

class EtaAnalysis;

class TList;
class AliESDEvent;
class TRefArray;
class AliESDVertex;
class AliESDCaloCells;
class EtaHandler;
class TH1F;
class TH1;

#include <string>


#include "AliAnalysisTaskSE.h"

class EtaTask : public AliAnalysisTaskSE
{
 public:
  EtaTask(const char* name = "EtaTask");
  virtual ~EtaTask();
  
  virtual void UserCreateOutputObjects();
  virtual Bool_t UserNotify();
  virtual void UserExec(Option_t * );
  virtual void Terminate(Option_t *);

 protected:
  EtaTask(const EtaTask&);//Not Implemented
  EtaTask& operator=(const EtaTask& );//Not Implemented

  AliESDEvent* GetEvent(); // returns ESD Event
  
  EtaAnalysis* fEtaAnalysis;
  TList* fOutputList;
  
  ClassDef(EtaTask, 1);
};

#endif
