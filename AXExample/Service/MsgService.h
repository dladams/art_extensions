// MsgService.h

// David Adams
// February 2016

// Interface for example message service.

#include "art/Framework/Services/Registry/ServiceMacros.h"

class MyService {

public:

  // Action.
  // A message should be displayed each time this is called.
  virtual int show() const =0;

};
