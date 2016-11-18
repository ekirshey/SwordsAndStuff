include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2IMAGE_INCLUDE_DIR}
	${SDL2TTF_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/SAS_System/include
	${PROJECT_SOURCE_DIR}/SAS_System/include/Rendering
	${PROJECT_SOURCE_DIR}/SAS_System/include/Input
	${PROJECT_SOURCE_DIR}/SAS_GUI/include
	${PROJECT_SOURCE_DIR}/SAS/include/
	${PROJECT_SOURCE_DIR}/SAS/include/Components
	${PROJECT_SOURCE_DIR}/SAS/include/Config
	${PROJECT_SOURCE_DIR}/SAS/include/DataManagement
	${PROJECT_SOURCE_DIR}/SAS/include/ECSFramework
	${PROJECT_SOURCE_DIR}/SAS/include/GameMechanics
	${PROJECT_SOURCE_DIR}/SAS/include/GameMechanics/Spells
	${PROJECT_SOURCE_DIR}/SAS/include/GameStates
	${PROJECT_SOURCE_DIR}/SAS/include/GameStates/StateFramework
	${PROJECT_SOURCE_DIR}/SAS/include/GameStates/States
	${PROJECT_SOURCE_DIR}/SAS/include/GameWorld
	${PROJECT_SOURCE_DIR}/SAS/include/GameWorld/Cities
	${PROJECT_SOURCE_DIR}/SAS/include/GameWorld/Lore
	${PROJECT_SOURCE_DIR}/SAS/include/SubSystems
	${PROJECT_SOURCE_DIR}/SAS/include/Systems
	${PROJECT_SOURCE_DIR}/SAS/include/Types
	${PROJECT_SOURCE_DIR}/SAS/include/Types/AITypes
	${PROJECT_SOURCE_DIR}/SAS/include/Utilities
)

file( GLOB SRCS 
	#Includes
	${PROJECT_SOURCE_DIR}/SAS/include/Components/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/Config/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/DataManagement/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/ECSFramework/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameMechanics/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameMechanics/Spells/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameStates/StateFramework/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameStates/States/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameWorld/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameWorld/Cities/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/GameWorld/Lore/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/SubSystems/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/Systems/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/Types/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/Types/AITypes/*.h
	${PROJECT_SOURCE_DIR}/SAS/include/Utilities/*.h
	#Source
	${PROJECT_SOURCE_DIR}/SAS/src/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/Config/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/DataManagement/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/ECSFramework/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameMechanics/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameMechanics/Spells/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameStates/StateFramework/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameStates/States/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameWorld/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameWorld/Cities/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/GameWorld/Lore/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/SubSystems/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/Systems/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/Types/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/Types/AITypes/*.cpp
	${PROJECT_SOURCE_DIR}/SAS/src/Utilities/*.cpp
)

#SET( CMAKE_CXX_FLAGS "-g -std=c++11 -DASIO_STANDALONE")

add_executable(SAS_GAME
	${SRCS} 
)

target_link_libraries (SAS_GAME LINK_PUBLIC ${SDL2_LIBRARY} ${SDL2IMAGE_LIB} ${SDL2TTF_LIB} SAS_System SAS_GUI )

foreach(FILE ${SRCS}) 
	# Get the directory of the source file
	get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

	# Remove common directory prefix to make the group
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	string(REPLACE "${PROJECT_SOURCE_DIR}/SAS/include" "" GROUP "${GROUP}")

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