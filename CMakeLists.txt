cmake_minimum_required(VERSION 3.10)
project(AccountingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/User.cpp
    src/Transaction.cpp
    src/AccountingSystem.cpp
    src/Statistics.cpp
    src/Visualization.cpp
)

# Create executable
add_executable(accounting_system ${SOURCES})

# Enable warnings
if(MSVC)
    target_compile_options(accounting_system PRIVATE /W4)
else()
    target_compile_options(accounting_system PRIVATE -Wall -Wextra -Wpedantic)
endif()
