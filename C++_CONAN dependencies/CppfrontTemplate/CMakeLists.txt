cmake_minimum_required (VERSION 3.27)

project (cpp_template)

find_package (fmt REQUIRED)
find_package (cppfront REQUIRED)

set (cppfront_CMD "${cppfront_PACKAGE_FOLDER_RELEASE}/bin/cppfront")

# Set variable for generated files directory
set(GEN_DIR ${CMAKE_BINARY_DIR}/gen)

# Make directory for generated files
file(MAKE_DIRECTORY ${GEN_DIR})

set(CPP2_SOURCES
    src/main.cpp2
)

# Function to generate a cpp file from a cpp2 file using cppfront
function (generate_cpp cpp2_file)
    get_filename_component(cpp_file ${cpp2_file} NAME_WE)
    set(cpp_file "${cpp_file}.cpp")
    add_custom_command (
        COMMAND ${cppfront_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/${cpp2_file} -o ${GEN_DIR}/${cpp_file}
        DEPENDS ${cpp2_file}
        OUTPUT ${GEN_DIR}/${cpp_file}
        COMMENT "Cppfront: ${cpp2_file} -> ${GEN_DIR}/${cpp_file}"
    )
    set(cpp_file_path ${GEN_DIR}/${cpp_file})
    return(PROPAGATE cpp_file_path)
endfunction()

# Call the function to generate cpp files from cpp2 files
set(GEN_CPP_SOURCES "")
foreach(cpp2_file ${CPP2_SOURCES})
    generate_cpp(${cpp2_file})
    list(APPEND GEN_CPP_SOURCES ${cpp_file_path})
endforeach()

message(STATUS "GEN_CPP_SOURCES: ${GEN_CPP_SOURCES}")

add_executable (cpp_template ${GEN_CPP_SOURCES})

set_property (TARGET cpp_template PROPERTY CXX_STANDARD 20)

target_link_libraries (cpp_template PUBLIC fmt::fmt)
target_link_libraries (cpp_template PUBLIC cppfront::cppfront)
