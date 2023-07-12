/**
 *@file opusdecoder.cpp
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
#include <filesystem>
#include <iostream>
#include <opus/opusfile.h>
#include "opusdecoder.hpp"
#include <cstddef>
#include <memory>
#include <opus/opus.h>
#include <opus/opus_types.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace core::opusdecoder {

OpusException::OpusException( int errCode ) : err( errCode ) {}
OpusException::~OpusException() = default;

const char * OpusException::what() const noexcept {
    switch ( err ) {
    case static_cast< int >( OpusErr::ALLOC_FAIL ):
        return "Memory allocation has failed.";
    case static_cast< int >( OpusErr::BAD_ARG ):
        return "One or more invalid/out of range arguments.";
    case static_cast< int >( OpusErr::BUFFER_TOO_SMALL ):
        return "Not enough bytes allocated in the buffer";
    case static_cast< int >( OpusErr::INTERNAL_ERROR ):
        return "An internal error was detected.";
    case static_cast< int >( OpusErr::INVALID_PACKET ):
        return "The compressed data passed is corrupted.";
    case static_cast< int >( OpusErr::INVALID_STATE ):
        return "An encoder or decoder structure is invalid or already freed";
    case static_cast< int >( OpusErr::UNIMPLEMENTED ):
        return "Invalid/unsupported request number.";
    default: return "unknown exception";
    }
}

WOpusDecoder::WOpusDecoder()  = default;
WOpusDecoder::~WOpusDecoder() = default;

std::vector< opus_int16 >
WOpusDecoder::decode( std::filesystem::path fileName ) {
    if ( !std::filesystem::exists( fileName ) )
        throw std::runtime_error( "file not exist" );

    int  err { 0 };
    auto opusFile = op_open_file( fileName.c_str(), &err );

    if ( err < 0 )
        throw OpusException( err );

    std::array< opus_int16, bufferSize > outBuffer {};
    int                                  numReadSamles { 1 };

    do {
        numReadSamles =
        op_read( opusFile, outBuffer.data(), bufferSize, nullptr );

        std::cout << numReadSamles << std::endl;
        auto endDataIt = outBuffer.begin();
        endDataIt += numReadSamles;
        outWave.insert( outWave.end(), outBuffer.begin(), endDataIt );

    } while ( numReadSamles > 0 );

    op_free( opusFile );
    if ( numReadSamles < 0 )
        throw OpusException( numReadSamles );

    return outWave;
}

}   // namespace core::opusdecoder
