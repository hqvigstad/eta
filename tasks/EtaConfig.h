#ifndef ETACONFIG_H
#define ETACONFIG_H
/*
Eta Prime Analysis for the ALICE Experiment.
Copyright (C) 2011 Henrik Qvigstad <henrik.qvigstad@cern.ch>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation 
version 2.1 of the License.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "EtaCandidate.h"
#include "EtaPriCandidate.h"
class AliESDtrack;
class AliESDCaloCluster;
class AliESDtrackCuts;

class EtaConfig
{
 public:
  EtaConfig();
  ~EtaConfig();
  
  bool PassCut(const EtaPriCandidate& , bool checkConstituents = false , AliESDVertex* relateToVertex = 0) const;
  bool PassCut(const EtaCandidate& , bool checkConstituents = false ) const;
  bool PassCut(const AliESDtrack* , const AliESDVertex* traceTo = 0) const;
  bool PassCut(const AliESDCaloCluster* ) const;

  double fClusterEnergyMin;
  double fEtaPtMin;
  double fEtaPriPtMin;
  int fNCellsMin;
  double fMuonPIDMin;
  int fNTPCClustersMin;
  int fNITSClustersMin;
  double fTrackPtMin;
  double fTrackChi2Max;
  double fEtaMass;
  double fEtaMassDiffMax;

 private:
  AliESDtrackCuts* fTrackCuts;
};

#endif
