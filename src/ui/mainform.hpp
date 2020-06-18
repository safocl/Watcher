#pragma once


#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include "gtkmm/application.h"
#include "gtkmm/grid.h"
#include "wnotebook.hpp"

namespace core::mForm {

class MainWindow final : public Gtk::Window {

    ui::WNotebook nb;
    Gtk::Button btnClose;
    Gtk::Grid grid;

    Gtk::Application * app;

    void onBtnCloseClicked();


public:
    MainWindow(Gtk::Application *);
    ~MainWindow();
};

}   // namespace core::mForm
