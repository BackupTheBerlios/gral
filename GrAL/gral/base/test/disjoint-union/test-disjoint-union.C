#include "Gral/Views/disjoint-union-view.h"

#include "Gral/Grids/Complex2D/all.h"
#include "Gral/Grids/Cartesian2D/all.h"

#include "Gral/IO/complex2d-format-output.h"

#include "Gral/Test/all.h"


#include <functional> // identity



int main() {
 
  // create Cartesian grid & geometry
  CartesianGrid2D R(3,3);
  typedef coordN<2> coord_type;
  typedef std::identity<coord_type>  mapping_type;
  typedef mapped_geometry_reg2d<mapping_type> reg_geom_type;
  mapping_type id; 
  reg_geom_type GeomR(id, R);


  // create unstructured grid & geometry
  Complex2D G;
  typedef stored_geometry_complex2D  us_geom_type;
  us_geom_type GeomG(G);
  ConstructGrid(G,GeomG, R, GeomR);

  // create disjoint union view of above grids and geometries
  typedef   disjoint_union_view::grid_view<Complex2D, CartesianGrid2D> union_type;
  union_type U(G,R);
  typedef disjoint_union_view::geom_view<us_geom_type, reg_geom_type> union_geom_type;
  union_geom_type GeomU(U,GeomG, GeomR);

  // test functionality of union view
  test_vertex_iterator        (U,cout);
  test_cell_iterator          (U,cout);
  test_vertex_on_cell_iterator(U,cout);

  typedef grid_types<union_type> ugt;
  typedef ugt::vertex_handle u_vertex_handle;


  // copy union into unstructured grid
  Complex2D UG;
  stored_geometry_complex2D GeomUG(UG);
  ConstructGrid(UG, GeomUG, U, GeomU);

  // output union to files
  {
    OstreamComplex2DFmt Out("union.complex2d.out");
    ConstructGrid(Out, UG, GeomUG);
  }
  {
    OstreamComplex2DFmt Out2("union2.complex2d.out");
    ConstructGrid(Out2, U, GeomU);
  }
}