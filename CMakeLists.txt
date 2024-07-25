cmake_minimum_required(VERSION 3.25)
project(coingetter LANGUAGES CXX)

# Set output directory for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/)

# Build static libraries for SFML to link
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BUILD_TYPE DEBUG)
set(SFML_STATIC_LIBRARIES TRUE)

# Pull SFML if on Windows
if (WIN32)
    add_subdirectory(sfml)
endif (WIN32)

include_directories(includes/)
file(GLOB SOURCES "src/*.cpp")
add_executable(coingetter ${SOURCES})

# Link SFML static libs
target_link_libraries(coingetter PRIVATE sfml-graphics sfml-window sfml-system sfml-main)

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

install(TARGETS coingetter)
