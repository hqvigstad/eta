#include "EtaPriCandidate.h"

EtaPriCandidate::EtaPriCandidate(EtaCandidate eta, AliESDtrack* track1, AliESDtrack* track2)
  : fEta(eta),
    fTrack1(track1),
    fTrack2(track2),
    fVector(),
    fVertex(eta.GetVertex())
{
  double pvec1[3], pvec2[3];
  track1->GetConstrainedPxPyPz(pvec1);
  track2->GetConstrainedPxPyPz(pvec2);
  TLorentzVector lVec1(pvec1);
  TLorentzVector lVec2(pvec2);
  
  fVector = lVec1 + lVec2 + eta.GetVector();
}
