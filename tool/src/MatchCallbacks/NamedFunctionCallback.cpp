
#include "cex/MatchCallbacks/NamedFunctionCallback.h"
#include "cex/binding_ids.h"

#include <malius/log/Logger.hpp>

namespace msc
{
namespace ast_match
{

void NamedFunctionCallback::run(
	const ::clang::ast_matchers::MatchFinder::MatchResult &result)
// __attribute__((annotate("TROLOLOLOL ")))
// my_stuff(LoopPrinter)
// __attribute__((convergent))
{
	// MA_INF0("CompileTimeRunner", "Does this even work?");

	::clang::ASTContext *context = result.Context;

	// const clang::FunctionDecl *funcDecl =
	// result.Nodes.getNodeAs<clang::FunctionDecl>("annotatedFunction");

	const ::clang::FunctionDecl *funcDecl =
		result.Nodes.getNodeAs<::clang::FunctionDecl>(
			msc::ast_match::id::named_function);

	// const clang::ForStmt *forStmt =
	// result.Nodes.getNodeAs<clang::ForStmt>("rangeBasedForLoop");

	// We do not want to convert header files!
	// if (!forStmt ||
	// !context->getSourceManager().isWrittenInMainFile(forStmt->getForLoc()))
	// {
	// return;
	// }

	// const clang::VarDecl *initVar =
	// result.Nodes.getNodeAs<clang::VarDecl>("initVarName"); const
	// clang::VarDecl *condVar =
	// result.Nodes.getNodeAs<clang::VarDecl>("condVarName"); const
	// clang::VarDecl *incVar =
	// result.Nodes.getNodeAs<clang::VarDecl>("incVarName");

	// char *testStr = initVar
	// if (!areSameVariable(initVar, condVar) || !areSameVariable(initVar,
	// incVar))
	// {
	// return;
	// }
	// llvm::outs() << "Potential array-based loop discovered.\n";

	// if (const ForStmt *forStmt =
	// result.Nodes.getNodeAs<clang::ForStmt>("rangeBasedForLoop"))
	// {
	// forStmt->dump();
	// }

	if (funcDecl)
	{
		// TODO

		// compile
		::clang::DeclarationNameInfo nameInfo = funcDecl->getNameInfo();
		::std::string name = nameInfo.getName().getAsString();

		// context->getFullLoc()
		// ::llvm::StringRef fileName =
		// context->getSourceManager().getFilename(funcDecl->getSourceRange().getBegin());
		::llvm::StringRef fileName =
			context->getSourceManager().getFilename(nameInfo.getLoc());
		// FullSourceLoc fullLoc =
		// context->getFullLoc(funcDecl->getSourceRange().getBegin()); fullLoc.

		// run
		MA_INFO("CompileTimeRunner", "Matched %s in file %s", name.data(),
				fileName.data());
		// MA_INFO("CompileTimeRunner", "Running %s at compile-time.",
		// name.data());

		// bool hasBody = funcDecl->hasBody();
		// clang::Stmt *body = funcDecl->getBody();
		// bool test = funcDecl->doesThisDeclarationHaveABody();

		// funcDecl->dump();
	}
}

} // namespace ast_match
} // namespace msc
