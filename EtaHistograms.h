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
  
  void Fill(EtaPriCandidate );
  void FillEtaCandidates(double pt, double m);
  void FillNCells(double e, int nCells);
  
 private:
  TList* fOutputList;
  TH2F* fEtaCandidates;
  TH2F* fEtaPriCandidates;
  TH2F* fNCells;
};
  

#endif
