/**
 *@file entityManager.cpp
 *@copyright GPL-3.0-or-later
 *@author safocl (megaSafocl)
 *@date 2023
 *
 * @detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of PockerCalc2.

 PockerCalc2 is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 PockerCalc2 is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 PockerCalc2. If not, see <https://www.gnu.org/licenses/>.
 */

#include "entityManager.hpp"
#include "configure/configure.hpp"
#include "ui/clockentity.hpp"
#include <algorithm>

namespace core::ui::entity {

Manager::Manager() {}

Manager::Manager( DynamicEntitiesLayouts layouts ) :
mEntitiesLayouts( std::move( layouts ) ) {
    loadFromConfig();
}

Manager::~Manager() {}

void Manager::setDynamicEntitiesLayouts(
DynamicEntitiesLayouts layouts ) {
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

void Manager::loadFromConfig() {
    auto conf = configure::Configure::init()->getParams();

    for ( auto logElement : conf.logs ) {
        mElements.logs.emplace_back( *mEntitiesLayouts.log,
                                     logElement );
        auto log = std::prev( mElements.logs.end() );

        log->mDestroyBtn->signal_clicked().connect(
        [ this, log ]() { mElements.logs.erase( log ); } );
    }
    for ( auto timerElement : conf.timers ) {
        auto [ h, m, s, v ] = timerElement;
        mElements.timers.emplace_back(
        *mEntitiesLayouts.timer, h, m, s, v );

        auto timer = std::prev( mElements.timers.end() );

        timer->mDestroyBtn->signal_clicked().connect(
        [ this, timer ]() { mElements.timers.erase( timer ); } );
    }

    for ( auto clockElement : conf.aclocks ) {
        auto [ h, m, s, v ] = clockElement;
        mElements.clocks.emplace_back(
        *mEntitiesLayouts.clock, h, m, s, v );

        auto clock = std::prev( mElements.clocks.end() );

        clock->mDestroyBtn->signal_clicked().connect(
        [ this, clock ]() { mElements.clocks.erase( clock ); } );
    }
}

void Manager::saveToConfig() {
    configure::LoggerNodeJson logs;
    for ( auto & log : mElements.logs )
        logs.push_back( log.getValues() );

    configure::TimerNodeJson timers;
    for ( auto & timer : mElements.timers )
        timers.push_back( timer.getValues() );

    configure::TimerNodeJson clocks;
    for ( auto & clock : mElements.clocks )
        clocks.push_back( clock.getValues() );

    auto conf         = configure::Configure::init();
    auto paramsToSave = conf->getParams();

    paramsToSave.logs.swap( logs );
    paramsToSave.timers.swap( timers );
    paramsToSave.aclocks.swap( clocks );

    conf->import( paramsToSave );
}

}   // namespace core::ui::entity
