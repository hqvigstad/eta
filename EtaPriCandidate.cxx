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
#include "EtaPriCandidate.h"
#include "EtaCandidate.h"
#include "AliESDtrack.h"

EtaPriCandidate::EtaPriCandidate(EtaCandidate eta, const AliESDtrack* track1, const AliESDtrack* track2)
  : fEta(eta),
    fTrack1(track1),
    fTrack2(track2),
    fVector()
{
  double pvec1[3], pvec2[3];
  track1->GetConstrainedPxPyPz(pvec1);
  track2->GetConstrainedPxPyPz(pvec2);
  TLorentzVector lVec1(pvec1);
  TLorentzVector lVec2(pvec2);
  
  fVector = lVec1 + lVec2 + eta.GetVector();
}
