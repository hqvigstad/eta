#ifndef TGDCANDIDATE_H
#define TGDCANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
class AliESDCaloCluster;
class AliESDVertex;
class AliESDEvent;

class TGDCandidate
{
 public:
  TGDCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2, AliESDVertex* );
  TRefArray GetParticleMeasurements() { return fParticleMeasurements; }
  const TLorentzVector& GetVector() { return fVector; }
  
 protected:
  TRefArray fParticleMeasurements;
  TLorentzVector fVector; // The measured lorentz
  AliESDVertex* fVertex;
};

#endif
