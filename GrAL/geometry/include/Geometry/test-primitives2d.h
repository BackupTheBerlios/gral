#ifndef GRAL_GB_TEST_PRIMITIVES2D_H
#define GRAL_GB_TEST_PRIMITIVES2D_H


/* ------------------------------------------------------------

    Copyright (C) 1997 - 2009 Guntram Berti

    This file is part of the Grid Algorithms Library (GrAL),
    available at http://gral.berlios.de

    GrAL is distributed under the MIT license,
    see the file LICENSE or http://gral.berlios.de/license

--------------------------------------------------------------- */


namespace GrAL {

template<class POINT>
struct test_algebraic_primitives2d
{
  void do_tests(::std::ostream & out);
};

} // namespace GrAL {

#ifdef NMWR_INCLUDE_TEMPLATE_DEFS
#include "Geometry/internal/test-primitives2d.C"
#endif


#endif
