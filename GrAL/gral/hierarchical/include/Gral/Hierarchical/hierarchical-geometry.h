#ifndef GRAL_GB_HIERARCHICAL_GEOMETRY_H
#define GRAL_GB_HIERARCHICAL_GEOMETRY_H

// $LICENSE_NEC

#include "Utility/ref-ptr.h"
#include "Gral/Hierarchical/hierarchical-grid-table.h"
#include "Gral/Hierarchical/hierarchical-grid.h"

namespace hierarchical {

  /*! \brief A geometry type  for hierarchical grids

      \author Guntram Berti

      \templateparams
      - \c HGRID : an hierarchical grid
      - \c FLATGEOM : a geometry on HGRID::flat_grid_type


  */
  template<class HGRID, class FLATGEOM>
  class hier_geometry : public hier_grid_table<HGRID, FLATGEOM> {
    typedef hier_grid_table<HGRID, FLATGEOM> base;
    typedef typename base::notifier_base  notifier_base;
    typedef typename base::notifier_type  notifier_type;
  public:
    typedef HGRID          hier_grid_type;
    typedef hier_grid_type grid_type;
    typedef hier_grid_type hgt;
    typedef typename hgt::level_handle   level_handle;

    typedef FLATGEOM                                flat_geometry_type;
    typedef typename flat_geometry_type::coord_type coord_type;

    typedef typename base::reference         reference;
    typedef typename base::const_reference   const_reference;

    template<class ELEMBASE>
    struct vertex_template { typedef typename hier_grid_type::template vertex_template<ELEMBASE>::type type;};
  private:
    ref_ptr<flat_geometry_type const> root_geom;
  public:
    hier_geometry();
    hier_geometry(        hier_grid_type const& gg);
    hier_geometry(ref_ptr<hier_grid_type const> gg);
    hier_geometry(        hier_grid_type const& gg,         flat_geometry_type const& root_geo);
    hier_geometry(ref_ptr<hier_grid_type const> gg, ref_ptr<flat_geometry_type const> root_geo);


    void set_grid  (        hier_grid_type const& gg);
    void set_grid  (ref_ptr<hier_grid_type const> gg);
    //void set_grid  (        hier_grid_type const& gg,         flat_geometry_type const& root_geo);
    //void set_grid  (ref_ptr<hier_grid_type const> gg, ref_ptr<flat_geometry_type const> root_geo);

    void clear();

    //! get in sync with grid: add/remove missing/superfluous level
    void update();

    reference       Geom(level_handle lev)       { return base::operator[](lev);}
    const_reference Geom(level_handle lev) const { return base::operator()(lev);}

    template<class V>
    coord_type coord(V const& v) const
    { return Geom(v.level()).coord(v.Flat());}

  private:
    //    void init(hier_grid_type const& gg);
  public:
    level_handle add_coarser_level();
    level_handle add_finer_level();
    void         remove_coarsest_level();
    void         remove_finest_level();

  }; //  class hier_geometry<HGRID, GE>


} // namespace hierarchical


#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "hierarchical-geometry.C"
#endif

#endif
