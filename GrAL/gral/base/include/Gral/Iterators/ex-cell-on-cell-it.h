#ifndef NMWR_GB_EXT_CELL_ON_CELL_IT_H
#define NMWR_GB_EXT_CELL_ON_CELL_IT_H

//----------------------------------------------------------------
//   (c) Guntram Berti, 1998
//   Chair for Numerical Mathematics & Scientific Computing (NMWR)
//   TU Cottbus - Germany
//   http://math-s.math.tu-cottbus.de/NMWR
//   
//----------------------------------------------------------------

#include "Grids/grid-functions.h"

//----------------------------------------------------------------
//
// An iterator over all cells having at least one common vertex
// with a given cell.
//
//----------------------------------------------------------------

template<class Grid>
class ExtendedCellOnCellIterator {
  typedef Grid grid_type;
  typedef grid_types<Grid> gt;
  typedef typename gt::CellOnCellIterator   CellOnCellIterator;
  typedef typename gt::VertexOnCellIterator VertexOnCellIterator;
  typedef typename gt::CellOnVertexIterator CellOnVertexIterator;
  typedef typename gt::Cell                 Cell;

  typedef Cell   value_type;
private:
  Cell  anchor;
  CellOnCellIterator   nb; // either nb is active, or v and vnb are active.
  VertexOnCellIterator v;
  CellOnVertexIterator vnb;
  partial_grid_function<Cell,bool> visited;

  typedef ExtendedCellOnCellIterator<Grid> self;
public:
  ExtendedCellOnCellIterator(const Cell& c) 
    : anchor(c),
      nb(c.FirstNeighbour()),
      v(c.FirstVertex()),
      visited(c.TheGrid(), false)
    {
      vnb = (*v).FirstCell();
      visited[anchor] = true;
    }

  Cell operator*() const { return (! nb.IsDone() ? *nb : *vnb);}
  bool IsDone() const { return (nb.IsDone() && vnb.IsDone());}
  bool DirNbIsDone() const { return (nb.IsDone());}
  self& operator++() { 
    if(! nb.IsDone()) {
      visited[*nb] = true;
      ++nb;
      
      if( nb.IsDone())
	advance_indirect_neighbour();
    }
    
    else {
      visited[*vnb] = true;
      advance_indirect_neighbour();
    }
    return (*this);
  }


private:
  void advance_indirect_neighbour() 
    {
      while( !vnb.IsDone() && visited[*vnb])
	++vnb;
      if( vnb.IsDone() && ! v.IsDone()) {
	++v;
	if(! v.IsDone()) {
           vnb = (*v).FirstCell();
	   advance_indirect_neighbour();
	}
      }
    }
};


// only non-direct neighbours (not facet-to-facet)

template<class Grid>
class IndirectCellOnCellIterator {
private:
  ExtendedCellOnCellIterator<Grid> ext;
  typedef Grid grid_type;
  typedef grid_types<Grid> gt;
  typedef typename gt::Cell                 Cell;

  typedef Cell   value_type;
  typedef IndirectCellOnCellIterator<Grid> self;
public:
  IndirectCellOnCellIterator(const Cell& C) : ext(C) 
    { while(!ext.DirNbIsDone()) ++ext; }
  self& operator++() { ++ext; return *this;}
  Cell operator*() const { return *ext;}
  bool IsDone()  const { return ext.IsDone();}
};

template<class Grid>
extern void test_extended_cell_on_cell_iterator(const Grid& g);

#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "Grids/Iterators/test-ex-cell-on-cell-it.C"
#endif


#endif
