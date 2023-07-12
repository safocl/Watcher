/**
 *@file timer.hpp
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

#pragma once

#include <chrono>
#include <functional>
#include <mutex>
#include <ratio>
#include <type_traits>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <atomic>

namespace core::utils {
class Timer final {
    std::atomic_bool closeThreadFlag { false };

public:
    void start( const std::chrono::seconds &       timerDuration,
                std::function< void( double ) > && refreshProgress,
                std::function< void() > &&         doOnEnd,
                std::function< void() > &&         doAction );
    void stop();

    static std::chrono::milliseconds ticksTime;
};
//std::chrono::milliseconds Timer::ticksTime{1};
}   // namespace core::utils
