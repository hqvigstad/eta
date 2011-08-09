#ifndef ETAANALYSIS_H
#define ETAANALYSIS_H
// Author: Henrik Qvigstad

#include "TGDCandidate.h"

#include <vector>
#include <iostream>
using namespace std;

class TList;
class EtaHistograms;
class AliESDEvent;

struct EtaConfig
{
  EtaConfig();
  double fCEnergyMin;
  int fNCellsMin;
};

EtaConfig::EtaConfig()
: fCEnergyMin(0.3), fNCellsMin(3)
{}

class EtaAnalysis 
{
 public:
  EtaAnalysis(const EtaConfig& config = EtaConfig());
  ~EtaAnalysis();

  void SetOutputList(TList* list) {fOutputList = list;}
  void ProcessEvent(AliESDEvent* );
  
  
 private:
  static const TRefArray GetClusters(AliESDEvent* );
  void PlotClusters(const TRefArray);
  static AliESDVertex* GetVertex(AliESDEvent* );
  vector<TGDCandidate> ProcessTGDCandidates(const TRefArray& caloClusters, AliESDVertex* vertex);

  const EtaConfig fConfig;
  TList* fOutputList; 
  EtaHistograms* fHistograms;
};

#endif
