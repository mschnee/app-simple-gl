set (_headers
	WindowController.h
	SceneController.h
)
set (_sources
	WindowController.cpp
	SceneController.cpp
)

add_library (frontend ${_headers} ${_sources})
set_property (TARGET frontend PROPERTY CXX_STANDARD 11)
set_property (TARGET frontend PROPERTY FOLDER "Application")

if (WIN32)
	set (OpenAlLibName openal32)
else()
	set (OpenAlLibName openal)
endif()

target_link_libraries (frontend
	debug sfml-window
	optimized sfml-window
	debug sfml-graphics
	optimized sfml-graphics
	debug sfml-audio
	optimized sfml-audio
	${OpenAlLibName}
	vorbis
	vorbisfile
	ogg
)
