module;

#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

module System.Diagnostics.Stopwatch;


namespace System::Diagnostics
{

Stopwatch::Stopwatch(bool startnow)
    :
    _start_time{ clock_type::now() },
    _is_running{ startnow }
{
}

Stopwatch Stopwatch::StartNew()
{
    return Stopwatch( true );
}

void Stopwatch::Start()
{
    if ( _is_running )
        return;
    _start_time = clock_type::now();
    _is_running = true;
    
    POSTCONDITION( IsRunning() );
}

void Stopwatch::Stop()
{
    auto n = clock_type::now();

    _accumulated_time += n - _start_time;
    _is_running = false;
    _start_time = n;

    POSTCONDITION( !IsRunning() );
}

void Stopwatch::Restart()
{
    // This is to make Start() function as we want
    // (i.e. pretend that we are stopped right now and then call Start())
    _is_running = false;

    _accumulated_time = clock_type::duration::zero();
    Start();

    POSTCONDITION( IsRunning() );
}

void Stopwatch::Reset()
{
    _is_running = false;
    _accumulated_time = clock_type::duration::zero();

    POSTCONDITION( !IsRunning() );
    POSTCONDITION( _accumulated_time == clock_type::duration::zero() );
}

bool Stopwatch::IsRunning() const
{
    return _is_running;
}

long Stopwatch::GetTimestamp()
{
    return clock_type::now().time_since_epoch().count();
}

TimeSpan Stopwatch::GetElapsedTime(long starting_time_stamp)
{
    clock_type::duration difference( clock_type::now().time_since_epoch().count() - starting_time_stamp );

    return { difference };
}

TimeSpan Stopwatch::GetElapsedTime(long starting_time_stamp, long ending_time_stamp)
{
    clock_type::duration difference( ending_time_stamp - starting_time_stamp );

    return { difference };
}

TimeSpan Stopwatch::Elapsed()
{
    if ( _is_running )
    {
        auto n = clock_type::now();

        // Capture the current time difference...
        _accumulated_time += (n - _start_time);
        
        // Reset the start time
        _start_time = n;
    }
    return { _accumulated_time };
}

long Stopwatch::ElapsedMilliseconds()
{
    clock_type::duration d = Elapsed();

    return std::chrono::floor<std::chrono::milliseconds>(d).count();
}

long Stopwatch::ElapsedTicks()
{
    clock_type::duration d = Elapsed();

    return d.count();
}

std::string Stopwatch::ToString() const
{
    if ( _is_running )
        return std::format("{} and running", _accumulated_time);
    else
        return std::format("{}", _accumulated_time);
}

}
