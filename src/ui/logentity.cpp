#include "logentity.hpp"


namespace core::ui {


LogEntity::LogEntity() : entry{}, btn{btnLabel} {

entry.set_placeholder_text("Write text");

entry.set_hexpand();

attach(entry, 1, 1);
    attach(btn, 2,1);
    

    show_all();
    
}
LogEntity::~LogEntity(){}


}
