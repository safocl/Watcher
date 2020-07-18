#include <opus/opusfile.h>
#include "opusdecoder.hpp"
#include <cstddef>
#include <memory>
#include <opus/opus.h>
#include <opus/opus_types.h>
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
WOpusDecoder::decode( std::string_view fileName ) {
    int  err { 0 };
    auto opusFile = op_open_file( fileName.data(), &err );

    if ( err < 0 )
        throw OpusException( err );

    std::vector< opus_int16 > outBuffer {};
    outBuffer.reserve( bufferSize );
    int numReadSamles { 1 };

    do {
        numReadSamles =
        op_read( opusFile, outBuffer.data(), bufferSize, nullptr );

        outWave.insert(
        outWave.end(), outBuffer.begin(), outBuffer.end() );

    } while ( numReadSamles > 0 );

    if ( numReadSamles < 0 )
        throw OpusException( numReadSamles );

    return outWave;
}

}   // namespace core::opusdecoder
