#ifndef __TAISEI_ERROR__
#define __TAISEI_ERROR__

#include <memory>

#include "AST/AST.h"

std::unique_ptr<ExprAST> LogError(const char *Str);
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);
llvm::Value *LogErrorV(const char *Str);

#endif