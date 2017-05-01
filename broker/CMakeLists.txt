cmake_minimum_required(VERSION 3.5)

if (APPLE)
  include_directories("/opt/local/include")
  link_directories("/opt/local/lib")
endif()

add_executable(client
  ${CMAKE_SOURCE_DIR}/client.c
)

add_executable(worker
  ${CMAKE_SOURCE_DIR}/worker.c
)

add_executable(broker
  ${CMAKE_SOURCE_DIR}/broker.c
)

target_link_libraries(client zmq)
target_link_libraries(worker zmq)
target_link_libraries(broker zmq)