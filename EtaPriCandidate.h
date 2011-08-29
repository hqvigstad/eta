#ifndef ETAPRICANDIDATE_H
#define ETAPRICANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"

#include "EtaCandidate.h"
class AliESDCaloCluster;
class AliESDVertex;
class AliESDEvent;

class EtaPriCandidate
{
 public:
  EtaPriCandidate(EtaCandidate eta, AliESDtrack* track1, AliESDtrack* track2);

  EtaCandidate GetEtaCandidate() {return fEta; }
  AliESDtrack* GetTrack1() {return fTrack1;}
  AliESDtrack* GetTrack2() {return fTrack2;}
  
  const TLorentzVector& GetVector() { return fVector; }
  const AliESDVertex* GetVertex() { return fVertex }
  
 protected:
  EtaCandidate fEta;
  AliESDtrack* fTrack1;
  AliESDtrack* fTrack2;

  TLorentzVector fVector; // The measured lorentz
  AliESDVertex* fVertex;
};

#endif
