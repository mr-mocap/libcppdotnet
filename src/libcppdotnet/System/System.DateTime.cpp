module;

#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

module System.DateTime;

import <chrono>;
import <cmath>;
import <compare>;
import <format>;
import <string>;
import <utility>;

import System.Exception;
import System.DayOfWeek;
import System.DateTimeKind;
import System.DateOnly;
import System.TimeOnly;
import System.TimeSpan;

namespace System
{

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int milliseconds)
    :
    _date_only( year, month, day ),
    _time_only( hour, minute, second, milliseconds )
{
}

DateTime::DateTime(const DateOnly &date_only, const TimeOnly &time_only)
    :
    _date_only( date_only ),
    _time_only( time_only)
{
}

DateTime::DateTime(const DateTime &other)
    :
    _date_only( other._date_only ),
    _time_only( other._time_only ),
    _kind( other._kind )
{
}

DateTime::DateTime(DateTime &&other)
    :
    _date_only( std::move(other._date_only) ),
    _time_only( std::move(other._time_only) ),
    _kind( std::move(other._kind) )
{
}

DateTime &DateTime::operator =(const DateTime &other)
{
    _date_only = other._date_only;
    _time_only = other._time_only;
    _kind = other._kind;
    return *this;
}

DateTime &DateTime::operator =(DateTime &&other)
{
    _date_only = std::move(other._date_only);
    _time_only = std::move(other._time_only);
    _kind = std::move(other._kind);
    return *this;
}

DateTime DateTime::Date() const
{
    return DateTime( _date_only, System::TimeOnly() );
}

TimeSpan DateTime::TimeOfDay() const
{
    return _time_only.ToTimeSpan();
}

DateTimeKind DateTime::Kind() const
{
    return _kind;
}

int DateTime::Year() const
{
    return _date_only.Year();
}

int DateTime::Month() const
{
    return _date_only.Month();
}

int DateTime::Day() const
{
    return _date_only.Day();
}

int DateTime::Hour() const
{
    return _time_only.Hour();
}

int DateTime::Minute() const
{
    return _time_only.Minute();
}

int DateTime::Second() const
{
    return _time_only.Second();
}

int DateTime::Millisecond() const
{
    return _time_only.Millisecond();
}

int DateTime::Microsecond() const
{
    return _time_only.Microsecond();
}

int DateTime::Nanosecond() const
{
    return _time_only.Nanosecond();
}

long DateTime::Ticks() const
{
    std::chrono::sys_days time_point_in_days( _date_only );
    std::chrono::sys_days origin( DateOnly::MinValue() );
    std::chrono::sys_days difference = time_point_in_days - origin.time_since_epoch();
    long     calculated_ticks = difference.time_since_epoch().count() * TimeSpan::TicksPerDay();

    //return difference.time_since_epoch().count() / TimeSpan::NanosecondsPerTick();
    return calculated_ticks + _time_only.Ticks();
}

enum System::DayOfWeek DateTime::DayOfWeek() const
{
    return _date_only.DayOfWeek();
}

int DateTime::DayOfYear() const
{
    return _date_only.DayOfYear();
}

DateTime DateTime::Now()
{
#if 0
    auto local_tp = current_zone()->to_local( system_clock::now() );

    return DateTime( sys_time( local_tp.time_since_epoch() ) );
#else
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::year_month_day           ymd{ std::chrono::floor<std::chrono::days>(now) };

    return DateTime( DateOnly( ymd ), TimeOnly( now.time_since_epoch() ) );
#endif
}

DateTime DateTime::UtcNow()
{
    std::chrono::system_clock::time_point now = std::chrono::clock_cast<std::chrono::system_clock, std::chrono::utc_clock>( std::chrono::utc_clock::now() );
    std::chrono::year_month_day           ymd{ std::chrono::floor<std::chrono::days>(now) };

    return DateTime( DateOnly( ymd ), TimeOnly( now.time_since_epoch() ) );
}

DateTime DateTime::Today()
{
    std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>( std::chrono::system_clock::now() ) };
    DateTime                    td{ DateOnly( ymd ), TimeOnly() };

    POSTCONDITION( td.Hour() == 0 );
    POSTCONDITION( td.Minute() == 0 );
    POSTCONDITION( td.Second() == 0 );

    return td;
}

DateTime DateTime::MinValue()
{
    return DateTime( DateOnly::MinValue(), TimeOnly::MinValue() );
}

DateTime DateTime::MaxValue()
{
    return DateTime( DateOnly::MaxValue(), TimeOnly::MaxValue() );
}

std::string DateTime::ToString() const
{
    return std::format("{} {}", _date_only.ToString(), _time_only.ToString() );
}

DateTime &DateTime::operator +=(const TimeSpan &time_span)
{
    return _accumulate( time_span );
}

DateTime &DateTime::operator -=(const TimeSpan &time_span)
{
    return _accumulate( -time_span );
}

DateTime &DateTime::operator +=(std::chrono::system_clock::duration time_duration)
{
    return _accumulate( time_duration );
}

DateTime &DateTime::operator -=(std::chrono::system_clock::duration time_duration)
{
    return _accumulate( -time_duration );
}

DateTime &DateTime::_accumulate(std::chrono::system_clock::duration time_duration)
{
    // First do the DateOnly part...
    {
        DateOnly result( _date_only );

        {
            std::chrono::days d = std::chrono::floor<std::chrono::days>( time_duration );

            result = result.AddDays( d.count() );
            time_duration -= d;
        }
        {
            std::chrono::months m = std::chrono::floor<std::chrono::months>( time_duration );

            result = result.AddMonths( m.count() );
            time_duration -= m;
        }
        {
            std::chrono::years y = std::chrono::floor<std::chrono::years>( time_duration );

            result = result.AddYears( y.count() );
            time_duration -= y;
        }
        _date_only = result;
    }

    // Then do the TimeOnly part
    {
        int excess_days;

        _time_only = _time_only.Add( time_duration, excess_days );
        _date_only = _date_only.AddDays( excess_days );
    }
    return *this;
}

DateTime DateTime::AddYears(int y) const
{
    return DateTime( _date_only.AddYears(y), _time_only );
}

DateTime DateTime::AddMonths(int months) const
{
    // First check that the parameter is within allowed bounds
    if ( months < -120'000 )
        ThrowWithTarget( ArgumentOutOfRangeException("months", "Parameter is less than minimum allowed value") );
    if ( months > 120'000 )
        ThrowWithTarget( ArgumentOutOfRangeException("months", "Parameter is greater than minimum allowed value") );

    return DateTime( _date_only.AddMonths( months ), _time_only );
}

DateTime DateTime::AddDays(double d) const
{
    double ipart;
    double fraction = std::modf( d, &ipart );
    TimeSpan ts_whole_days{ std::chrono::days{ static_cast<int>(ipart) } };
    double   leftover_ticks = fraction * static_cast<double>(TimeSpan::TicksPerDay());
    long fractional_day_in_ticks = static_cast<long>(leftover_ticks);

    return Add( ts_whole_days ).Add( TimeSpan( fractional_day_in_ticks ) );
}

DateTime DateTime::AddHours(double h) const
{
    double ipart;
    double fraction = std::modf( h, &ipart );
    TimeSpan ts_whole_hours{ std::chrono::hours{ static_cast<int>(ipart) } };
    long fractional_hours_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerHour());

    return Add( ts_whole_hours ).Add( TimeSpan( fractional_hours_in_ticks ) );
}

DateTime DateTime::AddMinutes(double m) const
{
    double ipart;
    double fraction = std::modf( m, &ipart );
    TimeSpan ts_whole_minutes{ std::chrono::minutes{ static_cast<int>(ipart) } };
    long fractional_minutes_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMinute());

    return Add( ts_whole_minutes ).Add( TimeSpan( fractional_minutes_in_ticks ) );
}

DateTime DateTime::AddSeconds(double s) const
{
    double ipart;
    double fraction = std::modf( s, &ipart );
    TimeSpan ts_whole_seconds{ std::chrono::seconds{ static_cast<int>(ipart) } };
    long fractional_seconds_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerSecond());

    return Add( ts_whole_seconds ).Add( TimeSpan( fractional_seconds_in_ticks ) );
}

DateTime DateTime::AddMilliseconds(double ms) const
{
    double ipart;
    double fraction = std::modf( ms, &ipart );
    TimeSpan ts_whole_milliseconds{ std::chrono::milliseconds{ static_cast<int>(ipart) } };
    long fractional_milliseconds_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMillisecond());

    return Add( ts_whole_milliseconds ).Add( TimeSpan( fractional_milliseconds_in_ticks ) );
}

DateTime DateTime::AddMicroseconds(double micro_seconds) const
{
    double ipart;
    double fraction = std::modf( micro_seconds, &ipart );
    TimeSpan ts_whole_microseconds{ std::chrono::microseconds{ static_cast<int>(ipart) } };
    long fractional_microseconds_in_ticks = static_cast<long>(fraction * TimeSpan::TicksPerMicrosecond());

    return Add( ts_whole_microseconds ).Add( TimeSpan( fractional_microseconds_in_ticks ) );
}

DateTime DateTime::AddTicks(long ticks) const
{
    return Add( TimeSpan(ticks) );
}

DateTime DateTime::Add(const TimeSpan &time_span) const
{
    // Detect a potential wrap-around...
    if ( Ticks() >= 0 )
    {
        // Overflow a long...
        if ( MaxValue().Ticks() - Ticks() < time_span.Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is greater than DateTime::MaxValue") );
    }
    else
    {
        if ( time_span.Ticks() < MinValue().Ticks() - Ticks() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is less than DateTime::MinValue") );
        
    }
        
    // We won't overflow the long, but we still might go out-of-bounds for a DateTime...
    DateTime result( *this );

    result._accumulate( time_span );
    if ( result < MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is less than DateTime::MinValue") );
    else
    {
        if ( result > MaxValue() )
            ThrowWithTarget( ArgumentOutOfRangeException("time_span", "The resulting DateTime is greater than DateTime::MaxValue") );
    }

    return result;
}

TimeSpan DateTime::Subtract(const DateTime &other_date) const
{
    std::chrono::sys_days left_days = _date_only;
    std::chrono::sys_days other_days = other_date._date_only;
    std::chrono::sys_days days_sub = left_days - other_days.time_since_epoch();
    TimeSpan difference( days_sub.time_since_epoch() );
    TimeSpan diff_time = _time_only.ToTimeSpan() - other_date._time_only.ToTimeSpan();

    return difference + diff_time;
}

DateTime DateTime::Subtract(const TimeSpan &other_time_span) const
{
    return DateTime( *this ) -= other_time_span;
}

int DateTime::Compare(const DateTime &t1, const DateTime &t2)
{
    std::strong_ordering result{ t1 <=> t2 };

    if ( result == std::strong_ordering::less )
        return -1;
    else if ( result == std::strong_ordering::equal )
        return 0;
    else
        return 1;
}

int DateTime::CompareTo(const DateTime &other) const
{
    return DateTime::Compare( *this, other);
}

DateTime DateTime::UnixEpoch()
{
    std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>( std::chrono::system_clock::time_point() ) };

    return DateTime( DateOnly( ymd ), TimeOnly::MinValue() );
}

}
