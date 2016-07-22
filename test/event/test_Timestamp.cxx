// test_Timestamp.cxx

// David Adams
// September 2015
//
// This test demonstrates how to use art::Timestamp.

#include "canvas/Persistency/Provenance/Timestamp.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdint.h>

using std::string;
using std::cout;
using std::endl;
using std::setw;
using std::uint32_t;
using std::uint64_t;

// Convert Nova time (64 MHz ticks since 2010) to an art
// timestamp where high word is unix time (sec since 1970)
// and low word is the remainder in ns.
art::Timestamp novaTimeToArtTime(int64_t novaTime) {
  const uint64_t ticksPerUsec = 64;
  const uint64_t ticksPerSec = 1000*1000*ticksPerUsec;
  const uint64_t nsecPerUsec = 1000;
  const uint64_t novaT0Sec = 1262304000;    // 01Jan2010 UTC in unix time
  uint64_t secSinceNovaT0 = novaTime/ticksPerSec;
  uint64_t ticksRem = novaTime - ticksPerSec*secSinceNovaT0;
  uint64_t sec = secSinceNovaT0 + novaT0Sec;
  uint64_t nsec = (ticksRem*nsecPerUsec)/ticksPerUsec;
  uint64_t tart = (sec << 32) + nsec;
  art::Timestamp ts(tart);
  return ts;
}

int64_t artTimeToNovaTime(art::Timestamp tart) {
  const uint64_t novaT0Sec = 1262304000;    // 01Jan2010 UTC in unix time
  uint64_t thi = tart.timeHigh();
  uint64_t tlo = tart.timeLow();
  uint64_t tnova = 1000*1000*64*(thi - novaT0Sec) + (tlo*64)/1000;
  return tnova;
}

art::Timestamp makets(uint32_t thi, uint32_t tlo) {
  uint64_t tthi = thi;
  uint64_t thilo = (tthi << 32) + tlo;
  return art::Timestamp(thilo);
}

//**********************************************************************

int test_Timestamp() {
  const string myname = "test_Timestamp: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";
  string scfg;

  cout << myname << line << endl;
  cout << myname << "Create test time" << endl;
  //uint32_t tsec = 2208988800;   // 2040
  uint32_t tsec = 1577836800;   // 2020
  //uint32_t tsec = 1483228800;   // 2017
  uint32_t trem = 123456789;

  cout << myname << line << endl;
  cout << myname << "Create timestamp." << endl;
  art::Timestamp ts1 = makets(tsec, trem);
  cout << myname << "Timestamp: " << setw(9) << ts1.timeHigh() << "."
       << setw(9) << ts1.timeLow() << " sec" << endl;
  assert( ts1.timeLow() == trem );
  assert( ts1.timeHigh() == tsec );

  cout << myname << line << endl;
  cout << myname << "Create nova time." << endl;
  uint64_t tnova = artTimeToNovaTime(ts1);
  art::Timestamp ts2 = novaTimeToArtTime(tnova);
  cout << myname << "Nova time: " <<tnova << endl;
  cout << myname << "Timestamp: " << setw(9) << ts2.timeHigh() << "."
       << setw(9) << ts2.timeLow() << " sec" << endl;
  assert( ts2.timeHigh() == tsec );
  int64_t lodiff = ts2.timeLow();
  lodiff -= trem;
  int64_t tol = 1000/64;
  cout << myname << "Low tolerance: " << tol << endl;
  assert( abs(lodiff) < tol );

  cout << "Done." << endl;
  return 0;
}

//**********************************************************************

int main() {
  return test_Timestamp();
}

//**********************************************************************
