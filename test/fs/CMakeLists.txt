set (_test_sources
	main.cpp
)

add_executable (test_fs main.cpp)
# Copy fixtures to be relative to the output of the test executables
add_custom_target (test_fs_copy_fixtures
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/test/fs/fixtures ${Sprites_Runtime_Path}/test_fixtures/fs
)

# Keep the folders clean
set_property (TARGET test_fs PROPERTY FOLDER "Unit Tests/fs")
set_property (TARGET test_fs_copy_fixtures PROPERTY FOLDER "Unit Tests/fs")

target_link_libraries (test_fs 
	gtest fs
)
add_dependencies (test_fs googletest-external fs test_fs_copy_fixtures)

add_test(cmake_test_fs test_fs)