// Author: Henrik Qvigstad

#include "AliESDEvent.h"
#include "EtaAnalysis.h"
#include "AliESDVertex.h"

#include "EtaHistograms.h"

EtaAnalysis::EtaAnalysis(const EtaConfig& config)
  : fConfig(config),
    fOutputList(0),
    fHistograms(0)
{
}

EtaAnalysis::~EtaAnalysis()
{
}

void EtaAnalysis::ProcessEvent(AliESDEvent* event)
{
  if( ! fHistograms )
    fHistograms = new EtaHistograms(fOutputList);

  // Get Calorimeter Clusters
  vector<AliESDCaloCluster*> caloClusters = GetClusters(event);
  fHistograms->FillFull(caloClusters);
  caloClusters = fConfig.SelectClusters( caloClusters );

  // Get Eta Candidates
  AliESDVertex* vertex = GetVertex(event);
  vector<EtaCandidate> etaCands = ExtractEtaCandidates(caloClusters, vertex);
  fHistograms->FillFull(etaCands);
  etaCands = fConfig.SelectEtaCands( etaCands );

  // Get Tracks
  vector<AliESDtrack*> tracks = GetTracks(event);
  fHistograms->FillFull(tracks);
  tracks = fConfig.SelectTracks( tracks );

  vector<EtaPriCandidate> etaPriCands = ExtractEtaPriCandidates(etaCands, tracks);
  fHistograms->FillFull(etaPriCands);
}


vector<AliESDCaloCluster*> EtaAnalysis::GetClusters(AliESDEvent* event)
{
  vector<AliESDCaloCluster*> cluArray;
  for(int iClu=0; iClu< event->GetNumberOfCaloClusters(); ++iClu)
    cluArray.push_back( event->GetCaloCluster(iClu) );
  return cluArray;
}

vector<AliESDtrack*> EtaAnalysis::GetTracks(AliESDEvent* event)
{
  vector<AliESDtrack*> tracks

  Int_t nTracks = event->GetNumberOfTracks();
  for(Int_t iTracks = 0; iTracks < nTracks; iTracks++)
    tracks.push_back( event->GetTrack(iTracks) );
  return tracks;
}


AliESDVertex* EtaAnalysis::GetVertex(AliESDEvent* event)
{
  AliESDVertex *esdVertex = (AliESDVertex* )event->GetPrimaryVertex();
  if (!esdVertex) {
    cout << "FATAL: Vertex not found" << endl;
  }
  return esdVertex;
}


static vector<EtaCandidate> EtaAnalysis::ExtractEtaCandidates(vector<AliESDCaloCluster*> clus, AliESDVertex* vertex)
{
  vector<EtaCandidate> cands;

  for(int i1  = 0; i1 < clus.size(); ++i1)
    for(int i2 = i1+1; i2 < clus.size(); ++i2)
      cands.push_back( EtaCandidate(clus[i1], clus[i2], vertex) );

  return cands;
}


vector<EtaPriCandidate> EtaAnalysis::ExtractEtaPriCandidates(vector<EtaCandidate> etas, vector<AliESDtrack*> trks)
{
  vector<EtaPriCandidate> cands;

  for(unsigned int ie=0; ie < etas.size(); ++ie)
    for(int it1=0; it1 < tracks.GetEntries(); ++it1)
      for(int it2=it1+1; it2 < tracks.GetEntries(); ++it2)
	cands.push_back( EtaPriCandidate(etas[ie], trks[it1], trks[it2]) );

  return cands;
}


void EtaAnalysis::Terminate()
{
  fHistograms->DrawSummery();
}

