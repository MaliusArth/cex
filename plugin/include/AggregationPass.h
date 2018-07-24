#pragma once

#include "llvm/Pass.h"

#include <set>

namespace llvm
{
class Function;
class Module;
} // namespace llvm

namespace msc
{
namespace cex
{

class AggregationPass : public ::llvm::FunctionPass
{
	std::set<::llvm::Function *> m_annotated_functions;

  public:
	static char ID;
	AggregationPass() : FunctionPass(ID) {}

	// We don't modify the program, so we preserve all analyses.
	void getAnalysisUsage(::llvm::AnalysisUsage &analysisUsage) const override;

	bool doInitialization(::llvm::Module &module) override;

	bool doFinalization(::llvm::Module &module) override;

  private:
	bool ShouldInstrumentFunc(::llvm::Function &function);

	void FindAnnotatedFunctions(::llvm::Module *module);

  public:
	bool runOnFunction(::llvm::Function &function) override;

	void print(llvm::raw_ostream &out_stream,
			   const ::llvm::Module *module) const override;

	std::set<::llvm::Function *> GetAnnotatedFunctions(void) const
	{
		return m_annotated_functions;
	}
};
} // namespace cex
} // namespace msc

// char AggregationPass::ID = 0;

// static ::llvm::RegisterPass<AggregationPass>
// X("find-cex", "Aggregate cex annotations", false /* Only looks at CFG */,
//   false /* Analysis Pass */);