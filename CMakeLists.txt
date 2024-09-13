cmake_minimum_required(VERSION 3.18)
project(Terminal_Renderer LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 11)

# Find all C++ and CUDA source files in src/
file(GLOB LIBRARY_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cu
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Check if any source files are found
if (NOT LIBRARY_SOURCES)
    message(FATAL_ERROR "No source files found in src/")
endif()

# Add the shared library
add_library(Terminal_Renderer SHARED ${LIBRARY_SOURCES})

# Glob all test files in the tests/ directory
file(GLOB TEST_FILES
    ${CMAKE_SOURCE_DIR}/tests/*.cpp
)

# Loop over each test file and create a corresponding executable and test
foreach(TEST_FILE ${TEST_FILES})
    set_target_properties(Terminal_Renderer PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_TYPE} "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY_${CONFIG_TYPE} "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE} "${CMAKE_BINARY_DIR}/bin"
    )
    # Extract the test name from the file name (strip directory and extension)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Create an executable for each test
    add_executable(${TEST_NAME} ${TEST_FILE})

    # Link the shared library to the test executable
    target_link_libraries(${TEST_NAME} Terminal_Renderer)

    # Register each test
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Enable testing
enable_testing()

# Set CUDA flags (optional)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -lineinfo")

# Set custom output directories for the library and binaries
set_target_properties(Terminal_Renderer PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Set output directory for all test executables
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()

