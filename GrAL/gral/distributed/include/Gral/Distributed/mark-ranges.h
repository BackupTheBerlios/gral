#ifndef NMWR_GB_COMPOSITE_MARK_LAYERS_H
#define NMWR_GB_COMPOSITE_MARK_LAYERS_H

//----------------------------------------------------------------
//   (c) Guntram Berti, 1998
//   Chair for Numerical Mathematics & Scientific Computing (NMWR)
//   TU Cottbus - Germany
//   http://math-s.math.tu-cottbus.de/NMWR
//   
//----------------------------------------------------------------


//----------------------------------------------------------------
/*! \brief Mark cells on partition boundary according to pattern.
   \ingroup overlapds

 The facets in \c boundary_f contain the complete boundary of
 the partition with respect to other partitions (i.e. they
 are not part of the underlying grids boundary).

 The Predicate \c inside controls if cells are to be collected
 inside (exposed) or outside (copied)  the partition.

 \preconditions:
 [inside(f.C1()) \f$ \iff \f$  ! inside(f.C2()))]  \f$ \forall f \in \f$ boundary_f

 \postconditions:
 \forall C \in c_layers : inside(C) = true.

 \b Algorithm:

 This routine essentially just branches to mark_on_vertices or
 mark_on_cells, according to pattern, after generating the
 proper starting sets ("seeds").

 \todo Why boundary_f passed by value?
*/
//----------------------------------------------------------------

template<class FacetRange, 
         class CellRange, 
         class OvlpPattern, class Pred>
void mark_layers(FacetRange           boundary_f,      
		 CellRange         &  c_layer,
		 OvlpPattern const &  ovlppattern,
		 Pred                 inside);

//----------------------------------------------------------------
/*! \brief collect the private elements
    \ingroup overlapds

   \b Semantics:

   priv = range(eit) \f$ \setminus \f$ ( exposed \f$\cup\f$ shared \f$\cup\f$ copied )
*/
//----------------------------------------------------------------

template<class ERange, class Eiter>
void mark_private_range(ERange& priv, 
			Eiter eit,
			const ERange& exposed, 
			const ERange& shared, 
			const ERange& copied);

#ifdef  NMWR_INCLUDE_TEMPLATE_DEFS
#include "Gral/Distributed/internal/mark-ranges.C"
#endif

#endif
