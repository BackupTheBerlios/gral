#ifndef GRAL_BG_GRIDS_CARTESIAN3D_MAPPED_GEOMETRY_H
#define GRAL_BG_GRIDS_CARTESIAN3D_MAPPED_GEOMETRY_H

// $LICENSE

#include "Gral/Grids/Cartesian3D/cartesian3d.h"

namespace cartesian3d {

  /*! A mapped geometry for CartesianGrid3D

     \templateparams
     - \c CoordMap
        - type \c result_type (called \c coord_type below)
        - <tt> coord_type operator()(coord_type) </tt>
  */
template<class CoordMap>
class mapped_geometry {

public:
  typedef CoordMap mapping_type;
  typedef typename mapping_type::result_type coord_type;
  typedef CartesianGrid3D grid_type;
  typedef grid_types<grid_type> gt;
  typedef gt::Vertex            Vertex;

private:
  grid_type const* g;
  mapping_type f;
  double dx,dy,dz;

public:
  mapped_geometry() : g(0) {}
  mapped_geometry(grid_type    const& gg,
		  mapping_type const& ff)
    : g(&gg), f(ff)
    {
      init();
    }
  void init(grid_type    const& gg,
	    mapping_type const& ff)
    {
      g = &gg; 
      f = ff;
      init();
    }

  double x(Vertex const& v) const { return dx * v.index()[0];}
  double y(Vertex const& v) const { return dy * v.index()[1];}
  double z(Vertex const& v) const { return dz * v.index()[2];}
  
  //  coord_type coord(Vertex const& v) const { return f(x(v),y(v),z(v));}
  coord_type coord(Vertex const& v) const { return f(coord_type(x(v),y(v),z(v)));}

  grid_type    const& TheGrid() const { return *g;}
  mapping_type const& TheMap()  const { return f;}

private:
  void init()
    {
      dx = 1.0 / g->NumOfXCells();
      dy = 1.0 / g->NumOfYCells();
      dz = 1.0 / g->NumOfZCells();
    } 
};

}; // namespace cartesian3d

#endif
