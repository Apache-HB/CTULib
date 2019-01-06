cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Cthulhu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework Cocoa -framework Metal -framework MetalKit")
endif(APPLE)

include_directories(./Cthulhu)

file(GLOB_RECURSE CthulhuCoreSources RELATIVE ${CMAKE_SOURCE_DIR} Cthulhu/Core/*.cpp)

add_library(CthulhuCore STATIC
    ${CthulhuCoreSources}
)

file(
    GLOB_RECURSE
    CthulhuGraphicsSourcesOS
    RELATIVE ${CMAKE_SOURCE_DIR}
    Cthulhu/Graphics/${CMAKE_SYSTEM_NAME}/*.*
)

file(
    GLOB
    CthulhuGraphicsSources
    RELATIVE ${CMAKE_SOURCE_DIR}
    Cthulhu/Graphics/*.cpp
)

set(CthulhuGraphicsSources ${CthulhuGraphicsSources} ${CthulhuGraphicsSourcesOS})

add_library(CthulhuGraphics STATIC
    ${CthulhuGraphicsSources}
)

target_link_libraries(CthulhuGraphics CthulhuCore)

add_executable(WindowTest Programs/Tests/Engine/Window.cpp)
target_link_libraries(WindowTest CthulhuGraphics)

file(GLOB_RECURSE CthulhuFileSystemSources RELATIVE ${CMAKE_SOURCE_DIR} Cthulhu/FileSystem/*.cpp)

add_library(CthulhuFileSystem STATIC
    ${CthulhuFileSystemSources}
)

file(GLOB_RECURSE CCTUSources RELATIVE ${CMAKE_SOURCE_DIR} Programs/Lang/*.cpp)

add_executable(cctu ${CCTUSources})
target_link_libraries(cctu CthulhuFileSystem)
target_link_libraries(cctu CthulhuCore)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    add_custom_target(
        doc
        COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf
        COMMENT "Generating documentation using Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the Cthulhu documentation")
endif(DOXYGEN_FOUND)
