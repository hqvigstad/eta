#ifndef ETAHANDLER_H
#define ETAHANDLER_H
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

#include "TObject.h"
#include "EtaCandidate.h"

class TList;
class TRefArray;
class TH1F;
class TH2F;
class TH1;

#include <vector>
#include <string>
using namespace std;

struct EtaHanConfig 
{
  EtaHanConfig();
  double fClusterEnergyCut = 0.3;
  int fNCellCut = 3;
  //double fEtaPtCut = 1.;
  double fTrackPtCut = 5.;
};
  
EtaHanConfig::EtaHanConfig()
: fClusterEnergyCut(0.3), fNCellCut(3), fTrackPtCut(5.)
{}
  


class EtaHandler
{
 public:
  EtaHandler(); 
  ~EtaHandler();
  
  void SetOutputList(TList* list) {fOutputList = list;}
  vector<EtaCandidate> EtaCandidates(double vertex[3], TRefArray* clusters, TRefArray* clusters2 = 0);

 private:
  void CreateHistograms();

  // Conveniance Functions
  TObject* FindOutputObject(const string name, const string className);
  TH1* FindTH1(const char* const name);
  TH2* FindTH2(const char* const name);
  
  TList* fOutputList; //points to where created output is added, set at creation
  
  // Configurations
  EtaHanConfig fConfig;
  
  static const double csEtaMass = 547.853;
};

#endif
