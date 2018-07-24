
#include "MatchCallbacks/AnnotatedFunctionCallback.h"
#include "binding_ids.h"

#include <malius/log/Logger.hpp>

#include "clang/AST/Attr.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclBase.h"
#include "clang/Basic/AttrKinds.h"
// #include "llvm/IR/Attributes.h"

namespace msc
{
namespace ast_match
{

void AnnotatedFunctionCallback::run(
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
			msc::ast_match::id::annotated_function);

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

	if (!funcDecl)
		return;

#if defined(_DEBUG)

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
	MA_INFO("AnnotatedFunctionCallback",
			"Matched %s with annotation in file %s",
			name.data() /* , attribute */, fileName.data());
	MA_INFO("AnnotatedFunctionCallback",
			"Qualified name is %s",
			funcDecl->getQualifiedNameAsString().data());
	// MA_INFO("CompileTimeRunner", "Running %s at compile-time.",
	// name.data());

	// bool hasBody = funcDecl->hasBody();
	// clang::Stmt *body = funcDecl->getBody();
	// bool test = funcDecl->doesThisDeclarationHaveABody();

	funcDecl->dump();
#endif

	bool do_cex_run = false;
	// ::clang::specific_attr_iterator<::clang::AnnotateAttr> testIt;
	// ::clang::AttrVec attrs =
	// funcDecl->specific_attrs<::clang::AnnotateAttr>();
	::llvm::iterator_range<
		::clang::specific_attr_iterator<::clang::AnnotateAttr>>
		attrs = funcDecl->specific_attrs<::clang::AnnotateAttr>();
	// for (::clang::Attr **attr = attrs.begin(); attr != attrs.end(); attr++)
	for (::clang::specific_attr_iterator<::clang::AnnotateAttr> attrIt =
			 attrs.begin();
		 attrIt != attrs.end(); attrIt++)
	{
		::clang::AnnotateAttr *annotate = *attrIt;
		::clang::attr::Kind kind = annotate->getKind();
		char const *spelling = annotate->getSpelling();
		::clang::StringRef annotation = annotate->getAnnotation();

		MA_INFO("AnnotatedFunctionCallback",
				"Spelling: %s Annotation: %s Kind: %zu", spelling,
				annotation.str().data(), static_cast<unsigned>(kind));

		MA_INFO("AnnotatedFunctionCallback", "Checking for Annotation: %s",
				m_annotation);

		if (annotation.compare(m_annotation) == 0)
		{
			MA_INFO("AnnotatedFunctionCallback",
					"Found annotated %s function!!!", m_annotation);
			do_cex_run = true;
			break;
		}
	}

	if (!do_cex_run)
	{
		return;
	}

	::clang::FunctionDecl const *definition = funcDecl->getDefinition();

	// compile

	// TODO: useful?
	bool return_test = funcDecl->isNoReturn();
	bool main_test = funcDecl->isMain();
}

} // namespace ast_match
} // namespace msc
