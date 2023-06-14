#include "entityManager.hpp"
#include "ui/clockentity.hpp"
#include <algorithm>

namespace core::ui::entity {

Manager::Manager() {}

Manager::Manager( DynamicEntitiesLayouts layouts ) :
mEntitiesLayouts( std::move( layouts ) ) {}

Manager::~Manager() {}

void Manager::setDynamicEntitiesLayouts( DynamicEntitiesLayouts layouts ) {
    mEntitiesLayouts = std::move( layouts );
}

void Manager::pushAcloack() {
    mElements.clocks.emplace_back( *mEntitiesLayouts.clock );

    auto clock = std::prev( mElements.clocks.end() );

    clock->mDestroyBtn->signal_clicked().connect(
    [ this, clock ]() { mElements.clocks.erase( clock ); } );
}

void Manager::pushTimer() {
    mElements.timers.emplace_back( *mEntitiesLayouts.timer );

    auto timer = std::prev( mElements.timers.end() );

    timer->mDestroyBtn->signal_clicked().connect(
    [ this, timer ]() { mElements.timers.erase( timer ); } );
}

void Manager::pushLogger() {
    mElements.logs.emplace_back( *mEntitiesLayouts.log );

    auto log = std::prev( mElements.logs.end() );

    log->mDestroyBtn->signal_clicked().connect(
    [ this, log ]() { mElements.logs.erase( log ); } );
}

void Manager::loadFromConfig() {}

void Manager::saveToConfig() {}

}   // namespace core::ui::entity
