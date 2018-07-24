set(LLVM_LINK_COMPONENTS
	# ExecutionEngine
	# Core
	Interpreter
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

	# ExecutionEngine Target Analysis ProfileData RuntimeDyld Object MCParser BitReader MC Core BinaryFormat Support Demangle

	X86Disassembler
	X86AsmParser
	X86CodeGen
	X86Desc
	X86Info
	X86AsmPrinter
	X86Utils
	GlobalISel
	SelectionDAG
	AsmPrinter
	DebugInfoCodeView
	DebugInfoMSF
	CodeGen
	ScalarOpts
	InstCombine
	TransformUtils
	BitWriter
	MCDisassembler
	MCJIT
	ExecutionEngine
	Target
	Analysis
	ProfileData
	RuntimeDyld
	Object
	MCParser
	BitReader
	MC
	Core
	BinaryFormat
	Support
	Demangle
	# nativecodegen

)