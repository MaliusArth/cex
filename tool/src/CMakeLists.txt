#add_clang_executable(inject++
#	main.cpp
#	config.cpp
#	FindNamedFunctionAction.cpp
#	CompileTimeRunner.cpp
#)
#
#target_link_libraries(inject++
#  PRIVATE
#	clangTooling
#	clangBasic
#	clangASTMatchers
#	# Inject
#	MALog
#	MAConfig
#)
#
#install(
#	TARGETS inject++
#	RUNTIME DESTINATION bin
#)
