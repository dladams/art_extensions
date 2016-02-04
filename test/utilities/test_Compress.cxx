// test_Compress.cxx

// David Adams
// February 2015
//
// Test Compress and Uncompress in raw.cxx.

#include "RawData/raw.h"
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::istringstream;

typedef std::vector<short> AdcVector;

#undef NDEBUG
#include <cassert>

int test_Compress(raw::Compress_t ctype) {
  const string myname = "test_Compress: ";
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  cout << line << endl;
  cout << myname << "Testing with compression type " << ctype << endl;

  const unsigned int nadc = 3200;
  AdcVector adc0(nadc, 50);
  cout << myname << "     Initial ADC size: " << adc0.size() << endl;
  assert( adc0.size() == nadc );

  // Compress.
  AdcVector adc1(adc0);
  cout << myname << "Compressing." << endl;
  unsigned int zerothreshold = 0;
  int pedestal = 1800;
  int nearestneighbor = 0;
  bool sticky = false;
  raw::Compress(adc1, ctype, zerothreshold, pedestal, nearestneighbor, sticky);
  cout << myname << "  Compressed ADC size: " << adc1.size() << endl;
  assert( adc1.size() > 0 );
  //assert( adc1.size() <= adc0.size() );

  // Check result.
  AdcVector adc2(nadc, 0);
  cout << myname << "Uncompressing." << endl;
  raw::Uncompress(adc1, adc2, pedestal, ctype);
  cout << myname << "Uncompressed ADC size: " << adc2.size() << endl;
  assert( adc2.size() ==  adc0.size() );
  int nbad = 0;
  for ( unsigned int iadc=0; iadc<adc0.size(); ++iadc ) {
    if ( adc0[iadc] != adc2[iadc] ) {
      cout << myname << "  Mismatch for entry " << iadc << ": " << adc0[iadc] << " != " << adc2[iadc] << endl;
      ++nbad;
      if ( nbad > 20 ) break;
    }
  }
  assert( nbad == 0 );

  cout << myname << "Done." << endl;
  return 0;
}

int main(int argc, char* argv[]) {
  int logLevel = 1;
  if ( argc > 1 ) {
    istringstream ssarg(argv[1]);
    ssarg >> logLevel;
  }
  test_Compress(raw::kNone);
  test_Compress(raw::kHuffman);
  test_Compress(raw::kZeroSuppression);
  test_Compress(raw::kZeroHuffman);
  return 0;
}
