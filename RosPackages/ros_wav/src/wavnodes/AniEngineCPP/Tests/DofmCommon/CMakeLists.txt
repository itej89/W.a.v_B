cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB fmCommon_sources 
./src/**.cc 
)

add_executable(DofmCommon ${SRCS} ${fmCommon_sources} )


target_include_directories(DofmCommon PUBLIC ${INCL})

target_link_libraries(DofmCommon
    fmCommon
    libgtest
    libgmock
)


install(TARGETS DofmCommon DESTINATION bin)