#ifndef GRAL_GB_ITERATORS_CELL_ON_VERTEX_ITERATOR_C
#define GRAL_GB_ITERATORS_CELL_ON_VERTEX_ITERATOR_C

// $LICENSE_NEC

#include "Gral/Iterators/cell-on-vertex-iterator.h"

template<class G, class GT>
std::map<G const*, typename  cell_on_vertex_iterator<G,GT>::cov_table *>
cell_on_vertex_iterator<G,GT>::ctxt;



#endif