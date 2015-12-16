set (_headers
    fs.h
	FileReader.h
	FileWriter.h
    Response.h
)

set (_sources
	FileReader.cpp
	FileWriter.cpp
    Response.cpp
)

add_library(fs ${_sources} ${_headers})
set_property (TARGET fs PROPERTY FOLDER "Application")