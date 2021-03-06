set (_test_sources
	main.cpp
)
set(_test_fixtures
	fixtures/test.json
)


add_executable (test_fs ${_test_sources} ${_test_fixtures})
add_dependencies (test_fs googletest-external test_sanity fs test_fs_copy_fixtures)

# Copy fixtures to be relative to the output of the test executables
add_custom_target (test_fs_copy_fixtures
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/test/fs/fixtures ${Sprites_Runtime_Path}/test_fixtures/fs
)

# Keep the folders clean
set_property (TARGET test_fs PROPERTY FOLDER "Unit Tests/fs")
set_property (TARGET test_fs_copy_fixtures PROPERTY FOLDER "Unit Tests/fs")

SOURCE_GROUP(Fixtures ${_test_fixtures})

target_link_libraries (test_fs
	gtest fs
)

add_test(cmake_test_fs test_fs)