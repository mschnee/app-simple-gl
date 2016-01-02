add_executable (Repair Repair.cpp Events/events.h)

set_property (TARGET Repair PROPERTY CXX_STANDARD 14)
set_property (TARGET Sprites PROPERTY CXX_STANDARD_REQUIRED TRUE)

target_link_libraries (Repair
	fs
	util
	EventEmitter
)


