// Generated by gmmproc 2.64.2 -- DO NOT MODIFY!
#ifndef _GIOMM_SOCKETCONTROLMESSAGE_P_H
#define _GIOMM_SOCKETCONTROLMESSAGE_P_H


#include <glibmm/private/object_p.h>

#include <glibmm/class.h>

namespace Gio
{

class SocketControlMessage_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = SocketControlMessage;
  using BaseObjectType = GSocketControlMessage;
  using BaseClassType = GSocketControlMessageClass;
  using CppClassParent = Glib::Object_Class;
  using BaseClassParent = GObjectClass;

  friend class SocketControlMessage;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();


  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.

  //Callbacks (virtual functions):
  static gsize get_size_vfunc_callback(GSocketControlMessage* self);
  static int get_level_vfunc_callback(GSocketControlMessage* self);
  static int get_type_vfunc_callback(GSocketControlMessage* self);
  static void serialize_vfunc_callback(GSocketControlMessage* self, gpointer data);
  static GSocketControlMessage* deserialize_vfunc_callback(
    int level, int type, gsize size, gpointer data);
  };


} // namespace Gio


#endif /* _GIOMM_SOCKETCONTROLMESSAGE_P_H */

