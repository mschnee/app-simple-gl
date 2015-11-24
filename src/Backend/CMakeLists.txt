set (_headers 
	Application.h
	Settings.h
)
set (_sources
	Application.cpp
	Settings.cpp
)

add_library (backend ${_headers} ${_sources})

set_property (TARGET backend PROPERTY FOLDER "Application") 