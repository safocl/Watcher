#include <iostream>
#include <chrono>
#include <cstdlib>
#include "aclock/aclock.hpp"
#include "timer/timer.hpp"
#include "loger/loger.hpp"
#include <gtkmm/application.h>
#include <gtkmm/frame.h>
#include <gtkmm/window.h>
#include <gtkmm/notebook.h>
#include "ui/wnotebook/wnotebook.hpp"

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  Gtk::Window window;
  window.set_default_size(400, 400);

  WNotebook nb1{};
  window.add(nb1);
  nb1.show_all();

  return app->run(window);
}
