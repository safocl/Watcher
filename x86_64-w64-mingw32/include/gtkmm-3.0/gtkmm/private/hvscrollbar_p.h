// Generated by gmmproc 2.60.0 -- DO NOT MODIFY!
#ifndef _GTKMM_HVSCROLLBAR_P_H
#define _GTKMM_HVSCROLLBAR_P_H
#ifndef GTKMM_DISABLE_DEPRECATED


#include <gtkmm/private/scrollbar_p.h>

#include <glibmm/class.h>

namespace Gtk
{

class VScrollbar_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = VScrollbar;
  using BaseObjectType = GtkVScrollbar;
  using BaseClassType = GtkVScrollbarClass;
  using CppClassParent = Gtk::Scrollbar_Class;
  using BaseClassParent = GtkScrollbarClass;

  friend class VScrollbar;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Gtk


#include <glibmm/class.h>

namespace Gtk
{

class HScrollbar_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = HScrollbar;
  using BaseObjectType = GtkHScrollbar;
  using BaseClassType = GtkHScrollbarClass;
  using CppClassParent = Gtk::Scrollbar_Class;
  using BaseClassParent = GtkScrollbarClass;

  friend class HScrollbar;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
};


} // namespace Gtk

#endif // GTKMM_DISABLE_DEPRECATED


#endif /* _GTKMM_HVSCROLLBAR_P_H */

