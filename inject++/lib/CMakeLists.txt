include_directories(
	include
	${CMAKE_CURRENT_SOURCE_DIR}/../../malius/libs/core/include
)

add_subdirectory(
	src
#	build.dir
)

# link_directories()