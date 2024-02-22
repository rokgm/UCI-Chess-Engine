add_library(uci Interface.cpp Interface.h)

target_link_libraries(uci
    PUBLIC
    core
)

target_include_directories(uci
    INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

target_compile_definitions(uci
    PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:RelWithDebInfo>:DEBUG>
)

# Set warning level and treat warnings as errors.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(logger PRIVATE -Werror -Wall -Wextra -Wpedantic -Wconversion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(logger PRIVATE /permissive /W4 /WX)
else()
    message(FATAL_ERROR "Compiler not supported for this project.")
endif()