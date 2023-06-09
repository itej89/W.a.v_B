cmake_minimum_required(VERSION 3.0.0)
project(fmSerial VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmSerial_sources ./src/**.cc ./src/**.c)
SET( SOURCE ${fmSerial_sources})  
SET(INCLUDES include include/FrameworkInterface/PublicTypes) 


add_library( fmSerial  ${SOURCE})
 

target_include_directories(fmSerial PUBLIC ${INCLUDES})

find_package( Threads )
target_link_libraries( fmSerial ${CMAKE_THREAD_LIBS_INIT} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmSerial PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)
                        