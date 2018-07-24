#include "ExecutionPass.h"
// #include "AggregationPass.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
// #include "llvm/Support/Options.h"
#include "llvm/Demangle/Demangle.h"
#include "llvm/ADT/STLExtras.h"


#include <set>
#include <string>
// #include <memory>
// #include <bits/unique_ptr.h>

//undefined symbol: _ZTVN4llvm2cl3optINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEELb0ENS0_6parserIS7_EEEE
// llvm::cl::opt<__cxx11::basic_string, char_traits, ESa, EL parser>
// template <class DataType, bool ExternalStorage = false,
        //   class ParserClass = parser<DataType>>

// llvm::cl::opt<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, false, llvm::cl::parser<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>>


namespace
{
// Apply a custom category to all command-line options so that they are the
// only ones displayed.
// static llvm::cl::OptionCategory cexCategory("cexPlugin Options");

// template <class DataType, bool ExternalStorage = false,
//   class ParserClass = parser<DataType>>
// class opt : public Option,
            // public opt_storage<DataType, ExternalStorage,
                            //    std::is_class<DataType>::value>
// static llvm::cl::opt<std::string>
	// runOpt("run", llvm::cl::desc("function to run at compile-time"),
		//    llvm::cl::value_desc("file path"), llvm::cl::cat(cexCategory));

}

namespace msc
{
namespace cex
{
// static const char *g_annotation_string = "cex_run";
static const char *g_annotation_string = "cex_run()";
// static const char *g_annotation_string = "cex_run(7)";

char ExecutionPass::ID = 0;

static ::llvm::RegisterPass<msc::cex::ExecutionPass>
	X("run-cex", "cex function execution", false /* Only looks at CFG */,
	  false /* Analysis Pass */);

// We don't modify the program, so we preserve all analyses.
void ExecutionPass::getAnalysisUsage(::llvm::AnalysisUsage &analysisUsage) const
{
	// analysisUsage.addRequired<msc::cex::AggregationPass>();
	// analysisUsage.addUsedIfAvailable<msc::cex::AggregationPass>();
}

bool ExecutionPass::doInitialization(::llvm::Module &module)
{
	llvm::errs() << "ExecutionPass init\n";
	// GetAnnotatedFunctions(&module);

	// std::string run_func = runOpt.getValue();
	std::string run_func(g_annotation_string);

	if (run_func.empty())
	{
		llvm::errs() << "No function to compile-time execute.\n";
		return false;
	}

	m_module = &module;
	llvm::Function *function = m_module->getFunction(run_func);

	// if(!function)
	// {
		// llvm::errs() << "Function '" << run_func << "' not found!\n";
		// return false;
	// }
	// assert("Function not found!" && function);
	llvm::errs() << "Mangled Name: " << function->getName().str() << "\n";
	size_t buffer_size = 1024u;
	std::unique_ptr<char[]> demangled_name = llvm::make_unique<char[]>(buffer_size);
	int status;
	llvm::itaniumDemangle(function->getName().str().data(), demangled_name.get(), &buffer_size, &status);
	llvm::errs() << "Status: " << status << "\n";
	llvm::errs() << "Demangled Name: " << demangled_name.get() << "\n";
	// delete[] demangled_name;

	llvm::Optional<uint64_t> optional_entryCount = function->getEntryCount();
	if(optional_entryCount.hasValue())
	{
		llvm::errs() << "EntryCount: " << optional_entryCount.getValue() << "\n";
	}

	return true;
}

bool ExecutionPass::doFinalization(::llvm::Module &module)
{
	llvm::errs() << "ExecutionPass final\n";
	return true;
}

// bool ExecutionPass::ShouldInstrumentFunc(::llvm::Function &function)
// {
	// return m_annotated_functions.find(&function) != m_annotated_functions.end();
// return m_annotated_functions.find(&function) != m_annotated_functions.end();
// }

// void ExecutionPass::GetAnnotatedFunctions(::llvm::Module *module) {}

// bool ExecutionPass::runOnModule(::llvm::Module &module)
bool ExecutionPass::runOnFunction(::llvm::Function &function)
{
	llvm::errs() << "ExecutionPass::runOnFunction\n";
	llvm::errs() << "Running on " << function.getName() << "\n";
	// if (run_func.empty())
	// {
		// return false;
	// }

	// if(function.getName().compare(run_func_name) == 0)
	// std::string run_func_call = runOpt.getValue();
	static std::string const run_func_call(g_annotation_string);
	llvm::StringRef func_name(run_func_call);

	size_t func_args_pos = func_name.find('(');
	llvm::StringRef func_args = func_name.drop_front(func_args_pos + 1);
	func_name = func_name.take_front(func_args_pos);

	llvm::errs() << "function name: " << func_name << "\n";
	llvm::errs() << "function args: " << func_args << "\n";

	// function.getReturnType();
	// TODO:
	// msc::cex::AggregationPass &analysis =
		// getAnalysis<msc::cex::AggregationPass>(/* function */);
	// std::set<::llvm::Function *> functions = analysis.GetAnnotatedFunctions();

	// function.dump();

	if (function.getName().compare(func_name) != 0)
	{
		return true;
	}
	// execute function
	llvm::errs() << " --- Found function!\n";

	// for (::llvm::Function *function : functions)
	// {
		// ::llvm::errs() << "Executing " << function->getName() << "\n";
		// function->dump();
		// /* code */
	// }
	// Result

	return false;
}

void ExecutionPass::print(::llvm::raw_ostream &out_stream,
						  const ::llvm::Module *module) const
{
	out_stream << "execution debug print stub\n";
}

} // namespace cex
} // namespace msc