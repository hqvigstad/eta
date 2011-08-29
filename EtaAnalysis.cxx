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
{}

void EtaAnalysis::ProcessEvent(AliESDEvent* event)
{
  if( ! fHistograms )
    fHistograms = new EtaHistograms(fOutputList);
  
  const TRefArray caloClusters = GetClusters(event);
  AliESDVertex* vertex = GetVertex(event);
  vector<EtaCandidate> etaCands = ExtractEtaCandidates(caloClusters, vertex);
  const TRefArray tracks = GetTracks(event);
  vector<EtaPriCandidate> etaPriCands = ExtractEtaPriCandidates(etaCands, tracks);

  vector<EtaPriCandidate>::iterator cand;
  for ( cand = etaPriCands.begin(); cand < etaPriCands.end(); ++cand )
    if ( fConfig->PassCut( *cand ) )
      fHistograms->Fill(*cand);
	 
}


const TRefArray EtaAnalysis::GetClusters(AliESDEvent* event)
{
  TRefArray cluArray;
  for(int iClu=0; iClu< event->GetNumberOfCaloClusters(); ++iClu)
    {
      AliESDCaloCluster* cluster = event->GetCaloCluster(iClu);
      fHistograms->FillNCells(cluster->E(), cluster->GetNCells() );

      // if pass Energy & N.Cells cut.
      //if(fConfig.fNCellsMin <= Energy  &&  fConfig.fCEnergyMin <= Energy )
      cluArray.Add( cluster );
    }
  return cluArray;
}

const TRefArray EtaAnalysis::GetTracks(AliESDEvent* event)
{
  TRefArray tracks;
  
  Int_t nTracks = event->GetNumberOfTracks();
  for(Int_t iTracks = 0; iTracks < nTracks; iTracks++) 
    {
      AliESDtrack *track = event->GetTrack(iTracks);
      tracks.Add(track);
    }
}


AliESDVertex* EtaAnalysis::GetVertex(AliESDEvent* event)
{
  AliESDVertex *esdVertex = (AliESDVertex* )event->GetPrimaryVertex();
  if (!esdVertex) {
    cout << "FATAL: Vertex not found" << endl;
  } 
  return esdVertex;
}


vector<EtaCandidate> EtaAnalysis::ExtractEtaCandidates(const TRefArray& caloClusters, AliESDVertex* vertex)
{
  vector<EtaCandidate> candidates;
   
  for(int i1  = 0; i1 < caloClusters.GetEntries(); ++i1)
    for(int i2 = i1+1; i2 < caloClusters.GetEntries(); ++i2) {
      AliESDCaloCluster* clu1 = (AliESDCaloCluster* ) caloClusters.At(i1);
      AliESDCaloCluster* clu2 = (AliESDCaloCluster* ) caloClusters.At(i2);
      
      EtaCandidate candidate(clu1, clu2, vertex);

      double m = candidate.GetVector().M();
      double pt = candidate.GetVector().Pt();
      fHistograms->FillEtaCandidates( pt, m );
      
      candidates.push_back( candidate );
    }
  return candidates;
}


vector<EtaPriCandidate> EtaAnalysis::ExtractEtaPriCandidates(vector<EtaCandidate> etas, const TRefArray& tracks)
{
  vector<EtaPriCandidate> candidates

    for(int iEta=0; iEta < etas.size(); ++iEta) 
    for(int iTrk1=0; iTrk1 < tracks.GetEntires(); ++iTrk1)
      for(int iTrk2=iTk1+1; iTrk2 < tracks.GetEntries(); ++iTrk2)
	{
	  EtaCandidate eta = etas[iEta];
	  AliESDtrack track1 = (AliESDtrack*) tracks[iTrk1];
	  AliESDtrack track2 = (AliESDtrack*) tracks[iTrk2];
	  
	  if( track1->Charge() != track2->Charge() )
	    {
	      EtaCandidate candidate = EtaPriCandidate(eta, track1, track2);
	      candidates.push_back( candidate );
	    }
	}
}
