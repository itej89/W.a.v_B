cmake_minimum_required(VERSION 3.0.0)
project(fmBotConnect VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmBotConnect_sources 
./src/**.cc 
./src/DataTypes/**.cc
./src/DataTypes/**.cc
./src/DataTypes/Delegates/**.cc
./src/DataTypes/Enums/**.cc
./src/DataTypes/FrameParsers/**.cc
./src/DataTypes/FrameParsers/Parsers/**.cc
./src/DataTypes/FrameParsers/RxFrames/**.cc
./src/DataTypes/FrameParsers/TxFrames/**.cc
)

SET( SOURCE ${fmBotConnect_sources})
SET(INCLUDES include ../fmCommon/include ../fmBoip/include ../json-nlohmann/include)

add_library(fmBotConnect  ${SOURCE})
target_include_directories(fmBotConnect PUBLIC ${INCLUDES})

find_package(Threads)
target_link_libraries(fmBotConnect ${CMAKE_THREAD_LIBS_INIT} nlohmann_json fmCommon fmBoip)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmBotConnect PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)