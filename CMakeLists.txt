include(shared.cmake)

# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(lib)
add_subdirectory(tool)
add_subdirectory(plugin)

# set(
# 	MALIUS_LIBS /home/maliusarth/projects/msc/thesis/inject++/malius/libs
# )

add_subdirectory(
	${MALIUS_ROOT}/libs/core
	${MALIUS_ROOT}/libs/core/build.dir
)

# add_subdirectory(
# 	${MALIUS_ROOT}/libs/predef
# 	${MALIUS_ROOT}/libs/predef/build.dir
# )

add_subdirectory(
	${MALIUS_ROOT}/libs/config
	${MALIUS_ROOT}/libs/config/build.dir
)

add_subdirectory(
	${MALIUS_ROOT}/libs/log
	${MALIUS_ROOT}/libs/log/build.dir
)