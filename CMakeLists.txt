project (Sprites)

cmake_minimum_required (VERSION 3.4.0)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)
include (ExternalProject)

ExternalProject_Add (EventEmitter-external
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/event-emitter
	INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/external
	CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add (SFML-external
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/SFML
	INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/external
	CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add (GSL-external
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/gsl
	INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/external
	CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add (rapidjson-external
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/rapidjson
	INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/external
	CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

include_directories (
	${CMAKE_CURRENT_BINARY_DIR}/external/include 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/external/gsl/include
)
link_directories    (${CMAKE_CURRENT_BINARY_DIR}/external/bin ${CMAKE_CURRENT_BINARY_DIR}/external/lib)

add_subdirectory (src)

add_dependencies (Sprites EventEmitter-external SFML-external GSL-external rapidjson-external)
