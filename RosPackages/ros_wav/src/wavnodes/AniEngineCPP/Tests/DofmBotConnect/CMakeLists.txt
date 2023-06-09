cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB DofmBotConnect_sources 
./src/**.cc 
)

add_executable(DofmBotConnect ${SRCS} ${DofmBotConnect_sources} )


target_include_directories(DofmBotConnect PUBLIC ${INCL})

target_link_libraries(DofmBotConnect
    fmBotConnect
    libgtest
    libgmock
)

install(TARGETS DofmBotConnect DESTINATION bin)