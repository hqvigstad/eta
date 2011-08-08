#ifndef ETACANDIDATE_H
#define ETACANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
class AliESDCaloCluster;
class AliESDVertex;

class EtaCandidate
{
 public:
  EtaCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2, double vertex[3]);
  TRefArray GetParticleMeasurements() { return particleMeasurements; }
  const TLorentzVector& GetVector() { return vector; }
  
 protected:
  TRefArray fParticleMeasurements;
  TLorentzVector fVector; // The measured lorentz
  AliESDVertex fVertex;
};

#endif
