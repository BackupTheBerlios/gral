#ifndef GRAL_GB_ALGORITHM_CONSTRUCT_ISOMORPHISM_H
#define GRAL_GB_ALGORITHM_CONSTRUCT_ISOMORPHISM_H

// $LICENSE_NEC

#include "Gral/Base/common-grid-basics.h"

/*! \brief Construct an isomorphism between two grids.
    \ingroup gridmorphisms
    \ingroup combinatoric_grid_algorithms

    Return value is true on successful construction,
    else false.

    \bug It does not really try all possible isomorphisms.
    If an isomorphism of 2 cells does not extend to an isomorphism
    of the whole grid, it does not try other isomorphisms of the same
    pair of cell. Thus, it cannot construct an isomorphism of a
    Cartesian 2x1 grid to a 1x2 grid.
*/
template<class GRID1, class GRID2, 
         class GT1,   class GT2,
         class PHI>
bool construct_isomorphism(GRID1 const& G1,
			   GRID2 const& G2,
			   GT1   gt1,                // only type used
			   GT2   gt2,                //    
			   PHI        & phi);   // OUT

/*! Convenience wrapper for general construct_isomorphism 
  \ingroup gridmorphisms
 */
template<class GRID1, class GRID2, 
         class PHI>
inline
bool construct_isomorphism(GRID1 const& G1,
			   GRID2 const& G2,
			   PHI        & phi)   // OUT
{ 
  return construct_isomorphism(G1,G2,
			       grid_types<GRID1>(), 
			       grid_types<GRID2>(),
			       phi);
}

/*! Extend a given isomorphism to the whole grid.
    \ingroup isomorphism

    Return value is true on successful extension to the whole
    grid (more precisely, to the component containing c1).
    It is false if this failed. In this case, phi contains
    the partial morphism constructed so far.
 */

template<class CELL1, class CELL2, class GRID1, class GRID2, class PHI>
bool extend_isomorphism(CELL1 const& c1,
			CELL2 const& c2,
			GRID1 const& G1,
			GRID2 const& G2,
			PHI        & phi);


#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "Gral/Algorithms/internal/construct-isomorphism.C"
#endif

#endif
