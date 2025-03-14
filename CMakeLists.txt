cmake_minimum_required(VERSION 3.8)

project(BSDFXMLParser VERSION 0.0.3 LANGUAGES CXX)
set(LIB_NAME ${PROJECT_NAME})

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()

if(NOT "${CMAKE_CXX_EXTENSIONS}")
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

include(GNUInstallDirs)
if(NOT "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()

if(NOT "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()

if(NOT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()

# Check to see if this project is included in another via add_subdirectory
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(DOWNLOAD_GTEST ON)
else()
    set(DOWNLOAD_GTEST OFF)
endif()

include(FetchContent)

# Test from FileParse should not be visible here
set(BUILD_FileParse_tests OFF CACHE BOOL "Build FileParse tests" FORCE)

set(FileParse_Branch "Version_1.0.5")

FetchContent_Declare(
    FileParse
    GIT_REPOSITORY https://github.com/LBNL-ETA/FileParse.git
    GIT_TAG ${FileParse_Branch}
)
FetchContent_MakeAvailable(FileParse)

# Set include directories for FileParse
set(FileParse_INCLUDE_DIRS "${fileparse_SOURCE_DIR}/include")
include_directories(${FileParse_INCLUDE_DIRS})

# Add your target
add_subdirectory(src)

Option(BUILD_BSDFXMLParser_Tests "Build tests for bsdf xml parsing." ON)

if(BUILD_BSDFXMLParser_Tests)
    enable_testing()
    add_subdirectory(test)

    # Set the path to the test directory
    set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
    target_compile_definitions(BSDFXMLParser-test PRIVATE TEST_DATA_DIR="${TEST_DATA_DIR}")

    # Add the test with the specified arguments
    add_test(NAME BSDFXMLParser-test
             COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BSDFXMLParser-test --gtest_catch_exceptions=0)
endif()

# Setting variable for parent projects so it can be checked if same version is used
set_property(TARGET ${LIB_NAME} PROPERTY FileParse_Branch ${FileParse_Branch})

if (MSVC)
    # Set warning level to 4 for MSVC
    add_compile_options(/W4)
else()
    # Set warning level to all for other compilers (e.g., GCC, Clang)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()