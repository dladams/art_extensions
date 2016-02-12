// StandardMsgService.h

// David Adams
// Febraury 2016
//
// Standard implementation of the service MsgService.
//
// Parameters:
//    Loglevel - 0: Never show message.
//               1: Show message at initialization only.
//               2: And show for each call to show.
//    Message - Message to display.

#include <string>
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"

class StandardMsgService {

public:

  // Natural ctor from params.
  StandardMsgService(fhicl::ParameterSet const& pset);

  // Ctor required by art.
  StandardMsgService(fhicl::ParameterSet const& pset, art::ActivityRegistry& reg);

  // Show message.
  int show() const;

private:

  // Parameters.
  int fLogLevel;
  std::string fMessage;

};
