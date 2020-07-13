// Generated by gmmproc 2.60.0 -- DO NOT MODIFY!
#ifndef _GTKMM_FLOWBOXCHILD_H
#define _GTKMM_FLOWBOXCHILD_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 2014 The gtkmm Development Team
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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm/bin.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GtkFlowBoxChild = struct _GtkFlowBoxChild;
using GtkFlowBoxChildClass = struct _GtkFlowBoxChildClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gtk
{ class FlowBoxChild_Class; } // namespace Gtk
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gtk
{

/** See the description of FlowBox.
 *
 * @ingroup Widgets
 * @ingroup Containers
 *
 * @newin{3,12}
 */

class FlowBoxChild
  : public Bin
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef FlowBoxChild CppObjectType;
  typedef FlowBoxChild_Class CppClassType;
  typedef GtkFlowBoxChild BaseObjectType;
  typedef GtkFlowBoxChildClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  FlowBoxChild(FlowBoxChild&& src) noexcept;
  FlowBoxChild& operator=(FlowBoxChild&& src) noexcept;

  // noncopyable
  FlowBoxChild(const FlowBoxChild&) = delete;
  FlowBoxChild& operator=(const FlowBoxChild&) = delete;

  ~FlowBoxChild() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class FlowBoxChild_Class;
  static CppClassType flowboxchild_class_;

protected:
  explicit FlowBoxChild(const Glib::ConstructParams& construct_params);
  explicit FlowBoxChild(GtkFlowBoxChild* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  GtkFlowBoxChild*       gobj()       { return reinterpret_cast<GtkFlowBoxChild*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const GtkFlowBoxChild* gobj() const { return reinterpret_cast<GtkFlowBoxChild*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::
  /// This is a default handler for the signal signal_activate().
  virtual void on_activate();


private:

public:

  /** Creates a new FlowBoxChild, to be used as a child of a FlowBox.
   */
  FlowBoxChild();

  
  /** Gets the current index of the @a child in its Gtk::FlowBox container.
   * 
   * @newin{3,12}
   * 
   * @return The index of the @a child, or -1 if the @a child is not
   * in a flow box.
   */
  int get_index() const;
  
  /** Returns whether the @a child is currently selected in its
   * Gtk::FlowBox container.
   * 
   * @newin{3,12}
   * 
   * @return <tt>true</tt> if @a child is selected.
   */
  bool is_selected() const;
  
  /** Marks @a child as changed, causing any state that depends on this
   * to be updated. This affects sorting and filtering.
   * 
   * Note that calls to this method must be in sync with the data
   * used for the sorting and filtering functions. For instance, if
   * the list is mirroring some external data set, and *two* children
   * changed in the external data set when you call
   * changed() on the first child, the sort function
   * must only read the new data for the first of the two changed
   * children, otherwise the resorting of the children will be wrong.
   * 
   * This generally means that if you don’t fully control the data
   * model, you have to duplicate the data that affects the sorting
   * and filtering functions into the widgets themselves. Another
   * alternative is to call invalidate_sort() on any
   * model change, but that is more expensive.
   * 
   * @newin{3,12}
   */
  void changed();

  
  /**
   * @par Slot Prototype:
   * <tt>void on_my_%activate()</tt>
   *
   * Flags: Run First, Action
   *
   * The signal_activate() signal is emitted when the user activates
   * a child widget in a Gtk::FlowBox, either by clicking or
   * double-clicking, or by using the Space or Enter key.
   * 
   * While this signal is used as a
   * [keybinding signal][GtkBindingSignal],
   * it can be used by applications for their own purposes.
   */

  Glib::SignalProxy< void > signal_activate();


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
   * @relates Gtk::FlowBoxChild
   */
  Gtk::FlowBoxChild* wrap(GtkFlowBoxChild* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_FLOWBOXCHILD_H */

