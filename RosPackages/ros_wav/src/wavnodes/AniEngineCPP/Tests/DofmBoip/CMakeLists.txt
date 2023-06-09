cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB fmBoip_sources 
./src/**.cc 
./src/Framework/**.cc
# ./src/Framework/TransportLayer/**.cc
./src/Framework/DataTypes/Extras/**.cc
)

add_executable(DofmBoip ${SRCS} ${fmBoip_sources} )


target_include_directories(DofmBoip PUBLIC ${INCL})

target_link_libraries(DofmBoip
    fmBoip
    libgtest
    libgmock
)


install(TARGETS DofmBoip DESTINATION bin)