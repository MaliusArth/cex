include_directories(
	include
	../lib/include
	${MALIUS_LIBS}/core/include
	${MALIUS_LIBS}/config/include
	${MALIUS_LIBS}/log/include
)

add_subdirectory(
	src
#	build.dir
)
