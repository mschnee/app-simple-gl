set (_headers 
	Application.h
	SettingsController.h
)
set (_sources
	Application.cpp
	SettingsController.cpp
)

add_library (backend ${_headers} ${_sources})
set_property (TARGET backend PROPERTY CXX_STANDARD 11)
set_property (TARGET backend PROPERTY FOLDER "Application") 