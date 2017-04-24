cmake_minimum_required(VERSION 3.5)

add_executable(client
  ${CMAKE_SOURCE_DIR}/client.c
)

add_executable(server
  ${CMAKE_SOURCE_DIR}/server.c
)

target_link_libraries(client zmq)
target_link_libraries(server zmq)
