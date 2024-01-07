cmake_minimum_required(VERSION 3.10)
project(SQL100k)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# 添加可执行文件
add_executable(CSVParser CSVParser.cpp Timer.cpp)

# 添加头文件路径
target_include_directories(CSVParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 添加MySQL Connector C++的链接信息
target_link_libraries(CSVParser mysqlcppconn)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)