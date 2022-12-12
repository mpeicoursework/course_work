add_library(tasks tasks.cpp)

target_include_directories(
    tasks
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    tasks
    rational
)