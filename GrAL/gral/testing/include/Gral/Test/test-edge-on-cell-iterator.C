#ifndef NMWR_GB_GRAL_TEST_EDGE_ON_CELL_ITERATOR_C
#define NMWR_GB_GRAL_TEST_EDGE_ON_CELL_ITERATOR_C

// $LICENSE

#include "Gral/Test/test-edge-on-cell-iterator.h"
#include "Utility/pre-post-conditions.h"

template<class G>
bool test_edge_on_cell_iterator(G const& g, std::ostream & out)
{
  typedef grid_types<G> gt;
  typedef typename gt::CellIterator         CellIterator;
  typedef typename gt::EdgeOnCellIterator EdgeOnCellIterator;

  for(CellIterator c(g); ! c.IsDone(); ++c) {
    int v_cnt = 0;
    for(EdgeOnCellIterator vc(*c); ! vc.IsDone(); ++vc, ++v_cnt) {
    ;
    }
    REQUIRE_ALWAYS(v_cnt == (int)(*c).NumOfEdges(), 
                   "v_cnt = " << v_cnt << " != c.NumOfEdges() = " 
                   << (*c).NumOfEdges() << '\n',1);

    EdgeOnCellIterator v;
    v = (*c).FirstEdge();
    EdgeOnCellIterator w = v;
    for( ; !v.IsDone(); ++v, ++w) {
      REQUIRE_ALWAYS( ( v ==  w), "Iterators differ!\n",1);
      REQUIRE_ALWAYS( (*v == *w), "Iterator values differ!\n",1);
    }
    REQUIRE_ALWAYS( (w.IsDone()), "", 1);
    REQUIRE_ALWAYS( (v == w), "Past-the-end iterators differ!\n", 1);
  
    if((*c).NumOfVertices() > 0) {
      v = (*c).FirstEdge();
      w = v;
      ++v;
      for( ; !v.IsDone(); ++v, ++w) 
        REQUIRE_ALWAYS( (*v != *w), "Iterators point to same edge!\n",1);
    }
  }
  return true;
}

#endif