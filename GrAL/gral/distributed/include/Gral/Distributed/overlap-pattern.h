#ifndef NMWR_GB_OVERLAP_PATTERN_H
#define NMWR_GB_OVERLAP_PATTERN_H

//----------------------------------------------------------------
//   (c) Guntram Berti, 1998
//   Chair for Numerical Mathematics & Scientific Computing (NMWR)
//   TU Cottbus - Germany
//   http://math-s.math.tu-cottbus.de/NMWR
//   
//----------------------------------------------------------------

#include <string>
#include <queue> // STL

#include "Gral/Base/type-tags.h"

//----------------------------------------------------------------
//
/*! \brief class for storing an overlap (incidence) pattern
  
   The pattern may be, for example,  the local stencil of a 
   numeric function.
*/
//----------------------------------------------------------------

class overlap_pattern {
private:
 queue<grid_element_tag,deque<grid_element_tag> > q;
public:
  overlap_pattern();
  overlap_pattern(string const& pat);

  void push(grid_element_tag t)  { q.push(t);}
  void pop()                     { q.pop();}
  grid_element_tag front() const { return q.front();}

  bool empty() const { return q.empty();}
};

#endif

