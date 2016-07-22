// test_EventID.cxx

// David Adams
// September 2015
//
// This test demonstrates how to use art::Event outside art.
// It is not easy to do.
//
// Suggestions for improving this are welcome.

#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/EventPrincipal.h"
#include "art/Persistency/Provenance/ProductMetaData.h"
#include "canvas/Persistency/Provenance/ReleaseVersion.h"
#include "canvas/Persistency/Provenance/ProcessConfiguration.h"
#include "canvas/Persistency/Provenance/ModuleDescription.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using art::EventID;

//**********************************************************************

int test_EventID() {
  const string myname = "test_EventID: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";
  string scfg;

  cout << myname << line << endl;
  cout << myname << "Create event ID." << endl;
  EventID eid(101, 0, 151);
  cout << "    Run: " << eid.run() << endl;
  cout << "  Event: " << eid.event() << endl;

  cout << myname << line << endl;
  cout << myname << "Checking event ID." << endl;
  assert( eid.run() == 101 );
  assert( eid.subRun() == 0 );
  assert( eid.event() == 151 );

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

//**********************************************************************

int main() {
  return test_EventID();
}

//**********************************************************************
