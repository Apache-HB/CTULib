cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(Cthulhu)

include_directories(${CMAKE_SOURCE_DIR}/Cthulhu)

file(GLOB_RECURSE CthulhuCoreSources RELATIVE ${CMAKE_SOURCE_DIR} Cthulhu/Core/*.cpp)

add_library(CthulhuCore STATIC
    ${CthulhuCoreSources}
)

#turns out part of cmake is in fact busted, 
#so we have to do this to enable C++17 instead
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

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

if (APPLE)
    #TODO: for some reason this generates a shedload of linking warnings
    #maybe theres a workaround that could be applied?
    target_link_libraries(
        CthulhuGraphics
        "-framework Cocoa"
        "-framework Metal"
        "-framework MetalKit"
    )
endif (APPLE)

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
    message("Doxygen needs to be installed to generate the Cthulhu documentation")
endif(DOXYGEN_FOUND)
