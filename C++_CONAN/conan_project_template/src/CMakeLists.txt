# required minimum version of cmake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# TODO add your source files here
set(PROJECTLIB_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy.cpp
    )

# TODO add your header files here
set(PROJECTLIB_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/dummy.h
    )

source_group("Header Files" FILES ${PROJECTLIB_HEADER_FILES})


# set default built type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# Check for clang compiler
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGCXX 1)
endif()

# Cache options
option(USE_STATIC_BOOST "Statically link Boost" ${WIN32})

# configure a header file to pass the version number to the source code

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../project_version.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/project_version.h"
)

#
# Build library for internal use only (unittests)
# TODO uncomment the EXCLUDE_FROM_ALL if your library is only used internally

add_library(projectlib STATIC
    EXCLUDE_FROM_ALL
    ${PROJECTLIB_SOURCE_FILES}
    ${PROJECTLIB_HEADER_FILES}
    )

add_library(internal::projectlib ALIAS projectlib)

target_include_directories(projectlib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(projectlib
      PUBLIC
      -pedantic
      -Wall
      -Wextra
      PRIVATE
      -Werror
      -Wcast-align
      -Wcast-qual
      -Wctor-dtor-privacy
      -Wdisabled-optimization
      -Wformat=2
      -Winit-self
      -Wlogical-op
      -Wmissing-declarations
      -Wmissing-include-dirs
      -Wnoexcept
      -Wold-style-cast
      -Woverloaded-virtual
      -Wredundant-decls
      -Wshadow
      -Wsign-conversion
      -Wsign-promo
      -Wstrict-null-sentinel
      -Wstrict-overflow=5
      -Wswitch-default
      -Wundef
      )

elseif(CMAKE_COMPILER_IS_CLANGCXX)
  target_compile_options(projectlib
      PUBLIC
      -Weverything
      -Wno-c++98-compat
      -Wno-padded
      PRIVATE
      -Werror
      )
endif(CMAKE_COMPILER_IS_GNUCXX)

# Define some common C++11 features
# TODO uncomment the C++11/14 features you use
target_compile_features(projectlib
    PUBLIC
    #   cxx_aggregate_default_initializers
    #   cxx_alias_templates
    #   cxx_alignas
    #   cxx_alignof
    #   cxx_attributes
    #   cxx_attribute_deprecated
    cxx_auto_type
    #   cxx_binary_literals
    #   cxx_constexpr
    #   cxx_contextual_conversions
    #   cxx_decltype_incomplete_return_types
    #   cxx_decltype
    #   cxx_decltype_auto
    #   cxx_default_function_template_args
    cxx_defaulted_functions
    cxx_defaulted_move_initializers
    cxx_delegating_constructors
    cxx_deleted_functions
    #   cxx_digit_separators
    #   cxx_enum_forward_declarations
    #   cxx_explicit_conversions
    #   cxx_extended_friend_declarations
    #   cxx_extern_templates
    cxx_final
    #   cxx_func_identifier
    #   cxx_generalized_initializers
    #   cxx_generic_lambdas
    #   cxx_inheriting_constructors
    #   cxx_inline_namespaces
    cxx_lambdas
    #   cxx_lambda_init_captures
    #   cxx_local_type_template_args
    #   cxx_long_long_type
    #   cxx_noexcept
    #   cxx_nonstatic_member_init
    cxx_nullptr
    cxx_override
    cxx_range_for
    #   cxx_raw_string_literals
    #   cxx_reference_qualified_functions
    #   cxx_relaxed_constexpr
    #   cxx_return_type_deduction
    #   cxx_right_angle_brackets
    cxx_rvalue_references
    #   cxx_sizeof_member
    cxx_static_assert
    cxx_strong_enums
    #   cxx_thread_local
    #   cxx_trailing_return_types
    #   cxx_unicode_literals
    #   cxx_uniform_initialization
    #   cxx_unrestricted_unions
    #   cxx_user_literals
    #   cxx_variable_templates
    #   cxx_variadic_macros
    #   cxx_variadic_templates
    #   cxx_template_template_parameters
    )

if(WIN32)
  if(MSVC)
    target_compile_options(projectlib
        PUBLIC
        /EHsc
        )
  endif(MSVC)
  target_compile_definitions(projectlib
      PUBLIC
      _WIN32_WINNT=0x0502
      )
endif(WIN32)

#
# Build main executable
#

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )
add_executable(${PROJECT_NAME}::exe ALIAS ${PROJECT_NAME})

if(USE_STATIC_BOOST)
  set(Boost_USE_STATIC_LIBS ON)
else(USE_STATIC_BOOST)
  target_compile_definitions(${PROJECT_NAME}
      PRIVATE
      BOOST_ALL_DYN_LINK
      )
endif(USE_STATIC_BOOST)

#
# with Boost
#
find_package(Boost COMPONENTS program_options)

if(Boost_Found)
  target_include_directories(${PROJECT_NAME}
      SYSTEM
      PUBLIC
      ${Boost_INCLUDE_DIRS}
      )

  target_link_libraries(${PROJECT_NAME}
      ${Boost_LIBRARIES}
      internal::projectlib
      )
else()
  target_link_libraries(${PROJECT_NAME}
      ${CONAN_LIBS}
      internal::projectlib
      )
endif()

#
# Build library with coverage support
#

if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
  add_library(projectlib-cov
      EXCLUDE_FROM_ALL
      ${PROJECTLIB_SOURCE_FILES}
      ${PROJECTLIB_HEADER_FILES}
      )
  add_library(internal::projectlib-cov ALIAS projectlib-cov)

  target_compile_options(projectlib-cov
      PUBLIC
      -fprofile-arcs
      -ftest-coverage
      -pedantic
      -Wall
      -Wextra
      PRIVATE
      -Werror
      )

  target_include_directories(projectlib-cov
      PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/../include
      )

  target_compile_features(projectlib-cov
      PUBLIC
      cxx_auto_type
      cxx_constexpr
      cxx_defaulted_functions
      cxx_defaulted_move_initializers
      cxx_delegating_constructors
      cxx_deleted_functions
      cxx_final
      cxx_lambdas
      cxx_nullptr
      cxx_override
      cxx_range_for
      cxx_rvalue_references
      cxx_strong_enums
      )

  export(TARGETS projectlib projectlib-cov NAMESPACE internal:: FILE ${CMAKE_CURRENT_SOURCE_DIR}/../project-export.cmake)
else(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
  export(TARGETS projectlib NAMESPACE internal:: FILE ${CMAKE_CURRENT_SOURCE_DIR}/../project-export.cmake)
endif(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
