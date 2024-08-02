cmake_minimum_required(VERSION 3.16)
project(coingetter LANGUAGES CXX)

# Set output directory for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/)

# Build dynamic libraries for SFML to link
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BUILD_TYPE DEBUG)
add_definitions(-DSFML_STATIC)

# Pull SFML if on Windows
add_subdirectory(SFML)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/includes/controllers
    ${CMAKE_SOURCE_DIR}/includes/core
    ${CMAKE_SOURCE_DIR}/includes/entities
    ${CMAKE_SOURCE_DIR}/includes/ui
    ${CMAKE_SOURCE_DIR}/includes/utils
)

# Link directory for external library dependencies
link_directories(${CMAKE_SOURCE_DIR}/SFML/extlibs/libs-mingw/x64)

# Source files to compile
file(GLOB SOURCES "src/**/*.cpp" "src/*.cpp")

# Handle icon stuff only on Windows
if (WIN32)
    # Ensure output directory for icon.o exists
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

    add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/output/icon.o
        COMMAND windres ${CMAKE_SOURCE_DIR}/resources/resources.rc -o ${CMAKE_SOURCE_DIR}/output/icon.o
        DEPENDS ${CMAKE_SOURCE_DIR}/resources/resources.rc
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/resources
        COMMENT "Generating icon.o"
    )

    add_custom_target(
        generate_icon ALL
        DEPENDS ${CMAKE_SOURCE_DIR}/output/icon.o
    )

    add_executable(coingetter ${SOURCES} ${CMAKE_SOURCE_DIR}/output/icon.o)
else (WIN32)
    add_executable(coingetter ${SOURCES})
endif (WIN32)

# Add flags to enforce static linking
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Set the path to the static winpthread library
# set(WINPTHREAD_STATIC_LIB "C:/msys64/mingw64/lib/libwinpthread.a")  # Adjust the path as necessary

if (WIN32)
    # Link SFML static libraries
    target_link_libraries(
        coingetter PRIVATE
        sfml-window
        sfml-system
        opengl32
        winmm
        gdi32
        sfml-graphics
        sfml-audio
        openal32
        flac
        vorbisenc
        vorbisfile
        vorbis
        ogg
        sfml-network
        ws2_32
        -static-libgcc
        -static-libstdc++
	${WINPTHREAD_STATIC_LIB}
    )
elseif (UNIX)
    target_link_libraries(
        coingetter PRIVATE
        sfml-window
        sfml-system
        sfml-graphics
        sfml-audio
        sfml-network
    )
endif()

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

# Cleanup
add_custom_command(
    TARGET coingetter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/output/icon.o
    COMMENT "Removing icon.o after build"
)
