cmake_minimum_required(VERSION 3.0.0)

file(GLOB INCL include)


file(GLOB fmKinetics_sources ./src/**.cc ./src/Framework/DataTypes/Constants/*.cc ./src/Framework/DataTypes/Parsers/*.cc ./src/Framework/DataTypes/Parsers/RequestCommandParser/*.cc ./src/Framework/DataTypes/Parsers/ResponseCommandParser/*.cc)

add_executable(DofmKinetics ${SRCS} ${fmKinetics_sources} )


target_include_directories(DofmKinetics PUBLIC ${INCL})

target_link_libraries(DofmKinetics
    fmKinetics
    libgtest
    libgmock
)

configure_file(CommandStore.sqlite CommandStore.db @ONLY)

install(TARGETS DofmKinetics DESTINATION bin)