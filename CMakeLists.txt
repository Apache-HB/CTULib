cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(Cthulhu CXX)

#turns out part of cmake is in fact busted
#so we have to do this to enable C++17 instead
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

# ========================================================
#                       [ Core ]
# ========================================================

#add base include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Cthulhu)

#collect all files in the core library
file(GLOB_RECURSE CORE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Cthulhu/Core/*.cpp)
file(GLOB_RECURSE CORE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Cthulhu/Core/*.h)

#add the core library as a target to build
add_library(Core STATIC ${CORE_SOURCES})

#install the core library so people can link to it
install(TARGETS Core DESTINATION bin/Cthulhu)

#install the headers so people can include the library
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Cthulhu/Core DESTINATION include/Cthulhu)

# ========================================================
#                      [ FileSystem ]
# ========================================================

file(GLOB_RECURSE FILE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Cthulhu/FileSystem/*.cpp)
file(GLOB_RECURSE FILE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Cthulhu/FileSystem/*.h)

add_library(FileSystem STATIC ${FILE_SOURCES})

# the filesystem relies on core
target_link_libraries(FileSystem Core)

install(TARGETS FileSystem DESTINATION bin/Cthulhu)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Cthulhu/FileSystem DESTINATION include/Cthulhu)

# file(
#     GLOB_RECURSE
#     CthulhuGraphicsSourcesOS
#     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#     Cthulhu/Graphics/${CMAKE_SYSTEM_NAME}/*.*
# )

# file(
#     GLOB
#     CthulhuGraphicsSources
#     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#     Cthulhu/Graphics/*.cpp
# )

# set(CthulhuGraphicsSources ${CthulhuGraphicsSources} ${CthulhuGraphicsSourcesOS})

# add_library(CthulhuGraphics STATIC
#     ${CthulhuGraphicsSources}
# )

# set_target_properties(CthulhuGraphics PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

# target_link_libraries(CthulhuGraphics CthulhuCore)

# if (APPLE)
#     target_link_libraries(
#         CthulhuGraphics
#         "-framework Cocoa"
#         "-framework Metal"
#         "-framework MetalKit"
#     )
# endif()

# option(BUILD_GUI "Build CthulhuGraphics" ON)

# if(BUILD_GUI)
#     install(TARGETS CthulhuGraphics DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release OPTIONAL)
# endif()

# enable_testing()

# #Core/Collections/String
# add_executable(StringTest Tests/Core/Collections/String.cpp)
# target_link_libraries(StringTest CthulhuCore)
# add_test(StringTest "StringTest")

# option(BUILD_DOC "Build documentation" OFF)

# if(BUILD_DOC)
# 	find_package(Doxygen)
# endif()

# if(DOXYGEN_FOUND AND BUILD_DOC)
#     file(MAKE_DIRECTORY Docs)
#     set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

#     configure_file(${DOXYGEN_OUT} @ONLY)

#     add_custom_target(
#         docs
#         COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#         COMMENT "Generating docs..."
#         VERBATIM
#     )
# else(DOXYGEN_FOUND)
#     message("Doxygen needs to be installed to generate documentation")
# endif()