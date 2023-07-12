/**
 *@file opusdecoder.hpp
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

#include <cstdint>
#include <exception>
#include <filesystem>
#include <istream>
#include <memory>
#include <opus/opus_defines.h>
#include <opus/opus_types.h>
#include <ostream>
#include <string_view>
#include <vector>

namespace core::opusdecoder {

enum class SampleRate : opus_int32 {
    SR_8000  = 8000,
    SR_12000 = 12000,
    SR_16000 = 16000,
    SR_24000 = 24000,
    SR_48000 = 48000

};

enum class OpusErr {
    OK               = OPUS_OK,
    BAD_ARG          = OPUS_BAD_ARG,
    BUFFER_TOO_SMALL = OPUS_BUFFER_TOO_SMALL,
    INTERNAL_ERROR   = OPUS_INTERNAL_ERROR,
    INVALID_PACKET   = OPUS_INVALID_PACKET,
    UNIMPLEMENTED    = OPUS_UNIMPLEMENTED,
    INVALID_STATE    = OPUS_INVALID_STATE,
    ALLOC_FAIL       = OPUS_ALLOC_FAIL
};

enum class Fec { OFF = 0, ON = 1 };

/* TODO
 * template <class T>
 * struct OpusAllocator final {};
 * */

class OpusException final : public std::exception {
    int err;

public:
    OpusException( int errCode );
    ~OpusException();
    const char * what() const noexcept override;
};

class WOpusDecoder final {
    std::vector< opus_int16 > outWave;

public:
    static constexpr int bufferSize { 5760 };

    WOpusDecoder();
    ~WOpusDecoder();
    [[nodiscard]] std::vector< opus_int16 >
    decode( std::filesystem::path fileName );
};

}   // namespace core::opusdecoder
