
#include "Gral/IO/gmv-format-output3d.h"
#include "Gral/Grids/Cartesian3D/all.h"

#include "Geometry/coords.h"
#include <functional>

template<class COORD>
struct Id {
  COORD operator()(COORD const& p) const
    { return p;}
  COORD operator()(double x, double y, double z) const 
    { return COORD(x,y,z);}
  typedef COORD result_type;
};

int main() {
  typedef grid_types<CartesianGrid3D> gt;
  typedef Id<coordN<3> > mapping_type;

  {
    CartesianGrid3D R(2,2,2);
    mapped_geometry_cartesian3d<mapping_type> GeomR(R, mapping_type());
    OstreamGMV3DFmt Out("2x2x2.out");
    ConstructGrid(Out,R,GeomR);
  }

  {
    CartesianGrid3D R(5,3,2);
    mapped_geometry_cartesian3d<mapping_type> GeomR(R, mapping_type());
    OstreamGMV3DFmt Out("5x3x2.out");
    ConstructGrid(Out,R,GeomR);
  } 

  {
    CartesianGrid3D R(3,3,3);
    mapped_geometry_cartesian3d<mapping_type> GeomR(R, mapping_type());
    grid_function<gt::Cell,   int> gf1(R,1);
    grid_function<gt::Vertex, int> gf2(R,2);
    OstreamGMV3DFmt Out("3x3x3.out");
    namespace hl = heterogeneous_list;
    hl::BEGIN B;
    ConstructGrid(Out,R,GeomR,
		  (B, Out.pair("gf1",gf1), Out.pair("gf2",gf2)));
    // ConstructGrid(Out,R,GeomR, (heterogeneous_list::BEGIN, gf1, gf2));
  } 



}