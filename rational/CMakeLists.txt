add_library(rational rational.cpp)

target_include_directories(
        rational
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        rational
)