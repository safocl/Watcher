/**
 *@file timer.cpp
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

#include "timer.hpp"
#include "sdlplayer/sdlplayer.hpp"
#include "configure/configure.hpp"

#include <SDL2/SDL_timer.h>

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>

namespace core::utils {
void Timer::start( const std::chrono::seconds &       timerDuration,
                   std::function< void( double ) > && refreshProgress,
                   std::function< void() > &&         doOnEnd,
                   std::function< void() > &&         doAction ) {
    closeThreadFlag = false;
    std::chrono::time_point doneSleepTimePoint {
        timerDuration + std::chrono::high_resolution_clock::now()
    };

    std::thread thrd { [ this,
                         refreshProgress,
                         doOnEnd,
                         doAction,
                         doneSleepTimePoint ] {
        const auto beginTimePoint =
        std::chrono::high_resolution_clock::now();
        const std::chrono::milliseconds fullDiffMs =
        std::chrono::duration_cast< std::chrono::milliseconds >(
        doneSleepTimePoint - beginTimePoint );
        while ( doneSleepTimePoint >=
                std::chrono::high_resolution_clock::now() &&
                closeThreadFlag == false ) {
            std::this_thread::sleep_for( Timer::ticksTime );
            const std::chrono::milliseconds lostMs =
            std::chrono::duration_cast< std::chrono::milliseconds >(
            doneSleepTimePoint -
            std::chrono::high_resolution_clock::now() );
            refreshProgress(
            static_cast< double >( lostMs.count() ) /
            static_cast< double >( fullDiffMs.count() ) );
        }

        doOnEnd();

        auto    t = std::chrono::system_clock::to_time_t(
        std::chrono::high_resolution_clock::now() );
        auto    timeOutput =
        std::put_time( std::localtime( &t ), "%F %T" );

        std::cout.imbue( std::locale( "en_US.utf8" ) );
        std::cout << "Timer stoped at: " << timeOutput << std::endl;

        if ( !closeThreadFlag ) {
            doAction();
        }
    } };
    thrd.detach();
}

void Timer::stop() { closeThreadFlag = true; }

std::chrono::milliseconds Timer::ticksTime { 1 };
}   // namespace core::utils
