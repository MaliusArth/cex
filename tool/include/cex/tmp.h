#pragma once

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace msc
{
namespace tmp
{
llvm::Function * create_custom_module()
{
	// .bc
	// opt -load $LLVM_BUILD/lib/CEXPlugin.so -cex-run [-load pass2] ./test.bc >
	// test_out.bc

	::llvm::LLVMContext llvmContext;

	// Create some module to put our function into it.
	std::unique_ptr<::llvm::Module> unique_module =
		::llvm::make_unique<::llvm::Module>("cexJIT", llvmContext);
	::llvm::Module *module = unique_module.get();

	// Create the add1 function entry and insert this entry into module M.  The
	// function will have a return type of "int" and take an argument of "int".
	::llvm::Function *Add1F =
		::llvm::cast<::llvm::Function>(module->getOrInsertFunction(
			"add1", ::llvm::Type::getInt32Ty(llvmContext),
			::llvm::Type::getInt32Ty(llvmContext)));

	// Add a basic block to the function. As before, it automatically inserts
	// because of the last argument.
	::llvm::BasicBlock *bb =
		::llvm::BasicBlock::Create(llvmContext, "EntryBlock", Add1F);

	// Create a basic block builder with default parameters.  The builder will
	// automatically append instructions to the basic block `BB'.
	::llvm::IRBuilder<> ir_builder(bb);

	// Get pointers to the constant `1'.
	::llvm::Value *One = ir_builder.getInt32(1);

	// Get pointers to the integer argument of the add1 function...
	assert(Add1F->arg_begin() != Add1F->arg_end()); // Make sure there's an arg
	::llvm::Argument *ArgX = &*Add1F->arg_begin();  // Get the arg
	ArgX->setName("AnArg"); // Give it a nice symbolic name for fun.

	// Create the add instruction, inserting it into the end of BB.
	::llvm::Value *Add = ir_builder.CreateAdd(One, ArgX);

	// Create the return instruction and add it to the basic block
	ir_builder.CreateRet(Add);

	// Now, function add1 is ready.

	// Now we're going to create function `foo', which returns an int and takes
	// no arguments.
	::llvm::Function *FooF =
		::llvm::cast<::llvm::Function>(module->getOrInsertFunction(
			"foo", ::llvm::Type::getInt32Ty(llvmContext)));

	// Add a basic block to the FooF function.
	bb = ::llvm::BasicBlock::Create(llvmContext, "EntryBlock", FooF);

	// Tell the basic block builder to attach itself to the new basic block
	ir_builder.SetInsertPoint(bb);

	// Get pointer to the constant `10'.
	::llvm::Value *Ten = ir_builder.getInt32(10);

	// Pass Ten to the call to Add1F
	::llvm::CallInst *Add1CallRes = ir_builder.CreateCall(Add1F, Ten);
	Add1CallRes->setTailCall(true);

	// Create the return instruction and add it to the basic block.
	ir_builder.CreateRet(Add1CallRes);

	return FooF;
}

} // namespace tmp
} // namespace msc