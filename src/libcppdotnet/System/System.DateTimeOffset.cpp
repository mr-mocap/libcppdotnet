module System.DateTimeOffset;

import System.DateTime;
import System.TimeSpan;
import System.DayOfWeek;

namespace System
{

DateTimeOffset::DateTimeOffset(const System::DateTime &dt)
    :
    _date_time( dt )
{
}

DateTimeOffset::DateTimeOffset(const System::DateTime &dt, const TimeSpan &offset)
    :
    _date_time( dt ),
    _offset_from_utc( offset )
{
}

const System::DateTime &DateTimeOffset::DateTime() const
{
    return _date_time;
}

const TimeSpan &DateTimeOffset::Offset() const
{
    return _offset_from_utc;
}

System::DateTime DateTimeOffset::Date() const
{
    return _date_time.Date();
}

enum DayOfWeek DateTimeOffset::DayOfWeek() const
{
    return _date_time.DayOfWeek();
}

int DateTimeOffset::DayOfYear() const
{
    return _date_time.DayOfYear();
}

int DateTimeOffset::Year() const
{
    return _date_time.Year();
}

int DateTimeOffset::Month() const
{
    return _date_time.Month();
}

int DateTimeOffset::Day() const
{
    return _date_time.Day();
}

int DateTimeOffset::Hour() const
{
    return _offset_from_utc.Hours();
}

int DateTimeOffset::Minute() const
{
    return _offset_from_utc.Minutes();
}

int DateTimeOffset::Second() const
{
    return _offset_from_utc.Seconds();
}

int DateTimeOffset::Millisecond() const
{
    return _offset_from_utc.Milliseconds();
}

int DateTimeOffset::Microsecond() const
{
    return _offset_from_utc.Microseconds();
}

int DateTimeOffset::Nanosecond() const
{
    return _offset_from_utc.Nanoseconds();
}

long DateTimeOffset::Ticks() const
{
    return _date_time.Ticks();
}

DateTimeOffset DateTimeOffset::MinValue()
{
    return DateTimeOffset( DateTime::MinValue() );
}

DateTimeOffset DateTimeOffset::MaxValue()
{
    return DateTimeOffset( DateTime::MaxValue() );
}

DateTimeOffset DateTimeOffset::UnixEpoch()
{
    return DateTimeOffset( DateTime::UnixEpoch() );
}

DateTimeOffset DateTimeOffset::Now()
{
    return DateTimeOffset( DateTime::Now() );
}

DateTimeOffset DateTimeOffset::UtcNow()
{
    return DateTimeOffset( DateTime::UtcNow() );
}

}
