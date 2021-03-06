#ifndef NMWR_GB_COMPOSITE_GRID_H
#define NMWR_GB_COMPOSITE_GRID_H


/* ------------------------------------------------------------

    Copyright (C) 1997 - 2009 Guntram Berti

    This file is part of the Grid Algorithms Library (GrAL),
    available at http://gral.berlios.de

    GrAL is distributed under the MIT license,
    see the file LICENSE or http://gral.berlios.de/license

--------------------------------------------------------------- */




#include "Gral/Base/common-grid-basics.h"
#include "Gral/Distributed/overlapping-grid.h"

namespace GrAL {

/*! \defgroup compositegrids Composite Grids
    \ingroup distributedgrids
    
*/


/*! \brief A grid composed of separate pieces
    \ingroup compositegrids
    
    An object of type CompositeGrid represents a  (global) grid
    which is partitioned into several parts.
    These parts form the cells of a coarse (quotient) grid.
    To each of this parts is associated an 
    OverlappingGrid. The union of these overlapping grids
    (with proper identification of the overlap) is
    isomorphic to the underlying global grid.
    
   \see composite_grid_function,
   \partof compositegrids
 */
template<class CoarseG, class FineG>
class CompositeGrid {
  typedef CompositeGrid<CoarseG,FineG>     self;
public:
  typedef FineG                            fine_grid_type;
  typedef CoarseG                          coarse_grid_type;
  typedef OverlappingGrid<coarse_grid_type,
                          fine_grid_type>  ovrlp_grid_type;
 
  typedef grid_types<coarse_grid_type> cgt;
  typedef grid_types<  fine_grid_type> fgt;

  typedef typename   cgt::Cell                         CoarseCell;
  typedef typename   cgt::CellIterator                 CoarseCellIterator;
  typedef typename   ovrlp_grid_type::overlap_type     overlap_type;
  typedef typename   overlap_type::CellNbIterator      CellNbIterator;
  typedef typename   overlap_type::VertexNbIterator    VertexNbIterator;
  typedef typename   overlap_type::NbIterator          NeighbourIterator;

  //  typedef ExtendedCellOnCellIterator<coarse_grid_type> NeighbourIterator;
  typedef typename ovrlp_grid_type::range_type_ref   range_type;
private:
  coarse_grid_type                           the_coarse;
  grid_function<CoarseCell,ovrlp_grid_type>  local_grids;

  // FORBIDDEN (for the moment)
  CompositeGrid  (self const& rhs);
  self& operator=(self const& rhs);
public:

  //------------------- construction -------------------------------

  CompositeGrid() {}

  void coarse_grid_complete() { 
    local_grids.set_grid(TheCoarseGrid());
    for(CoarseCellIterator C(TheCoarseGrid()); ! C.IsDone(); ++C)
      local_grids[*C].init(TheCoarseGrid());
  }

  void calc_dependent_information() { /*  none */ }

  //-------------------- component access ----------------------------

  coarse_grid_type      & TheCoarseGrid()       { return the_coarse;}
  coarse_grid_type const& TheCoarseGrid() const { return the_coarse;}

  ovrlp_grid_type      &  OvrlpGrid(const CoarseCell& c)       { return local_grids[c];}
  ovrlp_grid_type const&  OvrlpGrid(const CoarseCell& c) const { return local_grids(c);}

  fine_grid_type       &  Grid(const CoarseCell& c)       { return local_grids[c].TheGrid();}
  fine_grid_type  const&  Grid(const CoarseCell& c) const { return local_grids[c].TheGrid();}

  overlap_type const& Overlap(const CoarseCell& c) const { return OvrlpGrid(c).TheOverlap();}
  overlap_type      & Overlap(const CoarseCell& c)       { return OvrlpGrid(c).TheOverlap();}

  CellNbIterator FirstCellNeighbour(const CoarseCell& c) const 
    { return Overlap(c).FirstCellNeighbour();}
  VertexNbIterator FirstVertexNeighbour(const CoarseCell& c) const 
    { return Overlap(c).FirstVertexNeighbour();}

  NeighbourIterator  FirstNeighbour(const CoarseCell& c) const
    //{ return NeighbourIterator(c);}
    {return Overlap(c).FirstNeighbour();}
  
  range_type    LocalRange(const CoarseCell& c)   { return local_grids[c].LocalRange();}


};


template<class CoarseG, class FineG>
void check_composite_grid(const CompositeGrid<CoarseG,FineG>& CG);

} // namespace GrAL 

#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "Gral/Distributed/internal/composite-grid.C"
#endif

#endif
