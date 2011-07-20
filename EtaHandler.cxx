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
}

vector<EtaCandidate> 
EtaHandler::EtaCandidates(double vertex[3],
			  TRefArray* cArray,  TRefArray* cArray2 )
{
  if( ! cArray2 )
    cArray2 = cArray;
  
  vector<EtaCandidate> candidates;
  
  for(int i1  = 0; i1 < cArray->GetEntries(); ++i1)
    for(int i2 = i1; i2 < cArray2->GetEntries(); ++i2) {
      AliESDCaloCluster* c1 = (AliESDCaloCluster* ) cArray->At(i1);
      AliESDCaloCluster* c2 = (AliESDCaloCluster* ) cArray->At(i2);
      
      EtaCandidate cand;
      cand.AddCluster(c1, vertex);
      cand.AddCluster(c2, vertex);
      
      if( c1->E() > 0.5 && c2->E() > 0.5 // Cluster Energy
	  )
	{
	  candidates.push_back(cand);
	  cout << cand.GetVector().M() << endl;
	  // Ploting
	  FindTH1("fH2_GG_PtvIM")->Fill( cand.GetVector().Pt(),
					 cand.GetVector().M());
	}
    }
  
  return candidates;
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
  
