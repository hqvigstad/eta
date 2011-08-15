#ifndef EtaCANDIDATE_H
#define EtaCANDIDATE_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TRefArray.h"
class AliESDCaloCluster;
class AliESDVertex;
class AliESDEvent;

class EtaCandidate
{
 public:
  EtaCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2, AliESDVertex* );

  AliESDtrack* GetTrack1() {return fTrack1;}
  AliESDtrack* GetTrack2() {return fTrack2;}

  const TLorentzVector& GetVector() { return fVector; }
  
 protected:
  AliESDCaloCluster* fCluster1;
  AliESDCaloCluster* fCluster2;

  TLorentzVector fVector; // The measured lorentz
  AliESDVertex* fVertex;
};

#endif
