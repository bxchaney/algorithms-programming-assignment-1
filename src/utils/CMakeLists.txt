add_library(utils point_reader.cpp close.cpp brute_force.cpp efficient.cpp)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
