add_library(utils container.h point.h tree.h)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
