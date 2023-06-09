cmake_minimum_required(VERSION 3.0.0)
project(fmWavMove VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmWavMove_sources ./src/**.cc ./src/**.c)
SET( SOURCE ${fmWavMove_sources})  
SET(INCLUDES include) 


add_library( fmWavMove  ${SOURCE})
 

target_include_directories(fmWavMove PUBLIC ${INCLUDES})

find_package( Threads )
target_link_libraries( fmWavMove ${CMAKE_THREAD_LIBS_INIT} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmWavMove PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)
                        