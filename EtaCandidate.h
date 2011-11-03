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
  EtaCandidate(AliESDCaloCluster* clu1, AliESDCaloCluster* clu2, const AliESDVertex* );

  AliESDCaloCluster* GetCluster1() const {return fCluster1;}
  AliESDCaloCluster* GetCluster2() const {return fCluster2;}

  const TLorentzVector& GetVector() const { return fVector; }
  const AliESDVertex* GetVertex() const { return fVertex; }
  
 protected:
  AliESDCaloCluster* fCluster1;
  AliESDCaloCluster* fCluster2;

  TLorentzVector fVector; // The measured lorentz
  const AliESDVertex* fVertex;
};

#endif
