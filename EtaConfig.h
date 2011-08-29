#ifndef ETACONFIG_H
#define ETACONFIG_H
// Author: Henrik Qvigstad

#include "EtaCandidate.h"
#include "EtaPriCandidate.h"
class AliESDtrack;
class AliESDCaloCluster;

class EtaConfig
{
 public:
  EtaConfig();

  bool PassCut(const EtaPriCandidate& );
  bool PassCut(const EtaCandidate& );
  bool PassCut(AliESDtrack* );
  bool PassCut(AliESDCaloCluster* );
  

  double fCEnergyMin; // Cluster Energy Minimum
  double fEtaPtMin; // Eta Candidate Pt Minimum
  double fEtaPriPtMin; // Eta Prime Candidate Pt Minimum
  int fNCellsMin;
  double fMuonPIDMin;
  int fNTPCCMin;
  int fNITSCMin;
  double fTPtMin;
};

#endif
