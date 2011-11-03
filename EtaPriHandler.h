#ifndef ETAPRIHANDLER_H
#define ETAPRIHANDLER_H
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

class EtaPriHandler
{
  EtaPriHandler();
  ~EtaPriHandler();
  
  void SetOutputList(TList* list) {fOutputList = list;}
  void EtaPriCandidates(vector<EtaPriCandidate> etaPris, TRefArray* tracks, TRefArray* tracks2 = 0); 
  
 private:
  void CreateHistograms();
  
  // Conveniance Functions
  TLorentzVector GetMomentum(AliESDTrack* const track);
  TObject* FindOutputObject(const string name, const string className);
  TH1* FindTH1(const char* const name);
  TH2* FindTH2(const char* const name);

  TList* fOutputList; //points to where created output is added, set at creation
  
};

#endif
