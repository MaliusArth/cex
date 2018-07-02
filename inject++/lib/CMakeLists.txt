set(LLVM_LINK_COMPONENTS
	support
)

add_clang_library(Inject
	src/libInject.cpp

	LINK_LIBS
	clangBasic
	clangASTMatchers
)

target_include_directories(Inject

	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>

	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../../malius/libs/core/include
)

# add_subdirectory(
	# src
	# build.dir
# )

# target_link_directories()