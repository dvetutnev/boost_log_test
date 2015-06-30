#ifndef LOGGER_H
#define LOGGER_H

// std
#include <iostream>

// boost log
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>

namespace logger
{
    // уровни лога
    enum severity_level
    {
        trace,
        debug,
        info,
        warning,
        error,
        critical
    };

    // перегруженый оператор для вывода уровня лога
    template<typename CharT, typename TraitsT>
    inline std::basic_ostream<CharT, TraitsT>& operator << (std::basic_ostream<CharT, TraitsT>& strm, severity_level level)
    {
        static const char* const str[] =
        {
            "[trace]",
            "[debug]",
            "[info]",
            "[warning]",
            "[error]",
            "[critical]"
        };

        if (static_cast<std::size_t>(level) < (sizeof(str) / sizeof(*str)))
            strm << str[level];
        else
            strm << static_cast<int>(level);
        return strm;
    }

    // инициализация
    void init(std::string filename = "log.txt", severity_level level = info);
    // глобальный логгер, с мутексом и уровнями
    BOOST_LOG_GLOBAL_LOGGER(lgr, boost::log::sources::severity_logger_mt<severity_level>)
    // дефайны для быстрого доступа
    #define logtrace    BOOST_LOG_SEV(logger::lgr::get(), logger::trace)
    #define logdebug    BOOST_LOG_SEV(logger::lgr::get(), logger::debug)
    #define loginfo     BOOST_LOG_SEV(logger::lgr::get(), logger::info)
    #define logwarning  BOOST_LOG_SEV(logger::lgr::get(), logger::warning)
    #define logerror    BOOST_LOG_SEV(logger::lgr::get(), logger::error)
    #define logcritical BOOST_LOG_SEV(logger::lgr::get(), logger::critical)
}

#endif // LOGGER_H
