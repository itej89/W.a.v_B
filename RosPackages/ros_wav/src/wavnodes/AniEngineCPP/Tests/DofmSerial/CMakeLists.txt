cmake_minimum_required(VERSION 3.0.0)

file(GLOB SRCS ./src/*.cc)
file(GLOB INCL include)

add_executable(DofmSerial ${SRCS})

target_include_directories(DofmSerial PUBLIC ${INCL})

target_link_libraries(DofmSerial
    fmSerial
    nlohmann_json
    libgtest
    libgmock
)

configure_file(CommandList.txt CommandList.txt @ONLY)


install(TARGETS DofmSerial DESTINATION bin)