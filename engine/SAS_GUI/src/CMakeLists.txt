include_directories(
	${PROJECT_SOURCE_DIR}/SAS_GUI/include
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/GUIComponents
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/GUIDynamics
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/GUIViews
	${PROJECT_SOURCE_DIR}/SAS_System/include/
	${PROJECT_SOURCE_DIR}/SAS_Utils/include/
	${SDL2_INCLUDE_DIR}
	${SDL2IMAGE_INCLUDE_DIR}
	${SDL2TTF_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
)

file( GLOB SRCS 
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/*.h
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/GUIComponents/*.h
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/GUIDynamics/*.h
	${PROJECT_SOURCE_DIR}/SAS_GUI/include/GUIViews/*.h
	${PROJECT_SOURCE_DIR}/SAS_GUI/src/*.cpp
	${PROJECT_SOURCE_DIR}/SAS_GUI/src/GUIComponents/*.cpp
)

#SET( CMAKE_CX_xFLAGS "-g -std=c++11 -DASIO_STANDALONE")

add_library(SAS_GUI 
	${SRCS} 
)

target_link_libraries (SAS_GUI LINK_PUBLIC SAS_System SAS_Utils)

foreach(FILE ${SRCS}) 
	# Get the directory of the source file
	get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

	# Remove common directory prefix to make the group
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	string(REPLACE "${PROJECT_SOURCE_DIR}/SAS_GUI/include" "" GROUP "${GROUP}")

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