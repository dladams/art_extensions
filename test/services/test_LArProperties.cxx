// test_LArProperties.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft LArProperties
// service outside the art framework.

#include "Utilities/LArProperties.h"

#include <string>
#include <iostream>
#include "AXService/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"

using std::string;
using std::cout;
using std::endl;

int test_LArProperties(string gname) {
  const string myname = "test_LArProperties: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";
  string scfg;

  cout << myname << line << endl;
  cout << myname << "Fetch art service helper." << endl;
  ArtServiceHelper& ash = ArtServiceHelper::instance();

  cout << myname << line << endl;
  cout << myname << "Add the LArProperties service." << endl;
  scfg = "prodsingle_dune35t.fcl";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("LArProperties", scfg, true) == 0 );

  cout << myname << line << endl;
  cout << myname << "Add the DatabaseUtil service." << endl;
  scfg = "DBHostName: \"fnalpgsdev.fnal.gov\" DBName: \"dune_dev\" DBUser: \"dune_reader\" PassFileName: \".lpswd\" Port: 5438 ShouldConnect: false TableName: \"main_run\" ToughErrorTreatment: false";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("DatabaseUtil", scfg) == 0 );

  cout << myname << line << endl;
  cout << myname << "Print the services." << endl;
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );

  cout << myname << line << endl;
  cout << myname << "Get LArProperties service." << endl;
  art::ServiceHandle<util::LArProperties> plarsrv;

  cout << myname << line << endl;
  cout << myname << "Use LArProperties service." << endl;
  cout << myname << "    LAr Density: " << plarsrv->Density() << endl;
  cout << myname << "  DriftVelocity: " << plarsrv->DriftVelocity() << endl;

  cout << myname << line << endl;
  cout << myname << "Close services." << endl;
  ArtServiceHelper::close();

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v5";
  test_LArProperties(gname);
  return 0;
}
