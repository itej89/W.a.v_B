cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB DofmSystem_sources ./src/**.cc )

add_executable(DofmSystem ${SRCS} ${DofmSystem_sources} )


target_include_directories(DofmSystem PUBLIC ${INCL})

target_link_libraries(DofmSystem
    fmSystem
    libgtest
    libgmock
)

configure_file(CommandStore.sqlite CommandStore.db COPYONLY)

install(TARGETS DofmSystem DESTINATION bin)