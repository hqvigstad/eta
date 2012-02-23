#ifndef ETAHISTOGRAMS_H
#define ETAHISTOGRAMS_H
/*
Eta Prime Analysis for the ALICE Experiment.
Copyright (C) 2011 Henrik Qvigstad <henrik.qvigstad@cern.ch>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation 
version 2.1 of the License.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include "EtaPriCandidate.h"

class TH1I;
class TH2I;
class TH2F;
class TList;

class EtaHistograms
{
 public:
  EtaHistograms();
  EtaHistograms(TList* outputList);
  ~EtaHistograms();
  
  void SetOutputList(TList* list) {fOutputList = list;}
  TList* GetOutputList() {return fOutputList;}
  
  // *** Getters / Generators 
  TH2F* GetEtaCandidates();
  TH2F* GetEtaPriCandidates();
  TH2F* GetPi0Candidates();
  TH2F* GetOmegaCandidates();
  TH2F* GetNCells();
  TH2F* GetNTPCClusters();
  TH1I* GetNSelectedTracks();
  TH2I* GetTracksSelectedRatio();

 private:
  TList* fOutputList;

  TH2F* fEtaCandidates;
  TH2F* fEtaPriCandidates;
  TH2F* fPi0Candidates;
  TH2F* fOmegaCandidates;
  TH2F* fNCells;
  TH2F* fNTPCClusters;
  TH2F* fNITSClusters;
  TH1I* fNSelectedTracks;
  TH2I* fTracksSelectedRatio;

private:
  EtaHistograms(const EtaHistograms& );
  EtaHistograms& operator= (const EtaHistograms& );
};
  

#endif
