#include "Gral/Hierarchical/hierarchical-grid.h"
#include "Gral/Hierarchical/hierarchical-grid-function-base.h"
#include "Gral/Hierarchical/hierarchical-grid-function.h"
#include "Gral/Hierarchical/hierarchical-partial-grid-function.h"
#include "Gral/Grids/Cartesian3D/all.h"
#include "Gral/Grids/Cartesian2D/all.h"


#include <iostream>

template<class GRID>
void test_hier_gf(GRID const& root, GRID const& pattern, std::ostream& out) 
{
  typedef GRID flat_grid_type;
  typedef grid_types<flat_grid_type> cgt;
  typedef hierarchical::hgrid_cartesian<flat_grid_type> hier_grid_type;
  typedef hier_grid_type                                hgt;
  typedef typename hgt::level_handle                    level_handle;
  typedef typename hgt::HierCell                        HierCell; 

  hier_grid_type H(root,pattern);
  hierarchical::hier_grid_function        <HierCell, int> Hgf (H, 0);
  hierarchical::hier_partial_grid_function<HierCell, int> Hpgf(H, 0);

  
  H   .add_finer_level();
  Hgf .add_finer_level(1);
  Hpgf.add_finer_level(1);

  H   .add_coarser_level();
  Hgf .add_coarser_level(-1);
  Hpgf.add_coarser_level(-1);

  hierarchical::hier_grid_function        <HierCell, int> Hgf2 (Hgf);
  hierarchical::hier_partial_grid_function<HierCell, int> Hpgf2(Hpgf);

  for(level_handle lev = H.coarsest_level(); lev <= H.finest_level(); ++lev) {
    out << "Level " << lev << ":\n";
    for(typename cgt::CellIterator c(H.FlatGrid(lev)); !c.IsDone(); ++c) {
      out << (*c).index() << ": " << Hgf(lev)(*c) << " = ";
      HierCell hc(H,*c,lev);
      out << Hgf(hc) << " = "
	  << Hpgf(hc) << " = "
	  << Hgf2(hc) << " = "
	  << Hpgf2(hc) 
	  << "\n";
    }
  }
}


// explicit instantiation to make sure all members are compilable
namespace hierarchical { 
  template class hgrid_cartesian<cartesian3d::CartesianGrid3D>; 
  typedef hgrid_cartesian<cartesian3d::CartesianGrid3D>::HierCell HierCell;
  template class hier_grid_function<HierCell, int>;

  template class hier_grid_function_base<HierCell, int, grid_function>;
  template class hier_grid_function_base<HierCell, int, partial_grid_function>;
}


int main() {
  using namespace std;
  cout << "\n------------- 2D --------------\n";
  {
    namespace cart = cartesian2d;
    typedef cart::CartesianGrid2D               cart_grid_type;
    cart_grid_type root(3,3);
    cart_grid_type ref_pattern(3,2); // 2x1 cells!
    test_hier_gf(root,ref_pattern, cout);
  }
  cout << "\n------------- 3D --------------\n";
  {
    namespace cart = cartesian3d;
    typedef cart::CartesianGrid3D               cart_grid_type;
    cart_grid_type root(3,3,3);
    cart_grid_type ref_pattern(3,2,2); // 2x1x1 cells!
    test_hier_gf(root,ref_pattern, cout);
  }
}