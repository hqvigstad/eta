#include "EtaHandler.h"

#include "EtaCandidate.h"
#include "TRefArray.h"
#include "TLorentzVector.h"
#include "AliESDCaloCluster.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TIterator.h"
#include "TList.h"

#include <iostream>
using namespace std;

EtaHandler::EtaHandler(TList* list) 
{
  fOutputList = list;
  fOutputList->FirstLink(); // test, better to crash now rather then later
}

EtaHandler::~EtaHandler() 
{return;}

void EtaHandler::CreateHistograms()
{
  TH2F* fH2_GG_PtvIM = new TH2F("fH2_GG_PtvIM", "fH2_GG_PtvIM",
				200, 0, 20,  // Pt
				200, 0, 1);  // IM
  fOutputList->Add( fH2_GG_PtvIM );

  TH2F* fH2_EtaCand_PtvIM = new TH2F("fH2_EtaCand_PtvIM", "fH2_EtaCand_PtvIM",
				200, 0, 20,  // Pt
				200, 0, 1);  // IM
  fOutputList->Add( fH2_EtaCand_PtvIM );
}

vector<EtaCandidate> 
EtaHandler::EtaCandidates(double vertex[3],
			  TRefArray* cArray,  TRefArray* cArray2 )
{
  if( ! cArray2 )
    cArray2 = cArray;
  
  vector<EtaCandidate> candidates;
  
  for(int i1  = 0; i1 < cArray->GetEntries(); ++i1)
    for(int i2 = i1+1; i2 < cArray2->GetEntries(); ++i2) {
      AliESDCaloCluster* c1 = (AliESDCaloCluster* ) cArray->At(i1);
      AliESDCaloCluster* c2 = (AliESDCaloCluster* ) cArray->At(i2);
      
      EtaCandidate cand;
      cand.AddCluster(c1, vertex);
      cand.AddCluster(c2, vertex);
      
      
      double m cand.GetVector().M();
      double pt cand.GetVector().M();
      
      FindTH2("fH2_GG_PtvIM")->Fill( pt, m );
      
      if( c1->E() > sClusterEnergyCut  &&  c2->E() > sClusterEnergyCut && 
	  c1->GetNCells() >= sNCellCut  &&  c2->GetNCells() >= sNCellCut  && 
	  m > sEtaMass - sEtaMassCut  &&  m < sEtaMass + sEtaMassCutt
	  )
	{
	  FindTH1("fH2_EtaCand_PtvIM")->Fill( pt, m );
	  candidates.push_back( cand );
	}
    }
  
  return candidates;
}

void EtaHandler::EtaPrime(TList* etas, TRefArray* tracks, TRefArray* tracks2)
{
  if( ! tracks2 )
    tracks2 = tracks;
    
  vector<EtaCandidate> candidates;
  
  for(int ei = 0; ei < etas->GetEntries(); ++ei)
    for(int t1i = 0; t1i < tracks->GetEntries(); ++t1i)
      for(int t2i = i1+1; t2i < tracks2->GetEntries(); ++t2i) {
	return;
      }

}

TObject* EtaHandler::FindOutputObject(const char* const  name, 
				const char* const clas)
{
  TObject* obj = fOutputList->FindObject(name);
  if(! obj)
    cout <<"W-EtaHandler: Can't find object, name="
	 <<name<<", in fOutputList" << endl;
  if(! obj->InheritsFrom(clas) )
    cout << "W-EtaHandler: Object, name="
	 <<name<<", does not inherit from " <<clas << endl;
  return obj;
}
  
