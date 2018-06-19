set(LLVM_LINK_COMPONENTS
	support
)

add_clang_library(Inject
	libInject.cpp
	
	LINK_LIBS
	clangBasic
	clangASTMatchers
)