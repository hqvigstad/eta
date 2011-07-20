#include "EtaCandidate.h"

#include "AliESDCaloCluster.h"


void EtaCandidate::AddCluster(AliESDCaloCluster* cluster, double vertex[3])
{
  particleMeasurements.Add( cluster );
  
  TLorentzVector tempvec;
  cluster->GetMomentum(tempvec, vertex);
  vector += tempvec;
}
