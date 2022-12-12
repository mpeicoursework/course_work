if (BUILD_TESTING) 
    add_subdirectory(tests)
endif()

add_library(big_int big_int.cpp)

target_include_directories(
        big_int
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        big_int
        utils
)