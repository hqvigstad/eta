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
#include "AliESDCaloCluster.h"
#include "AliESDVertex.h"
#include "AliESDEvent.h"

EtaCandidate::EtaCandidate(AliVCluster* clu1, AliVCluster* clu2, const AliVVertex* vertex)
  : fCluster1(clu1),
    fCluster2(clu2),
    fVector(),
    fVertex(vertex)
{

  // extract vertex pos.
  double vertex_pos[3];
  fVertex->GetXYZ(vertex_pos);

  // Determine fVector
  TLorentzVector v1, v2;
  fCluster1->GetMomentum(v1, vertex_pos);
  fCluster2->GetMomentum(v2, vertex_pos);
  fVector = v1 + v2;
}
