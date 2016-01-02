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

if(WIN32)
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
else()
    target_link_libraries (frontend
        debug sfml-window
        optimized sfml-window
        debug sfml-graphics
        optimized sfml-graphics
        debug sfml-audio
        optimized sfml-audio
        openal
        vorbis
        vorbisfile
        ogg
    )
endif()
