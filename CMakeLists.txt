cmake_minimum_required(VERSION 3.10)

set(INSTALL_FOLDER C:/CustomCommands/bin)

# set the project name
project(dire VERSION 1.0)

configure_file(config.h.in config.h)

# add the executable
FILE(GLOB MY_SRCS "./*.cpp")
add_executable(dire ${MY_SRCS})
set_property(TARGET dire PROPERTY CXX_STANDARD 17)
add_custom_command(TARGET dire 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dire> ${INSTALL_FOLDER})

target_include_directories(dire PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

