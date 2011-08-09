#ifndef ETAHISTOGRAMS_H
#define ETAHISTOGRAMS_H

class TH2F;
class TList;

class EtaHistograms
{
 public:
  EtaHistograms(TList* outputList);
  ~EtaHistograms();
  
  void FillTGDCandidates(double pt, double m);
  void FillNCells(double e, int nCells);
  
 private:
  TList* fOutputList;
  TH2F* fTGDCandidates;
  TH2F* fNCells;
  
};
  

#endif
