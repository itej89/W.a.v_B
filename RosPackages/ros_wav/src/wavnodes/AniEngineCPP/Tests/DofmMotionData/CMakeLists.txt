cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB DofmMotionData_sources ./src/**.cc)

add_executable(DofmMotionData ${SRCS} ${DofmMotionData_sources})


target_include_directories(DofmMotionData PUBLIC ${INCL})

target_link_libraries(DofmMotionData
    fmDB
    fmMotionData
    nlohmann_json
    libgtest
    libgmock
)

configure_file(CommandStore.sqlite CommandStore.db COPYONLY)

install(TARGETS DofmMotionData DESTINATION bin)