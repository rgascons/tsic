#ifndef __TSIC_LEX_TOKEN__
#define __TSIC_LEX_TOKEN__

namespace tsic {


enum tok {
    eof = -1,

    // commands
    struct = -2,
    def = -3,
    extern = -4,

    // primary
    identifier = -5,
    number = -6,
};


/// Token
class Token {
	tok Kind;
}

} // End tsic namespace

#endif