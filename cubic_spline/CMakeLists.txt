add_library(cubic_spline cubic_spline.cpp)

target_include_directories(
    cubic_spline
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    cubic_spline
    rational
)