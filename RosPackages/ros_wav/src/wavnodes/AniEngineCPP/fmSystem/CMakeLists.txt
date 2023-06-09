cmake_minimum_required(VERSION 3.0.0)
project(fmSystem VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmSystem_sources ./src/**.cc ./src/Initialization/**.cc ./src/Initialization/BindJOB/**.cc  ./src/GameEffects/**.cc  ./src/JOBS/**.cc)
SET( SOURCE ${fmSystem_sources})
SET(INCLUDES include ../fmDB/include ../fmCommon/include ../fmMotionData/include ../fmKinetics/include )


add_library(fmSystem  ${SOURCE})


target_include_directories(fmSystem PUBLIC ${INCLUDES})

find_package( Threads )
#target_link_libraries( fmSystem ${CMAKE_THREAD_LIBS_INIT} log nlohmann_json fmKinetics fmMotionData fmCommon fmDB)
target_link_libraries( fmSystem ${CMAKE_THREAD_LIBS_INIT}  nlohmann_json fmKinetics fmMotionData fmCommon fmDB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmSystem PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)