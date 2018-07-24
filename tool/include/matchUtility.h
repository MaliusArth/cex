#pragma once

#include "clang/ASTMatchers/ASTMatchers.h"

// using namespace clang::ast_matchers;

namespace msc
{
namespace ast_match
{
namespace util
{

inline bool areSameVariable(const clang::ValueDecl *first,
							const clang::ValueDecl *second)
{
	return first && second &&
		   first->getCanonicalDecl() == second->getCanonicalDecl();
}

// [[clang::disable_tail_calls]]
inline bool areSameExpr(clang::ASTContext *context, const clang::Expr *first,
						const clang::Expr *second) /* MA_DEPRECATED */
{
	if (!first || !second)
		return false;
	llvm::FoldingSetNodeID firstID, secondID;
	first->Profile(firstID, *context, true);
	second->Profile(secondID, *context, true);
	return firstID == secondID;
}

} // namespace util
} // namespace ast_match
} // namespace msc
