module;

#include <glibmm.h>
#include <sigc++/sigc++.h>
#include <gtkmm/enums.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scalebutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/builder.h>
#include <gtkmm/switch.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

export module Gtkmm;

// export namespace Gtk {
// using Gtk::PositionType;
// using Gtk::SpinButton;
// using Gtk::Button;
// using Gtk::Grid;
// using Gtk::Label;
// using Gtk::ProgressBar;
// using Gtk::ScaleButton;
// using Gtk::Entry;
// using Gtk::Builder;
// using Gtk::Switch;
// using Gtk::Window;
// using Gtk::Application;
// }   // namespace Gtk
//
// export namespace sigc {
// using sigc::connection;
// }

export namespace WGtk {
using namespace Gtk;
}   // namespace WGtk
export namespace Wsigc {
using namespace sigc;
}   // namespace Wsigc
export namespace WGlib {
using namespace Glib;
}   // namespace WGlib
