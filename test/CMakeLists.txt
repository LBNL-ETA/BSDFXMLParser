include_directories("${PROJECT_SOURCE_DIR}")

set(PROJECT_TEST_NAME ${LIB_NAME}-test)

# Use FetchContent to manage GoogleTest
include(FetchContent)

if(DOWNLOAD_GTEST STREQUAL ON AND NOT TARGET gtest)
    # Set gtest_force_shared_crt before FetchContent_MakeAvailable
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    # Configure FetchContent to download GoogleTest
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2 # Use the desired version
    )

    FetchContent_MakeAvailable(googletest)
endif()

add_executable(${PROJECT_TEST_NAME}
    bsdf_xml_file_serialization.unit.cpp
    BSDFXMLEnumerators.unit.cpp
    main.cpp
    helper/Common.hpp
    helper/bsdfxml/TestHelper.hpp
    helper/bsdfxml/TestHelper.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_17)

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")
