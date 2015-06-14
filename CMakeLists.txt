cmake_minimum_required(VERSION 3.2)
project(CookieHTTP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB SRC src/*)
add_executable(CookieHTTP ${SRC})

if(WIN32)
  target_link_libraries(CookieHTTP wsock32 ws2_32)
endif()