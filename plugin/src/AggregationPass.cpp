#include "AggregationPass.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

namespace msc
{
namespace cex
{

static const char *g_annotation_string = "cex_run";

char AggregationPass::ID = 0;

static llvm::RegisterPass<msc::cex::AggregationPass> X("find-cex",
											   "cex function aggregation",
											   true /* Only looks at CFG */,
											   true /* Analysis Pass */);

// We don't modify the program, so we preserve all analyses.
void AggregationPass::getAnalysisUsage(
	llvm::AnalysisUsage &analysisUsage) const
{
	analysisUsage.setPreservesAll();
}

bool AggregationPass::doInitialization(llvm::Module &module)
{

	llvm::errs() << "AggregationPass init" << "\n";
	FindAnnotatedFunctions(&module);
	// module.getContext()

	return false;
}

bool AggregationPass::doFinalization(llvm::Module &module)
{
	llvm::errs() << "AggregationPass final" << "\n";
	return true;
}

bool AggregationPass::ShouldInstrumentFunc(llvm::Function &function)
{
	return m_annotated_functions.find(&function) != m_annotated_functions.end();
}

void AggregationPass::FindAnnotatedFunctions(llvm::Module *module)
{
	// TODO: take a look at the disassembly and find out if saving
	// global_end into a temporary explicitly has a performance advantage
	for (llvm::Module::global_iterator it = module->global_begin(),
										 end = module->global_end();
		 it != end; ++it)
	{
		if (it->getName() == "llvm.global.annotations")
		{
			llvm::ConstantArray *const_array =
				llvm::dyn_cast<llvm::ConstantArray>(it->getOperand(0));
			for (auto OI = const_array->op_begin(); OI != const_array->op_end();
				 ++OI)
			{
				llvm::ConstantStruct *const_struct =
					llvm::dyn_cast<llvm::ConstantStruct>(OI->get());
				llvm::Function *func = llvm::dyn_cast<llvm::Function>(
					const_struct->getOperand(0)->getOperand(0));
				llvm::GlobalVariable *AnnotationGL =
					llvm::dyn_cast<llvm::GlobalVariable>(
						const_struct->getOperand(1)->getOperand(0));
				llvm::StringRef annotation =
					llvm::dyn_cast<llvm::ConstantDataArray>(
						AnnotationGL->getInitializer())
						->getAsCString();
				if (annotation.compare(g_annotation_string) == 0)
				{
					m_annotated_functions.insert(func);
					// errs() << "Found annotated function " <<
					// func->getName()<<"\n";
				}
			}
		}
	}
}

bool AggregationPass::runOnFunction(llvm::Function &function)
{
	if (ShouldInstrumentFunc(function) == false)
		return false;
	llvm::errs() << "Instrumenting " << function.getName() << "\n";

	return false;
}

void AggregationPass::print(llvm::raw_ostream &out_stream,
							const llvm::Module *module) const
{
	out_stream << "analysis debug print stub\n";
}

} // namespace cex
} // namespace msc