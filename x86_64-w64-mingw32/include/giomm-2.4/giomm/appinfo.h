// Generated by gmmproc 2.64.2 -- DO NOT MODIFY!
#ifndef _GIOMM_APPINFO_H
#define _GIOMM_APPINFO_H

#include <giommconfig.h>


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 2007 The gtkmm Development Team
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
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <giomm/applaunchcontext.h>
#include <giomm/asyncresult.h>
#include <giomm/cancellable.h>

#include <exception>

#include <string>

#include <glibmm/interface.h>
#include <glibmm/listhandle.h>
#include <glibmm/arrayhandle.h>
#include <glibmm/object.h>
//#include <giomm/file.h>
#include <giomm/icon.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GAppInfoIface GAppInfoIface;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GAppInfo = struct _GAppInfo;
using GAppInfoClass = struct _GAppInfoClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gio
{ class GIOMM_API AppInfo_Class; } // namespace Gio
#endif // DOXYGEN_SHOULD_SKIP_THIS

namespace Gio
{

/** @addtogroup giommEnums giomm Enums and Flags */

/** 
 *  @var AppInfoCreateFlags APP_INFO_CREATE_NONE
 * No flags.
 * 
 *  @var AppInfoCreateFlags APP_INFO_CREATE_NEEDS_TERMINAL
 * Application opens in a terminal window.
 * 
 *  @var AppInfoCreateFlags APP_INFO_CREATE_SUPPORTS_URIS
 * Application supports URI arguments.
 * 
 *  @var AppInfoCreateFlags APP_INFO_CREATE_SUPPORTS_STARTUP_NOTIFICATION
 * Application supports startup notification. @newin{2,26}
 * 
 *  @enum AppInfoCreateFlags
 * 
 * Flags used when creating a AppInfo.
 *
 * @ingroup giommEnums
 * @par Bitwise operators:
 * <tt>%AppInfoCreateFlags operator|(AppInfoCreateFlags, AppInfoCreateFlags)</tt><br>
 * <tt>%AppInfoCreateFlags operator&(AppInfoCreateFlags, AppInfoCreateFlags)</tt><br>
 * <tt>%AppInfoCreateFlags operator^(AppInfoCreateFlags, AppInfoCreateFlags)</tt><br>
 * <tt>%AppInfoCreateFlags operator~(AppInfoCreateFlags)</tt><br>
 * <tt>%AppInfoCreateFlags& operator|=(AppInfoCreateFlags&, AppInfoCreateFlags)</tt><br>
 * <tt>%AppInfoCreateFlags& operator&=(AppInfoCreateFlags&, AppInfoCreateFlags)</tt><br>
 * <tt>%AppInfoCreateFlags& operator^=(AppInfoCreateFlags&, AppInfoCreateFlags)</tt><br>
 */
enum AppInfoCreateFlags
{
  APP_INFO_CREATE_NONE = 0x0,
  APP_INFO_CREATE_NEEDS_TERMINAL = (1 << 0),
  APP_INFO_CREATE_SUPPORTS_URIS = (1 << 1),
  APP_INFO_CREATE_SUPPORTS_STARTUP_NOTIFICATION = (1 << 2)
};

/** @ingroup giommEnums */
inline AppInfoCreateFlags operator|(AppInfoCreateFlags lhs, AppInfoCreateFlags rhs)
  { return static_cast<AppInfoCreateFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs)); }

/** @ingroup giommEnums */
inline AppInfoCreateFlags operator&(AppInfoCreateFlags lhs, AppInfoCreateFlags rhs)
  { return static_cast<AppInfoCreateFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs)); }

/** @ingroup giommEnums */
inline AppInfoCreateFlags operator^(AppInfoCreateFlags lhs, AppInfoCreateFlags rhs)
  { return static_cast<AppInfoCreateFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs)); }

/** @ingroup giommEnums */
inline AppInfoCreateFlags operator~(AppInfoCreateFlags flags)
  { return static_cast<AppInfoCreateFlags>(~static_cast<unsigned>(flags)); }

/** @ingroup giommEnums */
inline AppInfoCreateFlags& operator|=(AppInfoCreateFlags& lhs, AppInfoCreateFlags rhs)
  { return (lhs = static_cast<AppInfoCreateFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs))); }

/** @ingroup giommEnums */
inline AppInfoCreateFlags& operator&=(AppInfoCreateFlags& lhs, AppInfoCreateFlags rhs)
  { return (lhs = static_cast<AppInfoCreateFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs))); }

/** @ingroup giommEnums */
inline AppInfoCreateFlags& operator^=(AppInfoCreateFlags& lhs, AppInfoCreateFlags rhs)
  { return (lhs = static_cast<AppInfoCreateFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs))); }


class GIOMM_API File;

/** Application information, to describe applications installed on the system,
 * and launch them.
 * See also AppLaunchContext.
 *
 * @newin{2,16}
 */

class GIOMM_API AppInfo : public Glib::Interface
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = AppInfo;
  using CppClassType = AppInfo_Class;
  using BaseObjectType = GAppInfo;
  using BaseClassType = GAppInfoIface;

  // noncopyable
  AppInfo(const AppInfo&) = delete;
  AppInfo& operator=(const AppInfo&) = delete;

private:
  friend class AppInfo_Class;
  static CppClassType appinfo_class_;

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
protected:
  /**
   * You should derive from this class to use it.
   */
  AppInfo();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /** Called by constructors of derived classes. Provide the result of
   * the Class init() function to ensure that it is properly
   * initialized.
   *
   * @param interface_class The Class object for the derived type.
   */
  explicit AppInfo(const Glib::Interface_Class& interface_class);

public:
  // This is public so that C++ wrapper instances can be
  // created for C instances of unwrapped types.
  // For instance, if an unexpected C type implements the C interface.
  explicit AppInfo(GAppInfo* castitem);

protected:
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  AppInfo(AppInfo&& src) noexcept;
  AppInfo& operator=(AppInfo&& src) noexcept;

  ~AppInfo() noexcept override;

  static void add_interface(GType gtype_implementer);

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GAppInfo*       gobj()       { return reinterpret_cast<GAppInfo*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GAppInfo* gobj() const { return reinterpret_cast<GAppInfo*>(gobject_); }

private:


public:
  static Glib::RefPtr<AppInfo> create_from_commandline(const std::string& commandline,
                                                       const std::string& application_name,
                                                       AppInfoCreateFlags flags);

  /**  Creates a duplicate of this AppInfo.
   * @return A duplicate of this AppInfo.
   * @newin{2,36}
   */
  Glib::RefPtr<AppInfo> create_duplicate() const;
  

  // Note that the implementation of equal() is virtual via equal_vfunc().
  
  /** Checks if two AppInfo<!-- -->s are equal.
   * @param other The other AppInfo.
   * @return <tt>true</tt> if @a *this is equal to @a other, <tt>false</tt> otherwise.
   */
  bool equal(const Glib::RefPtr<AppInfo>& other) const;

  
  /** Gets the ID of an application. An id is a string that
   * identifies the application. The exact format of the id is
   * platform dependent. For instance, on Unix this is the
   * desktop file id from the xdg menu specification.
   * 
   * Note that the returned ID may be <tt>nullptr</tt>, depending on how
   * the @a appinfo has been constructed.
   * 
   * @return A string containing the application's ID.
   */
  std::string get_id() const;
  
  /** Gets the installed name of the application.
   * 
   * @return The name of the application for @a appinfo.
   */
  std::string get_name() const;
  
  /** Gets the display name of the application. The display name is often more
   * descriptive to the user than the name itself.
   * 
   * @newin{2,24}
   * 
   * @return The display name of the application for @a appinfo, or the name if
   * no display name is available.
   */
  std::string get_display_name() const;
  
  /** Gets a human-readable description of an installed application.
   * 
   * @return A string containing a description of the 
   * application @a appinfo, or <tt>nullptr</tt> if none.
   */
  std::string get_description() const;
  
  /** Gets the executable's name for the installed application.
   * 
   * @return A string containing the @a appinfo's application
   * binaries name.
   */
  std::string get_executable() const;
  
  /** Gets the commandline with which the application will be
   * started.  
   * 
   * @newin{2,20}
   * 
   * @return A string containing the @a appinfo's commandline,
   * or <tt>nullptr</tt> if this information is not available.
   */
  std::string get_commandline() const;

  
  /** Gets the icon for the application.
   * 
   * @return The default Icon for @a appinfo or <tt>nullptr</tt>
   * if there is no default icon.
   */
  Glib::RefPtr<Icon> get_icon();
  
  /** Gets the icon for the application.
   * 
   * @return The default Icon for @a appinfo or <tt>nullptr</tt>
   * if there is no default icon.
   */
  const Glib::RefPtr<const Icon> get_icon() const;

 
  /** Launches the application. This passes the @a file to the launched application
   * as an argument, using the optional @a context to get information
   * about the details of the launcher (like what screen it is on).
   * On error, an exception will be thrown accordingly.
   *
   * Note that even if the launch is successful the application launched
   * can fail to start if it runs into problems during startup. There is
   * no way to detect this.
   *
   * Some URIs can be changed when passed through a GFile (for instance
   * unsupported uris with strange formats like mailto:), so if you have
   * a textual uri you want to pass in as argument, consider using
   * launch_uris() instead.
   *
   * On UNIX, this function sets the @c GIO_LAUNCHED_DESKTOP_FILE
   * environment variable with the path of the launched desktop file and
   * @c GIO_LAUNCHED_DESKTOP_FILE_PID to the process
   * id of the launched process. This can be used to ignore
   * @c GIO_LAUNCHED_DESKTOP_FILE, should it be inherited
   * by further processes. The @c DISPLAY and
   * @c DESKTOP_STARTUP_ID environment variables are also
   * set, based on information provided in @a context.
   * @param file A File object.
   * @param context An AppLaunchContext.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   *
   * @newin{2,30}
   */
  bool launch(const Glib::RefPtr<Gio::File>& file, const Glib::RefPtr<AppLaunchContext>& context);

  /** Launches the application. This passes the @a file to the launched application
   * as an argument.
   * On error, an exception will be thrown accordingly.
   *
   * Note that even if the launch is successful the application launched
   * can fail to start if it runs into problems during startup. There is
   * no way to detect this.
   *
   * Some URIs can be changed when passed through a GFile (for instance
   * unsupported uris with strange formats like mailto:), so if you have
   * a textual uri you want to pass in as argument, consider using
   * launch_uris() instead.
   *
   * On UNIX, this function sets the @c GIO_LAUNCHED_DESKTOP_FILE
   * environment variable with the path of the launched desktop file and
   * @c GIO_LAUNCHED_DESKTOP_FILE_PID to the process
   * id of the launched process. This can be used to ignore
   * @c GIO_LAUNCHED_DESKTOP_FILE, should it be inherited
   * by further processes. The @c DISPLAY and
   * @c DESKTOP_STARTUP_ID environment variables are also
   * set, based on information provided in @a context.
   * @param file A File object.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   *
   * @newin{2,30}
   */
  bool launch(const Glib::RefPtr<Gio::File>& file);

  
  /** Launches the application. Passes @a files to the launched application
   * as arguments, using the optional @a context to get information
   * about the details of the launcher (like what screen it is on).
   * On error, @a error will be set accordingly.
   * 
   * To launch the application without arguments pass a <tt>nullptr</tt> @a files list.
   * 
   * Note that even if the launch is successful the application launched
   * can fail to start if it runs into problems during startup. There is
   * no way to detect this.
   * 
   * Some URIs can be changed when passed through a GFile (for instance
   * unsupported URIs with strange formats like mailto:), so if you have
   * a textual URI you want to pass in as argument, consider using
   * g_app_info_launch_uris() instead.
   * 
   * The launched application inherits the environment of the launching
   * process, but it can be modified with g_app_launch_context_setenv()
   * and g_app_launch_context_unsetenv().
   * 
   * On UNIX, this function sets the `GIO_LAUNCHED_DESKTOP_FILE`
   * environment variable with the path of the launched desktop file and
   * `GIO_LAUNCHED_DESKTOP_FILE_PID` to the process id of the launched
   * process. This can be used to ignore `GIO_LAUNCHED_DESKTOP_FILE`,
   * should it be inherited by further processes. The `DISPLAY` and
   * `DESKTOP_STARTUP_ID` environment variables are also set, based
   * on information provided in @a context.
   * 
   * @param files A List of File objects.
   * @param context A AppLaunchContext or <tt>nullptr</tt>.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   * 
   * @throws Glib::Error
   */
  bool launch(const std::vector< Glib::RefPtr<Gio::File> >& files, const Glib::RefPtr<AppLaunchContext>& context);

  /// A launch() convenience overload.
  bool launch(const std::vector< Glib::RefPtr<Gio::File> >& files);

  
  /** Checks if the application supports reading files and directories from URIs.
   * 
   * @return <tt>true</tt> if the @a appinfo supports URIs.
   */
  bool supports_uris() const;
  
  /** Checks if the application accepts files as arguments.
   * 
   * @return <tt>true</tt> if the @a appinfo supports files.
   */
  bool supports_files() const;

 
#ifndef GIOMM_DISABLE_DEPRECATED

  /** Launches the application. This passes the @a uris to the launched application
   * as arguments, using the optional @a context to get information
   * about the details of the launcher (like what screen it is on).
   * On error, @a error will be set accordingly.
   * 
   * To launch the application without arguments pass a <tt>nullptr</tt> @a uris list.
   * 
   * Note that even if the launch is successful the application launched
   * can fail to start if it runs into problems during startup. There is
   * no way to detect this.
   * 
   * @deprecated Use the method that takes an AppLaunchContext
   * 
   * @param uris A List containing URIs to launch.
   * @param context A AppLaunchContext or <tt>nullptr</tt>.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   * 
   * @throws Glib::Error
   */
  bool launch_uris(const Glib::ListHandle<std::string>& uris, GAppLaunchContext* context);
#endif // GIOMM_DISABLE_DEPRECATED


  //TODO: I think we use Glib::ustring elsewhere for URIs:
  // 2019-03-18 kjellahl: Glibmm is inconsistent; Glib::ustring in convert.hg,
  // std::string in uriutils.hg.
  // The reporter of libxml++ bug https://bugzilla.gnome.org/show_bug.cgi?id=790034
  // proposes std::string.
 

  /** Launches the application. This passes the @a uris to the launched application
   * as arguments, using the optional @a context to get information
   * about the details of the launcher (like what screen it is on).
   * On error, @a error will be set accordingly.
   * 
   * To launch the application without arguments pass a <tt>nullptr</tt> @a uris list.
   * 
   * Note that even if the launch is successful the application launched
   * can fail to start if it runs into problems during startup. There is
   * no way to detect this.
   * 
   * @param uris A List containing URIs to launch.
   * @param context A AppLaunchContext or <tt>nullptr</tt>.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   * 
   * @throws Glib::Error
   */
  bool launch_uris(const Glib::ListHandle<std::string>& uris, const Glib::RefPtr<AppLaunchContext>& context);

  /// A launch_uris() convenience overload.
  bool launch_uris(const Glib::ListHandle<std::string>& uris);

  /** Launches the application. This passes the @a uri to the launched application
   * as an arguments, using the optional @a context to get information
   * about the details of the launcher (like what screen it is on).
   * On error, an exception will be thrown accordingly.
   *
   * Note that even if the launch is successful the application launched
   * can fail to start if it runs into problems during startup. There is
   * no way to detect this.
   * @param uri A URI to launch.
   * @param context An AppLaunchContext.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   *
   * @newin{2,30}
   */
  bool launch_uri(const std::string& uri, const Glib::RefPtr<AppLaunchContext>& context);

  /** A launch_uri() convenience overload.
   *
   * @newin{2,30}
   */
  bool launch_uri(const std::string& uris);

  
  /** Async version of g_app_info_launch_uris().
   * 
   * The @a slot is invoked immediately after the application launch, but it
   * waits for activation in case of D-Bus–activated applications and also provides
   * extended error information for sandboxed applications, see notes for
   * g_app_info_launch_default_for_uri_async().
   * 
   * @newin{2,60}
   * 
   * @param uris A List containing URIs to launch.
   * @param context A AppLaunchContext or <tt>nullptr</tt>.
   * @param cancellable A Cancellable.
   * @param slot A SlotAsyncReady to call when the request is done.
   */
  void launch_uris_async(const std::vector<std::string>& uris, const Glib::RefPtr<AppLaunchContext>& context, const SlotAsyncReady& slot, const Glib::RefPtr<Cancellable>& cancellable =  {});

  /// A launch_uris_async() convenience overload.
  void launch_uris_async(const std::vector<std::string>& uris, const Glib::RefPtr<AppLaunchContext>& context, const Glib::RefPtr<Cancellable>& cancellable =  {});
  
  /** Finishes a g_app_info_launch_uris_async() operation.
   * 
   * @newin{2,60}
   * 
   * @param result A AsyncResult.
   * @return <tt>true</tt> on successful launch, <tt>false</tt> otherwise.
   * 
   * @throws Glib::Error
   */
  bool launch_uris_finish(const Glib::RefPtr<AsyncResult>& result);

  
  /** Checks if the application info should be shown in menus that 
   * list available applications.
   * 
   * @return <tt>true</tt> if the @a appinfo should be shown, <tt>false</tt> otherwise.
   */
  bool should_show() const;
  // FIXME: use better terminology than delete/do_delete
  
  /** Obtains the information whether the AppInfo can be deleted.
   * See g_app_info_delete().
   * 
   * @newin{2,20}
   * 
   * @return <tt>true</tt> if @a appinfo can be deleted.
   */
  bool can_delete() const;
  
  /** Tries to delete a AppInfo.
   * 
   * On some platforms, there may be a difference between user-defined
   * AppInfos which can be deleted, and system-wide ones which cannot.
   * See g_app_info_can_delete().
   * 
   * Virtual: do_delete
   * @newin{2,20}
   * 
   * @return <tt>true</tt> if @a appinfo has been deleted.
   */
  bool do_delete();

  
  /** Sets the application as the default handler for a given type.
   * 
   * @param content_type The content type.
   * @return <tt>true</tt> on success, <tt>false</tt> on error.
   * 
   * @throws Glib::Error
   */
  bool set_as_default_for_type(const std::string& content_type);
  
  /** Sets the application as the default handler for the given file extension.
   * 
   * @param extension A string containing the file extension
   * (without the dot).
   * @return <tt>true</tt> on success, <tt>false</tt> on error.
   * 
   * @throws Glib::Error
   */
  bool set_as_default_for_extension(const std::string& extension);
  
  /** Adds a content type to the application information to indicate the 
   * application is capable of opening files with the given content type.
   * 
   * @param content_type A string.
   * @return <tt>true</tt> on success, <tt>false</tt> on error.
   * 
   * @throws Glib::Error
   */
  bool add_supports_type(const std::string& content_type);
  
  /** Checks if a supported content type can be removed from an application.
   * 
   * @return <tt>true</tt> if it is possible to remove supported 
   * content types from a given @a appinfo, <tt>false</tt> if not.
   */
  bool can_remove_supports_type() const;
  
  /** Removes a supported type from an application, if possible.
   * 
   * @param content_type A string.
   * @return <tt>true</tt> on success, <tt>false</tt> on error.
   * 
   * @throws Glib::Error
   */
  bool remove_supports_type(const std::string& content_type);

 
  /** Retrieves the list of content types that @a app_info claims to support.
   * If this information is not provided by the environment, this function
   * will return <tt>nullptr</tt>.
   * This function does not take in consideration associations added with
   * g_app_info_add_supports_type(), but only those exported directly by
   * the application.
   * 
   * @newin{2,34}
   * 
   * @return A list of content types.
   */
  Glib::StringArrayHandle get_supported_types() const;

  
  /** Sets the application as the last used application for a given type.
   * This will make the application appear as first in the list returned
   * by g_app_info_get_recommended_for_type(), regardless of the default
   * application for that content type.
   * 
   * @param content_type The content type.
   * @return <tt>true</tt> on success, <tt>false</tt> on error.
   * 
   * @throws Glib::Error
   */
  bool set_as_last_used_for_type(const std::string& content_type);

 
  /** Gets a list of all of the applications currently registered
   * on this system.
   * 
   * For desktop files, this includes applications that have
   * `NoDisplay=true` set or are excluded from display by means
   * of `OnlyShowIn` or `NotShowIn`. See g_app_info_should_show().
   * The returned list does not include applications which have
   * the `Hidden` key set.
   * 
   * @return A newly allocated List of references to AppInfos.
   */
  static Glib::ListHandle<Glib::RefPtr<AppInfo> > get_all();

  
  /** Gets a list of all AppInfos for a given content type,
   * including the recommended and fallback AppInfos. See
   * g_app_info_get_recommended_for_type() and
   * g_app_info_get_fallback_for_type().
   * 
   * @param content_type The content type to find a AppInfo for.
   * @return List of AppInfos
   * for given @a content_type or <tt>nullptr</tt> on error.
   */
  static Glib::ListHandle<Glib::RefPtr<AppInfo> > get_all_for_type(const std::string& content_type);
  
  /** Gets the default AppInfo for a given content type.
   * 
   * @param content_type The content type to find a AppInfo for.
   * @param must_support_uris If <tt>true</tt>, the AppInfo is expected to
   * support URIs.
   * @return AppInfo for given @a content_type or
   * <tt>nullptr</tt> on error.
   */
  static Glib::RefPtr<AppInfo> get_default_for_type(const std::string& content_type, bool must_support_uris =  true);
  
  /** Gets the default application for handling URIs with
   * the given URI scheme. A URI scheme is the initial part
   * of the URI, up to but not including the ':', e.g. "http",
   * "ftp" or "sip".
   * 
   * @param uri_scheme A string containing a URI scheme.
   * @return AppInfo for given @a uri_scheme or <tt>nullptr</tt> on error.
   */
  static Glib::RefPtr<AppInfo> get_default_for_uri_scheme(const std::string& uri_scheme);
  
  /** Removes all changes to the type associations done by
   * g_app_info_set_as_default_for_type(),
   * g_app_info_set_as_default_for_extension(),
   * g_app_info_add_supports_type() or
   * g_app_info_remove_supports_type().
   * 
   * @newin{2,20}
   * 
   * @param content_type A content type.
   */
  static void reset_type_associations(const std::string& content_type);
  
  /** Utility function that launches the default application
   * registered to handle the specified uri. Synchronous I/O
   * is done on the uri to detect the type of the file if
   * required.
   * 
   * The D-Bus–activated applications don't have to be started if your application
   * terminates too soon after this function. To prevent this, use
   * g_app_info_launch_default_for_uri_async() instead.
   * 
   * @param uri The uri to show.
   * @param context An optional AppLaunchContext.
   * @return <tt>true</tt> on success, <tt>false</tt> on error.
   * 
   * @throws Glib::Error
   */
  static bool launch_default_for_uri(const std::string& uri, const Glib::RefPtr<AppLaunchContext>& context);

  /// A launch_default_for_uri() convenience overload.
  static bool launch_default_for_uri(const std::string& uri);

  
  /** Async version of g_app_info_launch_default_for_uri().
   * 
   * This version is useful if you are interested in receiving
   * error information in the case where the application is
   * sandboxed and the portal may present an application chooser
   * dialog to the user.
   * 
   * This is also useful if you want to be sure that the D-Bus–activated
   * applications are really started before termination and if you are interested
   * in receiving error information from their activation.
   * 
   * @newin{2,50}
   * 
   * @param uri The uri to show.
   * @param context An optional AppLaunchContext.
   * @param cancellable A Cancellable.
   * @param slot A SlotAsyncReady to call when the request is done.
   */
  static void launch_default_for_uri_async(const std::string& uri, const Glib::RefPtr<AppLaunchContext>& context, const SlotAsyncReady& slot, const Glib::RefPtr<Cancellable>& cancellable);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri, const Glib::RefPtr<AppLaunchContext>& context, const SlotAsyncReady& slot);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri, const Glib::RefPtr<AppLaunchContext>& context, const Glib::RefPtr<Cancellable>& cancellable);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri, const Glib::RefPtr<AppLaunchContext>& context);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri, const SlotAsyncReady& slot, const Glib::RefPtr<Cancellable>& cancellable);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri, const SlotAsyncReady& slot);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri, const Glib::RefPtr<Cancellable>& cancellable);

  /// A launch_default_for_uri_async() convenience overload.
  static void launch_default_for_uri_async(const std::string& uri);
  
  
  /** Finishes an asynchronous launch-default-for-uri operation.
   * 
   * @newin{2,50}
   * 
   * @param result A AsyncResult.
   * @return <tt>true</tt> if the launch was successful, <tt>false</tt> if @a error is set.
   * 
   * @throws Glib::Error
   */
  static bool launch_default_for_uri_finish(const Glib::RefPtr<AsyncResult>& result);

protected:
  //_WRAP_VFUNC(Glib::RefPtr<AppInfo> dup(), "dup")
  //_WRAP_VFUNC(bool equal(const Glib::RefPtr<AppInfo>& appinfo2), "equal")
  //_WRAP_VFUNC(std::string get_id() const, "get_id")
  //_WRAP_VFUNC(std::string get_name() const, "get_name")
  //_WRAP_VFUNC(std::string get_description() const, "get_description")
  //_WRAP_VFUNC(std::string get_executable() const, "get_executable")
  //_WRAP_VFUNC(Glib::RefPtr<Icon> get_icon() const, "get_icon")
//#m4 __CONVERSION(`const Glib::ListHandle<std::string>&',`GList*',`$3.data()')
//#m4 __CONVERSION(`GList*',`const Glib::ListHandle<std::string>&',`Glib::ListHandle<std::string>($3, Glib::OWNERSHIP_NONE)')
  //_WRAP_VFUNC(bool launch(const std::vector<Gio::File>& filenames, const Glib::RefPtr<AppLaunchContext>& context, GError** error), "launch")
  //_WRAP_VFUNC(bool supports_uris() const, "supports_uris")
  //_WRAP_VFUNC(bool supports_files() const, "supports_files")
  //_WRAP_VFUNC(bool launch_uris(const Glib::ListHandle<std::string>& uris, const Glib::RefPtr<AppLaunchContext>& context, GError** error), "launch_uris")
  //_WRAP_VFUNC(bool should_show() const, "should_show")
  //_WRAP_VFUNC(bool set_as_default_for_type(const std::string& content_type, GError** error), "set_as_default_for_type")
  //_WRAP_VFUNC(bool set_as_default_for_extension(const std::string& extension, GError** error), "set_as_default_for_extension")
  //_WRAP_VFUNC(bool add_supports_type(const std::string& content_type, GError** error), "add_supports_type")
  //_WRAP_VFUNC(bool can_remove_supports_type() const, "can_remove_supports_type")
  //_WRAP_VFUNC(bool remove_supports_type(const std::string& content_type, GError** error), "remove_supports_type")


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};

} // namespace Gio


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gio::AppInfo
   */
  GIOMM_API
  Glib::RefPtr<Gio::AppInfo> wrap(GAppInfo* object, bool take_copy = false);

} // namespace Glib


#endif /* _GIOMM_APPINFO_H */

