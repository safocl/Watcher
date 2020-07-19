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

    op_free(opusFile);
    if ( numReadSamles < 0 )
        throw OpusException( numReadSamles );

    return outWave;
}

}   // namespace core::opusdecoder
