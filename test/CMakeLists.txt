enable_testing()
set (_test_sources
	main.cpp
)

add_executable (test_sanity main.cpp)
add_dependencies (test_sanity build-all-externals)

set_property (TARGET test_sanity PROPERTY FOLDER "Unit Tests")
target_link_libraries (test_sanity 
	gtest
)


add_test(cmake_test_sanity test_sanity)

add_subdirectory (fs)