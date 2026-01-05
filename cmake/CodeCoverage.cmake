find_program(LCOV lcov REQUIRED)
find_program(GENHTML genhtml REQUIRED)

function(add_coverage_target)
    add_custom_target(coverage
        COMMAND ${CMAKE_CTEST_COMMAND}
        COMMAND ${LCOV} --directory . --capture --output-file coverage.info
        COMMAND ${LCOV} --remove coverage.info ${ARGV} --output-file coverage.filtered.info
        COMMAND ${GENHTML} coverage.filtered.info --output-directory coverage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report"
    )
endfunction()

