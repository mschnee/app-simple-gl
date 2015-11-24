add_executable (Sprites main.cpp)
add_subdirectory (Backend)
add_subdirectory (Frontend)

target_link_libraries (Sprites backend 
	debug EventEmitterd 
	optimized EventEmitter
)
