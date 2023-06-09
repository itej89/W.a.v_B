cmake_minimum_required(VERSION 3.0.0)

project(AniClient VERSION 0.1.0)


SET(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_FLAGS "-fPIC")
set(CMAKE_CXX_FLAGS "-fPIC")



# add_subdirectory(Main)
add_subdirectory(json-nlohmann)
add_subdirectory(fmCommon)
# add_subdirectory(fmDB)
add_subdirectory(fmSerial)
# add_subdirectory(fmKinetics)
# add_subdirectory(fmMotionData)
# add_subdirectory(fmSystem)
add_subdirectory(fmBoip)
add_subdirectory(fmBotConnect)
add_subdirectory(cpr)
# add_subdirectory(Tests)

