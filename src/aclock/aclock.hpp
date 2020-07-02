#pragma once

#include <atomic>
#include <chrono>
#include <ctime>
#include <memory>

namespace core::ui {
class ClockEntity;
}

class Aclock {
    std::atomic_bool                       offFlag_ { false };
    static const std::chrono::milliseconds tick_;

public:
    void on( const int               hour,
             const int               minute,
             const int               sec,
             core::ui::ClockEntity & obj );

    void off();
};
