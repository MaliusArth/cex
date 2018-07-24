#pragma once

// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"

// #include "llvm/ExecutionEngine/GenericValue.h"

#include <memory>
#include <string>

namespace llvm
{
	class LLVMContext;
	class ExecutionEngine;
	class Module;
	class Function;
	class StringRef;
}

namespace msc
{
namespace cex
{

bool initializeNativeTarget(void);

std::unique_ptr<llvm::Module> loadModule(llvm::LLVMContext &llvm_context,
										 std::string ir_file);
llvm::Function const * findFunction(llvm::Module const * const module, llvm::StringRef const signature);

//ExecutionEngine

llvm::ExecutionEngine * createEngine(std::unique_ptr<llvm::Module> unique_module);

// TODO: handle return value
void callFunction(llvm::ExecutionEngine * const engine, llvm::Function const * const function,
					   size_t argc, ...);

inline void callFunction(llvm::ExecutionEngine * const engine, llvm::Function const * const function)
{
	callFunction(engine, function, 0u);
}

// void parseArgs(std::vector<llvm::GenericValue> &out_args, llvm::StringRef in_args_str_ref);

// llvm::GenericValue * runFunction(llvm::Function *function, std::vector<llvm::GenericValue> &args);

// evaluateGenericValue(llvm::GenericValue *value);

} // namespace cex
} // namespace msc