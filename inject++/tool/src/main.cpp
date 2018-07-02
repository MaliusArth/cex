

// #include style: https://llvm.org/docs/CodingStandards.html#include-style

// Main Module Header
// a.k.a. the header file containing the interfaces a .cpp file implements
// (.h/.cpp pairs)

// Local/Private Headers
// #include "libInject/libInject.h"
// #include "FindNamedFunctionAction.h"
#include "CompileTimeRunner.h"
#include "MatchCallbacks/AnnotatedFunctionCallback.h"
#include "MatchCallbacks/NamedFunctionCallback.h"
#include "matchers.h"

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
// #include "clang/Tooling/Tooling.h"

#include "llvm/ADT/StringRef.h"

#include "clang/Frontend/Utils.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/FileManager.h"
#include "clang/Lex/Token.h"

#include "llvm/Support/MemoryBuffer.h"

// System #includes
// #include <cstring>	//TODO: TEMP
#include <memory>

// using namespace clang;
// using namespace clang::tooling;
// using namespace llvm;

namespace
{
// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory toolCategory("cex Options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp
	commonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

// A help message for the specific tool can be added afterwards.
static llvm::cl::extrahelp moreHelp("\nMore help text...\n\n");

static llvm::cl::opt<std::string>
	runOpt("run", llvm::cl::desc("function to run at compile-time"),
		   llvm::cl::value_desc("file path"), llvm::cl::cat(toolCategory));

// static llvm::cl::opt<unsigned, false, FileSizeParser> maxFileSizeOpt(
// "max-file-size", llvm::cl::desc("Maximum file size to accept"),
// llvm::cl::value_desc("size"), llvm::cl::cat(toolCategory)
// );
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
	MA_INFO("Main", "cex tool is running.%s", ".. bitch!");

	// llvm::cl::ParseCommandLineOptions(argc, argv);

	clang::tooling::CommonOptionsParser optionsParser(argc, argv, toolCategory);
	clang::tooling::ClangTool tool(optionsParser.getCompilations(),
								   optionsParser.getSourcePathList());


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
	msc::ast_match::NamedFunctionCallback named_function_callback;
	msc::ast_match::AnnotatedFunctionCallback annotated_function_callback;

	clang::ast_matchers::MatchFinder finder; // data_aggregation
	// finder.addMatcher(range_based_loopMatcher, &ctExec);
	// finder.addMatcher(annotatedFuncMatcher, &ctRunner);

	// using namespace ::clang::ast_matchers;

	// TODO: derive from MatchFinder
	// find_function_by_name(finder, runOpt.getValue(), ct_runner);
	msc::ast_match::find_functions_by_name(finder, runOpt.getValue(),
										   named_function_callback);
	msc::ast_match::find_functions_by_annotation(finder, "cex",
											 annotated_function_callback);

	// handle_run_cmd_line_arg(finder, ct_runner);
	// handle_annotated_functions(finder, annotated_function_callback);

	// std::unique_ptr<clang::tooling::FrontendActionFactory> factory =
	// clang::tooling::newFrontendActionFactory(&finder); clang::FrontendAction
	// *action = factory.get()->create();

	// run the matchers/callbacks
	std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
	int system_state = tool.buildASTs(ASTs);

	// aggregate all matched ASTs
	for (unsigned i = 0; i < ASTs.size(); ++i)
	{
		MA_INFO("Main", "Matching AST %u", i);
		clang::ASTContext &context = ASTs[i]->getASTContext();

		finder.matchAST(ASTs[i]->getASTContext());
	}

	// ::clang::CompilerInstance compiler;
	// ::clang::DiagnosticOptions diagnosticOptions;
	// compiler.createDiagnostics();
	// compiler.createDiagnostics(argc, argv);

	// ::clang::LangOptions langOpts;
	// ::clang::LinkageComputer link;


	::clang::CompilerInstance compiler;
	// compiler.resetAndLeakFileManager()
	compiler.createDiagnostics();                      // create DiagnosticsEngine
	// auto &fsOpts = compiler.getFileSystemOpts();
	// fsOpts.
	// create TargetOptions
	// ::clang::TargetOptions targetOptions;
	std::shared_ptr<::clang::TargetOptions> shared_targetOptions = std::make_shared<::clang::TargetOptions>();
	shared_targetOptions->Triple = llvm::sys::getDefaultTargetTriple();
	//create TargetInfo
	::clang::TargetInfo *targetInfo = ::clang::TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), shared_targetOptions);
	compiler.setTarget(targetInfo);
	// ::clang::FileManager * fileManager = compiler.createFileManager();                      // create FileManager
	// fileManager->
	::clang::FileManager &fileManager = tool.getFiles();
	compiler.setFileManager(&fileManager);
	// ::clang::FileEntry *file = fileManager.getVirtualFile("main.cpp.in");
	::llvm::IntrusiveRefCntPtr<::clang::vfs::FileSystem> shared_fs = fileManager.getVirtualFileSystem();
	::clang::vfs::FileSystem *fs = shared_fs.get();
	auto cwd = fs->getCurrentWorkingDirectory();
	assert(cwd && "cwd is missing!");
	MA_INFO("Compiler", "cwd: %s", cwd.get().c_str());
	// fs
	// ::clang::DirectoryEntry const *test = fileManager.getDirectory(".");
	// MA_INFO("Compiler", "root: %s", test->getName().data());
	compiler.createSourceManager(compiler.getFileManager()); // create SourceManager
	// compiler.InitializeSourceManager();

	// TU_Complete / TU_Prefix / TU_Module
	compiler.createPreprocessor(::clang::TranslationUnitKind::TU_Complete);                     // create Preprocessor

	const ::clang::FileEntry *pFile = compiler.getFileManager().getFile("main.cpp.in");
	assert(pFile && "File doesn't exist!");
	// llvm::MemoryBuffer buf(;
	// buf.
	// std::unique_ptr<llvm::MemoryBuffer> unique_mainBuffer = std::make_unique<llvm::MemoryBuffer>()
	// ::clang::FileID file_id = compiler.getSourceManager().getOrCreateFileID(pFile, ::clang::SrcMgr::CharacteristicKind::C_User);
	::clang::FileID file_id = compiler.getSourceManager().createFileID(pFile, ::clang::SourceLocation(), ::clang::SrcMgr::CharacteristicKind::C_User);
	compiler.getSourceManager().setMainFileID(file_id);

	// ----- Preprocessor -----
	// ----- Lexer -----
	compiler.getPreprocessor().EnterMainSourceFile();
	compiler.getDiagnosticClient().BeginSourceFile(compiler.getLangOpts(),
											 &compiler.getPreprocessor());
	::clang::Token tok;
	do
	{
		compiler.getPreprocessor().Lex(tok);
		if (compiler.getDiagnostics().hasErrorOccurred()) { break; }
		compiler.getPreprocessor().DumpToken(tok);
		// std::cerr << std::endl;
		MA_ERROR("Lexer", "%s", "\n");
	} while (tok.isNot(clang::tok::eof));
	compiler.getDiagnosticClient().EndSourceFile();

	// compiler.ExecuteAction(clang::tooling::newFrontendActionFactory(&finder).get());
	// clang::CompilerInstance::OutputFile file;
	// file.Filename = "OutputFile.txt";
	// compiler.addOutputFile(file);

	// TODO:
	/// An interface for collecting the dependencies of a compilation. Users
	/// should use \c attachToPreprocessor and \c attachToASTReader to get all
	/// of the dependencies.
	// std::shared_ptr<clang::DependencyCollector> deps_collector;
	// deps_collector.
	// compiler.addDependencyCollector();


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
return true;
}
