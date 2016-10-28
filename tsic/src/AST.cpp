#include "AST.h"
#include "Error.h"

LLVMContext Context::TheContext;
IRBuilder<> Context::Builder = IRBuilder<>(TheContext);
std::unique_ptr<Module> Context::TheModule;
std::map<std::string, Value*> Context::NamedValues; 

Value *NumberExprAST::codegen() {
    return ConstantFP::get(Context::TheContext, APFloat(Val));
}

Value *VariableExprAST::codegen() {
    Value *V = Context::NamedValues[Name];
    if (!V)
        LogErrorV("Unknown variable name");
    return V;
}

Value *BinaryExprAST::codegen() {
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    if (!L || !R)
        return nullptr;

    switch (Op)
    {
    case '+':
        return Context::Builder.CreateFAdd(L, R, "addtmp");
    case '-':
        return Context::Builder.CreateFSub(L, R, "subtmp");
    case '*':
        return Context::Builder.CreateFMul(L, R, "multmp");
    case '<':
        L = Context::Builder.CreateFCmpULT(L, R, "cmptmp");
        return Context::Builder.CreateUIToFP(L, Type::getDoubleTy(Context::TheContext), "booltmp");
    default:
        return LogErrorV("Invalid binary operator");
    }
}

Value *CallExprAST::codegen() {
    Function *CalleeF = Context::TheModule->getFunction(Callee);
    if (!CalleeF)
        return LogErrorV("Unknown function referenced");

    if (CalleeF->arg_size() != Args.size())
        return LogErrorV("Incorrect # arguments passed");

    std::vector<Value*> ArgsV;
    for (unsigned i = 0, e = Args.size(); i != e; ++i) {
        ArgsV.push_back(Args[i]->codegen());
        if (!ArgsV.back())
            return nullptr;
    }

    return Context::Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Function *PrototypeAST::codegen() {
    std::vector<Type*> Doubles(Args.size(), Type::getDoubleTy(Context::TheContext));
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(Context::TheContext), Doubles, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, Name, Context::TheModule.get());

    unsigned Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(Args[Idx++]);

    return F;
}

Function *FunctionAST::codegen() {
    Function *TheFunction = Context::TheModule->getFunction(Proto->getName());

    if (!TheFunction)
        TheFunction = Proto->codegen();

    if (!TheFunction)
        return nullptr;

    if (!TheFunction->empty())
        return (Function*)LogErrorV("Function cannot be redefined");

    BasicBlock *BB = BasicBlock::Create(Context::TheContext, "entry", TheFunction);
    Context::Builder.SetInsertPoint(BB);

    Context::NamedValues.clear();
    for (auto &Arg : TheFunction->args())
        Context::NamedValues[Arg.getName()] = &Arg;

    if (Value *RetVal = Body->codegen()) {
        Context::Builder.CreateRet(RetVal);

        verifyFunction(*TheFunction);

        return TheFunction;
    }

    TheFunction->eraseFromParent();
    return nullptr;
}