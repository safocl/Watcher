#pragma once

#include "clockentity.hpp"
#include "timerentity.hpp"
#include "logentity.hpp"

#include <list>

namespace core::ui::entity {

class Manager {
public:
    struct DynamicEntitiesLayouts {
        Gtk::Grid * clock;
        Gtk::Grid * timer;
        Gtk::Grid * log;
    };

private:
    struct DynamicElements {
        std::list< Clock > clocks;
        std::list< Timer > timers;
        std::list< Log >   logs;
    };

    DynamicElements        mElements;
    DynamicEntitiesLayouts mEntitiesLayouts;

public:
    Manager();
    Manager( DynamicEntitiesLayouts );
    ~Manager();

    void setDynamicEntitiesLayouts( DynamicEntitiesLayouts );

    void pushAcloack();
    void pushTimer();
    void pushLogger();

    void loadFromConfig();
    void saveToConfig();
};

};   // namespace core::ui::entity
