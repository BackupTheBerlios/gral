#ifndef NMWR_GB_GRAL_TEST_FACET_ON_CELL_ITERATOR_C
#define NMWR_GB_GRAL_TEST_FACET_ON_CELL_ITERATOR_C

// $LICENSE

#include "Gral/Test/test-facet-on-cell-iterator.h"
#include "Utility/pre-post-conditions.h"

template<class G>
bool test_facet_on_cell_iterator(G const& g, std::ostream & out)
{
  typedef grid_types<G> gt;
  typedef typename gt::CellIterator        CellIterator;
  typedef typename gt::FacetOnCellIterator FacetOnCellIterator;

  for(CellIterator c(g); ! c.IsDone(); ++c) {
    int v_cnt = 0;
    for(FacetOnCellIterator vc(*c); ! vc.IsDone(); ++vc, ++v_cnt) {
    ;
    }
    REQUIRE_ALWAYS(v_cnt == (int)(*c).NumOfFacets(), 
                   "v_cnt = " << v_cnt << " != c.NumOfFacets() = " 
                   << (*c).NumOfFacets() << '\n',1);

    FacetOnCellIterator v;
    v = (*c).FirstFacet();
    FacetOnCellIterator w = v;
    for( ; !v.IsDone(); ++v, ++w) {
      REQUIRE_ALWAYS( ( v ==  w), "Iterators differ!\n",1);
      REQUIRE_ALWAYS( (*v == *w), "Iterator values differ!\n",1);
    }
    REQUIRE_ALWAYS( (w.IsDone()), "", 1);
    REQUIRE_ALWAYS( (v == w), "Past-the-end iterators differ!\n", 1);
  
    if((*c).NumOfFacets() > 0) {
      v = (*c).FirstFacet();
      w = v;
      ++v;
      for( ; !v.IsDone(); ++v, ++w) 
        REQUIRE_ALWAYS( (*v != *w), "Iterators point to same facet!\n",1);
    }
  }
  return true;
}

#endif