
// #include style: https://llvm.org/docs/CodingStandards.html#include-style

// Main Module Header
// a.k.a. the header file containing the interfaces a .cpp file implements (.h/.cpp pairs)
#include "libInject/libInject.h"

// Local/Private Headers
#include "malius/core/lang.hpp"

// LLVM project/subproject headers (clang/..., lldb/..., llvm/..., etc)
// Declares clang::SyntaxOnlyAction.
// #include "clang/Frontend/FrontendActions.h"
// #include "clang/Tooling/CommonOptionsParser.h"
// #include "clang/Tooling/Tooling.h"

// Declares llvm::cl:extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"

// System #includes


// using namespace clang;
using namespace clang::ast_matchers;
// using namespace clang::tooling;
// using namespace llvm;

// clang::attr::Kind attrKind = clang::attr::Kind;
DeclarationMatcher annotatedFuncMatcher =
	clang::ast_matchers::functionDecl(hasAttr(clang::attr::Kind::Annotate))
		.bind("annotatedFunction");

// TODO: matches range based loop as for now
StatementMatcher range_based_loopMatcher =
	forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
		hasInitializer(integerLiteral(equals(0)))).bind("initVarName")))),
		hasCondition(binaryOperator(
			hasOperatorName("<"),
			hasLHS(ignoringParenImpCasts(declRefExpr(
				to(varDecl(hasType(isInteger())).bind("condVarName"))))),
			hasRHS(expr(hasType(isInteger()))))),
		hasIncrement(unaryOperator(
			hasOperatorName("++"),
			hasUnaryOperand(declRefExpr(
				to(varDecl(hasType(isInteger())).bind("incVarName"))))))
).bind("rangeBasedForLoop");

static bool areSameVariable(const clang::ValueDecl *first, const clang::ValueDecl *second)
{
	return first && second &&
		first->getCanonicalDecl() == second->getCanonicalDecl();
}

// [[clang::disable_tail_calls]]
static bool areSameExpr(clang::ASTContext *context, const clang::Expr *first,
                        const clang::Expr *second) MA_DEPRECATED
{
	if (!first || !second)
		return false;
	llvm::FoldingSetNodeID firstID, secondID;
	first->Profile(firstID, *context, true);
	second->Profile(secondID, *context, true);
	return firstID == secondID;
}

void CompileTimeExecutor::run(const clang::ast_matchers::MatchFinder::MatchResult &result)
// __attribute__((annotate("TROLOLOLOL ")))
// my_stuff(LoopPrinter)
// __attribute__((convergent))
{
	clang::ASTContext *context = result.Context;
	const clang::FunctionDecl *funcDecl =
		result.Nodes.getNodeAs<clang::FunctionDecl>("annotatedFunction");
	const clang::ForStmt *forStmt =
		result.Nodes.getNodeAs<clang::ForStmt>("rangeBasedForLoop");

	// We do not want to convert header files!
	if (!forStmt || !context->getSourceManager().isWrittenInMainFile(forStmt->getForLoc()))
	{
		return;
	}

	const clang::VarDecl *initVar = result.Nodes.getNodeAs<clang::VarDecl>("initVarName");
	const clang::VarDecl *condVar = result.Nodes.getNodeAs<clang::VarDecl>("condVarName");
	const clang::VarDecl *incVar = result.Nodes.getNodeAs<clang::VarDecl>("incVarName");
	// struct Testolio
	// {
	// 	int a;
	// };
	// Testolio test;
	
	// char *testStr = initVar
	if (!areSameVariable(initVar, condVar) || !areSameVariable(initVar, incVar))
	{
		return;
	}
	llvm::outs() << "Potential array-based loop discovered.\n";

//		if (const ForStmt *forStmt = result.Nodes.getNodeAs<clang::ForStmt>("rangeBasedForLoop"))
//		{
//			forStmt->dump();
//		}
}
