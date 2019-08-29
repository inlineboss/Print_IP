cmake_minimum_required(VERSION 3.8)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

project(print_ip VERSION 0.0.${VERSION_BUILD})

add_executable(
print_ip
src/main.cpp
src/usr_type_traits.h
src/out_byte.h
)

set_property(TARGET print_ip PROPERTY CXX_STANDARD 17)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip
    PRIVATE "${CMAKE_BINARY_DIR}" src/
)

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT askimarhond@gmail.com)

include(CPack)
