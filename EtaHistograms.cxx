#include "EtaHistograms.h"
// Author: Henrik Qvigstad

#include "TH1I.h"
#include "TH2F.h"
#include "TList.h"
#include "TCanvas.h"

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"

EtaHistograms::EtaHistograms()
  : fOutputList(0),
    fEtaCandidates(0),
    fEtaPriCandidates(0),
    fNCells(0),
    fNTPCClusters(0),
    fNITSClusters(0),
    fNSelectedTracks(0)
{}


EtaHistograms::EtaHistograms(TList* outputList)
  : fOutputList(0),
    fEtaCandidates(0),
    fEtaPriCandidates(0),
    fNCells(0),
    fNTPCClusters(0),
    fNITSClusters(0),
    fNSelectedTracks(0)
{
  SetOutputList( outputList );
}


EtaHistograms::~EtaHistograms()
{}


TH2F* EtaHistograms::GetEtaCandidates()
{
  if( ! fEtaCandidates )
    {
      fEtaCandidates = new TH2F("fEtaCandidates", "Two Gamma Decay Candidates", 1000, 0, 100, 1000, 0, 1);
      fEtaCandidates->GetXaxis()->SetTitle("Pt [GeV]");
      fEtaCandidates->GetYaxis()->SetTitle("IM [GeV]");
      fOutputList->Add(fEtaCandidates);
    }
  
  return fEtaCandidates;
}


TH2F* EtaHistograms::GetEtaPriCandidates()
{
  if( ! fEtaPriCandidates )
    {
      fEtaPriCandidates = new TH2F("fEtaPriCandidates", "Eta Prime Candidates", 1000, 0, 100, 1000, 0, 2);
      fEtaPriCandidates->GetXaxis()->SetTitle("Pt [GeV/c]");
      fEtaPriCandidates->GetYaxis()->SetTitle("IM [GeV/c^2]");
      fOutputList->Add(fEtaCandidates);
    }
  
  return fEtaPriCandidates;
}


TH2F* EtaHistograms::GetNCells()
{
  if( ! fNCells )
    {
      fNCells = new TH2F("fNCells", "Number of Cells in cluster", 1000, 0, 100, 100, 0, 100);
      fNCells->GetXaxis()->SetTitle("E [GeV]");
      fNCells->GetYaxis()->SetTitle("N. Cells");
      if( fOutputList )
	fOutputList->Add(fNCells);
      else
	Printf("Warning: EtaHistograms::GetNCells: no list to add fNCells to");
    }
  
  return fNCells;
}


TH2F* EtaHistograms::GetNTPCClusters()
{
  if( ! fNTPCClusters )
    {
      fNTPCClusters = new TH2F("fNTPCClusters", "Number of Clusters in TPC", 1000, 0, 100, 500, 0, 500);
      fNTPCClusters->GetXaxis()->SetTitle("Pt [GeV/c]");
      fNTPCClusters->GetYaxis()->SetTitle("N. Clusters, TPC");
      fOutputList->Add(fNTPCClusters);
    }
  
  return fNTPCClusters;
}



TH1I* EtaHistograms::GetNSelectedTracks()
{
  if( ! fNSelectedTracks )
    {
      fNSelectedTracks = new TH1I("fNSelectedTracks", "fNSelectedTracks", 1000, 0, 1000);
      fNSelectedTracks->GetXaxis()->SetTitle("N. Tracks");
      fOutputList->Add(fNSelectedTracks);
    }
  return fNSelectedTracks;
}

