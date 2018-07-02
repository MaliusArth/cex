#pragma once

#include "binding_ids.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/CommandLine.h"

namespace msc
{
namespace ast_match
{

using namespace ::clang::ast_matchers;

// narrow down the matching to user/project files
// with the user files defined as a match regex we can now initialize the
// matchers
// Coop.cpp: auto file_match =
// isExpansionInFileMatching(coop::match::get_file_regex_match_condition(user_include_path_root));
// project_scope_matcher
// TODO: handle external headers etc. (do I want to consider them? Probably
// not.)
auto const file_matcher = unless(isExpansionInSystemHeader());

// can only handle a single function at a time because of bind id (pass id as
// argument?)
// TODO: find_function_by_signature since there can be multiple overloads of the same func with the same name
//template <typename T>
void find_functions_by_name(
	::clang::ast_matchers::MatchFinder &finder,
	::llvm::StringRef func_name,
	// ::clang::ast_matchers::internal::Matcher<T>,
	::clang::ast_matchers::MatchFinder::MatchCallback &callback)
{
	if (func_name.empty())
	{
		return;
	}

	// llvm::StringRef run_func = runOpt.getValue();
	// using namespace ::clang::ast_matchers;

	// Find runFunc in src
	// RunDirectiveFinder runFinder;
	// FindNamedFunctionAction clRunFinder;
	// NamedFunctionFinder clRunFinder;
	// clang::ast_matchers::MatchFinder finder;
	// finder.addMatcher(annotatedFuncMatcher, &runFinder);

	// std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
	// tool.buildASTs(ASTs);
	// for(unsigned i = 0; i < ASTs.size(); ++i)
	// {
	// finder.matchAST(ASTs[i]->getASTContext());
	// }

	// Compile runFunc including dependencies.

	// Run runFunc (ignore return value?)
	// (save results aka used memory into obj used in later compilation)

	// using /* class */ clang::ast_matchers::DeclarationMatcher;
	// using /* class */ clang::ast_matchers::functionDecl;
	// using /* class */ clang::ast_matchers::hasName;

	// strip function arguments
	// possible function regex: ^\s*(\w+)\s*\((.*)\)
	size_t func_args_pos = func_name.find('(');
	llvm::StringRef func_args = func_name.drop_front(func_args_pos);
	func_name = func_name.take_front(func_args_pos);

	DeclarationMatcher named_function_matcher =
		functionDecl(file_matcher, hasName(func_name))
			.bind(msc::ast_match::id::named_function);

	// TODO: create_named_function_matcher
	// TODO: return matcher and
	finder.addMatcher(named_function_matcher, &callback);
}

// template<typename T>
void find_functions_by_annotation(
	::clang::ast_matchers::MatchFinder &finder,
	llvm::StringRef annotation,
	::clang::ast_matchers::MatchFinder::MatchCallback &callback)
{


	DeclarationMatcher annotated_function_matcher =
		functionDecl(file_matcher, hasAttr(::clang::attr::Kind::Annotate))
			.bind(msc::ast_match::id::annotated_function);

	finder.addMatcher(annotated_function_matcher, &callback);
}

} // namespace ast_match
} // namespace msc