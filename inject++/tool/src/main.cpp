

// #include style: https://llvm.org/docs/CodingStandards.html#include-style

// Main Module Header
// a.k.a. the header file containing the interfaces a .cpp file implements
// (.h/.cpp pairs)

// Local/Private Headers
#include "libInject/libInject.h"

// #include "hooks/macro_approach.h"

// External headers
#include <malius/core/lang.hpp>
#include <malius/log/Logger.hpp>

// LLVM project/subproject headers (clang/..., lldb/..., llvm/..., etc)

// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

// Declares llvm::cl:extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
// #include "clang/Frontend/FrontendAction.h"
// #include "clang/Tooling/Tooling.h"

// System #includes

// using namespace clang;
// using namespace clang::tooling;
// using namespace llvm;

namespace
{
	// Apply a custom category to all command-line options so that they are the
	// only ones displayed.
	static llvm::cl::OptionCategory MyToolCategory("inject++ options");

	// CommonOptionsParser declares HelpMessage with a description of the common
	// command-line options related to the compilation database and input files.
	// It's nice to have this help message in all tools.
	static llvm::cl::extrahelp
		CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

	// A help message for the specific tool can be added afterwards.
	static llvm::cl::extrahelp MoreHelp("\nMore help text...");
}

//  #define ANNOTATION
// #pragma

//////////////////////////////////////////////////////////////////////

// Reference: http://clang.llvm.org/docs/RAVFrontendAction.html

class FindNamedClassVisitor : public clang::RecursiveASTVisitor<FindNamedClassVisitor>
{
  public:
	explicit FindNamedClassVisitor(clang::ASTContext *context) : m_context(context) {}
	bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration)
	{
		if (Declaration->getQualifiedNameAsString() == "n::m::C")
		{
			// For debugging, dumping the AST nodes will show which nodes are
			// already
			// being visited.
			Declaration->dump();
			// getFullLoc uses the ASTContext's SourceManager to resolve the
			// source location and break it up into its line and column parts.
			clang::FullSourceLoc fullSrcLocation =
				m_context->getFullLoc(Declaration->getLocStart());
			if (fullSrcLocation.isValid())
				llvm::outs() << "Found declaration at "
							 << fullSrcLocation.getSpellingLineNumber() << ":"
							 << fullSrcLocation.getSpellingColumnNumber() << "\n";
		}
		// The return value indicates whether we want the visitation to proceed.
		// Return false to stop the traversal of the AST.
		return true;
	}

  private:
	clang::ASTContext *m_context;
};

class FindNamedClassConsumer : public clang::ASTConsumer
{
  public:
	explicit FindNamedClassConsumer(clang::ASTContext *context) : m_visitor(context) {}
	virtual void HandleTranslationUnit(clang::ASTContext &context)
	{
		// Traversing the translation unit decl via a RecursiveASTVisitor
		// will visit all nodes in the AST.
		m_visitor.TraverseDecl(context.getTranslationUnitDecl());
	}

  private:
	// A RecursiveASTVisitor implementation.
	FindNamedClassVisitor m_visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction
{
  public:
	typedef std::unique_ptr<clang::ASTConsumer> ASTConsumer_ptr;
	
	virtual ASTConsumer_ptr CreateASTConsumer(clang::CompilerInstance &compiler,
											  llvm::StringRef inFile)
	{
		return ASTConsumer_ptr(
			new FindNamedClassConsumer(&compiler.getASTContext()));
	}
};

int main(int argc, const char **argv)
{
	ma::log::ConsoleLogger logger(
		ma::log::VerbosityFilterPolicy(2),
		ma::log::SimpleFormatPolicy(),
		ma::log::ConsoleWriterPolicy()
	);

	MA_INF0("Main", "Inject++ Tool is running.");
	MA_INFO("Main", "Inject++ Tool is running.%s", ".. bitch!");

	clang::tooling::CommonOptionsParser optionsParser(argc, argv,
													  MyToolCategory);
	clang::tooling::ClangTool tool(optionsParser.getCompilations(),
								   optionsParser.getSourcePathList());

	// "/home/maliusarth/projects/ext/tools/llvm/6.0.0/x64/include",

	CompileTimeExecutor ctExec;
	clang::ast_matchers::MatchFinder finder;
	// finder.addMatcher(range_based_loopMatcher, &ctExec);
	finder.addMatcher(annotatedFuncMatcher, &ctExec);

	// std::unique_ptr<clang::tooling::FrontendActionFactory> factory =
	// clang::tooling::newFrontendActionFactory(&finder); clang::FrontendAction
	// *action = factory.get()->create(); typedef int Lustig;
	// typedef
	// typedef void(*fp)(int, int);
	// alias
	// using fp2 = void(int, int);

	// ASTFrontEndAction test;
	return tool.run(clang::tooling::newFrontendActionFactory(&finder).get());
}
