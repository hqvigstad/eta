#ifndef ETAANALYSIS_H
#define ETAANALYSIS_H
// Author: Henrik Qvigstad

#include "EtaCandidate.h"
#include "EtaPriCandidate.h"
#include "EtaConfig.h"

#include <vector>
#include <iostream>
using namespace std;

class TList;
class EtaHistograms;
class AliESDEvent;


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
  vector<EtaCandidate> ExtractEtaCandidates(const TRefArray& caloClusters, AliESDVertex* vertex);
  vector<EtaPriCandidate> ExtractEtaPriCandidates(vector<EtaCandidate> Etas, const TRefArray& tracks);

  EtaConfig fConfig;
  TList* fOutputList; 
  EtaHistograms* fHistograms;
};

#endif
