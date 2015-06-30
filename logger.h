#ifndef LOGGER_H
#define LOGGER_H

/*!
  \file
  \brief Модуль логирования.

  Интеграция:<br>
  Подключаем заголовок: include "logger.h"<br>
  Добавляем в сборку logger.c<br>
  Сборка CMAKE:<br>
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")<br>

set(Boost_USE_STATIC_LIBS ON)<br>
set(Boost_USE_MULTITHREADED ON)<br>
set(BOOST_COMPONENTS ${BOOST_COMPONENTS} log thread system)<br>
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)<br>
include_directories(${Boost_INCLUDE_DIRS})<br>

add_executable(${PROJECT_NAME} main.cpp logger.cpp)<br>
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})<br>
*/

// std
#include <iostream>

// boost log
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>

namespace logger
{
    //! Уровни логирования
    enum severity_level
    {
        trace,  ///< Трассировка
        debug,  ///< Отладка
        info,     ///< Информационные сообщения
        warning,      //!< Предупреждения
        error,    ///< Ошибки
        critical      ///< Критические ошибки
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

/*!
    Инциализация модуля логирования.
*/
    void init(std::string filename = "log.txt", severity_level level = info);

    // глобальный логгер, с мутексом и уровнями
    BOOST_LOG_GLOBAL_LOGGER(lgr, boost::log::sources::severity_logger_mt<severity_level>)

/*!
    дефайны для быстрого доступа, к глобальному логгеру
*/
    #define logtrace    BOOST_LOG_SEV(logger::lgr::get(), logger::trace)
    #define logdebug    BOOST_LOG_SEV(logger::lgr::get(), logger::debug)
    #define loginfo     BOOST_LOG_SEV(logger::lgr::get(), logger::info)
    #define logwarning  BOOST_LOG_SEV(logger::lgr::get(), logger::warning)
    #define logerror    BOOST_LOG_SEV(logger::lgr::get(), logger::error)
    #define logcritical BOOST_LOG_SEV(logger::lgr::get(), logger::critical)
}

#endif // LOGGER_H
