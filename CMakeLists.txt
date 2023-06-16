cmake_minimum_required(VERSION 3.16)
project(ticket_system)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2")

add_executable(code main.cpp bplus.h users.h processor.h train_system.h tools.h vector.hpp
        utility.hpp exceptions.hpp)
