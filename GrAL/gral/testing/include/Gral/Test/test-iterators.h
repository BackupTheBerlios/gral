#ifndef NMWR_GB_GRAL_TEST_ITERATORS_H
#define NMWR_GB_GRAL_TEST_ITERATORS_H

// $LICENSE

/*! \file  convenience header

 */

// sequence iterators
#include "Gral/Test/test-vertex-iterator.h"
#include "Gral/Test/test-edge-iterator.h"
#include "Gral/Test/test-face-iterator.h"
#include "Gral/Test/test-facet-iterator.h"
#include "Gral/Test/test-cell-iterator.h"

// incidence iterators

// on cells
#include "Gral/Test/test-vertex-on-cell-iterator.h"
#include "Gral/Test/test-edge-on-cell-iterator.C"
#include "Gral/Test/test-facet-on-cell-iterator.h"
#include "Gral/Test/test-cell-on-cell-iterator.h"

// on facets
#include "Gral/Test/test-vertex-on-facet-iterator.h"
#include "Gral/Test/test-edge-on-facet-iterator.h"

// on faces
#include "Gral/Test/test-vertex-on-face-iterator.h"
#include "Gral/Test/test-edge-on-face-iterator.h"

// on edges
#include "Gral/Test/test-vertex-on-edge-iterator.h"

// on vertices
#include "Gral/Test/test-vertex-on-vertex-iterator.h"
#include "Gral/Test/test-cell-on-vertex-iterator.h"


#endif
