set (_headers
    fs.h
	FileReader.h
	FileWriter.h
    Path.h
)

set (_sources
	FileReader.cpp
	FileWriter.cpp
    Path.cpp
)

add_library(fs ${_sources} ${_headers})
set_property (TARGET fs PROPERTY CXX_STANDARD 11)
set_property (TARGET fs PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property (TARGET fs PROPERTY FOLDER "Application")