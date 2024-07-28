cmake_minimum_required(VERSION 3.25)
project(coingetter LANGUAGES CXX)

# Set output directory for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/)

# Build dynamic libraries for SFML to link
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BUILD_TYPE DEBUG)
add_definitions(-DSFML_STATIC)

# Pull SFML if on Windows
if (WIN32)
    add_subdirectory(sfml)
endif (WIN32)

include_directories(includes/)
link_directories(${CMAKE_SOURCE_DIR}/SFML/extlibs/libs-mingw/x64)
file(GLOB SOURCES "src/*.cpp")
add_executable(coingetter ${SOURCES})

# Link SFML static libraries
target_link_libraries(
    coingetter PRIVATE
    sfml-window
    sfml-system
    opengl32
    winmm
    gdi32
    sfml-graphics
    sfml-system
    sfml-window
    opengl32
    freetype
    sfml-audio
    sfml-system
    openal32
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
    sfml-network
    sfml-system
    ws2_32
    sfml-system
    winmm
)

# Ensure the application is treated as a GUI application
if (WIN32)
    set_target_properties(coingetter PROPERTIES
        WIN32_EXECUTABLE YES
    )
endif (WIN32)

# Debugging output
message(STATUS "SFML libraries linked: ${SFML_LIBRARIES}")
message(STATUS "Project sources: ${SOURCES}")

# Copy resources into output directory
file(COPY fonts/ DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fonts/")
file(COPY sprites/ DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sprites/")
file(COPY sounds/ DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sounds/")

install(TARGETS coingetter)
