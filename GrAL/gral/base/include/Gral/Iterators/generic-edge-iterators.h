#ifndef GRAL_BASE_GB_GENERIC_EDGE_ITERATORS_H
#define GRAL_BASE_GB_GENERIC_EDGE_ITERATORS_H


/* ------------------------------------------------------------

    Copyright (C) 1997 - 2009 Guntram Berti

    This file is part of the Grid Algorithms Library (GrAL),
    available at http://gral.berlios.de

    GrAL is distributed under the MIT license,
    see the file LICENSE or http://gral.berlios.de/license

--------------------------------------------------------------- */


#include "Gral/Base/common-grid-basics.h"
#include "Container/my-hash-map.h"
#include <iostream>

namespace GrAL {

/*! \defgroup generic_edge Generic edge components

  \ingroup elements
  \ingroup iterators
  \see \ref elements module
  \see \ref iterators module
  \see \ref generic_facet

  \brief
   The components offer generic support for $GrAL Edge, 
   $GrAL EdgeIterator,
   and $GrAL EdgeOnCellIterator, 
   on top of a $GrAL Cell-VertexInputGridRange. 

   They are used for implementing %edge-related members of Complex3D.
   
   \todo Test
 */

/*! \brief enclosing namespace for generic edge components
 
   The classes defined in this namespace are to be used
   as mixins, cf. the implementation of Complex3D
   in complex3d.h.

    \ingroup generic_edge
    \see   generic_facet
 */
namespace generic_edge {

  template<class gt> class edge;
  
  template<class gt> class edge_iterator;
  
  template<class gt> class edge_on_cell_iterator;

  template<class gt> class edge_handle_t;

  template<class gt> class hasher_edge;

  template<class gt> class cell_mixin;

  template<class gt> class grid_mixin;

  template<class gt>
  struct grid_types_edge : public virtual  gt
    {
      // these typedefs should be superflous!
      typedef typename gt::grid_type     grid_type;
      typedef typename gt::size_type     size_type;

      typedef typename gt::Cell          Cell;
      typedef typename gt::Vertex        Vertex;
      typedef typename gt::cell_handle   cell_handle;
      typedef typename gt::vertex_handle vertex_handle;
      typedef typename gt::CellIterator  CellIterator;
      
      typedef typename get_archgt<gt, grid_types<typename gt::archetype_type> >::type agt;
      typedef typename agt::Edge         archEdge;        
      typedef typename agt::EdgeIterator archEdgeIterator;
      typedef typename agt::edge_handle  arch_edge_handle;
      
      typedef edge<gt>                   Edge;
      typedef edge_iterator<gt>          EdgeIterator;
      typedef edge_on_cell_iterator<gt>  EdgeOnCellIterator;
      typedef edge_handle_t<gt>          edge_handle; 
      typedef hasher_edge<gt>            edge_hasher_type;

      typedef cell_mixin<gt>  cell_base_type;
      typedef grid_mixin<gt>  grid_base_type;
    };


  // NOTE: handle is not unique, different handles may
  // point to the same edge.
    template<class gt>
      class edge_handle_t : public grid_types_edge<gt> {
	typedef edge_handle_t<gt> self;
	typedef grid_types_edge<gt> base;

      public:
	typedef grid_edge_handle_category    category;
	typedef typename base::cell_handle 	cell_handle;
	typedef typename base::arch_edge_handle arch_edge_handle;

	cell_handle      c;
	arch_edge_handle eh;
	edge_handle_t() {}
	edge_handle_t(cell_handle cc, arch_edge_handle eeh)
	  : c(cc), eh(eeh) {}
       
        bool operator==(self const& rhs) const { return (c == rhs.c && eh == rhs.eh);}
        bool operator!=(self const& rhs) const { return !((*this) == rhs);}
      };
    template<class gt>
       ::std::ostream& operator<<( ::std::ostream& out, edge_handle_t<gt> const& h)
      { return (out << h.c << ' ' << h.eh);}


  /*! \brief A generic iterator over the edges of cell.
    \ingroup iterators
    
    This class uses the cell archetype's EdgeIterator.
    
  */

    template<class gt>
      class edge_on_cell_iterator 
	: public grid_types_edge<gt> {
	
	typedef edge_on_cell_iterator<gt> self;
	typedef grid_types_edge<gt>       base;
      public:
	typedef typename base::Vertex        Vertex;
	typedef typename base::vertex_handle vertex_handle;
	typedef typename base::Cell          Cell;
	typedef typename base::archEdge         archEdge;
	typedef typename base::archEdgeIterator archEdgeIterator;
	typedef typename base::arch_edge_handle arch_edge_handle;
	typedef typename base::Edge          Edge;
	typedef typename base::edge_handle   edge_handle;
	typedef typename base::grid_type     grid_type;

	typedef typename get_incidence_iterator_category<grid_edge_category,
							 typename category<Cell>::type>::type
	category;
	typedef Cell anchor_type;
	typedef Edge value_type;

      private:
	Cell              c;
	archEdgeIterator  e;
      public:
	edge_on_cell_iterator() {}
	explicit 
	edge_on_cell_iterator(Cell const& cc) 
	  : c(cc), e(c.TheArchetype().FirstEdge()) {}
	edge_on_cell_iterator(Cell const& cc, archEdgeIterator ee) 
	  : c(cc), e(ee) {}
	edge_on_cell_iterator(Cell const& cc, arch_edge_handle ee)
	  : c(cc), e(c.TheArchetype(), ee) {}
	edge_on_cell_iterator(grid_type const& g, edge_handle const& h)
	  : c(g,h.c), e(c.TheArchetype(),h.eh) {}
	
	self& operator++() {c_();  ++e; return *this;}
	bool  IsDone()  const {cb_();  return e.IsDone();}
	Edge  operator*() const { c_(); return Edge(*this); }
	
	arch_edge_handle local_handle() const { c_(); return e.handle();}
	archEdge  ArchetypeEdge() const { c_(); return *e;}

	vertex_handle v1() const { c_(); return c.v(e.v1());}
	vertex_handle v2() const { c_(); return c.v(e.v2());}
	Vertex V1()        const { c_(); return Vertex(TheGrid(),v1());}
	Vertex V2()        const { c_(); return Vertex(TheGrid(),v2());}

	edge_handle  handle() const 
	  { c_(); return edge_handle(c.handle(), local_handle()); }	
	
	grid_type const& TheGrid()   const { c_(); return c.TheGrid();}
	Cell      const& TheCell()   const { c_(); return c;}
	Cell      const& TheAnchor() const { c_(); return c;}
	
	
	bool operator==(self const& rhs) const 
	  { cb_(), rhs.cb_(); return e == rhs.e;}
	bool operator!=(self const& rhs) const 
	  { return !((*this) == rhs);} 

	bool bound() const { return (c.valid());}
	bool valid() const { return (bound() && e.valid());}
	void c_()  const { REQUIRE(valid(), "",1);}
	void cb_() const { REQUIRE(bound(), "",1);}
      };


    template<class gt>
    class edge : public grid_types_edge<gt> {
      typedef edge<gt> self;
      typedef grid_types_edge<gt>       base;
    public:
      typedef typename base::Vertex        Vertex;
      typedef typename base::vertex_handle vertex_handle;
      typedef typename base::Cell          Cell;
      typedef typename base::Edge          Edge;
      typedef typename base::edge_handle   edge_handle;
      typedef typename base::grid_type     grid_type;
      
      typedef edge_type_tag                element_type_tag;
      typedef grid_edge_category           category;
    private:
      edge_on_cell_iterator<gt> e;
    public:
      edge() {}
      edge(edge_on_cell_iterator<gt> const& ee) : e(ee) {}
      edge(grid_type const& g, edge_handle h) : e(g,h) {}
      
      vertex_handle v1() const { c_(); return e.v1();}
      vertex_handle v2() const { c_(); return e.v2();}
      
      Vertex V1()        const { c_(); return Vertex(TheGrid(),v1());}
      Vertex V2()        const { c_(); return Vertex(TheGrid(),v2());}

      edge_handle handle() const { c_(); return e.handle();}
      grid_type const& TheGrid() const { c_(); return e.TheGrid();}

      bool operator==(self const& rhs) const { 
	c_(); rhs.c_();
	return(   (v1() == rhs.v1() && v2() == rhs.v2())
		  ||
		  (v1() == rhs.v2() && v2() == rhs.v1()));
      }
      bool operator!=(self const& rhs) const 
	{ return !((*this) == rhs);}
      bool operator<(self const& rhs) const {
	vertex_handle v_max =  ::std::max(v1(), v2()), 
	              v_min =  ::std::min(v1(), v2());
	vertex_handle w_max =  ::std::max(rhs.v1(), rhs.v2()),
	              w_min =  ::std::min(rhs.v1(), rhs.v2());
	return ( (v_max < w_max) ||  (v_max == w_max && v_min < w_min));
      }

      bool bound() const { return e.bound();}
      bool valid() const { return e.valid();}
      void c_() const { REQUIRE(valid(), "" ,1); }

    };

   

    template<class gt>
      struct hasher_edge {
	typedef edge<gt> key_type;
	typedef edge<gt> argument_type;
	typedef size_t   result_type;
	
	size_t operator()(edge<gt> const& e) const 
	  { 
	    typename gt::vertex_handle vmax =  ::std::max(e.v1(),e.v2());
	    typename gt::vertex_handle vmin =  ::std::min(e.v1(),e.v2());
	    return 8*vmax + vmin;
	  }
      };



    /*! \brief Edge iterator based on marking visited edges.

     */
    template<class gt>
    class edge_iterator : public grid_types_edge<gt> {
      typedef edge_iterator<gt> self;
      typedef grid_types_edge<gt>       base;
    public:
      typedef typename base::Vertex        Vertex;
      typedef typename base::vertex_handle vertex_handle;
      typedef typename base::Cell          Cell;
      typedef typename base::CellIterator  CellIterator;
      typedef typename base::Edge          Edge;
      typedef typename base::edge_handle   edge_handle;
      typedef typename base::grid_type     grid_type;

      typedef grid_edge_iterator_category category;
      typedef Edge      value_type;
      typedef grid_type anchor_type;
   private:
      CellIterator                      c;
      edge_on_cell_iterator<gt>         e;
      // partial_grid_function<Edge,bool>  visited;
      STDHASH::hash_map<edge<gt>, bool, hasher_edge<gt> > visited;
    public:
      edge_iterator() {}
      explicit  edge_iterator(grid_type const& g) : c(g)  { init();}
      explicit  edge_iterator(CellIterator cc)    : c(cc) { init();}

      self& operator++() { c_(); advance_till_valid(); return (*this);}
      Edge  operator*() const { c_(); return Edge(e);}
      bool  IsDone()    const { cb_(); return c.IsDone();}
      grid_type   const& TheGrid()   const { cb_();  return c.TheGrid();}
      anchor_type const& TheAnchor() const { cb_();  return c.TheGrid();}
      edge_handle handle() const { c_(); return e.handle();}

      bool operator==(self const& rhs) const 
      { cb_(); rhs.cb_(); return (rhs.IsDone() && IsDone()) || (c == rhs.c && e == rhs.e);}
      bool operator!=(self const& rhs) const 
      { return !((*this) == rhs);}

      bool valid() const { return c.valid() && e.valid();}
      bool bound() const { return c.bound();}
      void c_()       const { REQUIRE(valid(), "",1); }    
      void cb_() const { REQUIRE(bound(), "",1); }    

    private:
      void init() {
	 if (! c.IsDone()) {
	    e = edge_on_cell_iterator<gt>(c);
	    visited[*e] = true;
	 }
      }
      void advance() {
	++e;
	if(e.IsDone()) {
	  ++c;
	  if(! c.IsDone()) {
	    e = edge_on_cell_iterator<gt>(c);
	  }
	}
      }
      void advance_till_valid() {
	do {
	  advance();
	} while (! IsDone() && ! is_new_edge(*e));
	if( ! IsDone()) visited[*e] = true;
	
      }
      bool is_new_edge(edge<gt> const& e) const  
	{ return visited.find(e) == visited.end();}
    };

    // cell type in gt must derive from this type
    template<class gt> 
      class cell_mixin : public gt::cell_base_type 
      {
	typedef grid_types_edge<gt> gte;
	typedef typename gt::cell_base_type base;

      public:
	typedef typename gte::edge_handle edge_handle;
	typedef typename gte::Edge        Edge;
	typedef typename gte::arch_edge_handle arch_edge_handle;
	typedef typename gte::archEdge         archEdge;
	typedef typename gte::Cell             Cell;

	void c_() const { base::c_();}
	// map local (archetype) edges to global (grid) edges
	edge_handle_t<gt> e(arch_edge_handle const& h) const {
	  // cast to subclass gt::Cell
	  c_(); return edge_handle(base::handle(),h);
	}	
	edge_handle_t<gt> e(archEdge const& ae) const { c_(); return e(ae.handle());}

	edge<gt> E(arch_edge_handle const& h) const 
	  { c_(); return Edge(base::TheGrid(),e(h));}
	 edge<gt> E(archEdge const& ae) const { c_(); return E(ae.handle());}

        unsigned NumOfEdges() const { c_(); return base::TheArchetype().NumOfEdges();}
        edge_on_cell_iterator<gt> FirstEdge() const 
	  { c_(); return edge_on_cell_iterator<gt>(static_cast<Cell const&>(*this));}
        edge_on_cell_iterator<gt> EndEdge() const 
	  { c_(); return edge_on_cell_iterator<gt>(static_cast<Cell const&>(*this),
						   base::TheArchetype().EndEdge());}

      };


  template<class gt>
  class grid_mixin : public gt::grid_base_type {
  private:
    typedef grid_types_edge<gt> gte;
  public:
    typedef typename gte::grid_type   grid_type;
    typedef typename gte::size_type   size_type;
  private:
    mutable size_type   num_of_edges;
    mutable bool        num_of_edges_valid;

    void calc_num_of_edges() const {
      typename gte::EdgeIterator f(static_cast<grid_type const&>(*this)); 
      for(num_of_edges = 0; !f.IsDone(); ++f)
	++num_of_edges;
    }
  public:
    grid_mixin() : num_of_edges(0), num_of_edges_valid(false) {}

    size_type NumOfEdges() const {
      if(!num_of_edges_valid) {
	calc_num_of_edges();
	num_of_edges_valid = true;
      }
      return num_of_edges;
    }
  };

} // namespace

} // namespace GrAL 

#endif
