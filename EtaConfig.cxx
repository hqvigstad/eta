#include "EtaConfig.h"
// Author: Henrik Qvigstad

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"


EtaConfig::EtaConfig()
: fClusterEnergyMin(0.3),
  fEtaPtMin(0),
  fEtaPriPtMin(0),
  fNCellsMin(3),
  fMuonPIDMin(0.0),
  fNTPClustersMin(100),
  fNITSClustersMin(0),
  fTrackPtMin(0.2)
{}


bool EtaConfig::PassCut(const EtaPriCandidate& cand , bool checkConstituents, AliESDVertex* traceTo)
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

  return false;
}


bool EtaConfig::PassCut(const EtaCandidate& cand, bool checkConstituents)
{
  if( cand.GetVector().Pt() < fEtaPtMin )
    return false;

  if( checkConstituents )
    {
      if( ! PassCut(cand.GetCluster1()) )
	return false;
      if( ! PassCut(cand.GetCluster2()) )
	return false;
    }

  return false;
}


bool EtaConfig::PassCut(AliESDtrack* track, AliESDVertex* traceTo)
{
  if( track->Pt() < fTPtMin )
    return false;
  if( ! track->IsOn(AliESDtrack::kTPCpid) )
    return false;
  if( track->GetNcls(0) < fNITSClustersMin )
    return false;
  if( track->GetNcls(1) < fNTPClustersMin )
    return false;
  
  // PID
  Double_t p[10];
  track->GetTPCpid(p);
  AliPID pid(p);
  if( pid.GetProbability(AliPID::kMuon) < fMuonPIDMin )
    return false;
  
  // Extract momentum
  // Double_t p[3]; p[0] = 0.0; p[1] = 0.0; p[2]=0.0;
  // track->GetConstrainedPxPyPz(p);
  // Double_t px_rec = p[0];
  // Double_t py_rec = p[1];
  // Double_t pz_rec = p[2];

  return true;
}

bool EtaConfig::PassCut(AliESDCaloCluster* cluster)
{
  if( cluster->E() < fClusterEnergyMin)
    return false;
  if( cluster->GetNCells() < fNCellsMin )
    return false;

  return true;
}

