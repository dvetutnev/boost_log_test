#ifndef LOGGER_H
#define LOGGER_H

// std
#include <iostream>

// boost log
#include <boost/log/common.hpp>
#include <boost/log/sources/logger.hpp>
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

    //void init(enum severity_level level = trace);

    BOOST_LOG_GLOBAL_LOGGER(lgr, boost::log::sources::severity_logger_mt<severity_level>)

    #define logtrace    BOOST_LOG_SEV(lgt::get(), trace)
    #define logdebug    BOOST_LOG_SEV(lgr::get(), debug)
    #define loginfo     BOOST_LOG_SEV(lgr::get(), info)
    #define logwarning  BOOST_LOG_SEV(lgr::get(), warning)
    #define logerror    BOOST_LOG_SEV(lgr::get(), error)
    #define logcritical BOOST_LOG_SEV(lgr::get(), critical)
}

#endif // LOGGER_H
