set (_headers 
	WindowManager.h
	SceneManager.h
)
set (_sources
	WindowManager.cpp
	SceneManager.cpp
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
	openal
	vorbis
	vorbisfile
	ogg
)
