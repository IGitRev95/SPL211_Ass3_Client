cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 11)


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(EchoClient src/connectionHandler.cpp include/connectionHandler.h src/echoClient.cpp )
    target_link_libraries(EchoClient ${Boost_LIBRARIES})
endif()

add_executable(Client src/main.cpp)

#add_executable(EchoClient src/echoClient.cpp src/connectionHandler.cpp)