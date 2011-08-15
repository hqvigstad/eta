#ifndef ETAHISTOGRAMS_H
#define ETAHISTOGRAMS_H

class TH2F;
class TList;

class EtaHistograms
{
 public:
  EtaHistograms(TList* outputList);
  ~EtaHistograms();
  
  void FillEtaCandidates(double pt, double m);
  void FillNCells(double e, int nCells);
  
 private:
  TList* fOutputList;
  TH2F* fEtaCandidates;
  TH2F* fNCells;
  
};
  

#endif
