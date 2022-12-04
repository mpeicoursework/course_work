cmake_minimum_required(VERSION 3.16)

project(course_work)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
include(CTest)
if (BUILD_TESTING)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIR})
endif()

add_subdirectory(rational)
add_subdirectory(utils)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    rational
)


