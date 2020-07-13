// Generated by gmmproc 2.56.0 -- DO NOT MODIFY!
#ifndef _ATKMM_TABLE_P_H
#define _ATKMM_TABLE_P_H


#include <atk/atkobject.h>

#include <glibmm/private/interface_p.h>

namespace Atk
{

class Table_Class : public Glib::Interface_Class
{
public:
  using CppObjectType = Table;
  using BaseObjectType = AtkTable;
  using BaseClassType = AtkTableIface;
  using CppClassParent = Glib::Interface_Class;

  friend class Table;

  const Glib::Interface_Class& init();

  static void iface_init_function(void* g_iface, void* iface_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.
  static void row_inserted_callback(AtkTable* self, gint p0, gint p1);
  static void column_inserted_callback(AtkTable* self, gint p0, gint p1);
  static void row_deleted_callback(AtkTable* self, gint p0, gint p1);
  static void column_deleted_callback(AtkTable* self, gint p0, gint p1);
  static void row_reordered_callback(AtkTable* self);
  static void column_reordered_callback(AtkTable* self);
  static void model_changed_callback(AtkTable* self);

  //Callbacks (virtual functions):
  static AtkObject* ref_at_vfunc_callback(AtkTable* self, gint row, gint column);
  static gint get_index_at_vfunc_callback(AtkTable* self, gint row, gint column);
  static gint get_column_at_index_vfunc_callback(AtkTable* self, gint index_);
  static gint get_row_at_index_vfunc_callback(AtkTable* self, gint index_);
  static gint get_n_columns_vfunc_callback(AtkTable* self);
  static gint get_n_rows_vfunc_callback(AtkTable* self);
  static gint get_column_extent_at_vfunc_callback(AtkTable* self, gint row, gint column);
  static gint get_row_extent_at_vfunc_callback(AtkTable* self, gint row, gint column);
  static AtkObject* get_caption_vfunc_callback(AtkTable* self);
  static const gchar* get_column_description_vfunc_callback(AtkTable* self, gint column);
  static AtkObject* get_column_header_vfunc_callback(AtkTable* self, gint column);
  static const gchar* get_row_description_vfunc_callback(AtkTable* self, gint row);
  static AtkObject* get_row_header_vfunc_callback(AtkTable* self, gint row);
  static AtkObject* get_summary_vfunc_callback(AtkTable* self);
  static void set_caption_vfunc_callback(AtkTable* self, AtkObject* caption);
  static void set_column_description_vfunc_callback(AtkTable* self, gint column, const gchar* description);
  static void set_column_header_vfunc_callback(AtkTable* self, gint column, AtkObject* header);
  static void set_row_description_vfunc_callback(AtkTable* self, gint row, const gchar* description);
  static void set_row_header_vfunc_callback(AtkTable* self, gint row, AtkObject* header);
  static void set_summary_vfunc_callback(AtkTable* self, AtkObject* accessible);
  static gboolean is_column_selected_vfunc_callback(AtkTable* self, gint column);
  static gboolean is_row_selected_vfunc_callback(AtkTable* self, gint row);
  static gboolean is_selected_vfunc_callback(AtkTable* self, gint row, gint column);
  static gboolean add_row_selection_vfunc_callback(AtkTable* self, gint row);
  static gboolean remove_row_selection_vfunc_callback(AtkTable* self, gint row);
  static gboolean add_column_selection_vfunc_callback(AtkTable* self, gint column);
  static gboolean remove_column_selection_vfunc_callback(AtkTable* self, gint column);
  static gint get_selected_columns_vfunc_callback(AtkTable* self, gint** selected);
  static gint get_selected_rows_vfunc_callback(AtkTable* self, gint** selected);
};


} // namespace Atk


#endif /* _ATKMM_TABLE_P_H */

