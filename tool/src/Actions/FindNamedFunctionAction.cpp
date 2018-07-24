// Reference: http://clang.llvm.org/docs/RAVFrontendAction.html

#include "Actions/FindNamedFunctionAction.h"

#include "clang/Frontend/FrontendActions.h"
// #include "clang/Frontend/FrontendAction.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/CompilerInstance.h"

namespace ma
{

class FindNamedFunctionVisitor
	: public clang::RecursiveASTVisitor<FindNamedFunctionVisitor>
{
  public:
	explicit FindNamedFunctionVisitor(clang::ASTContext *context)
		: m_context(context)
	{
	}

	// bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration)
	bool VisitFunctionDecl(clang::FunctionDecl *Declaration)
	{
		if (Declaration->getQualifiedNameAsString() == "cex_main")
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
				llvm::outs()
					<< "Found declaration at "
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

class FindNamedFunctionConsumer : public ::clang::ASTConsumer
{
  public:
	explicit FindNamedFunctionConsumer(clang::ASTContext *context)
		: m_visitor(context)
	{
	}
	virtual void HandleTranslationUnit(clang::ASTContext &context)
	{
		// Traversing the translation unit decl via a RecursiveASTVisitor
		// will visit all nodes in the AST.
		m_visitor.TraverseDecl(context.getTranslationUnitDecl());
	}

  private:
	// A RecursiveASTVisitor implementation.
	FindNamedFunctionVisitor m_visitor;
};

std::unique_ptr<clang::ASTConsumer>
FindNamedFunctionAction::CreateASTConsumer(clang::CompilerInstance &compiler,
										llvm::StringRef inFile)
{
	return std::unique_ptr<clang::ASTConsumer>(
		new FindNamedFunctionConsumer(&compiler.getASTContext()));
}

} // namespace ma
