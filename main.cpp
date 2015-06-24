#include <iostream>

#include "logger.h"


int main()
{
    //logger::init();

    //logger::init(logger::trace);

    boost::log::sources::logger_mt lg;
    boost::log::sources::logger_mt lg2;

    BOOST_LOG(lg) << "In log";
    BOOST_LOG(lg2) << "In log2";
    //boost::log::sources::logger_mt.

    std::cout << "Hello World!" << std::endl;
    return 0;
}

