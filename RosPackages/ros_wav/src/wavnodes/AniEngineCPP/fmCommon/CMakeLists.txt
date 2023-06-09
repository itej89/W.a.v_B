cmake_minimum_required(VERSION 3.0.0)
project(fmCommon VERSION 0.1.0)

include(CTest)
enable_testing()



file(GLOB fmCommon_sources ./src/**.cc  ./src/TCPModule/DataTypes/Extras/**.cc 
                                        ./src/TCPModule/TransportLayers/**.cc 
                                        ./src/TCPModule/TransportLayers/Helpers/**.cc)
SET( SOURCE ${fmCommon_sources})
SET(INCLUDES include )


add_library(fmCommon  ${SOURCE})


target_include_directories(fmCommon PUBLIC ${INCLUDES})

find_package( Threads )
find_package(ZLIB)

#target_link_libraries(fmCommon ${CMAKE_THREAD_LIBS_INIT} log)
target_link_libraries(fmCommon ${CMAKE_THREAD_LIBS_INIT} ZLIB::ZLIB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmCommon PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)