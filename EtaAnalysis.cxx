// Author: Henrik Qvigstad

#include "EtaAnalysis.h"
#include "EtaHistograms.h"

EtaAnalysis::EtaAnalysis(const EtaConfig& config)
  : EtaConfig(config),
    fOutputList(0),
    fHistograms(0)
{
}

EtaAnalysis::EtaAnalysis()

void EtaAnalysis::ProcessEvent(AliESDEvent* event)
{
  if( ! fHistograms )
    fHists = new EtaHistograms(fOutputList);
  
  TRefArray caloClusters = GetClusters();
  vector<TGDCandidate> tgdCands = ProcessTGDCandidates(caloClusters, vertex);
}


const TRefArray EtaAnalysis::GetClusters(AliESDEvent* event)
{
  TRefArray cluArray;
  for(int i=0; i< event->GetNumberOfCaloClusters(); ++i)
    {
      AliESDCaloCluster* cluster = event->GetCaloCluster(i);
      cluArray->Add( event->GetCaloCluster(i) );
    }
  return cluArray;
}


vector<TGDCandidate> ProcessTGDCandidates(const TRefArray& caloClusters, AliESDVertex* vertex)
{
  vector<TGDCandidate> candidates;
  
  for(int i1  = 0; i1 < caloClusters->GetEntries(); ++i1)
    for(int i2 = i1+1; i2 < caloClusters->GetEntries(); ++i2) {
      AliESDCaloCluster* clu1 = (AliESDCaloCluster* ) caloClusters->At(i1);
      AliESDCaloCluster* clu2 = (AliESDCaloCluster* ) caloClusters->At(i2);
      
      TGDCandidate candidate(clu1, clu2, vertex);

      double m cand.GetVector().M();
      double pt cand.GetVector().Pt();
      fHistograms->FillTGDCandidates( pt, m );
      
      candidates.push_back( cand );
    }
  return candidates;
}
