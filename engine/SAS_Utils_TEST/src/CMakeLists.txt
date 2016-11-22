include_directories(
  ${PROJECT_SOURCE_DIR}/SAS_Utils/include
)

message("${PROJECT_SOURCE_DIR}")
file( GLOB SRCS 
	${PROJECT_SOURCE_DIR}/SAS_Utils_Test/src/*.cpp
)

add_executable(SAS_Utils_Test ${SRCS} )

target_link_libraries (SAS_Utils_Test LINK_PUBLIC SAS_Utils)