add_library(willow STATIC
    willow.cpp
)

target_include_directories(willow PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
