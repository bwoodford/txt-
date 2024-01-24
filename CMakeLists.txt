cmake_minimum_required(VERSION 3.10)

project(txtpp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set binary and library output paths
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Output compile_commands.json for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SOURCE_FILES 
    src/main.cpp
    src/terminal/Terminal.cpp
    src/editor/Cursor.cpp
    src/editor/Editor.cpp
    src/editor/structures/Row.cpp
    src/editor/structures/Buffer.cpp
    src/editor/structures/Node.cpp
    src/exceptions/terminal/TerminalException.cpp
    src/exceptions/app/AppException.cpp
)

# Include directories
include_directories(
    src/terminal
    src/editor
    src/editor/structures
    src/exceptions/terminal
    src/exceptions/app
)

# Create an executable
add_executable(txtpp ${SOURCE_FILES})

