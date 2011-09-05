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
class AliESDCaloCluster;
class AliESDtrack;


class EtaAnalysis 
{
 public:
  EtaAnalysis(const EtaConfig& config = EtaConfig());
  ~EtaAnalysis();

  void SetOutputList(TList* list) {fOutputList = list;}
  void ProcessEvent(AliESDEvent* );
  
  void Terminate();
  
  static vector<AliESDCaloCluster*> GetClusters(AliESDEvent* );
  static vector<AliESDtrack*> GetTracks(AliESDEvent* );
  static AliESDVertex* GetVertex(AliESDEvent* );
  static vector<EtaCandidate> ExtractEtaCandidates(vector<AliESDCaloCluster*>, AliESDVertex* );
  static vector<EtaPriCandidate> ExtractEtaPriCandidates(vector<EtaCandidate> , vector<AliESDtrack*>);

 private:
  EtaConfig fConfig;
  TList* fOutputList; 
  EtaHistograms* fHistograms;
};

#endif
