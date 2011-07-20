#ifndef ETACANDIDATE_H
#define ETACANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
class AliESDCaloCluster;

class EtaCandidate
{
 public:
  void AddCluster(AliESDCaloCluster* c, double vertex[3]);
  TRefArray GetParticleMeasurements() { return particleMeasurements; }
  const TLorentzVector& GetVector() { return vector; }
  
 protected:
  TRefArray particleMeasurements;
  TLorentzVector vector; // The measured lorentz
  
};

#endif
