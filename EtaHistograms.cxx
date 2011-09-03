#include "EtaHistograms.h"
// Author: Henrik Qvigstad

#include "TH2F.h"
#include "TList.h"
#include "TCanvas.h"

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"

EtaHistograms::EtaHistograms(TList* outputList)
  : fOutputList(outputList),
    fEtaCandidates(0),
    fEtaPriCandidates(0),
    fNCells(0)
{}


EtaHistograms::~EtaHistograms()
{}


void EtaHistograms::DrawSummery()
{
  new TCanvas;
  GetEtaCandidates()->Draw();
  new TCanvas;
  GetEtaPriCandidates()->Draw();
}

void EtaHistograms::Fill(const EtaPriCandidate& cand)
{
  TLorentzVector candVec = cand.GetVector();
  GetEtaPriCandidates()->Fill(candVec.Pt(), candVec.M());
}


void EtaHistograms::Fill(const EtaCandidate& eta)
{
  double m = eta.GetVector().M();
  double pt = eta.GetVector().Pt();
  GetEtaCandidates()->Fill(pt, m);
}

void EtaHistograms::Fill(AliESDCaloCluster* cluster)
{
  double e = cluster->E();
  double nCells = cluster->GetNCells();
  GetNCells()->Fill(e, nCells);
}


void EtaHistograms::Fill(AliESDtrack* track)
{
  
}

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
      fEtaPriCandidates->GetXaxis()->SetTitle("Pt [GeV]");
      fEtaPriCandidates->GetYaxis()->SetTitle("IM [GeV]");
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
      fOutputList->Add(fNCells);
    }
  return fNCells;
}
