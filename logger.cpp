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
//#include <boost/log/sinks.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
//#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>

// boost other
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/utility/empty_deleter.hpp>


using namespace boost::log;

BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logger::severity_level)

BOOST_LOG_GLOBAL_LOGGER_INIT(logger::lgr, sources::severity_logger_mt<logger::severity_level>)
{
    sources::severity_logger_mt<logger::severity_level> lg;
    return lg;
}

void logger::init(std::string filename, severity_level level)
{
    // удаляем старую конфигурацию
    core::get()->reset_filter();
    core::get()->remove_all_sinks();
    // включаем метку времени
    core::get()->add_global_attribute("TimeStamp", attributes::local_clock());
    // фильтр уровня лога
    core::get()->set_filter(severity >= level);

    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink_t;

    // file log
    boost::shared_ptr<text_sink_t> file_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ofstream> file_stream(new std::ofstream(filename, std::ofstream::out | std::ofstream::app)); // файл лога, новые записи добавляются в конец
    file_sink->locked_backend()->add_stream(file_stream);
    file_sink->locked_backend()->auto_flush();
    file_sink->set_formatter(expressions::stream // формат
                                << "[" << expressions::format_date_time(timestamp, "%Y-%m-%d %H:%M:%S.%f") << "]" // метка времени
                                << severity // уровень лога, оператор << перегружен в logger.h
                                << ": " << expressions::smessage);
    core::get()->add_sink(file_sink);

    // console log
    boost::shared_ptr<text_sink_t> console_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ostream> console_stream(&std::clog, boost::empty_deleter());
    console_sink->locked_backend()->add_stream(console_stream);
    console_sink->locked_backend()->auto_flush();
    console_sink->set_formatter(expressions::stream
                                //<< "[" << expressions::format_date_time(timestamp, "%Y-%m-%d %H:%M:%S.%f") << "]"
                                << severity
                                << ": " << expressions::smessage);
    core::get()->add_sink(console_sink);
}

