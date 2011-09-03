#include "EtaConfig.h"

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"

EtaConfig::EtaConfig()
: fCEnergyMin(0.3), 
  fEtaPtMin(0),
  fEtaPriPtMin(0),
  fNCellsMin(3),
  fMuonPIDMin(0.6),
  fNTPCCMin(100),
  fNITSCMin(0),
  fTPtMin(0.3)
{}

bool EtaConfig::PassCut(const EtaPriCandidate& cand )
{
  if( cand.GetVector().Pt() > fEtaPriPtMin 
      && PassCut( cand.GetEtaCandidate() )
      && cand.GetTrack1()->Charge() != cand.GetTrack2()->Charge()
      && PassCut( cand.GetTrack1() ) 
      && PassCut( cand.GetTrack2() )
      )
    return true;
  else 
    return false;
}

bool EtaConfig::PassCut(const EtaCandidate& cand)
{
  if( cand.GetVector().Pt() > fEtaPtMin 
      && PassCut( cand.GetCluster1() ) 
      && PassCut( cand.GetCluster2() )
      )
    return true;
  else 
    return false;
}

bool EtaConfig::PassCut(AliESDtrack* track)
{
  // Extract momentum
  // Double_t p[3]; p[0] = 0.0; p[1] = 0.0; p[2]=0.0;
  // track->GetConstrainedPxPyPz(p);
  // Double_t px_rec = p[0];
  // Double_t py_rec = p[1];
  // Double_t pz_rec = p[2];

  if( track->Pt() > fTPtMin 
      && track->IsOn(AliESDtrack::kTPCpid)
      && track->GetNcls(0) >= fNITSCMin
      && track->GetNcls(1) >= fNTPCCMin
      ) {
    Double_t p[10]; 
    track->GetTPCpid(p);
    AliPID pid(p);
    if( pid.GetProbability(AliPID::kMuon) > fMuonPIDMin )
      return true;
  }
  return false;
}

bool EtaConfig::PassCut(AliESDCaloCluster* cluster)
{
  if( cluster->E() > fCEnergyMin
      && cluster->GetNCells() > fNCellsMin
      )
    return true;
  else
    return false;
}
 
