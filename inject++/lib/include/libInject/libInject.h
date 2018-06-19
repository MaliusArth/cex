#pragma once

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"

// System #includes


// using namespace clang;
// using namespace clang::ast_matchers;
// using namespace llvm;

//StatementMatcher loopMatcher =
//	forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
//		hasInitializer(integerLiteral(equals(0)))))))).bind("forLoop");

extern clang::ast_matchers::DeclarationMatcher annotatedFuncMatcher;

class CompileTimeExecutor : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
	virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &result);
};