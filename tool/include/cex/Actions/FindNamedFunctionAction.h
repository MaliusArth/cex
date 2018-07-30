#pragma once

#include "clang/Frontend/FrontendActions.h"
// #include "clang/Frontend/FrontendAction.h"

#include <memory>

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

// class clang::ASTConsumer;
// class clang::CompilerInstance;
// class llvm::StringRef;

namespace msc
{
namespace cex
{
class FindNamedFunctionAction : public ::clang::ASTFrontendAction
// class FindNamedFunctionAction : public ::clang::GenerateModuleAction
// class FindNamedFunctionAction : public ::clang::EmitLLVMAction
{
  public:
	virtual std::unique_ptr<clang::ASTConsumer>
	CreateASTConsumer(clang::CompilerInstance &compiler,
					  llvm::StringRef inFile);
};
} // namespace cex
} // namespace msc
