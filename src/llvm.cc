#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/IRBuilder.h>

#include <llvm/Pass.h>


//class FunctionPass : publ
class TestClass : public llvm::FunctionPass{
  virtual bool runOnFunction(llvm::Function &f){
    if(f.getName().startswith("hello")){
      std::cout << "Function name start with hello\n";
    }
    return false;
  }
  static char ID;
};
char TestClass::ID = 'a';
static llvm::RegisterPass<TestClass> global("test_llvm", "test llvm", false, false);



int main(){
  llvm::LLVMContext& context = llvm::getGlobalContext();
  llvm::Module *module = new llvm::Module("top", context);

  llvm::FunctionType *functionType  = llvm::FunctionType::get(builder.getInt32Ty(), false);
  llvm::Function *mainFunc =
      llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, "main", module);

  llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  llvm::Value *helloWorld = builder.CreateGlobalString("Hello World");

  std::vector<llvm::Type *> putsArgs;
  putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
  llvm::ArrayRef<llvm::Type*> argsRef(putsArgs);

  llvm::FunctionType *putsType = llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
  llvm::Constant *putsFunc = module->getOrInsertFunction("puts", putsType);
                             
  builder.CreateAll(putsFunc, helloWorld);
  builder.CreateRetVoid();
  
  
  module->dump();
}
