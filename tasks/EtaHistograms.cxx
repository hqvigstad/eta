#include "EtaHistograms.h"
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
      if( fOutputList )
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
      if( fOutputList )
	fOutputList->Add(fEtaPriCandidates);
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
      if( fOutputList )
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
      if( fOutputList )
	fOutputList->Add(fNSelectedTracks);
    }
  return fNSelectedTracks;
}

