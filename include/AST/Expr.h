#ifndef __TSIC_AST_EXPR__
#define __TSIC_AST_EXPR__

#include "Utils/SourceLocation.h"

namespace tsic {

// TODO
class Expr {
public:

private:

}


///
/// 
class IntegerLiteral : public Expr {
	// TODO
}


///
/// 
class FloatingLiteral : public Expr {
	// TODO
}


///
///
class CharacterLiteral : public Expr {
public:
	enum CharacterKind {
		Ascii,
		Wide,
		UTF8,
		UTF16,
		UTF32
	};

private:
	unsigned Value;
	SourceLocation Loc;

public:
	
}


/// String Literal - This represnets a string literal expression. "string"
///
class StringLiteral : public Expr {

}


/// ArraySubscriptExpr - Array subscripting. A[4].
///
class ArraySubscriptExpr : public Expr {
	// TODO
}


/// CallExpr - Represents a function call. f(a, b).
///
class CallExpr : public Expr {
	// TODO
}


/// MemberExpr - Represents a member access expression. X.F.
///
class MemberExpr : public Expr {
	// TODO
}

} // End tsic namespace

#endif