include( /home/maliusarth/projects/msc/thesis/cex/shared.cmake )
project(CEXPlugin)

# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# set(CMAKE_DEBUG_POSTFIX _d)


# set(LLVM_LINK_COMPONENTS
	# ExecutionEngine
	# Core
	# Interpreter
	# Support
	# System
	# Target
	# X86Info
	# X86AsmPrinter
	# X86AsmParser
	# X86CodeGen
	# X86Desc
	# X86Utils
	# X86Disassembler
	# MC
	# MCDisassembler
	# RuntimeDyld
	# DebugInfoCodeView
	# DebugInfoPDB


	# ExecutionEngine
	# Target
	# Analysis
	# ProfileData
	# RuntimeDyld
	# Object
	# MCParser
	# BitReader
	# MC
	# Core
	# BinaryFormat
	# Support
	# Demangle

	# Interpreter

	# X86Disassembler
	# X86AsmParser
	# X86CodeGen
	# GlobalISel
	# SelectionDAG
	# AsmPrinter
	# DebugInfoCodeView
	# DebugInfoMSF
	# CodeGen
	# ScalarOpts
	# InstCombine
	# TransformUtils
	# BitWriter
	# X86Desc
	# MCDisassembler
	# X86Info
	# X86AsmPrinter
	# X86Utils
	# MCJIT
	# ExecutionEngine
	# Target
	# Analysis
	# ProfileData
	# RuntimeDyld
	# Object
	# MCParser
	# BitReader
	# MC
	# Core
	# BinaryFormat
	# Support
	# Demangle
# )

set(LLVM_LINK_COMPONENTS
	# ExecutionEngine
	# Target
	# Analysis
	# ProfileData
	# RuntimeDyld
	# Object
	# MCParser
	# BitReader
	# MC
	# Core
	# BinaryFormat
	# Support
	Demangle
)

add_llvm_loadable_module( ${PROJECT_NAME}
	# src/AggregationPass.cpp
	src/ExecutionPass.cpp
	# src/TestPass.cpp

	DEPENDS
	intrinsics_gen
	PLUGIN_TOOL
	opt
)

target_include_directories( ${PROJECT_NAME}

	# PUBLIC

	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	# ../lib/include
	# ${MALIUS_LIBS}/core/include
	# ${MALIUS_LIBS}/config/include
	# ${MALIUS_LIBS}/log/include
)

target_compile_options( ${PROJECT_NAME}
	PUBLIC
	# $<$<CONFIG:DEBUG>: -D_DEBUG -UNDEBUG -O0 >
	# $<$<CONFIG:RELEASE>: -O3 >

	# -D_GLIBCXX_USE_CXX11_ABI=0
	# -fstrict-aliasing -Wstrict-aliasing=2

	# -DGTEST_HAS_RTTI=0 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
	# -fPIC -fvisibility-inlines-hidden -Werror=date-time -Werror=unguarded-availability-new
	# -std=c++11 -Wall -W -Wno-unused-parameter -Wwrite-strings -Wcast-qual -Wmissing-field-initializers
	# -pedantic -Wno-long-long -Wcovered-switch-default -Wnon-virtual-dtor -Wdelete-non-virtual-dtor
	# -Wstring-conversion -fcolor-diagnostics -ffunction-sections -fdata-sections
	-fno-exceptions -fno-rtti
)

# target_compile_options(inject++ INTERFACE
# 	$<$<OR:$<COMPILER_ID:GNU>,$<COMPILER_ID:Clang>>:-rtti>
# )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
	# LLVMSystem
	# clangTooling
	# clangBasic
	# clangASTMatchers
	# Inject
	# MALog
	# MAConfig

)

# install(
# 	TARGETS CEXPlugin
# 	RUNTIME DESTINATION bin
# )


# add_subdirectory(
	# src
#	build.dir
# )
