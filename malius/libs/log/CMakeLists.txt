
include_directories(
	include
	../core/include
	../config/include
)

#[[
add_subdirectory(
	src
	build.dir
)
]]

add_library(MALog
	src/Logger.cpp
)