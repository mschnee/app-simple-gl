set (_headers
    fs.h
	FileReader.h
	FileWriter.h
    Path.h
	os/IPath.h
)

set (_sources
	FileReader.cpp
	FileWriter.cpp
    Path.cpp
)

if (WIN32)
	list(APPEND ${_headers} os/Path_Win.h)
elseif(MACOS)
	list(APPEND ${_headers} os/Path_Mac.h)
else()
	list(APPEND ${_headers} os/Path_Linux.h)
endif()

add_library(fs ${_sources} ${_headers})
add_dependencies (fs rapidjson-external)

set_property (TARGET fs PROPERTY CXX_STANDARD 11)
set_property (TARGET fs PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property (TARGET fs PROPERTY FOLDER "Application")