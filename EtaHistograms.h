#ifndef ETAHISTOGRAMS_H
#define ETAHISTOGRAMS_H

#include "EtaPriCandidate.h"

class TH2F;
class TList;

class EtaHistograms
{
 public:
  EtaHistograms(TList* outputList);
  ~EtaHistograms();
  
  void DrawSummery();
  
  void Fill(const EtaPriCandidate& );
  void Fill(const EtaCandidate& );
  void Fill(AliESDCaloCluster* );
  void Fill(AliESDtrack* );


  TH2F* GetEtaCandidates();
  TH2F* GetEtaPriCandidates();
  TH2F* GetNCells();

 private:
  TList* fOutputList;

  TH2F* fEtaCandidates;
  TH2F* fEtaPriCandidates;
  TH2F* fNCells;
};
  

#endif
