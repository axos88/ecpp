#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace ECPP {

    class Lexer {

        public:
            class InvalidTokenError { };

            class Instruction
            {
                public:
                    enum InstructionType {
                        STRING_INSTRUCTION,
                        CODE_INSTRUCTION,
                        PRINT_INSTRUCTION,
                        INCLUDE_INSTRUCTION
                    };

                private:
                    InstructionType type;
                    string contents;

                public:
                    Instruction(InstructionType type, string token, string beginTag = "", string endTag = "") : type(type)
                    {
                        if (token.find(beginTag) != 0) throw InvalidTokenError();
                        if (token.rfind(endTag) != token.length() - endTag.length()) throw InvalidTokenError();

                        contents = token.substr(beginTag.length(), token.length() - beginTag.length() - endTag.length());
                    }

                    string Contents() { return contents; }
                    InstructionType Type() { return type; }

                    static Instruction createStringInstruction(string contents) { return Instruction(Instruction::STRING_INSTRUCTION, contents, "", ""); }
                    static Instruction createCodeInstruction(string contents) { return Instruction(Instruction::CODE_INSTRUCTION, contents, "<% ", "%>"); }
                    static Instruction createPrintInstruction(string contents) { return Instruction(Instruction::PRINT_INSTRUCTION, contents, "<%=", "%>"); }
                    static Instruction createIncludeInstruction(string contents) { return Instruction(Instruction::INCLUDE_INSTRUCTION, contents, "<%i", "%>"); }
            };

            vector<Instruction> analyze(vector<string> tokens);
    };

};