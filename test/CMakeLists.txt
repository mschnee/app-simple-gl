enable_testing()
set (_test_sources
	main.cpp
)

add_executable (test_sanity main.cpp)
set_property (TARGET test_sanity PROPERTY FOLDER "Unit Tests")
target_link_libraries (test_sanity 
	gtest
)
add_dependencies (test_sanity googletest-external)

add_test(cmake_test_sanity test_sanity)