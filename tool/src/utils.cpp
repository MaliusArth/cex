
#include "cex/utils.h"

#include "llvm/IR/LLVMContext.h"
// #include "clang/Frontend/CompilerInstance.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

// Concrete ExecutionEngine Implementation Linking
// #include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/MCJIT.h"

#include <llvm/ExecutionEngine/SectionMemoryManager.h>
// #include "llvm/Support/Compiler.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/IR/Module.h"
#include "llvm/Bitcode/BitcodeReader.h"
// #include "llvm/Bitcode/BitcodeWriter.h"
// #include "llvm/Bitcode/BitcodeWriterPass.h"
#include "llvm/Demangle/Demangle.h"
// #include "llvm/IR/Mangler.h"

// #include <memory>
// #include <sstream>

namespace msc
{
namespace cex
{

bool initializeNativeTarget()
{
	bool err;
	err = ::llvm::InitializeNativeTarget();
	assert("Initializing native target failed!" && !err);
	if(err) return err;

	err = ::llvm::InitializeNativeTargetAsmPrinter();
	assert("Initializing native target asm printer failed!" && !err);
	if(err) return err;

	err = ::llvm::InitializeNativeTargetAsmParser();
	assert("Initializing native target asm parser failed!" && !err);
	return err;

	// ::llvm::InitializeNativeTargetDisassembler();

	// llvm::ForceJITLinking::ForceJITLinking();

	// llvm::LinkinJIT();

}

std::unique_ptr<llvm::Module> loadModule(llvm::LLVMContext &llvm_context,
										 std::string ir_file)
{
	std::string error_message;
	std::unique_ptr<llvm::Module> module;

	llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> memory_buffer_or_err =
		llvm::MemoryBuffer::getFile(ir_file);

	if (std::error_code err_code = memory_buffer_or_err.getError())
	{
		error_message =
			"Error loading file into memory buffer: " + err_code.message();
	}
	else
	{
		std::unique_ptr<llvm::MemoryBuffer> &unique_memory_buffer =
			memory_buffer_or_err.get();
		llvm::Expected<std::unique_ptr<llvm::Module>> expected_unique_module =
			llvm::parseBitcodeFile(
				unique_memory_buffer.get()->getMemBufferRef(), llvm_context);
		if (llvm::Error error = expected_unique_module.takeError())
		{
			llvm::handleAllErrors(
				std::move(error), [&](llvm::ErrorInfoBase &EIB) {
					error_message =
						"Error parsing Bitcode file: " + EIB.message();
				});
		}
		else
		{
			module = std::move(expected_unique_module.get() /* .release() */);
		}
	}
	if (!error_message.empty())
	{
		llvm::errs() << error_message << "\n";
	}

	/* 		::llvm::ErrorOr<std::unique_ptr<::llvm::MemoryBuffer>> err_buff
	   =
				::llvm::MemoryBuffer::getFile(ir_file);

			assert("Couldn't create memory buffer from IR file!" &&
	   err_buff);

			std::unique_ptr<::llvm::MemoryBuffer> unique_memory_buffer =
				std::move(err_buff.get());
			::llvm::MemoryBuffer *memory_buffer =
	   unique_memory_buffer.get();
			// llvm::MemoryBufferRef memory_buffer_ref(*(memory_buffer));

			llvm::StringRef mem_buff_str_ref = memory_buffer->getBuffer();
			llvm::errs() << mem_buff_str_ref << "\n";

			std::string error_string;

			// ::llvm::Module *module =
			llvm::Expected<std::unique_ptr<llvm::Module>> expected_module =
				/// Read the header of the specified bitcode buffer and
	   prepare for
				/// lazy
				/// deserialization of function bodies. If
	   ShouldLazyLoadMetadata is
				/// true, lazily load metadata as well. If IsImporting is
	   true, this
				/// module is being parsed for ThinLTO importing into
	   another
				/// module.
				// ::llvm::getLazyBitcodeModule(buff_ref, context, ...);
				::llvm::getOwningLazyBitcodeModule(std::move(unique_memory_buffer),
												   llvm_context, false,
	   false); if (llvm::Error error = expected_module.takeError())
			{
				llvm::handleAllErrors(std::move(error));
				// std::error_code err_code = llvm::errorToErrorCode(error);
				// llvm::errs() << err_code.message << "\n";
			}

			llvm::Expected<std::unique_ptr<llvm::Module>>
	   expected_parsed_module =
				llvm::parseBitcodeFile(memory_buffer->getMemBufferRef(),
									   llvm_context);

			// TODO:
			// llvm::handleExpected(expected_module, ...);
			// if(!expected_module)
			// {
			// llvm::Error err = expected_module.takeError();
			// llvm::errs() << "error loading memory buffer into module";
			assert("Error loading memory buffer into module" &&
	   expected_module);
			// }

			std::unique_ptr<llvm::Module> module =
	   std::move(expected_module.get()); */

	return module;
}

// make an asserted version of this too (assert for dev, err output for
// user)
llvm::Function const * findFunction(llvm::Module const * const module,
							 llvm::StringRef const signature)
{
	// std::string run_func(signature.str());

	if (signature.empty())
	{
		llvm::errs() << "No function name to look for was provided!\n";
		return nullptr;
	}

	// TODO: do this in an earlier stage (AST) and create module from it in
	// memory
	// or get ID through AST and use ID to get function from module
	::llvm::SymbolTableList<llvm::Function> const &funcs = module->getFunctionList();
	size_t buffer_size = 1024u;

	for (llvm::Function const &func : funcs)
	{
		llvm::StringRef module_function_name(func.getName());

		// DEBUG_TYPE("findFunction");

		// llvm::formatv();
		// DEBUG("Module function name: ");
		llvm::errs() << "Module function name: " << module_function_name
					 << "\n";

		std::unique_ptr<char[]> demangled_name =
			llvm::make_unique<char[]>(buffer_size);
		int status;
		llvm::itaniumDemangle(module_function_name.str().data(),
							  demangled_name.get(), &buffer_size, &status);

		llvm::errs() << "Status: " << status << "\n";
		llvm::errs() << "Demangled Name: " << demangled_name.get() << "\n";
		// llvm::StringRef demangled_name_ref(demangled_name);
		if (signature.compare(demangled_name.get()) == 0)
		{
			llvm::errs() << "Function " << signature << " found!\n";
			return &func;
			// break;
		}

		llvm::Optional<uint64_t> optional_entryCount = func.getEntryCount();
		if (optional_entryCount.hasValue())
		{
			llvm::errs() << "EntryCount: " << optional_entryCount.getValue()
						 << "\n";
		}

	}

	// std::string mangled_name;
	// llvm::raw_string_ostream string_stream(mangled_name);
	// llvm::Mangler::getNameWithPrefix(string_stream, signature,
	//  module->getDataLayout());
	// // getMangledName() //ExecutionEngine
	// // std::string module_function_name(string_stream.str());
	// string_stream.flush();
	// llvm::errs() << "Mangled name: " << mangled_name << "\n";

	// llvm::Function *function = module->getFunction(mangled_name);
	// llvm::errs() << "Mangled Name: " << function->getName().str() << "\n";

	// return function;
	return nullptr;
}

llvm::ExecutionEngine * createEngine(std::unique_ptr<llvm::Module> unique_module)
{
	std::string err_str;
	// ::llvm::EngineBuilder engine_builder(std::move(unique_module))
	// .setErrorStr(&err_str);
	// // .setVerifyModules(true);
	// engine_builder.create();
	// ::llvm::Use use;
	// use.set(&engine_builder);

	// ::llvm::Triple triple;
	// ::llvm::TargetMachine *target_machine = engine_builder.selectTarget(
	// // const Triple &TargetTriple,
	// // StringRef MArch,
	// // StringRef MCPU,
	// // const SmallVectorImpl<std::string>& MAttrs
	// );

	// engine_builder.setTargetOptions()

	// ::llvm::ExecutionEngine *engine = engine_builder.create();

	// Now we create the JIT.
	::llvm::ExecutionEngine *engine =
		::llvm::EngineBuilder(std::move(unique_module))
			.setErrorStr(&err_str)
			// .setVerifyModules(true)
			// .setMemoryManager(std::make_unique<llvm::SectionMemoryManager>())
			.setMCJITMemoryManager(llvm::make_unique<llvm::SectionMemoryManager>())
			.create();

	// Check the engine started up correctly here.
	// ...

	if (!engine)
	{
		fprintf(stderr, "Could not create ExecutionEngine: %s\n",
				err_str.c_str());
		// assert("Could not create ExecutionEngine");
		// return nullptr;
		// exit(1);
	}

	// engine->getMangledName();

	return engine;
}

void callFunction(llvm::ExecutionEngine * const engine, llvm::Function const * const function, size_t argc, ...)
{
	// Check the module parsed here.
	// ...

	// use engine builder instead
	// ::llvm::ExecutionEngine *engine =
	// ::llvm::ExecutionEngine::create(module);

	// Check the engine started up correctly here.
	// ...

	// can't call module, ownership has been moved to engine
	// ::llvm::Function *func = module->getFunction(function);

	// Check the function was found here.
	// ..
	// ::llvm::GenericValue val("test");
	// std::vector<::llvm::GenericValue> generic_args;
	// generic_args.reserve(count);

	// va_list args;
	// va_start(args, count);
	// char const *arg;
	// for (size_t i = 0; i < count; ++i)
	// {
	// arg = va_arg(args, char const *);
	// generic_args.emplace_back(arg);
	// }
	// va_end(args);

	// This is what crashes.
	// engine->runFunction(func, generic_args);	//execute main-like function
	// (i.e. those returning void or int, and taking either no
	/// arguments or (int, char*[])).

	// void *function_pointer = engine->getPointerToNamedFunction(function);


	llvm::FunctionType *funcType = function->getFunctionType();

	unsigned int num_params = funcType->getNumParams();
	llvm::errs() << "argc: " << argc << " num_params: " << num_params << "\n";
	assert(argc == num_params);
	for (unsigned int i = 0; i < num_params; i++)
	{
		llvm::Type *paramType;
		paramType = funcType->getParamType(i);
		paramType->dump();

		paramType->print(llvm::outs());
		// paramType->
		// paramType->isFirstClassType();
		// switch(paramType->getTypeID())
		// {
		// case llvm::Type::id
		// }
		// probably need to switch though paramType::ID enum
		// paramType
	}


	// engine->runFunction(function, );



	// MCJIT
	uint64_t function_address = engine->getFunctionAddress(function->getName().str());
	using function_ptr_type = void (*)();

	function_ptr_type function_ptr = reinterpret_cast<function_ptr_type>(function_address);
	function_ptr();


	// Interpreter
	void * function_address2 = engine->getPointerToFunction(const_cast<llvm::Function *>(function));
}

} // namespace cex
} // namespace msc
