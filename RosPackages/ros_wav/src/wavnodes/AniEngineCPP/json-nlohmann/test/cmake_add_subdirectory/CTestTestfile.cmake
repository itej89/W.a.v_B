# CMake generated Testfile for 
# Source directory: /home/tej/Documents/AniClientCpp/json-nlohmann/test/cmake_add_subdirectory
# Build directory: /home/tej/Documents/AniClientCpp/json-nlohmann/test/cmake_add_subdirectory
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_add_subdirectory_configure "/usr/bin/cmake" "-G" "Unix Makefiles" "-Dnlohmann_json_source=/home/tej/Documents/AniClientCpp/json-nlohmann" "/home/tej/Documents/AniClientCpp/json-nlohmann/test/cmake_add_subdirectory/project")
set_tests_properties(cmake_add_subdirectory_configure PROPERTIES  FIXTURES_SETUP "cmake_add_subdirectory")
add_test(cmake_add_subdirectory_build "/usr/bin/cmake" "--build" ".")
set_tests_properties(cmake_add_subdirectory_build PROPERTIES  FIXTURES_REQUIRED "cmake_add_subdirectory")
