#ifndef ETAPRIHANDLER_H
#define ETAPRIHANDLER_H

class EtaPriHandler
{
  EtaPriHandler();
  ~EtaPriHandler();
  
  void SetOutputList(TList* list) {fOutputList = list;}
  void EtaPriCandidates(vector<EtaPriCandidate> etaPris, TRefArray* tracks, TRefArray* tracks2 = 0); 
  
 private:
  void CreateHistograms();
  
  // Conveniance Functions
  TLorentzVector GetMomentum(AliESDTrack* const track);
  TObject* FindOutputObject(const string name, const string className);
  TH1* FindTH1(const char* const name);
  TH2* FindTH2(const char* const name);

  TList* fOutputList; //points to where created output is added, set at creation
  
};

#endif
