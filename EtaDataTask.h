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
  void GetClusters(TRefArray* clusters); // fills 'clusters'
  const AliESDVertex* GetVertex(Double_t vertex[3]); // sets vertex
  const AliESDCaloCells* GetPHOSCells(); 
  
  TList* fOutputList;
  const TObject* FindOutputObject(const char* const name, 
				  const char* const clas = "TObject");
  TH1F* FindTH1F(const char* const name)
      { return (TH1F*) FindOutputObject(name, "TH1F"); }
  TH1* FindTH1(const char* const name)
      { return (TH1*) FindOutputObject(name, "TH1"); }
  
  
  ClassDef(EtaDataTask, 1);
};

#endif
