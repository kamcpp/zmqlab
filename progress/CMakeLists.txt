cmake_minimum_required(VERSION 3.5)

if (APPLE)
  include_directories("/opt/local/include")
  link_directories("/opt/local/lib")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

add_executable(client
  ${CMAKE_SOURCE_DIR}/Client.cc
  ${CMAKE_SOURCE_DIR}/ProgressSyncProxy.cc
)

add_executable(broker
  ${CMAKE_SOURCE_DIR}/Broker.cc
)

add_executable(server
  ${CMAKE_SOURCE_DIR}/ProgressService.cc
  ${CMAKE_SOURCE_DIR}/ServiceRuntime.cc
  ${CMAKE_SOURCE_DIR}/Server.cc
)

target_link_libraries(client zmq)
target_link_libraries(broker zmq)
target_link_libraries(server zmq)

target_compile_options(client PUBLIC -std=c++11 -O3)
target_compile_options(broker PUBLIC -std=c++11 -O3)
target_compile_options(server PUBLIC -std=c++11 -O3)
