set (_headers
    fs.h
	FileReader.h
    Response.h
)

set (_sources
	FileReader.cpp
    Response.cpp
)

add_library(fs ${_sources} ${_headers})
set_property (TARGET fs PROPERTY FOLDER "Application")