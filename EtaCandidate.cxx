#include "EtaCandidate.h"

#include "AliESDCaloCluster.h"

EtaCandidate::EtaCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2,
			   double vertex[3])
{
  particleMeasurements.Add( clu1 );
  particleMeasurements.Add( clu2 );
  
  TLorentzVector v1, v2;
  clu1->GetMomentum(v1, vertex);
  clu2->GetMomentum(v2, vertex);
  vector = v1 + v2;
}
