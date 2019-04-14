cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(Cthulhu CXX)

#turns out part of cmake is in fact busted
#so we have to do this to enable C++17 instead
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

#build in release mode to enable optimizations
option(RELEASE "RELEASE" OFF)
if(RELEASE)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
    endif()
endif()

#build in debug mode to enable all the stack trace stuff
option(DEBUG "DEBUG" OFF)
if(DEBUG)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fsanitize=address")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DEBUG:FULL")
    endif()
endif()

if(RELEASE AND DEBUG)
    message(FATAL_ERROR "Release and debug modes are incompatible")
endif()

#force CTU_INLINE to always inline
option(FORCEINLINE "FORCEINLINE" OFF)
if(FORCEINLINE)
    add_compile_definitions(CTU_FORCEINLINE)
endif()



#enable the use of native instructions
option(NATIVE "NATIVE" ON)
if(NATIVE)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()
endif()



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Cthulhu)

file(
    GLOB_RECURSE 
    CthulhuCoreSources 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Cthulhu/Core/*.cpp
)

add_library(CthulhuCore STATIC
    ${CthulhuCoreSources}
)

file(
    GLOB_RECURSE
    CthulhuGraphicsSourcesOS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Cthulhu/Graphics/${CMAKE_SYSTEM_NAME}/*.*
)

file(
    GLOB
    CthulhuGraphicsSources
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Cthulhu/Graphics/*.cpp
)

set(CthulhuGraphicsSources ${CthulhuGraphicsSources} ${CthulhuGraphicsSourcesOS})

add_library(CthulhuGraphics STATIC
    ${CthulhuGraphicsSources}
)

target_link_libraries(CthulhuGraphics CthulhuCore)

if (APPLE)
    target_link_libraries(
        CthulhuGraphics
        "-framework Cocoa"
        "-framework Metal"
        "-framework MetalKit"
    )
endif()

file(
    GLOB_RECURSE 
    CthulhuFileSystemSources 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Cthulhu/FileSystem/*.cpp
)

add_library(CthulhuFileSystem STATIC
    ${CthulhuFileSystemSources}
)

enable_testing()

add_executable(StringTest Tests/Core/Collections/String.cpp)
target_link_libraries(StringTest CthulhuCore)
add_test(StringTest "StringTest")


option(BUILD_DOC "Build documentation" OFF)

if(BUILD_DOC)
	find_package(Doxygen)
endif()

if(DOXYGEN_FOUND AND BUILD_DOC)
    file(MAKE_DIRECTORY Docs)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    configure_file(${DOXYGEN_OUT} @ONLY)

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating docs..."
        VERBATIM
    )
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate documentation")
endif()