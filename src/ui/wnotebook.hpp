#include <gtkmm/notebook.h>
#include "wfraclock.hpp"
#include "wfrtm.hpp"
#include "wfrlog.hpp"

namespace core::ui {

class WNotebook final : public Gtk::Notebook {
    WFrAclock frAcl;
    WFrTm     frTm;
    WFrLog    frLog;

public:
    WNotebook();
    ~WNotebook();
};

}   // namespace core::ui
