#ifndef NMWR_GB_GRAPHICSDEVICE_GEOM_WORD_H
#define NMWR_GB_GRAPHICSDEVICE_GEOM_WORD_H

// $LICENSE

#include <math.h>
#include <string>

#include "Utility/pre-post-conditions.h"

#include "GraphicsDevice/geom.h"
#include "GraphicsDevice/rendering-language.h"
#include "GraphicsDevice/renderable-geom.h"
#include "GraphicsDevice/transformation.h"

/*! \brief A geometric representation of a string
    \ingroup geometricshape
    \todo replace member corner() with ll(), ul(), br().
    \see RWord()
    \see RLetter()
 */
class geom_word : public geom {
private:
  typedef geom_word self;
  std::string str;
  coord_type c[3]; //< c[0] = lower left, c[1] = lower right, c[2] = upper left
protected:
  void init(std::string const& ss, 
            coord_type  const& cc1);
  void init(std::string const& ss,
            coord_type  const& cc1,
            coord_type  const& cc2,
            coord_type  const& cc3);
public:
  geom_word(const string& ss,coord_type const& cc1) {str=ss;c[0]=cc1;}
  geom_word(const string& ss,
            coord_type const& cc1,
            coord_type const& cc2,
            coord_type const& cc3) 
  { init(ss,cc1,cc2,cc3); }
  virtual self * clone() const { return new self(*this); }

  virtual void write_geom_to(rendering_language& L) const; 

  string text() const { return str;}

  coord_type const&  corner(int i) const 
    {
      REQUIRE( (i <= 3 && i >=1),
	       "geom_word::corner called with i= "<<i,1);
      return c[i-1];
    }

};

/*! \brief Creator function for geometric string
    \ingroup geometricshape
 */
extern RenderableGeom RWord(std::string                const& str, 
                            RenderableGeom::coord_type const& c1,  //< lower left
                            RenderableGeom::coord_type const& c2,  //< lower right
                            RenderableGeom::coord_type const& c3); //< upper left


#endif