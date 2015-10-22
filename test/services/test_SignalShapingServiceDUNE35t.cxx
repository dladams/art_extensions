// test_SignalShapingServiceDUNE35t.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft LArProperties
// service outside the art framework.

#include "dune/Utilities/SignalShapingServiceDUNE35t.h"
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "AXService/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "Utilities/LArFFT.h"
#include "Geometry/Geometry.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::setw;

int test_SignalShapingServiceDUNE35t() {
  const string myname = "test_SignalShapingServiceDUNE35t: ";
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
  cout << myname << "Add the signal shaping service." << endl;
  bool isFile = false;
  // This doesn't work because defn is in a PROLOG.
  scfg = "services_dune.fcl";
  // This doesn't work because text must be preprocessed.
  scfg = "#include \"services_dune.fcl\"\n";
  scfg += "services: {\n";
  scfg += "user: @local::dune35t_services\n";
  scfg += "}";
  // This works if the file contains something like the above text.
  scfg = "myservices.fcl";
  isFile = true;
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("SignalShapingServiceDUNE35t", scfg, isFile) == 0 );

  cout << myname << line << endl;
  cout << myname << "Add the FFT service." << endl;
  assert( ash.addService("LArFFT", scfg, isFile) == 0 );

  cout << myname << line << endl;
  cout << myname << "Add other required services." << endl;
  assert( ash.addService("DetectorProperties", scfg, isFile) == 0 );
  assert( ash.addService("TimeService", scfg, isFile) == 0 );
  assert( ash.addService("Geometry", scfg, isFile) == 0 );
  assert( ash.addService("ExptGeoHelperInterface", scfg, isFile) == 0 );
  assert( ash.addService("LArProperties", scfg, isFile) == 0 );
  assert( ash.addService("DatabaseUtil", scfg, isFile) == 0 );

  cout << myname << "Print the services." << endl;
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );

  cout << myname << line << endl;
  cout << myname << "Get the geometry service." << endl;
  // Now because it takes time and makes noise.
  art::ServiceHandle<geo::Geometry> pgeo;

  cout << myname << line << endl;
  cout << myname << "Get the signal shaping service." << endl;
  art::ServiceHandle<util::SignalShapingServiceDUNE35t> psss;

  cout << myname << line << endl;
  cout << myname << "Retrieve shaping parameters." << endl;
  art::ServiceHandle<util::LArFFT> pfft;
  unsigned int xformSize = pfft->FFTSize();
  cout << "Transform size: " << xformSize << endl;
  cout << "Decon norm: " << psss->GetDeconNorm() << endl;
  cout << "UseFunctionFieldShape: " << psss->GetDeconNorm() << endl;
  cout << "Decon norm: " << psss->GetDeconNorm() << endl;

  cout << myname << line << endl;
  cout << myname << "Create raw data." << endl;
  vector<float> raw;
  for ( int i=0; i<20; ++i ) raw.push_back(0.0);
  raw.push_back(2.0);
  raw.push_back(4.0);
  raw.push_back(10.0);
  raw.push_back(6.0);
  raw.push_back(4.0);
  raw.push_back(2.0);
  assert( xformSize > raw.size() );

  cout << endl;
  cout << myname << "Deconvolute." << endl;
  vector<float> holder(xformSize);;
  for ( unsigned int i=0; i<raw.size(); ++i ) holder[i] = raw[i];
  psss->Deconvolute(0, holder);
  cout << "      Raw     Decon" << endl;
  for ( int unsigned i=0; i<raw.size(); ++i ) {
    cout << setw(10) << raw[i] << setw(10) << holder[i] << endl;
  }
  cout << myname << line << endl;
  cout << myname << "Close services." << endl;
  ArtServiceHelper::close();

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  test_SignalShapingServiceDUNE35t();
  return 0;
}
