set (_headers
    StringUtil.h
)

set (_sources
	StringUtil.cpp
)

add_library(util ${_sources} ${_headers})
set_property (TARGET util PROPERTY CXX_STANDARD 11)
set_property (TARGET util PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property (TARGET util PROPERTY FOLDER "Application")