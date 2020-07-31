#include <gtkmm/notebook.h>
#include "wfr.hpp"
#include "clockentity.hpp"
#include "timerentity.hpp"
#include "logentity.hpp"

namespace core::ui {

class WNotebook final : public Gtk::Notebook {
    Wfr< ClockEntity > frAcl;
    Wfr< TimerEntity > frTm;
    Wfr< LogEntity >   frLog;

public:
    WNotebook();
    ~WNotebook();
    void saveLayout() const;
};

}   // namespace core::ui
