#include <gtkmm/frame.h>
#include <gtkmm/notebook.h>
#include <memory>
#include <glibmm/ustring.h>



class WNotebook : public Gtk::Notebook {
    const Glib::UStringView tabLabel1{"Alarm clock"};
    const Glib::UStringView tabLabel2{"Timer"};
    const Glib::UStringView tabLabel3{"Logger"};

    std::unique_ptr <Gtk::Frame> frm1 = std::make_unique< Gtk::Frame >(tabLabel1.c_str());
    std::unique_ptr <Gtk::Frame> frm2 = std::make_unique< Gtk::Frame >(tabLabel2.c_str());
    std::unique_ptr <Gtk::Frame> frm3 = std::make_unique< Gtk::Frame >(tabLabel3.c_str());

    public:
    WNotebook();
    virtual ~WNotebook();
};
