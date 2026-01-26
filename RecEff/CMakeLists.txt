cmake_minimum_required (VERSION 3.29)

# CMakeLists for tools
project(RecEff VERSION 0.0.1 DESCRIPTION "Codes for track Reconstruction Efficiencies")

# Set up
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
set(CMAKE_PREFIX_PATH $ENV{ROOTSYS}/cmake)
#set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/build")
find_package(ROOT REQUIRED COMPONENTS RIO Net)
find_package(LZ4 REQUIRED)
add_definitions(-D__LZ4__)
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/RecEffLib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_SOURCE_DIR}/RecEffLib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
    SET(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/RecEffLib")
ENDIF("${isSystemDir}" STREQUAL "-1")

include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})
set(RecEff_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/RecEffTools.cc" )
set(RecEff_HEADERS
        "${PROJECT_SOURCE_DIR}/include/RecEffTools.h" )
add_library(RecEffLib SHARED ${RecEff_SOURCE_FILES})
set_target_properties(RecEffLib PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)
set (CMAKE_INSTALL_LIBDIR "lib")
#target_include_directories(uRWellLib PRIVATE include)
target_include_directories(RecEffLib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

include(GNUInstallDirs)
#include(CMakePackageConfigHelpers)

install(TARGETS RecEffLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(RecEffLib.pc.in RecEffLib.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/RecEffLib.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


# Add directories
add_subdirectory(hipo/hipo4)
add_subdirectory(AnaCodes)
#find_package(hipo4 REQUIRED)
