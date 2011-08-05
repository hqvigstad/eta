#ifndef ETACANDIDATE_H
#define ETACANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
class AliESDCaloCluster;

class EtaCandidate
{
 public:
  EtaCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2);
  TRefArray GetParticleMeasurements() { return particleMeasurements; }
  const TLorentzVector& GetVector() { return vector; }
  
 protected:
  TRefArray particleMeasurements;
  TLorentzVector vector; // The measured lorentz
  
};

#endif
