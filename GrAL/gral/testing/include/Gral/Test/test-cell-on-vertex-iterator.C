#ifndef NMWR_GB_GRAL_TEST_CELL_ON_VERTEX_ITERATOR_C
#define NMWR_GB_GRAL_TEST_CELL_ON_VERTEX_ITERATOR_C

// $LICENSE

#include "Gral/Test/test-cell-on-vertex-iterator.h"
#include "Utility/pre-post-conditions.h"

template<class G>
bool test_cell_on_vertex_iterator(G const& g, std::ostream & out)
{
  typedef grid_types<G> gt;
  typedef typename gt::VertexIterator         VertexIterator;
  typedef typename gt::CellOnVertexIterator   CellOnVertexIterator;

  for(VertexIterator f(g); ! f.IsDone(); ++f) {
    int v_cnt = 0;
    for(CellOnVertexIterator vf(*f); ! vf.IsDone(); ++vf, ++v_cnt) {
      ;
    }
    REQUIRE_ALWAYS(v_cnt == (int)(*f).NumOfCells(), 
                   "v_cnt = " << v_cnt << " != f.NumOfCells() = " 
                   << (*f).NumOfCells() << '\n',1);

    CellOnVertexIterator v;
    v = (*f).FirstCell();
    CellOnVertexIterator w = v;
    for( ; !v.IsDone(); ++v, ++w) {
      //REQUIRE_ALWAYS( &(v.TheGrid()) == &(f.TheGrid()), "",1);
      REQUIRE_ALWAYS( ( v ==  w), "Iterators differ!\n",1);
      REQUIRE_ALWAYS( (*v == *w), "Iterator values differ!\n",1);
    }
    REQUIRE_ALWAYS( (w.IsDone()), "", 1);
    REQUIRE_ALWAYS( (v == w), "Past-the-end iterators differ!\n", 1);
  
    if((*f).NumOfCells() > 0) {
      v = (*f).FirstCell();
      w = v;
      ++v;
      for( ; !v.IsDone(); ++v, ++w) 
        REQUIRE_ALWAYS( (*v != *w), "Iterators point to same vertex!\n",1);
    }
  }
  return true;
}

#endif