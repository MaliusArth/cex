add_clang_executable(inject++
	src/main.cpp
	src/config.cpp
	src/CompileTimeRunner.cpp

	# src/FindNamedFunctionAction.cpp
	src/MatchCallbacks/NamedFunctionCallback.cpp
	src/MatchCallbacks/AnnotatedFunctionCallback.cpp
)

target_include_directories(inject++

	# PUBLIC

	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	# ../lib/include
	${MALIUS_LIBS}/core/include
	${MALIUS_LIBS}/config/include
	${MALIUS_LIBS}/log/include
)

target_link_libraries(inject++
  PRIVATE
	clangTooling
	clangBasic
	clangASTMatchers
	# Inject
	MALog
	MAConfig
)

target_compile_options(inject++ PUBLIC $<$<CONFIG:DEBUG>:-fstrict-aliasing -Wstrict-aliasing=2>)
target_compile_options(inject++ PUBLIC $<$<CONFIG:RELEASE>:-fstrict-aliasing -Wstrict-aliasing=2>)
# target_compile_options(inject++ INTERFACE
# 	$<$<OR:$<COMPILER_ID:GNU>,$<COMPILER_ID:Clang>>:-rtti>
# )

install(
	TARGETS inject++
	RUNTIME DESTINATION bin
)


# add_subdirectory(
	# src
#	build.dir
# )
