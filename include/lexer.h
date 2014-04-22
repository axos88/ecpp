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
                    enum class Type {
                        STRING,
                        CODE,
                        PRINT,
                        INCLUDE
                    };
                private:
                    Type type;
                    string contents;

                public:
                    Instruction(Type type, string token, string beginTag = "", string endTag = "");

                    string Contents() { return contents; }
                    Type Type() { return type; }

                    static Instruction createStringInstruction(string contents) { return Instruction(Type::STRING, contents, "", ""); }
                    static Instruction createCodeInstruction(string contents) { return Instruction(Type::CODE, contents, "<% ", "%>"); }
                    static Instruction createPrintInstruction(string contents) { return Instruction(Type::PRINT, contents, "<%=", "%>"); }
                    static Instruction createIncludeInstruction(string contents) { return Instruction(Type::INCLUDE, contents, "<%i", "%>"); }
            };

            vector<Instruction> analyze(vector<string> tokens);
    };

};