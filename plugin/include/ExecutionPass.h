#pragma once

#include "llvm/Pass.h"

// #include <set>

namespace llvm
{
class Function;
class Module;
} // namespace llvm

namespace msc
{
namespace cex
{
// class ExecutionPass : public ::llvm::ModulePass
class ExecutionPass : public ::llvm::FunctionPass
{
	// std::set<::llvm::Function *> m_annotated_functions;
	llvm::Module *m_module = nullptr;

  public:
	static char ID;
	// ExecutionPass() : ModulePass(ID) {}
	ExecutionPass() : FunctionPass(ID) {}

	// We don't modify the program, so we preserve all analyses.
	void getAnalysisUsage(::llvm::AnalysisUsage &analysisUsage) const override;

	bool doInitialization(::llvm::Module &module) override;

	bool doFinalization(::llvm::Module &module) override;

  private:
	// bool ShouldInstrumentFunc(::llvm::Function &function);

	// void GetAnnotatedFunctions(::llvm::Module *module);

  public:
	bool runOnFunction(::llvm::Function &function) override;
	// bool runOnModule(::llvm::Module &module) override;

	void print(llvm::raw_ostream &out_stream,
			   const ::llvm::Module *module) const override;
};
} // namespace cex
} // namespace msc

// char ExecutionPass::ID = 0;

// static ::llvm::RegisterPass<ExecutionPass>
// X("find-cex", "Aggregate cex annotations", false /* Only looks at CFG */,
//   false /* Analysis Pass */);