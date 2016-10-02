include_directories(
  ${SDL2_INCLUDE_DIR}
  ${SDL2IMAGE_INCLUDE_DIR}
  ${SDL2TTF_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/SAS_System/include
  ${PROJECT_SOURCE_DIR}/SAS_System/include/Rendering
  ${PROJECT_SOURCE_DIR}/SAS_System/include/Input
  ${PROJECT_SOURCE_DIR}/SAS_GUI/include
)

message("${PROJECT_SOURCE_DIR}")
file( GLOB SRCS 
	${PROJECT_SOURCE_DIR}/SAS_Test/src/*.cpp
)

add_executable(SAS_Test ${SRCS} )

target_link_libraries (SAS_Test ${SDL2_LIBRARY} ${SDL2IMAGE_LIB} ${SDL2TTF_LIB} SAS_System SAS_GUI)