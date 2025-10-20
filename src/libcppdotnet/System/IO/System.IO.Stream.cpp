module System.IO.Stream;

import <cstddef>;
import <iostream>;
import <memory>;
import <string_view>;
import <utility>;

import System.IO.Exception;

namespace System::IO
{

Stream::Stream(std::unique_ptr<std::iostream> &&stream, bool can_read, bool can_write, bool can_seek)
    :
    _stream{ std::move(stream) },
    _canRead{ can_read },
    _canWrite{ can_write },
    _canSeek{ can_seek }
{
}

Stream::Stream(Stream &&other)
    :
    _stream{ std::move(other._stream) },
    _canRead{ other._canRead },
    _canWrite{ other._canWrite },
    _canSeek{ other._canSeek }
{
}

Stream::~Stream()
{
}

Stream &Stream::operator =(Stream &&other)
{
    _stream = std::move(other._stream);
    _canRead = other._canRead;
    _canWrite = other._canWrite;
    _canSeek = other._canSeek;
    return *this;
}

std::unique_ptr<Stream> Stream::Null()
{
    return std::make_unique<Stream>( ThisIsHereForStdMakeUnique{} );
}

void Stream::Close()
{
    _close();
}

void Stream::Flush()
{
    _flush();
}

void Stream::Write(std::string_view bytes)
{
    if ( _stream && CanWrite() )
        _stream->write( bytes.data(), bytes.size() );
}

void Stream::Write(ReadOnlySpan<std::byte> bytes)
{
    if ( _stream && CanWrite() )
        _stream->write( reinterpret_cast<const char *>(bytes.data()), bytes.Length() );
}

void Stream::WriteByte(std::byte value)
{
    if ( _stream && CanWrite() )
        _stream->put( std::bit_cast<char>(value) );
}

void Stream::WriteByte(uint8_t byte)
{
    if ( _stream && CanWrite() )
        _stream->put( byte );
}

std::string Stream::Read(int number_of_bytes)
{
    if ( _stream && CanRead() )
    {
        std::string input_buffer;

        input_buffer.resize( number_of_bytes );
        _stream->read( input_buffer.data(), number_of_bytes );
        return input_buffer;
    }
    return {};
}

int Stream::Read(Span<std::byte> buffer)
{
    if ( _stream && CanRead() )
    {
        if ( buffer.Length() == 0 )
            return 0; // No place to store the data, so don't read anything

        _stream->read( reinterpret_cast<char *>(buffer.data()), buffer.Length() );
        return buffer.Length(); // TODO: REALLY check the read byte count!
    }
    return 0;
}

int Stream::ReadByte()
{
    if ( _stream )
    {
        if ( !CanRead() )
            ThrowWithTarget( NotSupportedException("This stream does not support reading") );

        if ( _stream->eof() )
            return -1;

        return _stream->get();
    }

    return 0;
}

size_t Stream::Length()
{
    return _length();
}

size_t Stream::Position()
{
    return _position(); // Now, call the virtual method
}

void Stream::_close()
{
}

void Stream::_flush()
{
    if ( _stream )
        _stream->flush();
}

size_t Stream::_length()
{
    // Default behavior: Throw an exception IF we have a stream and can't seek
    if ( _stream )
    {
        if ( !CanSeek() )
            ThrowWithTarget( NotSupportedException("Finding the Length is not supported") );
    }

    return 0;
}

size_t Stream::_position()
{
    if ( _stream )
    {
        // Factor out the most common behavior
        if ( !CanSeek() )
            ThrowWithTarget( NotSupportedException("Finding the Position is not supported (Unable to Seek for this stream type)") );

        if ( _stream->fail() )
        {
            ThrowWithTarget( IO::IOException("Stream is in a fail state") );
        }
    }
    return 0;
}

long Stream::Seek(long offset, SeekOrigin origin)
{
    if ( _stream )
    {
        switch ( origin )
        {
        case SeekOrigin::Begin:
            _stream->seekp( offset, std::ios::beg );
            break;
        case SeekOrigin::Current:
            _stream->seekp( offset, std::ios::cur );
            break;
        case SeekOrigin::End:
            _stream->seekp( offset, std::ios::end );
            break;
        }
        return _stream->tellp();
    }
    return 0;
}

}
