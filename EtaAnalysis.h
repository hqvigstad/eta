#ifndef ETAANALYSIS_H
#define ETAANALYSIS_H
// Author: Henrik Qvigstad

#include "EtaCandidate.h"

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
  const TRefArray GetClusters(AliESDEvent* );
  const TRefArray GetTracks(AliESDEvent* );
  static AliESDVertex* GetVertex(AliESDEvent* );
  vector<EtaCandidate> ProcessEtaCandidates(const TRefArray& caloClusters, AliESDVertex* vertex);
  void ProcessEtaPriCandidates(vector<EtaCandidate> Etas, const TRefArray& tracks);

  const EtaConfig fConfig;
  TList* fOutputList; 
  EtaHistograms* fHistograms;
};

#endif
