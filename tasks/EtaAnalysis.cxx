#include "EtaAnalysis.h"
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


/*
 * Class for containing the instance of an eta analysis.
 * Use by feeding AliVEvents through member: ProcessEvent()
 * results are in form of histograms added to list set
 * by SetOutputList().
 */

ClassImp(EtaAnalysis)

#include "AliVParticle.h"
#include "AliESDEvent.h"

#include "AliMCEvent.h"
#include "AliESDVertex.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TList.h"

#include "EtaHistograms.h"

#include <iostream>
using namespace std;

EtaAnalysis::EtaAnalysis()
  : fConfig(new EtaConfig),
    fOutputList(0),
    fHistograms(new EtaHistograms ),
    fVerbose(1)
{
  // default constructor
}

EtaAnalysis::EtaAnalysis(const EtaConfig* config)
  : fConfig(new EtaConfig(*config)),
    fOutputList(0),
    fHistograms(new EtaHistograms ),
    fVerbose(0)
{
  // constructor for setting non standard configurations
}

EtaAnalysis::~EtaAnalysis()
{
  // destructor
  delete fConfig;
  delete fHistograms;
}


void EtaAnalysis::ProcessEvent(AliVEvent* event, AliMCEvent* mcEvent)
{
  // @event is analysed and its candidates are filled into the histograms.

  // Get Calorimeter Clusters
  const vector<AliVCluster*> caloClusters = GetClusters(event);
  const vector<AliVCluster*> selectedCaloClusters = SelectClusters( caloClusters, fConfig );

  // Get Eta Candidates
  const AliVVertex* vertex = GetVertex(event);
  const vector<EtaCandidate> etaCands = ExtractEtaCandidates(selectedCaloClusters, vertex);
  const vector<EtaCandidate> selectedEtaCands = SelectEtaCands( etaCands, fConfig );

  // Get Pi0 Candidates
  const vector<Pi0Candidate_t> selectedPi0Cands = SelectPi0Cands( etaCands, fConfig );

  // Get Tracks
  const vector<AliVParticle*> tracks = GetTracks(event);
  const vector<AliVParticle*> selectedTracks = SelectTracks( tracks, fConfig );

  // Get Eta Prime Candidates
  const vector<EtaPriCandidate> etaPriCands = ExtractEtaPriCandidates(selectedEtaCands, selectedTracks);

  // Get Omega Candidates
  const vector<OmegaCandidate_t> omegaCands = ExtractEtaPriCandidates(selectedPi0Cands, selectedTracks);



  // Fill Histograms
  FillFull(caloClusters, mcEvent);
  FillFull( etaCands, mcEvent);
  FillFull(tracks, mcEvent);
  FillFull(etaPriCands, mcEvent);
  FillFullOmegas(omegaCands, mcEvent);

  fHistograms->GetNSelectedTracks()->Fill( selectedTracks.size() );
  if( tracks.size() )
    fHistograms->GetTracksSelectedRatio()->Fill( selectedTracks.size(), double(selectedTracks.size())/tracks.size());

  if( fVerbose ) {
    cout << "Number Calo. Clusters:" << caloClusters.size()
	 << ", selected:" << selectedCaloClusters.size() << endl;
    cout << "Number Tracks:" << tracks.size()
	 << ", selected:" << selectedTracks.size() << endl;
  }
}



void EtaAnalysis::SetConfig(const EtaConfig* config)
{
  fConfig->operator=(*config);
}


void EtaAnalysis::SetOutputList(TList* list)
{
  // sets list where result histograms are added
  fOutputList = list;
  fHistograms->SetOutputList(list);
  fOutputList->Add(fConfig);
}


void EtaAnalysis::Terminate()
{
  // new TCanvas;
  // fHistograms->GetEtaCandidates()->Draw();
  // new TCanvas;
  // fHistograms->GetEtaPriCandidates()->Draw();
  Printf("-Number of eta/pi0 candidates: %d", int(fHistograms->GetEtaCandidates()->GetEntries()));
  Printf("-Number of omega candidates: %d", int(fHistograms->GetOmegaCandidates()->GetEntries()));
  Printf("-Number of eta' candidates: %d", int(fHistograms->GetEtaPriCandidates()->GetEntries()));
  printf("\n");
}


const vector<AliVCluster*> EtaAnalysis::GetClusters(const AliVEvent* event)
{
  vector<AliVCluster*> cluArray;
  for(int iClu=0; iClu< event->GetNumberOfCaloClusters(); ++iClu)
    cluArray.push_back( event->GetCaloCluster(iClu) );
  return cluArray;
}

const vector<AliVParticle*> EtaAnalysis::GetTracks(const AliVEvent* event)
{
  vector<AliVParticle*> tracks;

  Int_t nTracks = event->GetNumberOfTracks();
  for(Int_t iTracks = 0; iTracks < nTracks; iTracks++)
    tracks.push_back( event->GetTrack(iTracks) );
  return tracks;
}


const AliVVertex* EtaAnalysis::GetVertex(const AliVEvent* event)
{
  AliVVertex *esdVertex = (AliVVertex* )event->GetPrimaryVertex();
  if (!esdVertex) {
    cout << "FATAL: Vertex not found" << endl;
  }
  return esdVertex;
}


const vector<EtaCandidate> EtaAnalysis::ExtractEtaCandidates(const vector<AliVCluster*> & clus, const AliVVertex* vertex)
{
  vector<EtaCandidate> cands;

  for(int i1  = 0; i1 < (int)clus.size(); ++i1)
    for(int i2 = i1+1; i2 < (int)clus.size(); ++i2)
      cands.push_back( EtaCandidate(clus[i1], clus[i2], vertex) );

  return cands;
}


const vector<EtaPriCandidate> EtaAnalysis::ExtractEtaPriCandidates(const vector<EtaCandidate> & etas, const vector<AliVParticle*> & tracks)
{
  vector<EtaPriCandidate> cands;

  for(unsigned int ie=0; ie < etas.size(); ++ie)
    for(int it1=0; it1 < (int)tracks.size(); ++it1)
      for(int it2=it1+1; it2 < (int)tracks.size(); ++it2)
	cands.push_back( EtaPriCandidate(etas[ie], tracks[it1], tracks[it2]) );

  return cands;
}


void EtaAnalysis::FillFull( const vector<AliVCluster*>  clus, AliMCEvent* mce)
{
  for(unsigned int i=0; i<clus.size(); ++i)
    {
      double e = clus[i]->E();
      double nCells = clus[i]->GetNCells();
      fHistograms->GetNCells()->Fill(e, nCells);
    }
  if( mce )
    Printf("EtaAnalysis::FillFull does not use its AliMCEvent*");
}


void EtaAnalysis::FillFull( const vector<AliVParticle*> trks, AliMCEvent* mce)
{
  vector<AliVParticle*>::const_iterator iter;
  for(iter = trks.begin(); iter < trks.end(); iter++)
    {
      double pt = (*iter)->Pt();
      //double nTPCClusters = (*iter)->GetNcls(1);
      //fHistograms->GetNTPCClusters()->Fill(pt, nTPCClusters );
    }
  if( mce )
    Printf("EtaAnalysis::FillFull does not use its AliMCEvent*");
}


void EtaAnalysis::FillFull( const vector<EtaCandidate> cands, AliMCEvent* mce)
{
  for(int idx=0; idx < (int)cands.size(); ++idx)
    {
      double pt = cands[idx].GetVector().Pt();
      double m = cands[idx].GetVector().M();
      fHistograms->GetEtaCandidates()->Fill(pt, m );
    }
  if( mce )
    Printf("EtaAnalysis::FillFull does not use its AliMCEvent*");
}


void EtaAnalysis::FillFull( const vector<EtaPriCandidate> cands, AliMCEvent* mce)
{
  for(int i=0; i < (int)cands.size(); ++i)
    {
      double pt = cands[i].GetVector().Pt();
      double m = cands[i].GetVector().M();
      fHistograms->GetEtaPriCandidates()->Fill(pt, m );
    }
  if( mce )
    Printf("EtaAnalysis::FillFull does not use its AliMCEvent*");
}


void EtaAnalysis::FillFullOmegas( vector<OmegaCandidate_t> cands, AliMCEvent* mce )
{
  for(int i=0; i < (int)cands.size(); ++i)
    {
      double pt = cands[i].GetVector().Pt();
      double m = cands[i].GetVector().M();
      fHistograms->GetOmegaCandidates()->Fill(pt, m );
    }
  if( mce )
    Printf("EtaAnalysis::FillFull does not use its AliMCEvent*");
}


const vector<AliVCluster*> EtaAnalysis::SelectClusters(const vector<AliVCluster*>&  clusters, const EtaConfig* config)
{
  vector<AliVCluster*> selected;
  for(unsigned int ci = 0; ci < clusters.size(); ci++)
    if( config->PassCut(clusters[ci]) )
      selected.push_back( clusters[ci] );
  return selected;
}


const vector<EtaCandidate> EtaAnalysis::SelectEtaCands(const vector<EtaCandidate>& etas, const EtaConfig* config )
{
  vector<EtaCandidate> selected;
  for(unsigned int ei = 0; ei < etas.size(); ei++)
    if( config->PassCut(etas[ei]) )
      selected.push_back( etas[ei] );
  return selected;
}


const vector<Pi0Candidate_t> EtaAnalysis::SelectPi0Cands(const vector<EtaCandidate>& pi0s, const EtaConfig* config )
{
  vector<Pi0Candidate_t> selected;
  for(unsigned int pi = 0; pi < pi0s.size(); pi++)
    if( config->PassCutPi0(pi0s[pi]) )
      selected.push_back( pi0s[pi] );
  return selected;

}


const vector<AliVParticle*> EtaAnalysis::SelectTracks(const vector<AliVParticle*>& tracks, const EtaConfig* config, const AliVVertex* vertex)
{
  vector<AliVParticle*> selected;
  for(unsigned int ti = 0; ti < tracks.size(); ti++)
    if( config->PassCut( tracks[ti], vertex ) )
      selected.push_back( tracks[ti] );
  return selected;
}


