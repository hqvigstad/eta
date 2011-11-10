#include "EtaConfig.h"
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

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"
#include "AliESDtrackCuts.h"
#include "AliESDVertex.h"
#include "TMath.h"


EtaConfig::EtaConfig()
: fClusterEnergyMin(0.3),
  fEtaPtMin(0.0),
  fEtaPriPtMin(0.0),
  fNCellsMin(3),
  fMuonPIDMin(0.0),
  fNTPCClustersMin(0),
  fNITSClustersMin(0),
  fTrackPtMin(0.5),
  fTrackChi2Max(2),
  fEtaMass(547.853),
  fEtaMassDiffMax(547.853*0.05),
  fTrackCuts(0)
{
  fTrackCuts = AliESDtrackCuts::GetStandardITSTPCTrackCuts2010();
}


EtaConfig::~EtaConfig()
{
  delete fTrackCuts;
}

bool EtaConfig::PassCut(const EtaPriCandidate& cand , bool checkConstituents, AliESDVertex* traceTo) const
{
  if( cand.GetVector().Pt() < fEtaPriPtMin )
    return false;
  if( cand.GetTrack1()->Charge() == cand.GetTrack2()->Charge() )
    return false;

  if( checkConstituents )
    {
      if( ! PassCut(cand.GetEtaCandidate(), checkConstituents) )
	return false;
      if( ! PassCut(cand.GetTrack1(), traceTo) )
	return false;
      if( ! PassCut(cand.GetTrack2(), traceTo) )
	return false;
    }

  return true;
}


bool EtaConfig::PassCut(const EtaCandidate& cand, bool checkConstituents) const
{
  if( cand.GetVector().Pt() < fEtaPtMin )
    return false;
  
  if( fEtaMassDiffMax < TMath::Abs(cand.GetVector().M()-fEtaMass) )
    return false;

  if( checkConstituents )
    {
      if( ! PassCut(cand.GetCluster1()) )
	return false;
      if( ! PassCut(cand.GetCluster2()) )
	return false;
    }

  return true;
}


bool EtaConfig::PassCut(const AliESDtrack* track, const AliESDVertex* relateToVertex) const
{
  if( track->Pt() < fTrackPtMin )
    return false;
  // if( ! track->IsOn(AliESDtrack::kTPCpid) )
  //   return false;
  // if( track->GetNcls(0) < fNITSClustersMin )
  //   return false;
  // if( track->GetNcls(1) < fNTPCClustersMin )
  //   return false;

  // Use AcceptTrack to reject to reject non standard tracks
  if( ! fTrackCuts->AcceptTrack((AliESDtrack*) track) ) // conversion is quick fix, TODO: remove, as of nov 9, AcceptTrack takes 'const AliESDtrack*' in trunk.
    return false;

  // primery track selection based on constained chi2
  // if( relateToVertex ) {
  //   if( track->GetVertexID() == relateToVertex->GetID() ) {
  //     // track is related to @relateToVertex
  //     const Char_t trackChi2 = track->GetConstrainedChi2();
  //     // assuming chi2 is not normalised by degrees of freedom
  //     // mean = 1
  //     // upper 5% percentile is lower bound by ~1.65
  //     // upper 1% percentile is lower bound by ~2.33
  //     if ( trackChi2 > fTrackChi2Max )
  // 	return false;
  //   }
  //   else
  //     // TODO: relate to vertex, for now:
  //     return false;
  // } // end if( relateToVertex )

  // PID
  // Double_t p[10];
  // track->GetTPCpid(p);
  // AliPID pid(p);
  // if( pid.GetProbability(AliPID::kMuon) < fMuonPIDMin )
  //   return false;

  // Extract momentum
  // Double_t p[3]; p[0] = 0.0; p[1] = 0.0; p[2]=0.0;
  // track->GetConstrainedPxPyPz(p);
  // Double_t px_rec = p[0];
  // Double_t py_rec = p[1];
  // Double_t pz_rec = p[2];

  return true;
}

bool EtaConfig::PassCut(const AliESDCaloCluster* cluster) const
{
  if( cluster->E() < fClusterEnergyMin)
    return false;
  if( cluster->GetNCells() < fNCellsMin )
    return false;

  return true;
}

