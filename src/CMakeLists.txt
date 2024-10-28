set( CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON )

add_library( ${LIB_NAME}
        bsdfdata/Data.hpp
        bsdfdata/Parser.cpp
        bsdfdata/Parser.hpp
        bsdfdata/Enumerators.hpp
        bsdfdata/Enumerators.cpp
        bsdfdata/EnumSerializers.hpp
        bsdfdata/Serializers.hpp)

target_link_libraries(${LIB_NAME} PRIVATE xmlParser)
target_link_libraries(${LIB_NAME} PRIVATE FileParse)

# Set a property on the existing target
set_property(TARGET ${LIB_NAME} PROPERTY variable_name "test")

if(NOT "${fPIC}")
  set(fPIC ON)
endif()

if(fPIC)
  set_property(TARGET ${LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()


if (CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -pedantic -Werror )
endif()
if (MSVC)
    target_compile_options(${LIB_NAME} PRIVATE /W4 /WX)
endif()


target_compile_features(${LIB_NAME} PRIVATE cxx_std_17)
