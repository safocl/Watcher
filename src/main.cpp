#include <iostream>
#include <chrono>
#include <cstdlib>
#include "aclock/aclock.hpp"
#include "timer/timer.hpp"
#include "loger/loger.hpp"

int main() {
    constexpr int sec = 5;

    std::chrono::seconds timeToStop { sec };

    Timer timer {};
    timer.start( timeToStop );

    Loger loger1 { "unsleep" };
    loger1.log();

    Aclock ac {};
    ac.on( 2020, 5, 6, 16, 24, 0 );

    return 0;
}
