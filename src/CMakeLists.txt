add_executable (Sprites main.cpp)
add_dependencies (Sprites build-all-externals)
set_property (TARGET Sprites PROPERTY CXX_STANDARD 14)
set_property (TARGET Sprites PROPERTY CXX_STANDARD_REQUIRED TRUE)
add_subdirectory (Backend)
add_subdirectory (Frontend)
add_subdirectory (fs)
add_subdirectory (Util)

target_link_libraries (Sprites
	backend
	frontend
	fs
	util

	# externals
	debug EventEmitter
	optimized EventEmitter
	pthread
	c++
)

add_dependencies (backend EventEmitter-external SFML-external GSL-external rapidjson-external)
add_dependencies (frontend EventEmitter-external SFML-external GSL-external rapidjson-external)
add_dependencies (fs EventEmitter-external SFML-external GSL-external rapidjson-external)