cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 11)

link_libraries("-lboost_system")
link_libraries("-pthread")

#-----------------------------------------------------
#
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost COMPONENTS system)
#find_package( Threads )
#
##add_compile_definitions(_GLIBCXX_USE_CXX11_ABI true)
##add_compile_definitions(-D_GLIBCXX_USE_CXX11_ABI)
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    add_executable(EchoClient src/connectionHandler.cpp include/connectionHandler.h src/echoClient.cpp )
#    target_link_libraries(EchoClient ${Boost_LIBRARIES})
#endif()
#
##add_executable(Client src/main.cpp src/BGRegClient.cpp src/BGRegClient.h)
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    add_executable(BGRSclient src/connectionHandler.cpp include/connectionHandler.h src/BGRegClient.cpp include/BGRegClient.h src/Task.cpp include/Task.h src/UserInputReader.cpp include/UserInputReader.h include/Operation.h )#src/Operation.cpp)
#    target_link_libraries(BGRSclient ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
#endif()
#
##add_executable(EchoClient src/echoClient.cpp src/connectionHandler.cpp)

#-----------------------------------------------------

add_executable(EchoClient src/connectionHandler.cpp include/connectionHandler.h src/echoClient.cpp )
add_executable(BGRSclient src/connectionHandler.cpp include/connectionHandler.h src/BGRegClient.cpp include/BGRegClient.h src/Task.cpp include/Task.h src/UserInputReader.cpp include/UserInputReader.h include/Operation.h src/Operation.cpp)