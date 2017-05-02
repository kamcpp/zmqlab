cmake_minimum_required(VERSION 3.5)

if (APPLE)
  include_directories("/opt/local/include")
  link_directories("/opt/local/lib")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(client
  ${CMAKE_SOURCE_DIR}/client.cc
  ${CMAKE_SOURCE_DIR}/progress_sync_proxy.cc
)

add_executable(broker
  ${CMAKE_SOURCE_DIR}/broker.cc
)

add_executable(server
  ${CMAKE_SOURCE_DIR}/progress_service.cc
  ${CMAKE_SOURCE_DIR}/server.cc
)

target_link_libraries(client zmq)
target_link_libraries(broker zmq)
target_link_libraries(server zmq)

target_compile_options(client PUBLIC -std=c++11 -O3)
target_compile_options(broker PUBLIC -std=c++11 -O3)
target_compile_options(server PUBLIC -std=c++11 -O3)
