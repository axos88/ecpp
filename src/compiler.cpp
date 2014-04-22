#include "compiler.h"

namespace ECPP {

    string Compiler::renderString(Lexer::Instruction &i)
    {
        return "ret += \"" + i.Contents() + "\";";
    }
    string Compiler::renderCode(Lexer::Instruction &i)
    {
        return i.Contents();
    }
    string Compiler::renderInclude(Lexer::Instruction &i)
    {
        return "#include \"" + i.Contents() + "\"\r\n";
    }

    string Compiler::renderPrint(Lexer::Instruction &i)
    {
        return "ret += " + i.Contents() + ";";
    }

    map<string, string> Compiler::render(vector<Lexer::Instruction> &input)
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

        ret["include"] = includes;
        ret["code"] = code;

        return ret;
    }
}