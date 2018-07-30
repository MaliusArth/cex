#pragma once

#include "clang/Frontend/CompilerInstance.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"



namespace msc
{
namespace cex
{
class Preprocessor
{
	void run()
	{
		clang::CompilerInstance ci;
		ci.createDiagnostics(); // create DiagnosticsEngine
		ci.createFileManager();  // create FileManager
		ci.createSourceManager(ci.getFileManager()); // create SourceManager
		ci.createPreprocessor(clang::TranslationUnitKind::TU_Complete);  // create Preprocessor
		const clang::FileEntry *pFile = ci.getFileManager().getFile("hello.c");
		ci.getSourceManager().createMainFileID(pFile);
		ci.getPreprocessor().EnterMainSourceFile();
		ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), &ci.getPreprocessor());
		clang::Token tok;
		do {
			ci.getPreprocessor().Lex(tok);
			if( ci.getDiagnostics().hasErrorOccurred())
				break;
			ci.getPreprocessor().DumpToken(tok);
			std::cerr << std::endl;
		} while ( tok.isNot(clang::tok::eof));
		ci.getDiagnosticClient().EndSourceFile();
	}
}


// Reference: https://www.ibm.com/developerworks/library/os-createcompilerllvm1/index.html
class Compiler //: ::clang::CompilerInstance
{
	Compiler()
	{
		compiler.createDiagnostics();

	}

	void main()
	{
		llvm::LLVMContext& context = llvm::getGlobalContext();
		llvm::Module *module = new llvm::Module("root", context);
		llvm::IRBuilder<> builder(context);

		llvm::FunctionType *funcType =
			llvm::FunctionType::get(builder.getInt32Ty(), false);
		llvm::Function *mainFunc =
			llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

		llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
		builder.SetInsertPoint(entry);

		module->dump( );
	}


	::clang::CompilerInstance compiler;
	::clang::DiagnosticOptions diagnosticOptions;


}
} // namespace cex
} // namespace msc