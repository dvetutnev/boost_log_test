#ifndef LOGGER_H
#define LOGGER_H

// std
#include <iostream>

// boost log
#include <boost/log/common.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/attributes.hpp>
//#include <boost/log/sources/global_logger_storage.hpp>

namespace logger
{
    enum severity_level
    {
        trace,
        debug,
        info,
        warning,
        error,
        critical
    };

    template<typename CharT, typename TraitsT>
    inline std::basic_ostream<CharT, TraitsT>& operator << (std::basic_ostream<CharT, TraitsT>& strm, severity_level level)
    {
        static const char* const str[] =
        {
            "trace",
            "debug",
            "info",
            "warning",
            "error",
            "critical"
        };

        if (static_cast<std::size_t>(level) < (sizeof(str) / sizeof(*str)))
            strm << str[level];
        else
            strm << static_cast<int>(level);
        return strm;
    }

    void init();
/*
    BOOST_LOG_GLOBAL_LOGGER(lgr, boost::log::sources::severity_logger_mt<severity_level>)

    #define logtrace    BOOST_LOG_SEV(logger::lgt::get(), trace)
    #define logdebug    BOOST_LOG_SEV(lgr::get(), debug)
    #define loginfo     BOOST_LOG_SEV(lgr::get(), info)
    #define logwarning  BOOST_LOG_SEV(lgr::get(), warning)
    #define logerror    BOOST_LOG_SEV(logger::lgr::get(), logger::error)
    #define logcritical BOOST_LOG_SEV(lgr::get(), critical)
    */
}

#endif // LOGGER_H
