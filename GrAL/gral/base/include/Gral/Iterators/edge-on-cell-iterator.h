#ifndef GRAL_BASE_GB_EDGE_ON_CELL_ITERATOR_H
#define GRAL_BASE_GB_EDGE_ON_CELL_ITERATOR_H

// $LICENSE

#include "Gral/Base/common-grid-basics.h"
#include <hash_map>

/*! \defgroup generic_edge Generic edge components

    The components offer gneric support for edge, edge iteration
    and edge-on-celliteraration, on top of a $GrAL CellVertexInputGrid. 
 */

namespace generic_edge {

  template<class gt> class edge;
  
  template<class gt> class edge_iterator;
  
  template<class gt> class edge_on_cell_iterator;

  template<class gt> class edge_handle_t;

  template<class gt> class hasher_edge;

  //  template<class gt, class CELL> class cell_mixin;
  template<class gt> class cell_mixin;

  template<class gt>
  struct grid_types_edge : public virtual  gt
    {
      // these typedefs should be superflous!
      typedef typename gt::grid_type     grid_type;
      typedef typename gt::Cell          Cell;
      typedef typename gt::Vertex        Vertex;
      typedef typename gt::cell_handle   cell_handle;
      typedef typename gt::vertex_handle vertex_handle;
      typedef typename gt::CellIterator  CellIterator;
      

      typedef grid_types<typename gt::archetype_type> agt;
      typedef typename agt::Edge         archEdge;        
      typedef typename agt::EdgeIterator archEdgeIterator;
      typedef typename agt::edge_handle  arch_edge_handle;
      
      typedef edge<gt>                   Edge;
      typedef edge_iterator<gt>          EdgeIterator;
      typedef edge_on_cell_iterator<gt>  EdgeOnCellIterator;
      typedef edge_handle_t<gt>          edge_handle; 
      typedef hasher_edge<gt>            edge_hasher_type;

      // template<class CELL>
      // class edge_mixin_for_cell_type : public cell_mixin<gt,CELL> {};
      // typedef cell_mixin<gt>             edge_mixin_for_cell_type;
    
      //  typedef cell_mixin<gt, typename gt::cell_base_type> cell_base_type;
      typedef cell_mixin<gt>  cell_base_type;
    };


  // NOTE: handle is not unique, different handles may
  // point to the same edge.
    template<class gt>
      class edge_handle_t : public grid_types_edge<gt> {
	typedef edge_handle_t<gt> self;
      public:
	cell_handle      c;
	arch_edge_handle eh;
	edge_handle_t() {}
	edge_handle_t(cell_handle cc, arch_edge_handle eeh)
	  : c(cc), eh(eeh) {}
       
        bool operator==(self const& rhs) const { return (c == rhs.c && eh == rhs.eh);}
      };


  /*! \brief A generic iterator over the edges of cell.
    \ingroup iterators
    
    This class uses the cell archetype's EdgeIterator.
    
  */

    template<class gt>
      class edge_on_cell_iterator 
	: public grid_types_edge<gt> {
	
	typedef edge_on_cell_iterator<gt> self;
      private:
	Cell              c;
	archEdgeIterator  e;
      public:
	edge_on_cell_iterator() {}
	edge_on_cell_iterator(Cell const& cc) 
	  : c(cc), e(c.TheArchetype().FirstEdge()) {}
	edge_on_cell_iterator(Cell const& cc, archEdgeIterator ee) 
	  : c(cc), e(ee) {}
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

	bool bound() const { return (c.valid());}
	bool valid() const { return (bound() && e.valid());}
	void c_()  const { REQUIRE(valid(), "",1);}
	void cb_() const { REQUIRE(bound(), "",1);}
      };


    template<class gt>
    class edge : public grid_types_edge<gt> {
      typedef edge<gt> self;
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

      bool bound() const { return e.bound();}
      bool valid() const { return e.valid();}
      void c_() const { REQUIRE(valid(), "" ,1); }

    };

   

    template<class gt>
      struct hasher_edge {
	size_t operator()(edge<gt> const& e) const 
	  { 
	    typename gt::vertex_handle vmax = std::max(e.v1(),e.v2());
	    typename gt::vertex_handle vmin = std::min(e.v1(),e.v2());
	    return 8*vmax + vmin;
	  }
      };



    /*! Edge iterator based on marking visited edges.

     */
    template<class gt>
    class edge_iterator : public grid_types_edge<gt> {
      typedef edge_iterator<gt> self;
    private:
      CellIterator                      c;
      edge_on_cell_iterator<gt>         e;
      // partial_grid_function<Edge,bool>  visited;
      std::hash_map<edge<gt>, bool, hasher_edge<gt>, equal_to<edge<gt> > > visited;
    public:
      edge_iterator() {}
      edge_iterator(grid_type const& g) : c(g), e(c)
	{
	  if (! IsDone()) visited[*e] = true;
	}
      
      self& operator++() { c_(); advance_till_valid(); return (*this);}
      Edge  operator*() const { c_(); return Edge(e);}
      bool  IsDone()    const { cb_(); return c.IsDone();}
      grid_type const& TheGrid() const { c_(); return e.TheGrid();}
      edge_handle handle() const { c_(); return e.handle();}

      bool operator==(self const& rhs) const 
	{ cb_(); rhs.cb_(); return (c == rhs.c && e == rhs.e);}

      bool valid() const { return c.valid() && e.valid();}
      bool bound() const { return c.bound() && e.bound();}
      void c_()       const { REQUIRE(valid(), "",1); }    
      void cb_() const { REQUIRE(bound(), "",1); }    

    private:
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
    template<class gt> //, class CELL>
      class cell_mixin : public /*typename*/ gt::cell_base_type // , public CELL
      {
	typedef grid_types_edge<gt> gte;
      public:
	typedef typename gte::edge_handle edge_handle;
	typedef typename gte::Edge        Edge;
	typedef typename gte::arch_edge_handle arch_edge_handle;
	typedef typename gte::archEdge         archEdge;
	typedef typename gte::Cell             Cell;

	// map local (archetype) edges to global (grid) edges
	edge_handle_t<gt> e(arch_edge_handle const& h) const {
	  // cast to subclass gt::Cell
	  c_(); return edge_handle(handle(),h);
	}	
	edge_handle_t<gt> e(archEdge const& ae) const { c_(); return e(ae.handle());}

	edge<gt> E(arch_edge_handle const& h) const 
	  { c_(); return Edge(TheGrid(),e(h));}
	 edge<gt> E(archEdge const& ae) const { c_(); return E(ae.handle());}

        unsigned NumOfEdges() const { c_(); return TheArchetype().NumOfEdges();}
        edge_on_cell_iterator<gt> FirstEdge() const 
	  { c_(); return edge_on_cell_iterator<gt>(static_cast<Cell const&>(*this));}
        edge_on_cell_iterator<gt> EndEdge() const 
	  { c_(); return edge_on_cell_iterator<gt>(static_cast<Cell const&>(*this),
						   TheArchetype().EndEdge());}

      };
} // namespace


#endif
