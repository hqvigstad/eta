// Author: Henrik Qvigstad 

#include "EtaCandidate.h"
#include "AliESDCaloCluster.h"
#include "AliESDVertex.h"
#include "AliESDEvent.h"

EtaCandidate::EtaCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2, AliESDVertex* vertex)
  : fCluster1(clu1),
    fCluster2(clu2),
    fVector(),
    fVertex(0)
{

  // Set and extract vertex pos.
  fVertex = vertex;
  Double vertex_pos[3];
  vertex->GetXYZ(vertex_pos);

  // Determine fVector
  TLorentzVector v1, v2;
  fCluster1->GetMomentum(v1, vertex_pos);
  fCluster2->GetMomentum(v2, vertex_pos);
  fVector = v1 + v2;
}
