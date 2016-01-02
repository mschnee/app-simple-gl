add_executable (Sprites Sprites.cpp Events/events.h)
set_property (TARGET Sprites PROPERTY CXX_STANDARD 14)

set_property (TARGET Sprites PROPERTY CXX_STANDARD_REQUIRED TRUE)

target_link_libraries (Sprites
	backend
	frontend
	fs
	util

	# externals
	EventEmitter
)