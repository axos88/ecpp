#include "compiler.h"

namespace ECPP {

    static string strip(string input)
    {
        string ws = " \t\r\n";
        string str = input;
        size_t found;
        found = str.find_last_not_of(ws);
        if (found != string::npos)
            str.erase(found+1);
        else
            str.clear();            // str is all whitespace

        found = str.find_first_not_of(ws);
        if (found != string::npos)
            str.erase(0, found);
        else
            str.clear();            // str is all whitespace

        return str;
    }

    string Compiler::renderString(Lexer::Instruction &i)
    {
        return "ret += \"" + strip(i.Contents()) + "\";";
    }
    string Compiler::renderCode(Lexer::Instruction &i)
    {
        return strip(i.Contents());
    }
    string Compiler::renderInclude(Lexer::Instruction &i)
    {
        return "#include \"" + strip(i.Contents()) + "\"\r\n";
    }

    string Compiler::renderPrint(Lexer::Instruction &i)
    {
        return "ret += " + strip(i.Contents());
    }

    pair<string, string> Compiler::render(vector<Lexer::Instruction> &input)
    {
        auto ret = map<string, string>();

        string includes;
        string code;

        for(auto it = input.begin(); it != input.end(); it++)
        {
            Lexer::Instruction i = *it;

            switch(i.Type())
            {
                case Lexer::Instruction::Type::INCLUDE:
                    includes += renderInclude(i);
                    break;
                case Lexer::Instruction::Type::CODE:
                    code += renderCode(i);
                    break;
                case Lexer::Instruction::Type::PRINT:
                    code += renderPrint(i);
                    break;
                case Lexer::Instruction::Type::STRING:
                    code += renderString(i);
                    break;
                default:
                    throw UnknownInstructionType();
            }
        }

        return pair<string, string>(includes, code);
    }
}