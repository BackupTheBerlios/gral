#ifndef GRAL_GB_GRAPH_BGL_PROPERTY_MAP_H
#define GRAL_GB_GRAPH_BGL_PROPERTY_MAP_H

// $LICENSE_NEC_2005

#include <boost/ref.hpp>

namespace boost {

  //--- make reference_wrapper<property_map> work ----

  template<class PM>
  typename PM::value_type 
  get(reference_wrapper<PM const> pm, typename PM::key_type k) { return get(pm.get(),k);}

  template<class PM>
  typename PM::value_type 
  get(reference_wrapper<PM      > pm, typename PM::key_type k) { return get(pm.get(),k);}

  template<class PM>
  void 
  put(reference_wrapper<PM      > pm, typename PM::key_type k, typename PM::value_type t) 
  { put(pm.get(),k,t);}


} // namespace boost 

#endif
