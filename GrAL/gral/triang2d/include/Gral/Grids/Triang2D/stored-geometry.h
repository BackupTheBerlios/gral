#ifndef GRAL_GB_TRIANG2D_STORED_GEOMETRY_H
#define GRAL_GB_TRIANG2D_STORED_GEOMETRY_H

// $LICENSE_NEC

/*! \file

*/

#include "Gral/Grids/Triang2D/triang2d.h"
#include "Geometry/point-traits.h"
#include "Geometry/algebraic-primitives.h"
#include "Utility/pre-post-conditions.h"

#include <iostream>
#include <cmath>

/*! \brief Geometry wrapper class for Triang2D

   \ingroup triang2dmodule 

   This class assumes vertex coordinates in an array
   \f$ (x_0,y_0, x_1, y_1, \ldots) \f$.

   It is a model of $GrAL VertexGridGeometry.

   \see \ref test-triang2d-geometry.C
   \todo It could be parameterised by scalar type of coordinates, 
    and by space dimension.
 */
class stored_geometry_triang2d {
public:
  typedef Triang2D                  grid_type; 
  typedef grid_types<grid_type>     gt;
  typedef gt::Vertex                Vertex;
  typedef gt::Edge                  Edge;
  typedef gt::Facet                 Facet;
  typedef gt::Cell                  Cell;
  typedef gt::VertexOnCellIterator  VertexOnCellIterator;
  typedef gt::EdgeOnCellIterator    EdgeOnCellIterator;

private:
  grid_type const* g;
  double         * xy;
  bool             owned;
public:
  //! Empty geometry
  stored_geometry_triang2d() : g(0), xy(0), owned(false) {}
  //! initialize with value semantics (coords are owned)
  stored_geometry_triang2d(grid_type const& g_)
    : g(&g_)
    { 
      init_xy();
    }
  //! initialize with reference semantics (coords are referenced)
  stored_geometry_triang2d(grid_type const& g_, double* xy_)
    : g(&g_), xy(xy_), owned(false) {}

  //! destructor
  ~stored_geometry_triang2d() { clear();}

  //! change to value semantics
  void set_grid(grid_type const& g_) {
    clear();
    g = & g_;
    init_xy();
  }
  //! Dimension of embedding space
  unsigned space_dimension() const { return 2;}
private:
  void clear() { if (owned) delete [] xy; xy = 0;}
  void init_xy() {
    if(g->NumOfVertices() > 0) {
      xy = new double[2*g->NumOfVertices()];
      owned = true;
    }
    else {
      xy = 0;
      owned = false;
    }
  }

public:
  //! Anchor grid
  grid_type const& TheGrid() const { return *g;}

  class coord_type;
  class coord_proxy {
    double* xy_v; // start address of xyz values of a vertex
    friend class coord_type;
  public:
    coord_proxy(double* xy_v_) : xy_v(xy_v_) {}
    inline void operator=(coord_type const& coo);
    template<class COORD>
    void operator=(COORD const& coo);

    double  operator[](int i) const { cr(i); return xy_v[i]; }
    double& operator[](int i)       { cr(i); return xy_v[i]; }

  private:
    void cr(int i) const {      
      REQUIRE( 0 <= i && i <  2, "i = " << i << " out of range!\n",1);
    }
  };

  //! \brief coordinate representation
  class coord_type : public array_operators<coord_type, double, 2> {
    double xy[2];
  public:
    coord_type() {}
    coord_type(coord_proxy p)            { init(p.xy_v);}
    coord_type(double const* xy_)        { init(xy_);}
    coord_type(double d)                 { xy[0] = xy[1] = d;}
    coord_type(double x, double y)       { xy[0] = x; xy[1] = y;}
    coord_type& operator=(coord_proxy p) { init(p.xy_v); return *this;}
    template<class COORD>
    void operator=(COORD const& coo);


    double  operator[](int i) const { cr(i); return xy[i]; }
    double& operator[](int i)       { cr(i); return xy[i]; }

  private:
    void cr(int i) const {      
      REQUIRE( 0 <= i && i <  2, "i = " << i << " out of range!\n",1);
    }
    void init(double const* p)
      { xy[0] = p[0]; xy[1] = p[1]; }
  };
  //! Representation of real numbers
  typedef double scalar_type;


  //! coordinate of Vertex (read/write access)
  coord_proxy coord(Vertex const& v) 
    { return coord_proxy(xy + 2*v.handle());}
  //! coordinate of Vertex (read access)
  coord_type  coord(Vertex const& v) const 
    { return coord_type (xy + 2*v.handle());}

  //! Length of (straight) edge
  inline scalar_type length(Edge const& e) const;

  //! \f$ d-1 \f$ dimensional volume of Facet (i.e. edge length)
  scalar_type volume(Facet const& f)  const { return length(f);}

  //! Center of intertia of \c c
  coord_type center(Cell const& c) const { return (coord(c.V(0)) + coord(c.V(1)) + coord(c.V(2)))/3.0;}

  //! Barycenter/Centroid (average of vertices) of cell \c c
  coord_type barycenter(Cell const& c) const { return center(c);}

  //! solid angle of the wedge of vertex \c vc, in radians (2D) 
  inline scalar_type solid_angle(VertexOnCellIterator const& vc) const;

  /*! ratio of solid angle of wedge \c vc to complete solid angle

      The ratios of the wedges of an internal regular vertex sum up to 1.
   */
  scalar_type solid_angle_ratio(VertexOnCellIterator const& vc) const { return solid_angle(vc)/(2*M_PI);}
};


inline std::ostream&
operator<<(std::ostream& out, stored_geometry_triang2d::coord_type const& p)
{ return (out << p[0] << ' ' << p[1]);}

inline std::istream&
operator>>(std::istream&  in, stored_geometry_triang2d::coord_type & p)
{ return (in >> p[0] >> p[1]);}


inline void
stored_geometry_triang2d::coord_proxy::operator=
(stored_geometry_triang2d::coord_type const& p)
{  xy_v[0] = p[0]; xy_v[1] = p[1]; }

template<class COORD>
inline void
stored_geometry_triang2d::coord_proxy::operator=
(COORD const& p)
{ 
  typedef point_traits<COORD> pt;
  xy_v[0] = pt::x(p);
  xy_v[1] = pt::y(p);
  // std::cout << xy_v[0] << " " << xy_v[1] << std::endl;
}


template<class COORD>
inline void
stored_geometry_triang2d::coord_type::operator=
(COORD const& p)
{ 
  typedef point_traits<COORD> pt;
  xy[0] = pt::x(p);
  xy[1] = pt::y(p);
}

template<>
struct point_traits<stored_geometry_triang2d::coord_type> 
  : public point_traits_fixed_size_array
        <stored_geometry_triang2d::coord_type,double,2> {};

template<>
struct point_traits<stored_geometry_triang2d::coord_proxy> 
  : public point_traits_fixed_size_array
        <stored_geometry_triang2d::coord_proxy,double,2> 
{
  typedef Ptype reference_type;
  static void ConstructWithDim(unsigned d, Ptype)
    { REQUIRE( d == 2, "d = " << d, 1); }
};

template<class Q>
inline void assign_point(stored_geometry_triang2d::coord_proxy p,
			 Q const& q) 
{
 typedef point_traits<stored_geometry_triang2d::coord_proxy> ptP;
 typedef point_traits<Q> ptQ;

 REQUIRE( (ptP::Dim(p) == ptQ::Dim(q)), 
	  "Cannot assign points of different dimension!" 
	  << "(dim(p) = " << ptP::Dim(p)  << ", "
	  << "(dim(q) = " << ptQ::Dim(q), 1);
 
 int iq = ptQ::LowerIndex(q); 
 int ip = ptP::LowerIndex(p);  
 for(; iq <= ptQ::UpperIndex(q); ++ip, ++iq)
   p[ip] = q[iq]; 
}  



inline stored_geometry_triang2d::scalar_type 
stored_geometry_triang2d::length(stored_geometry_triang2d::Edge const& e) const 
{ 
  typedef algebraic_primitives<coord_type> ap;
  return ap::distance(coord(e.V1()), coord(e.V2()));
}


inline stored_geometry_triang2d::scalar_type 
stored_geometry_triang2d::solid_angle(stored_geometry_triang2d::VertexOnCellIterator const& vc) const 
{
  typedef algebraic_primitives<coord_type> ap;
  Edge e1;
  Vertex v = *vc;
  for(EdgeOnCellIterator ec(vc.TheCell()); !ec.IsDone(); ++ec)
    if(v == (*ec).V1() || v == (*ec).V2()) {
      e1 = *ec;
      break;
    }
  Edge e2 = TheGrid().switched_edge(v,e1, vc.TheCell());
  coord_type dir_e1 = (coord(TheGrid().switched_vertex(v,e1)) - coord(v));
  coord_type dir_e2 = (coord(TheGrid().switched_vertex(v,e2)) - coord(v));
  return ap::angle(dir_e1, dir_e2);
}

#endif
