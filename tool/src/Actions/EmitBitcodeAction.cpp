
#include "Actions/EmitBitcodeAction.h"

#include "clang/Frontend/CompilerInstance.h"

#include "llvm/ADT/StringRef.h"

#include <memory>

namespace msc
{
namespace cex
{

// EmitBitcodeAction::EmitBitcodeAction()
// {

// }

std::unique_ptr<clang::ASTConsumer>
EmitBitcodeAction::CreateASTConsumer(::clang::CompilerInstance &compiler,
									 ::llvm::StringRef inFile) override
{
	//TODO

	// return ConsumerFactory->newASTConsumer();
}

protected:
bool BeginSourceFileAction(::clang::CompilerInstance &compiler) override
{
	if (!clang::ASTFrontendAction::BeginSourceFileAction(compiler))
	{
		return false;
	}

	//TODO

	return true;
}

void EndSourceFileAction() override
{
	// TODO

	clang::ASTFrontendAction::EndSourceFileAction();
}

} // namespace cex
} // namespace msc
} // namespace msc