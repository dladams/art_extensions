// test_huffman.cxx

// David Adams
// February 2015
//
// Test Huffman compression in lardata/RawData/raw.cxx.

#include "RawData/raw.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

typedef std::vector<short> AdcVector;

int test_huffman() {
  const string myname = "test_huffman: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";
  string scfg;

  const unsigned int nadc = 3200;
  AdcVector adc0(nadc, 1800);
  cout << myname << "     Initial ADC size: " << adc0.size() << endl;
  assert( adc0.size() == nadc );

  AdcVector adc1(adc0);
  raw::CompressHuffman(adc1);
  cout << myname << "  Compressed ADC size: " << adc1.size() << endl;
  assert( adc1.size() > 0 );
  assert( adc1.size() <= adc0.size() );

  AdcVector adc2(nadc, 0);
  raw::UncompressHuffman(adc1, adc2);
  cout << myname << "Uncompressed ADC size: " << adc2.size() << endl;
  for ( unsigned int iadc=0; iadc<adc0.size(); ++iadc ) {
    if ( adc0[iadc] != adc2[iadc] )
      cout << myname << iadc << ": " << adc0[iadc] << " != " << adc2[iadc] << endl;
    assert( adc0[iadc] == adc2[iadc] );
  }
  assert( adc2.size() ==  adc0.size() );

  cout << myname << "Done." << endl;
  return 0;
}

int main() {
  test_huffman();
  return 0;
}
