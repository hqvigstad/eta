 #ifndef ETAANALYSIS_H
#define ETAANALYSIS_H
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

#include "EtaCandidate.h"
#include "EtaPriCandidate.h"
#include "EtaConfig.h"
#include "EtaHistograms.h"

#include <vector>
#include <iostream>
using namespace std;

class TList;
class AliVEvent;
class AliMCEvent;
class AliVCaloCluster;
class AliVtrack;

#include "TObject.h"

/*
 * Class for containing the instance of an eta analysis.
 */
class EtaAnalysis : public TObject
{
 public:
  EtaAnalysis();
  EtaAnalysis(const EtaConfig* config);
  
  ~EtaAnalysis();

  void ProcessEvent(AliVEvent* , AliMCEvent* mce = 0);

  void SetConfig(const EtaConfig* config);
  void SetOutputList(TList* list);
  void SetVerbose(int verbose) {fVerbose = verbose;}

  void Terminate();

  
 private:
  EtaAnalysis(const EtaAnalysis & ); // Not Implemented
  EtaAnalysis& operator= (const EtaAnalysis & ); // Not Implemented

  EtaConfig* fConfig; // the Configuration for the analysis
  TList* fOutputList; // the list fHistogram is to add to
  EtaHistograms* fHistograms; // histograms

  // *** Configurations ***
  Int_t fVerbose; // level of verbosity =0: quiet, =1: low, =2: medium, =3: high

  // *** Procedural Functions ***
  void FillFull( vector<AliVCaloCluster*>, AliMCEvent* mce = 0 );
  void FillFull( vector<AliVtrack*>, AliMCEvent* mce = 0 );
  void FillFull( vector<EtaCandidate>, AliMCEvent* mce = 0 );
  void FillFull( vector<EtaPriCandidate>, AliMCEvent* mce = 0 );
  void FillFullOmegas( vector<OmegaCandidate_t>, AliMCEvent* mce = 0 );


  // *** Functional Functions **
  static const vector<AliVCaloCluster*> GetClusters(const AliVEvent* );
  static const vector<AliVtrack*> GetTracks(const AliVEvent* );
  static const AliVVertex* GetVertex(const AliVEvent* );

  static const vector<EtaCandidate> ExtractEtaCandidates(const vector<AliVCaloCluster*>& , const AliVVertex* );
  static const vector<EtaPriCandidate> ExtractEtaPriCandidates(const vector<EtaCandidate>& , const vector<AliVtrack*>&);
  static const vector<AliVCaloCluster*> SelectClusters(const vector<AliVCaloCluster*>& , const EtaConfig* );
  static const vector<EtaCandidate> SelectEtaCands(const vector<EtaCandidate>& , const EtaConfig* );
  static const vector<Pi0Candidate_t> SelectPi0Cands(const vector<EtaCandidate>& , const EtaConfig* );
  static const vector<AliVtrack*> SelectTracks(const vector<AliVtrack*>& , const EtaConfig*, const AliVVertex* vertex = 0 );

  ClassDef(EtaAnalysis, 1)
};

#endif
