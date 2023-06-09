cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB fmDB_sources ./src/**.cc)

add_executable(DofmDB ${SRCS} ${fmDB_sources} )


target_include_directories(DofmDB PUBLIC ${INCL})

target_link_libraries(DofmDB
    fmDB
    libgtest
    libgmock
)

configure_file(CommandStore.sqlite CommandStore.db COPYONLY)

install(TARGETS DofmDB DESTINATION bin)