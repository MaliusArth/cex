include(/home/maliusarth/projects/msc/thesis/cex/shared.cmake)
project(cex)

# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_DEBUG_POSTFIX _d)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include(llvm_libs.cmake)

add_clang_executable( ${PROJECT_NAME}
	src/main.cpp
	src/config.cpp
	src/CompileTimeRunner.cpp

	# src/FindNamedFunctionAction.cpp
	src/MatchCallbacks/NamedFunctionCallback.cpp
	src/MatchCallbacks/AnnotatedFunctionCallback.cpp

	src/JIT.cpp
	src/utils.cpp
)

target_include_directories( ${PROJECT_NAME}
	# PUBLIC

	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	# ../lib/include
	${MALIUS_ROOT}/libs/core/include
	${MALIUS_ROOT}/libs/config/include
	${MALIUS_ROOT}/libs/log/include
)

# link_directories(${CMAKE_BINARY_DIR}/res)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	find_library(MA_CONFIG NAMES MAConfig libMAConfig)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
	find_library(MA_CONFIG NAMES MAConfig libMAConfig PATHS ${MALIUS_ROOT}/install/lib/Release)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

# TODO: make this macro work
# macro(find_malius_library var NAMES name... PATHS path...)
# 	if(CMAKE_BUILD_TYPE STREQUAL Debug)
# 		find_library(var NAMES name... PATHS ${MALIUS_ROOT}/install/lib/Debug)
# 	elseif(CMAKE_BUILD_TYPE STREQUAL Release)
# 		find_library(var NAMES name... PATHS ${MALIUS_ROOT}/install/lib/Release)
# 	endif(CMAKE_BUILD_TYPE STREQUAL Release)
# endmacro(find_malius_library)

# find_malius_library( MA_CONFIG
# 	NAMES MAConfig libMAConfig
# )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
	clangTooling
	clangBasic
	clangASTMatchers
	# Inject
	MALog
	MAConfig

)

# set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib)
# set_target_properties()

target_compile_options( ${PROJECT_NAME} PUBLIC $<$<CONFIG:DEBUG>:-fstrict-aliasing -Wstrict-aliasing=2> )
target_compile_options( ${PROJECT_NAME} PUBLIC $<$<CONFIG:RELEASE>:-fstrict-aliasing -Wstrict-aliasing=2> )
# target_compile_options(inject++ INTERFACE
# 	$<$<OR:$<COMPILER_ID:GNU>,$<COMPILER_ID:Clang>>:-rtti>
# )

set_target_properties( ${PROJECT_NAME}
	PROPERTIES
		DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)


install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
)

# add_subdirectory(
	# src
#	build.dir
# )
