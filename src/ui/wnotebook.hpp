#include <gtkmm/notebook.h>
#include "wfr.hpp"
#include "clockentity.hpp"
#include "timerentity.hpp"
#include "logentity.hpp"

namespace core::ui {

class WNotebook final : public Gtk::Notebook {
    WidgetProvider< AclockContanerFrame > frAcl;
    WidgetProvider< TimerContanerFrame >  frTm;
    WidgetProvider< LoggerContanerFrame > frLog;

public:
    WNotebook();
    ~WNotebook();
    void saveLayout() const;
};

}   // namespace core::ui
