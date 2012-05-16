#include "EtaConfig.h"
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

#include "etaparameters.h"
using namespace EtaParameters;

#include "AliESDCaloCluster.h"
#include "AliESDtrack.h"
#include "AliESDtrackCuts.h"
#include "AliESDVertex.h"
#include "TMath.h"

#include <iostream>
using namespace std;

ClassImp(EtaConfig)

EtaConfig::EtaConfig()
: TObject(),
  fEnableEMCAL(false),
  fClusterEnergyMin(0.5),
  fNCellsMin(3),
  fDistToBadCellMin(2),
  fTrackPtMin(0.0),
  fCheckPionPID(0.0),
  fTrackChi2Max(2),
  fEtaPtMin(1.0),
  fEtaMass(0.547853),
  fEtaMassDiffMax(fEtaMass*0.05),
  fPi0PtMin(0.5),
  fPi0Mass(0.1349766),
  fPi0MassDiffMax(fPi0Mass*0.05),
  fEtaPriPtMin(0.0),
  fTrackCuts(0),
  fVerbose(SILENT)
{
  //fTrackCuts = AliESDtrackCuts::GetStandardITSTPCTrackCuts2010();
  return;
}


EtaConfig::EtaConfig(const EtaConfig & obj)
: TObject(obj),
  fEnableEMCAL(false),
  fClusterEnergyMin(0.3),
  fNCellsMin(3),
  fDistToBadCellMin(2),
  fTrackPtMin(0.0),
  fCheckPionPID(0.0),
  fTrackChi2Max(2),
  fEtaPtMin(0.0),
  fEtaMass(0.547853),
  fEtaMassDiffMax(fEtaMass*0.05),
  fPi0PtMin(0.0),
  fPi0Mass(0.1349766),
  fPi0MassDiffMax(fPi0Mass*0.05),
  fEtaPriPtMin(0.0),
  fTrackCuts(0),
  fVerbose(SILENT)
{
  obj.Copy(*this);
}


EtaConfig& EtaConfig::operator=(const EtaConfig & obj)
{
  obj.Copy(*this);
  return *this;
}


EtaConfig::~EtaConfig()
{
  delete fTrackCuts;
  return;
}

void EtaConfig::Copy(TObject & obj) const
{
  if(&obj == this)
    return;
  
  TObject::Copy(obj);
  
  ((EtaConfig&)obj).fClusterEnergyMin = this->fClusterEnergyMin;
  ((EtaConfig&)obj).fNCellsMin = this->fNCellsMin;
  ((EtaConfig&)obj).fDistToBadCellMin = this->fDistToBadCellMin;
  
  ((EtaConfig&)obj).fTrackPtMin = this->fTrackPtMin;
  ((EtaConfig&)obj).fCheckPionPID = this->fCheckPionPID;

  ((EtaConfig&)obj).fEtaPtMin = this->fEtaPtMin;
  ((EtaConfig&)obj).fEtaMass = this->fEtaMass;
  ((EtaConfig&)obj).fEtaMassDiffMax = this->fEtaMassDiffMax;

  ((EtaConfig&)obj).fEtaPriPtMin = this->fEtaPriPtMin;
  
  if(fTrackCuts)
    ((EtaConfig&)obj).fTrackCuts = new AliESDtrackCuts(*fTrackCuts);
}

bool EtaConfig::PassEtaPrime(const EtaPriCandidate& cand , bool checkConstituents, AliVVertex* traceTo) const
{
  if( cand.GetVector().Pt() < fEtaPriPtMin )
    return false;
  if( cand.GetTrack1()->Charge() == cand.GetTrack2()->Charge() )
    return false;

  if( checkConstituents )
    {
      if( ! PassEta(cand.GetEtaCandidate(), checkConstituents) )
	return false;
      if( ! PassTrack(cand.GetTrack1(), traceTo) )
	return false;
      if( ! PassTrack(cand.GetTrack2(), traceTo) )
	return false;
    }

  return true;
}


bool EtaConfig::PassEta(const EtaCandidate& cand, bool checkConstituents) const
{
  if( cand.GetVector().Pt() < fEtaPtMin )
    return false;

  if( fEtaMassDiffMax < TMath::Abs(cand.GetVector().M()-fEtaMass) )
    return false;

  if( checkConstituents )
    {
      if( ! PassCluster(cand.GetCluster1()) )
	return false;
      if( ! PassCluster(cand.GetCluster2()) )
	return false;
    }

  return true;
}


bool EtaConfig::PassPi0(const Pi0Candidate_t& cand, bool checkConstituents) const
{
  if( cand.GetVector().Pt() < fPi0PtMin )
    return false;

  if( fPi0MassDiffMax < TMath::Abs(cand.GetVector().M()-fPi0Mass) )
    return false;

  if( checkConstituents )
    {
      if( ! PassCluster(cand.GetCluster1()) )
	return false;
      if( ! PassCluster(cand.GetCluster2()) )
	return false;
    }

  return true;
}


bool EtaConfig::PassTrack(const AliVTrack* track, const AliVVertex* relateToVertex) const
{
  if( track->Pt() < fTrackPtMin )
    return false;


  const AliESDtrack* esdTrack = dynamic_cast<const AliESDtrack*>(track);

  // PID
  if( esdTrack && fCheckPionPID ) {
    Double_t pids[10];
    esdTrack->GetTPCpid(pids);
    AliPID pid(pids);
    if( pid.GetProbability(AliPID::kPion) < pid.GetProbability(AliPID::kMuon) 
	|| pid.GetProbability(AliPID::kPion) < pid.GetProbability(AliPID::kElectron) 
	|| pid.GetProbability(AliPID::kPion) < pid.GetProbability(AliPID::kKaon) 
	|| pid.GetProbability(AliPID::kPion) < pid.GetProbability(AliPID::kProton) 
	)
      return false;
  }

  // Use AcceptTrack to reject to reject non standard tracks
  if( fTrackCuts && esdTrack && ! fTrackCuts->AcceptTrack((AliESDtrack*) track) )
    return false;


  
  // primery track selection based on constained chi2
  // if( relateToVertex ) {
  //   if( track->GetVertexID() == relateToVertex->GetID() ) {
  //     // track is related to @relateToVertex
  //     const Char_t trackChi2 = track->GetConstrainedChi2();
  //     // assuming chi2 is not normalised by degrees of freedom
  //     // mean = 1
  //     // upper 5% percentile is lower bound by ~1.65
  //     // upper 1% percentile is lower bound by ~2.33
  //     if ( trackChi2 > fTrackChi2Max )
  // 	return false;
  //   }
  //   else
  //     // TODO: relate to vertex, for now:
  //     return false;
  // } // end if( relateToVertex )

  // Extract momentum
  // Double_t p[3]; p[0] = 0.0; p[1] = 0.0; p[2]=0.0;
  // track->GetConstrainedPxPyPz(p);
  // Double_t px_rec = p[0];
  // Double_t py_rec = p[1];
  // Double_t pz_rec = p[2];

  return true;
}

bool EtaConfig::PassCluster(const AliVCluster* cluster) const
{
  if( ! fEnableEMCAL && cluster->IsEMCAL() ) {
    if( EtaParameters::TRACK <= fVerbose )
      Print("EtaConfig::PassCluster reject: cluster: EMCAL not enabled");
    return false;
  }
  if( cluster->E() < fClusterEnergyMin ) {
    if( EtaParameters::TRACK <= fVerbose )
      Printf("EtaConfig::PassCluster reject: cluster: energy cut, e:%f  cut:%f", cluster->E(), fClusterEnergyMin);
    return false;
  }
  if( cluster->GetNCells() < fNCellsMin ) {
    if( EtaParameters::TRACK <= fVerbose )
      Printf("EtaConfig::PassCluster reject: cluster: nCells cut, nCells:%d  cut:%d", cluster->GetNCells(), fNCellsMin);
    return false;
  }
  if( cluster->GetDistanceToBadChannel() < fDistToBadCellMin ) {
    if( EtaParameters::TRACK <= fVerbose )
      Printf("EtaConfig::PassCluster: reject cluster: distToBad: dist:%f  cut:%f", cluster->GetDistanceToBadChannel(), fDistToBadCellMin);
    return false;
  }

 
   if( TRACK_EXTRA <= fVerbose )
     Printf("EtaConfig::PassCluster: cluster passed");
  return true;
}

