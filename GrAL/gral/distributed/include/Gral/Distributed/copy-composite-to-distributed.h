#ifndef NMWR_GB_GRAL_DISTRIBUTED_COPY_COMPOSITE_TO_DISTRIBUTED_H
#define NMWR_GB_GRAL_DISTRIBUTED_COPY_COMPOSITE_TO_DISTRIBUTED_H


// $LICENSE


/*! \brief Construct a distributed grid from a composite one.
    \ingroup compositeio
    \ingroup distributedgrids

    This function allows  to construct a distributed grid from a
    composite grid, which may be for example an input adapter like
    composite_grid_input.
*/
template
< class DG,          // distributed grid
  class CG_SRC,      // composite grid (src)
  class CCORR_CRS,   //  grid morphism CG_SRC::coarse_grid -> CG::coarse_grid
  class VCORR,       //  vertex grid morphism CG_SRC::fine_grid -> DG::the_grid
  class CCORR        //  cell   grid morphism CG_SRC::fine_grid -> DG::the_grid
>
void CopyComposite2Distributed
(
 DG               & dg_dest,    // OUT
 CG_SRC      const& cg_src,     // IN
 CCORR_CRS        & src2dest_coarse_c, // OUT: C(Coarse_src) -> C(Coarse)
 VCORR            & src2dest_fine_v,   // OUT: C(Coarse_src) -> (V(FG_src) -> V(FG))
 CCORR            & src2dest_fine_c    // OUT: C(Coarse_src) -> (C(FG_src) -> C(FG))
 );

#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "Gral/Distributed/internal/copy-composite-to-distributed.C"
#endif

#endif
