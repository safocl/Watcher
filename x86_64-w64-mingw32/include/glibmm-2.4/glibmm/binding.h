// Generated by gmmproc 2.64.2 -- DO NOT MODIFY!
#ifndef _GLIBMM_BINDING_H
#define _GLIBMM_BINDING_H


/* Copyright (C) 2014 The glibmm Development Team
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

#include <glibmm/object.h>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <glibmm/value.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GBinding = struct _GBinding;
using GBindingClass = struct _GBindingClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{ class GLIBMM_API Binding_Class; } // namespace Glib
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Glib
{
/** @addtogroup glibmmEnums glibmm Enums and Flags */

/** 
 *  @var BindingFlags BINDING_DEFAULT
 * The default binding; if the source property
 * changes, the target property is updated with its value.
 * 
 *  @var BindingFlags BINDING_BIDIRECTIONAL
 * Bidirectional binding; if either the
 * property of the source or the property of the target changes,
 * the other is updated.
 * 
 *  @var BindingFlags BINDING_SYNC_CREATE
 * Synchronize the values of the source and
 * target properties when creating the binding; the direction of
 * the synchronization is always from the source to the target.
 * 
 *  @var BindingFlags BINDING_INVERT_BOOLEAN
 * If the two properties being bound are
 * booleans, setting one to <tt>true</tt> will result in the other being
 * set to <tt>false</tt> and vice versa. This flag will only work for
 * boolean properties, and cannot be used when passing custom
 * transformation functions to g_object_bind_property_full().
 * 
 *  @enum BindingFlags
 * 
 * Flags to be passed to g_object_bind_property() or
 * g_object_bind_property_full().
 * 
 * This enumeration can be extended at later date.
 * 
 * @newin{2,44}
 *
 * @ingroup glibmmEnums
 * @par Bitwise operators:
 * <tt>%BindingFlags operator|(BindingFlags, BindingFlags)</tt><br>
 * <tt>%BindingFlags operator&(BindingFlags, BindingFlags)</tt><br>
 * <tt>%BindingFlags operator^(BindingFlags, BindingFlags)</tt><br>
 * <tt>%BindingFlags operator~(BindingFlags)</tt><br>
 * <tt>%BindingFlags& operator|=(BindingFlags&, BindingFlags)</tt><br>
 * <tt>%BindingFlags& operator&=(BindingFlags&, BindingFlags)</tt><br>
 * <tt>%BindingFlags& operator^=(BindingFlags&, BindingFlags)</tt><br>
 */
enum BindingFlags
{
  BINDING_DEFAULT = 0x0,
  BINDING_BIDIRECTIONAL = 1 << 0,
  BINDING_SYNC_CREATE = 1 << 1,
  BINDING_INVERT_BOOLEAN = 1 << 2
};

/** @ingroup glibmmEnums */
inline BindingFlags operator|(BindingFlags lhs, BindingFlags rhs)
  { return static_cast<BindingFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs)); }

/** @ingroup glibmmEnums */
inline BindingFlags operator&(BindingFlags lhs, BindingFlags rhs)
  { return static_cast<BindingFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs)); }

/** @ingroup glibmmEnums */
inline BindingFlags operator^(BindingFlags lhs, BindingFlags rhs)
  { return static_cast<BindingFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs)); }

/** @ingroup glibmmEnums */
inline BindingFlags operator~(BindingFlags flags)
  { return static_cast<BindingFlags>(~static_cast<unsigned>(flags)); }

/** @ingroup glibmmEnums */
inline BindingFlags& operator|=(BindingFlags& lhs, BindingFlags rhs)
  { return (lhs = static_cast<BindingFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs))); }

/** @ingroup glibmmEnums */
inline BindingFlags& operator&=(BindingFlags& lhs, BindingFlags rhs)
  { return (lhs = static_cast<BindingFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs))); }

/** @ingroup glibmmEnums */
inline BindingFlags& operator^=(BindingFlags& lhs, BindingFlags rhs)
  { return (lhs = static_cast<BindingFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs))); }

} // namespace Glib

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value<Glib::BindingFlags> : public Glib::Value_Flags<Glib::BindingFlags>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace Glib
{


/** Bind two object properties.
 *
 * Glib::Binding is the representation of a binding between a property on a
 * Glib::ObjectBase instance (or source) and another property on another Glib::ObjectBase
 * instance (or target). Whenever the source property changes, the same
 * value is applied to the target property; for instance, the following binding:
 *
 * @code
 * Glib::Binding::bind_property(object1->property_a(), object2->property_b());
 * @endcode
 *
 * will cause property_b() of @a object2 to be updated
 * every time the value of property_a() of @a object1 changes.
 *
 * It is possible to create a bidirectional binding between two properties
 * of two Glib::ObjectBase instances, so that if either property changes, the
 * other is updated as well, for instance:
 *
 * @code
 * Glib::Binding::bind_property(object1->property_a(), object2->property_b(),
 *   Glib::BINDING_BIDIRECTIONAL);
 * @endcode
 *
 * will keep the two properties in sync.
 *
 * It is also possible to set a custom transformation function (in both
 * directions, in case of a bidirectional binding) to apply a custom
 * transformation from the source value to the target value before
 * applying it; for instance, the following binding:
 *
 * @code
 * bool celsius_to_fahrenheit(const double& celsius, double& fahrenheit);
 * bool fahrenheit_to_celsius(const double& fahrenheit, double& celsius);
 * Glib::Binding::bind_property(adjustment1->property_value(),
 *   adjustment2->property_value(), Glib::BINDING_BIDIRECTIONAL,
 *   sigc::ptr_fun(celsius_to_fahrenheit), sigc::ptr_fun(fahrenheit_to_celsius));
 * @endcode
 *
 * will keep property_value() of the two adjustments in sync; the
 * celsius_to_fahrenheit() function will be called whenever
 * property_value() of @a adjustment1 changes and will transform the current value
 * of the property before applying it to property_value() of @a adjustment2.
 *
 * Vice versa, the fahrenheit_to_celsius() function will be called whenever
 * property_value() of @a adjustment2 changes, and will transform the
 * current value of the property before applying it to property_value()
 * of @a adjustment1.
 *
 * Note that Glib::Binding does not resolve cycles by itself; a cycle like
 *
 * @code
 *   object1->property_A() -> object2->property_B()
 *   object2->property_B() -> object3->property_C()
 *   object3->property_C() -> object1->property_A()
 * @endcode
 *
 * might lead to an infinite loop. The loop, in this particular case,
 * can be avoided if the objects emit the GObject::notify signal only
 * if the value has effectively been changed. A binding is implemented
 * using the GObject::notify signal, so it is susceptible to all the
 * various ways of blocking a signal emission, like Glib::SignalProxyNormal::emission_stop()
 * or g_signal_handler_block().
 *
 * A binding will be severed, and the resources it allocates freed, whenever
 * either one of the Glib::ObjectBase instances it refers to is deleted,
 * when unbind() is called, or when the Glib::Binding instance loses
 * its last reference.
 *
 * @newin{2,44}
 */

class GLIBMM_API Binding : public Glib::Object
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = Binding;
  using CppClassType = Binding_Class;
  using BaseObjectType = GBinding;
  using BaseClassType = GBindingClass;

  // noncopyable
  Binding(const Binding&) = delete;
  Binding& operator=(const Binding&) = delete;

private:  friend class Binding_Class;
  static CppClassType binding_class_;

protected:
  explicit Binding(const Glib::ConstructParams& construct_params);
  explicit Binding(GBinding* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  Binding(Binding&& src) noexcept;
  Binding& operator=(Binding&& src) noexcept;

  ~Binding() noexcept override;

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GBinding*       gobj()       { return reinterpret_cast<GBinding*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GBinding* gobj() const { return reinterpret_cast<GBinding*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GBinding* gobj_copy();

private:


public:
  /** A slot to be called to transform values in a binding created by
   * bind_property_value().
   *
   * For instance:
   * @code
   *   bool on_transform_to(const GValue* from_value, GValue* to_value);
   * @endcode
   *
   * @return <tt>true</tt> if the transformation was successful, and <tt>false</tt> otherwise.
   */
  using SlotTransform = sigc::slot<bool, const GValue*, GValue*>;

  /** A slot to be called to transform values in a binding created by
   * bind_property().
   *
   * For instance:
   * @code
   *   bool on_transform_to(const Glib::ustring& from_string, int& to_int);
   * @endcode
   *
   * @return <tt>true</tt> if the transformation was successful, and <tt>false</tt> otherwise.
   */
  template <typename T_from, typename T_to>
  using SlotTypedTransform = sigc::slot<bool, const T_from&, T_to&>;

  // GValue* or Glib::ValueBase& in SlotTransform?
  // Binding_transform_callback_common() is simpler and faster with GValue*.
  // No need to copy between GValue and Glib::ValueBase. ValueBase would only
  // be marginally better for users of bind_property_value(). Users would want
  // Value<T_source> and Value<T_target>, meaning that bind_property_value()
  // would have to be a template function. Most users would probably still
  // prefer bind_property(). bind_property_value() is public partly because
  // it's a good place to present documentation common to all the
  // bind_property() overloads.
  // See also https://gitlab.gnome.org/GNOME/glibmm/issues/61
  /** Creates a binding between @a source_property and @a target_property,
   * allowing you to set the transformation functions to be used by the binding.
   *
   * If @a flags contains Glib::BINDING_BIDIRECTIONAL then the binding will be mutual:
   * if @a target_property changes then the @a source_property
   * will be updated as well. The @a transform_from function is only used in case
   * of bidirectional bindings, otherwise it will be ignored.
   *
   * The binding will automatically be removed when either the source or the
   * target instance is deleted. To remove the binding without affecting the
   * source and the target you can call unbind() on the returned Binding instance.
   *
   * A Glib::ObjectBase instance can have multiple bindings.
   *
   * If you supply transformation functions, it is usually easier to use one of the
   * bind_property() overloads, to avoid the use of GValue in the transformation functions.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @param transform_to The transformation function from the source to the target,
   *        or an empty slot to use the default.
   * @param transform_from The transformation function from the target to the source,
   *        or an empty slot to use the default.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @newin{2,44}
   */
  static Glib::RefPtr<Binding> bind_property_value(
    const PropertyProxy_Base& source_property,
    const PropertyProxy_Base& target_property,
    BindingFlags flags = BINDING_DEFAULT,
    const SlotTransform& transform_to = SlotTransform(),
    const SlotTransform& transform_from = SlotTransform());

  
  /** Creates a binding between @a source_property and @a target_property.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @see bind_property_value()
   *
   * @newin{2,44}
   */
  static Glib::RefPtr<Binding> bind_property(
    const PropertyProxy_Base& source_property,
    const PropertyProxy_Base& target_property,
    BindingFlags flags = BINDING_DEFAULT)
  {
    return bind_property_value(source_property, target_property, flags);
  }

  /** Creates a binding between @a source_property and @a target_property,
   * allowing you to set a transformation function to be used by the binding.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @param transform_to The transformation function from the source to the target,
   *        or an empty slot to use the default.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @tparam T_source Type of the source property. Must be a type that can be
   *         stored in a Glib::Value<T_source> object.
   * @tparam T_target Type of the target property. Must be a type that can be
   *         stored in a Glib::Value<T_target> object.
   * @tparam T_functor_to Type of functor that translates from the source to the target.
   *         Must be convertible to SlotTypedTransform<T_source, T_target>.
   *
   * @see bind_property_value()
   *
   * @newin{2,44}
   */
  template <typename T_source, typename T_target, typename T_functor_to>
  static Glib::RefPtr<Binding> bind_property(
    const PropertyProxy<T_source>& source_property,
    const PropertyProxy<T_target>& target_property,
    BindingFlags flags,
    const T_functor_to& transform_to)
  {
    SlotTypedTransform<T_source, T_target> slot_transform_to = transform_to;

    return bind_property_value(source_property, target_property, flags,
      slot_transform_to.empty() ? SlotTransform() : TransformProp<T_source, T_target>(slot_transform_to));
  }

  /** Creates a binding between @a source_property and @a target_property,
   * allowing you to set a transformation function to be used by the binding.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @param transform_to The transformation function from the source to the target,
   *        or an empty slot to use the default.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @tparam T_source Type of the source property. Must be a type that can be
   *         stored in a Glib::Value<T_source> object.
   * @tparam T_target Type of the target property. Must be a type that can be
   *         stored in a Glib::Value<T_target> object.
   * @tparam T_functor_to Type of functor that translates from the source to the target.
   *         Must be convertible to SlotTypedTransform<T_source, T_target>.
   *
   * @see bind_property_value()
   *
   * @newin{2,44}
   */
  template <typename T_source, typename T_target, typename T_functor_to>
  static Glib::RefPtr<Binding> bind_property(
    const PropertyProxy<T_source>& source_property,
    const PropertyProxy_WriteOnly<T_target>& target_property,
    BindingFlags flags,
    const T_functor_to& transform_to)
  {
    SlotTypedTransform<T_source, T_target> slot_transform_to = transform_to;

    return bind_property_value(source_property, target_property, flags,
      slot_transform_to.empty() ? SlotTransform() : TransformProp<T_source, T_target>(slot_transform_to));
  }

  /** Creates a binding between @a source_property and @a target_property,
   * allowing you to set a transformation function to be used by the binding.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @param transform_to The transformation function from the source to the target,
   *        or an empty slot to use the default.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @tparam T_source Type of the source property. Must be a type that can be
   *         stored in a Glib::Value<T_source> object.
   * @tparam T_target Type of the target property. Must be a type that can be
   *         stored in a Glib::Value<T_target> object.
   * @tparam T_functor_to Type of functor that translates from the source to the target.
   *         Must be convertible to SlotTypedTransform<T_source, T_target>.
   *
   * @see bind_property_value()
   *
   * @newin{2,44}
   */
  template <typename T_source, typename T_target, typename T_functor_to>
  static Glib::RefPtr<Binding> bind_property(
    const PropertyProxy_ReadOnly<T_source>& source_property,
    const PropertyProxy<T_target>& target_property,
    BindingFlags flags,
    const T_functor_to& transform_to)
  {
    SlotTypedTransform<T_source, T_target> slot_transform_to = transform_to;

    return bind_property_value(source_property, target_property, flags,
      slot_transform_to.empty() ? SlotTransform() : TransformProp<T_source, T_target>(slot_transform_to));
  }

  /** Creates a binding between @a source_property and @a target_property,
   * allowing you to set a transformation function to be used by the binding.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @param transform_to The transformation function from the source to the target,
   *        or an empty slot to use the default.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @tparam T_source Type of the source property. Must be a type that can be
   *         stored in a Glib::Value<T_source> object.
   * @tparam T_target Type of the target property. Must be a type that can be
   *         stored in a Glib::Value<T_target> object.
   * @tparam T_functor_to Type of functor that translates from the source to the target.
   *         Must be convertible to SlotTypedTransform<T_source, T_target>.
   *
   * @see bind_property_value()
   *
   * @newin{2,44}
   */
  template <typename T_source, typename T_target, typename T_functor_to>
  static Glib::RefPtr<Binding> bind_property(
    const PropertyProxy_ReadOnly<T_source>& source_property,
    const PropertyProxy_WriteOnly<T_target>& target_property,
    BindingFlags flags,
    const T_functor_to& transform_to)
  {
    SlotTypedTransform<T_source, T_target> slot_transform_to = transform_to;

    return bind_property_value(source_property, target_property, flags,
      slot_transform_to.empty() ? SlotTransform() : TransformProp<T_source, T_target>(slot_transform_to));
  }

  /** Creates a binding between @a source_property and @a target_property,
   * allowing you to set the transformation functions to be used by the binding.
   *
   * @param source_property The source property to bind.
   * @param target_property The target property to bind.
   * @param flags Flags to pass to Binding.
   * @param transform_to The transformation function from the source to the target,
   *        or an empty slot to use the default.
   * @param transform_from The transformation function from the target to the source,
   *        or an empty slot to use the default.
   * @return The Binding instance representing the binding between the two
   *         Glib::ObjectBase instances, or <tt>nullptr</tt> in case of error.
   *
   * @tparam T_source Type of the source property. Must be a type that can be
   *         stored in a Glib::Value<T_source> object.
   * @tparam T_target Type of the target property. Must be a type that can be
   *         stored in a Glib::Value<T_target> object.
   * @tparam T_functor_to Type of functor that translates from the source to the target.
   *         Must be convertible to SlotTypedTransform<T_source, T_target>.
   * @tparam T_functor_from Type of functor that translates from the target to the source.
   *         Must be convertible to SlotTypedTransform<T_target, T_source>.
   *
   * @see bind_property_value()
   *
   * @newin{2,44}
   */
  template <typename T_source, typename T_target, typename T_functor_to, typename T_functor_from>
  static Glib::RefPtr<Binding> bind_property(
    const PropertyProxy<T_source>& source_property,
    const PropertyProxy<T_target>& target_property,
    BindingFlags flags,
    const T_functor_to& transform_to,
    const T_functor_from& transform_from)
  {
    SlotTypedTransform<T_source, T_target> slot_transform_to = transform_to;
    SlotTypedTransform<T_target, T_source> slot_transform_from = transform_from;

    return bind_property_value(source_property, target_property, flags,
      slot_transform_to.empty() ? SlotTransform() : TransformProp<T_source, T_target>(slot_transform_to),
      slot_transform_from.empty() ? SlotTransform() : TransformProp<T_target, T_source>(slot_transform_from));
  }

  
  /** Retrieves the Object instance used as the source of the binding.
   * 
   * @newin{2,44}
   * 
   * @return The source Object.
   */
  Glib::RefPtr<Glib::ObjectBase> get_source();
  
  /** Retrieves the Object instance used as the source of the binding.
   * 
   * @newin{2,44}
   * 
   * @return The source Object.
   */
  Glib::RefPtr<const Glib::ObjectBase> get_source() const;
  
  /** Retrieves the name of the property of Binding::property_source() used as the source
   * of the binding.
   * 
   * @newin{2,44}
   * 
   * @return The name of the source property.
   */
  Glib::ustring get_source_property() const;
  
  /** Retrieves the Object instance used as the target of the binding.
   * 
   * @newin{2,44}
   * 
   * @return The target Object.
   */
  Glib::RefPtr<Glib::ObjectBase> get_target();
  
  /** Retrieves the Object instance used as the target of the binding.
   * 
   * @newin{2,44}
   * 
   * @return The target Object.
   */
  Glib::RefPtr<const Glib::ObjectBase> get_target() const;
  
  /** Retrieves the name of the property of Binding::property_target() used as the target
   * of the binding.
   * 
   * @newin{2,44}
   * 
   * @return The name of the target property.
   */
  Glib::ustring get_target_property() const;
  
  /** Retrieves the flags passed when constructing the Binding.
   * 
   * @newin{2,44}
   * 
   * @return The BindingFlags used by the Binding.
   */
  BindingFlags get_flags() const;

  /** Explicitly releases the binding between the source and the target
   * property expressed by this Binding instance.
   *
   * The binding is also released if either the source object or the target
   * object is deleted, or this Binding instance loses its last reference,
   * i.e. there is no more Glib::RefPtr that holds a pointer to it.
   *
   * @newin{2,44}
   */
  void unbind();
  

  /** Flags to be used to control the Binding
   * 
   * @newin{2,44}
   *
   * Default value: BINDING_DEFAULT
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::BindingFlags > property_flags() const;


  /** The Object that should be used as the source of the binding
   * 
   * @newin{2,44}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Glib::ObjectBase> > property_source() const;


  /** The name of the property of Binding::property_source() that should be used
   * as the source of the binding.
   * 
   * This should be in [canonical form][canonical-parameter-names] to get the
   * best performance.
   * 
   * @newin{2,44}
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_source_property() const;


  /** The Object that should be used as the target of the binding
   * 
   * @newin{2,44}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Glib::ObjectBase> > property_target() const;


  /** The name of the property of Binding::property_target() that should be used
   * as the target of the binding.
   * 
   * This should be in [canonical form][canonical-parameter-names] to get the
   * best performance.
   * 
   * @newin{2,44}
   *
   * Default value: ""
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_target_property() const;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /** Decrement the reference count for this object.
   * You should never need to do this manually - use the object via a RefPtr instead.
   */
  void unreference() const override;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:
  // The functor TransformProp can be implicitly converted to a SlotTransform
  // and used in a call to bind_property_value().
  template <typename T_from, typename T_to>
  class TransformProp : public sigc::functor_base
  {
  public:
    using result_type = bool;

    TransformProp(const SlotTypedTransform<T_from, T_to>& slot) : typed_transform(slot) {}

    bool operator()(const GValue* from_value, GValue* to_value)
    {
      Glib::Value<T_from> from_glib_value;
      from_glib_value.init(from_value);
      T_to to{};

      if (!typed_transform(from_glib_value.get(), to))
        return false;

      Glib::Value<T_to> to_glib_value;
      to_glib_value.init(to_value);
      to_glib_value.set(to);
      g_value_copy(to_glib_value.gobj(), to_value);
      return true;
    }

  private:
    SlotTypedTransform<T_from, T_to> typed_transform;
  };


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};

} // namespace Glib


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Glib::Binding
   */
  GLIBMM_API
  Glib::RefPtr<Glib::Binding> wrap(GBinding* object, bool take_copy = false);
}


#endif /* _GLIBMM_BINDING_H */

