

// #include style: https://llvm.org/docs/CodingStandards.html#include-style

// Main Module Header
// a.k.a. the header file containing the interfaces a .cpp file implements
// (.h/.cpp pairs)

// Local/Private Headers
// #include "libInject/libInject.h"
// #include "FindNamedFunctionAction.h"
// #include "CompileTimeRunner.h"

// AST includes
#include "MatchCallbacks/AnnotatedFunctionCallback.h"
#include "MatchCallbacks/NamedFunctionCallback.h"
#include "matchers.h"

// IR includes
#include "Actions/EmitBitcodeAction.h"
#include "JIT.h"
#include "utils.h"

#include "tmp.h"
// #include "setupCompilerInstance.h"

// #include "hooks/macro_approach.h"

// External headers
#include <malius/core/lang.hpp>
#include <malius/log/Logger.hpp>

// LLVM project/subproject headers (clang/..., lldb/..., llvm/..., etc)

// Declares clang::SyntaxOnlyAction.
// #include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

// Declares llvm::cl:extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/Frontend/ASTUnit.h"
// #include "clang/Frontend/FrontendAction.h"
#include "clang/CodeGen/CGFunctionInfo.h"
#include "clang/CodeGen/CodeGenAction.h"

#include "llvm/ADT/StringRef.h"

// #include "llvm/Bitcode/BitcodeReader.h"
// #include "llvm/Bitcode/BitcodeWriter.h"
// #include "llvm/Bitcode/BitcodeWriterPass.h"

// #include "clang/Frontend/Utils.h"	// TODO: DependencyFileGenerator |
// DependencyCollector | InitializePreprocessor #include
// "clang/Frontend/CompilerInstance.h" #include "clang/Basic/FileManager.h"
// #include "clang/Lex/Token.h"

// #include "llvm/Support/MemoryBuffer.h"

// #include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
// #include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "llvm/Support/MemoryBuffer.h"

// System #includes
// #include <cstring>	//TODO: TEMP
#include <cassert>
#include <memory>

// using namespace clang;
// using namespace clang::tooling;
// using namespace llvm;

namespace
{
// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory cexCategory("cex Options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp
	commonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

// A help message for the specific tool can be added afterwards.
static llvm::cl::extrahelp moreHelp("\nMore help text...\n\n");

static llvm::cl::opt<std::string>
	runOpt("run", llvm::cl::desc("function to run at compile-time"),
		   llvm::cl::value_desc("file path"), llvm::cl::cat(cexCategory));

// static llvm::cl::opt<unsigned, false, FileSizeParser> maxFileSizeOpt(
// "max-file-size", llvm::cl::desc("Maximum file size to accept"),
// llvm::cl::value_desc("size"), llvm::cl::cat(toolCategory)
// );

// static std::unique_ptr<msc::cex::CExJIT> cexJIT;
} // namespace

//////////////////////////////////////////////////////////////////////

// using namespace msc::ct_exec;
// using namespace msc::ast_match;
// using namespace msc::ast_match::util;

int main(int argc, const char **argv)
{
	// std::printf("main argc: %d\n", argc);

	ma::log::ConsoleLogger logger(ma::log::VerbosityFilterPolicy(2),
								  ma::log::SimpleFormatPolicy(),
								  ma::log::ConsoleWriterPolicy());

	// std::printf("ConsoleLogger\ttabbed \nbroken %s", "freestyla");
	// std::printf("ConsoleLogger\ttabbed %s\n", "freestyla");
	MA_INF0("Main", "cex tool is running.");
	MA_INFO("Main", "cex tool is running.%s", ".. RUN!");

	// ::llvm::cl::ParseCommandLineOptions(argc, argv, "cex compiler\n",
										// &llvm::errs());

	::clang::tooling::CommonOptionsParser optionsParser(argc, argv,
														cexCategory);
	::clang::tooling::ClangTool tool(optionsParser.getCompilations(),
									 optionsParser.getSourcePathList());
	/* 	ClangTool::ClangTool(const CompilationDatabase &Compilations,
						ArrayRef<std::string> SourcePaths,
						std::shared_ptr<PCHContainerOperations> PCHContainerOps)
		: Compilations(Compilations), SourcePaths(SourcePaths),
		PCHContainerOps(std::move(PCHContainerOps)),
		OverlayFileSystem(new vfs::OverlayFileSystem(vfs::getRealFileSystem())),
		InMemoryFileSystem(new vfs::InMemoryFileSystem),
		Files(new FileManager(FileSystemOptions(), OverlayFileSystem)),
		DiagConsumer(nullptr) {
		OverlayFileSystem->pushOverlay(InMemoryFileSystem);
		appendArgumentsAdjuster(getClangStripOutputAdjuster());
		appendArgumentsAdjuster(getClangSyntaxOnlyAdjuster());
		appendArgumentsAdjuster(getClangStripDependencyFileAdjuster());
	} */

	/* 	::clang::StringRef main_stub =
		"//cex includes"
		"int main(int argc, char const **argv)\n"
		"{\n"
		"	//cex func"
		"	return true;\n"
		"}\n";

		tool.mapVirtualFile("path/to/virtual/file", main_stub); */

	// Matching the source code

	// TODO: Split CompileTimeRunner into
	// CompileTimeFunctionFinder
	// CompileTimeFunctionRunner
	// msc::ast_match::CompileTimeRunner ct_runner;
	std::vector<::clang::FunctionDecl *> functionDecls;
	::msc::ast_match::NamedFunctionCallback
		named_function_callback /* (functionDecls) */;
	::msc::ast_match::AnnotatedFunctionCallback annotated_function_callback(
		"cex_run") /* (functionDecls) */;

	::clang::ast_matchers::MatchFinder finder; // data_aggregation
	// finder.addMatcher(range_based_loopMatcher, &ctExec);
	// finder.addMatcher(annotatedFuncMatcher, &ctRunner);

	// using namespace ::clang::ast_matchers;

	// TODO: derive from MatchFinder
	// ::msc::ast_match::find_functions_by_qualified_name(finder,
	// runOpt.getValue(),
	//  named_function_callback);
	::msc::ast_match::find_functions_by_name(finder, runOpt.getValue(),
											 named_function_callback);
	::msc::ast_match::find_functions_by_annotation(finder,
												   annotated_function_callback);

	// handle_run_cmd_line_arg(finder, ct_runner);
	// handle_annotated_functions(finder, annotated_function_callback);

	// std::unique_ptr<clang::tooling::FrontendActionFactory> factory =
	// clang::tooling::newFrontendActionFactory(&finder); clang::FrontendAction
	// *action = factory.get()->create();

	// run the matchers/callbacks
	::std::vector<std::unique_ptr<::clang::ASTUnit>> ASTs;
	int system_state = tool.buildASTs(ASTs);

	MA_INFO("Main", "buildASTs: %d ASTs.size(): %zu", system_state,
			ASTs.size());

	// aggregate all matched ASTs
	for (unsigned i = 0; i < ASTs.size(); ++i)
	{
		MA_INFO("Main", "Matching AST %u", i);
		::clang::ASTContext &context = ASTs[i]->getASTContext();

		finder.matchAST(ASTs[i]->getASTContext());
	}

	// TESTING
	// ::clang::FunctionDecl *func;

	// ::msc::cex::EmitBitcodeAction emitBitcodeAction;
	// emitBitcodeAction.setCompilerInstance();

	// ::std::unique_ptr<::clang::tooling::FrontendActionFactory>
	// unique_actionFactory =
	// 	::clang::tooling::newFrontendActionFactory(&finder);
	// ::clang::tooling::FrontendActionFactory *actionFactory =
	// actionFactory.get(); ConsumerFactoryAdaptor * action =
	// actionFactory->create();

	// ::clang::tooling::newFrontendActionFactory();
	// ::std::unique_ptr<::clang::tooling::FrontendActionFactory> actionFactory
	// =
	// 	::std::make_unique<::clang::tooling::FrontendActionFactory>();
	// actionFactory.get()->
	// ::clang::EmitCodeGenOnlyAction

	// TODO: look for composite action

	// ::clang::ASTFrontendAction test;
	// auto result =
	// // tool.run(::clang::tooling::newFrontendActionFactory(&finder).get());
	// tool.run(&emitBitcodeAction);
	// return result;

	// ::clang::CompilerInstance compiler;
	// ::clang::DiagnosticOptions diagnosticOptions;
	// compiler.createDiagnostics();
	// compiler.createDiagnostics(argc, argv);

	// ::clang::LangOptions langOpts;
	// ::clang::LinkageComputer link;

	// ---------- CompilerInstance ----------

	// ::clang::CompilerInstance compiler;	// vfs::getRealFileSystem()
	// ::msc::cex::setupCompilerInstance(compiler, tool.getFiles());

	// ---------- JIT ----------
	// works on *.bc or *.ll

	// ::llvm::InitializeNativeTarget();
	// ::llvm::InitializeNativeTargetAsmPrinter();
	// ::llvm::InitializeNativeTargetAsmParser();
	// ::llvm::InitializeModuleAndPassManager();

	::llvm::LLVMContext llvm_context;
	::llvm::llvm_shutdown_obj Y; // Call llvm_shutdown() on exit.

	static char const * k_bitcode_file = "test.bc";
	static char const * k_test_func = "cex_main()";

	msc::cex::initializeNativeTarget();

	// msc::cex::JIT jit(llvm_context);
	// jit.addModule();
	// jit.callFunction(k_bitcode_file, k_test_func, 0);

	// ::llvm::CodeGenFunction cgFunc()

	llvm::ExecutionEngine *engine = nullptr;
	llvm::Function const *function = nullptr;
	std::vector<llvm::Function const *> functions;
	{
	std::unique_ptr<::llvm::Module> unique_module =
		msc::cex::loadModule(llvm_context, k_bitcode_file);

	// Configure module
	// ::llvm::Module *module = unique_module.get();
	// module->setDataLayout(cexJIT->getTargetMachine().createDataLayout());

	// Create a new pass manager attached to it.
	// std::unique_ptr<::llvm::legacy::FunctionPassManager> function_pass_manager =
	// llvm::make_unique<::llvm::legacy::FunctionPassManager>(module);

	// Do simple "peephole" optimizations and bit-twiddling optzns.
	// function_pass_manager->add(createInstructionCombiningPass());
	// Reassociate expressions.
	// function_pass_manager->add(createReassociatePass());
	// Eliminate Common SubExpressions.
	// function_pass_manager->add(createGVNPass());
	// Simplify the control flow graph (deleting unreachable blocks, etc).
	// function_pass_manager->add(createCFGSimplificationPass());

	// function_pass_manager->doInitialization();

	// Run the main "interpreter loop" now.
	// MainLoop();

	// Check the module parsed here.
	// ...



	function = msc::cex::findFunction(unique_module.get(), k_test_func);
	// msc::cex::parseAnnotations(unique_module.get(), k_cex_annotation, functions);
	// msc::cex::parsePragmas(unique_module.get(), k_cex_annotation, function_args_tuples);
	engine = msc::cex::createEngine(std::move(unique_module));
	}
	msc::cex::callFunction(engine, function);

	/////////////////////////////////
	//TODO: do this in a pass instead
	// llvm::Function *function = msc::cex::findFunction(module, "cex_main()");
	// llvm::Function *function = module->getFunction("cex_main");

	// std::vector<::llvm::GenericValue> args{};
	// only support args in inline compile-time calls like #pragma run cex_main(7, "Malius", {13, 3.1415f})
	// because arg type evaluation/info is needed
	//or
	// count args and cast according to found function with same amount of args
	// limitation: function overloads can't have same amount of arguments
	// msc::cex::parseArgs(args, "7, \"Malius\", {13, 3.1415f}");
	// llvm::GenericValue *result = msc::cex::runFunction(function, args);
	/////////////////////////////////

	// ::llvm::outs() << "We just constructed this LLVM module:\n\n" << *module;
	// llvm::Function *FooF = msc::tmp::create_custom_module();

	// ::llvm::outs() << "\n\nRunning foo: ";
	// ::llvm::outs().flush();

	// Call the `foo' function with no arguments:
	// std::vector<::llvm::GenericValue> noargs{};

	// runFunction:
	/// For MCJIT execution engines, clients are encouraged to use the
	/// "GetFunctionAddress" method (rather than runFunction) and cast the
	/// returned uint64_t to the desired function pointer type. However, for
	/// backwards compatibility MCJIT's implementation can execute 'main-like'
	/// function (i.e. those returning void or int, and taking either no
	/// arguments or (int, char*[])).
	// ::llvm::GenericValue gv = engine->runFunction(FooF, noargs);

	// Import result of execution:
	// ::llvm::outs() << "Result: " << gv.IntVal << "\n";
	// delete engine;

	// parse ast and look for annotated functions

	// compile annotated functions including dependencies

	// Run annotated functions

	// temp save return results

	// compile entire program
	// -> bake saved return results into compilation
	// (substitute inline run calls with saved return results)

	// ASTFrontEndAction test;
	// auto result =
	//	tool.run(clang::tooling::newFrontendActionFactory(&finder).get());
	// return result;

	// clang --help | grep -- "-X"
	//   -Xanalyzer <arg>        Pass <arg> to the static analyzer
	//   -Xassembler <arg>       Pass <arg> to the assembler
	//   -Xclang <arg>           Pass <arg> to the clang compiler
	//   -Xcuda-fatbinary <arg>  Pass <arg> to fatbinary invocation
	//   -Xcuda-ptxas <arg>      Pass <arg> to the ptxas assembler
	//   -Xlinker <arg>          Pass <arg> to the linker
	//   -Xopenmp-target=<arg>   Pass <arg> to the specified target offloading
	//   toolchain. The triple that identifies the toolchain must be provided
	//   after the equals sign. -Xopenmp-target <arg>   Pass <arg> to the target
	//   offloading toolchain. -Xpreprocessor <arg>    Pass <arg> to the
	//   preprocessor

	return true;
}
