
#include "cex/JIT.h"
#include "cex/utils.h"

#include "llvm/IR/Module.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

// #include "llvm/Bitcode/BitcodeReader.h"
// #include "llvm/Bitcode/BitcodeWriter.h"
// #include "llvm/Bitcode/BitcodeWriterPass.h"

namespace msc
{
namespace cex
{

JIT::JIT(llvm::LLVMContext &llvm_context) : m_llvm_context(llvm_context) //,
//   m_compiler_instance(),
//   m_execution_engine()
{

	bool err;
	err = ::llvm::InitializeNativeTarget();
	assert("Initializing native target failed!" && !err);

	err = ::llvm::InitializeNativeTargetAsmPrinter();
	assert("Initializing native target asm printer failed!" && !err);

	err = ::llvm::InitializeNativeTargetAsmParser();
	assert("Initializing native target asm parser failed!" && !err);
}

void JIT::addModule(llvm::Module &module)
{

}

// void JIT::callFunction(std::string file,
					//    std::string /*::llvm::StringRef*/ function,
					//    size_t function_argc, ...)
// void JIT::callFunction(std::string /*::llvm::StringRef*/ signature, size_t argc,
					//   ...);
// {
	// // bool initialized = ::llvm::InitializeNativeTarget();
	// // assert(initialized);

	// // TrivialModuleLoader -> clang/Lex/ModuleLoader.h
	// std::unique_ptr<llvm::Module> unique_module =
		// msc::cex::loadModule(m_llvm_context, file);
	// llvm::Module *module = unique_module.get();
	// assert(module);

	// llvm::Function *func = msc::cex::findFunction(module, signature);

	// std::string err_str;
	// // ::llvm::EngineBuilder(std::move(unique_module))
	// // .setErrorStr(&err_str)
	// // // .setVerifyModules(true)
	// // .create();
	// // ::llvm::Use use;
	// // use.set(&engine_builder);

	// // ::llvm::Triple triple;
	// // ::llvm::TargetMachine *target_machine = engine_builder.selectTarget(
	// // // const Triple &TargetTriple,
	// // // StringRef MArch,
	// // // StringRef MCPU,
	// // // const SmallVectorImpl<std::string>& MAttrs
	// // );

	// // engine_builder.setTargetOptions()

	// // Now we create the JIT.
	// ::llvm::ExecutionEngine *engine =
		// ::llvm::EngineBuilder(std::move(unique_module))
			// .setErrorStr(&err_str)
			// // .setVerifyModules(true)
			// .create();

	// if (!engine)
	// {
		// fprintf(stderr, "Could not create ExecutionEngine: %s\n",
				// err_str.c_str());
		// return;
		// // exit(1);
	// }

	// // Check the module parsed here.
	// // ...

	// // use engine builder instead
	// // ::llvm::ExecutionEngine *engine =
	// // ::llvm::ExecutionEngine::create(module);

	// // Check the engine started up correctly here.
	// // ...

	// // can't call module, ownership has been moved to engine
	// // ::llvm::Function *func = module->getFunction(function);

	// // Check the function was found here.
	// // ..
	// // ::llvm::GenericValue val("test");
	// // std::vector<::llvm::GenericValue> generic_args;
	// // generic_args.reserve(count);

	// // va_list args;
	// // va_start(args, count);
	// // char const *arg;
	// // for (size_t i = 0; i < count; ++i)
	// // {
	// // arg = va_arg(args, char const *);
	// // generic_args.emplace_back(arg);
	// // }
	// // va_end(args);

	// // This is what crashes.
	// // engine->runFunction(func, generic_args);	//execute main-like function
	// // (i.e. those returning void or int, and taking either no
	// /// arguments or (int, char*[])).

	// void *function_pointer = engine->getPointerToNamedFunction(function);

	// uint64_t functionAddress = engine->getFunctionAddress(function);

	// llvm::FunctionType *funcType = func->getFunctionType();

	// unsigned int num_params = funcType->getNumParams();
	// for (unsigned int i = 0; i < num_params; i++)
	// {
		// llvm::Type *paramType;
		// paramType = funcType->getParamType(i);
		// paramType->dump();

		// paramType->print(llvm::outs());
		// // paramType->
		// // paramType->isFirstClassType();
		// // switch(paramType->getTypeID())
		// // {
		// // case llvm::Type::id
		// // }
		// // probably need to switch though paramType::ID enum
		// // paramType
	// }

	// using function_ptr = void(int, int);
	// uint64_t function_address = engine->getFunctionAddress(function);
// }

/* void InitializeModuleAndPassManager(::llvm::Module &module)
{
	// Open a new module.
	module = llvm::make_unique<Module>("my cool jit", llvmContext);
	module->setDataLayout(JIT->getTargetMachine().createDataLayout());

	// Create a new pass manager attached to it.
	TheFPM = llvm::make_unique<legacy::FunctionPassManager>(TheModule.get());

	// Do simple "peephole" optimizations and bit-twiddling optzns.
	TheFPM->add(createInstructionCombiningPass());
	// Reassociate expressions.
	TheFPM->add(createReassociatePass());
	// Eliminate Common SubExpressions.
	TheFPM->add(createGVNPass());
	// Simplify the control flow graph (deleting unreachable blocks, etc).
	TheFPM->add(createCFGSimplificationPass());

	TheFPM->doInitialization();
} */
} // namespace cex
} // namespace msc