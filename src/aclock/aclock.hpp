#pragma once

#include <atomic>
#include <chrono>
#include <ctime>
#include <functional>
#include <memory>

class Aclock final {
    std::atomic_bool                       offFlag_ { false };
    static const std::chrono::milliseconds tick_;

public:
    void on( const int                          hour,
             const int                          minute,
             const int                          sec,
             std::function< void( double ) > && refreshProgress,
             std::function< void() > &&         doOnEnd,
             std::function< void() > &&         doAction );

    void off();
};
