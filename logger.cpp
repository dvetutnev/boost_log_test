// main
#include "logger.h"

// std
#include <iostream>
#include <fstream>

// boost log
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
//#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
//#include <boost/log/sinks/sync_frontend.hpp>
//#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>

// boost other
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/utility/empty_deleter.hpp>

/*

void logger::init(enum severity_level level)
{
    using namespace boost::log;

    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink_t;

    // file log
    boost::shared_ptr<text_sink_t> file_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ofstream> file_stream(new std::ofstream("log.txt"));
    file_sink->locked_backend()->add_stream(file_stream);
    file_sink->locked_backend()->auto_flush();
    core::get()->add_sink(file_sink);


    // console log
    boost::shared_ptr<text_sink_t> console_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ostream> console_stream(&std::clog, boost::empty_deleter());
    console_sink->locked_backend()->add_stream(console_stream);
    console_sink->locked_backend()->auto_flush();
    core::get()->add_sink(console_sink);
}
*/

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>

using namespace boost::log;

BOOST_LOG_GLOBAL_LOGGER_INIT(logger::lgr, sources::severity_logger_mt<logger::severity_level>)
{
    sources::severity_logger_mt<logger::severity_level> lg;

    lg.add_attribute("RecordID", attributes::counter<unsigned int>(1));
    lg.add_attribute("TimeStamp", attributes::local_clock());
    lg.add_attribute("Scope", attributes::named_scope());

    core::get()->add_global_attribute("TimeStamp", attributes::local_clock());

    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink_t;

    // file log
    boost::shared_ptr<text_sink_t> file_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ofstream> file_stream(new std::ofstream("log.txt"));
    file_sink->locked_backend()->add_stream(file_stream);
    file_sink->locked_backend()->auto_flush();
    core::get()->add_sink(file_sink);


    // console log
    boost::shared_ptr<text_sink_t> console_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ostream> console_stream(&std::clog, boost::empty_deleter());
    console_sink->locked_backend()->add_stream(console_stream);
    console_sink->locked_backend()->auto_flush();
    core::get()->add_sink(console_sink);


    return lg;
}

