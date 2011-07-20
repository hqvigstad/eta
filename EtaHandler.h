#ifndef ETAHANDLER_H
#define ETAHANDLER_H

#include "TObject.h"
#include "EtaCandidate.h"

class TList;
class TRefArray;
class TH1F;
class TH2F;
class TH1;

#include <vector>
using namespace std;

class EtaHandler
{
 public:
  EtaHandler(TList* list); 
  ~EtaHandler();

  void CreateHistograms();
  vector<EtaCandidate> EtaCandidates(double vertex[3], TRefArray* clusters,
				   TRefArray* clusters2 = 0);
  /* void EtaPrimeCandidates(TList& addCandidatesTo, */
  /* 			  TList* Etas, TRefArray* tracks, TRefArray* tracks2);*/

 protected:
  TList* fOutputList; //points to where created output is added, set at creation

  
  TObject* FindOutputObject(const char* const name,
				  const char* const clas = "TObject");
  TH1F* FindTH1F(const char* const name)
      { return (TH1F*) FindOutputObject(name, "TH1F"); }
  TH1* FindTH1(const char* const name)
      { return (TH1*) FindOutputObject(name, "TH1"); }

};

#endif
