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

  AliESDCaloCluster* GetCluster1() const {return fCluster1;}
  AliESDCaloCluster* GetCluster2() const {return fCluster2;}

  const TLorentzVector& GetVector() const { return fVector; }
  AliESDVertex* GetVertex() const { return fVertex; }
  
 protected:
  AliESDCaloCluster* fCluster1;
  AliESDCaloCluster* fCluster2;

  TLorentzVector fVector; // The measured lorentz
  AliESDVertex* fVertex;
};

#endif
