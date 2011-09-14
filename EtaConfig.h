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

  bool PassCut(const EtaPriCandidate& , bool checkConstituents = false , AliESDVertex* traceTo = 0) const;
  bool PassCut(const EtaCandidate& , bool checkConstituents = false ) const;
  bool PassCut(AliESDtrack* , AliESDVertex* traceTo = 0) const;
  bool PassCut(AliESDCaloCluster* ) const;

  double fClusterEnergyMin;
  double fEtaPtMin;
  double fEtaPriPtMin;
  int fNCellsMin;
  double fMuonPIDMin;
  int fNTPCClustersMin;
  int fNITSClustersMin;
  double fTrackPtMin;
};

#endif
