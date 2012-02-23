#ifndef EtaCANDIDATE_H
#define EtaCANDIDATE_H
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
#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
class AliVCluster;
class AliVVertex;
class AliVEvent;

class EtaCandidate
{
 public:
  EtaCandidate(AliVCluster* clu1, AliVCluster* clu2, const AliVVertex* );
  EtaCandidate(const EtaCandidate& other);
  EtaCandidate& operator= (const EtaCandidate& other);

  AliVCluster* GetCluster1() const {return fCluster1;}
  AliVCluster* GetCluster2() const {return fCluster2;}

  const TLorentzVector& GetVector() const { return fVector; }
  const AliVVertex* GetVertex() const { return fVertex; }
  
 protected:
  AliVCluster* fCluster1;
  AliVCluster* fCluster2;

  TLorentzVector fVector; // The measured lorentz
  const AliVVertex* fVertex;
};

// essentially the same structurec
typedef EtaCandidate Pi0Candidate_t;

#endif
