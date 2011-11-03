#ifndef ETAHISTOGRAMS_H
#define ETAHISTOGRAMS_H

#include "EtaPriCandidate.h"

class TH1I;
class TH2F;
class TList;

class EtaHistograms
{
 public:
  EtaHistograms();
  EtaHistograms(TList* outputList);
  ~EtaHistograms();
  
  void SetOutputList(TList* list) {fOutputList = list;}
  TList* GetOutputList() {return fOutputList;}
  
  // *** Getters / Generators 
  TH2F* GetEtaCandidates();
  TH2F* GetEtaPriCandidates();
  TH2F* GetNCells();
  TH2F* GetNTPCClusters();
  TH1I* GetNSelectedTracks();

 private:
  TList* fOutputList;

  TH2F* fEtaCandidates;
  TH2F* fEtaPriCandidates;
  TH2F* fNCells;
  TH2F* fNTPCClusters;
  TH2F* fNITSClusters;
  TH1I* fNSelectedTracks;
};
  

#endif
