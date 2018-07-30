#pragma once

#include "clang/CodeGen/CodeGenAction.h"

namespace clang
{
class ASTConsumer;
class CompilerInstance;
// class ASTFrontendAction;
} // namespace clang

namespace llvm
{
class StringRef;
}

namespace msc
{
namespace cex
{
// class FindNamedFunctionAction : public ::clang::EmitBCAction
class EmitBitcodeAction : public ::clang::EmitLLVMAction
{
  public:
	// EmitBitcodeAction()
	// {

	// }

	std::unique_ptr<clang::ASTConsumer>
	CreateASTConsumer(::clang::CompilerInstance &compiler,
					  ::llvm::StringRef inFile) override;

  protected:
	bool BeginSourceFileAction(::clang::CompilerInstance &compiler) override;

	void EndSourceFileAction() override;
};
} // namespace cex
} // namespace msc