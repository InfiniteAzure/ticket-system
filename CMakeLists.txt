cmake_minimum_required(VERSION 3.16)
project(ticket_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(ticket_system main.cpp bplus.h users.h processor.h train_system.h tools.h vector.hpp
        utility.hpp exceptions.hpp)
