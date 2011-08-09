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
  PlotClusters(caloClusters);
  AliESDVertex* vertex = GetVertex(event);
  vector<TGDCandidate> tgdCands = ProcessTGDCandidates(caloClusters, vertex);
}


const TRefArray EtaAnalysis::GetClusters(AliESDEvent* event)
{
  TRefArray cluArray;
  for(int i=0; i< event->GetNumberOfCaloClusters(); ++i)
    {
      cluArray.Add( event->GetCaloCluster(i) );
      
    }
  return cluArray;
}

void EtaAnalysis::PlotClusters(const TRefArray caloClusters)
{
  for(int i1  = 0; i1 < caloClusters.GetEntries(); ++i1)
    {
      AliESDCaloCluster* clu1 = (AliESDCaloCluster* ) caloClusters.At(i1);
      double Energy = clu1->E();
      int nCells = clu1->GetNCells();

      // if pass Energy & N.Cells cut.
      if(fConfig.fNCellsMin <= Energy  &&  fConfig.fCEnergyMin <= Energy )
	fHistograms->FillNCells(Energy, nCells );
    }
}


vector<TGDCandidate> EtaAnalysis::ProcessTGDCandidates(const TRefArray& caloClusters, AliESDVertex* vertex)
{
  vector<TGDCandidate> candidates;
   
  for(int i1  = 0; i1 < caloClusters.GetEntries(); ++i1)
    for(int i2 = i1+1; i2 < caloClusters.GetEntries(); ++i2) {
      AliESDCaloCluster* clu1 = (AliESDCaloCluster* ) caloClusters.At(i1);
      AliESDCaloCluster* clu2 = (AliESDCaloCluster* ) caloClusters.At(i2);
      
      TGDCandidate candidate(clu1, clu2, vertex);

      double m = candidate.GetVector().M();
      double pt = candidate.GetVector().Pt();
      fHistograms->FillTGDCandidates( pt, m );
      
      candidates.push_back( candidate );
    }
  return candidates;
}


AliESDVertex* EtaAnalysis::GetVertex(AliESDEvent* event)
{
  AliESDVertex *esdVertex = (AliESDVertex* )event->GetPrimaryVertex();
  if (!esdVertex) {
    cout << "FATAL: Vertex not found" << endl;
  } 
  return esdVertex;
}
