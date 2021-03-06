#ifndef GRAL_GB_SEQUENCE_INTEGER_RANGE_H
#define GRAL_GB_SEQUENCE_INTEGER_RANGE_H


/* ------------------------------------------------------------

    Copyright (C) 2004 - 2009 Guntram Berti

    This file is part of the Grid Algorithms Library (GrAL),
    available at http://gral.berlios.de

    GrAL is distributed under the MIT license,
    see the file LICENSE or http://gral.berlios.de/license

--------------------------------------------------------------- */


#include "Geometry/interval.h"
#include "Container/sequence-algorithms.h"
#include "Utility/checked-istream.h"
#include "Utility/pre-post-conditions.h"

#include <ctype.h>
#include <iostream>
#include <vector>

namespace GrAL {  namespace sequence {

  /*! \brief Union of integer intervals

      This class represents a set of integers, represented
      as a sequence of closed intervals. It main feature 
      it the ability to read range descriptions like <tt>6,8,10-33,40-100</tt>
      via <tt>operator>></tt>.
   */
  template<class INT> class integer_range {
    typedef interval<INT> interval_type;
    typedef INT           element_type;
    std::vector<interval_type> intervals;
  public:
    //! Construct empty range
    integer_range() {}
    //! Construct range of single point
    integer_range(INT i) { intervals.push_back(interval_type(i,i));}
    //! Construct range of single interval
    integer_range(interval_type iv) { if(!iv.empty()) intervals.push_back(iv);}
    //! Construct ouf of a range of elements
    template<class IT>
    integer_range(IT b, IT e) { init(b,e);}

    //! True if no integer is contained
    bool empty() const { return intervals.empty();}
    //! Set to empty range
    void clear()       { intervals.clear();}

    //! STL-compliant iterator
    typedef typename std::vector<interval_type>::const_iterator interval_iterator;
    //! First interval
    interval_iterator begin_interval() const { return intervals.begin();}
    //! Past-the-end interval
    interval_iterator end_interval()   const { return intervals.end();}

    //! smallest element. The range is contained in [low(), high()]
    element_type low()  const {return intervals.front().low();}
    //! largest element. The range is contained in [low(), high()]
    element_type high() const {return intervals.back() .high();}

    // iterator over all elements in the range
    struct const_iterator {
      typedef const_iterator     self;
      typedef integer_range<INT> integer_range_type;
      typedef INT                value_type;

      interval_iterator          interval;
      int                        i;

      const_iterator() {}
      const_iterator(interval_iterator interval_, int i_) : interval(interval_), i(i_) {}
      value_type operator*() const { return (*interval).low() + i;}
      self & operator++() { 
	++i; 
	if(i > (*interval).high() - (*interval).low()) { 
	  ++interval; 
	  i = 0;
	}
	return *this;
      }
      bool operator==(self const& rhs) const { return interval == rhs.interval && i == rhs.i;}
      bool operator!=(self const& rhs) const { return !(*this == rhs);}
      bool operator< (self const& rhs) const { return interval < rhs.interval || (interval == rhs.interval && i < rhs.i);}
    };
    const_iterator begin() const { return const_iterator(begin_interval(), 0);}
    const_iterator end  () const { return const_iterator(end_interval(),   0);}

    /*! \brief Initialize range with sequence of elements

        The sequence [b,e[ may be unordered and contain duplicates.
    */
    template<class IT>
    void init(IT b, IT e);
    /*! \brief Add an element to the range.
        \pre <tt> i > high() </tt>
    */
    void push_back(element_type i) {
      REQUIRE(empty() || i > high(), "i=" << i,1);
      if(empty() || i > 1 + high())
	intervals.push_back(interval_type(i,i));
      else // i == 1 + high()
	intervals.back() = interval_type(intervals.back().low(), i);
    }
    //! True iff \c i is contained in an interval
    bool contains(INT i) const { 
      for(interval_iterator iv = begin_interval(); iv != end_interval(); ++iv)
	if(iv->contains(i))
	  return true;
      return false;
    }
    void read(std::istream& in);
  private:
    // returns false if read not successful
    bool read_interval(std::istream& in, interval_type& iv, bool& end);
    // returns false if read not successful
    bool read_number  (std::istream& in, INT & i);
    //  void compactify() { /* sort and join overlapping intervals */ }
  };

  /*! \brief Input operator. Can read range descriptions like <tt>6,8,10-33,40-100</tt>.
      
   */
  template<class INT>
  std::istream& operator>>(std::istream& in, integer_range<INT> & r)
  { r.read(in); return in;}

  /*! \brief Output operator

       Writes the range <tt>6,8,10-33,40-100</tt> 
       in the normalized form <tt>6-6,8-8,10-33,40-100</tt>.
   */ 
  template<class INT>
  std::ostream& operator<<(std::ostream& out, integer_range<INT> const& r)
  { 
    for(typename integer_range<INT>::interval_iterator iv = r.begin_interval(); iv != r.end_interval(); ++iv) {
      if(iv != r.begin_interval())
	out << ',';
      out << iv->l() << '-' << iv->r();
    }
    return out;
  }

  
  template<class INT>
  template<class IT>
  void integer_range<INT>::init(IT b, IT e)
    {
      std::vector<element_type> elements(b,e);
      sequence::sort_and_make_unique(elements);
      typename std::vector<element_type>::iterator 
	interval_beg = elements.begin(),
	interval_end = elements.begin();
      // get all intervals in elements
      while(interval_beg != elements.end()) {
	// find the largest interval in [interval_beg, elements.end()[, 
	// i.e. make [interval_beg, interval_end[ the largest sequence in elements without gap
	int n = 0;
	while(interval_end != elements.end() &&
	      *interval_end <= n + *interval_beg) {
	  ++interval_end;
	  ++n;
	}
	// now interval_end == elements.end() || *interval_end > 1 + interval_beg
	intervals.push_back(interval_type(* interval_beg,
					  *(interval_end-1)));
	interval_beg = interval_end;
      }
    }




  template<class INT> 
  void integer_range<INT>::read(std::istream& in)
  {
    clear();
    interval_type iv;
    bool end = false;
    while(!end && read_interval(in,iv,end) ) { 
      if(! iv.empty())
	intervals.push_back(iv);
    }
  }

  template<class INT> 
  bool integer_range<INT>::read_number  (std::istream& in, INT & i)
  {
    checked_istream checked_in(in);
    return (checked_in >> i);
  }
  
  template<class INT> 
  bool integer_range<INT>::read_interval(std::istream& in, typename integer_range<INT>::interval_type & iv, bool& end) 
  {
    INT low, high;
    bool res = true;
    if(! (in >> low)) {
      end = true;
      return false;
    }
    high = low;
    char next = '\0';

    if(in.eof() || ! in.get(next)) {
      end = true;
      in.clear();
    }
    else {
      if(next == '-') {
	res = read_number(in, high);
	if(res) {
	  if(in.get(next) &&  next != ',') {
	    if(! isspace(next)) {
	      res = false;
	    }
	    else {
	      end = true;
	    }
	    in.putback(next);
	  }
	}
      }
      else if( next == ',') {
	res = true;
	if(in.get(next)) {
	  end = ! (isdigit(next) || next == '-' || next == '+'); // sign prefixes!
	  in.putback(next);
	}
      }
      else if(isspace(next)) {
	res = true;
	end = true;
	in.putback(next);
      }
      else {
        res = false;
	end = true;
	// REQUIRE(false,"Failure to read interval!",1);
      }
    } // could get next char
    iv = interval_type(low,high);
    return res;
  }


} } // namespace GrAL {  namespace sequence {

#endif
