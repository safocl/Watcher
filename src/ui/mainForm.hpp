#include "wnotebook/wnotebook.hpp"
#include <gtkmm/window.h>

namespace core::mForm {

class MainWindow final : public Gtk::Window {
    core::ui::WNotebook nb;
    core::ui::WFrAclock frmAc;
    core::ui::WFrTm     frmTm;
    core::ui::WFrLog    frmLog;

public:
    MainWindow();
    ~MainWindow();
};

}   // namespace core::mForm
