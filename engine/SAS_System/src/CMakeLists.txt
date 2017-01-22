include_directories(
  ${SDL2_INCLUDE_DIR}
  ${SDL2IMAGE_INCLUDE_DIR}
  ${SDL2TTF_INCLUDE_DIR}	
  ${Boost_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/SAS_System/include
  ${PROJECT_SOURCE_DIR}/SAS_System/include/Rendering
  ${PROJECT_SOURCE_DIR}/SAS_System/include/Input
  ${PROJECT_SOURCE_DIR}/SAS_Utils/include
)

message("${PROJECT_SOURCE_DIR}")
file( GLOB SRCS 
	${PROJECT_SOURCE_DIR}/SAS_System/include/*.h
	${PROJECT_SOURCE_DIR}/SAS_System/include/Rendering/*.h
	${PROJECT_SOURCE_DIR}/SAS_System/include/Input/*.h
	${PROJECT_SOURCE_DIR}/SAS_System/src/*.cpp
	${PROJECT_SOURCE_DIR}/SAS_System/src/Rendering/*.cpp
	${PROJECT_SOURCE_DIR}/SAS_System/src/Input/*.cpp
)

#SET( CMAKE_CXX_FLAGS "-g -std=c++11 -DASIO_STANDALONE")

add_library(SAS_System ${SRCS} )

target_link_libraries (SAS_System ${SDL2_LIBRARY} ${SDL2IMAGE_LIB} ${SDL2TTF_LIB} SAS_Utils)

foreach(FILE ${SRCS}) 
	# Get the directory of the source file
	get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

	# Remove common directory prefix to make the group
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	string(REPLACE "${PROJECT_SOURCE_DIR}/SAS_System/include" "" GROUP "${GROUP}")

	# Make sure we are using windows slashes
	string(REPLACE "/" "\\" GROUP "${GROUP}")

	# Group into "Source Files" and "Header Files"
	if ("${FILE}" MATCHES ".*\\.cpp")
	   set(GROUP "Source Files${GROUP}")
	elseif("${FILE}" MATCHES ".*\\.h")
	   set(GROUP "Header Files${GROUP}")
	endif()

	source_group("${GROUP}" FILES "${FILE}")
endforeach()