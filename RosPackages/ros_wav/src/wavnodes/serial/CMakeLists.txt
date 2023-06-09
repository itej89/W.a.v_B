cmake_minimum_required(VERSION 2.8.3)
project(serial)


set(rt_LIBRARIES rt)
set(pthread_LIBRARIES pthread)


## Sources
set(serial_SRCS
    src/serial.cc
    include/serial/serial.h
    include/serial/v8stdint.h
)

list(APPEND serial_SRCS src/impl/unix.cc)

## Add serial library
add_library(${PROJECT_NAME} ${serial_SRCS})

target_link_libraries(${PROJECT_NAME} rt pthread)

## Uncomment for example
add_executable(serial_example examples/serial_example.cc)
add_dependencies(serial_example ${PROJECT_NAME})
target_link_libraries(serial_example ${PROJECT_NAME})

## Include headers
include_directories(include)


