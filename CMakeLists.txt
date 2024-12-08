cmake_minimum_required(VERSION 3.20)
project(DiplomNetology VERSION 1.0 LANGUAGES CXX)

set(OPENSSL_ROOT_DIR "C:\\Program Files\\OpenSSL-Win64") #OpenSSL
set(libpq_DIR "C:\\Program Files\\libpqxx-7.9.2") #libpqxx
set(BOOST_ROOT "C:\\Program Files\\Boost") #Boost

find_package(BOOST 1.86.0 REQUIRED )
find_package(OpenSSl REQUIRED)

if(NOT Boost_FOUND)
	message(FATAL_ERROR "Could not find Boost")
	endif()

add_compile_definitions(_WIN32_WINNT=0x0A01)

#PQXX:
set(PostgreSQL_ADDITIONAL_VERSIONS "17")
set(SKIP_BUILD_TEST ON)
add_subdirectory("C:\\Program Files\\libpqxx-7.9.2" pqxx-build)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8")

add_subdirectory(spider)

add_subdirectory(http_server)