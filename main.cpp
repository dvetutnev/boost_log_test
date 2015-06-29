#include <iostream>

#include "logger.h"
#include "tt.h"


int main()
{
    logger::init("log.log", logger::trace);
/*
    boost::log::sources::severity_logger_mt<logger::severity_level> lg3;

    //BOOST_LOG(lg) << "In log";
    //BOOST_LOG(lg2) << "In log2";
    //boost::log::sources::logger_mt.

    BOOST_LOG_SEV(lg3, logger::trace) << "test trace";
    BOOST_LOG_SEV(lg3, logger::debug) << "test debug";
    BOOST_LOG_SEV(lg3, logger::info) << "test info";
    BOOST_LOG_SEV(lg3, logger::warning) << "test warning";
    BOOST_LOG_SEV(lg3, logger::error) << "test error";
    BOOST_LOG_SEV(lg3, logger::critical) << "test critical";
*/

    logtrace << "trace";
    logdebug << "debug";
    loginfo << "info";
    logwarning << "warning";
    logerror << "error";
    logcritical << "critical";


    auto ptt = new tt();
    std::cout << "Hello World!" << std::endl;
    return 0;
}

