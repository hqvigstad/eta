// Author: Henrik Qvigstad 

#include "TGDCandidate.h"

#include "AliESDCaloCluster.h"

TGDCandidate::TGDCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2, AliESDVertex* vertex)
{
  fParticleMeasurements.Add( clu1 );
  fParticleMeasurements.Add( clu2 );
  fVertex = vertex;

  double vertex_pos[3]
  vertex->GetXYZ(vertex_pos);

  TLorentzVector v1, v2;
  clu1->GetMomentum(v1, vertex_pos);
  clu2->GetMomentum(v2, vertex_pos);
  fVector = v1 + v2;
}
