include_directories(
  ${PROJECT_SOURCE_DIR}/SAS_Rendering/include
  ${SDL2_INCLUDE_DIR}
  ${SDL2IMAGE_INCLUDE_DIR}
  ${SDL2TTF_INCLUDE_DIR}
)

message("${PROJECT_SOURCE_DIR}")
file( GLOB SRCS 
	${PROJECT_SOURCE_DIR}/SAS_Rendering/include/*.h
	${PROJECT_SOURCE_DIR}/SAS_Rendering/src/*.cpp
)

#SET( CMAKE_CXX_FLAGS "-g -std=c++11 -DASIO_STANDALONE")

add_library(SAS_Rendering STATIC ${SRCS} )

target_link_libraries (SAS_Rendering LINK_PUBLIC ${SDL2_LIBRARY} ${SDL2IMAGE_LIB} ${SDL2TTF_LIB})