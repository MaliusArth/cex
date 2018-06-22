set(
	MALIUS_LIBS /home/maliusarth/projects/msc/thesis/inject++/malius/libs
)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(lib)
add_subdirectory(tool)

add_subdirectory(
	${MALIUS_LIBS}/core
	${MALIUS_LIBS}/core/build.dir
)

add_subdirectory(
	${MALIUS_LIBS}/config
	${MALIUS_LIBS}/config/build.dir
)

add_subdirectory(
	${MALIUS_LIBS}/log
	${MALIUS_LIBS}/log/build.dir
)