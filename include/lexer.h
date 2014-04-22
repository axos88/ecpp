#ifndef __LEXER_H__
#define __LEXER_H__

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

                    static Instruction createStringInstruction(string token) { return Instruction(Type::STRING, token, "", ""); }
                    static Instruction createCodeInstruction(string token) { return Instruction(Type::CODE, token, "<% ", "%>"); }
                    static Instruction createPrintInstruction(string token) { return Instruction(Type::PRINT, token, "<%=", "%>"); }
                    static Instruction createIncludeInstruction(string token) { return Instruction(Type::INCLUDE, token, "<%i", "%>"); }

                    static Instruction create(string token);
            };

            vector<Instruction> analyze(vector<string> tokens);
    };

};

#endif