#include <iostream>
#include <chrono>
#include <cstdlib>
#include "timer/timer.hpp"
#include "loger/loger.hpp"


int main() {
    constexpr int sec = 5;

    std::chrono::seconds timeToStop { sec };

    Timer timer {};
    timer.start( timeToStop );
    
    Loger loger1{"sleep"};
    loger1.log();

}
