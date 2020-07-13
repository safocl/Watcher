// Generated by gmmproc 2.60.0 -- DO NOT MODIFY!
#ifndef _GTKMM_TEXTTAGTABLE_P_H
#define _GTKMM_TEXTTAGTABLE_P_H


#include <glibmm/private/object_p.h>

#include <glibmm/class.h>

namespace Gtk
{

class TextTagTable_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = TextTagTable;
  using BaseObjectType = GtkTextTagTable;
  using BaseClassType = GtkTextTagTableClass;
  using CppClassParent = Glib::Object_Class;
  using BaseClassParent = GObjectClass;

  friend class TextTagTable;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.
  static void tag_changed_callback(GtkTextTagTable* self, GtkTextTag* p0, gboolean p1);
  static void tag_added_callback(GtkTextTagTable* self, GtkTextTag* p0);
  static void tag_removed_callback(GtkTextTagTable* self, GtkTextTag* p0);

  //Callbacks (virtual functions):
};


} // namespace Gtk


#endif /* _GTKMM_TEXTTAGTABLE_P_H */

