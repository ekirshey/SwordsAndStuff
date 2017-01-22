include_directories(
	${PROJECT_SOURCE_DIR}/SAS_Utils/include
	${Boost_INCLUDE_DIRS}
)

file( GLOB SRCS 
	${PROJECT_SOURCE_DIR}/SAS_Utils/include/*.h
	${PROJECT_SOURCE_DIR}/SAS_Utils/src/*.cpp
)

add_library(SAS_Utils 
	${SRCS} 
)

foreach(FILE ${SRCS}) 
	# Get the directory of the source file
	get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

	# Remove common directory prefix to make the group
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	string(REPLACE "${PROJECT_SOURCE_DIR}/SAS_Utils/include" "" GROUP "${GROUP}")

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