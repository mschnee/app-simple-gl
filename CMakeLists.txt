project (Sprites)

cmake_minimum_required (VERSION 3.4.0)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -std=c++11")
endif()
include (ExternalProject)

set (Sprites_Output_Path ${CMAKE_CURRENT_BINARY_DIR}/out)
set (Sprites_Runtime_Path ${Sprites_Output_Path}/bin)
set (Sprites_Library_Path ${Sprites_Output_Path}/lib)
set (Sprites_Archive_Path ${Sprites_Output_Path}/lib)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Sprites_Archive_Path})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Sprites_Library_Path})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Sprites_Runtime_Path})

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${Sprites_Archive_Path})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${Sprites_Library_Path})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Sprites_Runtime_Path})

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${Sprites_Archive_Path})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${Sprites_Library_Path})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Sprites_Runtime_Path})

ExternalProject_Add (EventEmitter-external
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/event-emitter
    INSTALL_DIR ${Sprites_Output_Path}
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
      -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
)

ExternalProject_Add (SFML-external
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/SFML
    INSTALL_DIR ${Sprites_Output_Path}
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
      -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
)

ExternalProject_Add (GSL-external
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/gsl
    INSTALL_DIR ${Sprites_Output_Path}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Add (rapidjson-external
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/rapidjson
    INSTALL_DIR ${Sprites_Output_Path}
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
      -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
)

ExternalProject_Add (googletest-external
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/googletest
    INSTALL_DIR ${Sprites_Output_Path}
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
      -DGTEST_CREATE_SHARED_LIBRARY:BOOL=TRUE
      -DBUILD_SHARED_LIBS:BOOL=TRUE
      -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    STEP_TARGETS post_install
)

if (WIN32)
ExternalProject_Add_Step(googletest-external post_install
    DEPENDEES install
    LOG 1
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Sprites_Library_Path}/gmock.dll ${Sprites_Runtime_Path}/gmock.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Sprites_Library_Path}/gmock_main.dll ${Sprites_Runtime_Path}/gmock_main.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Sprites_Library_Path}/gtest.dll ${Sprites_Runtime_Path}/gtest.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Sprites_Library_Path}/gtest_main.dll ${Sprites_Runtime_Path}/gtest_main.dll
)
set_property (TARGET googletest-external-post_install PROPERTY FOLDER "External")
endif()

add_custom_target(all-external-projects
    DEPENDS googletest-external rapidjson-external GSL-external SFML-external EventEmitter-external
)

set_property (TARGET all-external-projects PROPERTY FOLDER "External")
set_property (TARGET googletest-external PROPERTY FOLDER "External")
set_property (TARGET rapidjson-external PROPERTY FOLDER "External")
set_property (TARGET GSL-external PROPERTY FOLDER "External")
set_property (TARGET SFML-external PROPERTY FOLDER "External")
set_property (TARGET EventEmitter-external PROPERTY FOLDER "External")

include_directories (
    ${Sprites_Output_Path}/include
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/external/gsl/include
)
link_directories (${Sprites_Runtime_Path} ${Sprites_Library_Path})

add_subdirectory (src)
add_subdirectory (test)

add_custom_target(build-all-externals
    DEPENDS googletest-external rapidjson-external GSL-external SFML-external EventEmitter-external
)