#ifndef __TSIC_LEX_TOKEN__
#define __TSIC_LEX_TOKEN__

namespace tsic {


enum tok {
    Eof = -1,

    // commands
    Struct = -2,
    Def = -3,
    Extern = -4,

    // primary
    Identifier = -5,
    Number = -6,
};


/// Token
class Token {
public:
	Token(tok k);
	Token(char c);

	inline bool operator==(const char& rhs){ return true; }
	inline bool operator!=(const char& rhs){ return !operator==(rhs); }

	char as_char();

private:
	tok Kind;
};

} // End tsic namespace

#endif
