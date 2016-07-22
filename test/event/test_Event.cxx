// test_Event.cxx

// David Adams
// September 2015
//
// This test demonstrates how to use art::Event outside art.
// It is not easy to do.
//
// Suggestions for improving this are welcome.

#include "art/Framework/Principal/Event.h"
#include "art/Persistency/Provenance/ProductMetaData.h"
#include "art/Framework/Principal/EventPrincipal.h"
#include "canvas/Persistency/Provenance/ReleaseVersion.h"
#include "canvas/Persistency/Provenance/ProcessConfiguration.h"
#include "canvas/Persistency/Provenance/ModuleDescription.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using art::MasterProductRegistry;
using art::ProductMetaData;
using art::Timestamp;
using art::EventID;
using art::EventAuxiliary;
using art::ProcessConfiguration;
using art::ReleaseVersion;
using art::PassID;
using art::ModuleDescription;
using art::EventPrincipal;
using art::Event;

//**********************************************************************

// Possible dangerous trick. We duplicate the the Schedule
// class in art so we can create the required instance of
// ProductMetaData.

namespace art {

class Schedule {
public:
  MasterProductRegistry mpr;
  Schedule();
};

Schedule::Schedule() {
  ProductMetaData::create_instance(mpr);
}

}  // end namespace art

//**********************************************************************

// Helper to check ProductMetaData.
// Returns true if there is an instance of that class.

bool checkProductMetaData() {
  bool chk = false;
  try {
    ProductMetaData::instance();
    chk = true;
  } catch(...) { }
  return chk;
}

//**********************************************************************

int test_Event() {
  const string myname = "test_Event: ";
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
  assert( eid.run() == 101 );
  assert( eid.subRun() == 0 );
  assert( eid.event() == 151 );

  cout << myname << line << endl;
  cout << myname << "Create dummy scheduler (to create required instance of ProductMetaData)." << endl;
  assert( ! checkProductMetaData() );
  art::Schedule sch;
  assert( checkProductMetaData() );

  cout << myname << line << endl;
  cout << myname << "Create event auxiliary." << endl;
  Timestamp ts;
  bool isReal = false;
  EventAuxiliary eva(eid, ts, isReal, EventAuxiliary::Data);

  cout << myname << line << endl;
  cout << myname << "Create process configuration." << endl;
  fhicl::ParameterSetID fid;
  ReleaseVersion relver("myversion");
  PassID passid("mypass");;
  ProcessConfiguration prc("myprocess", fid, relver, passid);

  cout << myname << line << endl;
  cout << myname << "Create event principal." << endl;
  EventPrincipal evp(eva, prc);

  cout << myname << line << endl;
  cout << myname << "Create module description." << endl;
  ModuleDescription md;

  cout << myname << line << endl;
  cout << myname << "Create event." << endl;
  Event evt(evp, md);
  cout << "    Run: " << evt.run() << endl;
  cout << "  Event: " << evt.event() << endl;
  cout << myname << "Checking event." << endl;
  assert( evt.run() == 101 );
  assert( evt.event() == 151 );

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

//**********************************************************************

int main() {
  return test_Event();
}

//**********************************************************************
