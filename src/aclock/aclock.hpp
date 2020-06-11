#include <ctime>
#include <memory>

class Aclock {
    std::unique_ptr< std::tm > aTime { nullptr };

public:
    void on( int year,
             int month,
             int mday,
             int hour,
             int minute,
             int sec );
};

std::tm tmFill( int year,
                int month,
                int mday,
                int hour,
                int minute,
                int sec );
