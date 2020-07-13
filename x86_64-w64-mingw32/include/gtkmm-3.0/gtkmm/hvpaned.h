// Generated by gmmproc 2.60.0 -- DO NOT MODIFY!
#ifndef _GTKMM_HVPANED_H
#define _GTKMM_HVPANED_H


#ifndef GTKMM_DISABLE_DEPRECATED


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 1998-2011 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <gtkmm/paned.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GtkHPaned = struct _GtkHPaned;
using GtkHPanedClass = struct _GtkHPanedClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gtk
{ class HPaned_Class; } // namespace Gtk
#endif //DOXYGEN_SHOULD_SKIP_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GtkVPaned = struct _GtkVPaned;
using GtkVPanedClass = struct _GtkVPanedClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gtk
{ class VPaned_Class; } // namespace Gtk
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gtk
{

/**
 * The Gtk::HPaned widget is a container widget with two children arranged
 * horizontally. The division between the two panes is adjustable by the
 * user by dragging a handle. See Gtk::Paned for details.
 *
 * @ingroup Widgets
 *
 * @deprecated Use Paned instead.
 */

class HPaned : public Paned
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef HPaned CppObjectType;
  typedef HPaned_Class CppClassType;
  typedef GtkHPaned BaseObjectType;
  typedef GtkHPanedClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  HPaned(HPaned&& src) noexcept;
  HPaned& operator=(HPaned&& src) noexcept;

  // noncopyable
  HPaned(const HPaned&) = delete;
  HPaned& operator=(const HPaned&) = delete;

  ~HPaned() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class HPaned_Class;
  static CppClassType hpaned_class_;

protected:
  explicit HPaned(const Glib::ConstructParams& construct_params);
  explicit HPaned(GtkHPaned* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GtkHPaned*       gobj()       { return reinterpret_cast<GtkHPaned*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GtkHPaned* gobj() const { return reinterpret_cast<GtkHPaned*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

  
public:
  HPaned();


};

/**
 * The Gtk::VPaned widget is a container widget with two children arranged
 * vertically. The division between the two panes is adjustable by the
 * user by dragging a handle. See Gtk::Paned for details.
 *
 * @ingroup Widgets
 *
 * @deprecated Use Paned instead.
 */

class VPaned : public Paned
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef VPaned CppObjectType;
  typedef VPaned_Class CppClassType;
  typedef GtkVPaned BaseObjectType;
  typedef GtkVPanedClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  VPaned(VPaned&& src) noexcept;
  VPaned& operator=(VPaned&& src) noexcept;

  // noncopyable
  VPaned(const VPaned&) = delete;
  VPaned& operator=(const VPaned&) = delete;

  ~VPaned() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class VPaned_Class;
  static CppClassType vpaned_class_;

protected:
  explicit VPaned(const Glib::ConstructParams& construct_params);
  explicit VPaned(GtkVPaned* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GtkVPaned*       gobj()       { return reinterpret_cast<GtkVPaned*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GtkVPaned* gobj() const { return reinterpret_cast<GtkVPaned*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

  
public:
  VPaned();


};

} // namespace Gtk


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::HPaned
   */
  Gtk::HPaned* wrap(GtkHPaned* object, bool take_copy = false);
} //namespace Glib


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::VPaned
   */
  Gtk::VPaned* wrap(GtkVPaned* object, bool take_copy = false);
} //namespace Glib


#endif // GTKMM_DISABLE_DEPRECATED


#endif /* _GTKMM_HVPANED_H */

