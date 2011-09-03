#ifndef ETAPRICANDIDATE_H
#define ETAPRICANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"

#include "EtaCandidate.h"
class AliESDCaloCluster;
class AliESDVertex;
class AliESDEvent;
class AliESDtrack;

class EtaPriCandidate
{
 public:
  EtaPriCandidate(EtaCandidate eta, AliESDtrack* track1, AliESDtrack* track2);

  const EtaCandidate& GetEtaCandidate() const {return fEta; }
  AliESDtrack* GetTrack1() const {return fTrack1;}
  AliESDtrack* GetTrack2() const {return fTrack2;}
  
  const TLorentzVector& GetVector() const { return fVector; }
  AliESDVertex* GetVertex() const { return fEta.GetVertex(); }
  
 protected:
  EtaCandidate fEta;
  AliESDtrack* fTrack1;
  AliESDtrack* fTrack2;

  TLorentzVector fVector; // The measured lorentz
};

#endif
