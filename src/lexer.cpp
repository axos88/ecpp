#include "lexer.h"

using namespace std;
using namespace ECPP;

namespace ECPP {
    Lexer::Instruction::Instruction(enum Type type, string token, string beginTag, string endTag) : type(type)
    {
        if (token.find(beginTag) != 0) throw InvalidTokenError();
        if (token.rfind(endTag) != token.length() - endTag.length()) throw InvalidTokenError();

        contents = token.substr(beginTag.length(), token.length() - beginTag.length() - endTag.length());
    }
}
