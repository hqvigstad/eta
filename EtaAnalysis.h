#ifndef ETAANALYSIS_H
#define ETAANALYSIS_H
// Author: Henrik Qvigstad

#include "EtaCandidate.h"
#include "EtaPriCandidate.h"
#include "EtaConfig.h"
#include "EtaHistograms.h"

#include <vector>
#include <iostream>
using namespace std;

class TList;
class AliESDEvent;
class AliESDCaloCluster;
class AliESDtrack;


class EtaAnalysis 
{
 public:
  EtaAnalysis();
  EtaAnalysis(const EtaConfig* config);
  ~EtaAnalysis();

  void SetOutputList(TList* list);
  void ProcessEvent(AliESDEvent* );
  
  void Terminate();

  void FillFull( vector<AliESDCaloCluster*> );
  void FillFull( vector<AliESDtrack*> );
  void FillFull( vector<EtaCandidate> );
  void FillFull( vector<EtaPriCandidate> );

  static const vector<AliESDCaloCluster*> GetClusters(const AliESDEvent* );
  static const vector<AliESDtrack*> GetTracks(const AliESDEvent* );
  static const AliESDVertex* GetVertex(const AliESDEvent* );

  static const vector<EtaCandidate> ExtractEtaCandidates(const vector<AliESDCaloCluster*>& , const AliESDVertex* );
  static const vector<EtaPriCandidate> ExtractEtaPriCandidates(const vector<EtaCandidate>& , const vector<AliESDtrack*>&); 
  
  static const vector<AliESDCaloCluster*> SelectClusters(const vector<AliESDCaloCluster*>& , const EtaConfig* );
  static const vector<EtaCandidate> SelectEtaCands(const vector<EtaCandidate>& , const EtaConfig* );
  static const vector<AliESDtrack*> SelectTracks(const vector<AliESDtrack*>& , const EtaConfig*, const AliESDVertex* vertex = 0 );

 private:
  EtaConfig* fConfig;
  TList* fOutputList; 
  EtaHistograms* fHistograms;
  
  int fVerbose;
};

#endif
