cmake_minimum_required(VERSION 3.7)
project(p2)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp SensorCommunication.cpp SensorConfiguration.cpp SensorTag.cpp)
add_executable(p2 ${SOURCE_FILES})
target_link_libraries(p2 Threads::Threads)
