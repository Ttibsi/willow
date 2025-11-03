add_library(willow STATIC)
set_target_properties(willow PROPERTIES LINKER_LANGUAGE CXX)
target_sources(willow
    # PRIVATE
        # foo.cpp
    PUBLIC
        reporters.h
        test.h
        willow.h
)

target_include_directories(willow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
