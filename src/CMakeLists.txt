add_executable (Sprites main.cpp)
add_subdirectory (Backend)
add_subdirectory (Frontend)
add_subdirectory (fs)

target_link_libraries (Sprites
	backend
	frontend
	fs

	# externals
	debug EventEmitterd
	optimized EventEmitter
)

add_dependencies (backend EventEmitter-external SFML-external GSL-external rapidjson-external)
add_dependencies (frontend EventEmitter-external SFML-external GSL-external rapidjson-external)
add_dependencies (fs EventEmitter-external SFML-external GSL-external rapidjson-external)