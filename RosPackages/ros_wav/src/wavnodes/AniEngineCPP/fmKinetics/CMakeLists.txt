cmake_minimum_required(VERSION 3.0.0)
project(fmKinetics VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmKinetics_sources ./src/**.cc ./src/**.c ./src/Framework/**.cc ./src/Framework/DataTypes/**.cc  ./src/Framework/DataTypes/Constants/**.cc  ./src/Framework/DataTypes/Parsers/**.cc  ./src/Framework/DataTypes/Parsers/RequestCommandParser/**.cc  ./src/Framework/DataTypes/Parsers/ResponseCommandParser/**.cc  ./src/FrameworkInterface/**.cc  ./src/FrameworkInterface/InterfaceImplementation/**.cc  ./src/FrameworkInterface/PublicTypes/**.cc  ./src/FrameworkInterface/PublicTypes/Config/**.cc  ./src/FrameworkInterface/PublicTypes/Constants/**.cc)
SET( SOURCE ${fmKinetics_sources})
SET(INCLUDES include ../fmDB/include ../fmCommon/include ../fmSerial/include include)


add_library(fmKinetics  ${SOURCE})


target_include_directories(fmKinetics PUBLIC ${INCLUDES})

find_package( Threads )
#target_link_libraries(fmKinetics ${CMAKE_THREAD_LIBS_INIT} log fmSerial fmCommon fmDB)
target_link_libraries(fmKinetics ${CMAKE_THREAD_LIBS_INIT}  fmSerial fmCommon fmDB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmKinetics PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)