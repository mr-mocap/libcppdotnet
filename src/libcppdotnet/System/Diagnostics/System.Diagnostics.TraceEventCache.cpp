module System.Diagnostics.TraceEventCache;

import <string>;
import <string_view>;

import System.Environment;
import System.DateTime;

namespace System::Diagnostics
{

std::string TraceEventCache::Callstack() const
{
    return Environment::StackTrace();
}

const System::DateTime &TraceEventCache::DateTime() const
{
    if ( !_datetime.has_value() )
        _datetime.emplace( System::DateTime::UtcNow() );
    return _datetime.value();
}

#if 0
Collections::Stack TraceEventCache::LogicalOperationStack() const
{
}
#endif

std::string_view TraceEventCache::ThreadId() const
{
    return "System::Diagnostics::TraceEventCache::ThreadId() IMPLEMENT ME!";
}

int TraceEventCache::ProcessId() const
{
    // TODO: FIXME
    return 0;
}

}
