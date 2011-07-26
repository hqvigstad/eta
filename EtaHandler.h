#ifndef ETAHANDLER_H
#define ETAHANDLER_H

#include "TObject.h"
#include "EtaCandidate.h"

class TList;
class TRefArray;
class TH1F;
class TH2F;
class TH1;

#include <vector>
using namespace std;

class EtaHandler
{
 public:
  EtaHandler(TList* list); 
  ~EtaHandler();

  void CreateHistograms();
  vector<EtaCandidate> EtaCandidates(double vertex[3], TRefArray* clusters,
				   TRefArray* clusters2 = 0);
  void EtaPrime(TList* etas, TRefArray* tracks, TRefArray* tracks2 = 0);

 protected:
  TList* fOutputList; //points to where created output is added, set at creation
  
  TLorentzVector GetMomentum(AliESDTrack* track);
  TObject* FindOutputObject(const char* const name,
				  const char* const clas = "TObject");
  TH1* FindTH1(const char* const name)
      { return (TH1*) FindOutputObject(name, "TH1"); }
  TH1F* FindTH2(const char* const name)
      { return (TH2*) FindOutputObject(name, "TH2"); }
  
  static const double sClusterEnergyCut = 0.3;
  static const int sNCellCut = 3;
  static const double sEtaMass = 547.853;
  static const double sEtaMassCut = 100.;
  // static const double sEtaPtCut = 1.;
  static const double sTrackPtCut = 5.;
  
};

#endif
