#ifndef NMWR_GB_GRAL_DISTRIBUTED_COMPOSITE_INPUT_C
#define NMWR_GB_GRAL_DISTRIBUTED_COMPOSITE_INPUT_C

// $LICENSE

#include "Gral/Distributed/composite-grid-input.h"
#include "Utility/as-string.h"

template<class CoarseGIn, class CoarseG, class OGIn>
composite_grid_input<CoarseGIn,CoarseG,OGIn>
::composite_grid_input(std::string const& base)
  : basenm(base)
{
  CoarseGIn crs_in(coarse_file_nm(basenm));
  ConstructGrid0(the_coarse,crs_in);

  local_grids.set_grid(TheCoarseGrid());
  for(CoarseCellIterator C(TheCoarseGrid()); ! C.IsDone(); ++C) {
    local_grids[*C].init(TheCoarseGrid(), basenm + "." + as_string(number(*C)));
  }
  
}

#endif