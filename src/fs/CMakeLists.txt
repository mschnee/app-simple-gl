set (_headers
	File.h
)

set (_sources
	File.cpp
)

add_library(fs ${_sources} ${_headers})
set_property (TARGET fs PROPERTY FOLDER "Application") 