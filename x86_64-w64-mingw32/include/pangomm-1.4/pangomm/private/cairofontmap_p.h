// Generated by gmmproc 2.64.1 -- DO NOT MODIFY!
#ifndef _PANGOMM_CAIROFONTMAP_P_H
#define _PANGOMM_CAIROFONTMAP_P_H


#include <glibmm/private/interface_p.h>

#include <glibmm/private/interface_p.h>

namespace Pango
{

class CairoFontMap_Class : public Glib::Interface_Class
{
public:
  using CppObjectType = CairoFontMap;
  using BaseObjectType = PangoCairoFontMap;
  using BaseClassType = PangoCairoFontMapIface;
  using CppClassParent = Glib::Interface_Class;

  friend class CairoFontMap;

  const Glib::Interface_Class& init();

  static void iface_init_function(void* g_iface, void* iface_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Pango


#endif /* _PANGOMM_CAIROFONTMAP_P_H */

