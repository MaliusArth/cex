include_directories(
	include
	../core/include
	../log/include
)

#[[
add_subdirectory(
	src
)
]]

add_library(MAConfig
	src/ConfigSettingInt.cpp
)