cmake_minimum_required(VERSION 3.18)
if (USE_CUDA)
  project(Terminal_Renderer LANGUAGES CXX CUDA)
  set(CMAKE_CUDA_STANDARD 11)
endif()
if (NOT USE_CUDA) 
  project(Terminal_Renderer LANGUAGES CXX)
  set(CMAKE_CXX_STANDARD 17)
endif()

option(USE_CPU "Build with CPU compute support" ON)
option(USE_GPU "Build with GPU compute support" OFF)
option(USE_CUDA "Build with CUDA compute support" OFF)
#-------------------------------------------------------#
# Collect source files
file(GLOB LIBRARY_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

if (USE_CPU)
    file(GLOB CPU_SOURCES
        ${CMAKE_SOURCE_DIR}/src/cpucompute/*.cpp
    )
    list(APPEND LIBRARY_SOURCES ${CPU_SOURCES})
endif()

if (USE_GPU)
    file(GLOB GPU_SOURCES
        ${CMAKE_SOURCE_DIR}/src/gpucompute/*.cpp
    )
    list(APPEND LIBRARY_SOURCES ${GPU_SOURCES})
endif()

if (USE_CUDA)
    file(GLOB CUDA_SOURCES
        ${CMAKE_SOURCE_DIR}/src/cudacompute/*.cpp
    )
    list(APPEND LIBRARY_SOURCES ${CUDA_SOURCES})
endif()
# Check if any source files are found
if (NOT LIBRARY_SOURCES)
    message(FATAL_ERROR "No source files found in src/")
endif()

#-------------------------------------------------------#
# Define include directories
set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/dependencies/stbi
)

if (USE_CPU)
    list(APPEND INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/include/cpucompute
    )
endif()

if (USE_GPU)
    list(APPEND INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/include/gpucompute
    )
endif()

if (USE_CUDA)
    list(APPEND INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/include/cudacompute
    )
endif()

include_directories(${INCLUDE_DIRS})

#-------------------------------------------------------#
# Collect test files
file(GLOB TEST_FILES
    ${CMAKE_SOURCE_DIR}/tests/*.cpp
)

if (USE_CPU)
    file(GLOB CPU_TEST_FILES
        ${CMAKE_SOURCE_DIR}/tests/cputests/*.cpp
    )
    list(APPEND TEST_FILES ${CPU_TEST_FILES})
endif()

if (USE_GPU)
    file(GLOB GPU_TEST_FILES
        ${CMAKE_SOURCE_DIR}/tests/gputests/*.cpp
    )
    list(APPEND TEST_FILES ${GPU_TEST_FILES})
endif()

if (USE_CUDA)
    file(GLOB CUDA_TEST_FILES
        ${CMAKE_SOURCE_DIR}/tests/cudatests/*.cpp
    )
    list(APPEND TEST_FILES ${CUDA_TEST_FILES})
endif()


#-------------------------------------------------------#



# Add the shared library
add_library(Terminal_Renderer SHARED ${LIBRARY_SOURCES})


#-------------------------------------------------------#

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

#-------------------------------------------------------#
# Add CUDA support if USE_CUDA is ON
if (USE_CUDA)
    enable_language(CUDA)
    set_target_properties(MyLibrary PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
    )
# Set CUDA flags (optional)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -lineinfo")
endif()



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

