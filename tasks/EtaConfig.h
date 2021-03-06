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

#include "etaparameters.h"

class AliVTrack;
class AliVCluster;
class AliESDtrackCuts;

#include "TObject.h"

class EtaConfig : public TObject
{
 public:
  EtaConfig();
  EtaConfig(const EtaConfig & );
  EtaConfig& operator=(const EtaConfig & );
  virtual ~EtaConfig();
  
  virtual void Copy(TObject & ) const;
  
  Bool_t PassEtaPrime(const EtaPriCandidate& , Bool_t checkConstituents = false , AliVVertex* relateToVertex = 0) const;
  Bool_t PassEta(const EtaCandidate& , Bool_t checkConstituents = false ) const;
  Bool_t PassPi0(const Pi0Candidate_t& , Bool_t checkConstituents = false ) const;
  Bool_t PassTrack(const AliVTrack* , const AliVVertex* traceTo = 0) const;
  Bool_t PassCluster(const AliVCluster* ) const;
  
  // Cluster Cut Parameters
  Bool_t fEnableEMCAL;
  Double_t fClusterEnergyMin;
  Int_t fNCellsMin;
  Double_t fDistToBadCellMin;
  // Track Cut Parameters
  Double_t fTrackPtMin;
  Bool_t fCheckPionPID;
  Double_t fTrackChi2Max;
  // Eta Cut Parameters
  Double_t fEtaPtMin;
  Double_t fEtaMass;
  Double_t fEtaMassDiffMax;
  // Pi0 Parameters
  Double_t fPi0PtMin;
  Double_t fPi0Mass;
  Double_t fPi0MassDiffMax;
  // Eta Prime Cut Parameters
  Double_t fEtaPriPtMin;

  Int_t fVerbose;

 private:
  AliESDtrackCuts* fTrackCuts;
  
  ClassDef(EtaConfig, 1)
};

#endif
