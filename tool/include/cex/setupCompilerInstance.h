#pragma once

#include "malius/log/Logger.hpp"

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"

#include <memory>

namespace msc
{
namespace cex
{

void setupCompilerInstance(::clang::CompilerInstance &compiler, ::clang::FileManager &fileManager)
{
	// ::clang::CompilerInstance compiler;
	// compiler.resetAndLeakFileManager()
	compiler.createDiagnostics(); // create DiagnosticsEngine
	// auto &fsOpts = compiler.getFileSystemOpts();
	// fsOpts.
	// create TargetOptions
	// ::clang::TargetOptions targetOptions;
	std::shared_ptr<::clang::TargetOptions> shared_targetOptions =
		std::make_shared<::clang::TargetOptions>();
	shared_targetOptions->Triple = llvm::sys::getDefaultTargetTriple();
	// create TargetInfo
	::clang::TargetInfo *targetInfo = ::clang::TargetInfo::CreateTargetInfo(
		compiler.getDiagnostics(), shared_targetOptions);
	compiler.setTarget(targetInfo);
	// ::clang::FileManager * fileManager = compiler.createFileManager(); //
	// create FileManager fileManager->
	// ::clang::FileManager &fileManager = tool.getFiles();
	compiler.setFileManager(&fileManager);
	// ::clang::FileEntry *file = fileManager.getVirtualFile("main.cpp.in");
	::llvm::IntrusiveRefCntPtr<::clang::vfs::FileSystem> shared_fs =
		fileManager.getVirtualFileSystem();
	::clang::vfs::FileSystem *fs = shared_fs.get();
	auto cwd = fs->getCurrentWorkingDirectory();
	assert(cwd && "cwd is missing!");
	MA_INFO("Compiler", "cwd: %s", cwd.get().c_str());
	// fs
	// ::clang::DirectoryEntry const *test = fileManager.getDirectory(".");
	// MA_INFO("Compiler", "root: %s", test->getName().data());
	compiler.createSourceManager(
		compiler.getFileManager()); // create SourceManager
	// compiler.InitializeSourceManager();

	// TU_Complete / TU_Prefix / TU_Module
	compiler.createPreprocessor(
		::clang::TranslationUnitKind::TU_Complete); // create Preprocessor

	const ::clang::FileEntry *pFile =
		compiler.getFileManager().getFile("main.cpp.in");
	assert(pFile && "File doesn't exist!");
	// llvm::MemoryBuffer buf(;
	// buf.
	// std::unique_ptr<llvm::MemoryBuffer> unique_mainBuffer =
	// std::make_unique<llvm::MemoryBuffer>()
	// ::clang::FileID file_id =
	// compiler.getSourceManager().getOrCreateFileID(pFile,
	// ::clang::SrcMgr::CharacteristicKind::C_User);
	::clang::FileID file_id = compiler.getSourceManager().createFileID(
		pFile, ::clang::SourceLocation(),
		::clang::SrcMgr::CharacteristicKind::C_User);
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
		if (compiler.getDiagnostics().hasErrorOccurred())
		{
			break;
		}
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
}
} // namespace cex
} // namespace msc
