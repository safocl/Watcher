// Generated by gmmproc 2.60.0 -- DO NOT MODIFY!
#ifndef _GTKMM_RADIOMENUITEM_H
#define _GTKMM_RADIOMENUITEM_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/*
 * Copyright (C) 1998-2002 The gtkmm Development Team
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

#include <gtkmm/checkmenuitem.h>
#include <gtkmm/radiobutton.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GtkRadioMenuItem = struct _GtkRadioMenuItem;
using GtkRadioMenuItemClass = struct _GtkRadioMenuItemClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gtk
{ class RadioMenuItem_Class; } // namespace Gtk
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gtk
{

class RadioMenuItem;

/** A CheckMenuItem that belongs to a group.
 * At each instant exactly one of the menu items from a group is selected.
 * @ingroup Menus
 * @ingroup Widgets
 */

class RadioMenuItem : public CheckMenuItem
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef RadioMenuItem CppObjectType;
  typedef RadioMenuItem_Class CppClassType;
  typedef GtkRadioMenuItem BaseObjectType;
  typedef GtkRadioMenuItemClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  RadioMenuItem(RadioMenuItem&& src) noexcept;
  RadioMenuItem& operator=(RadioMenuItem&& src) noexcept;

  // noncopyable
  RadioMenuItem(const RadioMenuItem&) = delete;
  RadioMenuItem& operator=(const RadioMenuItem&) = delete;

  ~RadioMenuItem() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class RadioMenuItem_Class;
  static CppClassType radiomenuitem_class_;

protected:
  explicit RadioMenuItem(const Glib::ConstructParams& construct_params);
  explicit RadioMenuItem(GtkRadioMenuItem* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GtkRadioMenuItem*       gobj()       { return reinterpret_cast<GtkRadioMenuItem*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GtkRadioMenuItem* gobj() const { return reinterpret_cast<GtkRadioMenuItem*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::
  /// This is a default handler for the signal signal_group_changed().
  virtual void on_group_changed();


private:

public:
  using Group = RadioButtonGroup;

  /** @newin{3,22}
   */
  RadioMenuItem();

  /** @newin{3,22}
   */
  explicit RadioMenuItem(const Glib::ustring& label, bool mnemonic = false);

  RadioMenuItem(Group& groupx);
  
  RadioMenuItem(Group& groupx, const Glib::ustring& label, bool mnemonic = false);
  

  //We ignore the _new_*_from_widget() functions because they are just the same as calling join_group() ourselves.
  

  /** Returns the group to which the radio menu item belongs, as a List of
   * Gtk::RadioMenuItem. The list belongs to GTK+ and should not be freed.
   * 
   * @return The group
   * of @a radio_menu_item.
   */
  Group get_group();
  
  void set_group(Group& group);

  /** Removes the radio menu item from the group.
   */
  void reset_group();

 
  /** Joins a Gtk::RadioMenuItem object to the group of another Gtk::RadioMenuItem
   * object.
   * 
   * This function should be used by language bindings to avoid the memory
   * manangement of the opaque SList of get_group()
   * and set_group().
   * 
   * A common way to set up a group of Gtk::RadioMenuItem instances is:
   * 
   * 
   * [C example ellipted]
   * 
   * @newin{3,22}
   * 
   * @param group_source A Gtk::RadioMenuItem whose group we are
   * joining, or <tt>nullptr</tt> to remove the @a radio_menu_item from its current
   * group.
   */
  void join_group(RadioMenuItem& group_source);

  
  /**
   * @par Slot Prototype:
   * <tt>void on_my_%group_changed()</tt>
   *
   * Flags: Run First
   *
   */

  Glib::SignalProxy< void > signal_group_changed();


  /// Note that %property_group() corresponds to join_group(), rather than to get_group() and set_group().
  /** The radio menu item whose group this widget belongs to.
   * 
   * @newin{3,22}
   *
   * @return A PropertyProxy_WriteOnly that allows you to set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_WriteOnly< RadioMenuItem* > property_group() ;


protected:
  void constructor(const Group& group);


};

} /* namspace Gtk */


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::RadioMenuItem
   */
  Gtk::RadioMenuItem* wrap(GtkRadioMenuItem* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_RADIOMENUITEM_H */

