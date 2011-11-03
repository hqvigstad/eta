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

#include "AliESDEvent.h"
#include "EtaAnalysis.h"
#include "AliESDVertex.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

#include "EtaHistograms.h"

#include <iostream>
using namespace std;

EtaAnalysis::EtaAnalysis()
  : fConfig(new EtaConfig),
    fOutputList(0),
    fHistograms(new EtaHistograms ),
    fVerbose(1)
{
}

EtaAnalysis::EtaAnalysis(const EtaConfig* config)
  : fConfig(new EtaConfig(*config)),
    fOutputList(0),
    fHistograms(new EtaHistograms ),
    fVerbose(1)
{
}

EtaAnalysis::~EtaAnalysis()
{
  delete fConfig;
  delete fHistograms;
}


void EtaAnalysis::SetOutputList(TList* list)
{
  fOutputList = list;
  fHistograms->SetOutputList(list);
}

void EtaAnalysis::ProcessEvent(AliESDEvent* event)
{
  // Get Calorimeter Clusters
  const vector<AliESDCaloCluster*> caloClusters = GetClusters(event);
  const vector<AliESDCaloCluster*> selectedCaloClusters = SelectClusters( caloClusters, fConfig );

  // Get Eta Candidates
  const AliESDVertex* vertex = GetVertex(event);
  const vector<EtaCandidate> etaCands = ExtractEtaCandidates(selectedCaloClusters, vertex);
  const vector<EtaCandidate> selectedEtaCands = SelectEtaCands( etaCands, fConfig );

  // Get Tracks
  const vector<AliESDtrack*> tracks = GetTracks(event);
  const vector<AliESDtrack*> selectedTracks = SelectTracks( tracks, fConfig );

  // Get Eta Prime Candidates
  const vector<EtaPriCandidate> etaPriCands = ExtractEtaPriCandidates(selectedEtaCands, selectedTracks);

  FillFull(caloClusters);
  FillFull( etaCands );
  FillFull(tracks);
  FillFull(etaPriCands);

  fHistograms->GetNSelectedTracks()->Fill( selectedTracks.size() );
    
    if( fVerbose ) {
    cout << "Number Calo. Clusters:" << caloClusters.size()
	 << ", selected:" << selectedCaloClusters.size() << endl;
    cout << "Number Tracks:" << tracks.size()
	 << ", selected:" << selectedTracks.size() << endl;
  }
}


const vector<AliESDCaloCluster*> EtaAnalysis::GetClusters(const AliESDEvent* event)
{
  vector<AliESDCaloCluster*> cluArray;
  for(int iClu=0; iClu< event->GetNumberOfCaloClusters(); ++iClu)
    cluArray.push_back( event->GetCaloCluster(iClu) );
  return cluArray;
}

const vector<AliESDtrack*> EtaAnalysis::GetTracks(const AliESDEvent* event)
{
  vector<AliESDtrack*> tracks;
  
  Int_t nTracks = event->GetNumberOfTracks();
  for(Int_t iTracks = 0; iTracks < nTracks; iTracks++)
    tracks.push_back( event->GetTrack(iTracks) );
  return tracks;
}


const AliESDVertex* EtaAnalysis::GetVertex(const AliESDEvent* event)
{
  AliESDVertex *esdVertex = (AliESDVertex* )event->GetPrimaryVertex();
  if (!esdVertex) {
    cout << "FATAL: Vertex not found" << endl;
  }
  return esdVertex;
}


const vector<EtaCandidate> EtaAnalysis::ExtractEtaCandidates(const vector<AliESDCaloCluster*> & clus, const AliESDVertex* vertex)
{
  vector<EtaCandidate> cands;

  for(int i1  = 0; i1 < (int)clus.size(); ++i1)
    for(int i2 = i1+1; i2 < (int)clus.size(); ++i2)
      cands.push_back( EtaCandidate(clus[i1], clus[i2], vertex) );

  return cands;
}


const vector<EtaPriCandidate> EtaAnalysis::ExtractEtaPriCandidates(const vector<EtaCandidate> & etas, const vector<AliESDtrack*> & tracks)
{
  vector<EtaPriCandidate> cands;

  for(unsigned int ie=0; ie < etas.size(); ++ie)
    for(int it1=0; it1 < (int)tracks.size(); ++it1)
      for(int it2=it1+1; it2 < (int)tracks.size(); ++it2)
	cands.push_back( EtaPriCandidate(etas[ie], tracks[it1], tracks[it2]) );

  return cands;
}


void EtaAnalysis::Terminate()
{
  new TCanvas;
  fHistograms->GetEtaCandidates()->Draw();
  new TCanvas;
  fHistograms->GetEtaPriCandidates()->Draw();
}


void EtaAnalysis::FillFull( const vector<AliESDCaloCluster*>  clus)
{
  for(unsigned int i=0; i<clus.size(); ++i)
    {
      double e = clus[i]->E();
      double nCells = clus[i]->GetNCells();
      fHistograms->GetNCells()->Fill(e, nCells);
    }
}


void EtaAnalysis::FillFull( const vector<AliESDtrack*> trks)
{
  vector<AliESDtrack*>::const_iterator iter;
  for(iter = trks.begin(); iter < trks.end(); iter++)
    {
      double pt = (*iter)->Pt();
      double nTPCClusters = (*iter)->GetNcls(1);
      fHistograms->GetNTPCClusters()->Fill(pt, nTPCClusters );
    }
}


void EtaAnalysis::FillFull( const vector<EtaCandidate> cands)
{
  for(int idx=0; idx < (int)cands.size(); ++idx)
    {
      double pt = cands[idx].GetVector().Pt();
      double m = cands[idx].GetVector().M();
      fHistograms->GetEtaCandidates()->Fill(pt, m );
    }
}


void EtaAnalysis::FillFull( const vector<EtaPriCandidate> cands)
{
  for(int i=0; i < (int)cands.size(); ++i)
    {
      double pt = cands[i].GetVector().Pt();
      double m = cands[i].GetVector().M();
      fHistograms->GetEtaPriCandidates()->Fill(pt, m );
    }
}


const vector<AliESDCaloCluster*> EtaAnalysis::SelectClusters(const vector<AliESDCaloCluster*>&  clusters, const EtaConfig* config)
{
  vector<AliESDCaloCluster*> selected;
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


const vector<AliESDtrack*> EtaAnalysis::SelectTracks(const vector<AliESDtrack*>& tracks, const EtaConfig* config, const AliESDVertex* vertex)
{
  vector<AliESDtrack*> selected;
  for(unsigned int ti = 0; ti < tracks.size(); ti++)
    if( config->PassCut( tracks[ti], vertex ) )
      selected.push_back( tracks[ti] );
  return selected;
}
