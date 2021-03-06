#ifndef ETAPRICANDIDATE_H
#define ETAPRICANDIDATE_H
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

#include "EtaCandidate.h"
class AliVCluster;
class AliVVertex;
class AliVEvent;
class AliVTrack;

class EtaPriCandidate
{
 public:
  EtaPriCandidate(EtaCandidate eta, const AliVTrack* track1, const AliVTrack* track2);
  EtaPriCandidate(const EtaPriCandidate& );
  EtaPriCandidate& operator= (const EtaPriCandidate& );

  const EtaCandidate& GetEtaCandidate() const {return fEta; }
  const AliVTrack* GetTrack1() const {return fTrack1;}
  const AliVTrack* GetTrack2() const {return fTrack2;}
  
  const TLorentzVector& GetVector() const { return fVector; }
  const AliVVertex* GetVertex() const { return fEta.GetVertex(); }
  
 protected:
  EtaCandidate fEta;
  const AliVTrack* fTrack1;
  const AliVTrack* fTrack2;

  TLorentzVector fVector; // The measured lorentz

};

// essentially the same structurec
typedef EtaPriCandidate OmegaCandidate_t;

#endif
