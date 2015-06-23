#include <iostream>
#include <fstream>

//using namespace std;


///*
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>


#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

//#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
//#include <boost/log/sinks/sync_frontend.hpp>
//#include <boost/log/sinks/text_ostream_backend.hpp>

#include <boost/utility/empty_deleter.hpp>

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
//*/

void logger_init()
{
    using namespace boost::log;

    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink_t;
    // file log
    boost::shared_ptr<text_sink_t> file_sink = boost::make_shared<text_sink_t>();
    //boost::shared_ptr<std::ofstream> file_stream("log.txt");
    file_sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>("log.txt"));
    //file_sink->locked_backend()->add_stream(file_stream);
    core::get()->add_sink(file_sink);
    // console log
    boost::shared_ptr<text_sink_t> console_sink = boost::make_shared<text_sink_t>();
    boost::shared_ptr<std::ostream> console_stream(&std::clog, boost::empty_deleter());
    //console_sink->locked_backend()->add_stream(boost::make_shared<std::ostream>(&std::clog, boost::empty_deleter()));
    console_sink->locked_backend()->add_stream(console_stream);

    core::get()->add_sink(console_sink);
}

//#include <boost/log/trivial.hpp>

int main()
{
    logger_init();
    boost::log::sources::logger lg;

    BOOST_LOG(lg) << "In log";

    std::cout << "Hello World!" << std::endl;
    return 0;
}

