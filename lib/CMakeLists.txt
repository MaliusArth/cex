include(/home/maliusarth/projects/msc/thesis/cex/shared.cmake)
project(CEX)

set(LLVM_LINK_COMPONENTS
	Support
)

add_clang_library( ${PROJECT_NAME}
	src/libCEX.cpp

	LINK_LIBS
	clangBasic
	clangASTMatchers
)

target_include_directories( ${PROJECT_NAME}

	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>

	PRIVATE
	${MALIUS_ROOT}/libs/core/include
)

# add_subdirectory(
	# src
	# build.dir
# )

# target_link_directories()