#include "logentity.hpp"
#include <functional>

namespace core::ui {

LogEntity::LogEntity() : entry {}, btn { btnLabel }, loger{} {
    entry.set_placeholder_text( "Write text" );

    entry.set_hexpand();

    attach( entry, 1, 1 );
    attach( btn, 2, 1 );

    show_all();

    btn.signal_clicked().connect(sigc::mem_fun(*this, &LogEntity::onButtonClicked));
            
}
LogEntity::~LogEntity() {}


void LogEntity::onButtonClicked(){

    loger.log(entry.get_text());


}

}   // namespace core::ui
