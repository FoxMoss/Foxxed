if(CMAKE_VERSION VERSION_LESS "4.1")
    cmake_minimum_required(VERSION 3.1)
else()
    cmake_minimum_required(VERSION 4.1)
endif()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++)

project(Foxxed)

option(BUILD_STATIC "Build static" OFF)

if(BUILD_STATIC)
  add_compile_options(--static)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
set(CPACK_PACKAGE_CONTACT fox.ellisontaylor@gmail.com)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER FoxMoss)
set(CPACK_PACKAGE_NAME "foxxed")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_GENERATOR "DEB;TGZ")

include(CPack)

add_subdirectory(src)

