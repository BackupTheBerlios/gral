/*! \file 

*/

/* ------------------------------------------------------------

    Copyright (C) 2007 - 2009 Guntram Berti

    This file is part of the Grid Algorithms Library (GrAL),
    available at http://gral.berlios.de

    GrAL is distributed under the MIT license,
    see the file LICENSE or http://gral.berlios.de/license

--------------------------------------------------------------- */


#include "Gral/IO/write-cgns.h"

#include "Gral/Grids/Triang2D/all.h"
#include "Gral/Geometries/simple-geometry.h"
#include "Container/tuple-point-traits.h"
#include "Container/bijective-mapping.h"

#include <string>

int main() {
  using namespace std;

  typedef GrAL::Triang2D                               grid_type;
  typedef GrAL::tuple<double,3>                        coord_type;
  typedef GrAL::simple_geometry<grid_type, coord_type> geom_type;

  typedef GrAL::grid_types<grid_type> gt;
  gt::size_type cells[] = { 0, 1, 2, 2, 1, 3};
  typedef coord_type ct;
  ct coords[] = { ct(0,0,0), ct(1,0,0), ct(0,1,0), ct(1,1,0) };
  gt::size_type nc = sizeof(cells)/(3*sizeof(gt::size_type));  
  gt::size_type nv = sizeof(coords)/sizeof(ct);  

  grid_type T    (cells, nc, nv);
  geom_type GeomT(T, coords+0, coords+nv);
  GrAL::grid_function<gt::Cell, int> regions(T);
  gt::CellIterator c(T);
  regions[gt::Cell(T,0)] = 0;
  regions[gt::Cell(T,1)] = 1;

  {
    string output = "2tri.cgns";
    GrAL::write_triangular_grid_to_cgns(output, T, GeomT, regions, 2);
  }
  {
    string output = "2tri-names.cgns";
    GrAL::bijective_mapping<string, string, GrAL::identity_if_undefined> names;
    names["Base"] = "GrAL test mesh";
    names["Region0"] = "Domain0";
    names["Region1"] = "Domain1";
    GrAL::write_triangular_grid_to_cgns(output, T, GeomT, regions, 2, names);
  }
}
