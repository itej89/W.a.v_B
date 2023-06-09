cmake_minimum_required(VERSION 3.0.0)
project(fmDB VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmDB_sources ./src/**.cc ./src/**.c)
SET( SOURCE ${fmDB_sources})  
SET(INCLUDES include) 


add_library( fmDB  ${SOURCE})
 

target_include_directories(fmDB PUBLIC ${INCLUDES})

find_package( Threads )
target_link_libraries( fmDB ${CMAKE_THREAD_LIBS_INIT}  ${CMAKE_DL_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmDB PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)
                        