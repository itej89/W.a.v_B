cmake_minimum_required(VERSION 3.0.0)
project(fmMotionData VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmMotionData_sources ./src/**.cc)
SET( SOURCE ${fmMotionData_sources})
SET(INCLUDES include ../fmDB/include ../fmCommon/include ../fmKinetics/include)


add_library(fmMotionData  ${SOURCE})


target_include_directories(fmMotionData PUBLIC ${INCLUDES})

find_package( Threads )
target_link_libraries(fmMotionData ${CMAKE_THREAD_LIBS_INIT} nlohmann_json  fmCommon fmDB fmKinetics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmMotionData PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)