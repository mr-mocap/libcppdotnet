module System.DateOnly;

export import <chrono>;
export import <compare>;
export import <format>;
export import <string>;

import System.Exception;

export import System.DayOfWeek;

#if 0
export import System.DateTime;
#endif

namespace System
{

DateOnly::DateOnly()
{
}

DateOnly::~DateOnly()
{
}

DateOnly::DateOnly(int year, int month, int day)
    :
    _year_month_day( std::chrono::year(year), std::chrono::month(month), std::chrono::day(day) )
{
    // POSTCONDITION( year <= 9999 );
    // POSTCONDITION( year >= 1 );
    // POSTCONDITION( month >= 1 );
    // POSTCONDITION( month <= 12 );
    // POSTCONDITION( day >= 1 );
    // POSTCONDITION( day <= 31 );
}

DateOnly::DateOnly(const std::chrono::year_month_day &ymd)
    :
    _year_month_day( ymd )
{
}

DateOnly::DateOnly(const std::chrono::sys_days &d)
    :
    _year_month_day( std::chrono::year_month_day( d ) )
{
}

DateOnly::DateOnly(const DateOnly &other)
    :
    _year_month_day( other._year_month_day )
{
}

DateOnly &DateOnly::operator =(const DateOnly &other)
{
    _year_month_day = other._year_month_day;
    return *this;
}

DateOnly::DateOnly(DateOnly &&other)
    :
    _year_month_day( std::move(other._year_month_day) )
{
}

DateOnly &DateOnly::operator =(DateOnly &&other)
{
    _year_month_day = std::move(other._year_month_day);
    return *this;
}

int DateOnly::Day() const
{
    unsigned int temp{ _year_month_day.day() };

    return static_cast<int>( temp );
}

int DateOnly::Month() const
{
    unsigned int temp{ _year_month_day.month() };

    return static_cast<int>( temp );
}

int DateOnly::Year() const
{
    return static_cast<int>( _year_month_day.year() );
}

int DateOnly::DayNumber() const
{
    std::chrono::sys_days num_days{ _year_month_day };

    return static_cast<int>( num_days.time_since_epoch().count() );
}

int DateOnly::DayOfYear() const
{
    using namespace std::chrono;

    sys_days temp_days{ _year_month_day };
    years    current_year = floor<years>( temp_days.time_since_epoch() );
    days     d            = duration_cast<days>( temp_days.time_since_epoch() - current_year );

    // Let's add 1 since the subtraction puts us at a 0-based number
    return static_cast<int>( d.count() + 1 );
}

DateOnly DateOnly::AddDays(int num_days) const
{
    using namespace std::chrono;

    sys_days as_time_point{ sys_days( _year_month_day ) };
    sys_days new_time_point = as_time_point + days( num_days );
    DateOnly new_date_only{ new_time_point };

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_days", "Parameter is less than minimum allowed value" ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_days", "Parameter is greater than minimum allowed value" ) );
    
    return new_date_only;
}

DateOnly DateOnly::AddMonths(int num_months) const
{
    DateOnly new_date_only( _year_month_day + std::chrono::months( num_months ) );

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_months", "Parameter is less than minimum allowed value" ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_months", "Parameter is greater than minimum allowed value" ) );
    
    return new_date_only;
}

DateOnly DateOnly::AddYears(int num_years) const
{
    DateOnly new_date_only( _year_month_day + std::chrono::years( num_years ) );

    if ( new_date_only <= MinValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_years", "Parameter is less than minimum allowed value" ) );
    else if ( new_date_only >= MaxValue() )
        ThrowWithTarget( ArgumentOutOfRangeException( "num_years", "Parameter is greater than minimum allowed value" ) );
    
    return new_date_only;
}

int DateOnly::CompareTo(const DateOnly &other) const
{
    std::strong_ordering result{ *this <=> other };

    if ( result == std::strong_ordering::less )
        return -1;
    else if ( result == std::strong_ordering::equal )
        return 0;
    else
        return 1;
}

DateOnly DateOnly::FromDayNumber(int day_number)
{
    return DateOnly::MinValue().AddDays( day_number );
}

void DateOnly::Deconstruct(int &year, int &month, int &day)
{
    year = Year();
    month = Month();
    day = Day();
}
#if 0
DateOnly DateOnly::FromDateTime(const DateTime &dt)
{
    return DateOnly{ dt.Year(), dt.Month(), dt.Day() };
}
#endif
std::string DateOnly::ToString() const
{
    return std::format("{}", _year_month_day);
}

enum System::DayOfWeek DateOnly::DayOfWeek() const
{
    std::chrono::weekday wd{ std::chrono::sys_days( _year_month_day ) };

    return static_cast<enum System::DayOfWeek>( wd.c_encoding() );
}

DateOnly DateOnly::MinValue()
{
    return DateOnly( 1, 1, 1 );
}

DateOnly DateOnly::MaxValue()
{
    return DateOnly( 9999, 12, 31 );

}

DateOnly::operator std::chrono::sys_days() const
{
    return _year_month_day;
}

DateOnly::operator std::chrono::year_month_day() const
{
    return _year_month_day;
}

}
