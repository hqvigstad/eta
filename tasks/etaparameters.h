#ifndef ETAPARAMETERS_H
#define ETAPARAMETERS_H

namespace EtaParameters {

  Int_t kEtap = 331;

  enum Verbose { SILENT=0,
		 FLOW=10, // flow of analysis
		 EVENT=20, // event level
		 CANDIDATE=30, // candidate level
		 TRACK=40, // Track, cluster
		 TRACK_EXTRA=45
  };
  
}

#endif