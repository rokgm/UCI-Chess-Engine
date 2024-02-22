cmake_minimum_required(VERSION 3.22)

project(chess_uci)

enable_language(CXX)

# Set C++ 17 standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Spdlog option
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)
FetchContent_Declare(GTest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.14.x
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog GTest)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    core
    logger 
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:RelWithDebInfo>:DEBUG>
)

# Set warning level and treat warnings as errors.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -Wconversion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /permissive /W4 /WX)
else()
    message(FATAL_ERROR "Compiler not supported for this project.")
endif()

target_precompile_headers(${PROJECT_NAME}
    PUBLIC
    [["logger/Logger.h"]]
)

# Copy book moves to binary folder
file(COPY book DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY book DESTINATION "${CMAKE_BINARY_DIR}")

enable_testing()
include(CTest)

add_subdirectory(src)
add_subdirectory(test)