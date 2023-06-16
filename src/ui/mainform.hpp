#pragma once

#include "entityManager.hpp"
#include "glibmm/refptr.h"
#include "gtkmm/builder.h"

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>
#include <gtkmm/grid.h>

namespace core::ui {

class MainWindow final : public Gtk::Window {
    Glib::RefPtr< Gtk::Builder > mMainWindowBuilder;

    Glib::RefPtr< Gtk::Application > mApp;

    entity::Manager mEntityManager;

public:
    MainWindow( Glib::RefPtr< Gtk::Application > );
    ~MainWindow();
};

}   // namespace core::ui
