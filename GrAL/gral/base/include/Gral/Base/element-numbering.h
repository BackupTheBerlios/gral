#ifndef GRAL_GB_BASE_ELEMENT_NUMBERING_H
#define GRAL_GB_BASE_ELEMENT_NUMBERING_H

// $LICENSE_NEC

#include "Gral/Base/common-grid-basics.h"


template<class E, class GT, class consecutive_tag>
class element_numbering_aux {};



template<class E, class GT, int N>
class element_numbering_aux<E, GT, consecutive_integer_tag<N> > 
{

public:
  typedef E element_type;
  typedef element_traits<E> et;
  typedef typename GT::grid_type grid_type;
private:
  grid_type const* g;
  int   offset_;
public:
  element_numbering_aux(grid_type const& gg, int offset = 0) 
    : g(&gg), offset_(offset) {}

  int operator()(element_type const& e) const 
    { return (e.handle() - N + offset_);}

  grid_type const& TheGrid() const { return *g;}

};


template<class E, class GT>
class element_numbering_aux<E, GT, non_consecutive_tag > 
{

public:
  typedef E element_type;
  typedef element_traits<E> et;
  typedef typename GT::grid_type grid_type;
  // how to get ElementIterator out of GT ????
private:
  grid_function<element_type, int> num;
  int   offset_;
public:
  element_numbering_aux(grid_type const& gg, int offset = 0) 
    : num(gg), offset_(offset) 
    {
      int n = offset_;
      for(typename et::ElementIterator e(num.TheGrid()); ! e.IsDone(); ++e)
	num[*e] = n++;
    }

  int operator()(element_type const& e) const 
    { return num(e);}

  grid_type const& TheGrid() const { return num.TheGrid();}

};


/*! \brief Provide a consecutive numbering of grid elements
 
   \ingroup elements
 
    This class has an important specialization in the 
    case that the corresponding elements are already numbered
    in a consecutive way. Then, we can compute the enumeration
    on the fly, by simply adding the offset. Else, we must use
    a grid function.

    \todo Make it deal correctly with grid subranges, where the
     \c consecutive_tag of underlying \c element_handle does not
     induce the Right Thing. 
 */

template<class E, class GT = grid_types<typename element_traits<E>::grid_type> >
class element_numbering :
  public element_numbering_aux<E, GT, typename element_traits<E>::consecutive_tag>
{
  typedef element_numbering_aux<E, GT, typename element_traits<E>::consecutive_tag> base;
public:
  element_numbering(typename base::grid_type const& g,
		    int offset = 0) : base(g, offset) {}
};

#endif
