#ifndef NMWR_GB_ADD_TOTAL_SHARED_H
#define NMWR_GB_ADD_TOTAL_SHARED_H

//----------------------------------------------------------------
//   (c) Guntram Berti, 1998
//   Chair for Numerical Mathematics & Scientific Computing (NMWR)
//   TU Cottbus - Germany
//   http://math-s.math.tu-cottbus.de/NMWR
//   
//----------------------------------------------------------------

//----------------------------------------------------------------
//
//  void AddTotalSharedRanges(...);
//
//  Collect shared vertices and facets of partition p 
//  of partitioning Prtng of Grid g.
//  This operates locally, i.e. must be called for each p.
//
//  OUTPUT:
//  -------
//    shared_v = shared_v \cup bv(p)
//    shared_f = shared_f \cup bf(p)
//    where
//      bv = {v \in V(p)| \exists q \neq p : v \in V(q)} 
//      bf = {f \in F(p)| \exists q \neq p : f \in F(q)}
//    are the vertices and facets, resp., that are shared
//    with some other partition q of Prtng.
// 
//----------------------------------------------------------------

template<class Grid, class Partition, class VertexRange, class FacetRange>
void AddTotalSharedRanges(VertexRange       & shared_v, // out
			  FacetRange        & shared_f, // out
			  Partition  const& Prtng,      // in
			  int               p,          // in
			  Grid       const& G);         // in


#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "Grids/Distributed/generic/add-total-shared.C"
#endif

#endif

