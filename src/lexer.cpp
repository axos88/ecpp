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

    Lexer::Instruction Lexer::Instruction::create(string token)
    {
        if (token.find("<% ") == 0)  return Lexer::Instruction::createCodeInstruction(token);
        if (token.find("<%=") == 0)  return Lexer::Instruction::createPrintInstruction(token);
        if (token.find("<%i") == 0)  return Lexer::Instruction::createIncludeInstruction(token);

        return Lexer::Instruction::createStringInstruction(token);
    }

    vector<Lexer::Instruction> Lexer::analyze(vector<string> tokens)
    {
        auto ret = vector<Lexer::Instruction>();

        for(auto it = tokens.begin(); it != tokens.end(); it++)
        {
            string token = *it;

            ret.push_back(Lexer::Instruction::create(token));
        }

        return ret;
    }
}
