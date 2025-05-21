# Look for an executable called gcovr
find_program(
    GCOVR_EXECUTABLE
    NAMES gcovr
    DOC "Path to gcovr executable"
)

include(FindPackageHandleStandardArgs)

# Handle standard arguments to find_package like REQUIRED and QUIET
find_package_handle_standard_args(Gcovr "Failed to find gcovr executable" GCOVR_EXECUTABLE)
