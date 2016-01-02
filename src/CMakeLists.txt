add_executable (Sprites main.cpp)

add_dependencies (Sprites all-external-projects backend frontend fs util)
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
	EventEmitter
    rapidjson
)

add_dependencies (backend all-external-projects)
add_dependencies (frontend all-external-projects)
add_dependencies (fs all-external-projects)