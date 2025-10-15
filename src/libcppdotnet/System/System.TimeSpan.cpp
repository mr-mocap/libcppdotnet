module;

#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

module System.TimeSpan;

import <chrono>;
import <cstdlib>;
import <format>;

import System.Exception;

namespace System
{

TimeSpan::TimeSpan(int hours, int minutes, int seconds)
    :
    TimeSpan(0, hours, minutes, seconds)
{
}

TimeSpan::TimeSpan(int d, int h, int m, int s)
    :
    _time_span( std::chrono::days(d) +
                std::chrono::hours(h) +
                std::chrono::minutes(m) +
                std::chrono::seconds(s) )
{
}

TimeSpan::TimeSpan(int d, int h, int m, int s, int ms)
    :
    _time_span( std::chrono::days(d) +
                std::chrono::hours(h) +
                std::chrono::minutes(m) +
                std::chrono::seconds(s) +
                std::chrono::milliseconds(ms) )
{
}

TimeSpan::TimeSpan(long ticks)
    :
    TimeSpan( ticks * std::chrono::nanoseconds( NanosecondsPerTick() ) )
{
}

TimeSpan::TimeSpan(std::chrono::system_clock::duration value)
    :
    _time_span( value )
{
}

TimeSpan::TimeSpan(const TimeSpan &other)
    :
    _time_span( other._time_span )
{
}

TimeSpan::TimeSpan(TimeSpan &&other)
    :
    _time_span( std::move(other._time_span) )
{
}

TimeSpan &TimeSpan::operator =(const TimeSpan &other)
{
    _time_span = other._time_span;
    return *this;
}

TimeSpan &TimeSpan::operator =(TimeSpan &&other)
{
    _time_span = std::move(other._time_span);
    return *this;
}

TimeSpan TimeSpan::FromTicks(long value)
{
    return TimeSpan( value );
}

TimeSpan TimeSpan::FromMicroseconds(long value)
{
    return TimeSpan( std::chrono::microseconds( value ) );
}

TimeSpan TimeSpan::FromMilliseconds(long milli, long micro)
{
    return TimeSpan( std::chrono::milliseconds( milli ) + std::chrono::microseconds( micro ) );
}

TimeSpan TimeSpan::FromSeconds(long value)
{
    return TimeSpan( std::chrono::seconds( value ) );
}

TimeSpan TimeSpan::FromMinutes(long value)
{
    return TimeSpan( std::chrono::minutes( value ) );
}

TimeSpan TimeSpan::FromHours(int value)
{
    return TimeSpan( std::chrono::hours( value ) );
}

TimeSpan TimeSpan::FromDays(int value)
{
    return TimeSpan( std::chrono::days( value ) );
}

TimeSpan TimeSpan::Zero()     { return TimeSpan( std::chrono::system_clock::duration::zero() ); }
TimeSpan TimeSpan::MinValue() { return TimeSpan( std::chrono::system_clock::duration::min() ); }
TimeSpan TimeSpan::MaxValue() { return TimeSpan( std::chrono::system_clock::duration::max() ); }

long TimeSpan::Ticks() const
{
    return _time_span.count() / NanosecondsPerTick();
}

TimeSpan::operator std::chrono::system_clock::duration() const
{
    return _time_span;
}

int TimeSpan::Days() const
{
    bool negative = (_time_span.count() < 0);
    long d = (negative) ? std::chrono::ceil<std::chrono::days>( _time_span ).count() : std::chrono::floor<std::chrono::days>( _time_span ).count();

    return static_cast<int>(d);
}

int TimeSpan::Hours() const
{
    bool negative = (_time_span.count() < 0);
    long h = (negative) ? std::chrono::ceil<std::chrono::hours>( _time_span ).count() : std::chrono::floor<std::chrono::hours>( _time_span ).count();
    std::ldiv_t  d = std::div( h, static_cast<long>(HoursPerDay()) );

    POSTCONDITION( d.rem >= -23 );
    POSTCONDITION( d.rem <=  23 );

    return d.rem;
}

int TimeSpan::Minutes() const
{
    bool negative = (_time_span.count() < 0);
    long m = (negative) ? std::chrono::ceil<std::chrono::minutes>( _time_span ).count() : std::chrono::floor<std::chrono::minutes>( _time_span ).count();
    std::ldiv_t d = std::div( m, MinutesPerHour() );

    POSTCONDITION( d.rem >= -59 );
    POSTCONDITION( d.rem <=  59 );

    return d.rem;
}

int TimeSpan::Seconds() const
{
    bool negative = (_time_span.count() < 0);
    long s = (negative) ? std::chrono::ceil<std::chrono::seconds>( _time_span ).count() : std::chrono::floor<std::chrono::seconds>( _time_span ).count();
    std::ldiv_t d = std::div( s, SecondsPerMinute() );

    POSTCONDITION( d.rem >= -59 );
    POSTCONDITION( d.rem <=  59 );

    return d.rem;
}

int TimeSpan::Milliseconds() const
{
    bool negative = (_time_span.count() < 0);
    long ms = (negative) ? std::chrono::ceil<std::chrono::milliseconds>( _time_span ).count() : std::chrono::floor<std::chrono::milliseconds>( _time_span ).count();
    std::ldiv_t d = std::div( ms, MillisecondsPerSecond() );

    POSTCONDITION( d.rem >= -999 );
    POSTCONDITION( d.rem <=  999 );

    return d.rem;
}

int TimeSpan::Microseconds() const
{
    bool negative = (_time_span.count() < 0);
    long ms = (negative) ? std::chrono::ceil<std::chrono::microseconds>( _time_span ).count() : std::chrono::floor<std::chrono::microseconds>( _time_span ).count();
    std::ldiv_t d = std::div( ms, MicrosecondsPerSecond() );

    POSTCONDITION( d.rem >= -999'999 );
    POSTCONDITION( d.rem <=  999'999 );

    return d.rem;
}

int TimeSpan::Nanoseconds() const
{
    // System clock is typically in nanoseconds, so we can just use the count() directly
    long ns = _time_span.count();
    std::ldiv_t d = std::div( ns, NanosecondsPerSecond() );

    POSTCONDITION( d.rem >= -99'999'999 );
    POSTCONDITION( d.rem <=  99'999'999 );

    return d.rem;
}

double TimeSpan::TotalDays() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerDay() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerDay() );

    return int_part + frac_part;
}

double TimeSpan::TotalHours() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerHour() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerHour() );

    return int_part + frac_part;
}

double TimeSpan::TotalMinutes() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerMinute() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerMinute() );

    return int_part + frac_part;
}

double TimeSpan::TotalSeconds() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerSecond() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerSecond() );

    return int_part + frac_part;
}

double TimeSpan::TotalMilliseconds() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerMillisecond() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerMillisecond() );

    return int_part + frac_part;
}

double TimeSpan::TotalMicroseconds() const
{
    std::ldiv_t d = std::div( Ticks(), TicksPerMicrosecond() );
    double int_part = d.quot;
    double frac_part = static_cast<double>(d.rem) / static_cast<double>( TicksPerMicrosecond() );

    return int_part + frac_part;
}

double TimeSpan::TotalNanoseconds() const
{
    return _time_span.count();
}

TimeSpan &TimeSpan::operator +=(std::chrono::system_clock::duration duration_to_add)
{
    _time_span += duration_to_add;
    return *this;
}

TimeSpan &TimeSpan::operator -=(std::chrono::system_clock::duration duration_to_subtract)
{
    _time_span -= duration_to_subtract;
    return *this;
}

template <class Representation>
TimeSpan TimeSpan::operator *=(const Representation &right)
{
    _time_span *= static_cast<std::chrono::system_clock::rep>( right );
    return *this;
}

template <class Representation>
TimeSpan TimeSpan::operator /=(const Representation &right)
{
    _time_span /= static_cast<std::chrono::system_clock::rep>( right );
    return *this;
}

TimeSpan TimeSpan::Add(const TimeSpan &time_span) const
{
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting TimeSpan is greater than TimeSpan::MaxValue") );
    }
    else
    {
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is less than DateTime::MinValue") );
        
    }
    return *this + time_span;
}

TimeSpan TimeSpan::Subtract(const TimeSpan &time_span) const
{
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        if ( MinValue().Ticks() + Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is less than DateTime::MinValue") );
    }
    else
    {
        if ( time_span.Ticks() < MaxValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting TimeSpan is greater than TimeSpan::MaxValue") );
        
    }
    return *this - time_span;
}

TimeSpan TimeSpan::Multiply(double scalar) const
{
    // using namespace std::literals;

    // // Detect a potential wrap-around...
    // long long this_count = _time_span.count();
    // long long other_count = time_span._time_span.count();
    // long long new_value = this_count * other_count;

    // if ( new_value > system_clock::duration( MaxValue() ).count() )
    //     ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting TimeSpan is greater than TimeSpan::MaxValue"sv) );
    // else
    // {
    //     if ( new_value < system_clock::duration( MinValue() ).count() )
    //         ThrowWithTarget( ArgumentOutOfRangeException("time_span"sv, "The resulting DateTime is less than DateTime::MinValue"sv) );
    // }

    // TODO: Implement Me Properly!
    return *this * scalar;
}

TimeSpan TimeSpan::Divide(double scalar) const
{
    // TODO: Implement Me Properly!
    return *this / scalar;
}

int TimeSpan::CompareTo(const TimeSpan &other) const
{
    return Compare( *this, other);
}

TimeSpan TimeSpan::Duration() const
{
    return TimeSpan( std::chrono::abs( _time_span ) );
}

TimeSpan TimeSpan::Negate() const
{
    return -*this;
}

std::string TimeSpan::ToString() const
{
    return std::format("{}", _time_span);
}

}
