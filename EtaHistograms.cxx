#include "TH2F.h"
#include "TList.h"

EtaHistograms::EtaHistograms(TList* outputList)
  : fOutputList(outputList),
    fTGDCandidates(0)
{
}


void EtaHistograms::FillTGDCandidates(double pt, double m)
{
  if( ! fTGDCandidates )
    {
      fTGDCandidates = new TH2F("fTGDCandidates", "Two Gamma Decay Candidates", 1000, 0, 100, 1000, 0, 1);
      fTGDCandidates->GetXaxis()->SetTitle("Pt [GeV]");
      fTGDCandidates->GetYaxis()->SetTitle("IM [GeV]");
      fOutputList->Add(fTGDCandidates);
    }
  fTGDCandidates->Fill(pt, m);
}

