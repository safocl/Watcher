// Generated by gmmproc 2.64.2 -- DO NOT MODIFY!
#ifndef _GIOMM_FILEOUTPUTSTREAM_P_H
#define _GIOMM_FILEOUTPUTSTREAM_P_H


#include <giomm/private/outputstream_p.h>

#include <glibmm/class.h>

namespace Gio
{

class FileOutputStream_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = FileOutputStream;
  using BaseObjectType = GFileOutputStream;
  using BaseClassType = GFileOutputStreamClass;
  using CppClassParent = Gio::OutputStream_Class;
  using BaseClassParent = GOutputStreamClass;

  friend class FileOutputStream;
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


} // namespace Gio


#endif /* _GIOMM_FILEOUTPUTSTREAM_P_H */

