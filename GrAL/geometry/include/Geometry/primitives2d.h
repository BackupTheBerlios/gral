#ifndef NMWR_GB_ALGEBRAIC_PRIMITIVES_2D_H
#define NMWR_GB_ALGEBRAIC_PRIMITIVES_2D_H


// $LICENSE

//----------------------------------------------------------------
//
// specialize dimension_dependent_primitives<POINT>
// to dimension_dependent_primitives_2d<POINT> for 2D points.
//
//----------------------------------------------------------------

#include <algorithm> // STL: swap


template<class POINT>
struct dimension_dependent_primitives_2d 
  : public virtual basic_algebraic_primitives<POINT> 
{
private:
  typedef basic_algebraic_primitives<POINT> base;
public:
  typedef typename base::scalar scalar;
  typedef typename base::real   real;


  static double det2(const POINT& p1, const POINT& p2)
    {
      int l = point_traits<POINT>::LowerIndex(p1);
      // IOMgr::Info() << "lower index: " << l << endl;
      // IOMgr::Info() << p1 << " " << p2 << endl;
      return (p1[l]*p2[l+1]-p1[l+1]*p2[l]);
    }

  static double signed_triangle_area(const POINT& p1, const POINT& p2, const POINT& p3)
    { 
      // IOMgr::Info() << "signed triangle area: " 
      //		    << p1 << " " << p2 << " " << p3 << endl;
      return (0.5 * det2(p1-p2,p1-p3)); }

  static double triangle_area(const POINT& p1, const POINT& p2, const POINT& p3)
    {
      double a(signed_triangle_area(p1,p2,p3));
      return(a >= 0 ? a : -a);
    }

  static POINT normal_with_same_length(const POINT& p)
    {
      int l = LowerIndex(p);
      return POINT(-p[l+1],p[l]);
    }

  static POINT normed_normal(const POINT& p)
    {
      POINT q(normal_with_same_length(p));
      return (q/norm_2(q));
    }


  static void transpose(POINT & p, POINT & q) {
    std::swap(y(p),x(q));
  }

  static POINT left_perp(POINT const& p) {
    return POINT(-y(p), x(p));
  }
  static void left_rotate(POINT & p) {
    scalar xp = x(p);
    x(p) = y(p);
    y(p) = -xp;
  }
  static POINT right_perp(POINT const& p) {
    return POINT(y(p), -x(p));
  }
  static void right_rotate(POINT & p) {
    scalar xp = x(p);
    x(p) = -y(p);
    y(p) =  xp;
  }
  static POINT any_perp(POINT const& p) {
    return POINT(-y(p), x(p));
  }
 
    /*! \brief Return normal direction of (1-dimensional) hyperspace spanned by [begin,end[.

      Dimension-independent interface.
   */
  template<class IT>
  static POINT perp(IT begin, IT end) { return normal_with_same_length(*begin);}


  static std::vector<POINT> basis_completion(std::vector<POINT> const& dirs) {
    std::vector<POINT> res;
    if(dirs.size() == 1) {
      res.resize(1);
      res[0] = perp(dirs.begin(), dirs.end());
    }
    else if(dirs.size() == 0) {
      res.resize(2);
      res[0] = pt::Origin(2); pt::x(res[0]) = 1;
      res[1] = pt::Origin(2); pt::y(res[1]) = 1;
    }
    return res;
  }

  // solve (A1,A2)*X = b
  static void solve2(POINT const& A1, POINT const& A2,
                     POINT      & X,  POINT const& b)
  {
    scalar d = det2(A1,A2);
    x(X) = ( y(A2) * x(b) - x(A2) * y(b))/d;
    y(X) = (-y(A1) * x(b) + x(A1) * y(b))/d;
  }

  static void solveA(POINT  A1, POINT  A2,
                     POINT& X , POINT  b)
  {
    if(fabs(x(A1)) < fabs(y(A1))) {
      std::swap(x(A1),y(A1));
      std::swap(x(A2),y(A2));
      std::swap(x(b) ,y(b));
    }
    // Lu = b, l_21 = a21/a11 = y(A1)/x(A1)
    scalar u1 = x(b);
    scalar u2 = y(b)-(y(A1)/x(A1))*u1;
    // Rx = u, r11 = x(A1), r12 = x(A2), r22 = y(A2) - y(A1)x(A1)^-1x(A2)
    y(X) = u2/(y(A2) - (y(A1)/x(A1))*x(A2));
    x(X) = (u1 - x(A2)*y(X))/x(A1);
  }
};

#endif
