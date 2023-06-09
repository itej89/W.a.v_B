cmake_minimum_required(VERSION 3.0.0)
project(fmBoip VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB fmBoip_sources ./src/**.cc ./src/Framework/**.cc  
                                     ./src/Framework/DataTypes/**.cc
                                     ./src/Framework/DataTypes/DOIP_OBJECTS/**.cc
                                     ./src/Framework/DataTypes/Extras/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_OBJECTS/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/ECU_VALUE_CODES/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_TESTER_REQUEST/TESTER_CODE_VALUES/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_TYPES/**.cc
                                     ./src/Framework/DataTypes/PAYLOAD_TYPE_OBJECT_MAP/**.cc
                                     ./src/Framework/DOIPFrameHelpers/**.cc
                                     ./src/Framework/DOIPLayer/**.cc
                                     ./src/Framework/DOIPLayer/DOIPStateMachines/DiagStates/**.cc
                                     ./src/Framework/DOIPLayer/DOIPStateMachines/**.cc
                                     ./src/Framework/Configuration/**.cc
                                     ./src/Framework/TransportLayer/**.cc
                                     ./src/Framework/TransportLayer/Helpers/**.cc
                                     ./src/Framework/Validation/**.cc )
SET( SOURCE ${fmBoip_sources})
SET(INCLUDES include ../fmCommon/include)


add_library(fmBoip  ${SOURCE})


target_include_directories(fmBoip PUBLIC ${INCLUDES})

find_package( Threads )
target_link_libraries(fmBoip ${CMAKE_THREAD_LIBS_INIT} fmCommon)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set_target_properties(fmBoip PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)