#include "EtaOutput.h"
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
#include "TH2I.h"
#include "TH2F.h"
#include "TList.h"
#include "TCanvas.h"

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"

EtaOutput::EtaOutput()
  : fOutputList(0),
    fEtaCandidates(0),
    fEtaPriCandidates(0),
    fPi0Candidates(0),
    fOmegaCandidates(0),
    fNCells(0),
    fNTPCClusters(0),
    fNITSClusters(0),
    fNSelectedTracks(0),
    fTracksSelectedRatio(0)
{}


EtaOutput::EtaOutput(TList* outputList)
  : fOutputList(0),
    fEtaCandidates(0),
    fEtaPriCandidates(0),
    fPi0Candidates(0),
    fOmegaCandidates(0),
    fNCells(0),
    fNTPCClusters(0),
    fNITSClusters(0),
    fNSelectedTracks(0),
    fTracksSelectedRatio(0)
{
  SetOutputList( outputList );
}


EtaOutput::~EtaOutput()
{}


TH2F* EtaOutput::GetEtaCandidates()
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


TH2F* EtaOutput::GetEtaPriCandidates()
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


TH2F* EtaOutput::GetPi0Candidates()
{
  if( ! fPi0Candidates )
    {
      fPi0Candidates = new TH2F("fPi0Candidates", "Two Gamma Decay Candidates", 1000, 0, 100, 1000, 0, 1);
      fPi0Candidates->GetXaxis()->SetTitle("Pt [GeV]");
      fPi0Candidates->GetYaxis()->SetTitle("IM [GeV]");
      if( fOutputList )
	fOutputList->Add(fPi0Candidates);
    }
  
  return fPi0Candidates;
}


TH2F* EtaOutput::GetOmegaCandidates()
{
  if( ! fOmegaCandidates )
    {
      fOmegaCandidates = new TH2F("fOmegaCandidates", "Two Gamma Decay Candidates", 1000, 0, 100, 1000, 0, 1);
      fOmegaCandidates->GetXaxis()->SetTitle("Pt [GeV]");
      fOmegaCandidates->GetYaxis()->SetTitle("IM [GeV]");
      if( fOutputList )
	fOutputList->Add(fOmegaCandidates);
    }
  
  return fOmegaCandidates;
}


TH2F* EtaOutput::GetNCells()
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


TH2F* EtaOutput::GetNTPCClusters()
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



TH1I* EtaOutput::GetNSelectedTracks()
{
  if( ! fNSelectedTracks )
    {
      fNSelectedTracks = new TH1I("fNSelectedTracks", "Number of Selected Tracks", 1000, 0, 1000);
      fNSelectedTracks->GetXaxis()->SetTitle("N. Selected Tracks");
      if( fOutputList )
	fOutputList->Add(fNSelectedTracks);
    }
  return fNSelectedTracks;
}

TH2I* EtaOutput::GetTracksSelectedRatio()
{
  if( ! fTracksSelectedRatio )
    {
      fTracksSelectedRatio = new TH2I("fTracksSelectedRatio", "The ratio of tracks to selected tracks", 1000, 0, 1000, 1100, 0, 1.1);
      fTracksSelectedRatio->GetXaxis()->SetTitle("N. Tracks");
      fTracksSelectedRatio->GetYaxis()->SetTitle("Selected / Total tracks");
      if( fOutputList )
	fOutputList->Add( fTracksSelectedRatio );
    }
  return fTracksSelectedRatio;
}
