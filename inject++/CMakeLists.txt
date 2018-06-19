set(
	MALIUS_LIBS /home/maliusarth/projects/msc/thesis/inject++/malius/libs
)

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