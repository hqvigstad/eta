#include "EtaHistograms.h"
// Author: Henrik Qvigstad

#include "TH2F.h"
#include "TList.h"

EtaHistograms::EtaHistograms(TList* outputList)
  : fOutputList(outputList),
    fEtaCandidates(0)
{
}


EtaHistograms::~EtaHistograms()
{}

void EtaHistograms::FillEtaCandidates(double pt, double m)
{
  if( ! fEtaCandidates )
    {
      fEtaCandidates = new TH2F("fEtaCandidates", "Two Gamma Decay Candidates", 1000, 0, 100, 1000, 0, 1);
      fEtaCandidates->GetXaxis()->SetTitle("Pt [GeV]");
      fEtaCandidates->GetYaxis()->SetTitle("IM [GeV]");
      fOutputList->Add(fEtaCandidates);
    }
  fEtaCandidates->Fill(pt, m);
}

void EtaHistograms::FillNCells(double e, int nCells)
{
  if( ! fNCells )
    {
      fNCells = new TH2F("fNCells", "Number of Cells in cluster", 1000, 0, 100, 100, 0, 100);
      fNCells->GetXaxis()->SetTitle("E [GeV]");
      fOutputList->Add(fNCells);
    }
  fNCells->Fill(e, nCells);
}
