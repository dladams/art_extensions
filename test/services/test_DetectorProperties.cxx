// test_DetectorProperties.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft DetectorProperties
// service outside the art framework.

#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"

#include <string>
#include <iostream>
#include "AXService/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"

using std::string;
using std::cout;
using std::endl;

int test_DetectorPropertiesService(string gname) {
  const string myname = "test_DetectorPropertiesService: ";
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
  cout << myname << "Add the DetectorPropertiesService service." << endl;
  scfg = "ElectronsToADC: 6.8906513e-3 NumberTimeSamples: 3200 ReadOutWindowSize: 3200 TimeOffsetU: 0 TimeOffsetV: 0 TimeOffsetZ: 0";
  scfg += " service_provider: DetectorPropertiesServiceStandard";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("DetectorPropertiesService", scfg) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get DetectorPropertiesService service." << endl;
  //art::ServiceHandle<detinfo::DetectorPropertiesService> pdetsrv;
  const detinfo::DetectorProperties* pdetsrv =
    art::ServiceHandle<detinfo::DetectorPropertiesService>()->provider();

  cout << myname << line << endl;
  cout << myname << "Use DetectorProperties service." << endl;
  cout << myname << "    SamplingRate: " << pdetsrv->SamplingRate() << endl;
  cout << myname << "  ElectronsToADC: " << pdetsrv->ElectronsToADC() << endl;

  // Close services.
  cout << myname << line << endl;
  cout << myname << "Close services." << endl;
  ArtServiceHelper::close();

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v5";
  test_DetectorPropertiesService(gname);
  return 0;
}
