set (_sources

)

set (_headers
	Path.h
	IPath.h
)

if (WIN32)
	list (APPEND ${_headers}
		Path_Win.h
	)
	list (APPEND ${_sources}
		Path_Win.cpp
	)
elseif(MACOS)
	list (APPEND ${_headers}
		Path_Mac.h
	)
	list (APPEND ${_sources}
		Path_Mac.cpp
	)
else()
	list (APPEND ${_headers}
		Path_Linux.h
	)
	list (APPEND ${_sources}
		Path_Linux.cpp
	)
endif()

add_library(os
	${_headers}
	${_sources}
)

set_property (TARGET os PROPERTY CXX_STANDARD 14)
set_property (TARGET os PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property (TARGET os PROPERTY FOLDER "Application")