#ifndef ETADATATASK_H
#define ETADATATASK_H

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

class EtaDataTask : public AliAnalysisTaskSE
{
 public:
  EtaDataTask(const char* name = "EtaDataTask");
  virtual ~EtaDataTask();
  
  virtual void UserCreateOutputObjects();
  virtual Bool_t UserNotify();
  virtual void UserExec(Option_t * );
  virtual void Terminate(Option_t *);

 protected:
  EtaDataTask(const EtaDataTask&);//Not Implemented
  EtaDataTask& operator=(const EtaDataTask& );//Not Implemented

  const AliESDEvent* GetEvent(); // returns ESD Event
  
  EtaAnalysis* fEtaAnalysis;
  TList* fOutputList;
  
  ClassDef(EtaDataTask, 1);
};

#endif
