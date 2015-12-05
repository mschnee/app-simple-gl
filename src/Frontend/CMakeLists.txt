set (_headers
	WindowController.h
	SceneController.h
)
set (_sources
	WindowController.cpp
	SceneController.cpp
)

add_library (frontend ${_headers} ${_sources})
set_property (TARGET frontend PROPERTY FOLDER "Application")

target_link_libraries (frontend
	debug sfml-window-d
	optimized sfml-window
	debug sfml-graphics-d
	optimized sfml-graphics
	debug sfml-audio-d
	optimized sfml-audio
	openal32
	vorbis
	vorbisfile
	ogg
)
