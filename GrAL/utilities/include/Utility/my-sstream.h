#ifndef GRAL_GB_UTILITY_MY_SSTREAM_H
#define GRAL_GB_UTILITY_MY_SSTREAM_H

// $LICENSE_NEC_2004

#include <string>

#ifdef GRAL_HAS_SSTREAM
#include <sstream>
#else
#include <strstream.h>

namespace std {

  // simple minded wrappers faking stringstreams

  class istringstream {
    istrstream base;
  public:
    //    istringstream() {}
    istringstream(string const& s) : base(s.c_str()) {}
    
    istrstream & get_stream() { return base;}
    operator istrstream & () { return base;}
    istrstream * operator&() { return &base;}
  };

  class ostringstream {
    ostrstream base;
  public:
    ostringstream() {}
    // ostringstream(string const& s) : base(s.c_str(), s.size()) {}
    
    ostrstream & get_stream() { return base;}
    operator ostrstream & () { return base;}
    ostrstream * operator&() { return &base;}
  };

  class stringstream {
    strstream base;
  public:
    stringstream() {}
    // stringstream(string const& s) : base(s.c_str(), s.size()) {}
    
    strstream & get_stream() { return base;}
    operator strstream & ()  { return base;}
    strstream * operator&()  { return &base;}
  };
}

#endif



#endif
