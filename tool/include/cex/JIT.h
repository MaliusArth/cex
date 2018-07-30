#pragma once

#include "clang/Frontend/CompilerInstance.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Compiler.h"

#include <cassert>
#include <memory>
#include <string>

namespace msc
{
namespace cex
{

class JIT
{
	llvm::LLVMContext &m_llvm_context;
	clang::CompilerInstance m_compiler_instance;
	llvm::ExecutionEngine *m_execution_engine;

  public:
	explicit JIT(llvm::LLVMContext &llvmContext);

	void addModule(llvm::Module &module);

	// void callFunction(std::string /*::llvm::StringRef*/ signature, size_t argc,
					//   ...);
};

} // namespace cex
} // namespace msc