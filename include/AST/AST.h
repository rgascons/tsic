#ifndef __TAISEI_AST__
#define __TAISEI_AST__

#include <string>
#include <vector>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"


using namespace llvm;

class Context {
public:
    static LLVMContext TheContext;
    static IRBuilder<> Builder;
    static std::unique_ptr<Module> TheModule;
    static std::map<std::string, Value*> NamedValues; 
};

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
    virtual ~ExprAST() {}
    virtual Value *codegen() = 0;
};

/// NumberExprAST - Expression class for numeric literals like "1.0"
class NumberExprAST : public ExprAST {
public:
    NumberExprAST(double Val) : Val(Val) {} 
    virtual Value *codegen();

private:
    double Val;
};


/// VariableExprAST - Expression class for referencing a variable.
class VariableExprAST : public ExprAST {
public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
    virtual Value *codegen();
    
private:
    std::string Name;
};


/// BinaryExprAST - Expression class for a binary operator
class BinaryExprAST : public ExprAST {
public:
    BinaryExprAST(char op,
        std::unique_ptr<ExprAST> LHS,
        std::unique_ptr<ExprAST> RHS)
        : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

    virtual Value*codegen();

private:
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;
};



class CallExprAST : public ExprAST {
public:
    CallExprAST(const std::string &Callee,
                std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {};

    virtual Value *codegen();

private:
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;
};


class PrototypeAST {
public:
    PrototypeAST(const std::string &Name, std::vector<std::string> Args)
        : Name(Name), Args(std::move(Args)) {}

    virtual Function *codegen();

    const std::string &getName() const { return Name; }

private:
    std::string Name;
    std::vector<std::string> Args;
};

class FunctionAST {
public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                std::unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}

    virtual Function *codegen();

private:
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;
};

#endif