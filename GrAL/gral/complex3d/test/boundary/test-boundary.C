/*! \file
    \author Guntram Berti <berti@ccrl-nece.de>
    $Id: test-boundary.C,v 1.1 2003/08/01 18:51:34 berti Exp $
*/

#include "Gral/Grids/Complex3D/boundary.h"

#include "Gral/Grids/Complex3D/all.h"
#include "Gral/Grids/Cartesian3D/all.h"

#include <iostream>

int main() {
  using namespace std;  

  using cartesian3d::CartesianGrid3D;
  typedef grid_types<Complex3D> gt;

  {
    CartesianGrid3D R(2,2,2);
    Complex3D       G;
    ConstructGrid0(G,R);
    BoundaryRange<Complex3D> Bd(G);
    typedef grid_types<BoundaryRange<Complex3D> > bgt;
    cout << "Boundary 2x2x2: " << Bd.NumOfFacets() << " Facets " << endl;
    for(bgt::FacetIterator bf(Bd); ! bf.IsDone(); ++bf) {
      cout << "Facet " << bf.handle() << ": ";
      for(bgt::VertexOnFacetIterator vbf(*bf); ! vbf.IsDone(); ++vbf)
	cout << vbf.handle() << " ";
      cout << endl;
    }    
  }
  {
    CartesianGrid3D R(3,3,3);
    Complex3D       G;
    ConstructGrid0(G,R);
    BoundaryRange<Complex3D> Bd(G);
    cout << "Boundary 3x3x3: " << Bd.NumOfFacets() << " Facets " << endl;
  }

}